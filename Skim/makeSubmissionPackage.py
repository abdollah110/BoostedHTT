import argparse

parser = argparse.ArgumentParser(description='create sumission files from the existing templates')
parser.add_argument('-x','--executable',action='store',default='SkimerBoost_mt',dest='exe', help='the name of the executable')
parser.add_argument('-i','--input',action='store',default='InputSample.txt',dest='InputSample', help='the name of the INpitSamples')
parser.add_argument('-n','--name',action='store',default='_tt_v1',dest='Name', help='suffix to the script names')
parser.add_argument('-o','--output',action='store',default='/store/user/abdollah/NewSkimBoost/mt/v2',dest='OutPut', help='Location of the output file')
args = parser.parse_args()


## template for Submit_run
Out_run=open('Submit_run_%s.sh'%args.Name,'w')
run_file=open('Submit_run.sh','r')
for line in run_file.readlines():

    if 'SkimerBoost_mt' in line:
        line=line.replace('SkimerBoost_mt',args.exe)
    if 'xrdcp -f ' in line:
        line=line.replace('/store/user/abdollah/NewSkimBoost/mt/v2',args.OutPut)
    if 'InputSamples' in line:
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
run_file=open('Submit_batch.jdl','r')
for line in run_file.readlines():
    if 'Executable' in line:
        line=line.replace('Submit_run.sh','Submit_run_%s.sh'%args.Name)
    if 'Queue' in line:
        line='Queue '+ str(count*10)
    Out_batch.write(line)
Out_batch.close()




    
    





