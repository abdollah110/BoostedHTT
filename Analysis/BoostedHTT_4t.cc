//#include "../interface/Functions.h"
#include <string>
#include <ostream>
#include <vector>
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooFunctor.h"
#include "RooMsgService.h"
#include "TLorentzVector.h"
#include "../interface/CLParser.h"
#include "../interface/boostHTT.h"
#include "../interface/makeHisto.h"

int main(int argc, char* argv[]) {
    
    CLParser parser(argc, argv);
    std::string sample = parser.Option("-s");
    std::string name = parser.Option("-n");
//    std::string path = parser.Option("-p");
//    std::string output_dir = parser.Option("-d");
//    std::string syst = parser.Option("-u");
//    std::string fname = path + sample + ".root";
    std::string fname = sample ;
    
    std::string year_str;
//    if (path.find("2016") != string::npos) year_str = "2016";
//    else if (path.find("2017") != string::npos) year_str = "2017";
//    else if (path.find("2018") != string::npos) year_str = "2018";
//    else cout<<"Which year are you looking for \n\n";
//    cout<<"%%%% Note: you are running on  "<< year_str <<"%%%%\n";
    
    stringstream yearstream(year_str);
    int year=0;
    yearstream >> year;
    
    
    // create output file
    auto suffix = "_output.root";
    auto prefix =  "";
    std::string filename;
    if (name == sample) {
        filename = prefix + name +  suffix;
    } else {
        filename = prefix + sample + std::string("_") + name +  suffix;
    }
    std::cout<<"output name is "<<filename.c_str()<<"\n";
    
    
    // open input file
    std::cout << "Opening file... " << sample << std::endl;
    auto InputFile = TFile::Open(fname.c_str());
    std::cout << "Loading Ntuple..." << std::endl;
    TTree *  Run_Tree;
    Run_Tree= Xttree(InputFile,"4tau_tree");
    
    //    auto HistoTot = reinterpret_cast<TH1D*>(InputFile->Get("ggNtuplizer/hEvents"));
    TH1F * HistoTot = (TH1F*) InputFile->Get("hcount");
    auto fout = new TFile(filename.c_str(), "RECREATE");
    
    myMap1 = new std::unordered_map<std::string, TH1F*>();
    myMap2 = new unordered_map<string, TH2F*>();
    
    TTree * outTr=  new TTree("tree_4tau","tree_4tau");
    

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
//
//    float LeptonIsoCut=0.15;
//    bool debug= false;
//    float LumiWeight = 1;
//    float PUWeight = 1;
//    float LepCorrection=1;
//    float zmasspt_weight=1;
//    float WBosonKFactor=1;
//    float preFireWeight=1;
//    float ttbar_rwt=1;
//    float zmasspt_weight_err=0;
//    float zmasspt_weight_nom=1;
//    float weight_Rivet =1;
//    float weight_g_NNLOPS = 1;
//    float Weight_PS=1;
//
//    float lep1Pt_=-10;
//    float lep2Pt_=-10;
//    float vis_mass=-10;
//    float LeadJetPt = -10;
//    float dR_Z_jet=-10;
//    bool lep1IsoPassL,lep2IsoPassL,lep1IsoPassV,lep2IsoPassV,OS,SS;
//    float tmass,ht,st,Met,FullWeight, dR_lep_lep, Metphi,BoostedTauRawIso, higgs_pT, higgs_m, m_sv_, wtnom_zpt_weight, gen_higgs_pT,gen_leadjet_pT;
//    float MuMatchedIsolation= -1; float EleMatchedIsolation =-1;
//    int nbjet, gen_matched1_, gen_matched2_,gen_matched1, gen_matched2, gen_nJet;
//
//    bool isGenTauSub_, isGenTauLead_;
//    bool Chan_emu, Chan_etau, Chan_mutau, Chan_tautau, Chan_emu_fid, Chan_etau_fid, Chan_mutau_fid, Chan_tautau_fid;
//
//    outTr->Branch("evtwt",&FullWeight,"evtwt/F");
//    outTr->Branch("pdfWeight", &pdfWeight);
//    outTr->Branch("pdfSystWeight", &pdfSystWeight);
//    outTr->Branch("pdf", &pdf);
//    outTr->Branch("zmasspt_weight",&zmasspt_weight,"zmasspt_weight/F");
//    outTr->Branch("lep1Pt",&lep1Pt_,"lep1Pt/F");
//    outTr->Branch("lep2Pt",&lep2Pt_,"lep2Pt/F");
//    outTr->Branch("lep1IsoPassL",&lep1IsoPassL,"lep1IsoPassL/O");
//    outTr->Branch("lep2IsoPassL",&lep2IsoPassL,"lep2IsoPassL/O");
//    outTr->Branch("lep1IsoPassV",&lep1IsoPassV,"lep1IsoPassV/O");
//    outTr->Branch("lep2IsoPassV",&lep2IsoPassV,"lep2IsoPassV/O");
//    outTr->Branch("OS",&OS,"OS/O");
//    outTr->Branch("SS",&SS,"SS/O");
//    outTr->Branch("vis_mass",&vis_mass,"vis_mass/F");
//    outTr->Branch("tmass",&tmass,"tmass/F");
//    outTr->Branch("ht",&ht,"ht/F");
//    outTr->Branch("st",&st,"st/F");
//    outTr->Branch("Met",&Met,"Met/F");
//    outTr->Branch("LeadJetPt",&LeadJetPt,"LeadJetPt/F");
//    outTr->Branch("dR_lep_lep",&dR_lep_lep,"dR_lep_lep/F");
//    outTr->Branch("BoostedTauRawIso",&BoostedTauRawIso,"BoostedTauRawIso/F");
//    outTr->Branch("higgs_pT",&higgs_pT,"higgs_pT/F");
//    outTr->Branch("higgs_m",&higgs_m,"higgs_m/F");
//    outTr->Branch("nbjet",&nbjet,"nbjet/I");
//    outTr->Branch("gen_higgs_pT",&gen_higgs_pT,"gen_higgs_pT/F");
//    outTr->Branch("gen_leadjet_pT",&gen_leadjet_pT,"gen_leadjet_pT/F");
//    outTr->Branch("isGenTauLead_",&isGenTauLead_,"isGenTauLead_/O");
//    outTr->Branch("isGenTauSub_",&isGenTauSub_,"isGenTauSub_/O");
//    outTr->Branch("MuMatchedIsolation",&MuMatchedIsolation,"MuMatchedIsolation/F");
//    outTr->Branch("EleMatchedIsolation",&EleMatchedIsolation,"EleMatchedIsolation/F");
//    outTr->Branch("gen_matched1_",&gen_matched1_,"gen_matched1_/I");
//    outTr->Branch("gen_matched2_",&gen_matched2_,"gen_matched2_/I");
//    outTr->Branch("run",&run,"run/I");
//    outTr->Branch("event",&event,"event/I");
//    outTr->Branch("lumis",&lumis,"lumis/I");
    
    
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
        
        
//
//        //2016
//        PassTrigger_21 = ((HLTJet >> 21 & 1)==1); //HLT_AK8PFJet360_TrimMass30_v // only 2016?
//        PassTrigger_22 = ((HLTJet >> 22 & 1)==1); //HLT_PFHT300_PFMET110_v // only 2016?
//
//
//        //2017 and 2018
//        PassTrigger_40 = ((HLTJet >> 40 & 1)==1); //HLT_AK8PFJet400_TrimMass30_v //HLT_AK8PFJet400_TrimMass30_v
//        PassTrigger_39 = ((HLTJet >> 39 & 1)==1); //HLT_PFHT500_PFMET100_PFMHT100_IDTight_v
//
//        // Trigger
//        //        https://cmsoms.cern.ch/cms/triggers/hlt_trigger_rates?cms_run=325175
//        //https://twiki.cern.ch/twiki/bin/viewauth/CMS/HLTPathsRunIIList
//        PassTrigger_20 = ((HLTJet >> 20 & 1)==1); //HLT_AK8PFHT700_TrimR0p1PT0p3Mass50_v // only 2016?
//        PassTrigger_37 = ((HLTJet >> 37 & 1)==1); //HLT_AK8PFHT800_TrimMass50_v // not effective
//        PassTrigger_38 = ((HLTJet >> 38 & 1)==1); //HLT_PFHT1050_v  NOT Effective at all
//        PassTrigger_41 = ((HLTJet >> 41 & 1)==1);// HLT_AK8PFJet420_TrimMass30_v  // not needed as HLT_AK8PFJet400_TrimMass30_v is available
//        PassTrigger_42 = ((HLTJet >> 42 & 1)==1);//HLT_PFHT500_PFMET110_PFMHT110_IDTight_v
//        PassTrigger_43 = ((HLTJet >> 43 & 1)==1); // HLT_AK8PFHT850_TrimMass50_v  HLT_AK8PFHT800_TrimMass50_v is OK as well
//        PassTrigger_44 = ((HLTJet >> 44 & 1)==1); //HLT_AK8PFHT900_TrimMass50_v

        plotFill("cutFlowTable",2 ,15,0,15);
        

        TLorentzVector LeadTau4Momentum,SubTau4Momentum, Z4Momentum, Met4Momentum, LeadTau4MomentumNominal, SubTau4MomentumNominal;
        //=========================================================================================================

if (nBoostedTau < 3) continue;

float LeadingBoostedTauPt= boostedTauPt->at(0);
float SubLeadingBoostedTauPt= boostedTauPt->at(1);
float ThirdBoostedTauPt= boostedTauPt->at(2);
float ForthBoostedTauPt= boostedTauPt->at(3);


plotFill("LeadingBoostedTauPt_",LeadingBoostedTauPt ,20,0,500);
plotFill("SubLeadingBoostedTauPt_",SubLeadingBoostedTauPt ,20,0,500);
plotFill("ThirdBoostedTauPt_",ThirdBoostedTauPt ,20,0,500);
plotFill("ForthBoostedTauPt_",ForthBoostedTauPt ,20,0,500);

        
        //=========================================================================================================
        // Event Selection
        //=========================================================================================================



        

        
        // Fill the tree
        outTr->Fill();
        
    } //End of Tree
    
    
    fout->cd();
    unordered_map<string, TH1F*>::const_iterator iMap1 = myMap1->begin();
    unordered_map<string, TH1F*>::const_iterator jMap1 = myMap1->end();
    
    for (; iMap1 != jMap1; ++iMap1)
        nplot1(iMap1->first)->Write();
    outTr->Write();
    
    unordered_map<string, TH2F*>::const_iterator iMap2 = myMap2->begin();
    unordered_map<string, TH2F*>::const_iterator jMap2 = myMap2->end();
    
    for (; iMap2 != jMap2; ++iMap2)
        nplot2(iMap2->first)->Write();
    
    fout->Close();
}

