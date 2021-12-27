from ROOT import *

#inputFile=TFile('allSingleMuD_Plus.root','r')
#inputFile=TFile('SingleMuon_Run2018_Trg_v4.root','r')


#
#            //Filling 2D eff plot
#            plotFill("ht_trgEff_2D_Before",AK8JetPt->at(ijet),AK8JetSoftDropMass->at(ijet),50,0,2000,30,0,300);
#            if (HLT_AK8PFJet360_TrimMass30){
#                plotFill("ht_trgEff_2D_After",AK8JetPt->at(ijet),AK8JetSoftDropMass->at(ijet) ,50,0,2000,30,0,300);
#            }
#
#            //Filling 1D eff plot
#            if (AK8JetPt->at(ijet) > 450  && AK8JetSoftDropMass->at(ijet) > 0 && fabs(AK8JetEta->at(ijet)) < 2.5)
#                plotFill("ht_trgEff_1D_Before",AK8JetSoftDropMass->at(ijet),30,0,300);
#            if (AK8JetPt->at(ijet) > 450  && AK8JetSoftDropMass->at(ijet) > 0 && fabs(AK8JetEta->at(ijet)) < 2.5 && HLT_AK8PFJet360_TrimMass30)
#                plotFill("ht_trgEff_1D_After",AK8JetSoftDropMass->at(ijet),30,0,300);
#
#        }
#
#
#        //Filling 2D eff plot
#        plotFill("met_trgEff_2D_Before",PFHT,PFMET,60,0,3000,50,0,1000);
#        if (HLT_PFHT300_PFMET110){
#            plotFill("met_trgEff_2D_After",PFHT,PFMET,60,0,3000,50,0,1000);
#        }
#
#        //Filling 1D eff plot
#        if (PFHT > 400 )
#            plotFill("met_trgEff_1D_Before",PFMET,50,0,1000);
#        if (PFHT > 400  && HLT_PFHT300_PFMET110)
#            plotFill("met_trgEff_1D_After",PFMET,50,0,1000);
#
#
#

#
#
#            //Filling 2D eff plot
#            plotFill("ht_trgEff_2D_Before",AK8JetPt->at(ijet),AK8JetSoftDropMass->at(ijet),40,0,2000,60,0,300);
#            if (HLT_AK8PFJet400_TrimMass30){
#                plotFill("ht_trgEff_2D_After",AK8JetPt->at(ijet),AK8JetSoftDropMass->at(ijet) ,40,0,2000,60,0,300);
#            }
#
#            //Filling 1D eff plot SDMass efficiency
#            if (AK8JetPt->at(ijet) > 450  && AK8JetSoftDropMass->at(ijet) > 0 && fabs(AK8JetEta->at(ijet)) < 2.5)
#                plotFill("SDMass_trgEff_1D_Before",AK8JetSoftDropMass->at(ijet),60,0,300);
#            if (AK8JetPt->at(ijet) > 450  && AK8JetSoftDropMass->at(ijet) > 0 && fabs(AK8JetEta->at(ijet)) < 2.5 && HLT_AK8PFJet400_TrimMass30)
#                plotFill("SDMass_trgEff_1D_After",AK8JetSoftDropMass->at(ijet),60,0,300);
#
#            //Filling 1D eff plot AK8Pt efficiency
#            if (AK8JetPt->at(ijet) > 200  && AK8JetSoftDropMass->at(ijet) > 30 && fabs(AK8JetEta->at(ijet)) < 2.5)
#                plotFill("AK8Pt_trgEff_1D_Before",AK8JetPt->at(ijet),40,0,2000);
#            if (AK8JetPt->at(ijet) > 200  && AK8JetSoftDropMass->at(ijet) > 30 && fabs(AK8JetEta->at(ijet)) < 2.5 && HLT_AK8PFJet400_TrimMass30)
#                plotFill("AK8Pt_trgEff_1D_After",AK8JetPt->at(ijet),40,0,2000);
#
#
#        }
#
#
#        //Filling 2D eff plot
#        plotFill("met_trgEff_2D_Before",PFHT,PFMET+MHT,60,0,3000,100,0,2000);
#        if (HLT_PFHT500_PFMET100_PFMHT100_IDTight){
#            plotFill("met_trgEff_2D_After",PFHT,PFMET+MHT,60,0,3000,100,0,2000);
#        }
#
#        //Filling 1D eff plot
#        if (PFHT > 600 )
#            plotFill("PFMET_trgEff_1D_Before",PFMET+MHT,100,0,2000);
#        if (PFHT > 600  && HLT_PFHT500_PFMET100_PFMHT100_IDTight)
#            plotFill("PFMET_trgEff_1D_After",PFMET+MHT,100,0,2000);
#
#
#        //Filling 1D eff plot
#        if (PFMET+MHT > 250 )
#            plotFill("PFHT_trgEff_1D_Before",PFMET+MHT,100,0,2000);
#        if (PFMET+MHT > 250  && HLT_PFHT500_PFMET100_PFMHT100_IDTight)
#            plotFill("PFHT_trgEff_1D_After",PFMET+MHT,100,0,2000);
#




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

