import os
import sys

for i in sys.argv:
    print i
    os.system('scp %s cmslpc126.fnal.gov:/uscms_data/d3/abdollah/Analysis/Limit/CMSSW_10_2_13/src/CombineHarvester/CombineTools/bin/.'%i)
                                         
python automate_analysis.py -e BoostedHTT2017_tt.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH/2018/tt/v1_fast_Hadd/ -o boost_tt_2018_v1
python automate_analysis.py -e BoostedHTT2017_tt.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH/2017/tt/v1_fast_Hadd/ -o boost_tt_2017_v1
python automate_analysis.py -e BoostedHTT2017_tt.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH/2016/tt/v1_fast_Hadd/ -o boost_tt_2016_v1
