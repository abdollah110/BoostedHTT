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

#parser.add_argument('integers', metavar='N', type=int, nargs='+',
#                    help='an integer for the accumulator')
#parser.add_argument('--sum', dest='accumulate', action='store_const',
#                    const=sum, default=max,
#                    help='sum the integers (default: find the max)')

parser.add_argument('SingleMuon', action='store_true',default='SingleMuon',
                    help="Which dataset")
parser.add_argument('-i','--in',dest='codex', default='BoostedHTT2017',
                    help="Provide a code name")
parser.add_argument('-x','--x',dest='extra', default='',
                    help="Provide extra name to be added in the Directory")
parser.add_argument('-s','--s',dest='sample', default='SingleMu',
                    help="Provide which dataset your are running")
parser.add_argument('-f','--f',dest='RunFullSample', default=False,
                    help="Run Full Sample")

                                                        

args = parser.parse_args()
print args.codex

preName='NewOutFiles_'
dirName=('%s%s_%s'%(preName,args.codex,args.extra)).replace('CodexAnalyzer_','')

SampleLoc=''

print 'This is what we are runinng on .....',args.sample
if args.sample=='MuTau':
    SampleLoc='/uscms_data/d3/abdollah/Analysis/BoostedH/CMSSW_9_4_13/src/BoostedHTT/InputSample/'
if args.sample=='DiMu':
    SampleLoc='/eos/uscms/store/user/abdollah/SkimBoost/mm/v4_Hadd/'
    

#if args.sample=='SingleEle':
#    SampleLoc='/Users/abdollah1/GIT_abdollah110/DM2018/ROOT94X/SampleLQ1/'

#if args.sample=='Mu50':
#    SampleLoc='/Users/abdollah1/GIT_abdollah110/DM2018/ROOT94X/lqsamples2_jetPt50_MT200/'

#CodexSignal='/Users/abdollah1/GIT_abdollah110/DM2018/ROOT94X/2017/Signal/'
CodexSignal='/Users/abdollah1/GIT_abdollah110/DM2018/ROOT94X/2017/NEWSIG2018/'

if not os.path.exists(dirName):
    os.makedirs(dirName)





InputBKg=[
            ['DYJetsToLL.root','DYJetsToLL*.root'],
            ['WJetsToLNu.root','WJetsToLNu*.root'],
            ['TTJets.root','TT*.root'],
            ['VV.root','ZZ*.root', 'WZ*.root', 'WW*.root'],
            ['SingleTop.root','ST_*.root'],
            ['Data.root','Data.root'],
]


#InputSignal=[
#             ['Codex_1200.root','Codex_1200_DM_500_X_550.root']
#]

#['Codex_15.root' , 'Codex_1200_DM_550_X_595.root'],


outF=open('out%s.txt'%dirName,'w')

outF.write("\n ./Make.sh %s.cc"%args.codex)
outF.write("\n cp %s.* %s/."%(args.codex,dirName))
outF.write("\n cp out%s.txt %s/."%(dirName,dirName))


for sam in range(0,len(InputBKg)):

#    outF.write("\n./%s.exe   %s/%s      %s%s "%(args.codex,dirName,InputBKg[sam][0],SampleLoc, InputBKg[sam][1] ))
    if len(InputBKg[sam])==2: outF.write("\n./%s.exe   %s/%s      %s%s "%(args.codex,dirName,InputBKg[sam][0],SampleLoc, InputBKg[sam][1] ))
    if len(InputBKg[sam])==3: outF.write("\n./%s.exe   %s/%s    %s%s %s%s"%(args.codex,dirName,InputBKg[sam][0],SampleLoc, InputBKg[sam][1], SampleLoc,InputBKg[sam][2] ))
    if len(InputBKg[sam])==4: outF.write("\n./%s.exe   %s/%s  %s%s %s%s %s%s"%(args.codex,dirName,InputBKg[sam][0],SampleLoc, InputBKg[sam][1], SampleLoc,InputBKg[sam][2], SampleLoc,InputBKg[sam][3] ))


#if not args.RunFullSample:
#    for sig in range(0,len(InputSignal)):
#        outF.write("\n./%s.exe   %s/%s      %s%s "%(args.codex,dirName,InputSignal[sig][0],CodexSignal, InputSignal[sig][1] ))
#
#if args.RunFullSample:
#    for sig in range(0,len(FullSignal)):
#          outF.write("\n./%s.exe   %s/%s      %s%s "%(args.codex,dirName,FullSignal[sig][0],CodexSignal, FullSignal[sig][1] ))
#

outF.close()

print "Run the following line"
print "source out%s.txt"%dirName
                
