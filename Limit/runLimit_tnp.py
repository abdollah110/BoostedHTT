import os
import sys
#from colorama import Fore, Back, Style

Years=['2016','2017','2018']
WPs=['V','L','M','T']
Bins=['bin0','bin1','bin2','bin3']

inputDir=sys.argv[0]
for year in Years:
    for wp in WPs:
        for bin in Bins:
            print 'now processing --year={} --bin={} --WP={} '.format(year,bin,wp)
            os.system('BoostedTau_limit_single_plus_CR_new --year={} --bin={} --WP={} --DIR={}'.format(year,bin,wp,inputDir))
os.system('sh add_auto_MC_Stat_TnP.sh {}'.format(inputDir))

for year in Years:
    for wp in WPs:
        for bin in Bins:
            os.chdir('{}/{}_{}_{}/125/'.format(inputDir,year,wp,bin))
            os.system('combineCards.py pass=DYJets_mt_1_13TeV.txt CR=DYJets_mm_1_13TeV.txt > Comb.txt')
            os.system('text2workspace.py Comb.txt -m 125 -o ws.root -P HiggsAnalysis.CombinedLimit.TagAndProbeModel:tagAndProbe')
            os.system('combine -M FitDiagnostics ws.root -m 125 --robustFit=1 --rMin -2 --rMax 2')
            os.system('PostFitShapesFromWorkspace -w ws.root -f fitDiagnostics.root:fit_s --postfit --print -d Comb.txt -o postfit_shapes.root -m 125')
            os.chdir('/uscms_data/d3/abdollah/Analysis/Limit/CMSSW_10_2_13/src/CombineHarvester/CombineTools/bin')

    

