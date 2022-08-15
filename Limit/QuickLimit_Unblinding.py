# python QuickLimit.pt NewV3 NN
import os
import sys
import ROOT
from ROOT import *


input=sys.argv[1]
output=sys.argv[2]
var=sys.argv[3]
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
for ch in Channel:
    for year in Year:
#        os.system('combineCards.py  {}/{}/125/H_{}_*_1_13TeV.txt > {}/{}/125/H_{}_1_13TeV.txt '.format(output,year,ch,output,year,ch))
#        os.system('text2workspace.py  {}/{}/125/H_{}_1_13TeV.txt -o {}/{}/125/H_{}.root -m 125 '.format(output,year,ch,output,year,ch))
#        os.system('combine -M Significance -d {}/{}/125/H_{}_1_13TeV.txt -t -1 -m 125 --expectSignal=1 -n ExpSig'.format(output,year,ch))
#        os.system('mv higgsCombineExpSig.Significance.mH125.root {}/higgsCombineExpSig.Significance.mH125_{}_{}_{}.root'.format(output,output,year,ch))
#        os.system('combine -M Significance -d {}/{}/125/H_{}_1_13TeV.txt -m 125 -n ObsSig'.format(output,year,ch))
#        os.system('mv higgsCombineObsSig.Significance.mH125.root {}/higgsCombineObsSig.Significance.mH125_{}_{}_{}.root'.format(output,output,year,ch))
        os.system('combine -M FitDiagnostics {}/{}/125/H_{}.root -m 125 --rMin -5 --rMax 5'.format(output,year,ch,output,year,ch))
        os.system('mv higgsCombineTest.FitDiagnostics.mH125.root {}/higgsCombineTest.FitDiagnostics.mH125.{}_{}_{}.root'.format(output,output,year,ch))
        os.system('mv fitDiagnosticsTest.root {}/fitDiagnostics.{}_{}_{}.root'.format(output,output,year,ch))
#        os.system('PostFitShapesFromWorkspace -w {}/{}/125/H_{}.root -f fitDiagnostics.root:fit_s --postfit  --print -d  {}/{}/125/H_{}_1_13TeV.txt -o {}/postfit_shapes_{}_{}_{}.root -m 125 '.format(output,year,ch, output,year,ch, output,output,year,ch))
        


#Out=TFile('Optimization_{}_{}.root'.format(output,var),'recreate')
#hist=TH1F('limit','',16,0,16)
#i=1
#for ch in Channel:
#    for year in Year:
#        output=TFile('higgsCombineTest.Significance.mH125_{}_{}_{}.root'.format(output,year,ch))
#        print ch, year
#        Lim=output.Get('limit')
#        for evt_BSM in Lim:
#            print Lim.limit
#            hist.SetBinContent(i,Lim.limit)
#            hist.GetXaxis().SetBinLabel(i,'{}_{}'.format(ch,year))
#            i += 1
#Out.cd()
#hist.Write()
#Out.Close()
