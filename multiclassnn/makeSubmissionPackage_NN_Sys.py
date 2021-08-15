# abdollah.mohammadi@cern.ch
###### This is the script for creating scripts for submitting jobs on LPC condor for running FASTMTT of SVFit
# python makeSubmissionPackage_NN.py -n firsttest4 -i InputSamples_NN.txt
######
import os
import sys
import argparse
import subprocess as sp

parser = argparse.ArgumentParser(description='create sumission files from the existing templates')
parser.add_argument('-n','--name',action='store',default='_tt_v1',dest='Name', help='suffix to the script names')
parser.add_argument('-i','--input',action='store',default='InputSamples_NN.txt',dest='Input', help='Location of the Input file')
args = parser.parse_args()


## template for Submit_run
Out_run=open('Submit_run_%s.sh'%args.Name,'w')
run_file=open('Template_Submit_NN_run_Sys.sh','r')
for line in run_file.readlines():

    line=line.replace('abdollah',os.environ['LOGNAME'])
    line=line.replace('TarFile','Files_%s'%args.Name)
    line=line.replace('OUTPUTFILE_LOCATION','{}_fast'.format(args.Input).replace('/eos/uscms/','').replace('/_','_'))


    Out_run.write(line)
Out_run.close()


## Count number of files
input_File=open(args.Input,'r')
count=0
for line in input_File.readlines():
    if len(line.strip()) == 0 : continue
    count+=1
print 'number of file is %d'%count


## template for Submit_batch
Out_batch=open('Submit_batch_%s.jdl'%args.Name,'w')
run_file=open('Template_Submit_NN_batch.jdl','r')
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
os.system('rm -r Files_%s'%args.Name)
os.system('mkdir Files_%s'%args.Name)
os.system('mv Submit_run_%s.sh Files_%s/.'%(args.Name,args.Name))
os.system('mv Submit_batch_%s.jdl Files_%s/.'%(args.Name,args.Name))
os.system('cp %s Files_%s/InputSamples_NN.txt'%(args.Input,args.Name))
# needed libraries for FastMTT
os.system('cp classify.py train.py  preprocess.py correlation.py visualize.py Files_%s/.'%(args.Name))
os.system('tar -zcp -f Files_%s.tar.gz  Files_%s'%(args.Name,args.Name))


os.system('xrdcp -f Files_%s.tar.gz root://cmseos.fnal.gov://store/user/${LOGNAME}/.'%args.Name)
    
os.system('mv Files_%s.tar.gz Files_%s/.'%(args.Name,args.Name))

root_file=open(args.Input,'r')
CurrentDIR=os.getcwd()
for line in root_file.readlines():
        newline=line.replace('\n','')
        outname=line.split('/')[-2]
        print '\n line {} and outname is {} \n'.format(line,outname)
        os.chdir('{}'.format(newline))
        os.chdir('../../')
        os.system('ls')
        os.system('tar -zcp -f  /eos/uscms/store/user/abdollah/NN_input_Sys/{}.tar.gz  {}'.format(outname,outname))
        os.chdir(CurrentDIR)

## Print the condos submit command
print 'total number of jobs to be submitted will be %d'%(count)
print 'Just run the following command:'
print '................................'
print 'cd Files_%s/; condor_submit Submit_batch_%s.jdl; cd -'%(args.Name,args.Name)
print '................................'




