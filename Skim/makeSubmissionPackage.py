# abdollah.mohammadi@cern.ch
###### This is the script for creating scripts for submitting jobs on LPC condor for skimming of ggNtuples
# python makeSubmissionPackage.py -x SkimerBoost_mt -i InputSample.txt -n muTau_v1 -o /store/user/abdollah/NewSkimBoost/mt/v1
######
import os
import sys
import argparse

parser = argparse.ArgumentParser(description='create sumission files from the existing templates')
parser.add_argument('-x','--executable',action='store',default='SkimerBoost_mt',dest='exe', help='the name of the executable')
parser.add_argument('-i','--input',action='store',default='InputSample.txt',dest='InputSample', help='the name of the INpitSamples')
parser.add_argument('-n','--name',action='store',default='_tt_v1',dest='Name', help='suffix to the script names')
parser.add_argument('-o','--output',action='store',default='/store/user/abdollah/NewSkimBoost/mt/v2',dest='OutPut', help='Location of the output file')
args = parser.parse_args()


## template for Submit_run
Out_run=open('Submit_run_%s.sh'%args.Name,'w')
run_file=open('Template_Submit_run.sh','r')
for line in run_file.readlines():

    line=line.replace('abdollah',os.environ['LOGNAME'])
    line=line.replace('SkimerBoost_mt',args.exe)
    line=line.replace('TarFile','Files_%s'%args.Name)
    line=line.replace('OUTPUTFILE_LOCATION',args.OutPut)
    line=line.replace('InputSamples.txt',args.InputSample)


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
run_file=open('Template_Submit_batch.jdl','r')
for line in run_file.readlines():
    line=line.replace('abdollah',os.environ['LOGNAME'])
    line=line.replace('Submit_run.sh','Submit_run_%s.sh'%args.Name)
    line=line.replace('THE_RUN_PATH', os.getcwd())
    if 'Queue' in line:
        line='Queue '+ str(count*10)
    Out_batch.write(line)
Out_batch.close()


## copy necessary files in the /eos are
logName=os.environ['LOGNAME']
os.system('rm -r Files_%s'%args.Name)
os.system('mkdir Files_%s'%args.Name)
os.system('mv Submit_run_%s.sh Files_%s/.'%(args.Name,args.Name))
os.system('mv Submit_batch_%s.jdl Files_%s/.'%(args.Name,args.Name))
os.system('cp %s Files_%s/.'%(args.exe,args.Name))
os.system('cp %s Files_%s/.'%(args.InputSample,args.Name))
os.system('cp NNLOPS_reweight.root Files_%s/.'%(args.Name))
os.system('tar -zcp -f Files_%s.tar.gz  Files_%s'%(args.Name,args.Name))

os.system('xrdcp -f Files_%s.tar.gz root://cmseos.fnal.gov://store/user/${LOGNAME}/.'%args.Name)

os.system('mv Files_%s.tar.gz Files_%s/.'%(args.Name,args.Name))
    
## Print the condos submit command
print 'total number of jobs to be submitted will be %d'%(count*10)
print 'Just run the following command:'
print '................................'
#print 'condor_submit Submit_batch_%s.jdl'%args.Name
print 'cd Files_%s/; condor_submit Submit_batch_%s.jdl; cd -'%(args.Name,args.Name)
print '................................'




