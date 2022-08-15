# python QuickLimit.pt NewV3 NN
import os
import sys
import ROOT
from ROOT import *


input=sys.argv[1]
var=sys.argv[2]

#os.system('hadd -f aux/{}_2016_{}.root aux/*2016*_{}.root'.format(input,var,input))
#os.system('hadd -f aux/{}_2017_{}.root aux/*2017*_{}.root'.format(input,var,input))
#os.system('hadd -f aux/{}_2018_{}.root aux/*2018*_{}.root'.format(input,var,input))


#os.system('BoostedTau --prefix="{}" --postfix="{}" --year=2016 --Var={}'.format(input,input,var))
#os.system('BoostedTau --prefix="{}" --postfix="{}" --year=2017 --Var={}'.format(input,input,var))
#os.system('BoostedTau --prefix="{}" --postfix="{}" --year=2018 --Var={}'.format(input,input,var))


os.system('sh add_auto_MC_Stat.sh {}'.format(input))

Channel=['em','et','mt','tt']
extra=['qcd','ztt','signal']
TotChannel=[]
for ch in Channel:
    for ex in extra:
          TotChannel.append(ch+'_'+ex)
#Channel=['tt']
Year = ['2016','2017','2018']
#Year = ['2018']

for count,ch in enumerate(TotChannel):
#for ch in Channel:
    for year in Year:
#        os.system('combineCards.py {}/{}/125/H_{}_*_1_13TeV.txt > {}/{}/125/H_{}_1_13TeV.txt '.format(input,year,ch,input,year,ch))
        os.system('text2workspace.py  {}/{}/125/H_{}_1_13TeV.txt -o {}/{}/125/H_{}.root -m 125 '.format(input,year,ch,input,year,ch))
        os.system('combine -M Significance -d {}/{}/125/H_{}_1_13TeV.txt -t -1 -m 125 --expectSignal=1'.format(input,year,ch))
        os.system('mv higgsCombineTest.Significance.mH125.root {}/higgsCombineTest.Significance.mH125_{}_{}_{}.root'.format(input,input,year,ch))
        os.system('combine -M FitDiagnostics {}/{}/125/H_{}.root -m 125 --rMin -5 --rMax 5'.format(input,year,ch,input,year,ch))
        os.system('PostFitShapesFromWorkspace -w {}/{}/125/H_{}.root -f fitDiagnostics.root:fit_s --postfit  --print -d  {}/{}/125/H_{}_1_13TeV.txt -o {}/postfit_shapes_{}_{}_{}.root -m 125 '.format(input,year,ch, input,year,ch, input,input,year,ch))
        os.system('mv fitDiagnostics.root {}/fitDiagnostics.{}_{}_{}.root'.format(input,input,year,ch))


Out=TFile('Optimization_{}_{}.root'.format(input,var),'recreate')
hist=TH1F('limit','',16,0,16)
i=1
for ch in Channel:
    for year in Year:
        Input=TFile('{}/higgsCombineTest.Significance.mH125_{}_{}_{}.root'.format(input,input,year,ch))
        print ch, year
        Lim=Input.Get('limit')
        for evt_BSM in Lim:
            print Lim.limit
            hist.SetBinContent(i,Lim.limit)
            hist.GetXaxis().SetBinLabel(i,'{}_{}'.format(ch,year))
            i += 1
Out.cd()
hist.Write()
Out.Close()
