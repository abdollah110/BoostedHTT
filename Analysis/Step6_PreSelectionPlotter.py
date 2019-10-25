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


gROOT.Reset()
ROOT.gROOT.SetBatch(True)


verbos_ = True
RB_=1

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
        sum += NormHisto.Integral()*pro[2]
    return sum


#####################################################
##   Start Making the Datacard Histograms
####################################################
def MakeTheHistogram(channel,NormMC,qcdOS,qcdSS,templateqcd,templateqcdShape,region):
    
    OutFile = TFile(InputFilesLocation+'/'+"TotalRootForLimit_PreSelection_"+channel + NormMC+".root" , 'RECREATE')

    if region=='_Pass':CatName='pass'
    if region=='_Fail':CatName='fail'
    tDirectory= OutFile.mkdir(CatName)
    print "catName=",CatName
    tDirectory.cd()

    allFiles=[]
    for pro in process:
        print "\t\t   ------>     Processing %s"%pro[0]
        tDirectory.cd()
    
        myfile = TFile(InputFilesLocation +'/'+ pro[0] + '.root')
        NormHisto =  myfile.Get(channel+NormMC )
                

        if not NormHisto:
            print "\n\n\n\n\n\n", pro
            myfile = TFile(InputFilesLocation +'/DYJetsToLL.root')
            NormHisto =  myfile.Get(channel+NormMC )
            NormHisto.Scale(0.001/NormHisto.Integral())
            RebinedHist= NormHisto.Rebin(RB_)
            tDirectory.WriteObject(RebinedHist,pro[1])
            
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
    
    OS_to_SS= getNormOfQCD_OS/getNormOfQCD_SS
    print "os/ss is= ", OS_to_SS
    
#    datass_file=TFile(InputFilesLocation +'/Data.root')
    
    qcd_Norm=tDirectory.Get("data_obs")
    qcd_Norm.Scale(0)
    qcd_Shape=qcd_Norm.Clone()
    
    
    
    for pro in process:

        myfile = TFile(InputFilesLocation +'/'+ pro[0] + '.root')
        
        NormHisto =  myfile.Get(channel+templateqcd )
        ShapeHisto =  myfile.Get(channel+templateqcdShape )
        if not NormHisto or not ShapeHisto: continue
        qcd_Norm.Add(NormHisto,pro[2])
        qcd_Shape.Add(ShapeHisto,pro[2])
        print pro, " intg= ", NormHisto.Integral()
#    OS_to_SS= 1.08
    for bin in range(qcd_Shape.GetNbinsX()):
        
        if qcd_Shape.GetBinContent(bin) < 0:
           print "\t before %s, bin %d is %f"%(NormMC, bin,qcd_Shape.GetBinContent(bin))
           qcd_Shape.SetBinContent(bin, 0.0001)
           qcd_Shape.SetBinError(bin, 0.0001)
           print "%s, bin %d is %f"%(NormMC, bin,qcd_Shape.GetBinContent(bin))
    


    qcd_Norm.Scale(OS_to_SS)
    NormQCD= qcd_Norm.Integral()
    if  NormQCD < 0:  NormQCD=0.001
    qcd_Shape.Scale(NormQCD/qcd_Shape.Integral())
    
    tDirectory.cd()
    tDirectory.WriteObject(qcd_Shape,"QCD")
    
    for bin in range(qcd_Shape.GetNbinsX()):
        print "%s, bin %d is %f"%(NormMC, bin,qcd_Shape.GetBinContent(bin))

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
                    templateqcdShape=Norm+reg+"_AntiIso"+"_SS"
                
                    MakeTheHistogram(channel,NormMC,qcdOS,qcdSS,templateqcd,templateqcdShape,reg)
