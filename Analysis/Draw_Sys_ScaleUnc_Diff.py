import os
import ROOT
from ROOT import *
import math


def findMaxBin(ibin,histList):
    maxBinContent=0
    maxBinError=0
    print len(histList)
    for hist in histList:
        binContent=hist.GetBinContent(ibin)
        if binContent>maxBinContent:
            maxBinContent=binContent
            maxBinError=hist.GetBinError(ibin)
    return maxBinContent,maxBinError


def findMinBin(ibin,histList):
    minBinContent=1000000
    minBinError=0
    for hist in histList:
        binContent=hist.GetBinContent(ibin)
        if binContent < minBinContent:
            minBinContent=binContent
            minBinError=hist.GetBinError(ibin)
    return minBinContent,minBinError


from glob import glob
from optparse import OptionParser

parser = OptionParser()
parser.add_option('--path', '-p', action='store',
                  default='root_files/', dest='path',
                  help='path to input file directory'
                  )
(options, args) = parser.parse_args()



InputRootFiles = [ifile for ifile in glob(options.path+'/*') if '.root' in ifile and 'pdfscale.root' not in ifile]

for inFile in InputRootFiles:
    print '\n\n\n\n starting ', inFile
    
    File=TFile(inFile,'R')
    
    File.Cp(File.GetName().replace('.root','_')+"pdfscale.root")
    
    channel=''
    year=0
    
    if '2016' in inFile:
        year = 2016
    elif '2017' in inFile:
        year = 2017
    elif '2018' in inFile:
        year = 2018
    elif '2020' in inFile:
        year = 2020
    else:
        print 'which year ???'
    print "the found year is {}".format(year)


    if '_em' in inFile or 'em2' in inFile:
        channel = 'em'
    elif '_me' in inFile or    'me2' in inFile:
        channel = 'em'
    elif '_mt' in inFile or 'mt2' in inFile:
        channel = 'mt'
    elif '_et' in inFile  or  'et2' in inFile:
        channel = 'et'
    elif '_tt' in inFile  or  'tt2' in inFile:
        channel = 'tt'
    else:
        print 'which channel ???'
    print "the found channel is {}".format(channel)


    cat=''
    if 'bin0' in inFile: cat = '_bin0'
    elif 'bin1' in inFile: cat = '_bin1'
    elif 'bin2' in inFile: cat = '_bin2'
    elif 'bin3' in inFile: cat = '_bin3'
    elif 'bin4' in inFile: cat = '_bin4'
    else:
        print 'which category/bin ???'
    print "the found category is {}".format(cat)
    

    lastSys=0
    lowBin=0
    highBin=1
##########################################################################################
# PDF Uncertainty
##########################################################################################
    process=['ZTT','TT']
    for pro in process:
    
        if pro=='ZTT': lastSys= 111
        else:
            if year==2016 : lastSys= 227
            elif year==2017 : lastSys= 972
            elif year==2018 : lastSys= 972
        
        print  '\t\t lastSys  -->  ', lastSys

        print 'histo name is {}{}/{}'.format(channel,cat,pro)
        HisMean=File.Get('{}{}/{}'.format(channel,cat,pro))
        print HisMean.GetName(), HisMean.GetNbinsX()
        
        histPdfUp=TH1F("pdfUp"+cat,"pdfUp"+cat,HisMean.GetNbinsX(),lowBin , highBin)
        histPdfDown=TH1F("pdfDown"+cat,"pdfDown"+cat,HisMean.GetNbinsX(),lowBin , highBin)
        for ibin in range(0,HisMean.GetNbinsX()):
        
            sumP=0
            numP=0
            sumN=0
            numN=0
                    
            meanCental=HisMean.GetBinContent(ibin+1)
            meanError=HisMean.GetBinError(ibin+1)
            for isys in range(9,lastSys):

                HistSys=File.Get('{}{}/{}___{}{}{}'.format(channel,cat,pro,channel,cat,str(isys)))
                if not HistSys:
                    print '\n %%%%% \n sample {} does not exist \n %%%%% \n'.format('{}{}/{}___{}{}{}'.format(channel,cat,pro,channel,cat,str(isys)))
                    continue
                meanSys=HistSys.GetBinContent(ibin+1)

                if meanSys > meanCental:
                    sumP +=((meanSys-meanCental)*(meanSys-meanCental))
                    numP +=1

                if meanSys < meanCental:
                    sumN +=((meanCental-meanSys)*(meanCental-meanSys))
                    numN +=1

            MaxBinValue= meanCental+math.sqrt( 1./(numP -1) *sumP  )
            MinBinValue= meanCental-math.sqrt( 1./(numN -1) *sumN  )

            histPdfUp.SetBinContent(ibin+1,MaxBinValue)
            histPdfUp.SetBinError(ibin+1,meanError)
            
            histPdfDown.SetBinContent(ibin+1,MinBinValue)
            histPdfDown.SetBinError(ibin+1,meanError)
            
        newFile=TFile(File.GetName().replace('.root','_')+"pdfscale.root",'UPDATE')
        tDirectory= newFile.Get(channel+cat)
        tDirectory.cd()
        tDirectory.WriteObject(histPdfUp,'{}_pdfUp'.format(pro))
        tDirectory.WriteObject(histPdfDown,'{}_pdfDown'.format(pro))
        newFile.Close()
        histPdfUp.Delete()
        histPdfDown.Delete()

                    


##########################################################################################
# Scale Uncertainty
##########################################################################################

    
    process=['ZTT','TT']
    for pro in process:
    
        HisMean=File.Get('{}{}/{}'.format(channel,cat,pro))
        histScaleUp=TH1F("scaleUp"+cat,"scaleUp"+cat,HisMean.GetNbinsX(),lowBin , highBin)
        histScaleDown=TH1F("scaleDown"+cat,"scaleDown"+cat,HisMean.GetNbinsX(),lowBin , highBin)
        for ibin in range(0,HisMean.GetNbinsX()):
        
            listHistForScale=[]
            for isys in range(0,9):
                    
        #        if isys==5 or isys==7: continue  # these 2 are non-physical related to the (2,0.5) or (0.5,2)
                if isys==6 or isys==8: continue  # these 2 are non-physical related to the (2,0.5) or (0.5,2)
                
                
                hist=File.Get('{}{}/{}___{}{}{}'.format(channel,cat,pro,channel,cat,str(isys)))
                if not hist:
                    print '\n %%%%% \n sample {} does not exist \n %%%%% \n'.format('{}{}/{}___{}{}{}'.format(channel,cat,pro,channel,cat,str(isys)))
                    continue
                
                listHistForScale.append(File.Get('{}{}/{}___{}{}{}'.format(channel,cat,pro,channel,cat,str(isys))))
                
            maxBinContent,maxBinError=findMaxBin(ibin+1,listHistForScale)
            minBinContent,minBinError=findMinBin(ibin+1,listHistForScale)
            histScaleUp.SetBinContent(ibin+1,maxBinContent)
            histScaleUp.SetBinError(ibin+1,maxBinError)
            histScaleDown.SetBinContent(ibin+1,minBinContent)
            histScaleDown.SetBinError(ibin+1,minBinError)

        newFile=TFile(File.GetName().replace('.root','_')+"pdfscale.root",'UPDATE')
        tDirectory= newFile.Get(channel+cat)
        tDirectory.cd()
        tDirectory.WriteObject(histScaleUp,'{}_scaleUp'.format(pro))
        tDirectory.WriteObject(histScaleDown,'{}_scaleDown'.format(pro))
        newFile.Close()
    
    
##########################################################################################
# End
##########################################################################################
