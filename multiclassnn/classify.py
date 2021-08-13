import pandas as pd
from subprocess import call
import multiprocessing
from ROOT import TFile
from glob import glob
from array import array
from os import environ, path, mkdir
from multiprocessing import Process
environ['KERAS_BACKEND'] = 'tensorflow'
from keras.models import load_model
from sklearn.preprocessing import StandardScaler

class Predictor:
  def __init__(self, data_name, model_name):
    self.bad = False
#    self.keep = keep
    self.data_copy = pd.DataFrame()
    # open the input data
    try:
      self.data = pd.HDFStore(data_name)['df']
    except:
      self.bad = True
      raise Exception('check {} for df'.format(data_name))

    # open the trained model
    try:
      self.model = load_model(model_name)
    except:
      self.bad = True
      raise Exception(model_name)

  def make_prediction(self, fname, channel, transform,nominal_input):
    self.data_copy = self.data_copy.iloc[0:0]
    if not self.bad:
      self.data_copy = self.data[
              (self.data['sample_names'] == fname) & (self.data['lepton'] == channel)
          ].copy()

#       get scaler setup
      scaler = StandardScaler()
      scaler_info = pd.HDFStore(nominal_input)['scaler']
      scaler_info = scaler_info.drop('isSM', axis=0)
      scaler.mean_ = scaler_info['mean'].values.reshape(1, -1)
      scaler.scale_ = scaler_info['scale'].values.reshape(1, -1)
      scaler_columns = scaler_info.index.values

      
      to_classify = self.data_copy[scaler_columns]


      if transform:
          print '\n the features are now being transformed ....'
          scaled = pd.DataFrame(
              scaler.transform(to_classify.values),
              columns=to_classify.columns.values, dtype='float64')

          guesses = self.model.predict(scaled.values, verbose=False)

      else:
          print '\n No feature transformation takes place ....'
          guesses = self.model.predict(to_classify.values, verbose=False)

      
      self.data_copy['guess_sig'] = guesses[:,0]
      self.data_copy['guess_bkg1'] = guesses[:,1]
      self.data_copy['guess_bkg2'] = guesses[:,2]
      self.data_copy.set_index('idx', inplace=True)

  def getGuess(self, index):
    try:
      guess = self.data_copy.loc[index, 'guess_sig']
      guess1 = self.data_copy.loc[index, 'guess_bkg1']
      guess2 = self.data_copy.loc[index, 'guess_bkg2']
    except:
      guess,guess1,guess2 = -999,-999,-999
    
    return guess,guess1,guess2

def run_process(proc):
    print proc
    return call(proc, shell=True)


def fillFile(ifile, channel, args, boost_pred, treeName):
  fname = ifile.split('/')[-1].split('.root')[0]
  print 'Starting process for file: {}'.format(fname)

  boost_pred.make_prediction(fname, channel, args.Transform, args.nominal_input)

  ## now let's try and get this into the root file
  root_file = TFile(ifile, 'READ')
  itree = root_file.Get(treename)


  oname = ifile.split('/')[-1].split('.root')[0]
  fout = TFile('{}/{}.root'.format(args.output_dir, oname), 'recreate')  ## make new file for output
  fout.cd()
  nevents = root_file.Get('nevents').Clone()
  nevents.Write()
  ntree = itree.CloneTree(-1, 'fast')

  branch_var = array('f', [0.])
  branch_var1 = array('f', [0.])
  branch_var2 = array('f', [0.])
  disc_branch = ntree.Branch('NN_disc', branch_var, 'NN_disc/F')
  disc_branch1 = ntree.Branch('NN_disc_QCD', branch_var1, 'NN_disc_QCD/F')
  disc_branch2 = ntree.Branch('NN_disc_ZTT', branch_var2, 'NN_disc_ZTT/F')
  nevts = ntree.GetEntries()
  
  evt_index = 0
  for _ in itree:
    if evt_index % 100000 == 0 and evt_index > 0:
      print 'Process: {} has completed: {} events out of {}'.format(fname, evt_index, nevts)
    branch_var[0],branch_var1[0],branch_var2[0] = boost_pred.getGuess(evt_index)

    evt_index += 1
    fout.cd()
    disc_branch.Fill()
    disc_branch1.Fill()
    disc_branch2.Fill()


  root_file.Close()
  fout.cd()
  ntree.Write()
  fout.Close()
  print '{} Completed.'.format(fname)

def main(args):


    print 'args.input_dir is ', args.input_dir
    if '_mt_' in args.input_dir:
        channel = 'mt'
        treeName = 'mutau_tree'
    elif '_et_' in args.input_dir:
        channel = 'et'
        treeName = 'etau_tree'
    elif '_em_' in args.input_dir:
        channel = 'em'
        treeName = 'emu_tree'
    elif '_me_' in args.input_dir:
        channel = 'me'
        treeName = 'emu_tree'
    elif '_tt_' in args.input_dir:
        channel = 'tt'
        treeName = 'tautau_tree'
    else:
        raise Exception('Hey. Bad channel. No. Try again.')


    if not path.isdir(args.output_dir):
        mkdir(args.output_dir)

    file_names = [ifile for ifile in glob('{}/*.root'.format(args.input_dir))]

#    keep_vbf = [
#                'njets','mt','mu_iso','mjj', 'higgs_pT','m_sv','Q2V1', 'Q2V2', 'Phi0', 'Phi1', 'costheta1', 'costheta2', 'costhetastar'
#                ]

#    boost_pred = Predictor(args.input_boost, args.model_boost, keep_vbf)
    boost_pred = Predictor(args.input_boost, args.model_boost)
    processes = [Process(target=fillFile, args=(ifile, channel, args, boost_pred,treeName)) for ifile in file_names]
    
    
#    n_processes = min(8, multiprocessing.cpu_count() / 2)
#    print multiprocessing.cpu_count(), "  n_process= ",n_processes
#    pool = multiprocessing.Pool(processes=n_processes)
#    print processes
#    r = pool.map_async(run_process, processes)
#    r.wait()
    
    
    for process in processes:
      process.start()
    for process in processes:
      process.join()

    print 'Finished processing.'


if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser()
#    parser.add_argument('--treename', '-t', action='store', dest='treename', default='etau_tree', help='name of input tree')
    parser.add_argument('--model-boost', '-m', action='store', dest='model_boost', default=None, help='name of model to use')
    parser.add_argument('--input-boost', '-i', action='store', dest='input_boost', default=None, help='name of input dataset')
    parser.add_argument('--dir', '-d', action='store', dest='input_dir', default='input_files/etau_stable_Oct24', help='name of ROOT input directory')
    parser.add_argument('--output-dir', '-o', action='store', dest='output_dir', default='output_files', help='name of directory for output')
    parser.add_argument('--Transform', '-s', action='store', dest='Transform', default=False, help='Trasnform the features or not')
    parser.add_argument('--nominal_input', '-n', action='store', dest='nominal_input', default=None, help='name of nominal_input file')


    main(parser.parse_args())
