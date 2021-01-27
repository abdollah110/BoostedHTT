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
    
    int year=0;
    float muPt_cut= 30;
    
    if (string(file->GetName()).find("2016") != string::npos) {year =2016; muPt_cut= 25;}
    else if (string(file->GetName()).find("2017") != string::npos ) {year =2017; muPt_cut= 28;}
    else if (string(file->GetName()).find("2018") != string::npos) {year =2018; muPt_cut= 28;}
    else (std::cout << "Year is not specificed in the outFile name !\n");
    
    fChain->SetBranchStatus("*",1);
    
    TH1F* hcount = new TH1F("hcount", "", 10, 0, 10);
    
    if (fChain == 0) return;
    
    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    float MuMass= 0.10565837;
    float eleMass= 0.000511;
    
    float  met_px = 0;
    float  met_py = 0;
    float  met = 0;
    float  metphi = 0;
    float pfCovMatrix00 = 0;
    float pfCovMatrix01 = 0;
    float pfCovMatrix10 = 0;
    float pfCovMatrix11 = 0;
    
    float  _met_JESUp = 0 ;
    float  _met_JESDown = 0 ;
    float  _met_UESUp = 0 ;
    float  _met_UESDown = 0 ;
    float  _metphi_JESUp = 0 ;
    float  _metphi_JESDown = 0 ;
    float  _metphi_UESUp = 0 ;
    float  _metphi_UESDown = 0 ;
    
    float  _met_reso_Up = 0;
    float  _met_reso_Down = 0;
    float  _met_resp_Up = 0;
    float  _met_resp_Down = 0;
    float  _metphi_reso_Up = 0;
    float  _metphi_reso_Down = 0;
    float  _metphi_resp_Up = 0;
    float  _metphi_resp_Down = 0;
    
    
    float  m_1 = 0;
    float  px_1 = 0;
    float  py_1 = 0;
    float  pz_1 = 0;
    float  e_1 = 0;
    float  pt_1 = 0;
    float  phi_1 = 0;
    float  eta_1 = 0;
    
    float  m_2 = 0;
    float  px_2 = 0;
    float  py_2 = 0;
    float  pz_2 = 0;
    float  e_2 = 0;
    float  pt_2 = 0;
    float  phi_2 = 0;
    float  eta_2 = 0;
    
    int era = 0;
    int decayMode2 = 1;
    int lepIndex = -1;
    int tauIndex= -1;
    int NumPair=0;
    
    
    BoostTree->Branch("era", &era);
    BoostTree->Branch("NumPair", &NumPair);
    
    BoostTree->Branch("met_px", &met_px);
    BoostTree->Branch("met_py", &met_py);
    BoostTree->Branch("met", &met);
    BoostTree->Branch("metphi", &metphi);
    BoostTree->Branch("metcov00", &pfCovMatrix00);
    BoostTree->Branch("metcov01", &pfCovMatrix01);
    BoostTree->Branch("metcov10", &pfCovMatrix10);
    BoostTree->Branch("metcov11", &pfCovMatrix11);
    
    // Systematics
    BoostTree->Branch("met_JESUp", &_met_JESUp);
    BoostTree->Branch("met_JESDown", &_met_JESDown);
    BoostTree->Branch("met_UESUp", &_met_UESUp);
    BoostTree->Branch("met_UESDown", &_met_UESDown);
    BoostTree->Branch("metphi_JESUp", &_metphi_JESUp);
    BoostTree->Branch("metphi_JESDown", &_metphi_JESDown);
    BoostTree->Branch("metphi_UESUp", &_metphi_UESUp);
    BoostTree->Branch("metphi_UESDown", &_metphi_UESDown);
    
    BoostTree->Branch("met_reso_Up", &_met_reso_Up);
    BoostTree->Branch("met_reso_Down", &_met_reso_Down);
    BoostTree->Branch("met_resp_Up", &_met_resp_Up);
    BoostTree->Branch("met_resp_Down", &_met_resp_Down);
    BoostTree->Branch("metphi_reso_Up", &_metphi_reso_Up);
    BoostTree->Branch("metphi_reso_Down", &_metphi_reso_Down);
    BoostTree->Branch("metphi_resp_Up", &_metphi_resp_Up);
    BoostTree->Branch("metphi_resp_Down", &_metphi_resp_Down);
    
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
    BoostTree->Branch("decayMode2", &decayMode2);
    
    BoostTree->Branch("lepIndex", &lepIndex);
    BoostTree->Branch("tauIndex", &tauIndex);
    
    for (int jentry=0; jentry<nentries;jentry++) {
        
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        
        if(jentry % 10000 == 0) cout << "Processed " << jentry << " events out of " <<nentries<<endl;
        
        hcount->Fill(1);
        if (!isData)
            hcount->Fill(2,genWeight);
        
        TLorentzVector BoostTau4Mom, Lep4Mom;
        auto numLepTau(0);
        bool foundApair= false;
        
        for (int imu = 0; imu < nMu; ++imu){
            
            if (muPt->at(imu) < muPt_cut || fabs(muEta->at(imu)) > 2.4) continue;
            hcount->Fill(3);
            if (muPt->at(imu) < 52  && pfMET < 40  ) continue;
            hcount->Fill(4);
            
            Lep4Mom.SetPtEtaPhiM(muPt->at(imu),muEta->at(imu),muPhi->at(imu),MuMass);
            
            for (int ibtau = 0; ibtau < nBoostedTau; ++ibtau){
                
                if (boostedTauPt->at(ibtau) < 30 || fabs(boostedTauEta->at(ibtau)) > 2.3 ) continue;
                if (boostedTaupfTausDiscriminationByDecayModeFinding->at(ibtau) < 0.5 ) continue;
                if (boostedTauByLooseMuonRejection3->at(ibtau) < 0.5) continue;
                if (boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(ibtau) < -0.5) continue;
                hcount->Fill(5);
                BoostTau4Mom.SetPtEtaPhiM(boostedTauPt->at(ibtau),boostedTauEta->at(ibtau),boostedTauPhi->at(ibtau),boostedTauMass->at(ibtau));
                
                if(BoostTau4Mom.DeltaR(Lep4Mom) > 0.8 || BoostTau4Mom.DeltaR(Lep4Mom) < 0.1) continue;
                hcount->Fill(6);
                decayMode2 = boostedTauDecayMode->at(ibtau);
                numLepTau++;
                if (!foundApair){
                    lepIndex=imu;
                    tauIndex=ibtau;
                }
                foundApair=true;
            }
        }
        
        if(numLepTau < 1) continue;
        hcount->Fill(7);
        
        met_px = pfMET*sin(pfMETPhi);
        met_py = pfMET*cos(pfMETPhi);
        met = pfMET;
        metphi = pfMETPhi;
        
        m_1 = Lep4Mom.M();
        px_1 = Lep4Mom.Px();
        py_1 = Lep4Mom.Py();
        pz_1 = Lep4Mom.Pz();
        e_1 = Lep4Mom.E();
        pt_1 = Lep4Mom.Pt();
        phi_1 = Lep4Mom.Phi();
        eta_1 = Lep4Mom.Eta();
        
        m_2 = BoostTau4Mom.M();
        px_2 = BoostTau4Mom.Px();
        py_2 = BoostTau4Mom.Py();
        pz_2 = BoostTau4Mom.Pz();
        e_2 = BoostTau4Mom.E();
        pt_2 = BoostTau4Mom.Pt();
        phi_2 = BoostTau4Mom.Phi();
        eta_2 = BoostTau4Mom.Eta();
        
        pfCovMatrix00 = metcov00;
        pfCovMatrix01 = metcov01;
        pfCovMatrix10 = metcov10;
        pfCovMatrix11 = metcov11;
        era = year;
        NumPair=numLepTau;
        
        _met_JESUp = met_JESUp ;
        _met_JESDown = met_JESDown ;
        _met_UESUp = met_UESUp ;
        _met_UESDown = met_UESDown ;
        _metphi_JESUp = metphi_JESUp ;
        _metphi_JESDown = metphi_JESDown ;
        _metphi_UESUp = metphi_UESUp ;
        _metphi_UESDown = metphi_UESDown ;
        
        _met_reso_Up = met_reso_Up;
        _met_reso_Down = met_reso_Down;
        _met_resp_Up = met_resp_Up;
        _met_resp_Down = met_resp_Down;
        _metphi_reso_Up = metphi_reso_Up;
        _metphi_reso_Down = metphi_reso_Down;
        _metphi_resp_Up = metphi_resp_Up;
        _metphi_resp_Down = metphi_resp_Down;
        
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
    
    SkimerBoost t(InputFile);
    t.Loop(OutputFile);    
    return 0;
}



