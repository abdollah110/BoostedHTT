#include "../interface/Functions.h"
#include <string>
#include <ostream>
#include <vector>
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooFunctor.h"
#include "RooMsgService.h"
#include "../interface/CLParser.h"


int main(int argc, char* argv[]) {
    
    CLParser parser(argc, argv);
    std::string sample = parser.Option("-s");
    std::string name = parser.Option("-n");
    std::string path = parser.Option("-p");
    std::string output_dir = parser.Option("-d");
    std::string syst = parser.Option("-u");
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
    
    
    // open input file
    std::cout << "Opening file... " << sample << std::endl;
    auto fin = TFile::Open(fname.c_str());
    std::cout << "Loading Ntuple..." << std::endl;
    TTree *  Run_Tree;
    Run_Tree= Xttree(fin,"EventTree");
    
    //    auto HistoTot = reinterpret_cast<TH1D*>(fin->Get("ggNtuplizer/hEvents"));
    TH1F * HistoTot = (TH1F*) fin->Get("hcount");
    auto fout = new TFile(filename.c_str(), "RECREATE");
    
    myMap1 = new std::map<std::string, TH1F*>();
    myMap2 = new map<string, TH2F*>();
    
    //########################################
    // Muon Id, Iso, Trigger and Tracker Eff files
    //########################################
    TH2F** HistoMuId=FuncHistMuId(year);
    //    TH2F** HistoMuIso=FuncHistMuIso();
    TH2F** HistoMuTrg=FuncHistMuTrigger_50(year);
    //    TGraphAsymmErrors * HistoMuTrack=FuncHistMuTrack();
    
    //########################################
    // Pileup files
    //########################################
    
    TH1F *  HistoPUData =HistPUData(year_str);
    TH1F * HistoPUMC = new TH1F();
    //    if (! (fname.find("Data") != string::npos || fname.find("Run") != string::npos ))
    //        HistoPUMC=HistPUMC(fin);
    
    
    //###############################################################################################
    //  Fix Parameters
    //###############################################################################################
    float MuMass= 0.10565837;
    float eleMass= 0.000511;
    float JetPtCut=30;
    float BJetPtCut=20;
    float muonPtCut=30;
    if (year==2018) muonPtCut=35;
    
    
    float DeepCSVCut=   1000   ;                  //  loose  https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
    if (year== 2016) DeepCSVCut =     0.8953  ;
    if (year== 2017) DeepCSVCut =     0.8001  ;
    if (year== 2018) DeepCSVCut =    0.7527   ;
    
    float LeptonIsoCut=0.20;
    bool debug= false;
    
    
    Int_t nentries_wtn = (Int_t) Run_Tree->GetEntries();
    cout<<"nentries_wtn===="<<nentries_wtn<<"\n";
    for (Int_t i = 0; i < nentries_wtn; i++) {
        //                    for (Int_t i = 0; i < 10000; i++) {
        
        Run_Tree->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);
        
        
        //=========================================================================================================
        // Trigger
        bool PassTrigger = ((HLTEleMuX >> 19 & 1)==1);
        //              else if (name.find("HLT_Mu50_v")                                          != string::npos) bitEleMuX = 21;
        // else if (name.find("HLT_IsoMu27_v") != string::npos) bitEleMuX = 19; // 2017
        if (! PassTrigger) continue;
        plotFill("cutFlowTable",2 ,15,0,15);
        
        
        //  This part is to avoid of the duplicate of mu-tau pair from one events
        std::vector<string> HistNamesFilled;
        HistNamesFilled.clear();
        
        
        //###############################################################################################
        //  GenInfo
        //###############################################################################################
        vector<float>  genInfo=GeneratorInfo();
        float ZBosonPt=genInfo[2];
        float ZBosonMass=genInfo[4];
        
        // BJet veto
        int numBJet=numBJets(BJetPtCut,DeepCSVCut);
        if (numBJet > 0) continue;
        
        //electron veto
        int numele =getNumElectron();
        if (numele > 0) continue;
        
        
        //############################################################################################
        //###########       Loop over MuJet events   #################################################
        //############################################################################################
        
        
        
        for (int ibtau = 0; ibtau < nBoostedTau; ++ibtau){
            
            
            
            //###############################################################################################
            //  Weight
            //###############################################################################################
            float LumiWeight = 1;
            float PUWeight = 1;
            float LepCorrection=1;
            
            if (!isData){
                
                // Lumi weight
                LumiWeight = getLuminsoity(year) * XSection(sample)*1.0 / HistoTot->GetBinContent(2);
                
            }
            
            
            
            //###############################################################################################
            
            
            float FullWeight = LumiWeight*LepCorrection;
            std::string FullStringName = "";
            
            plotFill("denum"+FullStringName,boostedTauPt->at(ibtau) ,100,0,500,FullWeight);
            
            if (boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNew->at(ibtau) > 0.5){
                plotFill("numLoose"+FullStringName,boostedTauPt->at(ibtau) ,100,0,500,FullWeight);
            }

            if (boostedTauByTightIsolationMVArun2v1DBoldDMwLTNew->at(ibtau) > 0.5){
                plotFill("numTight"+FullStringName,boostedTauPt->at(ibtau) ,100,0,500,FullWeight);
            }

            //                            plotFill("dR"+FullStringName,SubMu4Momentum.DeltaR(LeadMu4Momentum) ,100,0,1,FullWeight);
            //                            plotFill("ZMass"+FullStringName,ZCandida.M() ,60,60,120,FullWeight);
            //                            plotFill("ht"+FullStringName,ht ,120,0,1200,FullWeight);
            
            
        }//boostedTau loop
        
        
        //###############################################################################################
        //  Doing EleTau Analysis
        //###############################################################################################
    } //End of Tree
    //##############  end of dielectron
    
    
    fout->cd();
    
    map<string, TH1F*>::const_iterator iMap1 = myMap1->begin();
    map<string, TH1F*>::const_iterator jMap1 = myMap1->end();
    
    for (; iMap1 != jMap1; ++iMap1)
    nplot1(iMap1->first)->Write();
    
    map<string, TH2F*>::const_iterator iMap2 = myMap2->begin();
    map<string, TH2F*>::const_iterator jMap2 = myMap2->end();
    
    for (; iMap2 != jMap2; ++iMap2)
    nplot2(iMap2->first)->Write();
    
    fout->Close();
    
    
}
