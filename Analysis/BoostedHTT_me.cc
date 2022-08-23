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

    bool isEmbed= false;
    if (sample.find("Embed") != string::npos) isEmbed= true;

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
    Run_Tree= Xttree(InputFile,"mue_tree");
//    Run_Tree= Xttree(InputFile,"EventTree");
    
    //    auto HistoTot = reinterpret_cast<TH1D*>(InputFile->Get("ggNtuplizer/hEvents"));
    TH1F * HistoTot = (TH1F*) InputFile->Get("hcount");
    auto fout = new TFile(filename.c_str(), "RECREATE");
    
    myMap1 = new std::unordered_map<std::string, TH1F*>();
    myMap2 = new unordered_map<string, TH2F*>();
    
//    TTree * outTr=  new TTree("mue_tree","mue_tree"); // Now change to emu to be able to combine before training NN
    TTree * outTr=  new TTree("emu_tree","emu_tree");
    
    //########################################
    // Muon Id, Iso, Trigger and Tracker Eff files
    //########################################
    TH2F** HistoMuId=FuncHistMuId(year);
    TH2F** HistoMuIso=FuncHistMuIso(year);
    TH2F** HistoMuTrg50=FuncHistMuTrigger_50(year);
    TH2F** HistoMuTrg27=FuncHistMuTrigger_27(year);
    //    TGraphAsymmErrors * HistoMuTrack=FuncHistMuTrack();
    TH2F** HistoEleId=FuncHistEleId(year);
    
    TFile* SF_files = TFile::Open("data/htt_scalefactors_legacy_2018.root", "READ");
    RooWorkspace *ws_SF = reinterpret_cast<RooWorkspace *>(SF_files->Get("w"));
    SF_files->Close();
    
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
    
    float DeepCSVCut=   1000   ;                  //  Medium  https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
    if (year== 2016) DeepCSVCut =       0.6321    ;
    if (year== 2017) DeepCSVCut =      0.4941    ;
    if (year== 2018) DeepCSVCut =      0.4184     ;


