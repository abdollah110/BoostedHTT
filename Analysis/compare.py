
import os, sys
#rootFile=sys.argv[1]
#histNum=sys.argv[2]
#histDeNum=sys.argv[3]

import ROOT
from ROOT import *
ROOT.gStyle.SetOptStat(0)
#c=TCanvas()
#inFile=TFile(rootFile)
#hNum=inFile.Get(histNum)
#print hNum.Integral()
#hDeNum=inFile.Get(histDeNum)
#print hDeNum.Integral()
#hNum.Divide(hDeNum)
#hNum.GetYaxis().SetRangeUser(0,3)
#hNum.Draw()
#c.SaveAs('out.pdf')
#


channels =[
    ('mt', 'process_trees_lt_fr'),
    ('et', 'process_trees_lt_fr'),
    ('tt', 'process_trees_tt'),
]
year = ['2016','2017','2018']
for yr in year:
    for ch in channels:
    
        qcd_W=TFile('Output/templates/{}{}_m_sv_fakeComparison_qcd_W.root'.format(ch[0],yr),'READ')
        qcd=TFile('Output/templates/{}{}_m_sv_fakeComparison_qcd.root'.format(ch[0],yr),'READ')

        hist_qcd_W=qcd_W.Get('{}_0jet/QCD'.format(ch[0]))
        hist_qcd=qcd.Get('{}_0jet/QCD'.format(ch[0]))
        hist_W=qcd_W.Get('{}_0jet/W'.format(ch[0]))
        hist_W_alone=hist_W.Clone()
        hist_W.Add(hist_qcd)
        c=TCanvas()
        hist_qcd_W.Draw()
        hist_qcd_W.SetMarkerStyle(24)
        hist_qcd_W.SetMaximum(hist_qcd_W.GetMaximum()*2)
        hist_W.SetLineColor(3)
        hist_W.SetMarkerColor(3)
        hist_W.SetMarkerStyle(21)
        hist_W.Draw('same')
        
        leg = ROOT.TLegend(0.12, 0.7, 0.85, 0.85)
        leg.SetLineColor(0)
        leg.SetFillColor(0)
#        leg.SetTextFont(61)
#        leg.SetTextFont(42)
        leg.SetTextSize(0.035)

        # data
        leg.AddEntry(hist_qcd_W, 'Collective est. of QCD and W= {}'.format(round(hist_qcd_W.Integral(),0)), 'ep')
        leg.AddEntry(hist_W, 'Est. of QCD from data ({})+ W from MC({}) = {}'.format(round(hist_qcd.Integral(),0),round(hist_W_alone.Integral(),0),round(hist_qcd.Integral()+hist_W_alone.Integral(),0)), 'ep')
#        leg.AddEntry(hist_W, 'Estimation of QCD from data ({})+ W from simulation({}) = {} {}'.format(hist_qcd.Integral(),hist_W.Integral(),hist_qcd.Integral()+hist_W.Integral()), 'ep')
        leg.Draw()
        
        hist_qcd_W.SetTitle('{}_{}'.format(ch[0],yr))
        hist_qcd_W.GetXaxis().SetTitle('m_{#tau#tau} [GeV]')
        c.SaveAs('qcdCompare_{}_{}.pdf'.format(ch[0],yr))
        
        
        
#Output/templates/mt2016_m_sv_fakeComparison_qcd_W.root
#Output/templates/mt2017_m_sv_fakeComparison_qcd_W.root
#Output/templates/mt2018_m_sv_fakeComparison_qcd_W.root
#Output/templates/et2016_m_sv_fakeComparison_qcd_W.root
#Output/templates/et2017_m_sv_fakeComparison_qcd_W.root
#Output/templates/et2018_m_sv_fakeComparison_qcd_W.root
#Output/templates/tt2016_m_sv_fakeComparison_qcd_W.root
#Output/templates/tt2017_m_sv_fakeComparison_qcd_W.root
#Output/templates/tt2018_m_sv_fakeComparison_qcd_W.root
#Output/templates/et2016_m_sv_fakeComparison_qcd.root
#Output/templates/et2017_m_sv_fakeComparison_qcd.root
#Output/templates/et2018_m_sv_fakeComparison_qcd.root
#Output/templates/mt2018_m_sv_fakeComparison_qcd.root
#Output/templates/mt2017_m_sv_fakeComparison_qcd.root
#Output/templates/mt2016_m_sv_fakeComparison_qcd.root
#Output/templates/tt2018_m_sv_fakeComparison_qcd.root
#Output/templates/tt2017_m_sv_fakeComparison_qcd.root
#Output/templates/tt2016_m_sv_fakeComparison_qcd.root
