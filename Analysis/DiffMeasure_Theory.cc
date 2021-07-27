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
#include "../interface/bjet_weighter.h"


int main(int argc, char* argv[]) {
    
    CLParser parser(argc, argv);
    std::string sample = parser.Option("-s");
    std::string name = parser.Option("-n");
    std::string path = parser.Option("-p");
    std::string output_dir = parser.Option("-d");
    std::string syst = parser.Option("-u");
    std::string fname = path + sample + ".root";
    
    std::string year_str;
    if (path.find("2016") != string::npos) year_str = "2016";
    else if (path.find("2017") != string::npos) year_str = "2017";
    else if (path.find("2018") != string::npos) year_str = "2018";
    else cout<<"Which year are you looking for \n\n";
    cout<<"%%%% Note: you are running on  "<< year_str <<"%%%%\n";



    std::string channel_tree;
    if (path.find("/mt") != string::npos) channel_tree = "mutau_tree";
    else if (path.find("/et") != string::npos) channel_tree = "etau_tree";
    else if (path.find("/em") != string::npos) channel_tree = "emu_tree";
    else if (path.find("/me") != string::npos) channel_tree = "mue_tree";
    else if (path.find("/tt") != string::npos) channel_tree = "tautau_tree";
    else cout<<"Which channel are you looking for \n\n";
    cout<<"%%%% Note: you are running on  "<< channel_tree <<"%%%%\n";



    stringstream yearstream(year_str);
    int year=0;
    yearstream >> year;
    
    
    std::string systname = "";
    if (!syst.empty()) {
        systname = "_" + syst;
    }
    
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
    
    float xbin[5]={0,350,450,600,2000};
    
    // open input file
    std::cout << "Opening file... " << sample << std::endl;
    auto InputFile = TFile::Open(fname.c_str());
    std::cout << "Loading Ntuple..." << std::endl;
    TTree *  Run_Tree;
    Run_Tree= Xttree(InputFile,channel_tree);
    //    Run_Tree= Xttree(InputFile,"EventTree");
    
    
    //    auto HistoTot = reinterpret_cast<TH1D*>(InputFile->Get("ggNtuplizer/hEvents"));
    TH1F * HistoTot = (TH1F*) InputFile->Get("hcount");
    auto fout = new TFile(filename.c_str(), "RECREATE");
    
    myMap1 = new std::map<std::string, TH1F*>();
    myMap2 = new map<string, TH2F*>();
    TH1F * higpt=new TH1F("hig","hig",sizeof(xbin)/sizeof(xbin[0]) - 1, &xbin[0]);

    
    //###############################################################################################
    // Parameters
    //###############################################################################################
    float MuMass= 0.10565837;
    float eleMass= 0.000511;
    float JetPtCut=30;
    float BJetPtCut=20;
    
    
    Int_t nentries_wtn = (Int_t) Run_Tree->GetEntries();
    cout<<"nentries_wtn===="<<nentries_wtn<<"\n";
    for (Int_t i = 0; i < nentries_wtn; i++) {
        
        Run_Tree->GetEntry(i);
        if (i % 1000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

        TLorentzVector Mu4Momentum,Tau4Momentum, Z4Momentum, Met4Momentum,Ele4Momentum;
        TLorentzVector LeadTau4Momentum,SubTau4Momentum;

        //=========================================================================================================
        //MET Shape systematics
//        Met=pfMET;
//        Metphi=pfMETPhi;
        float Met=pfMetNoRecoil;
        float Metphi=pfMetPhiNoRecoil;
        Met4Momentum.SetPtEtaPhiM(Met, 0, Metphi, 0);
                    // Lumi weight
        float LumiWeight = XSection(sample)*1.0 / HistoTot->GetBinContent(2);

        //=========================================================================================================
        
        if (channel_tree.find("mutau_tree") != string::npos) {
        
        // Muon selection
        int idx_lep= lepIndex;
        if (muPt->at(idx_lep) < 30 || fabs(muEta->at(idx_lep)) > 2.4) continue;
        Mu4Momentum.SetPtEtaPhiM(muPt->at(idx_lep),muEta->at(idx_lep),muPhi->at(idx_lep),MuMass);
        // Tau selection
        int idx_tau= tauIndex;
        if (boostedTauPt->at(idx_tau) <= 30 || fabs(boostedTauEta->at(idx_tau)) >= 2.3 ) continue;
        Tau4Momentum.SetPtEtaPhiM(boostedTauPt->at(idx_tau),boostedTauEta->at(idx_tau),boostedTauPhi->at(idx_tau),boostedTauMass->at(idx_tau));

        TLorentzVector higgs = Tau4Momentum+Mu4Momentum +Met4Momentum;
        TLorentzVector LeadJet= getLeadJet(Mu4Momentum, Tau4Momentum);
        if (higgs.Pt() < 280) continue;
        higpt->Fill(higgs.Pt(),LumiWeight);
        
        }
    
    
    
    } //End of Tree
    
    
    fout->cd();
    
    map<string, TH1F*>::const_iterator iMap1 = myMap1->begin();
    map<string, TH1F*>::const_iterator jMap1 = myMap1->end();
    for (; iMap1 != jMap1; ++iMap1)
    nplot1(iMap1->first)->Write();
    
    map<string, TH2F*>::const_iterator iMap2 = myMap2->begin();
    map<string, TH2F*>::const_iterator jMap2 = myMap2->end();
    for (; iMap2 != jMap2; ++iMap2)
    nplot2(iMap2->first)->Write();

    higpt->Write();
    fout->Close();
}