//    float DeepCSVCut=   1000   ;                  //  Loose  https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
//    if (year== 2016) DeepCSVCut =      0.2217   ;
//    if (year== 2017) DeepCSVCut =     0.1522   ;
//    if (year== 2018) DeepCSVCut =     0.1241    ;

    
    float LeptonIsoCut=0.30;
    bool debug= false;
    float MuIdCorrection=1;
    float MuIsoCorrection=1;
    float MuTrgCorrection=1;
    float LepCorrection=1;
    float EleIdCorrection =1;
    float LumiWeight = 1;
    float PUWeight = 1;
    float zmasspt_weight=1;
    float WBosonKFactor=1;
    float preFireWeight = 1;
    float ttbar_rwt=1;
    float zmasspt_weight_err=0;
    float zmasspt_weight_nom=1;
    float weight_Rivet =1;
    float weight_g_NNLOPS = 1;

    float lepPt_=-10;
    float elept_=-10;
    float vis_mass=-10;
    float LeadJetPt = -10;
    float dR_Z_jet=-10;
    bool OS,SS,lep1IsoPass,lep2IsoPass;
    float tmass,tmass2, ht,st,Met,FullWeight, dR_lep_lep, Metphi, higgs_pT, higgs_m, m_sv_, wtnom_zpt_weight, gen_higgs_pT,gen_leadjet_pT;
    float MuMatchedIsolation= -1; float EleMatchedIsolation =-1;
    float IsoLep1Value, IsoLep2Value, D_zeta;
    int nbjet, gen_matched1_, gen_matched2_,gen_matched1, gen_matched2;

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
    outTr->Branch("pdfWeight", &pdfWeight);
    outTr->Branch("pdfSystWeight", &pdfSystWeight);
    outTr->Branch("pdf", &pdf);
    outTr->Branch("zmasspt_weight",&zmasspt_weight,"zmasspt_weight/F");
    outTr->Branch("lep1Pt",&lepPt_,"lep1Pt/F");
    outTr->Branch("lep2Pt",&elept_,"lep2Pt/F");
    outTr->Branch("OS",&OS,"OS/O");
    outTr->Branch("SS",&SS,"SS/O");
    outTr->Branch("lep1IsoPass",&lep1IsoPass,"lep1IsoPass/O");
    outTr->Branch("lep2IsoPass",&lep2IsoPass,"lep2IsoPass/O");
    outTr->Branch("vis_mass",&vis_mass,"vis_mass/F");
    outTr->Branch("tmass",&tmass,"tmass/F");
    outTr->Branch("ht",&ht,"ht/F");
    outTr->Branch("st",&st,"st/F");
    outTr->Branch("Met",&Met,"Met/F");
    outTr->Branch("LeadJetPt",&LeadJetPt,"LeadJetPt/F");
    outTr->Branch("dR_lep_lep",&dR_lep_lep,"dR_lep_lep/F");
    outTr->Branch("IsoLep1Value",&IsoLep1Value,"IsoLep1Value/F");
    outTr->Branch("IsoLep2Value",&IsoLep2Value,"IsoLep2Value/F");
    outTr->Branch("higgs_pT",&higgs_pT,"higgs_pT/F");
    outTr->Branch("higgs_m",&higgs_m,"higgs_m/F");
    outTr->Branch("m_sv",&m_sv_,"m_sv/F");
    outTr->Branch("dR_Z_jet",&dR_Z_jet,"dR_Z_jet/F");
    outTr->Branch("nbjet",&nbjet,"nbjet/I");
    outTr->Branch("gen_higgs_pT",&gen_higgs_pT,"gen_higgs_pT/F");
    outTr->Branch("gen_leadjet_pT",&gen_leadjet_pT,"gen_leadjet_pT/F");
    outTr->Branch("MuMatchedIsolation",&MuMatchedIsolation,"MuMatchedIsolation/F");
    outTr->Branch("EleMatchedIsolation",&EleMatchedIsolation,"EleMatchedIsolation/F");
    outTr->Branch("D_zeta",&D_zeta,"D_zeta/F");
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
        // Trigger
        bool HLT_Mu50 = ((HLTEleMuX >> 21 & 1)==1); // else if (name.find("HLT_Mu50_v")  != string::npos) bitEleMuX = 21;
        bool HLT_Mu27 = ((HLTEleMuX >> 19 & 1)==1); // else if (name.find("HLT_IsoMu27_v") != string::npos) bitEleMuX = 19;
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
        
