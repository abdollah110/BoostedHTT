from ROOT import *

Type_2D=['ht','met']
Type_1D=['SDMass','AK8Pt','PFMET','PFHT']
Year = ['2016','2017','2018']

for year in Year:

    inputFile=TFile('TriggerEff_{}.root'.format(year),'r')
    
    for type_2D in Type_2D:
        
        RBX_=1
        RBY_=1
        if type_2D=='met':RBX_=2 ; RBY_=2
        numHist=inputFile.Get('{}_trgEff_2D_After'.format(type_2D))
        denumHist=inputFile.Get('{}_trgEff_2D_Before'.format(type_2D))
        numHistRB=numHist.RebinY(RBY_).RebinX(RBX_)
        denumHistRB=denumHist.RebinY(RBY_).RebinX(RBX_)
        #numHistRB=numHist.RebinX(2)
        #denumHistRB=denumHist.RebinY(2)
        #numHistRB.GetXaxis().SetRangeUser(0,1200)
        numHistRB.Divide(denumHistRB)
        can=TCanvas()
        #gStyle.SetPaintTextFormat('g');
        gStyle.SetPaintTextFormat('0.1f ')
        gStyle.SetTextSize(0.01);
        gStyle.SetOptStat(0)
        numHistRB.Draw("textcolz")
        can.SaveAs('{}_trgEff_2D_{}.pdf'.format(type_2D,year))
        outFile=TFile('{}_trgEff_2D_{}.root'.format(type_2D,year),'RECREATE')
        outH=numHistRB.Clone()
        outH.SetName('TrgEfficiency2D')
        outH.Write()
        outFile.Close()

    
    for type_1D in Type_1D:

        numHist_1D=inputFile.Get('{}_trgEff_1D_After'.format(type_1D))
        denumHist_1D=inputFile.Get('{}_trgEff_1D_Before'.format(type_1D))
        can2=TCanvas()
        gStyle.SetOptStat(0)
        numHist_1D.Divide(denumHist_1D)
        numHist_1D.GetYaxis().SetRangeUser(0,1)
        numHist_1D.Draw()
        can2.SaveAs('{}_trgEff_1D_{}.pdf'.format(type_1D,year))

