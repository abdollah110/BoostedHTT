#! /usr/bin/python

# To change this template, choose Tools | Templates
# and open the template in the editor.
#http://root.cern.ch/viewvc/trunk/tutorials/pyroot/hsimple.py?revision=20881&view=markup
__author__ = "abdollahmohammadi"
__date__ = "$Feb 23, 2013 10:39:33 PM$"

import sys
import math
import ROOT
from ROOT import *
from ctypes import *
import ROOT as r
import array
import os

InputFilesLocation=sys.argv[1]

year=0
if '2016' in InputFilesLocation: year =2016
if '2017' in InputFilesLocation: year =2017
if '2018' in InputFilesLocation: year =2018

gROOT.Reset()
ROOT.gROOT.SetBatch(True)
RB_=1
process=[
    ['VV','Diboson',-1],
    ['TT','ttbar',-1],
    ['ZTT','DYJets125',-1],
    ['W','WJets',-1],
    ['Data','data_obs',+1],
]
systs = [""]
 


#####################################################
##   Start Making the Datacard Histograms
####################################################
def MakeTheHistogram(NormMC):
    
    OutFile = TFile(InputFilesLocation+'/'+"Fake_"+NormMC+".root" , 'RECREATE')

    CatName='pass'
    tDirectory= OutFile.mkdir(CatName)
    print "catName=",CatName
    tDirectory.cd()

    allFiles=[]
    for pro in process:
        print "\t\t   ------>     Processing %s"%pro[0]
        tDirectory.cd()
    
        myfile = TFile(InputFilesLocation +'/'+ pro[0] + '.root')
        NormHisto =  myfile.Get(NormMC )
                

        if not NormHisto:
            print "\n\n\n\n\n\n", pro
        else:
            RebinedHist= NormHisto.Rebin(RB_)
            tDirectory.WriteObject(RebinedHist,pro[1])

    for pro in process:
        for sys in systs:
            sysfileName=InputFilesLocation.replace('NN_nominal','')+'/NN_'+sys+'/'+pro[0]+'_'+sys+'.root'
            print '=====>  ',sysfileName
            if not os.path.exists(sysfileName):
                continue
            else:
                print sysfileName
                sysfile = TFile(sysfileName)
                sysNormHisto =  sysfile.Get(NormMC )
                sysRebinedHist= sysNormHisto.Rebin(RB_)
                tDirectory.WriteObject(sysRebinedHist,pro[1]+'_'+sys)

    OutFile.Close()


if __name__ == "__main__":
    
    PlotName=['denum','numVLoose','numLoose','numTight', 'denum_eta','numVLoose_eta','numLoose_eta','numTight_eta', 'denum_dR','numVLoose_dR','numLoose_dR','numTight_dR', 'MT', 'LepPt', 'Met','ZMass','st']
    for Norm in PlotName:
        MakeTheHistogram(Norm)
