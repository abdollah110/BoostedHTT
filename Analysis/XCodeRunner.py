import os

import argparse
import logging
import os
import shutil
import subprocess
import sys
import re
import subprocess

parser = argparse.ArgumentParser(description='Process some integers.')

#parser.add_argument('SingleMuon', action='store_true',default='SingleMuon',
#                    help="Which dataset")
parser.add_argument('-i','--in',dest='code', default='BoostedHTT2017',
                    help="Provide a code name")
parser.add_argument('-x','--x',dest='extra', default='',
                    help="Provide extra name to be added in the Directory")
parser.add_argument('-s','--s',dest='sample', default='MT',
                    help="Provide which dataset your are running")
parser.add_argument('-f','--f',dest='RunFullSample', default=False,
                    help="Run Full Sample")

                                                        

args = parser.parse_args()
print args.code

preName='NewOutFiles_'
dirName=('%s%s_%s'%(preName,args.code,args.extra)).replace('CodexAnalyzer_','')

SampleLoc=''

print 'This is what we are runinng on .....',args.sample
if args.sample=='MT':
#    SampleLoc='/uscms_data/d3/abdollah/Analysis/BoostedH/CMSSW_9_4_13/src/BoostedHTT/InputSample/'
    SampleLoc='/uscms_data/d3/abdollah/Analysis/BoostedH/BBNTUPLE/ggNtuple_skim_2017_mt/'
if args.sample=='MM':
    SampleLoc='/eos/uscms/store/user/abdollah/SkimBoost/mm/v4_Hadd/'
if args.sample=='ET':
    SampleLoc='/Users/abdollah1/GIT_abdollah110/DM2018/ROOT94X/SampleLQ1/'

if not os.path.exists(dirName):
    os.makedirs(dirName)

process=[
            ['DYJetsToLL.root','DYJetsToLL_M-50_HT*.root'],
            ['WJetsToLNu.root','WJetsToLNu_HT-*.root'],
            ['TTJets.root','TT*.root'],
            ['VV.root','ZZ*.root', 'WZ*.root', 'WW*.root'],
            ['SingleTop.root','ST_*.root'],
            ['Data.root','Data.root'],
]

outF=open('out%s.txt'%dirName,'w')

outF.write("\n ./Make.sh %s.cc"%args.code)
outF.write("\n cp %s.* %s/."%(args.code,dirName))
outF.write("\n cp out%s.txt %s/."%(dirName,dirName))


for pro in range(0,len(process)):

    if len(process[pro])==2: outF.write("\n./%s.exe   %s/%s      %s%s "%(args.code,dirName,process[pro][0],SampleLoc, process[pro][1] ))
    if len(process[pro])==3: outF.write("\n./%s.exe   %s/%s    %s%s %s%s"%(args.code,dirName,process[pro][0],SampleLoc, process[pro][1], SampleLoc,process[pro][2] ))
    if len(process[pro])==4: outF.write("\n./%s.exe   %s/%s  %s%s %s%s %s%s"%(args.code,dirName,process[pro][0],SampleLoc, process[pro][1], SampleLoc,process[pro][2], SampleLoc,process[pro][3] ))


outF.close()

print "Run the following line"
print "source out%s.txt"%dirName
                
