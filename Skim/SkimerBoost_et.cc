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
        
        TLorentzVector BoostTau4Mom, Ele4Mom;
        int decayMode2 = 1;
        float MT = 0;
        auto numEleTau(0);
        for (int iele = 0; iele < nEle; ++iele){
            if (elePt->at(iele) < 35 || fabs(eleEta->at(iele)) > 2.5) continue;
            

            bool eleMVAIdExtra_i= false;
            if (fabs (eleSCEta->at(iele)) <= 0.8 && eleIDMVAIso->at(iele) >    0.837   ) eleMVAIdExtra_i= true;
            else if (fabs (eleSCEta->at(iele)) >  0.8 &&fabs (eleSCEta->at(iele)) <=  1.5 && eleIDMVAIso->at(iele) >    0.715   ) eleMVAIdExtra_i= true;
            else if ( fabs (eleSCEta->at(iele)) >=  1.5 && eleIDMVAIso->at(iele) >   0.357   ) eleMVAIdExtra_i= true;
            else eleMVAIdExtra_i= false;
            
            if (!eleMVAIdExtra_i) continue;
            
            

            Ele4Mom.SetPtEtaPhiM(elePt->at(iele),eleEta->at(iele),elePhi->at(iele),eleMass);
            
            MT =TMass_F(Ele4Mom.Pt(),Ele4Mom.Px(),Ele4Mom.Py(),pfMET,pfMETPhi);
            if(MT > 80) continue;
            
            
            for (int ibtau = 0; ibtau < nBoostedTau; ++ibtau){
            
                if (boostedTauPt->at(ibtau) < 40 || fabs(boostedTauEta->at(ibtau)) > 2.3 ) continue;
                if (boostedTaupfTausDiscriminationByDecayModeFinding->at(ibtau) < 0.5 ) continue;
                if (boostedTauByMVA6TightElectronRejection->at(ibtau) < 0.5) continue;
                if (boostedTauByLooseMuonRejection3->at(ibtau) < 0.5) continue;
                if (boostedTauByVLooseIsolationMVArun2v1DBoldDMwLT->at(ibtau) < 0.5) continue;

                BoostTau4Mom.SetPtEtaPhiM(boostedTauPt->at(ibtau),boostedTauEta->at(ibtau),boostedTauPhi->at(ibtau),boostedTauMass->at(ibtau));
                
                if(BoostTau4Mom.DeltaR(Ele4Mom) > 0.8 || BoostTau4Mom.DeltaR(Ele4Mom) < 0.1) continue;
                decayMode2 = boostedTauDecayMode->at(ibtau);
                numEleTau++;
                break;
                
                
            }
        }
        
        if(numEleTau < 1) continue;
        hcount->Fill(4);
        
        
        float  met_px = pfMET*sin(pfMETPhi);
        float  met_py = pfMET*cos(pfMETPhi);
        float  met = pfMET;
        float  metphi = pfMETPhi;
        
        float  m_1 = Ele4Mom.M();
        float  px_1 = Ele4Mom.Px();
        float  py_1 = Ele4Mom.Py();
        float  pz_1 = Ele4Mom.Pz();
        float  e_1 = Ele4Mom.E();
        float  pt_1 = Ele4Mom.Pt();
        float  phi_1 = Ele4Mom.Phi();
        float  eta_1 = Ele4Mom.Eta();

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
    
    SkimerBoost t("root://cmsxrootd.fnal.gov/"+InputFile);
    t.Loop(OutputFile);
    
    return 0;
}



