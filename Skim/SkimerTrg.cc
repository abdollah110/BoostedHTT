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


void SkimerBoost::Loop(TString outputName, int skm)
{
    
    

    TH1F* hEvents = (TH1F*)gDirectory->Get("ggNtuplizer/hEvents");
    TH1F* hPU     = (TH1F*)gDirectory->Get("ggNtuplizer/hPU");
    TH1F* hPUTrue = (TH1F*)gDirectory->Get("ggNtuplizer/hPUTrue");
    
    TFile* file = TFile::Open(outputName, "RECREATE");
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
    fChain->SetBranchStatus("c*",1);
    fChain->SetBranchStatus("jet*",1);
    fChain->SetBranchStatus("AK8*",1);
    fChain->SetBranchStatus("ele*",1);
    fChain->SetBranchStatus("mu*",1);
//    fChain->SetBranchStatus("pho",0);
    fChain->SetBranchStatus("tau*",1);
    fChain->SetBranchStatus("m*",1);
    fChain->SetBranchStatus("b*",1);
    
    TH1F* hcount = new TH1F("hcount", "", 10, 0, 10);
    
    if (fChain == 0) return;
    
    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    
    
    
    
    for (int jentry=0; jentry<nentries;jentry++) {
        
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        
        
        
        if(jentry % 10000 == 0) cout << "Processed " << jentry << " events out of " <<nentries<<endl;
        hcount->Fill(1);
        hcount->Fill(2,genWeight);
        
        
        auto numMu(0);
        for (int imu = 0; imu < nMu; ++imu){
            if (muPt->at(imu) > 50){
                numMu++;
            }
        }
        if  (!numMu) continue;
        hcount->Fill(3);
        
        if(pfMET < 50) continue;
        hcount->Fill(4);
        
        
        auto BoostedTau(0);
        auto BoostedIsoTau(0);
        TLorentzVector BoostedTau4Momentum, Jet4Momentum;
        for (int ijet = 0; ijet < nJet; ++ijet){
            if (jetPt->at(ijet) > 200 &&  fabs(jetEta->at(ijet)) < 3.0 ){
                Jet4Momentum.SetPtEtaPhiM(jetPt->at(ijet),jetEta->at(ijet),jetPhi->at(ijet),jetEn->at(ijet));
                for (int ibtau = 0; ibtau < nBoostedTau; ++ibtau){
                    if (boostedTauPt->at(ibtau) > 30 && fabs(boostedTauEta->at(ibtau)) < 2.5  ){
                        BoostedTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(ibtau),boostedTauEta->at(ibtau),boostedTauPhi->at(ibtau),boostedTauMass->at(ibtau));
                        if(BoostedTau4Momentum.DeltaR(Jet4Momentum) > 0.5){
                            BoostedTau++;
                            if (1){
                                BoostedIsoTau++;
                            }
                        }
                    }
                }
            }
        }
        
        if(BoostedTau < 2) continue;
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
    
    string FinaName=argv[1];
    stringstream ss(FinaName);
    
    string token;
    string M;
    int count=0;
    string realName;
    while (getline(ss,token, '/'))
    {
        count++;
        cout<< token <<endl;
        if (count == 5) {
            cout<<"   ----->    5   "<<token<<"  _____   \n";
            realName=token;
        }
        M=token;
    }
    
    TString outputName = "skimed_"+realName+M;
    cout<<" outputName is ---> "<<outputName<<"\n";
    cout<<" FinaName is ---> "<<FinaName<<"\n";
    
//    SkimerBoost t("root://cmsxrootd.fnal.gov//store/user/abdollah/BoostedH/An2017/"+FinaName);
    SkimerBoost t("root://cmsxrootd.fnal.gov//store/user/tmitchel/BoostedH/An2017/"+FinaName);
    //FinaName.erase(FinaName.begin(),FinaName.end()-10);
    //  SkimerBoost t("root://cmsxrootd.fnal.gov//"+FinaName);
    t.Loop(outputName, 0);
    return 0;
}