//        if (syst == "met_reso_Up") {Met = met_reso_Up; Metphi=metphi_reso_Up;}
//        if (syst == "met_resp_Up") {Met = met_resp_Up; Metphi=metphi_resp_Up;}
//        if (syst == "met_reso_Down") {Met = met_reso_Down; Metphi=metphi_reso_Down;}
//        if (syst == "met_resp_Down") {Met = met_resp_Down; Metphi=metphi_resp_Down;}
        
        TLorentzVector Mu4Momentum,Ele4Momentum, Z4Momentum, Met4Momentum;
        //=========================================================================================================
        // Muon selection
        int idx_mu= lepIndex;
        int idx_ele= tauIndex;
        
        
        Mu4Momentum.SetPtEtaPhiM(muPt->at(idx_mu),muEta->at(idx_mu),muPhi->at(idx_mu),MuMass);
        
        bool selectMuon_1= false;
        bool selectMuon_2= false;
        
        IsoLep1Value=muPFChIso->at(idx_mu)/muPt->at(idx_mu);
        if ( (muPFNeuIso->at(idx_mu) + muPFPhoIso->at(idx_mu) - 0.5* muPFPUIso->at(idx_mu) )  > 0.0)
            IsoLep1Value= ( muPFChIso->at(idx_mu) + muPFNeuIso->at(idx_mu) + muPFPhoIso->at(idx_mu) - 0.5* muPFPUIso->at(idx_mu))/muPt->at(idx_mu);
        
        // from 30 to 28
        if (muPt->at(idx_mu) < 28 || fabs(muEta->at(idx_mu)) > 2.4) continue;
        plotFill("cutFlowTable",2 ,15,0,15);
        
        bool MuId=( (muIDbit->at(idx_mu) >> 1 & 1)  && fabs(muD0->at(idx_mu)) < 0.045 && fabs(muDz->at(idx_mu)) < 0.2);
        MuIdCorrection = getCorrFactorMuonId(year, isData,  Mu4Momentum.Pt(), Mu4Momentum.Eta() ,HistoMuId);
        
        if (! MuId) continue;
        plotFill("cutFlowTable",3 ,15,0,15);
        
        // 55 to 52 and met from 40 to 30
        if (muPt->at(idx_mu) < 52  && HLT_Mu27 && Met > 30 && elePt->at(idx_ele) < 37){
            selectMuon_1 = true;
            MuTrgCorrection = getCorrFactorMuonTrg(isData,  Mu4Momentum.Pt(), Mu4Momentum.Eta() ,HistoMuTrg27);
            MuIsoCorrection = getCorrFactorMuonIso(year, isData,  Mu4Momentum.Pt(), Mu4Momentum.Eta() ,HistoMuIso);
            
        }
        // 55 to 52
        if (muPt->at(idx_mu) >= 52  && HLT_Mu50 ) {
            selectMuon_2 = true;
            MuTrgCorrection = getCorrFactorMuonTrg(isData,  Mu4Momentum.Pt(), Mu4Momentum.Eta() ,HistoMuTrg50);
        }
        
        if (!selectMuon_1 && !selectMuon_2) continue;
        plotFill("cutFlowTable",4 ,15,0,15);
        //=========================================================================================================
        // Electron selection
        Ele4Momentum.SetPtEtaPhiM(elePt->at(idx_ele),eleEta->at(idx_ele),elePhi->at(idx_ele),eleMass);
        
        if (elePt->at(idx_ele) <= 10 || fabs(eleEta->at(idx_ele)) >= 2.5) continue;
        plotFill("cutFlowTable",5 ,15,0,15);
        
        bool eleMVAId= false;
        if (fabs (eleSCEta->at(idx_ele)) <= 0.8 && eleIDMVANoIso->at(idx_ele) >    0.837   ) eleMVAId= true;
        else if (fabs (eleSCEta->at(idx_ele)) >  0.8 &&fabs (eleSCEta->at(idx_ele)) <=  1.5 && eleIDMVANoIso->at(idx_ele) >    0.715   ) eleMVAId= true;
        else if ( fabs (eleSCEta->at(idx_ele)) >=  1.5 && eleIDMVANoIso->at(idx_ele) >   0.357   ) eleMVAId= true;
        else eleMVAId= false;
        if (!eleMVAId) continue;

        plotFill("cutFlowTable",6 ,15,0,15);
        IsoLep2Value=elePFChIso->at(idx_ele)/elePt->at(idx_ele);
        if ( (elePFNeuIso->at(idx_ele) + elePFPhoIso->at(idx_ele) - 0.5* elePFPUIso->at(idx_ele) )  > 0.0)
            IsoLep2Value= ( elePFChIso->at(idx_ele) + elePFNeuIso->at(idx_ele) + elePFPhoIso->at(idx_ele) - 0.5* elePFPUIso->at(idx_ele))/elePt->at(idx_ele);
        
        
        EleIdCorrection = getCorrFactorEleId(isData,  Ele4Momentum.Pt(), eleSCEta->at(idx_ele) ,HistoEleId);
                                
        LepCorrection= MuIdCorrection * MuIsoCorrection * MuTrgCorrection * EleIdCorrection;


        bool MuMatchedTauStatus=MatchedBoostedTauId(Mu4Momentum);
        bool muonIsoStatu = IsoLep1Value < LeptonIsoCut;
        plotFill("IsoCorrelationMu",muonIsoStatu, MuMatchedTauStatus, 2, 0, 2, 2, 0, 2);
//        plotFill("cutFlowTable",2 ,15,0,15);
//        if (!MuMatchedTauStatus ) continue;
        MuMatchedIsolation = MatchedBoostedTauIsolation(Mu4Momentum);

        bool EleMatchedTauStatus=MatchedBoostedTauId(Ele4Momentum);
        bool eleIsoStatu = IsoLep2Value < LeptonIsoCut;
        plotFill("IsoCorrelationEle",eleIsoStatu, EleMatchedTauStatus, 2, 0, 2, 2, 0, 2);
