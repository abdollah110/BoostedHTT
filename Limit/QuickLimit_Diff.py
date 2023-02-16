# python QuickLimit.pt NewV3 NN
import os
import sys
import ROOT
from ROOT import *


output=sys.argv[1]
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
#Channel=['em']
#Year = ['2016']

for ch in Channel:
    for year in Year:
        print '\n\n\n\n  {}   {}   \n\n\n\n\n'.format(ch,year)
        os.chdir('{}/{}/125/'.format(output,year))
#        os.system('cd {}/{}/125/'.format(output,year))
        os.system('combineCards.py  H_{}_*_13TeV.txt > H_{}_13TeV.txt '.format(ch,ch))
        os.system("text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO 'map=.*/.*H.*PTH_0_350.*:r_H_PTH_0_350[1,-25,25]' --PO 'map=.*/.*H.*PTH_350_450.*:r_H_PTH_350_450[1,-25,25]' --PO 'map=.*/.*H.*PTH_450_600.*:r_H_PTH_450_600[1,-25,25]' --PO 'map=.*/.*H.*PTH_G.600.*:r_H_PTH_GT600[1,-25,25]' H_{}_13TeV.txt -m 125".format(ch))
#        os.system('combine -M Significance -d {}/{}/125/H_{}_1_13TeV.txt -t -1 -m 125 --expectSignal=1 -n ExpSig'.format(output,year,ch))
#        os.system('mv higgsCombineExpSig.Significance.mH125.root {}/higgsCombineExpSig.Significance.mH125_{}_{}_{}.root'.format(output,output,year,ch))
#        os.system('combine -M Significance -d {}/{}/125/H_{}_1_13TeV.txt -m 125 -n ObsSig'.format(output,year,ch))
#        os.system('mv higgsCombineObsSig.Significance.mH125.root {}/higgsCombineObsSig.Significance.mH125_{}_{}_{}.root'.format(output,output,year,ch))
        os.system('combine -M FitDiagnostics H_{}_13TeV.root -m 125 --setParameterRanges r_H_PTH_0_350=-15,15:r_H_PTH_350_450=-15,15:r_H_PTH_450_600=-15,15:r_H_PTH_GT600=-15,15'.format(ch))
#        os.system('mv higgsCombineTest.FitDiagnostics.mH125.root {}/higgsCombineTest.FitDiagnostics.mH125.{}_{}_{}.root'.format(output,output,year,ch))
#        os.system('mv fitDiagnosticsTest.root {}/fitDiagnostics.{}_{}_{}.root'.format(output,output,year,ch))
        os.system('PostFitShapesFromWorkspace -w H_{}_13TeV.root -f fitDiagnosticsTest.root:fit_s --postfit  --print -d  H_{}_13TeV.txt -o postfit_shapes_{}_{}.root -m 125 '.format(ch, ch, year,ch))
        os.chdir('/afs/cern.ch/work/a/abdollah/scratch1/LimiBoosted/CMSSW_10_2_13/src/CombineHarvester/CombineTools/bin/')
        
