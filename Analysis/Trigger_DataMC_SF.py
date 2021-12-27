from ROOT import *

Type_2D=['ht','met']
Year = ['2016','2017','2018']

for year in Year:
    for type_2D in Type_2D:
    
        inputFile_data=TFile('data/{}_trgEff_2D_{}.root'.format(type_2D,year),'r')
        inputFile_mc=TFile('data/{}_trgEff_2D_{}_mc.root'.format(type_2D,year),'r')
        
        RBX_=1
        RBY_=1
        if type_2D=='met':RBX_=2 ; RBY_=2
        numHist=inputFile_data.Get('TrgEfficiency2D')
        denumHist=inputFile_mc.Get('TrgEfficiency2D')
        numHistRB=numHist.RebinY(RBY_).RebinX(RBX_)
        denumHistRB=denumHist.RebinY(RBY_).RebinX(RBX_)
        #numHistRB=numHist.RebinX(2)
        #denumHistRB=denumHist.RebinY(2)
        #numHistRB.GetXaxis().SetRangeUser(0,1200)
        numHistRB.Divide(denumHistRB)
        
        
        for ibin in range(numHistRB.GetXaxis().GetNbins()):
            for jbin in range(numHistRB.GetYaxis().GetNbins()):
                if numHistRB.GetBinContent(ibin+1,jbin+1) > 1.5:
                   numHistRB.SetBinContent(ibin+1,jbin+1,1.5)
        
        can=TCanvas()
        #gStyle.SetPaintTextFormat('g');
        gStyle.SetPaintTextFormat('0.1f ')
        gStyle.SetTextSize(0.01);
        gStyle.SetOptStat(0)
        numHistRB.Draw("textcolz")
        can.SaveAs('sf_{}_trgEff_2D_{}.pdf'.format(type_2D,year))
        outFile=TFile('sf_{}_trgEff_2D_{}.root'.format(type_2D,year),'RECREATE')
        outH=numHistRB.Clone()
        outH.SetName('TrgEfficiency2D')
        outH.Write()
        outFile.Close()
