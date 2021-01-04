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
    //    fChain->SetBranchStatus("*",0);
    //    fChain->SetBranchStatus("vt*",1);
    //    fChain->SetBranchStatus("EventTag",1);
    //    fChain->SetBranchStatus("run",1);
    //    fChain->SetBranchStatus("event",1);
    //    fChain->SetBranchStatus("lumis",1);
    //    fChain->SetBranchStatus("isData",1);
    //    fChain->SetBranchStatus("HLT*",1);
    //    fChain->SetBranchStatus("gen*",1);
    //    fChain->SetBranchStatus("pdf*",1);
    //    fChain->SetBranchStatus("pthat",1);
    //    fChain->SetBranchStatus("processID",1);
    //    fChain->SetBranchStatus("rho*",1);
    //    fChain->SetBranchStatus("pu*",1);
    //    fChain->SetBranchStatus("mc*",1);
    //    fChain->SetBranchStatus("pfMET*",1);
    //    fChain->SetBranchStatus("n*",1);
    //    //    fChain->SetBranchStatus("c*",1);
    //    fChain->SetBranchStatus("jet*",1);
    //    fChain->SetBranchStatus("AK8*",1);
    //    fChain->SetBranchStatus("ele*",1);
    //    fChain->SetBranchStatus("mu*",1);
    //    fChain->SetBranchStatus("tau*",1);
    //    fChain->SetBranchStatus("m*",1);
    //    fChain->SetBranchStatus("b*",1);
    
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
        
        
        TLorentzVector LeadMu4Momentum, SubMu4Momentum;
        
        auto numMuAK8Jet(0);
        for (int imu = 0; imu < nMu; ++imu){
            if (muPt->at(imu) < 50 || fabs(muEta->at(imu)) > 2.4) continue;
            
            LeadMu4Momentum.SetPtEtaPhiM(muPt->at(imu),muEta->at(imu),muPhi->at(imu),MuMass);
            
            
            for (int ijet=0; ijet < nAK8Jet ; ijet ++){
                
                if (AK8JetPt->at(ijet) < 150 || fabs(AK8JetEta->at(ijet)) > 3.0 ) continue;
                                    
                for (int j = 0; j < AK8puppiSDSJMass->at(ijet).size(); j++){
                    
                    if (AK8puppiSDSJMass->at(ijet).at(j) > 20){
                    numMuAK8Jet++;
                    }
                }
                
            }
        }
        
        if(numMuAK8Jet < 1) continue;
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


