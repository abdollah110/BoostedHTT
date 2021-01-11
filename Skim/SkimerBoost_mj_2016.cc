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
#include "../interface/Functions.h"
using namespace std;


void SkimerBoost::Loop(TString OutputFile)
{
    
    TH1F* hEvents = (TH1F*)gDirectory->Get("ggNtuplizer/hEvents");
    
    TFile* file = TFile::Open(OutputFile, "RECREATE");
    TTree* MyNewTree = fChain->CloneTree(0);
    
    int year=0;
    if (string(file->GetName()).find("2016") != string::npos) year =2016;
    else if (string(file->GetName()).find("2017") != string::npos ) year =2017;
    else if (string(file->GetName()).find("2018") != string::npos) year =2018;
    else (std::cout << "Year is not specificed in the outFile name !\n");
    
    fChain->SetBranchStatus("*",1);
    
    myMap1 = new std::map<std::string, TH1F*>();
    myMap2 = new std::map<std::string, TH2F*>();
    
    
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
        
        bool HLT_Mu50 = ((HLTEleMuX >> 21 & 1)==1);
        if (! HLT_Mu50) continue;
        
        bool HLT_AK8PFJet360_TrimMass30 = ((HLTJet >> 21 & 1)==1);
        bool HLT_PFHT300_PFMET110 = ((HLTJet >> 22 & 1)==1);
        
        
        auto numMuonJet(0);
        float PFHT= getST(30);
        float PFMET=pfMET;
        //        float MHT=getMHT(30);
        
        
        for (int ijet=0; ijet < nAK8Jet ; ijet ++){
            
            if (AK8JetPt->at(ijet) < 200  || AK8JetSoftDropMass->at(ijet) < 0 || fabs(AK8JetEta->at(ijet)) > 2.5) continue;
            numMuonJet++;
            
            //Filling 2D eff plot
            plotFill("ht_trgEff_2D_Before",AK8JetPt->at(ijet),AK8JetSoftDropMass->at(ijet),50,0,2000,30,0,300);
            if (HLT_AK8PFJet360_TrimMass30){
                plotFill("ht_trgEff_2D_After",AK8JetPt->at(ijet),AK8JetSoftDropMass->at(ijet) ,50,0,2000,30,0,300);
            }
            
            //Filling 1D eff plot
            if (AK8JetPt->at(ijet) > 450  && AK8JetSoftDropMass->at(ijet) > 0 && fabs(AK8JetEta->at(ijet)) < 2.5)
            plotFill("ht_trgEff_1D_Before",AK8JetSoftDropMass->at(ijet),30,0,300);
            if (AK8JetPt->at(ijet) > 450  && AK8JetSoftDropMass->at(ijet) > 0 && fabs(AK8JetEta->at(ijet)) < 2.5 && HLT_AK8PFJet360_TrimMass30)
                plotFill("ht_trgEff_1D_After",AK8JetSoftDropMass->at(ijet),30,0,300);

        }
        
        
        //Filling 2D eff plot
        plotFill("met_trgEff_2D_Before",PFHT,PFMET,60,0,3000,50,0,1000);
        if (HLT_PFHT300_PFMET110){
            plotFill("met_trgEff_2D_After",PFHT,PFMET,60,0,3000,50,0,1000);
        }
        
        //Filling 1D eff plot
        if (PFHT > 400 )
            plotFill("met_trgEff_1D_Before",PFMET,50,0,1000);
        if (PFHT > 400  && HLT_PFHT300_PFMET110)
            plotFill("met_trgEff_1D_After",PFMET,50,0,1000);
        
        
        if(numMuonJet < 1) continue;
        
        MyNewTree->Fill();
    }
    
    
    MyNewTree->AutoSave();
    hEvents->Write();
    
    map<string, TH1F*>::const_iterator iMap1 = myMap1->begin();
    map<string, TH1F*>::const_iterator jMap1 = myMap1->end();
    
    for (; iMap1 != jMap1; ++iMap1)
    nplot1(iMap1->first)->Write();
    
    map<string, TH2F*>::const_iterator iMap2 = myMap2->begin();
    map<string, TH2F*>::const_iterator jMap2 = myMap2->end();
    
    for (; iMap2 != jMap2; ++iMap2)
    nplot2(iMap2->first)->Write();
    
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


// Lowest unprescaled trigger           2016                         2017                                     2018

//           HLT_AK8PFJet360_TrimMass30_v                      HLT_AK8PFJet400_TrimMass30(36.75/ 41.54)   HLT_AK8PFJet400_TrimMass30_v
//           HLT_AK8PFJet500 (not in yet 33.64/36.47 )         HLT_AK8PFJet500 (not in yet)               HLT_AK8PFJet500 (not in yet)
//           HLT_PFHT300_PFMET110_v                            HLT_PFHT500_PFMET100_PFMHT100_IDT          HLT_PFHT500_PFMET100_PFMHT100_IDT
//           HLT_PFHT900_v                                     HLT_PFHT1050_v                             HLT_PFHT1050_v