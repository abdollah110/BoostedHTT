import sys
import ROOT
import copy
from optparse import OptionParser

InputFile = sys.argv[1]

parser = OptionParser()
parser.add_option('--ztt', '-z', action='store_true',
                  default=False, dest='is_zttMC',
                  help='run on embedded or MC ZTT'
                  )
(options, args) = parser.parse_args()



year=0
if '2016' in InputFile:
    year = 2016
elif '2017' in InputFile:
    year = 2017
elif '2018' in InputFile:
    year = 2018
else:
    print 'which year ???'

channel=''
DirName=''
executable=''


if 'em2' in InputFile:
    channel = 'em'
    DirName = 'em_0jet'
    executable = 'process_trees_em'
elif 'me2' in InputFile:
    channel = 'me'
    DirName = 'em_0jet'
    executable = 'process_trees_em'
elif 'mt2' in InputFile:
    channel = 'mt'
    DirName = 'mt_0jet'
    executable = 'process_trees_lt_fr'
elif 'et2' in InputFile:
    channel = 'et'
    DirName = 'et_0jet'
    executable = 'process_trees_lt_fr'
elif 'tt2' in InputFile:
    channel = 'tt'
    DirName = 'tt_0jet'
    executable = 'process_trees_tt'
else:
    print 'which channel ???'





file = ROOT.TFile(InputFile,'r')
file1D = ROOT.TFile('boosted_'+str(year)+channel+'1D_NN_8bin.root', 'recreate')
mydir=file1D.mkdir(DirName)

processes = [
        'data_obs','ZTT', 'W',  'TT', 'VV',
        'QCD',
          'ggH125', 'XH125', 'JJH125'
#         'EWKZ',
    ] # input histos




for i_histo in processes: # loop over input histos (processes)
#    if not file.Get(DirName).Get(i_histo):
    histo2D=file.Get(DirName).Get(i_histo+'_2D__')
    print histo2D.GetName(), histo2D.Integral(), histo2D.GetXaxis().GetNbins()

    nx=histo2D.GetXaxis().GetNbins()
    ny=histo2D.GetYaxis().GetNbins()
    
    Newhisto=ROOT.TH1F('histo',histo2D.GetName(),nx*(ny+1)/2,0,nx*(ny+1)/2)
    Newhisto.SetName((histo2D.GetName()).replace('_2D__',''))

    k=1
    for i in range(nx):
        for j in range(ny):
        
            if i+j >nx-1 : continue
            print i, j , histo2D.GetBinContent(i+1,j+1)
            Newhisto.SetBinContent(k,histo2D.GetBinContent(i+1,j+1))
            Newhisto.SetBinError(k,histo2D.GetBinError(i+1,j+1))
            k = k+1
            
    mydir.cd()
    Newhisto.Write()

file1D.Close()

            
            
