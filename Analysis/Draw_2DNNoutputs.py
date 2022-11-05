import sys
import ROOT
import copy
from ROOT import *
from optparse import OptionParser

InputFile = sys.argv[1]



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
#file1D = ROOT.TFile('boosted_'+str(year)+channel+'1D_NN_10bin.root', 'recreate')
#mydir=file1D.mkdir(DirName)
ROOT.gStyle.SetOptStat(0)
processes = [
        'data_obs','ZTT',
        'QCD', 'ggH125'
#         'EWKZ',
    ] # input histos




for i_histo in processes: # loop over input histos (processes)
#    if not file.Get(DirName).Get(i_histo):
    histo2D=file.Get(DirName).Get(i_histo+'_2D__')
    print histo2D.GetName(), histo2D.Integral(), histo2D.GetXaxis().GetNbins()


    c=TCanvas()
    histo2D.SetTitle('')
#    histo2D.SetMaximum(1.5)
#    histo2D.SetMinimum(0.5)
    histo2D.GetXaxis().SetTitle("NN output (signal v.s. fake&ztt)")
#    histo2D.SetMarkerStyle(21)
#    histo2D.GetXaxis().SetTitleSize(0.18)
#    histo2D.GetXaxis().SetTitleOffset(0.8)
#    histo2D.GetXaxis().SetTitleFont(42)
#    histo2D.GetXaxis().SetLabelFont(42)
#    histo2D.GetXaxis().SetLabelSize(.111)

    
#    histo2D.GetYaxis().SetTitleSize(0.12)
#    histo2D.GetYaxis().SetTitleFont(42)
#    histo2D.GetYaxis().SetTitleOffset(.475)
#    histo2D.GetYaxis().SetLabelSize(.12)
#    histo2D.GetYaxis().SetNdivisions(204)
    histo2D.GetYaxis().SetTitle("NN output (ztt v.s. fake&sig)")
    
    
    
    
    histo2D.Draw("box")

    ll = ROOT.TText(.5, .9, "{}, ({} channel)".format(i_histo , channel))
#    ll.SetNDC(ROOT.kTRUE)
#    ll.SetTextSize(0.06)
#    ll.SetTextFont(42)
    ll.Draw()

    c.SaveAs("Output/2DRootFiles/_2DNN_{}_{}_{}.pdf".format(i_histo,str(year),channel))

#    nx=histo2D.GetXaxis().GetNbins()
#    ny=histo2D.GetYaxis().GetNbins()
#
#    Newhisto=ROOT.TH1F('histo',histo2D.GetName(),nx*(ny+1)/2,0,nx*(ny+1)/2)
#    Newhisto.SetName((histo2D.GetName()).replace('_2D__',''))
#
#    k=1
#    for i in range(nx):
#        for j in range(ny):
#
#            if i+j >9 : continue
#            print i, j , histo2D.GetBinContent(i+1,j+1)
#            Newhisto.SetBinContent(k,histo2D.GetBinContent(i+1,j+1))
#            Newhisto.SetBinError(k,histo2D.GetBinError(i+1,j+1))
#            k = k+1
#
#    mydir.cd()
#    Newhisto.Write()
#
#file1D.Close()

            
            
