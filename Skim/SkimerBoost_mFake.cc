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
    std::cout << "Year is ---> "<< year <<"\n";
    
    
    fChain->SetBranchStatus("*",1);
    
    TH1F* hcount = new TH1F("hcount", "", 10, 0, 10);
    
    if (fChain == 0) return;
    
    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    float MuMass= 0.10565837;
    float eleMass= 0.000511;
    float tauPt_cut= 30;
    
    
    for (int jentry=0; jentry<nentries;jentry++) {
        
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        
        
        
        if(jentry % 10000 == 0) cout << "Processed " << jentry << " events out of " <<nentries<<endl;
        
        hcount->Fill(1);
        if (!isData)
            hcount->Fill(2,genWeight);
        
        
        TLorentzVector LeadMu4Momentum, SubMu4Momentum, ZBoson4Momentum, LeadTau4Momentum;
        
        auto  numMuFake(0);
        for (int imu = 0; imu < nMu; ++imu){
            if (muPt->at(imu) < 28 || fabs(muEta->at(imu)) > 2.4) continue;
//            if (!(muIDbit->at(imu) >> 1 & 1)) continue;
            LeadMu4Momentum.SetPtEtaPhiM(muPt->at(imu),muEta->at(imu),muPhi->at(imu),MuMass);
            
            for (int ibtau = 0; ibtau < nBoostedTau; ++ibtau){
                if (boostedTauPt->at(ibtau) < tauPt_cut || fabs(boostedTauEta->at(ibtau)) > 2.3 ) continue;
                if (boostedTaupfTausDiscriminationByDecayModeFinding->at(ibtau) < 0.5 ) continue;
//                if (boostedTaupfTausDiscriminationByDecayModeFindingNewDMs->at(ibtau) < 0.5 ) continue;
                if (boostedTauByIsolationMVArun2v1DBnewDMwLTrawNew->at(ibtau) < -0.5) continue;
                if (boostedTauByLooseMuonRejection3->at(ibtau) < 0.5 ) continue;
                
                LeadTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(ibtau),boostedTauEta->at(ibtau),boostedTauPhi->at(ibtau),boostedTauMass->at(ibtau));
                
//                if (LeadTau4Momentum.DeltaR(LeadMu4Momentum) < 1.5 ) continue;
                if (LeadTau4Momentum.DeltaR(LeadMu4Momentum) < 0.8 ) continue; // for next round
                
                numMuFake++;
            }
        }
        
        if( numMuFake < 1) continue;
        hcount->Fill(3);
        
        
        
        MyNewTree->Fill();
    }
    
    
    MyNewTree->AutoSave();
    hEvents->Write();
    hcount->Write();
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



