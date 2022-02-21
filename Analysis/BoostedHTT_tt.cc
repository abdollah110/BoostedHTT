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
    cout<<"%%%% Note: you are running on  "<< year_str <<"%%%%\n";
    
    bool isEmbed= false;
    if (sample.find("Embed") != string::npos) isEmbed= true;
    
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

    TFile* SF_files = TFile::Open("data/htt_scalefactors_legacy_2018.root", "READ");
    RooWorkspace *ws_SF = reinterpret_cast<RooWorkspace *>(SF_files->Get("w"));
    SF_files->Close();

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
    
    auto trgEff_HT_SF = TFile::Open(("data/sf_ht_trgEff_2D_"+year_str+".root").c_str());
    TH2F * triggerEff_HT_SF = (TH2F *) trgEff_HT_SF->Get("TrgEfficiency2D");
    
    auto trgEff_MET_SF = TFile::Open(("data/sf_met_trgEff_2D_"+year_str+".root").c_str());
    TH2F * triggerEff_MET_SF = (TH2F *) trgEff_MET_SF->Get("TrgEfficiency2D");
    
    //########################################
    // Rivet
    //########################################
    TFile *f_NNLOPS = TFile::Open("data/NNLOPS_reweight.root");
    TGraph *g_NNLOPS_0jet = reinterpret_cast<TGraph *>(f_NNLOPS->Get("gr_NNLOPSratio_pt_powheg_0jet"));
    TGraph *g_NNLOPS_1jet = reinterpret_cast<TGraph *>(f_NNLOPS->Get("gr_NNLOPSratio_pt_powheg_1jet"));
    TGraph *g_NNLOPS_2jet = reinterpret_cast<TGraph *>(f_NNLOPS->Get("gr_NNLOPSratio_pt_powheg_2jet"));
    TGraph *g_NNLOPS_3jet = reinterpret_cast<TGraph *>(f_NNLOPS->Get("gr_NNLOPSratio_pt_powheg_3jet"));
    //    TGraph *g_NNLOPS_mcatnlo_0jet = reinterpret_cast<TGraph *>(f_NNLOPS->Get("gr_NNLOPSratio_pt_mcatnlo_0jet"));
    //    TGraph *g_NNLOPS_mcatnlo_1jet = reinterpret_cast<TGraph *>(f_NNLOPS->Get("gr_NNLOPSratio_pt_mcatnlo_1jet"));
    //    TGraph *g_NNLOPS_mcatnlo_2jet = reinterpret_cast<TGraph *>(f_NNLOPS->Get("gr_NNLOPSratio_pt_mcatnlo_2jet"));
    //    TGraph *g_NNLOPS_mcatnlo_3jet = reinterpret_cast<TGraph *>(f_NNLOPS->Get("gr_NNLOPSratio_pt_mcatnlo_3jet"));
    
    event_info event(syst);
    
    //###############################################################################################
    // Parameters
    //###############################################################################################
    float MuMass= 0.10565837;
    float eleMass= 0.000511;
    float JetPtCut=30;
    float BJetPtCut=30;
    
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
    float WBosonKFactor=1;
    float preFireWeight=1;
    float ttbar_rwt=1;
    float zmasspt_weight_err=0;
    float zmasspt_weight_nom=1;
    float weight_Rivet =1;
    float weight_g_NNLOPS = 1;
    
    float lep1Pt_=-10;
    float lep2Pt_=-10;
    float vis_mass=-10;
    float LeadJetPt = -10;
    float dR_Z_jet=-10;
    bool lep1IsoPassL,lep2IsoPassL,lep1IsoPassV,lep2IsoPassV,OS,SS;
    float tmass,ht,st,Met,FullWeight, dR_lep_lep, Metphi,BoostedTauRawIso, higgs_pT, higgs_m, m_sv_, wtnom_zpt_weight, gen_higgs_pT,gen_leadjet_pT;
    float MuMatchedIsolation= -1; float EleMatchedIsolation =-1;
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
    int nbjet, gen_matched1_, gen_matched2_,gen_matched1, gen_matched2;

    bool isGenTauSub_, isGenTauLead_;
    bool Chan_emu, Chan_etau, Chan_mutau, Chan_tautau, Chan_emu_fid, Chan_etau_fid, Chan_mutau_fid, Chan_tautau_fid;
    
    outTr->Branch("Chan_emu",&Chan_emu,"Chan_emu/O");
    outTr->Branch("Chan_etau",&Chan_etau,"Chan_etau/O");
    outTr->Branch("Chan_mutau",&Chan_mutau,"Chan_mutau/O");
    outTr->Branch("Chan_tautau",&Chan_tautau,"Chan_tautau/O");
    outTr->Branch("Chan_emu_fid",&Chan_emu_fid,"Chan_emu_fid/O");
    outTr->Branch("Chan_etau_fid",&Chan_etau_fid,"Chan_etau_fid/O");
    outTr->Branch("Chan_mutau_fid",&Chan_mutau_fid,"Chan_mutau_fid/O");
    outTr->Branch("Chan_tautau_fid",&Chan_tautau_fid,"Chan_tautau_fid/O");
    
    outTr->Branch("evtwt",&FullWeight,"evtwt/F");
    outTr->Branch("zmasspt_weight",&zmasspt_weight,"zmasspt_weight/F");
    outTr->Branch("lep1Pt",&lep1Pt_,"lep1Pt/F");
    outTr->Branch("lep2Pt",&lep2Pt_,"lep2Pt/F");
    outTr->Branch("lep1IsoPassL",&lep1IsoPassL,"lep1IsoPassL/O");
    outTr->Branch("lep2IsoPassL",&lep2IsoPassL,"lep2IsoPassL/O");
    outTr->Branch("lep1IsoPassV",&lep1IsoPassV,"lep1IsoPassV/O");
    outTr->Branch("lep2IsoPassV",&lep2IsoPassV,"lep2IsoPassV/O");
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
    outTr->Branch("nbjet",&nbjet,"nbjet/I");
    outTr->Branch("gen_higgs_pT",&gen_higgs_pT,"gen_higgs_pT/F");
    outTr->Branch("gen_leadjet_pT",&gen_leadjet_pT,"gen_leadjet_pT/F");
    outTr->Branch("isGenTauLead_",&isGenTauLead_,"isGenTauLead_/O");
    outTr->Branch("isGenTauSub_",&isGenTauSub_,"isGenTauSub_/O");
    outTr->Branch("MuMatchedIsolation",&MuMatchedIsolation,"MuMatchedIsolation/F");
    outTr->Branch("EleMatchedIsolation",&EleMatchedIsolation,"EleMatchedIsolation/F");
    outTr->Branch("gen_matched1_",&gen_matched1_,"gen_matched1_/I");
    outTr->Branch("gen_matched2_",&gen_matched2_,"gen_matched2_/I");
    
    string JetSys="Nominal";
    if (syst=="JEnTotUp") JetSys="JetTotUp";
    else if (syst=="JEnTotDown") JetSys="JetTotDown";
    else std::cout<<"This is nominal Jet\n";
    
    
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
        if (isData && (metFilters!=0)) continue;
        //=========================================================================================================
        //MET Shape systematics
        //        Met=pfMET;
        //        Metphi=pfMETPhi;
        Met=pfMetNoRecoil;
        Metphi=pfMetPhiNoRecoil;
        
        if (syst == "MissingEn_JESUp") {Met = pfMET_T1JESUp; Metphi=pfMETPhi_T1JESUp; m_sv=m_sv_JES_Up ;}
        if (syst == "MissingEn_JESDown") {Met = pfMET_T1JESDo;  Metphi=pfMETPhi_T1JESDo; m_sv=m_sv_JES_Down ;}
        if (syst == "MissingEn_UESUp") {Met = pfMET_T1UESUp;  Metphi=pfMETPhi_T1UESUp; m_sv=m_sv_UES_Up ;}
        if (syst == "MissingEn_UESDown") {Met = pfMET_T1UESDo;  Metphi=pfMETPhi_T1UESDo; m_sv=m_sv_UES_Down ;}
        
        //        if (syst == "TESUp") {m_sv=m_sv_TES_Up ;}
        //        if (syst == "TESDown") {m_sv=m_sv_TES_Down ;}
        
        //        if (syst == "met_reso_Up") {Met = met_reso_Up; Metphi=metphi_reso_Up;}
        //        if (syst == "met_resp_Up") {Met = met_resp_Up; Metphi=metphi_resp_Up;}
        //        if (syst == "met_reso_Down") {Met = met_reso_Down; Metphi=metphi_reso_Down;}
        //        if (syst == "met_resp_Down") {Met = met_resp_Down; Metphi=metphi_resp_Down;}
        
        
        TLorentzVector LeadTau4Momentum,SubTau4Momentum, Z4Momentum, Met4Momentum;
        //=========================================================================================================
        // Lead tau selection
        int idx_leadtau= leadtauIndex;
        LeadTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(idx_leadtau),boostedTauEta->at(idx_leadtau),boostedTauPhi->at(idx_leadtau),boostedTauMass->at(idx_leadtau));
        bool isGenTauLead= isMatchedToGenTau(LeadTau4Momentum);
        if (syst == "TESUp" && isGenTauLead) {LeadTau4Momentum *= 1+0.03 ; m_sv=m_sv_TES_Up ;}
        if (syst == "TESDown" && isGenTauLead) {LeadTau4Momentum *= 1-0.03 ;m_sv=m_sv_TES_Down ;}
        
        
        if (LeadTau4Momentum.Pt() <= 30 || fabs(boostedTauEta->at(idx_leadtau)) >= 2.3 ) continue;
        if (boostedTaupfTausDiscriminationByDecayModeFinding->at(idx_leadtau) < 0.5 ) continue;
        if (boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(idx_leadtau) < -0.5) continue;
        if (boostedTauagainstElectronVLooseMVA62018->at(idx_leadtau) < 0.5) continue;
        if (boostedTauByLooseMuonRejection3->at(idx_leadtau) < 0.5) continue;
        plotFill("cutFlowTable",3 ,15,0,15);
        
        //=========================================================================================================
        // sublead Tau selection
        int idx_subleadtau= subtauIndex;
        SubTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(idx_subleadtau),boostedTauEta->at(idx_subleadtau),boostedTauPhi->at(idx_subleadtau),boostedTauMass->at(idx_subleadtau));
        bool isGenTauSub= isMatchedToGenTau(SubTau4Momentum);
        if (syst == "TESUp" && isGenTauSub) {SubTau4Momentum *= 1+0.03 ; m_sv=m_sv_TES_Up ;}
        if (syst == "TESDown" && isGenTauSub) {SubTau4Momentum *= 1-0.03 ;m_sv=m_sv_TES_Down ;}
        
        if (SubTau4Momentum.Pt() <= 30 || fabs(boostedTauEta->at(idx_subleadtau)) >= 2.3 ) continue;
        if (boostedTaupfTausDiscriminationByDecayModeFinding->at(idx_subleadtau) < 0.5 ) continue;
        if (boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(idx_subleadtau) < -0.5) continue;
        if (boostedTauagainstElectronVLooseMVA62018->at(idx_subleadtau) < 0.5) continue;
        if (boostedTauByLooseMuonRejection3->at(idx_subleadtau) < 0.5) continue;
        
        plotFill("cutFlowTable",4 ,15,0,15);
        
        dR_lep_lep= SubTau4Momentum.DeltaR(LeadTau4Momentum);
        if (nJet < 1 ) continue;
        TLorentzVector LeadJet= getLeadJet(LeadTau4Momentum, SubTau4Momentum,JetSys);
        
        
        //=========================================================================================================
        // Cut on AK8 (for trigger purposes)
        float AK8Pt=0;
        float AK8Mass=0;
        float AK8Eta=100;
        
        float PFHT= getST(JetPtCut,JetSys);
        float PFMET=Met;
        float MHT=getMHT(JetPtCut,JetSys);
        st= getST(JetPtCut,JetSys);
        ht= getHT(JetPtCut, LeadTau4Momentum, SubTau4Momentum,JetSys);
        
        float TriggerWeight = 1;
        float TriggerWeightError = 1;
        float _cut_AK8Pt_,_cut_AK8Mass_,_cut_PFHT_,_cut_PFMET_,_cut_PFMHT_, _cut_PFMETMHT_, _cut_st_;
        bool _Pass_AK8_Trigger_, _Pass_METHT_Trigger_;
        
        
        
        
        
        //=========================================================================================================
        // Trigger Efficiency
        //=========================================================================================================
        if (year== 2016  && PFHT > 400 ){
            plotFill("RunBeforeTrigger",run, 50 ,273000,285000);
            if (PassTrigger_20) plotFill("RunHLTJet37",run, 50 ,273000,285000);
            if (PassTrigger_21) plotFill("RunHLTJet38",run, 50 ,273000,285000);
            if (PassTrigger_22) plotFill("RunHLTJet39",run, 50 ,273000,285000);
            if (PassTrigger_40) plotFill("RunHLTJet40",run, 50 ,273000,285000);
        }
        else if (year== 2017 && PFHT > 400){
            plotFill("RunBeforeTrigger",run, 50 ,297000,307000);
            if (PassTrigger_37) plotFill("RunHLTJet37",run, 50 ,297000,307000);
            if (PassTrigger_38) plotFill("RunHLTJet38",run, 50 ,297000,307000);
            if (PassTrigger_39) plotFill("RunHLTJet39",run, 50 ,297000,307000);
            if (PassTrigger_40) plotFill("RunHLTJet40",run, 50 ,297000,307000);
        }
        else if (year== 2018 && PFHT > 400){
            plotFill("RunBeforeTrigger",run, 50 ,315000,326000);
            if (PassTrigger_37) plotFill("RunHLTJet37",run, 50 ,315000,326000);
            if (PassTrigger_38) plotFill("RunHLTJet38",run, 50 ,315000,326000);
            if (PassTrigger_39) plotFill("RunHLTJet39",run, 50 ,315000,326000);
            if (PassTrigger_40) plotFill("RunHLTJet40",run, 50 ,315000,326000);
        }
        //=========================================================================================================
        
        
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
            if (syst=="JEnTotUp") AK8Pt=AK8JetPtTotUncUp->at(ijet);;
            if (syst=="JEnTotDown") AK8Pt=AK8JetPtTotUncDown->at(ijet);;
            
            AK8Mass=AK8JetSoftDropMass->at(ijet);
            AK8Eta=fabs(AK8JetEta->at(ijet));
            
            if (AK8Pt > 450 && AK8Mass > 30 && AK8Eta < 2.5) break;
            
        }
        
        
        bool passing= true;
        
        ////apply trigger only on data
        if (year==2017){
            if ( (!isData ||  (isData && _Pass_AK8_Trigger_)) &&  AK8Pt > _cut_AK8Pt_ && AK8Mass > _cut_AK8Mass_ && AK8Eta < 2.5){
                TriggerWeight = getTriggerWeight(year, isData,  AK8Pt , AK8Mass ,triggerEff_HT);
                TriggerWeightError = getTriggerWeightError(year, isData,  AK8Pt , AK8Mass ,triggerEff_HT);
                passing= true;
            }
            else if ( (!isData ||  (isData && _Pass_METHT_Trigger_)) &&  PFHT > _cut_PFHT_ && PFMET > _cut_PFMET_ && MHT> _cut_PFMHT_ && PFMET+MHT > _cut_PFMETMHT_){
                TriggerWeight = getTriggerWeight(year, isData,  PFHT,PFMET,MHT ,triggerEff_MET);
                TriggerWeightError = getTriggerWeightError(year, isData,  PFHT,PFMET,MHT ,triggerEff_MET);
                passing= true;
            }
            else {
                passing = false;
            }
        }
        else {
            // apply trigger on simulation as well as data
            if ( _Pass_AK8_Trigger_ &&  AK8Pt > _cut_AK8Pt_ && AK8Mass > _cut_AK8Mass_ && AK8Eta < 2.5){
                TriggerWeight = getTriggerWeight(year, isData,  AK8Pt , AK8Mass ,triggerEff_HT_SF);
                TriggerWeightError = getTriggerWeightError(year, isData,  AK8Pt , AK8Mass ,triggerEff_HT_SF);
                passing= true;
            }
            else if (_Pass_METHT_Trigger_ &&  PFHT > _cut_PFHT_ && PFMET > _cut_PFMET_ && MHT> _cut_PFMHT_ && PFMET+MHT > _cut_PFMETMHT_){
                TriggerWeight = getTriggerWeight(year, isData,  PFHT,PFMET,MHT ,triggerEff_MET_SF);
                TriggerWeightError = getTriggerWeightError(year, isData,  PFHT,PFMET,MHT ,triggerEff_MET_SF);
                passing= true;
            }
            else {
                passing = false;
            }
        }
        
        //        if (! passing) continue;  FIXME  this is for trigger studies for embedded
        
        //=========================================================================================================
        // Event Selection
        //=========================================================================================================
        Met4Momentum.SetPtEtaPhiM(Met, 0, Metphi, 0);
        Z4Momentum=SubTau4Momentum+LeadTau4Momentum;
        TLorentzVector higgs = SubTau4Momentum+LeadTau4Momentum +Met4Momentum;
        
        
        if( dR_lep_lep > 0.8 || dR_lep_lep < 0.1) continue;
        plotFill("cutFlowTable",8 ,15,0,15);
        
        tmass = TMass_F(LeadTau4Momentum.Pt(), LeadTau4Momentum.Px(), LeadTau4Momentum.Py(),  Met,  Metphi);
        //        if (tmass > 200) continue; //FIXME removed for Validation study
        plotFill("cutFlowTable",9 ,15,0,15);
        
        if (m_sv < 50) continue; //FIXME removed for Validation study
        plotFill("cutFlowTable",10 ,15,0,15);
        
        // BJet veto
        int numBJet=numBJets(BJetPtCut,DeepCSVCut,JetSys);
        //        if (numBJet > 0) continue;
        //        plotFill("cutFlowTable",8 ,15,0,15);
        
        
        //        electron veto
        //        int numele =getNumElectron();
        int numele =getNumElectron(SubTau4Momentum+LeadTau4Momentum);
        if (numele > 0) continue;
        plotFill("cutFlowTable",11 ,15,0,15);
        
        //muon veto
        //        int numMu =getNumMuon();
        int numMu =getNumMuon(SubTau4Momentum+LeadTau4Momentum);
        if (numMu > 0) continue;
        plotFill("cutFlowTable",12 ,15,0,15);
        
        higgs_pT = higgs.Pt();
        if (higgs_pT < 250 ) continue;
        plotFill("cutFlowTable",13 ,15,0,15);
        
        
