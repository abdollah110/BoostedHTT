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
    //    float luminosity=    35867;
    //    float luminosity=    41530;
    
    
    float leadPt_=-10;
    float subPt_=-10;
    float vis_mass=-10;
    float LeadJetPt = -10;
    float dR_Z_jet=-10;
    bool PassLead,PassSub,PassLeadCombined,PassSubCombined,PassLeadCharged,PassSubCharged,OS,SS;
    float tmass,ht,st,Met,FullWeight, dR_tau_tau, Metphi,BoostedTauRawIso, higgs_pT, higgs_m, m_sv_, wtnom_zpt_weight;
            // Trigger
        bool PassTrigger_37;
        bool PassTrigger_38;
        bool PassTrigger_39;
        bool PassTrigger_40;
        bool PassTrigger_41;
        bool PassTrigger_42;
        bool PassTrigger_43;
        bool PassTrigger_44;

    
    outTr->Branch("evtwt",&FullWeight,"evtwt/F");
    //    outTr->Branch("evtwtZpt",&wtnom_zpt_weight,"evtwtZPt/F");
    outTr->Branch("leadPt",&leadPt_,"leadPt/F");
    outTr->Branch("subPt",&subPt_,"subPt/F");
    outTr->Branch("PassLead",&PassLead,"PassLead/O");
    outTr->Branch("PassSub",&PassSub,"PassSub/O");
    outTr->Branch("PassLeadCombined",&PassLeadCombined,"PassLeadCombined/O");
    outTr->Branch("PassSubCombined",&PassSubCombined,"PassSubCombined/O");
    outTr->Branch("PassLeadCharged",&PassLeadCharged,"PassLeadCharged/O");
    outTr->Branch("PassSubCharged",&PassSubCharged,"PassSubCharged/O");
    outTr->Branch("OS",&OS,"OS/O");
    outTr->Branch("SS",&SS,"SS/O");
    outTr->Branch("vis_mass",&vis_mass,"vis_mass/F");
    outTr->Branch("tmass",&tmass,"tmass/F");
    outTr->Branch("ht",&ht,"ht/F");
    outTr->Branch("st",&st,"st/F");
    outTr->Branch("Met",&Met,"Met/F");
    outTr->Branch("LeadJetPt",&LeadJetPt,"LeadJetPt/F");
    outTr->Branch("dR_tau_tau",&dR_tau_tau,"dR_tau_tau/F");
    //    outTr->Branch("IsoLepValue",&IsoLepValue,"IsoLepValue/F");
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
    
    
    
    Int_t nentries_wtn = (Int_t) Run_Tree->GetEntries();
    cout<<"nentries_wtn===="<<nentries_wtn<<"\n";
    for (Int_t i = 0; i < nentries_wtn; i++) {
        
        Run_Tree->GetEntry(i);
        if (i % 1000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);
        
        plotFill("cutFlowTable",1 ,15,0,15);
        //=========================================================================================================
        // Trigger
         PassTrigger_37 = ((HLTJet >> 37 & 1)==1); //HLT_AK8PFHT800_TrimMass50_v // not effective
         PassTrigger_38 = ((HLTJet >> 38 & 1)==1); //HLT_PFHT1050_v  NOT Effective at all
         PassTrigger_39 = ((HLTJet >> 39 & 1)==1); //HLT_PFHT500_PFMET100_PFMHT100_IDTight_v
         PassTrigger_40 = ((HLTJet >> 40 & 1)==1); //HLT_AK8PFJet400_TrimMass30_v //HLT_AK8PFJet400_TrimMass30_v
         PassTrigger_41 = ((HLTJet >> 41 & 1)==1);// HLT_AK8PFJet420_TrimMass30_v
         PassTrigger_42 = ((HLTJet >> 42 & 1)==1);//HLT_PFHT500_PFMET110_PFMHT110_IDTight_v
         PassTrigger_43 = ((HLTJet >> 43 & 1)==1); // HLT_AK8PFHT850_TrimMass50_v
         PassTrigger_44 = ((HLTJet >> 44 & 1)==1); //HLT_AK8PFHT900_TrimMass50_v
        //        //              else if (name.find("HLT_Mu50_v")                                          != string::npos) bitEleMuX = 21;
        //        // else if (name.find("HLT_IsoMu27_v") != string::npos) bitEleMuX = 19; // 2017
        //        if (!(PassTrigger_40 || PassTrigger_39)) continue;
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
        if (Met < 50 ) continue ;
        
        TLorentzVector LeadTau4Momentum,SubTau4Momentum, Z4Momentum, Met4Momentum;
        //=========================================================================================================
        // Lead tau selection
        int idx_leadtau= leadtauIndex;
        
        if (boostedTauPt->at(idx_leadtau) <= 40 || fabs(boostedTauEta->at(idx_leadtau)) >= 2.3 ) continue;
        if (boostedTaupfTausDiscriminationByDecayModeFinding->at(idx_leadtau) < 0.5 ) continue;
        if (boostedTauagainstElectronVLooseMVA62018->at(idx_leadtau) < 0.5) continue;
        if (boostedTauByLooseMuonRejection3->at(idx_leadtau) < 0.5) continue;
        LeadTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(idx_leadtau),boostedTauEta->at(idx_leadtau),boostedTauPhi->at(idx_leadtau),boostedTauMass->at(idx_leadtau));
        plotFill("cutFlowTable",3 ,15,0,15);
        
