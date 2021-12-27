from ROOT import *
import os, sys
from glob import glob
infile=sys.argv[1]

allfile= [ifile for ifile in glob(infile+'/*/*/higg*root') if '201' in ifile ]
for infile in allfile:
    input=TFile(infile,'r')
    tr=input.Get('limit')

    for i in tr:
        if round(i.quantileExpected,2) == 0.5:
            print  infile.split('/')[1], round(i.quantileExpected,2), round(i.limit,2)