//=========================================================================================================
        //=========================================================================================================
        float embedWeight = 1;
        if (isEmbed){
            
            if (genWeight > 1 || genWeight < 0) {
                LumiWeight=0;
            }
            else {
                LumiWeight = genWeight;
            }

            ws_SF->var("gt1_pt")->setVal(getMatchedGenTau(LeadTau4Momentum).Pt());
            ws_SF->var("gt1_eta")->setVal(getMatchedGenTau(LeadTau4Momentum).Eta());
            ws_SF->var("gt2_pt")->setVal(getMatchedGenTau(SubTau4Momentum).Pt());
            ws_SF->var("gt2_eta")->setVal(getMatchedGenTau(SubTau4Momentum).Eta());
            embedWeight *=ws_SF->function("m_sel_trg_ratio")->getVal();
            
            ws_SF->var("gt_pt")->setVal(getMatchedGenTau(LeadTau4Momentum).Pt());
            ws_SF->var("gt_eta")->setVal(getMatchedGenTau(LeadTau4Momentum).Eta());
            embedWeight *=ws_SF->function("m_sel_idEmb_ratio")->getVal();
            
            ws_SF->var("gt_pt")->setVal(getMatchedGenTau(SubTau4Momentum).Pt());
            ws_SF->var("gt_eta")->setVal(getMatchedGenTau(SubTau4Momentum).Eta());
            embedWeight *=ws_SF->function("m_sel_idEmb_ratio")->getVal();
            
            ws_SF->var("t_pt")->setVal(LeadTau4Momentum.Pt());
            embedWeight *=ws_SF->function("tt_emb_PFTau35OR40_tight_kit_ratio")->getVal();
                        
            ws_SF->var("t_pt")->setVal(SubTau4Momentum.Pt());
            embedWeight *=ws_SF->function("tt_emb_PFTau35OR40_tight_kit_ratio")->getVal();
            
        }
        
        if (!isData){
            
            // Lumi weight
            LumiWeight = getLuminsoity(year,"tt") * XSection(sample)*1.0 / HistoTot->GetBinContent(2);
            
            float PUMC_=HistoPUMC->GetBinContent(puTrue->at(0)+1);
            float PUData_=HistoPUData->GetBinContent(puTrue->at(0)+1);
            
            if (PUMC_ ==0)
                cout<<"PUMC_ is zero!!! & num pileup= "<< puTrue->at(0)<<"\n";
            else
                PUWeight= PUData_/PUMC_;
            
            //prefire
            preFireWeight = L1ECALPrefire;
            if (syst == "prefireUp") {preFireWeight = L1ECALPrefireUp;}
            if (syst == "prefireDown") {preFireWeight = L1ECALPrefireDown;}
            
            //TriggerWeight uncertainty
            if (syst == "trig_ttUp") {TriggerWeight  = TriggerWeight+TriggerWeightError;}
            if (syst == "trig_ttDown") {TriggerWeight  = TriggerWeight-TriggerWeightError;}

        // Separate Drell-Yan processes
         gen_matched1 = ZCategory(LeadTau4Momentum);
         gen_matched2 = ZCategory(SubTau4Momentum);


        if (name == "ZLL" && (gen_matched1 >4 || gen_matched2 >4)) {
            continue;
        } else if ((name == "ZTT") && (gen_matched1 <5 && gen_matched2 < 5)) {
            continue;
        }

//        if (name == "ZLL" && Zcateg > 4) {
//            continue;
//        } else if ((name == "ZTT") &&Zcateg != 5) {
//            continue;
//        } else if (name == "ZJ" && Zcateg != 6) {
//            continue;
//        }


            //  GenInfo
            vector<float>  genInfo=GeneratorInfo();
            float WBosonPt=genInfo[1];
            float ZBosonPt=genInfo[3];
            float ZBosonMass=genInfo[4];
            
            if  (name == "ZL" || name == "ZTT" || name == "ZLL") {
                
                if (ZBosonPt > 999) ZBosonPt=999;
                if (ZBosonMass < 61) ZBosonMass = 61;
                if (ZBosonMass > 119) ZBosonMass = 119;
                zmasspt_weight_nom=zpt_hist->GetBinContent(zpt_hist->GetXaxis()->FindBin(ZBosonMass), zpt_hist->GetYaxis()->FindBin(ZBosonPt));
                zmasspt_weight_err=zpt_hist->GetBinError(zpt_hist->GetXaxis()->FindBin(ZBosonMass), zpt_hist->GetYaxis()->FindBin(ZBosonPt));
                
                zmasspt_weight = zmasspt_weight_nom + 0 * zmasspt_weight_err;
                if (syst == "Z_masspt_Up")  zmasspt_weight = zmasspt_weight_nom + 1 * zmasspt_weight_err;
                if (syst == "Z_masspt_Down") zmasspt_weight = zmasspt_weight_nom + -1 * zmasspt_weight_err;
            }
            
            if (name == "W" && (sample.find("_HT_") != string::npos) ){
                WBosonKFactor= FuncBosonKFactor("W1Cen") + FuncBosonKFactor("W2Cen") * WBosonPt; //HT binned & inclusive K-factor
                if (syst == "WBosonKFactorUp") WBosonKFactor= FuncBosonKFactor("W1Up") + FuncBosonKFactor("W2Up") * WBosonPt; //HT binned & inclusive K-factor
                if (syst == "WBosonKFactorDown") WBosonKFactor= FuncBosonKFactor("W1Down") + FuncBosonKFactor("W2Down") * WBosonPt; //HT binned & inclusive K-factor
            }
            // top-pT Reweighting
            if (name == "TT") {
                ttbar_rwt= newTopPtReweight(genInfo[5],genInfo[6],year,"nominal" );
                if (syst == "ttbarShape_Up") {
                    ttbar_rwt= newTopPtReweight(genInfo[5],genInfo[6],year,"ttbarShape_Up" );
                } else if (syst == "ttbarShape_Down") {
                    ttbar_rwt= newTopPtReweight(genInfo[5],genInfo[6],year,"ttbarShape_Down" );
                }
            }
            
        }
        
        //###############################################################################################
        //  Higgs theory uncertainty
        //###############################################################################################
        
        if (fname.find("ggH125") != std::string::npos) { // now is used for all of prodiuction mode
            if (Rivet_nJets30 == 0)
                weight_g_NNLOPS = g_NNLOPS_0jet->Eval(std::min(Rivet_higgsPt, static_cast<float>(125.0)));
            if (Rivet_nJets30 == 1)
                weight_g_NNLOPS = g_NNLOPS_1jet->Eval(std::min(Rivet_higgsPt, static_cast<float>(625.0)));
            if (Rivet_nJets30 == 2)
                weight_g_NNLOPS = g_NNLOPS_2jet->Eval(std::min(Rivet_higgsPt, static_cast<float>(800.0)));
            if (Rivet_nJets30 >= 3)
                weight_g_NNLOPS = g_NNLOPS_3jet->Eval(std::min(Rivet_higgsPt, static_cast<float>(925.0)));
            
            NumV WG1unc;
            WG1unc = qcd_ggF_uncert_2017(Rivet_nJets30, Rivet_higgsPt, Rivet_stage1_cat_pTjet30GeV);
            if (syst.find("THU_ggH") != std::string::npos) {
                weight_Rivet= 1 + event.getRivetUnc(WG1unc, syst);
            }
        }
        //###############################################################################################
        
        plotFill("weight_g_NNLOPS",weight_g_NNLOPS ,100,0,2);
        plotFill("weight_Rivet",weight_Rivet ,100,0,2);
        
        plotFill("TriggerWeight",TriggerWeight ,100,0,1);
        plotFill("LepCorrection",LepCorrection ,100,0,2);
        plotFill("LumiWeight",LumiWeight ,1000,0,10000);
        plotFill("PUWeight",PUWeight ,200,0,2);
        plotFill("zmasspt_weight",zmasspt_weight ,200,0,2);
        plotFill("preFireWeight",preFireWeight ,200,0,2);
        plotFill("WBosonKFactor",WBosonKFactor ,200,0,2);
        plotFill("ttbar_rwt",ttbar_rwt ,200,0,2);
        plotFill("embedWeight",embedWeight ,200,0,2);
        
        //###############################################################################################
        //  tree branches
        //###############################################################################################
        
        
        higgs_m = higgs.M();
        OS = boostedTauCharge->at(idx_leadtau) * boostedTauCharge->at(idx_subleadtau) < 0;
        SS =  boostedTauCharge->at(idx_leadtau) * boostedTauCharge->at(idx_subleadtau) > 0;
        lep1IsoPassL = boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNew->at(idx_leadtau) > 0.5;
        lep2IsoPassL = boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNew->at(idx_subleadtau) > 0.5;
        lep1IsoPassV = boostedTauByVLooseIsolationMVArun2v1DBoldDMwLTNew->at(idx_leadtau) > 0.5;
        lep2IsoPassV = boostedTauByVLooseIsolationMVArun2v1DBoldDMwLTNew->at(idx_subleadtau) > 0.5;
        
        lep1Pt_=LeadTau4Momentum.Pt();
        lep2Pt_=SubTau4Momentum.Pt();
        vis_mass=Z4Momentum.M();
        LeadJetPt = LeadJet.Pt();
        dR_Z_jet=LeadJet.DeltaR(Z4Momentum);
        BoostedTauRawIso=boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(idx_subleadtau);
        m_sv_=m_sv;
        //  Weights
        FullWeight = LumiWeight*LepCorrection * PUWeight * TriggerWeight*zmasspt_weight * preFireWeight * WBosonKFactor * ttbar_rwt* weight_Rivet *embedWeight;
        nbjet=numBJet;
