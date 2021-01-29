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
      print 'data is not loaded properly'
      self.bad = True

    # open the trained model
    try:
#      self.model = load_model('models/{}.hdf5'.format(model_name))
      self.model = load_model('{}'.format(model_name))
#      self.model=   load_model('models/outputModel_wis.hdf5')
    except:
      print 'model is not loaded properly'
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
#      print 'guess not found'
      guess= -999
    
    return guess

def run_process(proc):
    print proc
    return call(proc, shell=True)


def fillFile(ifile, channel, args, boost_pred, treeName):
  fname = ifile.split('/')[-1].split('.root')[0]
  print 'Starting process for file: {}'.format(fname)
    
  boost_pred.make_prediction(fname, channel)
  print 'not predict yet'

  ## now let's try and get this into the root file
  root_file = TFile(ifile, 'READ')
  itree = root_file.Get(treeName)
#  itree = root_file.Get(args.treename)
  

  oname = ifile.split('/')[-1].split('.root')[0]
  fout = TFile('{}/{}.root'.format(args.output_dir, oname), 'recreate')  ## make new file for output
  fout.cd()
#  nevents = root_file.Get('nevents').Clone()
#  nevents.Write()
  ntree = itree.CloneTree(-1, 'fast')

  branch_var = array('f', [0.])
  disc_branch_boost = ntree.Branch('NN_disc', branch_var, 'NN_disc/F')
  nevts = ntree.GetEntries()
  
  evt_index = 0
  for _ in itree:
    if evt_index % 10000 == 0 and evt_index > 0:
      print 'Process: {} has completed: {} events out of {}'.format(fname, evt_index, nevts)
    branch_var[0]= boost_pred.getGuess(evt_index)
#    print 'branch_var= ', branch_var

    evt_index += 1
    fout.cd()
    disc_branch_boost.Fill()


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
    elif '_tt_' in args.input_dir:
        channel = 'tt'
        treeName = 'tautau_tree'
    else:
        raise Exception('Hey. Bad channel. No. Try again.')

#    if args.treename == 'mutau_tree':
#        channel = 'mt'
#    elif args.treename == 'etau_tree':
#        channel = 'et'
#    elif args.treename == 'emu_tree':
#        channel = 'em'
#    elif args.treename == 'tautau_tree':
#        channel = 'tt'
#    else:
#        raise Exception('Hey. Bad channel. No. Try again.')
#
#

    if not path.isdir(args.output_dir):
        mkdir(args.output_dir)

    file_names = [ifile for ifile in glob('{}/*.root'.format(args.input_dir))]

    keep_boost = [
                'lep1Pt','lep2Pt','Met','m_sv', 'LeadJetPt','higgs_m','higgs_pT','st','tmass'
                ]

    boost_pred = Predictor(args.input_boost, args.model_boost, keep_boost)

    processes = [fillFile(ifile, channel, args, boost_pred, treeName) for ifile in file_names]
    
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
#    parser.add_argument('--treename', '-t', action='store', dest='treename', default='etau_tree', help='name of input tree')
    parser.add_argument('--model-boost', '-m', action='store', dest='model_boost', default=None, help='name of model to use')
    parser.add_argument('--input-boost', '-i', action='store', dest='input_boost', default=None, help='name of input dataset')
    parser.add_argument('--dir', '-d', action='store', dest='input_dir', default='input_files/etau_stable_Oct24', help='name of ROOT input directory')
    parser.add_argument('--output-dir', '-o', action='store', dest='output_dir', default='output_files', help='name of directory for output')


    main(parser.parse_args())
