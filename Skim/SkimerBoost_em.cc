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
    
    float  met_px = 0;
    float  met_py = 0;
    float  met = 0;
    float  metphi = 0;
    float pfCovMatrix00 = 0;
    float pfCovMatrix01 = 0;
    float pfCovMatrix10 = 0;
    float pfCovMatrix11 = 0;
    
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
    int tau1Index = -1;
    int tau2Index= -1;
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
    
    BoostTree->Branch("tau1Index", &tau1Index);
    BoostTree->Branch("tau2Index", &tau2Index);
    
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
        
        TLorentzVector Ele4Mom, Lep4Mom;
        auto numLepLep(0);
        bool foundApair= false;
        
        for (int imu = 0; imu < nMu; ++imu){
            //            if (foundApair) break;
            if (muPt->at(imu) < 52 || fabs(muEta->at(imu)) > 2.4) continue;
            Lep4Mom.SetPtEtaPhiM(muPt->at(imu),muEta->at(imu),muPhi->at(imu),MuMass);
            
            
            for (int iele = 0; iele < nEle; ++iele){
                //            if (foundApair) break;
                if (elePt->at(iele) < 15 || fabs(eleEta->at(iele)) > 2.5) continue;
                
                
                bool eleMVAId= false;
                if (fabs (eleSCEta->at(iele)) <= 0.8 && eleIDMVANoIso->at(iele) >    0.837   ) eleMVAId= true;
                else if (fabs (eleSCEta->at(iele)) >  0.8 &&fabs (eleSCEta->at(iele)) <=  1.5 && eleIDMVANoIso->at(iele) >    0.715   ) eleMVAId= true;
                else if ( fabs (eleSCEta->at(iele)) >=  1.5 && eleIDMVANoIso->at(iele) >   0.357   ) eleMVAId= true;
                else eleMVAId= false;
                
                if (!eleMVAId) continue;
                
                Ele4Mom.SetPtEtaPhiM(elePt->at(iele),eleEta->at(iele),elePhi->at(iele),eleMass);
                
                
                if(Ele4Mom.DeltaR(Lep4Mom) > 0.8 || Ele4Mom.DeltaR(Lep4Mom) < 0.1) continue;
                //                decayMode2 = boostedTauDecayMode->at(ibtau);
                numLepLep++;
                if (!foundApair){
                    tau1Index=imu;
                    tau2Index=iele;
                }
                foundApair=true;
                //                break;
            }
        }
        
        if(numLepLep < 1) continue;
        hcount->Fill(4);
        
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
        
        m_2 = Ele4Mom.M();
        px_2 = Ele4Mom.Px();
        py_2 = Ele4Mom.Py();
        pz_2 = Ele4Mom.Pz();
        e_2 = Ele4Mom.E();
        pt_2 = Ele4Mom.Pt();
        phi_2 = Ele4Mom.Phi();
        eta_2 = Ele4Mom.Eta();
        
        pfCovMatrix00 = metcov00;
        pfCovMatrix01 = metcov01;
        pfCovMatrix10 = metcov10;
        pfCovMatrix11 = metcov11;
        era = 2017;
        NumPair=numLepLep;
        
        
        BoostTree->Fill();
    }
    
    
    BoostTree->SetName("emu_tree");
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



