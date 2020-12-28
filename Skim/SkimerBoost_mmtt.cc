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
using namespace std;


void SkimerBoost::Loop(TString OutputFile)
{
    
    TH1F* hEvents = (TH1F*)gDirectory->Get("ggNtuplizer/hEvents");
    TH1F* hPU     = (TH1F*)gDirectory->Get("ggNtuplizer/hPU");
    TH1F* hPUTrue = (TH1F*)gDirectory->Get("ggNtuplizer/hPUTrue");
    
    TFile* file = TFile::Open(OutputFile, "RECREATE");
    TTree* MyNewTree = fChain->CloneTree(0);
    
    int year=0;
    if (string(file->GetName()).find("2016") != string::npos) year =2016;
    else if (string(file->GetName()).find("2017") != string::npos ) year =2017;
    else if (string(file->GetName()).find("2018") != string::npos) year =2018;
    else (std::cout << "Year is not specificed in the outFile name !\n");
    
    
    fChain->SetBranchStatus("*",1);
    
    TH1F* hcount = new TH1F("hcount", "", 10, 0, 10);
    
    if (fChain == 0) return;
    
    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    float MuMass= 0.10565837;
    float eleMass= 0.000511;
    
    
    
    for (int jentry=0; jentry<nentries;jentry++) {
        
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        
        
        
        if(jentry % 10000 == 0) cout << "Processed " << jentry << " events out of " <<nentries<<endl;
        
        hcount->Fill(1);
        if (!isData)
            hcount->Fill(2,genWeight);
        
        
        TLorentzVector LeadMu4Momentum, SubMu4Momentum, ZBoson4Momentum, LeadTau4Momentum, SubTau4Momentum;
        
        auto numMuMuTauTau(0);
        for (int imu = 0; imu < nMu; ++imu){
            if (muPt->at(imu) < 30 || fabs(muEta->at(imu)) > 2.4) continue;
            if (!(muIDbit->at(imu) >> 0 & 1)) continue;
            LeadMu4Momentum.SetPtEtaPhiM(muPt->at(imu),muEta->at(imu),muPhi->at(imu),MuMass);
            
            for (int jmu = imu+1; jmu < nMu; ++jmu){
                if (muPt->at(jmu) < 10 || fabs(muEta->at(jmu)) > 2.4) continue;
                if (!(muIDbit->at(jmu) >> 0 & 1)) continue;
                SubMu4Momentum.SetPtEtaPhiM(muPt->at(jmu),muEta->at(jmu),muPhi->at(jmu),MuMass);
                
                if(LeadMu4Momentum.DeltaR(SubMu4Momentum) > 0.8 || LeadMu4Momentum.DeltaR(SubMu4Momentum) < 0.1 ) continue;
                ZBoson4Momentum=LeadMu4Momentum+SubMu4Momentum;
                if (ZBoson4Momentum.M() < 60 || ZBoson4Momentum.M() > 120) continue;
                if (muCharge->at(imu) * muCharge->at(jmu) > 0) continue;
                
                for (int ibtau = 0; ibtau < nBoostedTau; ++ibtau){
                    if (boostedTauPt->at(ibtau) < 30 || fabs(boostedTauEta->at(ibtau)) > 2.3 ) continue;
                    if (boostedTaupfTausDiscriminationByDecayModeFindingNewDMs->at(ibtau) < 0.5 ) continue;
                    if (boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(ibtau) < 0) continue;
                    LeadTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(ibtau),boostedTauEta->at(ibtau),boostedTauPhi->at(ibtau),boostedTauMass->at(ibtau));
                    
                    if (LeadTau4Momentum.DeltaR(LeadMu4Momentum) < 0.1 || LeadTau4Momentum.DeltaR(SubMu4Momentum) < 0.1 ) continue;
                    
                    for (int jbtau = ibtau+1; jbtau < nBoostedTau; ++jbtau){
                        if (boostedTauPt->at(jbtau) < 30 || fabs(boostedTauEta->at(jbtau)) > 2.3 ) continue;
                        if (boostedTaupfTausDiscriminationByDecayModeFindingNewDMs->at(jbtau) < 0.5 ) continue;
                        if (boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(jbtau) < 0) continue;
                        SubTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(jbtau),boostedTauEta->at(jbtau),boostedTauPhi->at(jbtau),boostedTauMass->at(jbtau));
                        
                        if(SubTau4Momentum.DeltaR(LeadTau4Momentum) > 0.8 || SubTau4Momentum.DeltaR(LeadTau4Momentum) < 0.1) continue;
                        
                        if (SubTau4Momentum.DeltaR(LeadMu4Momentum) < 0.1 || SubTau4Momentum.DeltaR(SubMu4Momentum) < 0.1 ) continue;
                        
                        numMuMuTauTau++;
                    }
                }
            }
        }
        
        if(numMuMuTauTau < 1) continue;
        hcount->Fill(3);
        
        
        
        MyNewTree->Fill();
    }
    
    
    MyNewTree->AutoSave();
    hEvents->Write();
    hcount->Write();
    hPU->Write();
    hPUTrue->Write();
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



