#include "../interface/Functions.h"
#include <string>
#include <ostream>
#include <vector>
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooFunctor.h"
#include "RooMsgService.h"
#include "../interface/CLParser.h"
#include "../interface/LumiReweightingStandAlone.h"


int main(int argc, char* argv[]) {
    
    CLParser parser(argc, argv);
    std::string sample = parser.Option("-s");
    std::string name = parser.Option("-n");
    std::string path = parser.Option("-p");
    std::string output_dir = parser.Option("-d");
    //    std::string syst = parser.Option("-u");
    std::string fname = path + sample + ".root";
    //    std::string year_str = parser.Option("-y");
    
    std::string year_str;
    if (path.find("2016") != string::npos) year_str = "2016";
    else if (path.find("2017") != string::npos) year_str = "2017";
    else if (path.find("2018") != string::npos) year_str = "2018";
    else cout<<"Which year are you looking for \n\n";
    
    stringstream yearstream(year_str);
    int year=0;
    yearstream >> year;
    
    
    std::string systname = "";
    
    // create output file
    auto suffix = "_output.root";
    auto prefix = "Output/trees/" + output_dir + "/"+systname+"/";
    std::string filename;
    if (name == sample) {
        filename = prefix + name + systname + suffix;
    } else {
        filename = prefix + sample + std::string("_") + name + systname + suffix;
    }
    std::cout<<"output name is "<<filename.c_str()<<"\n";
    
    
    // open input file
    std::cout << "Opening file... " << sample << std::endl;
    auto InputFile = TFile::Open(fname.c_str());
    std::cout << "Loading Ntuple..." << std::endl;
    TTree *  Run_Tree;
    //    Run_Tree= Xttree(InputFile,"mutau_tree");
    Run_Tree= Xttree(InputFile,"EventTree");
    
    
    //    auto HistoTot = reinterpret_cast<TH1D*>(InputFile->Get("ggNtuplizer/hEvents"));
    TH1F * HistoTot = (TH1F*) InputFile->Get("hcount");
    auto fout = new TFile(filename.c_str(), "RECREATE");
    
    myMap1 = new std::map<std::string, TH1F*>();
    myMap2 = new std::map<std::string, TH2F*>();
    
    
    Int_t nentries_wtn = (Int_t) Run_Tree->GetEntries();
    cout<<"nentries_wtn===="<<nentries_wtn<<"\n";
    for (Int_t i = 0; i < nentries_wtn; i++) {
        
        Run_Tree->GetEntry(i);
        if (i % 1000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);
        //=========================================================================================================
        // Trigger
        bool PassTrigger = ((HLTEleMuX >> 21 & 1)==1);
        bool HLT_AK8PFJet400_TrimMass30 = ((HLTJet >> 40 & 1)==1);
        //              else if (name.find("HLT_Mu50_v")                                          != string::npos) bitEleMuX = 21;
        if (! PassTrigger) continue;
        
        //        else if (name.find("HLT_AK8PFHT800_TrimMass50_v")                                     != string::npos) bitJet = 37;
        //        else if (name.find("HLT_PFHT1050_v")                                                  != string::npos) bitJet = 38;
        //        else if (name.find("HLT_PFHT500_PFMET100_PFMHT100_IDTight_v")                         != string::npos) bitJet = 39;
        //        else if (name.find("HLT_AK8PFJet400_TrimMass30_v")                                    != string::npos) bitJet = 40;
        
        
        for (int ijet=0; ijet < nAK8Jet ; ijet ++){
            
            if (AK8JetPt->at(ijet) < 200  || AK8JetSoftDropMass < 0 || fabs(AK8JetEta->at(ijet)) > 2.5) continue;
            plotFill("trgEff_Before",AK8JetPt->at(ijet),AK8JetSoftDropMass->at(ijet),40,0,2000,30,0,300);
            if (HLT_AK8PFJet400_TrimMass30){
                plotFill("trgEff_After",AK8JetPt->at(ijet),AK8JetSoftDropMass->at(ijet) ,40,0,2000,30,0,300);
            }
            
            if (AK8JetPt->at(ijet) < 450  || AK8JetSoftDropMass < 0 || fabs(AK8JetEta->at(ijet)) > 2.5) continue;
            plotFill("finalTrgEff_Before",AK8JetSoftDropMass->at(ijet),30,0,300);
            if (HLT_AK8PFJet400_TrimMass30){
                plotFill("finalTrgEff_After",AK8JetSoftDropMass->at(ijet),30,0,300);
            }
            
        }
        
    } //End of Tree
    
    
    fout->cd();
    map<string, TH1F*>::const_iterator iMap1 = myMap1->begin();
    map<string, TH1F*>::const_iterator jMap1 = myMap1->end();
    
    for (; iMap1 != jMap1; ++iMap1)
    nplot1(iMap1->first)->Write();
    //    outTr->Write();
    
    map<string, TH2F*>::const_iterator iMap2 = myMap2->begin();
    map<string, TH2F*>::const_iterator jMap2 = myMap2->end();
    
    for (; iMap2 != jMap2; ++iMap2)
    nplot2(iMap2->first)->Write();
    
    fout->Close();
}


