# python QuickLimit.pt NewV3 NN
import os
import sys
import ROOT
from ROOT import *


input=sys.argv[1]
#output=sys.argv[2]
#var=sys.argv[3]
#
#os.system('BoostedTau_3NN --prefix="{}" --postfix="{}" --year=2016 --Var={}'.format(input,output,var))
#os.system('BoostedTau_3NN --prefix="{}" --postfix="{}" --year=2017 --Var={}'.format(input,output,var))
#os.system('BoostedTau_3NN --prefix="{}" --postfix="{}" --year=2018 --Var={}'.format(input,output,var))
#
#
#
#os.system('sh add_auto_MC_Stat.sh {}'.format(output))

Channel=['em','et','mt','tt']
Year = ['2016','2017','2018']
#for ch in Channel:
#    for year in Year:
##        os.system('combineCards.py  {}/{}/125/H_{}_*_1_13TeV.txt > {}/{}/125/H_{}_1_13TeV.txt '.format(output,year,ch,output,year,ch))
##        os.system('text2workspace.py  {}/{}/125/H_{}_1_13TeV.txt -o {}/{}/125/H_{}.root -m 125 '.format(output,year,ch,output,year,ch))
##        os.system('combine -M Significance -d {}/{}/125/H_{}_1_13TeV.txt -t -1 -m 125 --expectSignal=1 -n ExpSig'.format(output,year,ch))
##        os.system('mv higgsCombineExpSig.Significance.mH125.root {}/higgsCombineExpSig.Significance.mH125_{}_{}_{}.root'.format(output,output,year,ch))
##        os.system('combine -M Significance -d {}/{}/125/H_{}_1_13TeV.txt -m 125 -n ObsSig'.format(output,year,ch))
##        os.system('mv higgsCombineObsSig.Significance.mH125.root {}/higgsCombineObsSig.Significance.mH125_{}_{}_{}.root'.format(output,output,year,ch))
#        os.system('combine -M FitDiagnostics {}/{}/125/H_{}.root -m 125 --rMin -5 --rMax 5'.format(output,year,ch,output,year,ch))
#        os.system('mv higgsCombineTest.FitDiagnostics.mH125.root {}/higgsCombineTest.FitDiagnostics.mH125.{}_{}_{}.root'.format(output,output,year,ch))
#        os.system('mv fitDiagnosticsTest.root {}/fitDiagnostics.{}_{}_{}.root'.format(output,output,year,ch))
##        os.system('PostFitShapesFromWorkspace -w {}/{}/125/H_{}.root -f fitDiagnostics.root:fit_s --postfit  --print -d  {}/{}/125/H_{}_1_13TeV.txt -o {}/postfit_shapes_{}_{}_{}.root -m 125 '.format(output,year,ch, output,year,ch, output,output,year,ch))
#

#V32_fixTESNew_13bin_Unblinding/higgsCombineObsSig.Significance.mH125_V32_fixTESNew_13bin_Unblinding_2018_mt.root



Type=['ObsSig','ExpSig']
for type in Type:
    Out=TFile('OutReadFile_{}_{}.root'.format(input,type),'recreate')
    histSignificance=TH1F('significance','',13,0,13)
    histRValue=TH1F('signal strength','',13,0,13)
    i=1
    for ch in Channel:
        for year in Year:
#            significance
            output=TFile('{}/higgsCombine{}.Significance.mH125_{}_{}_{}.root'.format(input,type,input,year,ch))
            print ch, year
            Lim=output.Get('limit')
            for evt_BSM in Lim:
                print Lim.limit
                histSignificance.SetBinContent(i,Lim.limit)
                histSignificance.GetXaxis().SetBinLabel(i,'{}_{}'.format(ch,year))
#            r-value
            rvalueFile=TFile('{}/fitDiagnostics.{}_{}_{}.root'.format(input,input,year,ch))
            tr=rvalueFile.Get('tree_fit_sb')
            for ev in tr:
                print ev.r, ev.rErr, ev.rLoErr, ev.rHiErr
                histRValue.SetBinContent(i,ev.r)
                histRValue.SetBinError(i,ev.rErr)
                histRValue.GetXaxis().SetBinLabel(i,'{}_{}'.format(ch,year))
                i += 1
                
#     results for combined
    allSig=TFile('{}/CMB/higgsCombine{}.Significance.mH125_{}_all.root'.format(input,type,input))
    Lim=allSig.Get('limit')
    for evt_BSM in Lim:
        print Lim.limit
        histSignificance.SetBinContent(i,Lim.limit)
        histSignificance.GetXaxis().SetBinLabel(i,'cmb')
        if 'Obs' in type: histSignificance.GetYaxis().SetTitle('Observed Significance')
        if 'Exp' in type: histSignificance.GetYaxis().SetTitle('Expected Significance')

    allrValue=TFile('{}/CMB/fitDiagnostics.{}_all.root'.format(input,input))
    tr=allrValue.Get('tree_fit_sb')
    for ev in tr:
        print ev.r, ev.rErr, ev.rLoErr, ev.rHiErr
        histRValue.SetBinContent(i,ev.r)
        histRValue.SetBinError(i,ev.rErr)
        histRValue.GetXaxis().SetBinLabel(i,'cmb')
        histRValue.GetYaxis().SetTitle('Signal Strength')
    
    Out.cd()
    histSignificance.Write()
    histRValue.Write()
    Out.Close()
