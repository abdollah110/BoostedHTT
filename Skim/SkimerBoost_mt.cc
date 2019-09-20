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


void SkimerBoost::Loop(TString OutputFile, int skm)
{
    
    
    
    TH1F* hEvents = (TH1F*)gDirectory->Get("ggNtuplizer/hEvents");
    TH1F* hPU     = (TH1F*)gDirectory->Get("ggNtuplizer/hPU");
    TH1F* hPUTrue = (TH1F*)gDirectory->Get("ggNtuplizer/hPUTrue");
    
    TFile* file = TFile::Open(OutputFile, "RECREATE");
    TTree* MyNewTree = fChain->CloneTree(0);
    
    fChain->SetBranchStatus("*",0);
    //    fChain->SetBranchStatus("hasGoodVtx",1);
    fChain->SetBranchStatus("vt*",1);
    fChain->SetBranchStatus("EventTag",1);
    fChain->SetBranchStatus("run",1);
    fChain->SetBranchStatus("event",1);
    fChain->SetBranchStatus("lumis",1);
    fChain->SetBranchStatus("isData",1);
    fChain->SetBranchStatus("HLT*",1);
    fChain->SetBranchStatus("gen*",1);
    fChain->SetBranchStatus("pdf*",1);
    fChain->SetBranchStatus("pthat",1);
    fChain->SetBranchStatus("processID",1);
    fChain->SetBranchStatus("rho*",1);
    fChain->SetBranchStatus("pu*",1);
    fChain->SetBranchStatus("mc*",1);
    fChain->SetBranchStatus("pfMET*",1);
    fChain->SetBranchStatus("n*",1);
    //    fChain->SetBranchStatus("c*",1);
    fChain->SetBranchStatus("jet*",1);
        fChain->SetBranchStatus("AK8*",1);
    fChain->SetBranchStatus("ele*",1);
    fChain->SetBranchStatus("mu*",1);
    //    fChain->SetBranchStatus("pho",0);
    fChain->SetBranchStatus("tau*",1);
    fChain->SetBranchStatus("m*",1);
    fChain->SetBranchStatus("b*",1);
    
    TH1F* hcount = new TH1F("hcount", "", 5, 1, 5);
    
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
        hcount->Fill(2,genWeight);
        
        if (pfMET < 75) continue;
        hcount->Fill(3);
        
        TLorentzVector BoostedTau4Momentum, Mu4Momentum;
        
        auto numMuTau(0);
        for (int imu = 0; imu < nMu; ++imu){
            if (muPt->at(imu) > 30 && fabs(muEta->at(imu)) < 2.4){
                
                Mu4Momentum.SetPtEtaPhiM(muPt->at(imu),muEta->at(imu),muPhi->at(imu),MuMass);
                
                for (int ibtau = 0; ibtau < nBoostedTau; ++ibtau){
                    if (boostedTauPt->at(ibtau) > 20 && fabs(boostedTauEta->at(ibtau)) < 2.3 ){
                        BoostedTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(ibtau),boostedTauEta->at(ibtau),boostedTauPhi->at(ibtau),boostedTauMass->at(ibtau));
                        if(BoostedTau4Momentum.DeltaR(Mu4Momentum) < 0.8 && BoostedTau4Momentum.DeltaR(Mu4Momentum) > 0.4){
                            numMuTau++;
                        }
                    }
                }
            }
        }
        
        if(numMuTau < 1) continue;
        hcount->Fill(4);
        
        float MT =TMass_F(Mu4Momentum.Pt(),Mu4Momentum.Px(),Mu4Momentum.Py(),pfMET,pfMETPhi);
        if(MT > 40) continue;
        hcount->Fill(5);
        
        
        
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
    
    SkimerBoost t("root://cmsxrootd.fnal.gov/"+InputFile);
    t.Loop(OutputFile, 0);

    return 0;
}



