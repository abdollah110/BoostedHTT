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
    
    myMap1 = new std::unordered_map<std::string, TH1F*>();
    myMap2 = new unordered_map<string, TH2F*>();
    
    TTree * outTr=  new TTree("tautau_tree","tautau_tree");
    
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
    float Weight_PS=1;
    
    float lep1Pt_=-10;
    float lep2Pt_=-10;
    float vis_mass=-10;
    float LeadJetPt = -10;
    float dR_Z_jet=-10;
    bool lep1IsoPassL,lep2IsoPassL,lep1IsoPassV,lep2IsoPassV,OS,SS;
    float tmass,ht,st,Met,FullWeight, dR_lep_lep, Metphi,BoostedTauRawIso, higgs_pT, higgs_m, m_sv_, wtnom_zpt_weight, gen_higgs_pT,gen_leadjet_pT;
    float MuMatchedIsolation= -1; float EleMatchedIsolation =-1;
    int nbjet, gen_matched1_, gen_matched2_,gen_matched1, gen_matched2, gen_nJet;

    bool isGenTauSub_, isGenTauLead_;
    bool Chan_emu, Chan_etau, Chan_mutau, Chan_tautau, Chan_emu_fid, Chan_etau_fid, Chan_mutau_fid, Chan_tautau_fid;
        
    outTr->Branch("evtwt",&FullWeight,"evtwt/F");
    outTr->Branch("pdfWeight", &pdfWeight);
    outTr->Branch("pdfSystWeight", &pdfSystWeight);
    outTr->Branch("pdf", &pdf);    
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
    outTr->Branch("nbjet",&nbjet,"nbjet/I");
    outTr->Branch("gen_higgs_pT",&gen_higgs_pT,"gen_higgs_pT/F");
    outTr->Branch("gen_leadjet_pT",&gen_leadjet_pT,"gen_leadjet_pT/F");
    outTr->Branch("isGenTauLead_",&isGenTauLead_,"isGenTauLead_/O");
    outTr->Branch("isGenTauSub_",&isGenTauSub_,"isGenTauSub_/O");
    outTr->Branch("MuMatchedIsolation",&MuMatchedIsolation,"MuMatchedIsolation/F");
    outTr->Branch("EleMatchedIsolation",&EleMatchedIsolation,"EleMatchedIsolation/F");
    outTr->Branch("gen_matched1_",&gen_matched1_,"gen_matched1_/I");
    outTr->Branch("gen_matched2_",&gen_matched2_,"gen_matched2_/I");
    outTr->Branch("run",&run,"run/I");
    outTr->Branch("event",&event,"event/I");
    outTr->Branch("lumis",&lumis,"lumis/I");
    
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
        plotFill("cutFlowTable",2 ,15,0,15);
        Met=pfMetNoRecoil;
        Metphi=pfMetPhiNoRecoil;

        TLorentzVector LeadTau4Momentum,SubTau4Momentum, Z4Momentum, Met4Momentum, LeadTau4MomentumNominal, SubTau4MomentumNominal;
        //=========================================================================================================
        // Lead tau selection
        int idx_leadtau= leadtauIndex;
        LeadTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(idx_leadtau),boostedTauEta->at(idx_leadtau),boostedTauPhi->at(idx_leadtau),boostedTauMass->at(idx_leadtau));
        LeadTau4MomentumNominal = LeadTau4Momentum;
        bool isGenTauLead= isMatchedToGenTau(LeadTau4Momentum);
        
        if (LeadTau4Momentum.Pt() <= 30 || fabs(boostedTauEta->at(idx_leadtau)) >= 2.3 ) continue;
        if (boostedTaupfTausDiscriminationByDecayModeFinding->at(idx_leadtau) < 0.5 ) continue;
//        if (boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(idx_leadtau) < -0.5) continue;
//        if (boostedTauagainstElectronVLooseMVA62018->at(idx_leadtau) < 0.5) continue;
//        if (boostedTauByLooseMuonRejection3->at(idx_leadtau) < 0.5) continue;
        plotFill("cutFlowTable",3 ,15,0,15);
        
        //=========================================================================================================
        // sublead Tau selection
        int idx_subleadtau= subtauIndex;
        SubTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(idx_subleadtau),boostedTauEta->at(idx_subleadtau),boostedTauPhi->at(idx_subleadtau),boostedTauMass->at(idx_subleadtau));
        SubTau4MomentumNominal = SubTau4Momentum;
        bool isGenTauSub= isMatchedToGenTau(SubTau4Momentum);

        if (SubTau4Momentum.Pt() <= 30 || fabs(boostedTauEta->at(idx_subleadtau)) >= 2.3 ) continue;
        if (boostedTaupfTausDiscriminationByDecayModeFinding->at(idx_subleadtau) < 0.5 ) continue;
