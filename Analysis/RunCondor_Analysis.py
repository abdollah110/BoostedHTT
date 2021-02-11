# Just update thos code and run
# to remove sys just remove --sys
#python RunCondor_Analysis.py
from glob import glob
import os
import sys
dir= sys.argv[1]
nfsDir= sys.argv[2]
useSys= sys.argv[3]
#Sys= sys.argv[2]
#dir='/hdfs/store/user/abdollah/Hadd_2018_preapproval3'  ## no '/ at the end'

year=0
if '2016' in dir: year = '2016'
if '2017' in dir: year = '2017'
if '2018' in dir: year = '2018'

if 'sys' in useSys:
    SysType='--sys'
else:
    SysType=''

for path in glob('{}/*'.format(dir)):
    print 'path is ', path
    sample=path.split('/')[-1]
    print 'sample is {} in {} and path is {}'.format(sample,dir,path)
    os.system('python Condor_Analysis.py -y {}  -p {} --output-dir Condor_em_{}_{} -e analyze_em --nfs {}  {} --condor'.format(year,path,year,sample,nfsDir, SysType))