//        TLorentzVector leadMatch= getMatchedGenTau(LeadTau4Momentum);
//        plotFill("GenMatchedLeadTau",leadMatch.DeltaR(LeadTau4Momentum) ,20,0,1);
//        vector<float> leadRecoMatch= getMatchedRecoTau(LeadTau4Momentum);
        
        //=========================================================================================================
        // sublead Tau selection
        int idx_subleadtau= subtauIndex;
        
        if (boostedTauPt->at(idx_subleadtau) <= 40 || fabs(boostedTauEta->at(idx_subleadtau)) >= 2.3 ) continue;
        if (boostedTaupfTausDiscriminationByDecayModeFinding->at(idx_subleadtau) < 0.5 ) continue;
        if (boostedTauagainstElectronVLooseMVA62018->at(idx_subleadtau) < 0.5) continue;
        if (boostedTauByLooseMuonRejection3->at(idx_subleadtau) < 0.5) continue;
        
        SubTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(idx_subleadtau),boostedTauEta->at(idx_subleadtau),boostedTauPhi->at(idx_subleadtau),boostedTauMass->at(idx_subleadtau));
        plotFill("cutFlowTable",4 ,15,0,15);
        
//        TLorentzVector subMatch= getMatchedGenTau(SubTau4Momentum);
//        plotFill("GenMatchedSubTau",subMatch.DeltaR(SubTau4Momentum) ,20,0,1);
//        vector<float> subRecoMatch= getMatchedRecoTau(SubTau4Momentum);
        
        dR_tau_tau= SubTau4Momentum.DeltaR(LeadTau4Momentum);
        
