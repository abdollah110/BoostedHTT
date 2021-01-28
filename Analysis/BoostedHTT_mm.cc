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
    auto InputFile = TFile::Open(fname.c_str());
    std::cout << "Loading Ntuple..." << std::endl;
    TTree *  Run_Tree;
    Run_Tree= Xttree(InputFile,"EventTree");
    
    //    auto HistoTot = reinterpret_cast<TH1D*>(InputFile->Get("ggNtuplizer/hEvents"));
    TH1F * HistoTot = (TH1F*) InputFile->Get("hcount");
    auto fout = new TFile(filename.c_str(), "RECREATE");
    
    myMap1 = new std::map<std::string, TH1F*>();
    myMap2 = new map<string, TH2F*>();
    
    //########################################
    // Muon Id, Iso, Trigger and Tracker Eff files
    //########################################
    TH2F** HistoMuId=FuncHistMuId(year);
    TH2F** HistoMuTrg=FuncHistMuTrigger_50(year);
    
    //########################################
    // Pileup files
    //########################################
    
    TH1F *  HistoPUData =HistPUData(year_str);
    TH1F * HistoPUMC = new TH1F();
    if (! (fname.find("Data") != string::npos || fname.find("Run") != string::npos ))
        HistoPUMC=HistPUMC(InputFile);
    
    
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
    std::vector<Float_t> PT_binning{0,250,300,350,400,500,1500};
    std::vector<Float_t> Mass_binning{60,85,95,120};
    
    float LeptonIsoCut=0.20;
    bool debug= false;
    
    
    Int_t nentries_wtn = (Int_t) Run_Tree->GetEntries();
    cout<<"nentries_wtn===="<<nentries_wtn<<"\n";
    for (Int_t i = 0; i < nentries_wtn; i++) {
        
        Run_Tree->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);
        
        
        //=========================================================================================================
        // Trigger
        bool PassTrigger = ((HLTEleMuX >> 21 & 1)==1);//if (name.find("HLT_Mu50_v")   != string::npos) bitEleMuX = 21;
        
        if (! PassTrigger) continue;
        plotFill("cutFlowTable",2 ,15,0,15);
        
        
        // BJet veto
        int numBJet=numBJets(BJetPtCut,DeepCSVCut);
        if (numBJet > 0) continue;
        
        //electron veto
        int numele =getNumElectron();
        if (numele > 0) continue;
        
        
        //############################################################################################
        //###########       Loop over MuJet events   #################################################
        //############################################################################################
        
        TLorentzVector LeadMu4Momentum, SubMu4Momentum, ZCandida;
        
        for (int imu = 0; imu < nMu; ++imu){
            
            if (muPt->at(imu) <= 53 || fabs(muEta->at(imu)) >= 2.4) continue;
            bool MuId=( (muIDbit->at(imu) >> 2 & 1)  && fabs(muD0->at(imu)) < 0.045 && fabs(muDz->at(imu)) < 0.2);
            if (!MuId ) continue;
            LeadMu4Momentum.SetPtEtaPhiM(muPt->at(imu),muEta->at(imu),muPhi->at(imu),MuMass);
            
            for (int jmu = imu+1; jmu < nMu; ++jmu){
                if (muPt->at(jmu) <= 10 || fabs(muEta->at(jmu)) >= 2.4) continue;
                bool MuId_sub=( (muIDbit->at(jmu) >> 2 & 1)  && fabs(muD0->at(jmu)) < 0.045 && fabs(muDz->at(jmu)) < 0.2);
                if (!MuId_sub ) continue;
                SubMu4Momentum.SetPtEtaPhiM(muPt->at(jmu),muEta->at(jmu),muPhi->at(jmu),MuMass);
                
                ZCandida=SubMu4Momentum+LeadMu4Momentum;
                if (ZCandida.M() < 60 ||  ZCandida.M() > 120 ) continue;
                
                float ht= getHT(JetPtCut, LeadMu4Momentum, SubMu4Momentum);
                float st= getST(JetPtCut);
                if (ht < 200) continue;
                
                if (SubMu4Momentum.DeltaR(LeadMu4Momentum) > 0.8 || SubMu4Momentum.DeltaR(LeadMu4Momentum) < 0.1) continue;
                //###############################################################################################
                //  Weight
                //###############################################################################################
                float LumiWeight = 1;
                float PUWeight = 1;
                float LeadMuIdCorrection = getCorrFactorMuonId(year, isData,  LeadMu4Momentum.Pt(), LeadMu4Momentum.Eta() ,HistoMuId);
                float SubMuIdCorrection = getCorrFactorMuonId(year, isData,  SubMu4Momentum.Pt(), SubMu4Momentum.Eta() ,HistoMuId);
                float MuTrgCorrection = getCorrFactorMuonTrg(isData,  LeadMu4Momentum.Pt(), LeadMu4Momentum.Eta() ,HistoMuTrg);
                float LepCorrection= LeadMuIdCorrection *SubMuIdCorrection * MuTrgCorrection;
                float ZBosonPt=-1;
                float ZBosonMass=-1;
                float WBosonKFactor=1;
                float WBosonPt=0;
                
                if (!isData){
                    
                    // Lumi weight
                    LumiWeight = getLuminsoity(year) * XSection(sample)*1.0 / HistoTot->GetBinContent(2);
                    
                    float PUMC_=HistoPUMC->GetBinContent(puTrue->at(0)+1);
                    float PUData_=HistoPUData->GetBinContent(puTrue->at(0)+1);
                    
                    if (PUMC_ ==0)
                        cout<<"PUMC_ is zero!!! & num pileup= "<< puTrue->at(0)<<"\n";
                    else
                        PUWeight= PUData_/PUMC_;
                    
                    vector<float>  genInfo=GeneratorInfo();
                    WBosonPt=genInfo[1];
                    ZBosonPt=genInfo[3];
                    ZBosonMass=genInfo[4];
                    
                    if (name == "W" && (sample.find("_HT_") != string::npos) ){
                        WBosonKFactor= FuncBosonKFactor("W1Cen") + FuncBosonKFactor("W2Cen") * WBosonPt; //HT binned & inclusive K-factor
                    }
                    
                    
                }
                
                plotFill("LumiWeight",LumiWeight ,1000,0,100);
                plotFill("LepCorrection",LepCorrection ,100,0,2);
                plotFill("PUWeight",PUWeight ,200,0,2);
                plotFill("WBosonKFactor",WBosonKFactor ,200,0,2);
                
                //###############################################################################################
                //  Gen Info
                //###############################################################################################
                
                //###############################################################################################
                //  Charge Categorization
                //###############################################################################################
                
                float chargeMuMu= muCharge->at(imu) * muCharge->at(jmu);
                
                const int size_q = 2;
                bool q_OS = chargeMuMu < 0;
                bool q_SS =  chargeMuMu > 0;
                
                bool Q_category[size_q] = {q_OS, q_SS};
                std::string Q_Cat[size_q] = {"_OS", "_SS"};
                
                
                //###############################################################################################
                
                for (int iq = 0; iq < size_q; iq++) {
                    if (Q_category[iq]) {
                        
                        
                        float FullWeight = LumiWeight*LepCorrection * PUWeight * WBosonKFactor;
                        std::string FullStringName = Q_Cat[iq] ;
                        
                        plotFill("dR"+FullStringName,SubMu4Momentum.DeltaR(LeadMu4Momentum) ,100,0,1,FullWeight);
                        plotFill("ht"+FullStringName,ht ,150,0,1500,FullWeight);
                        plotFill("st"+FullStringName,st ,150,0,1500,FullWeight);
                        plotFill("ZMass"+FullStringName,ZCandida.M() ,60,60,120,FullWeight);
                        plotFill("ZPt"+FullStringName,ZCandida.Pt() ,100,0,1000,FullWeight);
                        plotFill("2DZMassPt"+FullStringName,ZCandida.M(),ZCandida.Pt(),Mass_binning.size()-1,&Mass_binning[0],PT_binning.size()-1,&PT_binning[0], FullWeight);
                        plotFill("genZMass"+FullStringName,ZBosonMass ,40,0,200,FullWeight);
                        plotFill("genZPt"+FullStringName,ZBosonPt ,100,0,1000,FullWeight);
                        plotFill("genZMass-recoZMass"+FullStringName,ZBosonMass-ZCandida.M(),100,-200,200,FullWeight);
                        plotFill("genZPt-recoZPt"+FullStringName,ZBosonPt-ZCandida.Pt() ,100,-500,500,FullWeight);
                        if (ZCandida.M() < 85)
                            plotFill("ZPt_Below"+FullStringName,ZCandida.Pt() ,100,0,1000,FullWeight);
                        if (ZCandida.M() > 85 && ZCandida.M() < 95)
                            plotFill("ZPt_OnMass"+FullStringName,ZCandida.Pt() ,100,0,1000,FullWeight);
                        if (ZCandida.M() > 95)
                            plotFill("ZPt_Above"+FullStringName,ZCandida.Pt() ,100,0,1000,FullWeight);
                        
                        
                    }
                }
                
                
            }//boostedTau loop
        }//muon loop
        
        
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
