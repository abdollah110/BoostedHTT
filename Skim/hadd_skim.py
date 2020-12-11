#python hadd_skim.py -g /eos/uscms/store/user/tmitchel/BoostedH/An2017/MC/*/*  -s /eos/uscms/store/user/abdollah/SkimBoost/mm/v4 -n v1

import glob
import os
import sys
import argparse

parser = argparse.ArgumentParser(description='create sumission files from the existing templates')

parser.add_argument('-g','--ggntuple',action='store', default='/eos/uscms/store/user/tmitchel/BoostedH/An2017/MC/*/*',dest='ggntuple',  help='the name of the INpitSamples')
parser.add_argument('-s','--skim',action='store',
    default='/eos/uscms/store/user/abdollah/SkimBoost/mm/v4',dest='skim', help='Location of the output file')
parser.add_argument('-n','--name',action='store',
    default='v1',dest='name', help='suffix')

args = parser.parse_args()



#ggNtupleFiles='/eos/uscms/store/user/tmitchel/BoostedH/An2017/MC/*/*'
#skimFiles='/eos/uscms/store/user/abdollah/SkimBoost/mm/v4'

ggNtupleFiles=args.ggntuple
skimFiles=args.skim

HaddLoc='root://cmseos.fnal.gov:/'+skimFiles.replace('/eos/uscms','')+'_Hadd'

if not os.path.exists(HaddLoc):
    os.makedirs(HaddLoc)

outFile=open('_run_to_hadd_{}.sh'.format(args.name),'w')
for gl in glob.glob(ggNtupleFiles):
    print  'gl is {}'.format(gl)
    sample=gl.rpartition('/')[-1].replace('crab_','')
    outFile.write('hadd %s/%s.root    %s/*%s*.root \n'%(HaddLoc,sample,skimFiles,sample))
#    os.system('hadd %s/%s.root    %s/%s*.root'%(HaddLoc,sample,skimFiles,sample))

outFile.close()
    



