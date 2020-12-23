import ROOT
from ROOT import *

class plot:

    def __init__(self,input,HistName,XaxisName,OutName='out.pdf'):
        self.input = input
        self.HistName=HistName
        self.XaxisName=XaxisName
        self.OutName=OutName


    def get_TProfile(self):
        """ return the TProfille of the TH2 histogram """
        
        file=TFile(self.input)
        hist=file.Get(self.HistName)
        histTprof=hist.ProfileX()
    
        c=TCanvas()
        ROOT.gStyle.SetOptStat(0)
    
        histTprof.Draw()
        histTprof.SetTitle('')
        histTprof.SetMarkerSize(1)
        histTprof.SetMarkerStyle(20)
        histTprof.GetXaxis().SetTitle('dR_{#tau#tau}')
        histTprof.GetYaxis().SetTitle(self.XaxisName)
        histTprof.GetYaxis().SetRangeUser(-.05,1.05)
        c.SaveAs(self.OutName)
    
        
        
