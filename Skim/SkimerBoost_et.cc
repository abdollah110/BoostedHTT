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
        
        TLorentzVector BoostTau4Mom, Lep4Mom;
        auto numLepTau(0);
        bool foundApair= false;
        
        
        for (int iele = 0; iele < nEle; ++iele){
            
            if (elePt->at(iele) < 37 || fabs(eleEta->at(iele)) > 2.5) continue;
            hcount->Fill(3);
            if (elePt->at(iele) < 120 &&  pfMetNoRecoil < 30) continue;
            hcount->Fill(4);
            
            bool eleMVAId= false;
            if (fabs (eleSCEta->at(iele)) <= 0.8 && eleIDMVANoIso->at(iele) >    0.837   ) eleMVAId= true;
            else if (fabs (eleSCEta->at(iele)) >  0.8 &&fabs (eleSCEta->at(iele)) <=  1.5 && eleIDMVANoIso->at(iele) >    0.715   ) eleMVAId= true;
            else if ( fabs (eleSCEta->at(iele)) >=  1.5 && eleIDMVANoIso->at(iele) >   0.357   ) eleMVAId= true;
            else eleMVAId= false;
            
            if (!eleMVAId) continue;
            hcount->Fill(5);
            
            Lep4Mom.SetPtEtaPhiM(elePt->at(iele),eleEta->at(iele),elePhi->at(iele),eleMass);
            
            
            for (int ibtau = 0; ibtau < nBoostedTau; ++ibtau){
                
                
                if (boostedTauPt->at(ibtau) < 30 || fabs(boostedTauEta->at(ibtau)) > 2.3 ) continue;
                if (boostedTaupfTausDiscriminationByDecayModeFinding->at(ibtau) < 0.5 ) continue;
                if (boostedTauagainstElectronVLooseMVA62018->at(ibtau) < 0.5) continue;
                if (boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(ibtau) < -0.5) continue;
                hcount->Fill(6);
                BoostTau4Mom.SetPtEtaPhiM(boostedTauPt->at(ibtau),boostedTauEta->at(ibtau),boostedTauPhi->at(ibtau),boostedTauMass->at(ibtau));
                
                if(BoostTau4Mom.DeltaR(Lep4Mom) > 0.8 || BoostTau4Mom.DeltaR(Lep4Mom) < 0.1) continue;
                hcount->Fill(7);
                decayMode2 = boostedTauDecayMode->at(ibtau);
                numLepTau++;
                if (! foundApair){
                    lepIndex=iele;
                    tauIndex=ibtau;
                }
                foundApair=true;
            }
        }
        
        if(numLepTau < 1) continue;
        hcount->Fill(8);
        
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
        
        NumPair=numLepTau;
            
        BoostTree->Fill();
    }
    
    
    BoostTree->SetName("etau_tree");
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

