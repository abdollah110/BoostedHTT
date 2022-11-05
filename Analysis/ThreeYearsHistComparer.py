
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

yr2016=sys.argv[1]
yr2017=sys.argv[2]
yr2018=sys.argv[3]
FinalDir=sys.argv[4]

file2016=TFile(yr2016,'READ')
file2017=TFile(yr2017,'READ')
file2018=TFile(yr2018,'READ')


processes=['TT','VV','JJH125','NonDY','QCD','W','XH125','ZTT','data_obs','ggH125','mcFake']
channels=['et','mt','tt']
#channels=['mt']

for pro in processes:
    for ch in channels:
    
        print 'starting channel {} and process {}'.format(ch,pro)
    
        hist2016=file2016.Get('{}_0jet/{}'.format(ch,pro))
        hist2017=file2017.Get('{}_0jet/{}'.format(ch,pro))
        hist2018=file2018.Get('{}_0jet/{}'.format(ch,pro))

        hist2016.SetLineColor(2)
        hist2017.SetLineColor(3)
        hist2018.SetLineColor(4)


        hist2016.SetMaximum(hist2016.GetMaximum()*2)

        C=TCanvas()
        hist2016.DrawNormalized()
        hist2017.DrawNormalized('same')
        hist2018.DrawNormalized('same')
        
        


        leg = ROOT.TLegend(0.42, 0.7, 0.85, 0.85)
        leg.SetLineColor(0)
        leg.SetFillColor(0)
        leg.SetTextSize(0.035)

        leg.AddEntry(hist2016, '2016', 'epl')
        leg.AddEntry(hist2017, '2017', 'epl')
        leg.AddEntry(hist2018, '2018', 'epl')
        
        leg.Draw()

        C.SaveAs('{}/_3yearCompare_{}_{}.pdf'.format(FinalDir,ch,pro))
        
#
#channels =[
#    ('mt', 'process_trees_lt_fr'),
#    ('et', 'process_trees_lt_fr'),
#    ('tt', 'process_trees_tt'),
#]
#year = ['2016','2017','2018']
#for yr in year:
#    for ch in channels:
#
#        qcd_W=TFile('Output/templates/{}{}_m_sv_fakeComparison_qcd_W.root'.format(ch[0],yr),'READ')
#        qcd=TFile('Output/templates/{}{}_m_sv_fakeComparison_qcd.root'.format(ch[0],yr),'READ')
#
#        hist_qcd_W=qcd_W.Get('{}_0jet/QCD'.format(ch[0]))
#        hist_qcd=qcd.Get('{}_0jet/QCD'.format(ch[0]))
#        hist_W=qcd_W.Get('{}_0jet/W'.format(ch[0]))
#        hist_W_alone=hist_W.Clone()
#        hist_W.Add(hist_qcd)
#        c=TCanvas()
#        hist_qcd_W.Draw()
#        hist_qcd_W.SetMarkerStyle(24)
#        hist_qcd_W.SetMaximum(hist_qcd_W.GetMaximum()*2)
#        hist_W.SetLineColor(3)
#        hist_W.SetMarkerColor(3)
#        hist_W.SetMarkerStyle(21)
#        hist_W.Draw('same')
#
#        leg = ROOT.TLegend(0.12, 0.7, 0.85, 0.85)
#        leg.SetLineColor(0)
#        leg.SetFillColor(0)
##        leg.SetTextFont(61)
##        leg.SetTextFont(42)
#        leg.SetTextSize(0.035)
#
#        # data
#        leg.AddEntry(hist_qcd_W, 'Collective est. of QCD and W= {}'.format(round(hist_qcd_W.Integral(),0)), 'ep')
#        leg.AddEntry(hist_W, 'Est. of QCD from data ({})+ W from MC({}) = {}'.format(round(hist_qcd.Integral(),0),round(hist_W_alone.Integral(),0),round(hist_qcd.Integral()+hist_W_alone.Integral(),0)), 'ep')
##        leg.AddEntry(hist_W, 'Estimation of QCD from data ({})+ W from simulation({}) = {} {}'.format(hist_qcd.Integral(),hist_W.Integral(),hist_qcd.Integral()+hist_W.Integral()), 'ep')
#        leg.Draw()
#
#        hist_qcd_W.SetTitle('{}_{}'.format(ch[0],yr))
#        hist_qcd_W.GetXaxis().SetTitle('m_{#tau#tau} [GeV]')
#        c.SaveAs('qcdCompare_{}_{}.pdf'.format(ch[0],yr))
#
#
#
##Output/templates/mt2016_m_sv_fakeComparison_qcd_W.root
##Output/templates/mt2017_m_sv_fakeComparison_qcd_W.root
##Output/templates/mt2018_m_sv_fakeComparison_qcd_W.root
##Output/templates/et2016_m_sv_fakeComparison_qcd_W.root
##Output/templates/et2017_m_sv_fakeComparison_qcd_W.root
##Output/templates/et2018_m_sv_fakeComparison_qcd_W.root
##Output/templates/tt2016_m_sv_fakeComparison_qcd_W.root
##Output/templates/tt2017_m_sv_fakeComparison_qcd_W.root
##Output/templates/tt2018_m_sv_fakeComparison_qcd_W.root
##Output/templates/et2016_m_sv_fakeComparison_qcd.root
##Output/templates/et2017_m_sv_fakeComparison_qcd.root
##Output/templates/et2018_m_sv_fakeComparison_qcd.root
##Output/templates/mt2018_m_sv_fakeComparison_qcd.root
##Output/templates/mt2017_m_sv_fakeComparison_qcd.root
##Output/templates/mt2016_m_sv_fakeComparison_qcd.root
##Output/templates/tt2018_m_sv_fakeComparison_qcd.root
##Output/templates/tt2017_m_sv_fakeComparison_qcd.root
##Output/templates/tt2016_m_sv_fakeComparison_qcd.root
