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
    Run_Tree= Xttree(InputFile,"tautau_tree");
    
    //    auto HistoTot = reinterpret_cast<TH1D*>(InputFile->Get("ggNtuplizer/hEvents"));
    TH1F * HistoTot = (TH1F*) InputFile->Get("hcount");
    auto fout = new TFile(filename.c_str(), "RECREATE");
    
    myMap1 = new std::map<std::string, TH1F*>();
    myMap2 = new map<string, TH2F*>();
    
    TTree * outTr=  new TTree("tautau_tree","tautau_tree");
    
    
    //########################################
    // Pileup files
    //########################################
    
    TH1F *  HistoPUData =HistPUData(year_str);
    TH1F * HistoPUMC = new TH1F();
    if (! (fname.find("Data") != string::npos || fname.find("Run") != string::npos ))
        HistoPUMC=HistPUMC(InputFile);
    
    // Z-pT reweighting
    //        TFile *zpt_file = new TFile("data/zpt_weights_2016_BtoH.root");
    TFile *zpt_file = new TFile(("data/zmm_2d"+year_str+".root").c_str());
    auto zpt_hist = reinterpret_cast<TH2F*>(zpt_file->Get("Ratio2D"));
    
    //###############################################################################################
    // 2D TRigger Efficiency
    //###############################################################################################
    auto trgEff_HT = TFile::Open(("data/ht_trgEff_2D_"+year_str+".root").c_str());
    TH2F * triggerEff_HT = (TH2F *) trgEff_HT->Get("TrgEfficiency2D");
    
    auto trgEff_MET = TFile::Open(("data/met_trgEff_2D_"+year_str+".root").c_str());
    TH2F * triggerEff_MET = (TH2F *) trgEff_MET->Get("TrgEfficiency2D");
    
    
    //###############################################################################################
    // Parameters
    //###############################################################################################
    float MuMass= 0.10565837;
    float eleMass= 0.000511;
    float JetPtCut=30;
    float BJetPtCut=20;
    
    float DeepCSVCut=   1000   ;                  //  loose  https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
    if (year== 2016) DeepCSVCut =     0.8953  ;
    if (year== 2017) DeepCSVCut =     0.8001  ;
    if (year== 2018) DeepCSVCut =    0.7527   ;
    
    float LeptonIsoCut=0.15;
    bool debug= false;
    float LumiWeight = 1;
    float PUWeight = 1;
    float LepCorrection=1;
    float zmasspt_weight=1;
    
    float lep1Pt_=-10;
    float lep2Pt_=-10;
    float vis_mass=-10;
    float LeadJetPt = -10;
    float dR_Z_jet=-10;
    bool lep1IsoPass,lep2IsoPass,OS,SS;
    float tmass,ht,st,Met,FullWeight, dR_lep_lep, Metphi,BoostedTauRawIso, higgs_pT, higgs_m, m_sv_, wtnom_zpt_weight;
    // Trigger
    bool PassTrigger_37;
    bool PassTrigger_38;
    bool PassTrigger_39;
    bool PassTrigger_40;
    bool PassTrigger_41;
    bool PassTrigger_42;
    bool PassTrigger_43;
    bool PassTrigger_44;
    bool PassTrigger_20;
    bool PassTrigger_21;
    bool PassTrigger_22;
    
    
    outTr->Branch("evtwt",&FullWeight,"evtwt/F");
    outTr->Branch("zmasspt_weight",&zmasspt_weight,"zmasspt_weight/F");
    outTr->Branch("lep1Pt",&lep1Pt_,"lep1Pt/F");
    outTr->Branch("lep2Pt",&lep2Pt_,"lep2Pt/F");
    outTr->Branch("lep1IsoPass",&lep1IsoPass,"lep1IsoPass/O");
    outTr->Branch("lep2IsoPass",&lep2IsoPass,"lep2IsoPass/O");
    outTr->Branch("OS",&OS,"OS/O");
    outTr->Branch("SS",&SS,"SS/O");
    outTr->Branch("vis_mass",&vis_mass,"vis_mass/F");
    outTr->Branch("tmass",&tmass,"tmass/F");
    outTr->Branch("ht",&ht,"ht/F");
    outTr->Branch("st",&st,"st/F");
    outTr->Branch("Met",&Met,"Met/F");
    outTr->Branch("LeadJetPt",&LeadJetPt,"LeadJetPt/F");
    outTr->Branch("dR_lep_lep",&dR_lep_lep,"dR_lep_lep/F");
    outTr->Branch("BoostedTauRawIso",&BoostedTauRawIso,"BoostedTauRawIso/F");
    outTr->Branch("higgs_pT",&higgs_pT,"higgs_pT/F");
    outTr->Branch("higgs_m",&higgs_m,"higgs_m/F");
    outTr->Branch("m_sv",&m_sv_,"m_sv/F");
    outTr->Branch("PassTrigger_37",&PassTrigger_37,"PassTrigger_37/O");
    outTr->Branch("PassTrigger_38",&PassTrigger_38);
    outTr->Branch("PassTrigger_39",&PassTrigger_39);
    outTr->Branch("PassTrigger_40",&PassTrigger_40);
    outTr->Branch("PassTrigger_41",&PassTrigger_41);
    outTr->Branch("PassTrigger_42",&PassTrigger_42);
    outTr->Branch("PassTrigger_43",&PassTrigger_43);
    outTr->Branch("PassTrigger_44",&PassTrigger_44);
    outTr->Branch("PassTrigger_20",&PassTrigger_20);
    outTr->Branch("PassTrigger_21",&PassTrigger_21);
    outTr->Branch("PassTrigger_22",&PassTrigger_22);
    
    
    
    Int_t nentries_wtn = (Int_t) Run_Tree->GetEntries();
    cout<<"nentries_wtn===="<<nentries_wtn<<"\n";
    for (Int_t i = 0; i < nentries_wtn; i++) {
        
        Run_Tree->GetEntry(i);
        if (i % 1000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);
        
        plotFill("cutFlowTable",1 ,15,0,15);
        //=========================================================================================================
        // Lowest unprescaled trigger           2016                         2017                                     2018
        
        //           HLT_AK8PFJet360_TrimMass30_v                      HLT_AK8PFJet400_TrimMass30(36.75/ 41.54)   HLT_AK8PFJet400_TrimMass30_v
        //           HLT_AK8PFJet500 (not in yet 33.64/36.47 )         HLT_AK8PFJet500 (not in yet)               HLT_AK8PFJet500 (not in yet)
        //           HLT_PFHT300_PFMET110_v                            HLT_PFHT500_PFMET100_PFMHT100_IDT          HLT_PFHT500_PFMET100_PFMHT100_IDT
        //           HLT_PFHT900_v                                     HLT_PFHT1050_v                             HLT_PFHT1050_v
        
        
        
        //2016
        PassTrigger_21 = ((HLTJet >> 21 & 1)==1); //HLT_AK8PFJet360_TrimMass30_v // only 2016?
        PassTrigger_22 = ((HLTJet >> 22 & 1)==1); //HLT_PFHT300_PFMET110_v // only 2016?
        
        
        //2017 and 2018
        PassTrigger_40 = ((HLTJet >> 40 & 1)==1); //HLT_AK8PFJet400_TrimMass30_v //HLT_AK8PFJet400_TrimMass30_v
        PassTrigger_39 = ((HLTJet >> 39 & 1)==1); //HLT_PFHT500_PFMET100_PFMHT100_IDTight_v
        
        // Trigger
        //        https://cmsoms.cern.ch/cms/triggers/hlt_trigger_rates?cms_run=325175
        //https://twiki.cern.ch/twiki/bin/viewauth/CMS/HLTPathsRunIIList
        PassTrigger_20 = ((HLTJet >> 20 & 1)==1); //HLT_AK8PFHT700_TrimR0p1PT0p3Mass50_v // only 2016?
        PassTrigger_37 = ((HLTJet >> 37 & 1)==1); //HLT_AK8PFHT800_TrimMass50_v // not effective
        PassTrigger_38 = ((HLTJet >> 38 & 1)==1); //HLT_PFHT1050_v  NOT Effective at all
        PassTrigger_41 = ((HLTJet >> 41 & 1)==1);// HLT_AK8PFJet420_TrimMass30_v  // not needed as HLT_AK8PFJet400_TrimMass30_v is available
        PassTrigger_42 = ((HLTJet >> 42 & 1)==1);//HLT_PFHT500_PFMET110_PFMHT110_IDTight_v
        PassTrigger_43 = ((HLTJet >> 43 & 1)==1); // HLT_AK8PFHT850_TrimMass50_v  HLT_AK8PFHT800_TrimMass50_v is OK as well
        PassTrigger_44 = ((HLTJet >> 44 & 1)==1); //HLT_AK8PFHT900_TrimMass50_v
        //        //              else if (name.find("HLT_Mu50_v")                                          != string::npos) bitEleMuX = 21;
        //        // else if (name.find("HLT_IsoMu27_v") != string::npos) bitEleMuX = 19; // 2017
        //        else if (name.find("HLT_PFMET110_PFMHT110_IDTight_v")                            != string::npos) bitJet = 26;
        //        else if (name.find("HLT_PFMET120_PFMHT120_IDTight_v")                            != string::npos) bitJet = 27;
        //              else if (name.find("HLT_PFHT300_PFMET110_v")                                     != string::npos) bitJet = 22; //2016 // HTMHT
        // HLT_PFHT500_PFMET100_PFMHT100_IDTight_v //2017 // HTMHT
        
        plotFill("cutFlowTable",2 ,15,0,15);
        //=========================================================================================================
        // MET Filters
        // Here we apply MET Filters
        // Here we apply prefire weights
        
        //=========================================================================================================
        //MET Shape systematics
        Met=pfMET;
        Metphi=pfMETPhi;
        if (syst == "met_JESUp") {Met = met_JESUp; Metphi=metphi_JESUp;}
        if (syst == "met_JESDown") {Met = met_JESDown;  Metphi=metphi_JESDown;}
        if (syst == "met_UESUp") {Met = met_UESUp;  Metphi=metphi_UESUp;}
        if (syst == "met_UESDown") {Met = met_UESDown;  Metphi=metphi_UESDown;}
        
        TLorentzVector LeadTau4Momentum,SubTau4Momentum, Z4Momentum, Met4Momentum;
        //=========================================================================================================
        // Lead tau selection
        int idx_leadtau= leadtauIndex;
        
        if (boostedTauPt->at(idx_leadtau) <= 30 || fabs(boostedTauEta->at(idx_leadtau)) >= 2.3 ) continue;
        if (boostedTaupfTausDiscriminationByDecayModeFinding->at(idx_leadtau) < 0.5 ) continue;
        //        if (boostedTauagainstElectronVLooseMVA62018->at(idx_leadtau) < 0.5) continue;
        //        if (boostedTauByLooseMuonRejection3->at(idx_leadtau) < 0.5) continue;
        LeadTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(idx_leadtau),boostedTauEta->at(idx_leadtau),boostedTauPhi->at(idx_leadtau),boostedTauMass->at(idx_leadtau));
        plotFill("cutFlowTable",3 ,15,0,15);
        
        //=========================================================================================================
        // sublead Tau selection
        int idx_subleadtau= subtauIndex;
        
        if (boostedTauPt->at(idx_subleadtau) <= 30 || fabs(boostedTauEta->at(idx_subleadtau)) >= 2.3 ) continue;
        if (boostedTaupfTausDiscriminationByDecayModeFinding->at(idx_subleadtau) < 0.5 ) continue;
        //        if (boostedTauagainstElectronVLooseMVA62018->at(idx_subleadtau) < 0.5) continue;
        //        if (boostedTauByLooseMuonRejection3->at(idx_subleadtau) < 0.5) continue;
        
        SubTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(idx_subleadtau),boostedTauEta->at(idx_subleadtau),boostedTauPhi->at(idx_subleadtau),boostedTauMass->at(idx_subleadtau));
        plotFill("cutFlowTable",4 ,15,0,15);
        
        dR_lep_lep= SubTau4Momentum.DeltaR(LeadTau4Momentum);
        TLorentzVector LeadJet= getLeadJet(LeadTau4Momentum, SubTau4Momentum);
        
        //=========================================================================================================
        // Cut on AK8 (for trigger purposes)
        float AK8Pt=0;
        float AK8Mass=0;
        float AK8Eta=100;
        
        float PFHT= getST(JetPtCut);
        float PFMET=pfMET;
        float MHT=getMHT(JetPtCut);
        st= getST(JetPtCut);
        ht= getHT(JetPtCut, LeadTau4Momentum, SubTau4Momentum);
        
        float TriggerWeight = 1;
        float _cut_AK8Pt_,_cut_AK8Mass_,_cut_PFHT_,_cut_PFMET_,_cut_PFMHT_, _cut_PFMETMHT_, _cut_st_;
        bool _Pass_AK8_Trigger_, _Pass_METHT_Trigger_;
        
        if (year== 2016){
            
            _cut_AK8Pt_ = 450;
            _cut_AK8Mass_ = 30;
            _cut_PFHT_ = 400;
            _cut_PFMET_ = 180;
            _cut_PFMHT_= 0;
            _cut_PFMETMHT_ = 180;
            _Pass_AK8_Trigger_=PassTrigger_21;
            _Pass_METHT_Trigger_=PassTrigger_22;
            _cut_st_ = 400;
            
        } else if (year== 2017){
            
            _cut_AK8Pt_ = 450;
            _cut_AK8Mass_ = 30;
            _cut_PFHT_ = 700;
            _cut_PFMET_ = 120;
            _cut_PFMHT_= 120;
            _cut_PFMETMHT_ = 280;
            _Pass_AK8_Trigger_=PassTrigger_40;
            _Pass_METHT_Trigger_=PassTrigger_39;
            _cut_st_ = 600;
            
            
        } else if (year== 2018){
            
            _cut_AK8Pt_ = 450;
            _cut_AK8Mass_ = 30;
            _cut_PFHT_ = 700;
            _cut_PFMET_ = 120;
            _cut_PFMHT_= 120;
            _cut_PFMETMHT_ = 280;
            _Pass_AK8_Trigger_=PassTrigger_40;
            _Pass_METHT_Trigger_=PassTrigger_39;
            _cut_st_ = 600;
            
        }
        
        for (int ijet=0; ijet < nAK8Jet ; ijet ++){
            
            AK8Pt=AK8JetPt->at(ijet);
            AK8Mass=AK8JetSoftDropMass->at(ijet);
            AK8Eta=fabs(AK8JetEta->at(ijet));
            
            if (AK8Pt > 450 && AK8Mass > 30 && AK8Eta < 2.5) break;
            
        }
        
        
        bool passing= true;
        
         if ( (!isData ||  (isData && _Pass_AK8_Trigger_)) &&  AK8Pt > _cut_AK8Pt_ && AK8Mass > _cut_AK8Mass_ && AK8Eta < 2.5){
            TriggerWeight = getTriggerWeight(year, isData,  AK8Pt , AK8Mass ,triggerEff_HT);
            passing= true;
        }
        else if ( (!isData ||  (isData && _Pass_METHT_Trigger_)) &&  PFHT > _cut_PFHT_ && PFMET > _cut_PFMET_ && MHT> _cut_PFMHT_ && PFMET+MHT > _cut_PFMETMHT_){
            TriggerWeight = getTriggerWeight(year, isData,  PFHT,PFMET,MHT ,triggerEff_MET);
            passing= true;
        }
        else {
            passing = false;
        }
        
        if (! passing) continue;
        
        //=========================================================================================================
        // Event Selection
        //=========================================================================================================
        
        if( dR_lep_lep > 0.8 || dR_lep_lep < 0.1) continue;
        plotFill("cutFlowTable",8 ,15,0,15);
        
        tmass = TMass_F(LeadTau4Momentum.Pt(), LeadTau4Momentum.Px(), LeadTau4Momentum.Py(),  Met,  Metphi);
        if (tmass > 200) continue;
        plotFill("cutFlowTable",9 ,15,0,15);
        
        if (m_sv < 50) continue;
        plotFill("cutFlowTable",10 ,15,0,15);
        
        // BJet veto
        //        int numBJet=numBJets(BJetPtCut,DeepCSVCut);
        //        if (numBJet > 0) continue;
        //        plotFill("cutFlowTable",8 ,15,0,15);
        
        
