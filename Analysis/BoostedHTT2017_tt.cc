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
    // Muon Id, Iso, Trigger and Tracker Eff files
    //########################################
    TH2F** HistoMuId=FuncHistMuId();
    TH2F** HistoMuIso=FuncHistMuIso();
    TH2F** HistoMuTrg=FuncHistMuTrigger();
    TGraphAsymmErrors * HistoMuTrack=FuncHistMuTrack();
    
    //########################################
    // Pileup files
    //########################################
    
    TH1F *  HistoPUData =HistPUData();
    
//    size_t isInputData = InputFile->find("Data");
    size_t isInputData = fname.find("Data");
    TH1F * HistoPUMC = new TH1F();
    if (isInputData== string::npos)
        HistoPUMC=HistPUMC(InputFile);
    
    
    
    
    // H->tau tau scale factors
    TFile htt_sf_file("data/htt_scalefactors_2017_v2.root");
    RooWorkspace *htt_sf = reinterpret_cast<RooWorkspace*>(htt_sf_file.Get("w"));
    htt_sf_file.Close();
    
//    // Z-pT reweighting
//    TFile *zpt_file = new TFile("data/zpt_weights_2016_BtoH.root");
//    auto zpt_hist = reinterpret_cast<TH2F*>(zpt_file->Get("zptmass_histo"));
    
    
//    size_t isInputData = fname.find("Data");
    
    //    reweight::LumiReWeighting* PU_weights;
    //    // PU reweighting
    //    if (isInputData== string::npos){
    //        // read inputs for lumi reweighting
    //        PU_weights = new reweight::LumiReWeighting(fname, "pileup/pu_distributions_data_2017.root", "hPUTrue", "pileup");
    //    }
    
    //###############################################################################################
    // Parameters
    //###############################################################################################
    float MuMass= 0.10565837;
    float eleMass= 0.000511;
    float JetPtCut=30;
    float BJetPtCut=20;
    
    //    float CSVCut=   0.9535   ;                  //  https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation80XReReco
    float CSVCut=   0.8838   ;                  //  medium  https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
    float LeptonIsoCut=0.15;
    bool debug= false;
    //    float luminosity=    35867;
    float luminosity=    41530;
    
    
    float leadPt_=-10;
    float subPt_=-10;
    float vis_mass=-10;
    float LeadJetPt = -10;
    float dR_Z_jet=-10;
    bool PassLead,PassSub,PassLeadCombined,PassSubCombined,PassLeadCharged,PassSubCharged,OS,SS;
    float tmass,ht,st,Met,FullWeight, dR_tau_tau, Metphi,BoostedTauRawIso, higgs_pT, higgs_m, m_sv_, wtnom_zpt_weight;
    
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
    
    
    Int_t nentries_wtn = (Int_t) Run_Tree->GetEntries();
    cout<<"nentries_wtn===="<<nentries_wtn<<"\n";
    for (Int_t i = 0; i < nentries_wtn; i++) {
        
        Run_Tree->GetEntry(i);
        if (i % 1000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);
        
        plotFill("cutFlowTable",1 ,15,0,15);
        //=========================================================================================================
        // Trigger
        bool PassTrigger_37 = ((HLTJet >> 37 & 1)==1); //HLT_AK8PFHT800_TrimMass50_v
        bool PassTrigger_38 = ((HLTJet >> 38 & 1)==1); //HLT_PFHT1050_v
        bool PassTrigger_39 = ((HLTJet >> 39 & 1)==1); //HLT_PFHT500_PFMET100_PFMHT100_IDTight_v
        bool PassTrigger_40 = ((HLTJet >> 40 & 1)==1); //HLT_AK8PFJet400_TrimMass30_v
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
//        if (boostedTaupfTausDiscriminationByDecayModeFinding->at(idx_leadtau) < 0.5 ) continue;
        if (boostedTauByMVA6VLooseElectronRejection->at(idx_leadtau) < 0.5) continue;
        if (boostedTauByLooseMuonRejection3->at(idx_leadtau) < 0.5) continue;
    LeadTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(idx_leadtau),boostedTauEta->at(idx_leadtau),boostedTauPhi->at(idx_leadtau),boostedTauMass->at(idx_leadtau));
        plotFill("cutFlowTable",3 ,15,0,15);
        
        TLorentzVector leadMatch= getMatchedGenTau(LeadTau4Momentum);
        plotFill("GenMatchedLeadTau",leadMatch.DeltaR(LeadTau4Momentum) ,20,0,1);
        vector<float> leadRecoMatch= getMatchedRecoTau(LeadTau4Momentum);

        //=========================================================================================================
        // sublead Tau selection
        int idx_subleadtau= subtauIndex;
        
        if (boostedTauPt->at(idx_subleadtau) <= 40 || fabs(boostedTauEta->at(idx_subleadtau)) >= 2.3 ) continue;
