import glob
import os

ggNtupleFiles='/eos/uscms/store/user/tmitchel/BoostedH/An2017/MC/*/*'
skimFiles='/eos/uscms/store/user/abdollah/SkimBoost/mm/v4'
HaddLoc='root://cmseos.fnal.gov:/'+skimFiles.replace('/eos/uscms','')+'_Hadd'

if not os.path.exists(HaddLoc):
    os.makedirs(HaddLoc)

outFile=open('_run_to_hadd.sh','w')
for gl in glob.glob(ggNtupleFiles):
    sample=gl.rpartition('/')[-1].replace('crab_','')
    outFile.write('hadd %s/%s.root    %s/%s*.root \n'%(HaddLoc,sample,skimFiles,sample))
#    os.system('hadd %s/%s.root    %s/%s*.root'%(HaddLoc,sample,skimFiles,sample))

outFile.close()
    



