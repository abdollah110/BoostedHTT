#define SkimerBoost_cxx
#include "SkimerBoost.h"
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

#include "../interface/Functions.h"
using namespace std;


void SkimerBoost::Loop(TString OutputFile)
{
    
    TH1F* hEvents = (TH1F*)gDirectory->Get("ggNtuplizer/hEvents");
    TH1F* hPU     = (TH1F*)gDirectory->Get("ggNtuplizer/hPU");
    TH1F* hPUTrue = (TH1F*)gDirectory->Get("ggNtuplizer/hPUTrue");
    
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
    float xbin[5]={0,350,450,600,2000};
    TH1F * higpt=new TH1F("hig","hig",sizeof(xbin)/sizeof(xbin[0]) - 1, &xbin[0]);
    
    
    for (int jentry=0; jentry<nentries;jentry++) {
        
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        
        if(jentry % 10000 == 0) cout << "Processed " << jentry << " events out of " <<nentries<<endl;
        
        TLorentzVector Mu4Momentum,Tau4Momentum, Z4Momentum, Met4Momentum,Ele4Momentum;
        TLorentzVector LeadTau4Momentum,SubTau4Momentum;
        
        //=========================================================================================================
        Met4Momentum.SetPtEtaPhiM(genMET, 0, genMETPhi, 0);
        // Lumi weight
        std::string sample       = file->GetName();
        float LumiWeight = XSection(sample)*1.0 / hEvents->GetBinContent(2);
        
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
        
        if (genTauVec.size() < 2 ) continue;
        
        cout<<genTauVec<<" "<<genMuVec<<" "<<genEleVec<<"\t";
        cout<<genNuTauVec<<" "<<genNuMuVec<<" "<<genNuEleVec<<"\n";
        
        
        //emu
        if (genMuVec.size() > 0 && genEleVec.size() > 0 ) {
            
            cout<<"entering emu\n";
            if (genMuVec[0].Pt() < 10 || fabs(genMuVec[0].Eta()) > 2.4) continue;
            if (genEleVec[0].Pt() < 10 || fabs(genEleVec[0].Eta() ) > 2.5) continue;
            
            TLorentzVector higgs = genEleVec[0]+genMuVec[0] +Met4Momentum;
            TLorentzVector LeadJet= getLeadJet(genEleVec[0],genMuVec[0]);
            if (higgs.Pt() < 280) continue;
            higpt->Fill(higgs.Pt(),LumiWeight);
        }
        
        //mutau
        else if (genMuVec.size() > 0 &&  genEleVec.size() < 1 ){
            cout<<"entering mutau\n";
            findDr fdMatch0 = FindClosetDr(genTauVec[0],genMuVec);
            findDr fdMatch1 = FindClosetDr(genTauVec[1],genMuVec);
                        
            int tauCandOrder=fdMatch0.dR < fdMatch1.dR ?  1:0;
            
            findDr fdMatchNu = FindClosetDr(genTauVec[tauCandOrder],genNuTauVec);
            TLorentzVector VisibleTau = genTauVec[tauCandOrder] - genNuTauVec[fdMatchNu.order];
            float visibleTauCandPt = VisibleTau.Pt();
            
            if (genMuVec[0].Pt() < 30 || fabs(genMuVec[0].Eta()) > 2.4) continue;
            if ( VisibleTau.Pt() < 30 || fabs(VisibleTau.Eta()) > 2.4) continue;
            
            TLorentzVector higgs = VisibleTau+genMuVec[0] +Met4Momentum;
            TLorentzVector LeadJet= getLeadJet(VisibleTau , genMuVec[0]);
            if (higgs.Pt() < 280) continue;
            higpt->Fill(higgs.Pt(),LumiWeight);
        }
        
        //etau
        else if (genMuVec.size() < 1 &&  genEleVec.size() > 0 ){
            
            cout<<"entering etau\n";
            findDr fdMatch0 = FindClosetDr(genTauVec[0],genEleVec);
            findDr fdMatch1 = FindClosetDr(genTauVec[1],genEleVec);
            
            int tauCandOrder=fdMatch0.dR < fdMatch1.dR ?  1:0;
            
            findDr fdMatchNu = FindClosetDr(genTauVec[tauCandOrder],genNuTauVec);
            TLorentzVector VisibleTau = genTauVec[tauCandOrder] - genNuTauVec[fdMatchNu.order];
            float visibleTauCandPt = VisibleTau.Pt();
            
            if (genEleVec[0].Pt() < 30 || fabs(genEleVec[0].Eta() ) > 2.5) continue;
            if ( VisibleTau.Pt() < 30 || fabs(VisibleTau.Eta() )> 2.5) continue;
            
            TLorentzVector higgs = VisibleTau+genEleVec[0] +Met4Momentum;
            TLorentzVector LeadJet= getLeadJet(VisibleTau , genEleVec[0]);
            if (higgs.Pt() < 280) continue;
            higpt->Fill(higgs.Pt(),LumiWeight);
            
        }
        else
        {
        cout<<"entering tautau\n";
            findDr fdMatchNu0 = FindClosetDr(genTauVec[0],genNuTauVec);
            findDr fdMatchNu1 = FindClosetDr(genTauVec[1],genNuTauVec);
            
            TLorentzVector VisibleTau0 = genTauVec[0] - genNuTauVec[fdMatchNu0.order];
            TLorentzVector VisibleTau1 = genTauVec[1] - genNuTauVec[fdMatchNu1.order];
            
            if (VisibleTau0.Pt() < 30 || fabs(VisibleTau0.Eta()) > 2.3) continue;
            if (VisibleTau1.Pt() < 30 || fabs(VisibleTau1.Eta()) > 2.3) continue;
            
            //    cout<< VisibleTau0.Pt()<< " " << VisibleTau1.Pt() <<"  \t " << boostedTauPt->at(leadtauIndex) << "  " <<boostedTauPt->at(subtauIndex)<<"\n";
            //    cout<< VisibleTau0.Eta()<< " " << VisibleTau1.Eta() <<"  \t " << boostedTauEta->at(leadtauIndex) << "  " <<boostedTauEta->at(subtauIndex)<<"\n\n";
            
            TLorentzVector higgs = VisibleTau0+VisibleTau1 +Met4Momentum;
            TLorentzVector LeadJet= getLeadJet(VisibleTau0 , VisibleTau1);
            if (higgs.Pt() < 280) continue;
            higpt->Fill(higgs.Pt(),LumiWeight);
            
        }
    }
    
    
    BoostTree->AutoSave();
    hEvents->Write();
    hcount->Write();
    higpt->Write();
    if (hPU) hPU->Write();
    if (hPUTrue) hPUTrue->Write();
    file->Close();
}

int main(int argc, char* argv[]){
    
    string InputFile=argv[1];
    string OutputFile=argv[2];
    
    cout<< "\n===\n input is "<<InputFile  <<"  and output is "<<OutputFile<<"\n===\n";
    
    SkimerBoost t(InputFile);
    t.Loop(OutputFile);
    return 0;
}



