//# For the next round   add PU information


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
    TTree* BoostTree = fChain->CloneTree(0);
    
    fChain->SetBranchStatus("*",0);
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
    fChain->SetBranchStatus("tau*",1);
    fChain->SetBranchStatus("m*",1);
    fChain->SetBranchStatus("b*",1);
    
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
        
        if (pfMET < 50) continue;
        hcount->Fill(3);
        
        TLorentzVector BoostTau4Mom, Mu4Mom;
        int decayMode2 = 1;
        float MT = 0;
        auto numMuTau(0);
        int muIndex = -1;
        int tauIndex= -1;

        for (int imu = 0; imu < nMu; ++imu){
            if (muPt->at(imu) < 50 || fabs(muEta->at(imu)) > 2.4) continue;
            
            
//            bool MuId=( muIDbit->at(imu) >> 2 & 1); //(iMu->passed(reco::Muon::CutBasedIdMediumPrompt)) tmpmuIDbit += pow(2,  2);
            
//            if (!MuId) continue;
                            
            Mu4Mom.SetPtEtaPhiM(muPt->at(imu),muEta->at(imu),muPhi->at(imu),MuMass);
            
            MT =TMass_F(Mu4Mom.Pt(),Mu4Mom.Px(),Mu4Mom.Py(),pfMET,pfMETPhi);
            if(MT > 80) continue;
            
            
            for (int ibtau = 0; ibtau < nBoostedTau; ++ibtau){
            
                if (boostedTauPt->at(ibtau) < 40 || fabs(boostedTauEta->at(ibtau)) > 2.3 ) continue;
                if (boostedTaupfTausDiscriminationByDecayModeFinding->at(ibtau) < 0.5 ) continue;
                if (boostedTauByMVA6VLooseElectronRejection->at(ibtau) < 0.5) continue;
                if (boostedTauByTightMuonRejection3->at(ibtau) < 0.5) continue;
                if (boostedTauByVLooseIsolationMVArun2v1DBoldDMwLT->at(ibtau) < 0.5) continue;

                BoostTau4Mom.SetPtEtaPhiM(boostedTauPt->at(ibtau),boostedTauEta->at(ibtau),boostedTauPhi->at(ibtau),boostedTauMass->at(ibtau));
                
                if(BoostTau4Mom.DeltaR(Mu4Mom) > 0.8 || BoostTau4Mom.DeltaR(Mu4Mom) < 0.1) continue;
                decayMode2 = boostedTauDecayMode->at(ibtau);
                numMuTau++;
                muIndex=imu;
                tauIndex=ibtau;
                break;
                
                
            }
        }
        
        if(numMuTau < 1) continue;
        hcount->Fill(4);
        
        
        float  met_px = pfMET*sin(pfMETPhi);
        float  met_py = pfMET*cos(pfMETPhi);
        float  met = pfMET;
        float  metphi = pfMETPhi;
        
        float  m_1 = Mu4Mom.M();
        float  px_1 = Mu4Mom.Px();
        float  py_1 = Mu4Mom.Py();
        float  pz_1 = Mu4Mom.Pz();
        float  e_1 = Mu4Mom.E();
        float  pt_1 = Mu4Mom.Pt();
        float  phi_1 = Mu4Mom.Phi();
        float  eta_1 = Mu4Mom.Eta();

        float  m_2 = BoostTau4Mom.M();
        float  px_2 = BoostTau4Mom.Px();
        float  py_2 = BoostTau4Mom.Py();
        float  pz_2 = BoostTau4Mom.Pz();
        float  e_2 = BoostTau4Mom.E();
        float  pt_2 = BoostTau4Mom.Pt();
        float  phi_2 = BoostTau4Mom.Phi();
        float  eta_2 = BoostTau4Mom.Eta();

        float pfCovMatrix00 = metcov00;
        float pfCovMatrix01 = metcov01;
        float pfCovMatrix10 = metcov10;
        float pfCovMatrix11 = metcov11;
        int era = 2017;
    
        
        BoostTree->Branch("tmass",&MT);
        BoostTree->Branch("era", &era);

        BoostTree->Branch("met_px", &met_px);
        BoostTree->Branch("met_py", &met_py);
        BoostTree->Branch("met", &met);
        BoostTree->Branch("metphi", &metphi);
        
        BoostTree->Branch("m_1", &m_1);
        BoostTree->Branch("px_1", &px_1);
        BoostTree->Branch("py_1", &py_1);
        BoostTree->Branch("pz_1", &pz_1);
        BoostTree->Branch("e_1", &e_1);
        BoostTree->Branch("pt_1", &pt_1);
        BoostTree->Branch("phi_1", &phi_1);
        BoostTree->Branch("eta_1", &eta_1);

        BoostTree->Branch("m_2", &m_2);
        BoostTree->Branch("px_2", &px_2);
        BoostTree->Branch("py_2", &py_2);
        BoostTree->Branch("pz_2", &pz_2);
        BoostTree->Branch("e_2", &e_2);
        BoostTree->Branch("pt_2", &pt_2);
        BoostTree->Branch("phi_2", &phi_2);
        BoostTree->Branch("eta_2", &eta_2);
    
        
        BoostTree->Branch("metcov00", &pfCovMatrix00);
        BoostTree->Branch("metcov01", &pfCovMatrix01);
        BoostTree->Branch("metcov10", &pfCovMatrix10);
        BoostTree->Branch("metcov11", &pfCovMatrix11);

        BoostTree->Branch("decayMode2", &decayMode2);
        
        BoostTree->Branch("muIndex", &muIndex);
        BoostTree->Branch("tauIndex", &tauIndex);

        BoostTree->Fill();
    }
    
    
    BoostTree->SetName("mutau_tree");
    BoostTree->AutoSave();
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
    
    SkimerBoost t("root://cmsxrootd.fnal.gov/"+InputFile);
    t.Loop(OutputFile);
    
    return 0;
}



