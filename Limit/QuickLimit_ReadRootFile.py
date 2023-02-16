# python QuickLimit.pt NewV3 NN
import os
import sys
import ROOT
from ROOT import *


input=sys.argv[1]
analType=sys.argv[2]
# noOverlap  or withOverlap
#

Channel=['em','et','mt','tt']
if 'noOverlap' in analType:
    Channel=['et','mt','tt']
Year = ['2016','2017','2018']

#V32_fixTESNew_13bin_Unblinding/higgsCombineObsSig.Significance.mH125_V32_fixTESNew_13bin_Unblinding_2018_mt.root



Type=['ObsSig','ExpSig']
for type in Type:
    Out=TFile('OutReadFile_{}_{}_{}.root'.format(analType,input,type),'recreate')
    histSignificance=TH1F('significance','',13,0,13)
    histRValue=TH1F('signal strength','',13,0,13)
    if 'noOverlap' in analType:
        histSignificance=TH1F('significance','',10,0,10)
        histRValue=TH1F('signal strength','',10,0,10)
    i=1
    for ch in Channel:
        for year in Year:
#            significance
            output=TFile('{}/higgsCombine{}.Significance.mH125_{}_{}_{}.root'.format(input,type,input,year,ch))
            print ch, year
            Lim=output.Get('limit')
            for evt_BSM in Lim:
                print type , ' ---is--- ' , Lim.limit
                histSignificance.SetBinContent(i,Lim.limit)
                histSignificance.GetXaxis().SetBinLabel(i,'{}_{}'.format(ch,year))
#            r-value
            rvalueFile=TFile('{}/fitDiagnostics.{}_{}_{}.root'.format(input,input,year,ch))
            tr=rvalueFile.Get('tree_fit_sb')
            for ev in tr:
                print ' ---muValue--- ' , ev.r, ev.rErr, ev.rLoErr, ev.rHiErr
                histRValue.SetBinContent(i,ev.r)
                histRValue.SetBinError(i,ev.rErr)
                histRValue.GetXaxis().SetBinLabel(i,'{}_{}'.format(ch,year))
                i += 1
                
#     results for combined
#    allSig=TFile('{}/CMB/higgsCombine{}.Significance.mH125_{}_all.root'.format(input,type,input))
    allSig=TFile('{}/higgsCombine{}.Significance.mH125_{}_all.root'.format(input,type,input))
    Lim=allSig.Get('limit')
    print 'all'
    for evt_BSM in Lim:
        print  type , ' ---CMB is--- ' , Lim.limit
        histSignificance.SetBinContent(i,Lim.limit)
        histSignificance.GetXaxis().SetBinLabel(i,'cmb')
        if 'Obs' in type: histSignificance.GetYaxis().SetTitle('Observed Significance')
        if 'Exp' in type: histSignificance.GetYaxis().SetTitle('Expected Significance')

#    allrValue=TFile('{}/CMB/fitDiagnostics.{}_all.root'.format(input,input))
    allrValue=TFile('{}/fitDiagnostics.{}_all.root'.format(input,input))
    print 'all file is ', '{}/fitDiagnostics.{}_all.root'.format(input,input)
    tr=allrValue.Get('tree_fit_sb')
    for ev in tr:
        print ' ---muValue all--- ' , ev.r, ev.rErr, ev.rLoErr, ev.rHiErr
        histRValue.SetBinContent(i,ev.r)
        histRValue.SetBinError(i,ev.rErr)
        histRValue.GetXaxis().SetBinLabel(i,'cmb')
        histRValue.GetYaxis().SetTitle('Signal Strength')
    
    Out.cd()
    histSignificance.Write()
    histRValue.Write()
    Out.Close()