//        gen_higgs_pT = Rivet_higgsPt;
//        gen_leadjet_pT = Rivet_j1pt;
        isGenTauSub_=isGenTauSub;
        isGenTauLead_=isGenTauLead;
        
        //  fiducial info
        FidSelection fiducial = PassFoducial();
        Chan_emu = fiducial.emu ;
        Chan_etau = fiducial.etau ;
        Chan_mutau = fiducial.mutau ;
        Chan_tautau = fiducial.tautau ;
        Chan_emu_fid = fiducial.emu_fid ;
        Chan_etau_fid = fiducial.etau_fid ;
        Chan_mutau_fid = fiducial.mutau_fid ;
        Chan_tautau_fid = fiducial.tautau_fid ;
        gen_matched1_=gen_matched1;
        gen_matched2_=gen_matched2;
        
        // Fill the tree
        outTr->Fill();
        
        //     if (lep1IsoPassV && lep2IsoPassV && m_sv_ > 120 && m_sv_ < 130 && dR_lep_lep > 0.3 && dR_lep_lep < 0.6)
        //      std::cout<<"mass= "<<m_sv_<<" Higgs pt="<<higgs.Pt() <<"   Run:Lumi:Eve"<<run<<":"<<lumis<<":"<<event__<<"\n";
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

