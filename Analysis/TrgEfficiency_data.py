import os
import sys
import ROOT
from ROOT import *
import array

rb_ = array.array("d",[0,100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000])

def add_CMS(year):
    lowX=0.21
    lowY=0.80
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(61)
    lumi.SetTextSize(0.06)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("CMS Internal {}".format(year))
    return lumi


def MakeCompare(root1,hist1,name1, root2,hist2, name2,Sample):

    year=0
    if '2016' in root1:
        year = 2016
    elif '2017' in root1:
        year = 2017
    elif '2018' in root1:
        year = 2018
    else:
        print 'which year ???'

    
    ROOT.gStyle.SetFrameLineWidth(3)
    ROOT.gStyle.SetLineWidth(3)
    ROOT.gStyle.SetOptStat(0)
    
    c=ROOT.TCanvas("canvas","",0,0,600,600)
    c.cd()
    
    
    file1=TFile(root1,"open")
    print "---->,", file1.GetName()
    Histo1=file1.Get(hist1)
#    Histo1=Histo1_.Rebin(len(rb_)-1,"",rb_)
    Histo1.SetLineColor(4)
    Histo1.SetLineWidth(2)
    Histo1.SetMarkerSize(1.3)
#    Histo1.SetMaximum(Histo1.GetMaximum()*200)
    
    Histo1.SetMarkerColor(4)
    Histo1.SetMarkerStyle(20)
    
    file2=TFile(root2,"open")
    Histo2=file2.Get(hist2)
#    Histo2=Histo2_.Rebin(len(rb_)-1,"",rb_)
    Histo2.SetLineColor(2)
    Histo2.SetLineWidth(3)
    Histo2.SetMarkerColor(2)
    Histo2.SetMarkerSize(1.5)
    Histo2.SetMarkerStyle(29)
    
    Histo1.SetMaximum(Histo2.GetMaximum()*1.5)
    
#    file3=TFile(root3,"open")
#    Histo3_=file3.Get(hist3)
#    Histo3=Histo3_.Rebin(len(rb_)-1,"",rb_)
#    Histo3.SetLineColor(4)
#    Histo3.SetLineWidth(4)
#    Histo3.SetMarkerColor(4)
#    Histo3.SetMarkerStyle(24)
    

#    Histo1.SetTitle('')
    Histo1.GetXaxis().SetTitle('boson p_{T} (GeV)')
#    Histo1.GetXaxis().SetLabelSize(0.04)
#    Histo1.GetXaxis().SetNdivisions(505)
#    Histo1.GetXaxis().SetTitleSize(0.05)
#    Histo1.GetXaxis().SetTitleOffset(0.9)
#    Histo1.GetXaxis().SetLabelSize(0.04)
#    Histo1.GetXaxis().SetTitleFont(42)
#    Histo1.GetYaxis().SetTitle("Events")
#    Histo1.GetXaxis().SetRangeUser(50,1000)

    Histo1.GetXaxis().SetTitle("")
    Histo1.GetXaxis().SetTitleSize(0)
    Histo1.GetXaxis().SetLabelSize(0)
    Histo1.GetXaxis().SetNdivisions(505)
    Histo1.GetYaxis().SetLabelFont(42)
    Histo1.GetYaxis().SetLabelOffset(0.01)
    Histo1.GetYaxis().SetLabelSize(0.06)
    Histo1.GetYaxis().SetTitleSize(0.075)
    Histo1.GetYaxis().SetTitleOffset(1.04)
    Histo1.SetTitle("")
#    Histo1.Setlabel("")
    Histo1.GetYaxis().SetTitle("Events")
#    Histo1.GetXaxis().SetRangeUser(50,1000)    




    pad1 = ROOT.TPad("pad1","pad1",0,0.35,1,1)
#    pad1.SetLogy()
    pad1.Draw()
    pad1.cd()
    pad1.SetFillColor(0)
    pad1.SetBorderMode(0)
    pad1.SetBorderSize(10)
    pad1.SetTickx(1)
    pad1.SetTicky(1)
    pad1.SetLeftMargin(0.18)
    pad1.SetRightMargin(0.05)
    pad1.SetTopMargin(0.122)
    pad1.SetBottomMargin(0.026)
    pad1.SetFrameFillStyle(0)
    pad1.SetFrameLineStyle(0)
    pad1.SetFrameLineWidth(3)
    pad1.SetFrameBorderMode(0)
    pad1.SetFrameBorderSize(10)
    
    
    
    
    
    
    Histo1.Draw()
    Histo2.Draw('same')
#    Histo3.Draw('same')
    
    
    l2=add_CMS(year)
    l2.Draw()


    categ  = ROOT.TPaveText(0.15, 0.4+0.013, 0.85, 0.5+0.1, "NDC")
    categ.SetBorderSize(   0 )
    categ.SetFillStyle(    0 )
    categ.SetTextAlign(   12 )
    categ.SetTextSize ( 0.06 )
    categ.SetTextColor(    1 )