//        if (boostedTaupfTausDiscriminationByDecayModeFinding->at(idx_subleadtau) < 0.5 ) continue;
        if (boostedTauByMVA6VLooseElectronRejection->at(idx_subleadtau) < 0.5) continue;
        if (boostedTauByLooseMuonRejection3->at(idx_subleadtau) < 0.5) continue;
        
    SubTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(idx_subleadtau),boostedTauEta->at(idx_subleadtau),boostedTauPhi->at(idx_subleadtau),boostedTauMass->at(idx_subleadtau));
        plotFill("cutFlowTable",4 ,15,0,15);
        
        TLorentzVector subMatch= getMatchedGenTau(SubTau4Momentum);
        plotFill("GenMatchedSubTau",subMatch.DeltaR(SubTau4Momentum) ,20,0,1);
        vector<float> subRecoMatch= getMatchedRecoTau(SubTau4Momentum);

        dR_tau_tau= SubTau4Momentum.DeltaR(LeadTau4Momentum);
        
        //=========================================================================================================
        //  Tau POG tests
        //=========================================================================================================
        int numIso=0;
        int numIsoOverLap=0;
        float EnergyIso=0;
        float EnergyIsoOverLap=0;
        
        //=========== Charge PFCandidates==========
        for (int i=0; i< boostedTauIsolationPFCands->at(idx_leadtau).size(); i++){
            numIso++;
            EnergyIso +=boostedTauIsolationPFCands->at(idx_leadtau)[i];
            // overlap with subleading SignalPFCandidates
            for (int j=0; j< boostedTauSignalPFCands->at(idx_subleadtau).size(); j++){
                if (boostedTauIsolationPFCands->at(idx_leadtau)[i] ==  boostedTauSignalPFCands->at(idx_subleadtau)[j]) {
                    numIsoOverLap++;
                    EnergyIsoOverLap +=boostedTauIsolationPFCands->at(idx_leadtau)[i];
                }
            }
            // overlap with subleading IsoPFCandidates
            for (int j=0; j< boostedTauIsolationPFCands->at(idx_subleadtau).size(); j++){
                if (boostedTauIsolationPFCands->at(idx_leadtau)[i] ==  boostedTauIsolationPFCands->at(idx_subleadtau)[j]) {
                    numIsoOverLap++;
                    EnergyIsoOverLap +=boostedTauIsolationPFCands->at(idx_leadtau)[i];
                }
            }
        }
        //===========  PFGammaCandidates==========
        for (int i=0; i< boostedTauIsolationPFGammaCands->at(idx_leadtau).size(); i++){
            numIso++;
            EnergyIso +=boostedTauIsolationPFGammaCands->at(idx_leadtau)[i];
            // overlap with subleading SignalPFCandidates
            for (int j=0; j< boostedTauSignalPFGammaCands->at(idx_subleadtau).size(); j++){
                if (boostedTauIsolationPFGammaCands->at(idx_leadtau)[i] == boostedTauSignalPFGammaCands->at(idx_subleadtau)[j]) {
                    numIsoOverLap++;
                    EnergyIsoOverLap +=boostedTauIsolationPFGammaCands->at(idx_leadtau)[i];
                }
            }
            // overlap with subleading IsoPFCandidates
            for (int j=0; j< boostedTauIsolationPFGammaCands->at(idx_subleadtau).size(); j++){
                if (boostedTauIsolationPFGammaCands->at(idx_leadtau)[i] == boostedTauIsolationPFGammaCands->at(idx_subleadtau)[j]) {
                    numIsoOverLap++;
                    EnergyIsoOverLap +=boostedTauIsolationPFGammaCands->at(idx_leadtau)[i];
                }
            }
        }
                
            
            
//        cout <<"\t leading Tau pt is "<<boostedTauPt->at(idx_leadtau)<<"\n";
//        for (int i=0; i< boostedTauSignalPFCands->at(idx_leadtau).size(); i++)
//            cout<<"boostedTauSignalPFCands->at(idx_leadtau)["<<i<<"] " <<boostedTauSignalPFCands->at(idx_leadtau)[i]<<"\n";
//        for (int i=0; i< boostedTauSignalPFGammaCands->at(idx_leadtau).size(); i++)
//            cout<<"boostedTauSignalPFGammaCands->at(idx_leadtau)["<<i<<"] " <<boostedTauSignalPFGammaCands->at(idx_leadtau)[i]<<"\n";
//        for (int i=0; i< boostedTauIsolationPFCands->at(idx_leadtau).size(); i++)
//            cout<<"boostedTauIsolationPFCands->at(idx_leadtau)["<<i<<"] " <<boostedTauIsolationPFCands->at(idx_leadtau)[i]<<"\n";
//        for (int i=0; i< boostedTauIsolationPFGammaCands->at(idx_leadtau).size(); i++)
//            cout<<"boostedTauIsolationPFGammaCands->at(idx_leadtau)["<<i<<"] " <<boostedTauIsolationPFGammaCands->at(idx_leadtau)[i]<<"\n";

