import glob
import os
files='/eos/uscms/store/user/abdollah/SkimBoost/mm/v4'
HaddLoc=files+'_Hadd'

for gl in glob.glob('/eos/uscms/store/user/tmitchel/BoostedH/An2017/MC/*/*'):
    name=gl.rpartition('/')[-1].replace('crab_','')
#    os.system('hadd $s/%s.root    $s/%s*.root'%(HaddLoc,name,files,name))
    print 'hadd %s/%s.root    %s/%s*.root'%(HaddLoc,name,files,name)
    
    

