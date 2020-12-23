import os
import sys

for i in sys.argv:
    print i
    os.system('scp %s cmslpc126.fnal.gov:/uscms_data/d3/abdollah/Analysis/Limit/CMSSW_10_2_13/src/CombineHarvester/CombineTools/bin/.'%i)
                                         