//        cout <<"\t Subleading Tau pt is "<<boostedTauPt->at(idx_subleadtau)<<"\n";
//        for (int i=0; i< boostedTauSignalPFCands->at(idx_subleadtau).size(); i++)
//            cout<<"boostedTauSignalPFCands->at(idx_subleadtau)["<<i<<"] " <<boostedTauSignalPFCands->at(idx_subleadtau)[i]<<"\n";
//        for (int i=0; i< boostedTauSignalPFGammaCands->at(idx_subleadtau).size(); i++)
//            cout<<"boostedTauSignalPFGammaCands->at(idx_subleadtau)["<<i<<"] " <<boostedTauSignalPFGammaCands->at(idx_subleadtau)[i]<<"\n";
//        for (int i=0; i< boostedTauIsolationPFCands->at(idx_subleadtau).size(); i++)
//            cout<<"boostedTauIsolationPFCands->at(idx_subleadtau)["<<i<<"] " <<boostedTauIsolationPFCands->at(idx_subleadtau)[i]<<"\n";
//        for (int i=0; i< boostedTauIsolationPFGammaCands->at(idx_subleadtau).size(); i++)
//            cout<<"boostedTauIsolationPFGammaCands->at(idx_subleadtau)["<<i<<"] " <<boostedTauIsolationPFGammaCands->at(idx_subleadtau)[i]<<"\n";

        
        plotFill("dR_ratio_multiplicity",dR_tau_tau,numIsoOverLap*1.0/numIso,10,0,1,10,0,1);
        plotFill("dR_ratio_energy",dR_tau_tau,EnergyIsoOverLap*1.0/EnergyIso,10,0,1,10,0,1);
        
        if (dR_tau_tau < 0.5){
                    
            plotFill("GenMatchedLeadCombineIso",boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits->at(idx_leadtau) - leadRecoMatch[5]  ,2000,-200,200);
            plotFill("GenMatchedSubCombineIso",boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits->at(idx_subleadtau) - leadRecoMatch[5]  ,2000,-200,200);
            plotFill("GenMatchedLeadMVAIso",leadRecoMatch[1] - boostedTauByIsolationMVArun2v1DBoldDMwLTraw->at(idx_leadtau) ,200,-1,1);
            plotFill("GenMatchedSubMVAIso",subRecoMatch[1] - boostedTauByIsolationMVArun2v1DBoldDMwLTraw->at(idx_subleadtau) ,200,-1,1);
            }

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
        int numBJet=numBJets(BJetPtCut,CSVCut);
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
        
        //=========================================================================================================
        // Separate Drell-Yan processes
        int Zcateg = ZCategory(SubTau4Momentum);
        if (name == "ZLL" && Zcateg > 4) {
            continue;
        } else if ((name == "ZTT") &&Zcateg != 5) {
            continue;
        } else if (name == "ZJ" && Zcateg != 6) {
            continue;
        }
        
        //=========================================================================================================
        // Weights & Correction
        
        float LumiWeight = 1;
        float PUWeight = 1;
        float LepCorrection=1;
//        float nom_zpt_weight=1.0;
        //  GenInfo
//        vector<float>  genInfo=GeneratorInfo();
//        float ZBosonPt=genInfo[3];
//        float ZBosonMass=genInfo[4];

        
        if (!isData){
            
            // Lumi weight
            LumiWeight = luminosity * XSection(sample)*1.0 / HistoTot->GetBinContent(2);
            
            // Pilu up weights
            int puNUmmc=int(puTrue->at(0)*5);
            int puNUmdata=int(puTrue->at(0)*5);
            float PUMC_=HistoPUMC->GetBinContent(puNUmmc+1);
            float PUData_=HistoPUData->GetBinContent(puNUmdata+1);
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
        PassLead = boostedTauByLooseIsolationMVArun2v1DBoldDMwLT->at(idx_leadtau) > 0.5 ;
        PassSub = boostedTauByLooseIsolationMVArun2v1DBoldDMwLT->at(idx_subleadtau) > 0.5 ;
        PassLeadCombined = boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits->at(idx_leadtau) > 0.5 ;
        PassSubCombined = boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits->at(idx_subleadtau) > 0.5 ;
        PassLeadCharged = boostedTauChargedIsoPtSum->at(idx_leadtau) < 2.0 ;
        PassSubCharged = boostedTauChargedIsoPtSum->at(idx_subleadtau) < 2.0 ;

        
        
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


