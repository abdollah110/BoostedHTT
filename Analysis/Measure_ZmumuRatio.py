from ROOT import *
import array
import sys

ifile=sys.argv[1]

#inputFile=TFile('boost_mm_2016_v4/TotalRootForLimit_PreSelection_2DZMassPt_OS.root','r')
inputFile=TFile(ifile,'r')

year=0
if '2016' in ifile:
    year = 2016
elif '2017' in ifile:
    year = 2017
elif '2018' in ifile:
    year = 2018
else:
    print 'which year ???'

histData=inputFile.Get('pass/data_obs')
histDYLL=inputFile.Get('pass/DYJets125')
histW=inputFile.Get('pass/W')
histTT=inputFile.Get('pass/TT')
histVV=inputFile.Get('pass/VV')

all=[histData,histDYLL,histW, histVV, histTT]
nonDY=[histW, histVV, histTT]

for sam in nonDY:
    sam.Scale(-1)
    histData.Add(sam)
    

histDataOrg=histData.Clone()
histDYLLOrg=histDYLL.Clone()

histData.Divide(histDYLL)

can=TCanvas()

gStyle.SetPaintTextFormat('0.2f ')
gStyle.SetTextSize(0.01);
gStyle.SetOptStat(0)

histData.SetTitle("scale factor ("+str(year)+")")
histData.GetXaxis().SetTitle("m_{#mu#mu} [GeV]")
histData.GetYaxis().SetTitle("pT_{#mu#mu} [GeV]")
histData.Draw("textcolz")
can.SaveAs('zmm_ratio_{}.pdf'.format(year))

histDataErr=histData.Clone()
for i in range(0,histDataErr.GetNbinsX()):
    for j in range(0,histDataErr.GetNbinsY()):
        histDataErr.SetBinContent(i+1,j+1,histDataErr.GetBinError(i+1,j+1))


histDataErr.SetTitle("scale factor uncertainty ("+str(year)+")")
histDataErr.GetXaxis().SetTitle("m_{#mu#mu} [GeV]")
histDataErr.GetYaxis().SetTitle("pT_{#mu#mu} [GeV]")
histDataErr.Draw("textcolz")
can.SaveAs('zmm_ratio_{}_Err.pdf'.format(year))

histDataOrg.Draw("textcolz")
can.SaveAs('_data_{}.pdf'.format(year))

histDYLLOrg.Draw("textcolz")
can.SaveAs('_zll_{}.pdf'.format(year))

outFile=TFile('dataTest/zmm_2d_{}.root'.format(year),'RECREATE')
outH=histData.Clone()
outH.SetName('Ratio2D')
outH.Write()
outFile.Close()

for i in range(histData.GetNbinsX()):
    for j in range(histData.GetNbinsY()):
        print i+1, j+1, histData.GetBinContent(i+1,j+1), '+/-', histData.GetBinError(i+1,j+1)
