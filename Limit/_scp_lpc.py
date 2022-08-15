import os
import sys

for i in sys.argv:
    print i
    os.system('scp %s cmslpc-sl7.fnal.gov:/uscms_data/d3/abdollah/Analysis/ggNtuple/CMSSW_10_2_10/src/BoostedHTT/Limit/.'%i)
                                        
