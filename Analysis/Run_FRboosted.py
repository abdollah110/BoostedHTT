import ROOT
from ROOT import *
import sys
input=sys.argv[1]
year=0
if '2016' in input: year =2016 ; lumi = "35.9 fb^{-1}"
elif '2017' in input: year =2017 ; lumi = "41.5 fb^{-1}"
elif '2018' in input: year =2018 ; lumi = "59.7 fb^{-1}"
else: print 'Which year are you looking for\n'

Nums=['numVLoose','numLoose','numMedium','numTight']
for num in Nums:
    inputFile=TFile(input,'r')
    vv=input.replace('Data','VV')
    inputFileVV=TFile(vv,'r')
    numHist=inputFile.Get(num)
    numHistvv=inputFileVV.Get(num)
    denumHist=inputFile.Get('denum')
    denumHistvv=inputFileVV.Get('denum')
    numHist.Add(numHistvv,-1)
    denumHist.Add(denumHistvv,-1)
    numHistRB=numHist.Rebin(2)
    denumHistRB=denumHist.Rebin(2)
    numHistRB.Divide(denumHistRB)
    can=TCanvas()
    numHistRB.GetYaxis().SetRangeUser(0,1)
    numHistRB.GetYaxis().SetTitle('Jet to tau fake rate')
    numHistRB.GetXaxis().SetTitle('boosted #tau p_{T}')
    numHistRB.Draw()

    cms = ROOT.TLatex()
    cms.SetNDC(ROOT.kTRUE)
    cms.SetTextFont(61)
    cms.SetTextSize(0.07)
    cms.DrawLatex(0.16, 0.8, "CMS")

    prel = ROOT.TLatex()
    prel.SetNDC(ROOT.kTRUE)
    prel.SetTextFont(52)
    prel.SetTextSize(0.04)
    prel.DrawLatex(0.16, 0.74, "Preliminary")

    can.SaveAs('Output/fake/fr_{}_{}.pdf'.format(num,year))
    can.SaveAs('Output/fake/fr_{}_{}.root'.format(num,year))
    OutRoot=TFile('data/File_fr_{}_{}.root'.format(num,year),'RECREATE')
    numHistRB.Write()
    OutRoot.Close()