//        electron veto
        int numele =getNumElectron();
        if (numele > 0) continue;
        plotFill("cutFlowTable",11 ,15,0,15);
        
        //muon veto
        int numMu =getNumMuon();
        if (numMu > 0) continue;
        plotFill("cutFlowTable",12 ,15,0,15);

        //st cut
//        if (st < _cut_st_) continue;
        plotFill("cutFlowTable",13 ,15,0,15);

        //=========================================================================================================
        
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
            float ZBosonPt=genInfo[3];
            float ZBosonMass=genInfo[4];
            
            if  (name == "ZL" || name == "ZTT" || name == "ZLL") {
                
                if (ZBosonPt > 999) ZBosonPt=999;
                if (ZBosonMass < 61) ZBosonMass = 61;
                if (ZBosonMass > 119) ZBosonMass = 119;
                zmasspt_weight=zpt_hist->GetBinContent(zpt_hist->GetXaxis()->FindBin(ZBosonMass), zpt_hist->GetYaxis()->FindBin(ZBosonPt));
            }
        }
        
        plotFill("LumiWeight",LumiWeight ,1000,0,10000);
        plotFill("LepCorrection",LepCorrection ,100,0,2);
        plotFill("TriggerWeight",TriggerWeight ,100,0,1);
        plotFill("PUWeight",PUWeight ,200,0,2);
        plotFill("zmasspt_weight",zmasspt_weight ,200,0,2);
        
        //###############################################################################################
        //  tree branches
        //###############################################################################################
        
        Met4Momentum.SetPtEtaPhiM(pfMET, 0, pfMETPhi, 0);
        Z4Momentum=SubTau4Momentum+LeadTau4Momentum;
        TLorentzVector higgs = SubTau4Momentum+LeadTau4Momentum +Met4Momentum;
        
        higgs_pT = higgs.Pt();
        if (higgs_pT < 250 ) continue;
        plotFill("cutFlowTable",14 ,15,0,15);
        
        higgs_m = higgs.M();
        OS = boostedTauCharge->at(idx_leadtau) * boostedTauCharge->at(idx_subleadtau) < 0;
        SS =  boostedTauCharge->at(idx_leadtau) * boostedTauCharge->at(idx_subleadtau) > 0;
        lep1IsoPass = boostedTauByVLooseIsolationMVArun2v1DBoldDMwLTNew->at(idx_leadtau) > 0.5;
        lep2IsoPass = boostedTauByVLooseIsolationMVArun2v1DBoldDMwLTNew->at(idx_subleadtau) > 0.5;
        
        lep1Pt_=boostedTauPt->at(idx_leadtau);
        lep2Pt_=boostedTauPt->at(idx_subleadtau);
        vis_mass=Z4Momentum.M();
        LeadJetPt = LeadJet.Pt();
        dR_Z_jet=LeadJet.DeltaR(Z4Momentum);
        BoostedTauRawIso=boostedTauByIsolationMVArun2v1DBoldDMwLTraw->at(idx_subleadtau);
        m_sv_=m_sv;
        //  Weights
        FullWeight = LumiWeight*LepCorrection * TriggerWeight*zmasspt_weight;
        
        // Fill the tree
        outTr->Fill();
        
    } //End of Tree
    
    
    fout->cd();
    map<string, TH1F*>::const_iterator iMap1 = myMap1->begin();
    map<string, TH1F*>::const_iterator jMap1 = myMap1->end();
    
    for (; iMap1 != jMap1; ++iMap1)
    nplot1(iMap1->first)->Write();
    outTr->Write();
    
    map<string, TH2F*>::const_iterator iMap2 = myMap2->begin();
    map<string, TH2F*>::const_iterator jMap2 = myMap2->end();
    
    for (; iMap2 != jMap2; ++iMap2)
    nplot2(iMap2->first)->Write();
    
    fout->Close();
}