//        if (boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(idx_subleadtau) < -0.5) continue;
//        if (boostedTauagainstElectronVLooseMVA62018->at(idx_subleadtau) < 0.5) continue;
//        if (boostedTauByLooseMuonRejection3->at(idx_subleadtau) < 0.5) continue;
        plotFill("cutFlowTable",4 ,15,0,15);
        
        dR_lep_lep= SubTau4Momentum.DeltaR(LeadTau4Momentum);
        if (nJet < 1 ) continue;
        TLorentzVector LeadJet= getLeadJet(LeadTau4Momentum, SubTau4Momentum,JetSys);
            
        //=========================================================================================================
        // Event Selection
        //=========================================================================================================
        Met4Momentum.SetPtEtaPhiM(Met, 0, Metphi, 0);
        Z4Momentum=SubTau4Momentum+LeadTau4Momentum;
        TLorentzVector higgs = SubTau4Momentum+LeadTau4Momentum +Met4Momentum;
        
        
//        if( dR_lep_lep > 0.8 || dR_lep_lep < 0.1) continue;
//        plotFill("cutFlowTable",8 ,15,0,15);
        
        tmass = TMass_F(LeadTau4Momentum.Pt(), LeadTau4Momentum.Px(), LeadTau4Momentum.Py(),  Met,  Metphi);
        plotFill("cutFlowTable",9 ,15,0,15);
        
        
        higgs_pT = higgs.Pt();
//        if (higgs_pT < 250 ) continue; //FIXME removed for Validation study
        plotFill("cutFlowTable",13 ,15,0,15);
        

        OS = boostedTauCharge->at(idx_leadtau) * boostedTauCharge->at(idx_subleadtau) < 0;
        SS =  boostedTauCharge->at(idx_leadtau) * boostedTauCharge->at(idx_subleadtau) > 0;
        lep1IsoPassL = boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNew->at(idx_leadtau) > 0.5;
        lep2IsoPassL = boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNew->at(idx_subleadtau) > 0.5;
        lep1IsoPassV = boostedTauByVLooseIsolationMVArun2v1DBoldDMwLTNew->at(idx_leadtau) > 0.5;
        lep2IsoPassV = boostedTauByVLooseIsolationMVArun2v1DBoldDMwLTNew->at(idx_subleadtau) > 0.5;


        if (SS) continue;
        if (!isGenTauSub || !isGenTauLead) continue;
        
        
        plotFill("CorrelationIsoTot", lep1IsoPassL,lep2IsoPassL,20,0,2,20,0,2,);
        if (higgs_pT < 400) plotFill("CorrelationIsoTotLowPt", lep1IsoPassL,lep2IsoPassL,2,0,2,2,0,2);
        if (higgs_pT > 400) plotFill("CorrelationIsoTotHighPt", lep1IsoPassL,lep2IsoPassL,2,0,2,2,0,2);

        plotFill("higgs_pT_denum", higgs_pT,20,0,1000);
        plotFill("dR_denum", dR_lep_lep,10,1,0);
        plotFill("Rivet_higgsPt_denum", Rivet_higgsPt,20,0,1000);

        if (lep1IsoPassL && lep2IsoPassL) {
        plotFill("higgs_pT_num", higgs_pT,20,0,1000);
        plotFill("dR_num", dR_lep_lep,10,1,0);
        plotFill("Rivet_higgsPt_num", Rivet_higgsPt,20,0,1000);
        }
                
        
        lep1Pt_=LeadTau4Momentum.Pt();
        lep2Pt_=SubTau4Momentum.Pt();
        vis_mass=Z4Momentum.M();
        LeadJetPt = LeadJet.Pt();
        dR_Z_jet=LeadJet.DeltaR(Z4Momentum);
        BoostedTauRawIso=boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(idx_subleadtau);
        m_sv_=m_sv;
        //  Weights
//        FullWeight = LumiWeight*LepCorrection * PUWeight * TriggerWeight*zmasspt_weight * preFireWeight * WBosonKFactor * ttbar_rwt* weight_Rivet *weight_g_NNLOPS* Weight_PS;
//        nbjet=numBJet;
        gen_higgs_pT = Rivet_higgsPt;
        gen_leadjet_pT = Rivet_j1pt;
        gen_nJet = Rivet_nJets30;
        isGenTauSub_=isGenTauSub;
        isGenTauLead_=isGenTauLead;
                
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

