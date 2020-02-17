import os
import sys

for i in sys.argv:
    print i
    os.system('scp %s cmslpc26.fnal.gov:/uscms_data/d3/abdollah/Analysis/Limit/CMSSW_8_1_0/src/auxiliaries/shapes/'%i)