//        plotFill("cutFlowTable",2 ,15,0,15);
//        if (!EleMatchedTauStatus ) continue;
        EleMatchedIsolation = MatchedBoostedTauIsolation(Ele4Momentum);

        
        //=========================================================================================================
        // Event Selection
        Met4Momentum.SetPtEtaPhiM(Met, 0, Metphi, 0);
        Z4Momentum=Ele4Momentum+Mu4Momentum;
        TLorentzVector higgs = Ele4Momentum+Mu4Momentum +Met4Momentum;
//        if (event==58851135 || event==17274037) cout<<"Hey there is an event with njet ======0\n";
        if (nJet < 1 ) continue;
        TLorentzVector LeadJet= getLeadJet(Mu4Momentum, Ele4Momentum,JetSys);

        dR_lep_lep= Ele4Momentum.DeltaR(Mu4Momentum);
        if( dR_lep_lep > 0.8 || dR_lep_lep < 0.1) continue;
        plotFill("cutFlowTable",7 ,15,0,15);
        
        tmass = TMass_F(Z4Momentum.Pt(), Z4Momentum.Px(), Z4Momentum.Py(),  Met,  Metphi);
        
        // calculate mt, x and y for systematics as well
        float met_x = Met * cos(Metphi);
        float met_y = Met * sin(Metphi);
        
        // calculate D_zeta
        float zeta_x = (Ele4Momentum.Px()/Ele4Momentum.Pt()+ Mu4Momentum.Px()/Mu4Momentum.Pt());
        float zeta_y = (Ele4Momentum.Py()/Ele4Momentum.Pt()+ Mu4Momentum.Py()/Mu4Momentum.Pt());
        float zeta = sqrt (zeta_x*zeta_x + zeta_y*zeta_y);
        float p_zeta_x= (Ele4Momentum.Px() + Mu4Momentum.Px() + met_x)*zeta_x/zeta;
        float p_zeta_y= (Ele4Momentum.Py() + Mu4Momentum.Py() + met_y)*zeta_y/zeta;
        float p_zeta_vis_x= (Ele4Momentum.Px() + Mu4Momentum.Px() )*zeta_x/zeta;
        float p_zeta_vis_y= (Ele4Momentum.Py() + Mu4Momentum.Py() )*zeta_y/zeta;
        
        D_zeta = (p_zeta_x + p_zeta_y)  - 1.85*(p_zeta_vis_x + p_zeta_vis_y);
        
        
        
        if (tmass > 80 ) continue;//remove for OS/SS
        plotFill("cutFlowTable",8 ,15,0,15);
        
        if (m_sv < 50) continue; //remove for OS/SS
        plotFill("cutFlowTable",9 ,15,0,15);
        
        // BJet veto
        int numBJet=numBJets(BJetPtCut,DeepCSVCut,JetSys);
        if (numBJet > 0) continue;
        plotFill("cutFlowTable",10 ,15,0,15);
        
        // HT cut
        ht= getHT(JetPtCut, Mu4Momentum, Ele4Momentum,JetSys);
        if (ht < 200) continue;
        plotFill("cutFlowTable",11 ,15,0,15);
        
        // ST definition
        st= getST(JetPtCut,JetSys);
        
        //electron veto
        int numele =getNumElectron();
        if (numele > 1) continue;
        plotFill("cutFlowTable",12 ,15,0,15);
        
        //muon veto
        int numMu =getNumMuon();
        if (numMu > 1) continue;
        plotFill("cutFlowTable",13 ,15,0,15);

        if (higgs.Pt() < 250) continue;   //remove for OS/SS
        plotFill("cutFlowTable",14 ,15,0,15);


        //=========================================================================================================
        float embedWeight = 1;
        if (isEmbed){
            
            if (genWeight > 1 || genWeight < 0) {
                LumiWeight=0;
            }
            else {
                LumiWeight = genWeight;
            }


            ws_SF->var("m_pt")->setVal(Mu4Momentum.Pt());
            ws_SF->var("m_eta")->setVal(Mu4Momentum.Eta());
            ws_SF->var("m_iso")->setVal(IsoLep1Value);
            ws_SF->var("e_pt")->setVal(Ele4Momentum.Pt());
            ws_SF->var("e_eta")->setVal(Ele4Momentum.Eta());
            ws_SF->var("e_iso")->setVal(IsoLep2Value);
            
            embedWeight *= ws_SF->function("m_trk_ratio")->getVal();
            embedWeight *= ws_SF->function("e_trk_embed_ratio")->getVal();
            embedWeight *= ws_SF->function("e_idiso_ic_embed_ratio")->getVal();
            embedWeight *= ws_SF->function("m_idiso_ic_embed_ratio")->getVal();
            
            //         scalefactor correcting for the efficiency of the DoubleMuon-HLT during selection
            ws_SF->var("gt1_pt")->setVal(getMatchedGenMu(Mu4Momentum).Pt());
            ws_SF->var("gt1_eta")->setVal(getMatchedGenMu(Mu4Momentum).Eta());
            ws_SF->var("gt2_pt")->setVal(getMatchedGenEle(Ele4Momentum).Pt());
            ws_SF->var("gt2_eta")->setVal(getMatchedGenEle(Ele4Momentum).Eta());
            
            double trg_ratio_new(ws_SF->function("m_sel_trg_ic_ratio")->getVal());
            embedWeight *= trg_ratio_new;
            
            //          scalefactor correcting for the efficiency of the DoubleMuon-HLT during selection
            ws_SF->var("gt_pt")->setVal(Ele4Momentum.Pt());
            ws_SF->var("gt_eta")->setVal(Ele4Momentum.Eta());
            double id_ratio_1_new(ws_SF->function("m_sel_id_ic_ratio")->getVal());
            embedWeight *= id_ratio_1_new;
            
            //          scalefactor correcting for the efficiency of the muon ID during selection
            ws_SF->var("gt_pt")->setVal(getMatchedGenMu(Mu4Momentum).Pt());
            ws_SF->var("gt_eta")->setVal(getMatchedGenMu(Mu4Momentum).Eta());
            double id_ratio_2_new(ws_SF->function("m_sel_id_ic_ratio")->getVal());
            embedWeight *= id_ratio_2_new;
            
  
  }
  
        if (!isData){
            
            // Lumi weight
            LumiWeight = getLuminsoity(year,"me") * XSection(sample)*1.0 / HistoTot->GetBinContent(2);

            float PUMC_=HistoPUMC->GetBinContent(puTrue->at(0)+1);
            float PUData_=HistoPUData->GetBinContent(puTrue->at(0)+1);

            if (PUMC_ ==0)
                cout<<"PUMC_ is zero!!! & num pileup= "<< puTrue->at(0)<<"\n";
            else
                PUWeight= PUData_/PUMC_;
            
            // prefire
            preFireWeight = L1ECALPrefire;
            if (syst == "prefireUp") {preFireWeight = L1ECALPrefireUp;}
            if (syst == "prefireDown") {preFireWeight = L1ECALPrefireDown;}
            
        //=========================================================================================================
        // Separate Drell-Yan processes
         gen_matched1 = ZCategory(Mu4Momentum);
         gen_matched2 = ZCategory(Ele4Momentum);


//        if (name == "ZLL" && (gen_matched1 >4 || gen_matched2 >4)) {
//            continue;
//        } else if ((name == "ZTT") && (gen_matched1 <5 && gen_matched2 < 5)) {
//            continue;
//        }
//
//        int Zcateg = ZCategory(Ele4Momentum);
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

        higgs_pT = higgs.Pt();
        higgs_m = higgs.M();
        OS = muCharge->at(idx_mu) * eleCharge->at(idx_ele) < 0;
        SS =  muCharge->at(idx_mu) * eleCharge->at(idx_ele) > 0;
        lep1IsoPass= selectMuon_1? IsoLep1Value < LeptonIsoCut : 1;
        lep2IsoPass= selectMuon_1? IsoLep2Value < LeptonIsoCut : 1;
        lepPt_=muPt->at(idx_mu);
        elept_=elePt->at(idx_ele);
        vis_mass=Z4Momentum.M();
        LeadJetPt = LeadJet.Pt();
        dR_Z_jet=LeadJet.DeltaR(Z4Momentum);
        m_sv_=m_sv;
        FullWeight = LumiWeight*LepCorrection*PUWeight*zmasspt_weight * WBosonKFactor * preFireWeight * ttbar_rwt* weight_Rivet *embedWeight;
        nbjet= numBJet;
        gen_higgs_pT = Rivet_higgsPt;
        gen_leadjet_pT = Rivet_j1pt;

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