//        //=========================================================================================================
//        //  Tau POG tests
//        //=========================================================================================================
//        int numIso=0;
//        int numIsoOverLap=0;
//        float EnergyIso=0;
//        float EnergyIsoOverLap=0;
//
//        //=========== Charge PFCandidates==========
//        for (int i=0; i< boostedTauIsolationPFCands->at(idx_leadtau).size(); i++){
//            numIso++;
//            EnergyIso +=boostedTauIsolationPFCands->at(idx_leadtau)[i];
//            // overlap with subleading SignalPFCandidates
//            for (int j=0; j< boostedTauSignalPFCands->at(idx_subleadtau).size(); j++){
//                if (boostedTauIsolationPFCands->at(idx_leadtau)[i] ==  boostedTauSignalPFCands->at(idx_subleadtau)[j]) {
//                    numIsoOverLap++;
//                    EnergyIsoOverLap +=boostedTauIsolationPFCands->at(idx_leadtau)[i];
//                }
//            }
//            // overlap with subleading IsoPFCandidates
//            for (int j=0; j< boostedTauIsolationPFCands->at(idx_subleadtau).size(); j++){
//                if (boostedTauIsolationPFCands->at(idx_leadtau)[i] ==  boostedTauIsolationPFCands->at(idx_subleadtau)[j]) {
//                    numIsoOverLap++;
//                    EnergyIsoOverLap +=boostedTauIsolationPFCands->at(idx_leadtau)[i];
//                }
//            }
//        }
//        //===========  PFGammaCandidates==========
//        for (int i=0; i< boostedTauIsolationPFGammaCands->at(idx_leadtau).size(); i++){
//            numIso++;
//            EnergyIso +=boostedTauIsolationPFGammaCands->at(idx_leadtau)[i];
//            // overlap with subleading SignalPFCandidates
//            for (int j=0; j< boostedTauSignalPFGammaCands->at(idx_subleadtau).size(); j++){
//                if (boostedTauIsolationPFGammaCands->at(idx_leadtau)[i] == boostedTauSignalPFGammaCands->at(idx_subleadtau)[j]) {
//                    numIsoOverLap++;
//                    EnergyIsoOverLap +=boostedTauIsolationPFGammaCands->at(idx_leadtau)[i];
//                }
//            }
//            // overlap with subleading IsoPFCandidates
//            for (int j=0; j< boostedTauIsolationPFGammaCands->at(idx_subleadtau).size(); j++){
//                if (boostedTauIsolationPFGammaCands->at(idx_leadtau)[i] == boostedTauIsolationPFGammaCands->at(idx_subleadtau)[j]) {
//                    numIsoOverLap++;
//                    EnergyIsoOverLap +=boostedTauIsolationPFGammaCands->at(idx_leadtau)[i];
//                }
//            }
//        }
//
//
//        plotFill("dR_ratio_multiplicity",dR_tau_tau,numIsoOverLap*1.0/numIso,10,0,1,10,0,1);
//        plotFill("dR_ratio_energy",dR_tau_tau,EnergyIsoOverLap*1.0/EnergyIso,10,0,1,10,0,1);
//
//        if (dR_tau_tau < 0.5){
//
//            plotFill("GenMatchedLeadCombineIso",boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits->at(idx_leadtau) - leadRecoMatch[5]  ,2000,-200,200);
//            plotFill("GenMatchedSubCombineIso",boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits->at(idx_subleadtau) - leadRecoMatch[5]  ,2000,-200,200);
//            plotFill("GenMatchedLeadMVAIso",leadRecoMatch[1] - boostedTauByIsolationMVArun2v1DBoldDMwLTraw->at(idx_leadtau) ,200,-1,1);
//            plotFill("GenMatchedSubMVAIso",subRecoMatch[1] - boostedTauByIsolationMVArun2v1DBoldDMwLTraw->at(idx_subleadtau) ,200,-1,1);
//        }
//
        //=========================================================================================================
        // Event Selection
        //=========================================================================================================
        
        if( dR_tau_tau > 0.8 || dR_tau_tau < 0.1) continue;
        plotFill("cutFlowTable",5 ,15,0,15);
        
        tmass = TMass_F(LeadTau4Momentum.Pt(), LeadTau4Momentum.Px(), LeadTau4Momentum.Py(),  Met,  Metphi);
        //        if (tmass > 80) continue;
        plotFill("cutFlowTable",6 ,15,0,15);
        
        if (m_sv < 50) continue;
        plotFill("cutFlowTable",7 ,15,0,15);
        
        // BJet veto
        int numBJet=numBJets(BJetPtCut,DeepCSVCut);
        if (numBJet > 0) continue;
        plotFill("cutFlowTable",8 ,15,0,15);
        
        // HT cut
        ht= getHT(JetPtCut, LeadTau4Momentum, SubTau4Momentum);
        if (ht < 200) continue;
        plotFill("cutFlowTable",9 ,15,0,15);
        
        // ST definition
        st= getST(JetPtCut);
        if (st < 500) continue;
        plotFill("cutFlowTable",10 ,15,0,15);
        
        //electron veto
        int numele =getNumElectron();
        if (numele > 0) continue;
        plotFill("cutFlowTable",11 ,15,0,15);
        
        //muon veto
        int numMu =getNumMuon();
        if (numMu > 0) continue;
        plotFill("cutFlowTable",12 ,15,0,15);
        
        
        //Leading jet
        TLorentzVector LeadJet= getLeadJet(LeadTau4Momentum, SubTau4Momentum);
        
        float LumiWeight = 1;
        float PUWeight = 1;
        float LepCorrection=1;
        //        float nom_zpt_weight=1.0;
        //  GenInfo
        vector<float>  genInfo=GeneratorInfo();
        float ZBosonPt=genInfo[3];
        float ZBosonMass=genInfo[4];
        
        
        if (!isData){
            
            // Lumi weight
            LumiWeight = getLuminsoity(year) * XSection(sample)*1.0 / HistoTot->GetBinContent(2);
            
            float PUMC_=HistoPUMC->GetBinContent(puTrue->at(0)+1);
            float PUData_=HistoPUData->GetBinContent(puTrue->at(0)+1);
            
            if (PUMC_ ==0)
                cout<<"PUMC_ is zero!!! & num pileup= "<< puTrue->at(0)<<"\n";
            else
                PUWeight= PUData_/PUMC_;
            
        }
        
        plotFill("LumiWeight",LumiWeight ,1000,0,10000);
        plotFill("LepCorrection",LepCorrection ,100,0,2);
        //        plotFill("nom_zpt_weight",nom_zpt_weight ,100,0,2);
        plotFill("PUWeight",PUWeight ,200,0,2);
        
        //###############################################################################################
        //  tree branches
        //###############################################################################################
        
        Met4Momentum.SetPtEtaPhiM(pfMET, 0, pfMETPhi, 0);
        Z4Momentum=SubTau4Momentum+LeadTau4Momentum;
        TLorentzVector higgs = SubTau4Momentum+LeadTau4Momentum +Met4Momentum;
        
        higgs_pT = higgs.Pt();
        higgs_m = higgs.M();
        OS = boostedTauCharge->at(idx_leadtau) * boostedTauCharge->at(idx_subleadtau) < 0;
        SS =  boostedTauCharge->at(idx_leadtau) * boostedTauCharge->at(idx_subleadtau) > 0;
        PassLead = boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNew->at(idx_leadtau) > 0.5;
        PassSub = boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNew->at(idx_subleadtau) > 0.5;
        
        leadPt_=boostedTauPt->at(idx_leadtau);
        subPt_=boostedTauPt->at(idx_subleadtau);
        vis_mass=Z4Momentum.M();
        LeadJetPt = LeadJet.Pt();
        dR_Z_jet=LeadJet.DeltaR(Z4Momentum);
        BoostedTauRawIso=boostedTauByIsolationMVArun2v1DBoldDMwLTraw->at(idx_subleadtau);
        m_sv_=m_sv;
        //  Weights
        FullWeight = LumiWeight*LepCorrection;
        //        wtnom_zpt_weight=nom_zpt_weight;
        
        // Fill the tree
        outTr->Fill();
        
        
        plotFill("trg_37",PassTrigger_37 ,2,0,2);
        plotFill("trg_38",PassTrigger_38 ,2,0,2);
        plotFill("trg_39",PassTrigger_39 ,2,0,2);
        plotFill("trg_40",PassTrigger_40 ,2,0,2);
        plotFill("Trg_39_40",PassTrigger_39*PassTrigger_40 ,2,0,2);
        plotFill("trg_41",PassTrigger_41 ,2,0,2);
        plotFill("trg_42",PassTrigger_42 ,2,0,2);
        plotFill("trg_43",PassTrigger_43 ,2,0,2);
        plotFill("trg_44",PassTrigger_44 ,2,0,2);
        
        
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


