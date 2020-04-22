# abdollah.mohammadi@cern.ch
###### This is the script for creating scripts for submitting jobs on LPC condor for running FASTMTT of SVFit
# python makeSubmissionPackage_sv.py -x FastMTT -i InputSamples_sv.txt -n muTau_v1 -o /store/user/abdollah/SVFit/mt/v1
######
import os
import sys
import argparse
import subprocess as sp

parser = argparse.ArgumentParser(description='create sumission files from the existing templates')
parser.add_argument('-x','--executable',action='store',default='FastMTT',dest='exe', help='the name of the executable')
parser.add_argument('-i','--input',action='store',default='InputSamples_sv.txt',dest='InputSample', help='the name of the INpitSamples')
parser.add_argument('-n','--name',action='store',default='_tt_v1',dest='Name', help='suffix to the script names')
parser.add_argument('-o','--output',action='store',default='/store/user/abdollah/NewSkimBoost/mt/v2',dest='OutPut', help='Location of the output file')
args = parser.parse_args()


## template for Submit_run
Out_run=open('Submit_run_%s.sh'%args.Name,'w')
run_file=open('Template_Submit_sv_run.sh','r')
for line in run_file.readlines():

    line=line.replace('abdollah',os.environ['LOGNAME'])
    line=line.replace('FastMTT',args.exe)
    line=line.replace('TarFile','Files_%s'%args.Name)
    line=line.replace('OUTPUTFILE_LOCATION',args.OutPut)
    line=line.replace('InputSamples_sv.txt',args.InputSample)


    Out_run.write(line)
Out_run.close()


## Count number of files
input_File=open(args.InputSample,'r')
count=0
for line in input_File.readlines():
    if len(line.strip()) == 0 : continue
    count+=1
print 'number of file is %d'%count


## template for Submit_batch
Out_batch=open('Submit_batch_%s.jdl'%args.Name,'w')
run_file=open('Template_Submit_sv_batch.jdl','r')
for line in run_file.readlines():
    line=line.replace('abdollah',os.environ['LOGNAME'])
    line=line.replace('Submit_run.sh','Submit_run_%s.sh'%args.Name)
    line=line.replace('THE_RUN_PATH', os.getcwd())
    if 'Queue' in line:
        line='Queue '+ str(count)
    Out_batch.write(line)
Out_batch.close()


## copy necessary files in the /eos are
logName=os.environ['LOGNAME']
#exeLocation = sp.getoutput('which %s'%args.exe)
exeLocation = os.popen('which %s'%args.exe).read().replace('\n','')
#exeLocation=os.system('which %s'%args.exe)
print 'exeLocation= ', exeLocation
os.system('rm -r Files_%s'%args.Name)
os.system('mkdir Files_%s'%args.Name)
os.system('cp Submit_run_%s.sh Files_%s/.'%(args.Name,args.Name))
os.system('cp Submit_batch_%s.jdl Files_%s/.'%(args.Name,args.Name))
os.system('cp %s Files_%s/.'%(exeLocation,args.Name))
os.system('cp %s Files_%s/.'%(args.InputSample,args.Name))
# needed libraries for FastMTT
os.system('cp %s Files_%s/.'%("$CMSSW_BASE/lib/*/libTauAnalysisSVfitTF.so" ,args.Name))
os.system('cp %s Files_%s/.'%("$CMSSW_BASE/lib/*/libHTT-utilitiesRecoilCorrections.so" ,args.Name))
os.system('cp %s Files_%s/.'%("$CMSSW_BASE/lib/*/libTauAnalysisClassicSVfit.so" ,args.Name))
os.system('tar -zcp -f Files_%s.tar.gz  Files_%s'%(args.Name,args.Name))


os.system('xrdcp -f Files_%s.tar.gz root://cmseos.fnal.gov://store/user/${LOGNAME}/.'%args.Name)
    
    
## Print the condos submit command
print 'total number of jobs to be submitted will be %d'%(count)
print 'Just run the following command:'
print '................................'
print 'condor_submit Submit_batch_%s.jdl'%args.Name
print '................................'




