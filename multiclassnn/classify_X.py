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

class Predictor:
  def __init__(self, data_name, model_name, keep):
    self.bad = False
    self.keep = keep
    self.data_copy = pd.DataFrame()
    # open the input data
    try:
      self.data = pd.HDFStore(data_name)['df']
#      self.data = pd.HDFStore('datasets/testData_wis.h5')['df']
    except:
      self.bad = True

    # open the trained model
    try:
      self.model = load_model('models/{}.hdf5'.format(model_name))
#      self.model=   load_model('models/outputModel_wis.hdf5')
    except:
      self.bad = True

  def make_prediction(self, fname, channel):
    print fname, channel
    self.data_copy = self.data_copy.iloc[0:0]
    if not self.bad:
      self.data_copy = self.data[
#              (self.data['sample_names'] == fname) & (self.data['lepton'] == channel)
              (self.data['sample_names'] == fname)
          ].copy()
      print 'to_classify'
      to_classify = self.data_copy[self.keep]
#      print to_classify
      self.model.summary()
      print "to_classify.values", to_classify.values
      guesses = self.model.predict(to_classify.values, verbose=True)
      print 'is now predicted'
      self.data_copy['guess_sig'] = guesses[:,0]
      self.data_copy.set_index('idx', inplace=True)


  def getGuess(self, index):
    try:
      guess = self.data_copy.loc[index, 'guess_sig']
    except:
      guess= -999
    
    return guess

def run_process(proc):
    print proc
    return call(proc, shell=True)


def fillFile(ifile, channel, args, vbf_pred):
  fname = ifile.split('/')[-1].split('.root')[0]
  print 'Starting process for file: {}'.format(fname)
    
  vbf_pred.make_prediction(fname, channel)
#  boost_pred.make_prediction(fname, channel)
  print 'not predict yet'

  ## now let's try and get this into the root file
  root_file = TFile(ifile, 'READ')
  itree = root_file.Get(args.treename)

  oname = ifile.split('/')[-1].split('.root')[0]
  fout = TFile('{}/{}.root'.format(args.output_dir, oname), 'recreate')  ## make new file for output
  fout.cd()
#  nevents = root_file.Get('nevents').Clone()
#  nevents.Write()
  ntree = itree.CloneTree(-1, 'fast')

  branch_var = array('f', [0.])
  disc_branch_vbf = ntree.Branch('NN_disc', branch_var, 'NN_disc/F')
  nevts = ntree.GetEntries()
  
  evt_index = 0
  for _ in itree:
    if evt_index % 10000 == 0 and evt_index > 0:
      print 'Process: {} has completed: {} events out of {}'.format(fname, evt_index, nevts)
    branch_var[0]= vbf_pred.getGuess(evt_index)
#    print 'branch_var= ', branch_var

    evt_index += 1
    fout.cd()
    disc_branch_vbf.Fill()


  root_file.Close()
  fout.cd()
  ntree.Write()
  fout.Close()
  print '{} Completed.'.format(fname)

def main(args):
    if args.treename == 'emu_tree':
        channel = 'mt'
#    elif args.treename == 'etau_tree':
#        channel = 'et'
    else:
        raise Exception('Hey. Bad channel. No. Try again.')

    if not path.isdir(args.output_dir):
        mkdir(args.output_dir)

    file_names = [ifile for ifile in glob('{}/*.root'.format(args.input_dir))]

    keep_vbf = [
#                'taupt','Met','vis_mass', 'LeadJetPt','higgs_pT','higgs_m'
                'vis_mass','higgs_pT','mjj','m_sv','Q2V1', 'Q2V2', 'Phi', 'Phi1', 'costheta1', 'costheta2', 'costhetastar'
                ]

    vbf_pred = Predictor(args.input_vbf, args.model_vbf, keep_vbf)

    processes = [fillFile(ifile, 'mt', args, vbf_pred) for ifile in file_names]
    
#    n_processes = min(8, multiprocessing.cpu_count() / 2)
#    print multiprocessing.cpu_count(), "  n_process= ",n_processes
#    pool = multiprocessing.Pool(processes=n_processes)
#    print processes
#    r = pool.map_async(run_process, processes)
#    r.wait()
    
    
#    for process in processes:
#      process.start()
#    for process in processes:
#      process.join()

    print 'Finished processing.'


if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser()
    parser.add_argument('--treename', '-t', action='store', dest='treename', default='etau_tree', help='name of input tree')
    parser.add_argument('--model-vbf', action='store', dest='model_vbf', default=None, help='name of model to use')
#    parser.add_argument('--model-boost', action='store', dest='model_boost', default=None, help='name of model to use')
    parser.add_argument('--input-vbf', action='store', dest='input_vbf', default=None, help='name of input dataset')
#    parser.add_argument('--input-boost', action='store', dest='input_boost', default=None, help='name of input dataset')
    parser.add_argument('--dir', '-d', action='store', dest='input_dir', default='input_files/etau_stable_Oct24', help='name of ROOT input directory')
    parser.add_argument('--output-dir', '-o', action='store', dest='output_dir', default='output_files', help='name of directory for output')


    main(parser.parse_args())
