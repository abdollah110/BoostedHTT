# This code is to change the 5 bin to 4 bin histogram
import ROOT
from ROOT import *
import array
import re
from array import *
from optparse import OptionParser
import sys

#parser = OptionParser()
import argparse
parser = argparse.ArgumentParser("Compare total template to stage 1.1 templates")
parser.add_argument(
        "-i",
        "--inputfile",
        action="store",
        dest="inputfile",
        default="X.root",
        help="Which file1name to run over?")
parser.add_argument(
        "-o",
        "--outputfile",
        action="store",
        dest="outputfile",
        default="Y.root",
        help="Which file1name to run over?")
args = parser.parse_args()

inputfile =args.inputfile
outputfile=args.outputfile

file=ROOT.TFile(inputfile,"r")
file.cd()
dirList = gDirectory.GetListOfKeys()


ofile=ROOT.TFile(outputfile,"recreate")
categories_list= file.GetListOfKeys()
categories=[]
for k2 in categories_list:
	categories.append(k2.GetName())
ncat=len(categories)
for k1 in dirList: # loop over categories
    print 'hi ', k1

    names_histos_used=[]

    h1 = k1.ReadObj()
    nom=k1.GetName()
    ofile.mkdir(nom)
    h1.cd()
    histoList = gDirectory.GetListOfKeys()
    name_last=""
    N_histo=0



    for histo in histoList:
    
        print histo, '\t' , histo.GetName()
        histo_name=histo.GetName()
        h1.cd()
        h2 = histo.ReadObj()
#        print 'number of bins   ', numBin(h2)
        h3=h2.Clone()
        xList = [250,350,450,600,2000]
#        inclusiveBinning = array.array('d', [0,350,450,600,2000])
#        inclusiveBinning = array.array('d', xList)
        inclusiveBinning = array('d', xList)
        print 'siz is ', len(inclusiveBinning)-1, inclusiveBinning[0], inclusiveBinning[4]
#        xList = [0,350]
        NewHist=TH1F(histo_name,histo_name,len(inclusiveBinning)-1,inclusiveBinning)
#        NewHist.Rebin(xList[0])
        NewHist.SetBinContent(1,h3.GetBinContent(1))
        NewHist.SetBinError(1,h3.GetBinError(1))
        NewHist.SetBinContent(2,h3.GetBinContent(2))
        NewHist.SetBinError(2,h3.GetBinError(2))
        NewHist.SetBinContent(3,h3.GetBinContent(3))
        NewHist.SetBinError(3,h3.GetBinError(3))
        NewHist.SetBinContent(4,h3.GetBinContent(4)+h3.GetBinContent(5))
        NewHist.SetBinError(4,h3.GetBinError(4)+h3.GetBinError(5))

        
        ofile.cd(nom)
        NewHist.SetTitle(histo_name)
        NewHist.Write(histo_name)
        
ofile.Close()
