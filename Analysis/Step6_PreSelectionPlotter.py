#! /usr/bin/python

# To change this template, choose Tools | Templates
# and open the template in the editor.
#http://root.cern.ch/viewvc/trunk/tutorials/pyroot/hsimple.py?revision=20881&view=markup
__author__ = "abdollahmohammadi"
__date__ = "$Feb 23, 2013 10:39:33 PM$"

import math
import ROOT
from ROOT import *
#from ROOT import TCanvas
#from ROOT import TFile
#from ROOT import TH1F
#from ROOT import TH2F
#from ROOT import TNtuple
#from ROOT import TProfile
#from ROOT import gBenchmark
#from ROOT import gROOT
#from ROOT import gRandom
#from ROOT import gSystem
from ctypes import *
import ROOT as r
import array


gROOT.Reset()
import os


ROOT.gROOT.SetBatch(True)

InputFilesLocation = 'NewOutFiles_BoostedHTT2017_/'
#InputFilesLocation = 'NewOutFiles_BoostedHTT2017_old/'

verbos_ = True
RB_=1

#process=[
#['VV','VV',-1],
#['SingleTop','SingleTop',-1],
#['TTJets','TT',-1],
#['DYJetsToLL','ZTT',-1],
#['WJetsToLNu','W',-1],
#['Data','data_obs',+1],
#]

process=[
['VV','Diboson',-1],
['SingleTop','SingleTop',-1],
['TTJets','ttbar',-1],
['DYJetsToLL','DYJets125',-1],
['WJetsToLNu','WJets',-1],
['Data','data_obs',+1],
]



def getNormOfQCD(channel,NormMC):
    sum=0
    for pro in process:
        myfile = TFile(InputFilesLocation +'/'+ pro[0] + '.root')
        NormHisto =  myfile.Get(channel+NormMC)
        if not NormHisto: continue
#        print "accesing the ", pro[0], channel+NormMC
        sum += NormHisto.Integral()*pro[2]
    return sum


#####################################################
##   Start Making the Datacard Histograms
####################################################
def MakeTheHistogram(channel,NormMC,qcdOS,qcdSS,templateqcd,templateqcdShape,region):
    
    OutFile = TFile(InputFilesLocation+'/'+"TotalRootForLimit_PreSelection_"+channel + NormMC+".root" , 'RECREATE')

    if region=='_Pass':CatName='pass'
    if region=='_Fail':CatName='fail'
#    CatName=region
#    CatName=region.replace('_Pass','pass')
#    CatName=region.replace('_Fail','fail')
    tDirectory= OutFile.mkdir(CatName)
    print "catName=",CatName
    tDirectory.cd()

    allFiles=[]
    for pro in process:
        ################################################
        #  Filling SingleTop
        ################################################
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
                
                
    ################################################
    #  Estimate OS/SS ratio
    ################################################

    getNormOfQCD_OS=getNormOfQCD(channel,qcdOS)
    print "getNormOfQCD_OS= ", getNormOfQCD_OS
    getNormOfQCD_SS=getNormOfQCD(channel,qcdSS)
    print "getNormOfQCD_SS= ", getNormOfQCD_SS
    
    print "os/ss is= ", getNormOfQCD_OS/getNormOfQCD_SS
    
#    datass_file=TFile(InputFilesLocation +'/Data.root')
    
    qcd_Norm=tDirectory.Get("ttbar")
    qcd_Norm.Scale(0)
    qcd_Shape=qcd_Norm.Clone()
    
    
    
    for pro in process:

        myfile = TFile(InputFilesLocation +'/'+ pro[0] + '.root')
        
        NormHisto =  myfile.Get(channel+templateqcd )
        ShapeHisto =  myfile.Get(channel+templateqcdShape )
        if not NormHisto or not ShapeHisto: continue
        qcd_Norm.Add(NormHisto,pro[2])
        qcd_Shape.Add(ShapeHisto,pro[2])
        
    qcd_Norm.Scale(getNormOfQCD_OS/getNormOfQCD_SS)
    qcd_Shape.Scale(qcd_Norm.Integral()/qcd_Shape.Integral())
    
    tDirectory.cd()
    tDirectory.WriteObject(qcd_Shape,"QCD")
    
    
    OutFile.Close()





if __name__ == "__main__":
    
    PlotName=["ZMass","dR","tmass","ht"]


#    Isolation=["_Iso", "_AntiIso"]
#    Charge= ["_OS","_SS"]
    region= ["_Pass", "_Fail"]

    Isolation=["_Iso"]
    Charge= ["_OS"]
#    region= ["_Pass"]


    for Norm in PlotName:
    
        for q in Charge:
            for iso in Isolation:
                for reg in region:
            
                    channel=''
                                        
                    NormMC=Norm+reg+iso+q
                    qcdOS=Norm+"_Fail"+"_AntiIso"+"_OS"
                    qcdSS=Norm+"_Fail"+"_AntiIso"+"_SS"
                    templateqcd=Norm+reg+iso+"_SS"
                    templateqcdShape=Norm+reg+iso+"_SS"
                
                    MakeTheHistogram(channel,NormMC,qcdOS,qcdSS,templateqcd,templateqcdShape,reg)
