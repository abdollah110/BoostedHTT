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



def make_prediction(fname, channel):
    data = pd.HDFStore('datasets/testData.h5')['df']
    model=   load_model('models/outputModel_wis.hdf5')
    keep = ['muPt','taupt','lepIso','tmass', 'ht','Met','LeadJetPt', 'dR_mu_tau']
    data_copy = pd.DataFrame()
    data_copy = data_copy.iloc[0:0]
    data_copy = data[(data['sample_names'] == fname)].copy()
              
    to_classify = data_copy[keep]
    model.summary()
    guesses = model.predict(to_classify.values, verbose=True)
    print guesses



def fillFile(ifile, channel):
      fname = ifile.split('/')[-1].split('.root')[0]
      print 'Starting process for file: {}'.format(fname)
      make_prediction(fname, channel)


file_names = [ifile for ifile in glob('{}/*.root'.format("PreNN_mutau_2017"))]
#processes = [Process(target=fillFile, args=(ifile, 'mt')) for ifile in file_names]
processes = [fillFile(ifile, 'mt') for ifile in file_names]

#
#
#class Predictor:
#  def __init__(self, data_name, model_name, keep):
#    self.bad = False
#    self.keep = keep
#    self.data_copy = pd.DataFrame()
#    # open the input data
#    try:
##      self.data = pd.HDFStore(data_name)['df']
#
#    except:
#      self.bad = True
#
#    # open the trained model
#    try:
##      self.model = load_model('models/{}.hdf5'.format(model_name))
#      self.model=   load_model('models/outputModel_wis.hdf5')
#    except:
#      self.bad = True
#
#  def make_prediction(self, fname, channel):
#    print fname, channel
#    self.data_copy = self.data_copy.iloc[0:0]
#    if not self.bad:
#      self.data_copy = self.data[
##              (self.data['sample_names'] == fname) & (self.data['lepton'] == channel)
#              (self.data['sample_names'] == fname)
#          ].copy()
#      print 'to_classify'
#      to_classify = self.data_copy[self.keep]
##      print to_classify
#      self.model.summary()
#      print "to_classify.values", to_classify.values
#      guesses = self.model.predict(to_classify.values, verbose=True)
#      print 'is now predicted'
#      self.data_copy['guess_sig'] = guesses[:,0]
##      self.data_copy['guess_bkg1'] = guesses[:,1]
##      self.data_copy['guess_bkg2'] = guesses[:,2]
#      self.data_copy.set_index('idx', inplace=True)
##      print "\n\n &&&&&&& ", self.data_copy
#
#  def getGuess(self, index):
#    try:
#      guess = self.data_copy.loc[index, 'guess_sig']
##      guess1 = self.data_copy.loc[index, 'guess_bkg1']
##      guess2 = self.data_copy.loc[index, 'guess_bkg2']
##      print index, "  guess= ", guess
#    except:
#      guess= -999
#
#    return guess
#
#def run_process(proc):
#    print proc
#    return call(proc, shell=True)
#
#
#def fillFile(ifile, channel, args, vbf_pred):
#  fname = ifile.split('/')[-1].split('.root')[0]
#  print 'Starting process for file: {}'.format(fname)
#
#  vbf_pred.make_prediction(fname, channel)
##  boost_pred.make_prediction(fname, channel)
#  print 'not predict yet'
#
#  ## now let's try and get this into the root file
#  root_file = TFile(ifile, 'READ')
#  itree = root_file.Get(args.treename)
#
##  #===== AM  [not needed anymore]
##  TName=args.treename
###  if "Up" in ifile.split("_")[-2] or "Down" in ifile.split("_")[-2]:
##  if "Up" in ifile or "Down" in ifile:
##    TName=TName+"_"+ifile.split("_")[-3]+"_"+ifile.split("_")[-2]
##
##  itree = root_file.Get(TName)
##  #===== AM
#
#  oname = ifile.split('/')[-1].split('.root')[0]
#  fout = TFile('{}/{}.root'.format(args.output_dir, oname), 'recreate')  ## make new file for output
#  fout.cd()
#  nevents = root_file.Get('nevents').Clone()
#  nevents.Write()
#  ntree = itree.CloneTree(-1, 'fast')
#
##  branch_var = array('f', [0.])
##  branch_var1 = array('f', [0.])
##  branch_var2 = array('f', [0.])
#  branch_var_vbf = array('f', [0.])
##  branch_var_boost = array('f', [0.])
##  disc_branch = ntree.Branch('NN_disc', branch_var, 'NN_disc/F')
##  disc_branch1 = ntree.Branch('NN_disc_TT', branch_var1, 'NN_disc_TT/F')
##  disc_branch2 = ntree.Branch('NN_disc_ZTT', branch_var2, 'NN_disc_ZTT/F')
#  disc_branch_vbf = ntree.Branch('NN_disc_vbf', branch_var_vbf, 'NN_disc_vbf/F')
##  disc_branch_boost = ntree.Branch('NN_disc_boost', branch_var_boost, 'NN_disc_boost/F')
#  nevts = ntree.GetEntries()
#
#  evt_index = 0
#  for _ in itree:
#    if evt_index % 10000 == 0 and evt_index > 0:
#      print 'Process: {} has completed: {} events out of {}'.format(fname, evt_index, nevts)
##    branch_var[0],branch_var1[0],branch_var2[0] = vbf_pred.getGuess(evt_index)
#    branch_var= vbf_pred.getGuess(evt_index)
##    branch_var_vbf[0] = vbf_pred.getGuess(evt_index)
##    branch_var_boost[0] = boost_pred.getGuess(evt_index)
#
#    evt_index += 1
#    fout.cd()
##    disc_branch.Fill()
##    disc_branch1.Fill()
##    disc_branch2.Fill()
#    disc_branch_vbf.Fill()
##    disc_branch_boost.Fill()
#
#
#  root_file.Close()
#  fout.cd()
#  ntree.Write()
#  fout.Close()
#  print '{} Completed.'.format(fname)
#
#def main(args):
#    if args.treename == 'mutau_tree':
#        channel = 'mt'
#    elif args.treename == 'etau_tree':
#        channel = 'et'
#    elif args.treename == 'emu_tree':
#        channel = 'em'
#    elif args.treename == 'emu_tree_':
#        channel = 'em'
#    else:
#        raise Exception('Hey. Bad channel. No. Try again.')
#
#    if not path.isdir(args.output_dir):
#        mkdir(args.output_dir)
#
#    file_names = [ifile for ifile in glob('{}/*.root'.format(args.input_dir))]
#
#    keep_vbf = [
##                'mjj', 'higgs_pT','m_sv','mt',
##2016                'njets','mt',  'mu_iso','D_zeta','mjj', 'higgs_pT','vis_mass'
##               'njets', 'mt',  'mu_iso','D_zeta',
##                'mjj',  'higgs_pT','m_sv',
##                'Q2V1', 'Q2V2', 'Phi', 'Phi1', 'costheta1', 'costheta2', 'costhetastar'
#                'muPt','taupt','lepIso','tmass', 'ht','Met','LeadJetPt', 'dR_mu_tau'
#                ]
#
#    vbf_pred = Predictor(args.input_vbf, args.model_vbf, keep_vbf)
#
##    keep_boost = [
##             'muPt','taupt','lepIso','tmass', 'ht','Met','LeadJetPt', 'dR_mu_tau'
##    ]
##    boost_pred = Predictor(args.input_boost, args.model_boost, keep_boost)
#
##    processes = [Process(target=fillFile, args=(ifile, channel, args, vbf_pred)) for ifile in file_names]
#    processes = [Process(target=fillFile, args=("PreNN_mutau_2017/ZTT.root", 'mt', args, vbf_pred)) for ifile in file_names]
#
#
##    n_processes = min(8, multiprocessing.cpu_count() / 2)
##    print multiprocessing.cpu_count(), "  n_process= ",n_processes
##    pool = multiprocessing.Pool(processes=n_processes)
##    print processes
##    r = pool.map_async(run_process, processes)
##    r.wait()
#
#
#    for process in processes:
#      process.start()
#    for process in processes:
#      process.join()
#
#    print 'Finished processing.'
#
#
#if __name__ == "__main__":
#    from argparse import ArgumentParser
#    parser = ArgumentParser()
#    parser.add_argument('--treename', '-t', action='store', dest='treename', default='etau_tree', help='name of input tree')
#    parser.add_argument('--model-vbf', action='store', dest='model_vbf', default=None, help='name of model to use')
##    parser.add_argument('--model-boost', action='store', dest='model_boost', default=None, help='name of model to use')
#    parser.add_argument('--input-vbf', action='store', dest='input_vbf', default=None, help='name of input dataset')
##    parser.add_argument('--input-boost', action='store', dest='input_boost', default=None, help='name of input dataset')
#    parser.add_argument('--dir', '-d', action='store', dest='input_dir', default='input_files/etau_stable_Oct24', help='name of ROOT input directory')
#    parser.add_argument('--output-dir', '-o', action='store', dest='output_dir', default='output_files', help='name of directory for output')
#
#
#    main(parser.parse_args())
