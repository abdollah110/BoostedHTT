import os
import sys
import ROOT
from ROOT import *

ROOT.gStyle.SetFrameLineWidth(3)
ROOT.gStyle.SetLineWidth(3)
ROOT.gStyle.SetOptStat(0)

file1=sys.argv[1]
file2=sys.argv[2]
histName=sys.argv[3]
dirName=sys.argv[4]

F1=TFile(file1,'read')
F2=TFile(file2,'read')

his1=F1.Get(dirName+'/'+ histName)
his2=F2.Get(dirName+'/'+ histName)


c=TCanvas()
c.SetLogy()

his1.SetMarkerStyle(22)
his1.SetMarkerColor(2)
his2.SetMarkerStyle(20)
his2.SetMarkerColor(4)

his1.GetXaxis().SetTitle('Higgs p_{T} [GeV]')

his1.Draw()
his2.Draw('same')

leg=ROOT.TLegend(0.6, 0.6, 0.85, 0.82, "", "brNDC")
leg.SetLineWidth(0)
leg.SetLineStyle(0)
leg.SetFillStyle(0)
leg.SetTextSize(0.04)
#    leg.SetBorderSize(0)
leg.SetTextFont(62)
leg.AddEntry(his1,'dR < 0.8','p')
leg.AddEntry(his2,'dR < 0.5','p')
#    leg.AddEntry(Histo3,name3,'lp')

leg.Draw()



c.SaveAs('overlap_{}_{}.pdf'.format(histName,dirName))
