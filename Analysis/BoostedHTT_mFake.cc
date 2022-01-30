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
    TH2F** HistoMuIso=FuncHistMuIso(year);
    TH2F** HistoMuTrg50=FuncHistMuTrigger_50(year);
    TH2F** HistoMuTrg27=FuncHistMuTrigger_27(year);
    //    TGraphAsymmErrors * HistoMuTrack=FuncHistMuTrack();
    
    //########################################
    // Pileup files
    //########################################
    
    TH1F *  HistoPUData =HistPUData(year_str);
    TH1F * HistoPUMC = new TH1F();
    if (! (fname.find("Data") != string::npos || fname.find("Run") != string::npos ))
        HistoPUMC=HistPUMC(fin);
    
    //    // H->tau tau scale factors
    //    TFile htt_sf_file("data/htt_scalefactors_2017_v2.root");
    //    RooWorkspace *htt_sf = reinterpret_cast<RooWorkspace*>(htt_sf_file.Get("w"));
    //    htt_sf_file.Close();
    
    // Z-pT reweighting
    //        TFile *zpt_file = new TFile("data/zpt_weights_2016_BtoH.root");
    TFile *zpt_file = new TFile(("data/zmm_2d"+year_str+".root").c_str());
    auto zpt_hist = reinterpret_cast<TH2F*>(zpt_file->Get("Ratio2D"));
    
    
    //###############################################################################################
    //  Fix Parameters
    //###############################################################################################
    float MuMass= 0.10565837;
    float eleMass= 0.000511;
    float JetPtCut=30;
    float BJetPtCut=30;
    float muonPtCut=30;
    if (year==2018) muonPtCut=35;
    float leadMuIdCorrection=1;
    float subMuIdCorrection=1;
    float MuIsoCorrection=1;
    float MuTrgCorrection=1;
    float LepCorrection=1;
    float zmasspt_weight=1;
    float LumiWeight = 1;
    float PUWeight = 1;
    float ttbar_rwt = 1;
    
    
    float DeepCSVCut=   1000   ;                  //  Loose  https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
    if (year== 2016) DeepCSVCut =      0.2217   ;
    if (year== 2017) DeepCSVCut =     0.1522   ;
    if (year== 2018) DeepCSVCut =     0.1241    ;
    
    Int_t nentries_wtn = (Int_t) Run_Tree->GetEntries();
    cout<<"nentries_wtn===="<<nentries_wtn<<"\n";
    for (Int_t i = 0; i < nentries_wtn; i++) {
        //                    for (Int_t i = 0; i < 10000; i++) {
        
        Run_Tree->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);
        
        
        //=========================================================================================================
        // Trigger
        bool HLT_Mu27 = ((HLTEleMuX >> 19 & 1)==1); // else if (name.find("HLT_IsoMu27_v") != string::npos) bitEleMuX = 19;
        
        if (! HLT_Mu27) continue;
        plotFill("cutFlowTable",2 ,15,0,15);
        
        //###############################################################################################
        //  GenInfo
        //###############################################################################################
        vector<float>  genInfo=GeneratorInfo();
        float ZBosonPt=genInfo[2];
        float ZBosonMass=genInfo[4];
        
        // BJet veto
        int numBJet=numBJets(BJetPtCut,DeepCSVCut);
        if (numBJet > 0) continue;
        
        plotFill("cutFlowTable",3 ,15,0,15);
        
        //electron veto
        int numele =getNumElectron();
        if (numele > 0) continue;
        plotFill("cutFlowTable",4 ,15,0,15);
        
        //electron veto
        int nummu =getNumMuon();
        if (nummu > 1) continue;
        plotFill("cutFlowTable",5 ,15,0,15);
        float st= getST(JetPtCut);
        //############################################################################################
        //###########       Loop over MuJet events   #################################################
        //############################################################################################
        TLorentzVector LeadMu4Momentum, SubMu4Momentum, LeadTau4Momentum, ZCandida;
        
        
        for (int imu = 0; imu < nMu; ++imu){
            
            if (muPt->at(imu) <= 28 || fabs(muEta->at(imu)) >= 2.4) continue;
            bool MuId=( (muIDbit->at(imu) >> 2 & 1)  && fabs(muD0->at(imu)) < 0.045 && fabs(muDz->at(imu)) < 0.2);
            if (!MuId ) continue;
            
            float IsoLep1Value=muPFChIso->at(imu)/muPt->at(imu);
            if ( (muPFNeuIso->at(imu) + muPFPhoIso->at(imu) - 0.5* muPFPUIso->at(imu) )  > 0.0)
                IsoLep1Value= ( muPFChIso->at(imu) + muPFNeuIso->at(imu) + muPFPhoIso->at(imu) - 0.5* muPFPUIso->at(imu))/muPt->at(imu);
            
            if (IsoLep1Value > 0.15) continue;
            
            plotFill("cutFlowTable",6 ,15,0,15);
            
            LeadMu4Momentum.SetPtEtaPhiM(muPt->at(imu),muEta->at(imu),muPhi->at(imu),MuMass);
            
            leadMuIdCorrection = getCorrFactorMuonId(year, isData,  LeadMu4Momentum.Pt(), LeadMu4Momentum.Eta() ,HistoMuId);
            MuTrgCorrection = getCorrFactorMuonTrg(isData,  LeadMu4Momentum.Pt(), LeadMu4Momentum.Eta() ,HistoMuTrg27);
            MuIsoCorrection = getCorrFactorMuonIso(year, isData,  LeadMu4Momentum.Pt(), LeadMu4Momentum.Eta() ,HistoMuIso);
            
            LepCorrection= leadMuIdCorrection * MuIsoCorrection * MuTrgCorrection;
            
            for (int ibtau = 0; ibtau < nBoostedTau; ++ibtau){
                
                if (boostedTauPt->at(ibtau) < 30 || fabs(boostedTauEta->at(ibtau)) > 2.3 ) continue;
                if (boostedTaupfTausDiscriminationByDecayModeFindingNewDMs->at(ibtau) < 0.5 ) continue;
//                if (boostedTaupfTausDiscriminationByDecayModeFinding->at(ibtau) < 0.5 ) continue;
                if (boostedTauByIsolationMVArun2v1DBnewDMwLTrawNew->at(ibtau) < -0.5) continue;
                if (boostedTauByLooseMuonRejection3->at(ibtau) < 0.5) continue;
                if (boostedTauagainstElectronVLooseMVA62018->at(ibtau) < 0.5) continue;
                
                plotFill("cutFlowTable",7 ,15,0,15);
                LeadTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(ibtau),boostedTauEta->at(ibtau),boostedTauPhi->at(ibtau),boostedTauMass->at(ibtau));
                
                //                if (LeadTau4Momentum.DeltaR(LeadMu4Momentum) < 1.5) continue;
                if (LeadTau4Momentum.DeltaR(LeadMu4Momentum) < 0.8) continue;
                
                plotFill("cutFlowTable",8 ,15,0,15);
                
                float Met=pfMET;
                float Metphi=pfMETPhi;
                float tmass = TMass_F(LeadMu4Momentum.Pt(), LeadMu4Momentum.Px(), LeadMu4Momentum.Py(),  Met,  Metphi);
                float ZMass = (LeadTau4Momentum+LeadMu4Momentum).M();
                //###############################################################################################
                //  Weight
                //###############################################################################################
                float WBosonKFactor=1;
                float WBosonKFactor_ewkUp=1;
                float WBosonKFactor_ewkDown=1;
                
                
                if (!isData){
                    
                    // Lumi weight
                    LumiWeight = getLuminsoity(year) * XSection(sample)*1.0 / HistoTot->GetBinContent(2);
                    
                    float PUMC_=HistoPUMC->GetBinContent(puTrue->at(0)+1);
                    float PUData_=HistoPUData->GetBinContent(puTrue->at(0)+1);
                    
                    if (PUMC_ ==0)
                        cout<<"PUMC_ is zero!!! & num pileup= "<< puTrue->at(0)<<"\n";
                    else
                        PUWeight= PUData_/PUMC_;
                    
                    //  GenInfo
                    vector<float>  genInfo=GeneratorInfo();
                    float WBosonPt=genInfo[1];
                    float ZBosonPt=genInfo[3];
                    float ZBosonMass=genInfo[4];
                    
                    if  (name == "ZL" || name == "ZTT" || name == "ZLL") {
                        
                        if (ZBosonPt > 999) ZBosonPt=999;
                        if (ZBosonMass < 61) ZBosonMass = 61;
                        if (ZBosonMass > 119) ZBosonMass = 119;
                        zmasspt_weight=zpt_hist->GetBinContent(zpt_hist->GetXaxis()->FindBin(ZBosonMass), zpt_hist->GetYaxis()->FindBin(ZBosonPt));
                    }
                    
                    if (name == "W" && (sample.find("_HT_") != string::npos) ){
                        WBosonKFactor= FuncBosonKFactor("W1Cen") + FuncBosonKFactor("W2Cen") * WBosonPt; //HT binned & inclusive K-factor
                    }
                    if (name == "TT") {
                        ttbar_rwt= newTopPtReweight(genInfo[5],genInfo[6],year,"nominal" );
                    }
                }
                
                float FullWeight = LumiWeight*LepCorrection*zmasspt_weight * PUWeight * WBosonKFactor * ttbar_rwt;
                
                plotFill("LumiWeight",LumiWeight ,1000,0,100);
                plotFill("LepCorrection",LepCorrection ,100,0,2);
                plotFill("PUWeight",PUWeight ,200,0,2);
                plotFill("zmasspt_weight",zmasspt_weight ,200,0,2);
                plotFill("WBosonKFactor_weight",WBosonKFactor ,300,0,3);
                plotFill("FullWeight",FullWeight ,300,0,3);
                //###############################################################################################
                
                std::string FullStringName = "";
                
                plotFill("denum"+FullStringName,boostedTauPt->at(ibtau) ,100,0,500,FullWeight);
                plotFill("denum_eta"+FullStringName,boostedTauEta->at(ibtau) ,100,-2.5,2.5,FullWeight);
                plotFill("denum_dR"+FullStringName,LeadTau4Momentum.DeltaR(LeadMu4Momentum) ,100,0,5,FullWeight);
                
                if (boostedTauByVLooseIsolationMVArun2v1DBnewDMwLTNew->at(ibtau) > 0.5){
                    plotFill("numVLoose"+FullStringName,boostedTauPt->at(ibtau) ,100,0,500,FullWeight);
                    plotFill("numVLoose_eta"+FullStringName,boostedTauEta->at(ibtau) ,100,-2.5,2.5,FullWeight);
                    plotFill("numVLoose_dR"+FullStringName,LeadTau4Momentum.DeltaR(LeadMu4Momentum) ,100,0,5,FullWeight);
                    
                }
                
                if (boostedTauByLooseIsolationMVArun2v1DBnewDMwLTNew->at(ibtau) > 0.5){
                    plotFill("numLoose"+FullStringName,boostedTauPt->at(ibtau) ,100,0,500,FullWeight);
                    plotFill("numLoose_eta"+FullStringName,boostedTauEta->at(ibtau) ,100,-2.5,2.5,FullWeight);
                    plotFill("numLoose_dR"+FullStringName,LeadTau4Momentum.DeltaR(LeadMu4Momentum) ,100,0,5,FullWeight);
                    
                }
                if (boostedTauByMediumIsolationMVArun2v1DBnewDMwLTNew->at(ibtau) > 0.5){
                    plotFill("numMedium"+FullStringName,boostedTauPt->at(ibtau) ,100,0,500,FullWeight);
                    plotFill("numMedium_eta"+FullStringName,boostedTauEta->at(ibtau) ,100,-2.5,2.5,FullWeight);
                    plotFill("numMedium_dR"+FullStringName,LeadTau4Momentum.DeltaR(LeadMu4Momentum) ,100,0,5,FullWeight);
                    
                }
                
                if (boostedTauByTightIsolationMVArun2v1DBnewDMwLTNew->at(ibtau) > 0.5){
                    plotFill("numTight"+FullStringName,boostedTauPt->at(ibtau) ,100,0,500,FullWeight);
                    plotFill("numTight_eta"+FullStringName,boostedTauEta->at(ibtau) ,100,-2.5,2.5,FullWeight);
                    plotFill("numTight_dR"+FullStringName,LeadTau4Momentum.DeltaR(LeadMu4Momentum) ,100,0,5,FullWeight);
                    
                }
                
                plotFill("MT"+FullStringName,tmass ,100,0,500,FullWeight);
                plotFill("Met"+FullStringName,Met ,100,0,500,FullWeight);
                plotFill("ZMass"+FullStringName,ZMass ,100,0,500,FullWeight);
                plotFill("st"+FullStringName,st ,100,0,2000,FullWeight);
                plotFill("LepPt"+FullStringName,LeadMu4Momentum.Pt() ,100,0,1000,FullWeight);
                
                
            }//boostedTau loop
            
        } // leading muon
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
