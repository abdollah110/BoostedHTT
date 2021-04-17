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
    
    if (string(file->GetName()).find("2016") != string::npos) {year =2016; }
    else if (string(file->GetName()).find("2017") != string::npos ) {year =2017; }
    else if (string(file->GetName()).find("2018") != string::npos) {year =2018; }
    else (std::cout << "Year is not specificed in the outFile name !\n");
    
    
    fChain->SetBranchStatus("*",1);
    
    TH1F* hcount = new TH1F("hcount", "", 10, 0, 10);
    
    if (fChain == 0) return;
    
    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    float MuMass= 0.10565837;
    float eleMass= 0.000511;
        
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
    
    int decayMode2 = 1;
    int lepIndex = -1;
    int tauIndex= -1;
    int NumPair=0;
    
    
    BoostTree->Branch("NumPair", &NumPair);
        
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
        
        TLorentzVector Ele4Mom, Mu4Mom;
        auto numLepLep(0);
        bool foundApair= false;
        
        for (int imu = 0; imu < nMu; ++imu){
            
            if (muPt->at(imu) < muPt_cut || fabs(muEta->at(imu)) > 2.4) continue;
            hcount->Fill(3);
            if (muPt->at(imu) < 55  && pfMetNoRecoil < 40  ) continue;
            hcount->Fill(4);
            
            Mu4Mom.SetPtEtaPhiM(muPt->at(imu),muEta->at(imu),muPhi->at(imu),MuMass);
            
            for (int iele = 0; iele < nEle; ++iele){
                if (elePt->at(iele) < 10 || fabs(eleEta->at(iele)) > 2.5) continue;
                hcount->Fill(5);
                
                bool eleMVAId= false;
                if (fabs (eleSCEta->at(iele)) <= 0.8 && eleIDMVANoIso->at(iele) >    0.837   ) eleMVAId= true;
                else if (fabs (eleSCEta->at(iele)) >  0.8 &&fabs (eleSCEta->at(iele)) <=  1.5 && eleIDMVANoIso->at(iele) >    0.715   ) eleMVAId= true;
                else if ( fabs (eleSCEta->at(iele)) >=  1.5 && eleIDMVANoIso->at(iele) >   0.357   ) eleMVAId= true;
                else eleMVAId= false;
                
                if (!eleMVAId) continue;
                hcount->Fill(6);
                
                Ele4Mom.SetPtEtaPhiM(elePt->at(iele),eleEta->at(iele),elePhi->at(iele),eleMass);
                
                if(Ele4Mom.DeltaR(Mu4Mom) > 0.8 || Ele4Mom.DeltaR(Mu4Mom) < 0.1) continue;
                hcount->Fill(7);
                numLepLep++;
                if (!foundApair){
                    lepIndex=imu;
                    tauIndex=iele;
                }
                foundApair=true;
            }
        }
        
        if(numLepLep < 1) continue;
        hcount->Fill(8);
        
        m_1 = Mu4Mom.M();
        px_1 = Mu4Mom.Px();
        py_1 = Mu4Mom.Py();
        pz_1 = Mu4Mom.Pz();
        e_1 = Mu4Mom.E();
        pt_1 = Mu4Mom.Pt();
        phi_1 = Mu4Mom.Phi();
        eta_1 = Mu4Mom.Eta();
        
        m_2 = Ele4Mom.M();
        px_2 = Ele4Mom.Px();
        py_2 = Ele4Mom.Py();
        pz_2 = Ele4Mom.Pz();
        e_2 = Ele4Mom.E();
        pt_2 = Ele4Mom.Pt();
        phi_2 = Ele4Mom.Phi();
        eta_2 = Ele4Mom.Eta();
        
        NumPair=numLepLep;
        
        BoostTree->Fill();
    }
    
    
    BoostTree->SetName("mue_tree");
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



