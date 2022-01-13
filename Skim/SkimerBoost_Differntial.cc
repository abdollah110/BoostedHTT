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
    
    TH1F* hcount = new TH1F("hcount", "", 10, 0, 10);
    
    if (fChain == 0) return;
    
    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    float MuMass= 0.10565837;
    float eleMass= 0.000511;
    float xbin[6]={0,350,450,600,800,2000};
//    float xbin[6]={0,300,400,550,800,2000};
//    float jetbin[6]={0,300,400,550,800,2000};
    TH1F * higpt=new TH1F(("HiggsPt"+Sys).c_str(),("HiggsPt"+Sys).c_str(),sizeof(xbin)/sizeof(xbin[0]) - 1, &xbin[0]);
    TH1F * higpt_nnlops=new TH1F(("HiggsPt_nnlops"+Sys).c_str(),("HiggsPt"+Sys).c_str(),sizeof(xbin)/sizeof(xbin[0]) - 1, &xbin[0]);
    TH1F * jetpt=new TH1F(("JetPt"+Sys).c_str(),("JetPt"+Sys).c_str(),sizeof(xbin)/sizeof(xbin[0]) - 1, &xbin[0]);
    TH1F * jetpt_nnlops=new TH1F(("JetPt_nnlops"+Sys).c_str(),("JetPt"+Sys).c_str(),sizeof(xbin)/sizeof(xbin[0]) - 1, &xbin[0]);
    
    event_info event(Sys);
    
    for (int jentry=0; jentry<nentries;jentry++) {
        
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        
        if (nJet < 1) continue;
        if(jentry % 10000 == 0) cout << "Processed " << jentry << " events out of " <<nentries<<endl;
        
        TLorentzVector Mu4Momentum,Tau4Momentum, Z4Momentum, Met4Momentum,Ele4Momentum;
        TLorentzVector LeadTau4Momentum,SubTau4Momentum;
        
        //=========================================================================================================
        Met4Momentum.SetPtEtaPhiM(genMET, 0, genMETPhi, 0);
        // Lumi weight
        std::string sample       = file->GetName();
        float LumiWeight = XSection_Diff(InputFile)*1.0 / hEvents->GetBinContent(2);
//        float LumiWeight = 1;
        
        //=========================================================================================================
        
        TLorentzVector genTau, genMu, genEle, genNuTau, genNuMu, genNuEle;
        vector<TLorentzVector> genTauVec, genMuVec, genEleVec, genNuTauVec, genNuEleVec, genNuMuVec;
        
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
            if ( fabs(mcPID->at(igen)) ==16 && fabs(mcMomPID->at(igen))==15){
                genNuTau.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
                genNuTauVec.push_back(genNuTau);
            }
            
        }
        
        if (genTauVec.size() < 2 ) {
        std:cout<<"There is no pair of genTau in this event and the size of getTauVector is "<<genTauVec.size()<<"\n";
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
            
        
        
        //emu
        if (genMuVec.size() ==1  && genEleVec.size() ==1 ) {
                                    
            if (fabs(genMuVec[0].Eta()) > 2.4 || fabs(genEleVec[0].Eta() ) > 2.5) continue;
            bool me_loose = genMuVec[0].Pt() < 52 && genMuVec[0].Pt() > 28 && genEleVec[0].Pt() > 10 && genMET > 30 ;
            bool me_tight = genMuVec[0].Pt() >= 52 && genEleVec[0].Pt() > 10;
            bool em_loose = genEleVec[0].Pt()< 115 && genEleVec[0].Pt()> 38 && genMuVec[0].Pt()  > 10 && genMET > 30 ;
            bool em_tight = genEleVec[0].Pt()>= 115 && genMuVec[0].Pt()  > 10;
            if ( !me_loose && !me_tight && !em_loose && !em_tight ) continue;
            if (Rivet_higgsPt < 250) continue;
            
            TLorentzVector LeadJet= getLeadJet(genEleVec[0],genMuVec[0], jentry);

            higpt->Fill(Rivet_higgsPt,LumiWeight * weight_Rivet);
            higpt_nnlops->Fill(Rivet_higgsPt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            jetpt->Fill(LeadJet.Pt(),LumiWeight * weight_Rivet);
            jetpt_nnlops->Fill(LeadJet.Pt(),weight_g_NNLOPS* LumiWeight * weight_Rivet);

        }
        
        //mutau
        else if (genMuVec.size() ==1 &&  genEleVec.size() ==0 ){
            
            findDr fdMatch0 = FindClosetDr(genTauVec[0],genMuVec);
            findDr fdMatch1 = FindClosetDr(genTauVec[1],genMuVec);
                        
            int tauCandOrder=fdMatch0.dR < fdMatch1.dR ?  1:0;
            
            findDr fdMatchNu = FindClosetDr(genTauVec[tauCandOrder],genNuTauVec);
            TLorentzVector VisibleTau = genTauVec[tauCandOrder] - genNuTauVec[fdMatchNu.order];
            
            if (fabs(genMuVec[0].Eta()) > 2.4 || fabs(VisibleTau.Eta()) > 2.3 ) continue;
            if ( VisibleTau.Pt() < 30 ) continue;
            bool looseMu = genMuVec[0].Pt() > 28 && genMuVec[0].Pt() < 52 && genMET > 30 ;
            bool tightMu = genMuVec[0].Pt() >= 52;
            if (!looseMu && !tightMu) continue;
            if (Rivet_higgsPt < 250) continue;
            
            TLorentzVector LeadJet= getLeadJet(VisibleTau , genMuVec[0], jentry);
            
            
            higpt->Fill(Rivet_higgsPt,LumiWeight * weight_Rivet);
            higpt_nnlops->Fill(Rivet_higgsPt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            jetpt->Fill(LeadJet.Pt(),LumiWeight * weight_Rivet);
            jetpt_nnlops->Fill(LeadJet.Pt(),weight_g_NNLOPS* LumiWeight * weight_Rivet);
        }
        
        //etau
        else if (genMuVec.size() ==0 &&  genEleVec.size() ==1 ){
                        
            findDr fdMatch0 = FindClosetDr(genTauVec[0],genEleVec);
            findDr fdMatch1 = FindClosetDr(genTauVec[1],genEleVec);
            
            int tauCandOrder=fdMatch0.dR < fdMatch1.dR ?  1:0;
            
            findDr fdMatchNu = FindClosetDr(genTauVec[tauCandOrder],genNuTauVec);
            TLorentzVector VisibleTau = genTauVec[tauCandOrder] - genNuTauVec[fdMatchNu.order];
            
            
            if (fabs(genEleVec[0].Eta()) > 2.5 || fabs(VisibleTau.Eta()) > 2.3 ) continue;
            if ( VisibleTau.Pt() < 30) continue;
            bool looseEle = genEleVec[0].Pt() > 38 && genEleVec[0].Pt() < 115 && genMET > 30 ;
            bool tightEle = genEleVec[0].Pt() >= 115;
            if (!looseEle && !tightEle) continue;
            if (Rivet_higgsPt < 250) continue;
            
            TLorentzVector LeadJet= getLeadJet(VisibleTau , genEleVec[0], jentry);

            
            higpt->Fill(Rivet_higgsPt,LumiWeight * weight_Rivet);
            higpt_nnlops->Fill(Rivet_higgsPt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            jetpt->Fill(LeadJet.Pt(),LumiWeight * weight_Rivet);
            jetpt_nnlops->Fill(LeadJet.Pt(),weight_g_NNLOPS* LumiWeight * weight_Rivet);
            
        }
        else
        {
        

            
            findDr fdMatchNu0 = FindClosetDr(genTauVec[0],genNuTauVec);
            findDr fdMatchNu1 = FindClosetDr(genTauVec[1],genNuTauVec);

            TLorentzVector VisibleTau0 = genTauVec[0] - genNuTauVec[fdMatchNu0.order];
            TLorentzVector VisibleTau1 = genTauVec[1] - genNuTauVec[fdMatchNu1.order];

            if (VisibleTau0.Pt() < 30 || fabs(VisibleTau0.Eta()) > 2.3) continue;
            if (VisibleTau1.Pt() < 30 || fabs(VisibleTau1.Eta()) > 2.3) continue;
            if (Rivet_higgsPt < 250) continue;
            
            
            TLorentzVector AK8LeadJet= getLeadJet(VisibleTau0 , VisibleTau1, jentry);
            
            bool tt_ht = AK8LeadJet.Pt() > 100 ;
            bool tt_met = genHT > 500 && genMET > 120;
            
            if (!tt_ht && !tt_met) continue;
            
            TLorentzVector LeadJet= getLeadJet(VisibleTau0 , VisibleTau1, jentry);
            
            higpt->Fill(Rivet_higgsPt,LumiWeight * weight_Rivet);
            higpt_nnlops->Fill(Rivet_higgsPt,weight_g_NNLOPS* LumiWeight * weight_Rivet);
            jetpt->Fill(LeadJet.Pt(),LumiWeight * weight_Rivet);
            jetpt_nnlops->Fill(LeadJet.Pt(),weight_g_NNLOPS* LumiWeight * weight_Rivet);
            
            std::cout<<"Channel is tautau: #mu= "<<genMuVec.size() <<"  #ele= "<<genEleVec.size()<<"\n";
        }
    }
    
    
//    BoostTree->AutoSave();
    hEvents->Write();
    hcount->Write();
    higpt->Write();
    higpt_nnlops->Write();
    jetpt->Write();
    jetpt_nnlops->Write();

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