#    if Sample.find('14'): Sample=Sample.replace(14,1200)
    categ.AddText(Sample)
    categ.Draw()
    
    
    

    leg=ROOT.TLegend(0.2, 0.6, 0.55, 0.82, "", "brNDC")
    leg.SetLineWidth(1)
    leg.SetLineStyle(0)
    leg.SetFillStyle(0)
    leg.SetTextSize(0.04)
#    leg.SetBorderSize(0)
    leg.SetTextFont(62)
    leg.AddEntry(Histo1,name1,'p')
    leg.AddEntry(Histo2,name2,'p')
#    leg.AddEntry(Histo3,name3,'lp')
    
    leg.Draw()
    
    pad1.RedrawAxis()
    
    c.cd()
    pad2 = ROOT.TPad("pad2","pad2",0,0,1,0.35);
    pad2.SetTopMargin(0.05);
    pad2.SetBottomMargin(0.35);
    pad2.SetLeftMargin(0.18);
    pad2.SetRightMargin(0.05);
    pad2.SetTickx(1)
    pad2.SetTicky(1)
    pad2.SetFrameLineWidth(3)
    pad2.SetGridx()
    pad2.SetGridy()
    pad2.Draw()
    pad2.cd()
    
    
    
    
    h1=Histo1.Clone()
    maxVal=0.5
    if 'MET' in Sample:maxVal =0.9
    h1.SetMaximum(maxVal)
    h1.SetMinimum(0.0)
    h1.SetMarkerStyle(20)
    h1.SetMarkerColor(4)
#    h1.GetXaxis().SetTitle('boson p_{T} (GeV)')
    
#    h5=Histo3.Clone()
#    h5.SetMarkerStyle(24)
#    h5.SetMarkerColor(4)
    
    
    h2=Histo2.Clone()
    
    
    h1.Sumw2()
    h2.Sumw2()
    
    
#    h5.Sumw2()
#    h3.Sumw2()

    h1.SetStats(0)
    h2.SetStats(0)
#    h3.SetStats(0)
#    h5.SetStats(0)
    h1.SetTitle("")
    
    h1.Divide(h2)
#    h5.Divide(h2)
    
    
    h1.GetXaxis().SetTitle("")
    h1.GetXaxis().SetLabelSize(0.08)
    h1.GetYaxis().SetLabelSize(0.08)
    h1.GetYaxis().SetTitle("Trg. Eff.")
    h1.GetXaxis().SetNdivisions(505)
    h1.GetYaxis().SetNdivisions(5)
    h1.GetXaxis().SetTitleSize(0.15)
    h1.GetYaxis().SetTitleSize(0.1)
    h1.GetYaxis().SetTitleOffset(0.56)
    h1.GetXaxis().SetTitleOffset(1.04)
    h1.GetXaxis().SetLabelSize(0.11)
    h1.GetYaxis().SetLabelSize(0.11)
    h1.GetXaxis().SetTitleFont(42)
    h1.GetYaxis().SetTitleFont(42)
    h1.GetXaxis().SetTitle('run')
    
    h1.Draw()
#    h5.Draw("same")


    c.cd()
    pad1.Draw()
    
    ROOT.gPad.RedrawAxis()
    
    c.Modified()
    
    
    
    c.SaveAs('_TrgEff_{}_{}.pdf'.format(year,Sample))


inputfile=sys.argv[1]
trigger=sys.argv[2]
triggerName=sys.argv[3]

MakeCompare(inputfile, trigger,'After HLT Cut', inputfile, 'RunBeforeTrigger','Before HLT Cut',triggerName)




#python TrgEfficiency_data.py newBoost_tt_2016_TrgFix/_nominal/JetHT.root RunHLTJet38 HLT_AK8PFJet360_TrimMass30
#python TrgEfficiency_data.py newBoost_tt_2017_TrgFix/_nominal/JetHT.root RunHLTJet40 HLT_AK8PFJet400_TrimMass30
#python TrgEfficiency_data.py newBoost_tt_2018_TrgFix/_nominal/JetHT.root RunHLTJet40 HLT_AK8PFJet400_TrimMass30
#python TrgEfficiency_data.py newBoost_tt_2016_TrgFix/_nominal/HTMHT.root RunHLTJet39 HLT_PFHT300_PFMET110
#python TrgEfficiency_data.py newBoost_tt_2017_TrgFix/_nominal/HTMHT.root RunHLTJet39 HLT_PFHT500_PFMET100_PFMHT100_IDTight
#python TrgEfficiency_data.py newBoost_tt_2018_TrgFix/_nominal/JetHT.root RunHLTJet39 HLT_PFHT500_PFMET100_PFMHT100_IDTight

