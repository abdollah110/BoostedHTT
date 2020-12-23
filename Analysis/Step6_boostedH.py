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


verbos_ = True
RB_=1

bcde_to_bcdef=1
#if year ==2018:
#    bcde_to_bcdef=0.95

process=[
    ['H125','HTT',0],
    ['VV','Diboson',-1],
#    ['SingleTop','SingleTop',-1],
    ['TT','ttbar',-1],
    ['ZTT','DYJets125',-1],
#    ['ZLL','ZLL',-1],
#    ['ZJ','ZJ',-1],
    ['W','WJets',-1],
    ['Data','data_obs',+1],
]

#systs = ['met_JESUp', 'met_JESDown', 'met_UESUp', 'met_UESDown','dyShape_Up', 'dyShape_Down', 'zmumuShape_Up', 'zmumuShape_Down']
systs = ['met_JESUp', 'met_JESDown', 'met_UESUp', 'met_UESDown']
#systs = [""]
  
#
#
#if name != 'embed' and name != 'data_obs':
#     systs += [
#             'met_JESUp', 'met_JESDown', 'met_UESUp', 'met_UESDown'
#              ]
#
##  if name == 'TT':
##    systs += ['ttbarShape_Up', 'ttbarShape_Down']
#
#  if name == 'ZLL' or name == 'ZTT' or name == 'ZJ':
#    systs += ['dyShape_Up', 'dyShape_Down', 'zmumuShape_Up', 'zmumuShape_Down']
    
    
    

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

    if region=='_PassL' or region=='_PassM' or region=='_PassT' :CatName='pass'
    if region=='_FailL' or region=='_FailM' or region=='_FailT' :CatName='fail'
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
##            myfile = TFile(InputFilesLocation +'/DYJetsToLL.root')
#            myfile = TFile(InputFilesLocation +'/ZTT.root')
#            NormHisto =  myfile.Get(channel+NormMC )
#            NormHisto.Scale(0.001/NormHisto.Integral())
#            RebinedHist= NormHisto.Rebin(RB_)
#            tDirectory.WriteObject(XX,pro[1])
            
        else:
            RebinedHist= NormHisto.Rebin(RB_)
            if not 'Data' in pro[0] : RebinedHist.Scale(bcde_to_bcdef)
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
                sysNormHisto =  sysfile.Get(channel+NormMC )
                sysRebinedHist= sysNormHisto.Rebin(RB_)
                tDirectory.WriteObject(sysRebinedHist,pro[1]+'_'+sys)

                
                
    ################################################
    #  Estimate OS/SS ratio
    ################################################

    getNormOfQCD_OS=getNormOfQCD(channel,qcdOS)
    print "getNormOfQCD_OS= ", getNormOfQCD_OS
    getNormOfQCD_SS=getNormOfQCD(channel,qcdSS)
    print "getNormOfQCD_SS= ", getNormOfQCD_SS
    
#    OS_to_SS= getNormOfQCD_OS/getNormOfQCD_SS
#    print "os/ss is= ", OS_to_SS
    
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
    OS_to_SS= 1.08
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
    
    PlotName=["ZMass","tmass","ht","lepPt","tauPt","MET"]
#    PlotName=["ZMass"]


#    Isolation=["_Iso", "_AntiIso"]
#    Charge= ["_OS","_SS"]
    region= ["_PassL", "_FailL","_PassM", "_FailM","_PassT", "_FailT"]
#    region= ["_PassM", "_FailM"]
#    region= ["_PassT", "_FailT"]

    Isolation=["_Iso"]
    Charge= ["_OS"]



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
