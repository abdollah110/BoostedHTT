import os
import ROOT
from ROOT import *
import sys

def add_CMS():
    lowX=0.11
    lowY=0.83
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(61)
    lumi.SetTextSize(0.06)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("CMS")
    return lumi
def add_Simulation():
    lowX=0.23
    lowY=0.83
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(22)
    lumi.SetTextSize(0.06)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("Simulation")
    return lumi
def make_legend():
        output = ROOT.TLegend(0.15, 0.7, 0.45, 0.92, "", "brNDC")
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillStyle(0)
        output.SetBorderSize(0)
        output.SetTextFont(62)
        return output



Input= sys.argv[1]
inputF=TFile(Input,"READ")
num=inputF.Get("higgs_pT_num")
denum=inputF.Get("higgs_pT_denum")
num.Divide(denum)

c=ROOT.TCanvas("canvas","",0,0,600,600)

num.SetMarkerSize(2)
num.SetMarkerStyle(20)
num.SetMarkerColor(55)
num.SetLineColor(55)

#num.GetXaxis().SetTitleSize(0)
num.GetXaxis().SetNdivisions(505)
num.GetYaxis().SetLabelFont(42)

num.GetYaxis().SetLabelSize(0.04)
num.GetXaxis().SetLabelSize(0.04)

num.GetYaxis().SetTitleSize(0.04)
num.GetXaxis().SetTitleSize(0.04)
num.GetYaxis().SetTitleOffset(1.1)
#num.GetYaxis().SetLabelOffset(0.5)
num.SetTitle("")
#num.GetYaxis().SetTitle("Events")
num.SetStats(0)
#num.SetTitle("")
num.GetYaxis().SetTitle("#tau_{h}#tau_{h} isolation efficiency")
num.GetXaxis().SetTitle("Higgs p_{T} [GeV]")
num.Draw("ep")
lumi=add_CMS()
lumi.Draw()
sim=add_Simulation()
sim.Draw()
legende=make_legend()
legende.AddEntry(num,"BoostedTau","p")
legende.Draw()

outName=Input.split("/")[-1].replace(".root","")
c.SaveAs('{}.pdf'.format(outName))
