import os
import sys

for i in sys.argv:
    print i
    os.system('scp %s lxplus.cern.ch:/afs/cern.ch/work/a/abdollah/scratch1/LimiBoosted/CMSSW_10_2_13/src/CombineHarvester/CombineTools/bin/. '%i)
                                        
