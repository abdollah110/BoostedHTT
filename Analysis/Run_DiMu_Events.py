#! /usr/bin/python

# To change this template, choose Tools | Templates
# and open the template in the editor.
#http://root.cern.ch/viewvc/trunk/tutorials/pyroot/hsimple.py?revision=20881&view=markup
__author__ = "abdollahmohammadi"
__date__ = "$Feb 23, 2013 10:39:33 PM$"

import math
import ROOT
import sys
import os
from ROOT import *
from ctypes import *
import ROOT as r
import array
gROOT.Reset()

ROOT.gROOT.SetBatch(True)
InputFilesLocation=sys.argv[1]

year=0
if '2016' in InputFilesLocation: year =2016
elif '2017' in InputFilesLocation: year =2017
elif '2018' in InputFilesLocation: year =2018
else: print 'Which year are you looking for\n'
print 'processing {}'.format(year)

verbos_ = True
#RB_=60
RB_=1

process=[
    ['VV','VV',-1],
    ['TT','TT',-1],
    ['ZTT','DYJets125',-1],
    ['W','W',-1],
    ['Data','data_obs',+1],
]

#####################################################
##   Start Making the Histograms
####################################################
def MakeTheHistogram(channel,NormMC,region):
    
    OutFile = TFile(InputFilesLocation+'/'+"_"+channel + NormMC+"-"+str(year)+".root" , 'RECREATE')

    if region=='':CatName='pass'
    tDirectory= OutFile.mkdir(CatName)
    print "catName=",CatName
    tDirectory.cd()

    for pro in process:
        print "--------------------------------------------------->     Processing %s"%pro[0]
        tDirectory.cd()
    
        myfile = TFile(InputFilesLocation +'/'+ pro[0] + '.root')
        NormHisto =  myfile.Get(channel+NormMC )
                
        if NormHisto:
            if not NormHisto:
                raise Exception('Not valid %s'%pro[1])
            else:
                RebinedHist= NormHisto.Rebin(RB_)
                tDirectory.WriteObject(RebinedHist,pro[1])
                    
    OutFile.Close()





if __name__ == "__main__":
    
    PlotName=["ZMass","dR","ht","2DZMassPt","ZPt","ZPt_Below","ZPt_OnMass","ZPt_Above"]

    region= [""]

    Isolation=[""]
    Charge= ["_OS"]

    for Norm in PlotName:
    
        for q in Charge:
            for iso in Isolation:
                for reg in region:
            
                    channel=''
                                        
                    NormMC=Norm+reg+iso+q
                    MakeTheHistogram(channel,NormMC,reg)
