//###################################################################################################
/*
What does this code is doing?
1) First it counts number of true GenTau, GenMu and GenElectron, and  their neutrinos & save the 4-momenta of each candidates in a vector
2) Find the Rivet weight for each event with njet multiplicity which depends on the generated Higgs pT (also the systematics) [The distributions of pHT and Njets in the gluon fusion production simulation are corrected to match the predictions of the N N L O P S generator]
3) Keep events in case they pass any fiducial cuts for em, et, mt or tt.
4) Two histograms for Higgs pT are stored, one with lumi weight and the other lumiWeight and Rivet and its uncertainty
5)Note: binning matter here


shoud replace the Lead jet pt here with River_j1pt
*/
//###################################################################################################
#define SkimerBoost_cxx
//#include "SkimerBoost.h"
#include "SkimerBoost_Diff.h"
#include "ComputeWG1Unc.h"
#include "event_info.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TLorentzVector.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <TMath.h>
#include <string>
#include <sstream>
//#include "../interface/WeightCalculator.h"
//#include "../interface/Corrector.h"
//#include "../interface/makeHisto.h"

#include "Function_Skim.h"
#include "event_info.h"
using namespace std;


void SkimerBoost::Loop(TString OutputFile,std::string InputFile,std::string Sys)
{
    
    TH1F* hEvents = (TH1F*)gDirectory->Get("ggNtuplizer/hEvents");
    TH1F* hPU     = (TH1F*)gDirectory->Get("ggNtuplizer/hPU");
    TH1F* hPUTrue = (TH1F*)gDirectory->Get("ggNtuplizer/hPUTrue");
    
    TFile *f_NNLOPS = TFile::Open("NNLOPS_reweight.root");
    TGraph *g_NNLOPS_0jet = reinterpret_cast<TGraph *>(f_NNLOPS->Get("gr_NNLOPSratio_pt_powheg_0jet"));
    TGraph *g_NNLOPS_1jet = reinterpret_cast<TGraph *>(f_NNLOPS->Get("gr_NNLOPSratio_pt_powheg_1jet"));
    TGraph *g_NNLOPS_2jet = reinterpret_cast<TGraph *>(f_NNLOPS->Get("gr_NNLOPSratio_pt_powheg_2jet"));
    TGraph *g_NNLOPS_3jet = reinterpret_cast<TGraph *>(f_NNLOPS->Get("gr_NNLOPSratio_pt_powheg_3jet"));
    TGraph *g_NNLOPS_mcatnlo_0jet = reinterpret_cast<TGraph *>(f_NNLOPS->Get("gr_NNLOPSratio_pt_mcatnlo_0jet"));
    TGraph *g_NNLOPS_mcatnlo_1jet = reinterpret_cast<TGraph *>(f_NNLOPS->Get("gr_NNLOPSratio_pt_mcatnlo_1jet"));
    TGraph *g_NNLOPS_mcatnlo_2jet = reinterpret_cast<TGraph *>(f_NNLOPS->Get("gr_NNLOPSratio_pt_mcatnlo_2jet"));
    TGraph *g_NNLOPS_mcatnlo_3jet = reinterpret_cast<TGraph *>(f_NNLOPS->Get("gr_NNLOPSratio_pt_mcatnlo_3jet"));

    
    
    TFile* file = TFile::Open(OutputFile, "RECREATE");
    TTree* BoostTree = fChain->CloneTree(0);
    
    float tauPt_cut= 20;
    
    fChain->SetBranchStatus("*",1);
    
    TH1F* hcount = new TH1F(("hcount"+Sys).c_str(), "", 10, 0, 10);
    
    if (fChain == 0) return;
    
    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    float MuMass= 0.10565837;
    float eleMass= 0.000511;
//    float xbin[5]={0,350,450,600,2000};
    float xbin_hpt[5]={250,350,450,600,2000};
    float xbin_jpt[5]={0,350,450,600,2000};
//    float xbin[6]={0,350,450,600,800,2000};
//    float xbin[6]={0,300,400,550,800,2000};
//    float jetbin[6]={0,300,400,550,800,2000};

    TH1F * higpt=new TH1F(("HiggsPt"+Sys).c_str(),("HiggsPt"+Sys).c_str(),sizeof(xbin_hpt)/sizeof(xbin_hpt[0]) - 1, &xbin_hpt[0]);
    TH1F * higpt_TrigCut=new TH1F(("HiggsPttrg"+Sys).c_str(),("HiggsPttrg"+Sys).c_str(),sizeof(xbin_hpt)/sizeof(xbin_hpt[0]) - 1, &xbin_hpt[0]);
    TH1F * higpt_em=new TH1F(("HiggsPt_em"+Sys).c_str(),("HiggsP_emt"+Sys).c_str(),sizeof(xbin_hpt)/sizeof(xbin_hpt[0]) - 1, &xbin_hpt[0]);
    TH1F * higpt_et=new TH1F(("HiggsPt_et"+Sys).c_str(),("HiggsPt_et"+Sys).c_str(),sizeof(xbin_hpt)/sizeof(xbin_hpt[0]) - 1, &xbin_hpt[0]);
    TH1F * higpt_mt=new TH1F(("HiggsPt_mt"+Sys).c_str(),("HiggsPt_mt"+Sys).c_str(),sizeof(xbin_hpt)/sizeof(xbin_hpt[0]) - 1, &xbin_hpt[0]);
    TH1F * higpt_tt=new TH1F(("HiggsPt_tt"+Sys).c_str(),("HiggsP_tt"+Sys).c_str(),sizeof(xbin_hpt)/sizeof(xbin_hpt[0]) - 1, &xbin_hpt[0]);
    TH1F * higpt_TrigCut_tt=new TH1F(("HiggsPt_trg_tt"+Sys).c_str(),("HiggsP_trg_tt"+Sys).c_str(),sizeof(xbin_hpt)/sizeof(xbin_hpt[0]) - 1, &xbin_hpt[0]);

    TH1F * higpt_nnlops=new TH1F(("HiggsPt_nnlops"+Sys).c_str(),("HiggsPtnn"+Sys).c_str(),sizeof(xbin_hpt)/sizeof(xbin_hpt[0]) - 1, &xbin_hpt[0]);
    TH1F * higpt_nnlops_TrigCut=new TH1F(("HiggsPttrg_nnlops"+Sys).c_str(),("HiggsPtnntrg"+Sys).c_str(),sizeof(xbin_hpt)/sizeof(xbin_hpt[0]) - 1, &xbin_hpt[0]);
    TH1F * higpt_nnlops_em=new TH1F(("HiggsPt_nnlops_em"+Sys).c_str(),("HiggsPnn_emt"+Sys).c_str(),sizeof(xbin_hpt)/sizeof(xbin_hpt[0]) - 1, &xbin_hpt[0]);
    TH1F * higpt_nnlops_et=new TH1F(("HiggsPt_nnlops_et"+Sys).c_str(),("HiggsPtnn_et"+Sys).c_str(),sizeof(xbin_hpt)/sizeof(xbin_hpt[0]) - 1, &xbin_hpt[0]);
    TH1F * higpt_nnlops_mt=new TH1F(("HiggsPt_nnlops_mt"+Sys).c_str(),("HiggsPtnn_mt"+Sys).c_str(),sizeof(xbin_hpt)/sizeof(xbin_hpt[0]) - 1, &xbin_hpt[0]);
    TH1F * higpt_nnlops_tt=new TH1F(("HiggsPt_nnlops_tt"+Sys).c_str(),("HiggsPnn_tt"+Sys).c_str(),sizeof(xbin_hpt)/sizeof(xbin_hpt[0]) - 1, &xbin_hpt[0]);
    TH1F * higpt_nnlops_TrigCut_tt=new TH1F(("HiggsPt_nnlops_trg_tt"+Sys).c_str(),("HiggsPnn_trg_tt"+Sys).c_str(),sizeof(xbin_hpt)/sizeof(xbin_hpt[0]) - 1, &xbin_hpt[0]);

    TH1F * jetpt=new TH1F(("JetPt"+Sys).c_str(),("JetPt"+Sys).c_str(),sizeof(xbin_jpt)/sizeof(xbin_jpt[0]) - 1, &xbin_jpt[0]);
    TH1F * jetpt_TrigCut=new TH1F(("JetPttrg"+Sys).c_str(),("JetPttrg"+Sys).c_str(),sizeof(xbin_jpt)/sizeof(xbin_jpt[0]) - 1, &xbin_jpt[0]);
    TH1F * jetpt_em=new TH1F(("JetPt_em"+Sys).c_str(),("JetP_emt"+Sys).c_str(),sizeof(xbin_hpt)/sizeof(xbin_hpt[0]) - 1, &xbin_hpt[0]);
    TH1F * jetpt_et=new TH1F(("JetPt_et"+Sys).c_str(),("JetPt_et"+Sys).c_str(),sizeof(xbin_hpt)/sizeof(xbin_hpt[0]) - 1, &xbin_hpt[0]);
    TH1F * jetpt_mt=new TH1F(("JetPt_mt"+Sys).c_str(),("JetPt_mt"+Sys).c_str(),sizeof(xbin_hpt)/sizeof(xbin_hpt[0]) - 1, &xbin_hpt[0]);
    TH1F * jetpt_tt=new TH1F(("JetPt_tt"+Sys).c_str(),("JetP_tt"+Sys).c_str(),sizeof(xbin_hpt)/sizeof(xbin_hpt[0]) - 1, &xbin_hpt[0]);
    TH1F * jetpt_TrigCut_tt=new TH1F(("JetPttrg_tt"+Sys).c_str(),("JetPtrg_tt"+Sys).c_str(),sizeof(xbin_hpt)/sizeof(xbin_hpt[0]) - 1, &xbin_hpt[0]);


    TH1F * jetpt_nnlops=new TH1F(("JetPt_nnlops"+Sys).c_str(),("JetPtnn"+Sys).c_str(),sizeof(xbin_jpt)/sizeof(xbin_jpt[0]) - 1, &xbin_jpt[0]);
    TH1F * jetpt_nnlops_TrigCut=new TH1F(("JetPttrg_nnlops"+Sys).c_str(),("JetPtnntrg"+Sys).c_str(),sizeof(xbin_jpt)/sizeof(xbin_jpt[0]) - 1, &xbin_jpt[0]);
    TH1F * jetpt_nnlops_em=new TH1F(("JetPt_nnlops_em"+Sys).c_str(),("JetPnn_emt"+Sys).c_str(),sizeof(xbin_hpt)/sizeof(xbin_hpt[0]) - 1, &xbin_hpt[0]);
    TH1F * jetpt_nnlops_et=new TH1F(("JetPt_nnlops_et"+Sys).c_str(),("JetPtnn_et"+Sys).c_str(),sizeof(xbin_hpt)/sizeof(xbin_hpt[0]) - 1, &xbin_hpt[0]);
    TH1F * jetpt_nnlops_mt=new TH1F(("JetPt_nnlops_mt"+Sys).c_str(),("JetPtnn_mt"+Sys).c_str(),sizeof(xbin_hpt)/sizeof(xbin_hpt[0]) - 1, &xbin_hpt[0]);
    TH1F * jetpt_nnlops_tt=new TH1F(("JetPt_nnlops_tt"+Sys).c_str(),("JetPnn_tt"+Sys).c_str(),sizeof(xbin_hpt)/sizeof(xbin_hpt[0]) - 1, &xbin_hpt[0]);
    TH1F * jetpt_nnlops_TrigCut_tt=new TH1F(("JetPt_nnlopstrg_tt"+Sys).c_str(),("JetPnntrg_tt"+Sys).c_str(),sizeof(xbin_hpt)/sizeof(xbin_hpt[0]) - 1, &xbin_hpt[0]);


    TH1F * TauMul=new TH1F("TauMul","TauMul",5,0,5);
    
    event_info event(Sys);
    
    for (int jentry=0; jentry<nentries;jentry++) {
        
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        
        if (nJet < 1) continue;
        if(jentry % 10000 == 0) cout << "Processed " << jentry << " events out of " <<nentries<<endl;
        
        TLorentzVector Mu4Momentum,Tau4Momentum, Z4Momentum, Met4Momentum,Ele4Momentum;
        TLorentzVector LeadTau4Momentum,SubTau4Momentum;
        
        hcount->Fill(1);
        //=========================================================================================================
        Met4Momentum.SetPtEtaPhiM(genMET, 0, genMETPhi, 0);
        // Lumi weight
        std::string sample       = file->GetName();
        float LumiWeight = XSection_Diff(InputFile)*1.0 / hEvents->GetBinContent(2);
//        float LumiWeight = 1;
        
        //=========================================================================================================
        
//              (ip->pdgId() == 22 && (ip->isPromptFinalState() || ip->isLastCopy())) ||
//      (status == 1 && abs(ip->pdgId()) == 11 && (ip->isPromptFinalState() || ip->isLastCopy())) ||
//      (status == 1 && abs(ip->pdgId()) == 13 && (ip->isPromptFinalState() || ip->isLastCopy())) ||
//      (status == 1 && (abs(ip->pdgId()) == 12 || abs(ip->pdgId()) == 14 || abs(ip->pdgId()) == 16)) ||
//      (status == 1 && ( abs(ip->pdgId()) >= 11 && abs(ip->pdgId()) <= 16 ) && ip->pt() > 3.0)  ||
//      (status < 10 && abs(ip->pdgId()) == 15 && ip->pt() > 3.0);
      
        TLorentzVector genTau,genTau2, genMu, genEle, genNuTau, genNuMu, genNuEle;
        vector<TLorentzVector> genTauVec,genTauVec2, genMuVec, genEleVec, genNuTauVec, genNuEleVec, genNuMuVec;
        
        for (int igen=0;igen < nMC; igen++){
            
            
            if ( fabs(mcPID->at(igen)) ==11 && fabs(mcMomPID->at(igen))==15 && fabs(mcGMomPID->at(igen))==25){
                genEle.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
                genEleVec.push_back(genEle);
            }
            if ( fabs(mcPID->at(igen)) ==12 && fabs(mcMomPID->at(igen))==15 && fabs(mcGMomPID->at(igen))==25){
                genNuEle.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
                genNuEleVec.push_back(genNuEle);
            }
            if ( fabs(mcPID->at(igen)) ==13 && fabs(mcMomPID->at(igen))==15 && fabs(mcGMomPID->at(igen))==25){
                genMu.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
                genMuVec.push_back(genMu);
            }
            if ( fabs(mcPID->at(igen)) ==14 && fabs(mcMomPID->at(igen))==15 && fabs(mcGMomPID->at(igen))==25){
                genNuMu.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
                genNuMuVec.push_back(genNuMu);
            }
            if ( fabs(mcPID->at(igen)) ==15 && fabs(mcMomPID->at(igen))==25){
                genTau.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
                genTauVec.push_back(genTau);
            }
            if ( fabs(mcPID->at(igen)) ==15){
                genTau2.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
                genTauVec2.push_back(genTau2);
            }
            if ( fabs(mcPID->at(igen)) ==16 && fabs(mcMomPID->at(igen))==15){
                genNuTau.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
                genNuTauVec.push_back(genNuTau);
            }
            
        }
        
        TauMul->Fill(genTauVec.size());
        if (genTauVec.size() < 2 ) {
//        std:cout<<"There is no pair of genTau in this event and the size of getTauVector is "<<genTauVec.size()<< "  nu size="<< genNuTauVec.size()<< "  "<< genTauVec2.size() << "\n";
        continue;
        }
        
        
            float weight_Rivet =1;
            float weight_g_NNLOPS = 1;
            NumV WG1unc;
            if (InputFile.find("GluGluHToTauTau") != std::string::npos) { // should be used only for ggH // check this
                if (Rivet_nJets30 == 0)
                    weight_g_NNLOPS = g_NNLOPS_0jet->Eval(std::min(Rivet_higgsPt, static_cast<float>(125.0)));
                if (Rivet_nJets30 == 1)
                    weight_g_NNLOPS = g_NNLOPS_1jet->Eval(std::min(Rivet_higgsPt, static_cast<float>(625.0)));
                if (Rivet_nJets30 == 2)
                    weight_g_NNLOPS = g_NNLOPS_2jet->Eval(std::min(Rivet_higgsPt, static_cast<float>(800.0)));
                if (Rivet_nJets30 >= 3)
                    weight_g_NNLOPS = g_NNLOPS_3jet->Eval(std::min(Rivet_higgsPt, static_cast<float>(925.0)));
                
                WG1unc = qcd_ggF_uncert_2017(Rivet_nJets30, Rivet_higgsPt, Rivet_stage1_cat_pTjet30GeV);
                if (Sys.find("THU_ggH") != std::string::npos) {
                    weight_Rivet= 1 + event.getRivetUnc(WG1unc, Sys);
                }
            }
            
        
        float LeadJetPt= Rivet_j1pt;
        
        //emu
        if (genMuVec.size() ==1  && genEleVec.size() ==1 ) {
                                    
            if (genMuVec[0].DeltaR(genEleVec[0]) > 0.8) continue;
            if (genMuVec[0].DeltaR(genEleVec[0]) < 0.1) continue;
            if (fabs(genMuVec[0].Eta()) > 2.4 || fabs(genEleVec[0].Eta() ) > 2.5) continue;
            bool me_loose = genMuVec[0].Pt() < 52 && genMuVec[0].Pt() > 28 && genEleVec[0].Pt() > 10 && genMET > 30 ;
            bool me_tight = genMuVec[0].Pt() >= 52 && genEleVec[0].Pt() > 10;
            bool em_loose = genEleVec[0].Pt()< 115 && genEleVec[0].Pt()> 38 && genMuVec[0].Pt()  > 10 && genMET > 30 ;
            bool em_tight = genEleVec[0].Pt()>= 115 && genMuVec[0].Pt()  > 10;
            if ( !me_loose && !me_tight && !em_loose && !em_tight ) continue;
            if (Rivet_higgsPt < 250) continue;
            
//            TLorentzVector LeadJet= getLeadJet(genEleVec[0],genMuVec[0], jentry);
            

            higpt->Fill(Rivet_higgsPt,LumiWeight * weight_Rivet);
            higpt_TrigCut->Fill(Rivet_higgsPt,LumiWeight * weight_Rivet);
            higpt_em->Fill(Rivet_higgsPt,LumiWeight * weight_Rivet);
            higpt_nnlops->Fill(Rivet_higgsPt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            higpt_nnlops_TrigCut->Fill(Rivet_higgsPt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            higpt_nnlops_em->Fill(Rivet_higgsPt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            jetpt->Fill(Rivet_j1pt,LumiWeight * weight_Rivet);
            jetpt_TrigCut->Fill(Rivet_j1pt,LumiWeight * weight_Rivet);
            jetpt_em->Fill(Rivet_j1pt,LumiWeight * weight_Rivet);
            jetpt_nnlops->Fill(Rivet_j1pt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            jetpt_nnlops_TrigCut->Fill(Rivet_j1pt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            jetpt_nnlops_em->Fill(Rivet_j1pt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            hcount->Fill(2);
        }
        
        //mutau
        else if (genMuVec.size() ==1 &&  genEleVec.size() ==0 ){
            

            findDr fdMatch0 = FindClosetDr(genTauVec[0],genMuVec);
            findDr fdMatch1 = FindClosetDr(genTauVec[1],genMuVec);
                        
            int tauCandOrder=fdMatch0.dR < fdMatch1.dR ?  1:0;
            
            findDr fdMatchNu = FindClosetDr(genTauVec[tauCandOrder],genNuTauVec);
            TLorentzVector VisibleTau = genTauVec[tauCandOrder] - genNuTauVec[fdMatchNu.order];

            if (genMuVec[0].DeltaR(VisibleTau) > 0.8) continue;
            if (genMuVec[0].DeltaR(VisibleTau) < 0.1) continue;

            if (fabs(genMuVec[0].Eta()) > 2.4 || fabs(VisibleTau.Eta()) > 2.3 ) continue;
            if ( VisibleTau.Pt() < 30 ) continue;
            bool looseMu = genMuVec[0].Pt() > 28 && genMuVec[0].Pt() < 52 && genMET > 30 ;
            bool tightMu = genMuVec[0].Pt() >= 52;
            if (!looseMu && !tightMu) continue;
            if (Rivet_higgsPt < 250) continue;
            
//            TLorentzVector LeadJet= getLeadJet(VisibleTau , genMuVec[0], jentry);
            
            
            higpt->Fill(Rivet_higgsPt,LumiWeight * weight_Rivet);
            higpt_TrigCut->Fill(Rivet_higgsPt,LumiWeight * weight_Rivet);
            higpt_mt->Fill(Rivet_higgsPt,LumiWeight * weight_Rivet);
            higpt_nnlops->Fill(Rivet_higgsPt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            higpt_nnlops_TrigCut->Fill(Rivet_higgsPt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            higpt_nnlops_mt->Fill(Rivet_higgsPt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            jetpt->Fill(Rivet_j1pt,LumiWeight * weight_Rivet);
            jetpt_TrigCut->Fill(Rivet_j1pt,LumiWeight * weight_Rivet);
            jetpt_mt->Fill(Rivet_j1pt,LumiWeight * weight_Rivet);
            jetpt_nnlops->Fill(Rivet_j1pt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            jetpt_nnlops_TrigCut->Fill(Rivet_j1pt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            jetpt_nnlops_mt->Fill(Rivet_j1pt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            hcount->Fill(3);
        }
        
        //etau
        else if (genMuVec.size() ==0 &&  genEleVec.size() ==1 ){
                        
            findDr fdMatch0 = FindClosetDr(genTauVec[0],genEleVec);
            findDr fdMatch1 = FindClosetDr(genTauVec[1],genEleVec);
            
            int tauCandOrder=fdMatch0.dR < fdMatch1.dR ?  1:0;
            
            findDr fdMatchNu = FindClosetDr(genTauVec[tauCandOrder],genNuTauVec);
            TLorentzVector VisibleTau = genTauVec[tauCandOrder] - genNuTauVec[fdMatchNu.order];
            
            if (genEleVec[0].DeltaR(VisibleTau) > 0.8) continue;
            if (genEleVec[0].DeltaR(VisibleTau) < 0.1) continue;

            
            if (fabs(genEleVec[0].Eta()) > 2.5 || fabs(VisibleTau.Eta()) > 2.3 ) continue;
            if ( VisibleTau.Pt() < 30) continue;
            bool looseEle = genEleVec[0].Pt() > 38 && genEleVec[0].Pt() < 115 && genMET > 30 ;
            bool tightEle = genEleVec[0].Pt() >= 115;
            if (!looseEle && !tightEle) continue;
            if (Rivet_higgsPt < 250) continue;
            
//            TLorentzVector LeadJet= getLeadJet(VisibleTau , genEleVec[0], jentry);

            
            higpt->Fill(Rivet_higgsPt,LumiWeight * weight_Rivet);
            higpt_TrigCut->Fill(Rivet_higgsPt,LumiWeight * weight_Rivet);
            higpt_et->Fill(Rivet_higgsPt,LumiWeight * weight_Rivet);
            higpt_nnlops->Fill(Rivet_higgsPt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            higpt_nnlops_TrigCut->Fill(Rivet_higgsPt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            higpt_nnlops_et->Fill(Rivet_higgsPt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            jetpt->Fill(Rivet_j1pt,LumiWeight * weight_Rivet);
            jetpt_TrigCut->Fill(Rivet_j1pt,LumiWeight * weight_Rivet);
            jetpt_et->Fill(Rivet_j1pt,LumiWeight * weight_Rivet);
            jetpt_nnlops->Fill(Rivet_j1pt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            jetpt_nnlops_TrigCut->Fill(Rivet_j1pt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            jetpt_nnlops_et->Fill(Rivet_j1pt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            hcount->Fill(4);
        }
        //tautau
            else if (genMuVec.size() ==0  && genEleVec.size() ==0 ){
            
            findDr fdMatchNu0 = FindClosetDr(genTauVec[0],genNuTauVec);
            findDr fdMatchNu1 = FindClosetDr(genTauVec[1],genNuTauVec);

            TLorentzVector VisibleTau0 = genTauVec[0] - genNuTauVec[fdMatchNu0.order];
            TLorentzVector VisibleTau1 = genTauVec[1] - genNuTauVec[fdMatchNu1.order];

            if (VisibleTau0.DeltaR(VisibleTau1) > 0.8) continue;
            if (VisibleTau0.DeltaR(VisibleTau1) < 0.1) continue;

            if (VisibleTau0.Pt() < 30 || fabs(VisibleTau0.Eta()) > 2.3) continue;
            if (VisibleTau1.Pt() < 30 || fabs(VisibleTau1.Eta()) > 2.3) continue;
            if (Rivet_higgsPt < 250) continue;
            
            
            
            
            

            higpt->Fill(Rivet_higgsPt,LumiWeight * weight_Rivet);
            higpt_tt->Fill(Rivet_higgsPt,LumiWeight * weight_Rivet);
            higpt_nnlops->Fill(Rivet_higgsPt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            higpt_nnlops_tt->Fill(Rivet_higgsPt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            jetpt->Fill(Rivet_j1pt,LumiWeight * weight_Rivet);
            jetpt_tt->Fill(Rivet_j1pt,LumiWeight * weight_Rivet);
            jetpt_nnlops->Fill(Rivet_j1pt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            jetpt_nnlops_tt->Fill(Rivet_j1pt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            hcount->Fill(5);


//            TLorentzVector AK8LeadJet= getLeadJet(VisibleTau0 , VisibleTau1, jentry);
            
            bool tt_ht = false;
//            if (nAK8Jet > 0) tt_ht = (AK8JetGenJetPt->at(0) > 450 && AK8JetMass->at(0)> 30);
            if (nAK8Jet > 0) tt_ht = (AK8JetGenJetPt->at(0) > 450 );
//            bool tt_met = ((year==2016 && genHT > 400 && genMET > 180) || (year>2016 && genHT > 700 && genMET > 120));
            bool tt_met = false;
//            tt_met = ((year==2016 && genHT > 400 && genMET > 180) || (year>2016 && genHT > 700 && genMET > 120));
            tt_met = (genHT > 500 && genMET > 100);
            
            
            if (!tt_ht && !tt_met) continue;



            higpt_TrigCut->Fill(Rivet_higgsPt,LumiWeight * weight_Rivet);
            higpt_TrigCut_tt->Fill(Rivet_higgsPt,LumiWeight * weight_Rivet);
            higpt_nnlops_TrigCut->Fill(Rivet_higgsPt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            higpt_nnlops_TrigCut_tt->Fill(Rivet_higgsPt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            jetpt_TrigCut->Fill(Rivet_j1pt,LumiWeight * weight_Rivet);
            jetpt_TrigCut_tt->Fill(Rivet_j1pt,LumiWeight * weight_Rivet);
            jetpt_nnlops_TrigCut->Fill(Rivet_j1pt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            jetpt_nnlops_TrigCut_tt->Fill(Rivet_j1pt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            hcount->Fill(6);
//            std::cout<<"Channel is tautau: #mu= "<<genMuVec.size() <<"  #ele= "<<genEleVec.size()<<"\n";
        }
    }
    
    
//    BoostTree->AutoSave();
    hEvents->Write();
    hcount->Write();

    higpt->Write();
    higpt_TrigCut->Write();
    higpt_em->Write();
    higpt_et->Write();
    higpt_mt->Write();
    higpt_tt->Write();
    higpt_TrigCut_tt->Write();

    higpt_nnlops->Write();
    higpt_nnlops_TrigCut->Write();
    higpt_nnlops_em->Write();
    higpt_nnlops_et->Write();
    higpt_nnlops_mt->Write();
    higpt_nnlops_tt->Write();
    higpt_nnlops_TrigCut_tt->Write();

    jetpt->Write();
    jetpt_TrigCut->Write();
    jetpt_em->Write();
    jetpt_et->Write();
    jetpt_mt->Write();
    jetpt_tt->Write();
    jetpt_TrigCut_tt->Write();

    jetpt_nnlops->Write();
    jetpt_nnlops_TrigCut->Write();
    jetpt_nnlops_em->Write();
    jetpt_nnlops_et->Write();
    jetpt_nnlops_mt->Write();
    jetpt_nnlops_tt->Write();
    jetpt_nnlops_TrigCut_tt->Write();



    TauMul->Write();

//    if (hPU) hPU->Write();
//    if (hPUTrue) hPUTrue->Write();
    file->Close();
}

int main(int argc, char* argv[]){
    
    string InputFile=argv[1];
    string OutputFile=argv[2];
//    string Sys=argv[3];
    
    cout<< "\n===\n input is "<<InputFile  <<"  and output is "<<OutputFile<<"\n===\n";
    
    
    vector<std::string> AllSys  {"_Nominal","_THU_ggH_Mu","_THU_ggH_Res","_THU_ggH_Mig01","_THU_ggH_Mig12","_THU_ggH_VBF2j","_THU_ggH_VBF3j","_THU_ggH_PT60","_THU_ggH_PT120","_THU_ggH_qmtop"};
    for (auto Sys : AllSys){
        cout<<"Sys is "<<Sys<<"\n";
        SkimerBoost t(InputFile);
        t.Loop("OutDiff_"+Sys+"_"+OutputFile,InputFile,Sys);
        }
    return 0;
}



