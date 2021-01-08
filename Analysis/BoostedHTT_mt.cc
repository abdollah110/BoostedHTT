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
    Run_Tree= Xttree(InputFile,"mutau_tree");
    //    Run_Tree= Xttree(InputFile,"EventTree");
    
    
    //    auto HistoTot = reinterpret_cast<TH1D*>(InputFile->Get("ggNtuplizer/hEvents"));
    TH1F * HistoTot = (TH1F*) InputFile->Get("hcount");
    auto fout = new TFile(filename.c_str(), "RECREATE");
    
    myMap1 = new std::map<std::string, TH1F*>();
    myMap2 = new map<string, TH2F*>();
    
    TTree * outTr=  new TTree("mutau_tree","mutau_tree");
    
    
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
        HistoPUMC=HistPUMC(InputFile);
    
    
    
    
    // H->tau tau scale factors
    TFile htt_sf_file("data/htt_scalefactors_2017_v2.root");
    RooWorkspace *htt_sf = reinterpret_cast<RooWorkspace*>(htt_sf_file.Get("w"));
    htt_sf_file.Close();
    
    //    // Z-pT reweighting
    //    TFile *zpt_file = new TFile("data/zpt_weights_2016_BtoH.root");
    //    auto zpt_hist = reinterpret_cast<TH2F*>(zpt_file->Get("zptmass_histo"));
    
    
    //###############################################################################################
    // Parameters
    //###############################################################################################
    float MuMass= 0.10565837;
    float eleMass= 0.000511;
    float JetPtCut=30;
    float BJetPtCut=20;
    
    float DeepCSVCut= 1   ;                  //  Tight  https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
    if (year== 2016) DeepCSVCut =     0.8953  ;
    if (year== 2017) DeepCSVCut =     0.8001  ;
    if (year== 2018) DeepCSVCut =    0.7527   ;
    
    
    float LeptonIsoCut=0.30;
    bool debug= false;
    

    
    float lepPt_=-10;
    float taupt_=-10;
    float vis_mass=-10;
    float LeadJetPt = -10;
    float dR_Z_jet=-10;
    bool OS,SS,lep1IsoPass,lep2IsoPass;
    float tmass,ht,st,Met,FullWeight, dR_lep_lep, Metphi,BoostedTauRawIso, higgs_pT, higgs_m, m_sv_, wtnom_zpt_weight;
    
    outTr->Branch("evtwt",&FullWeight,"evtwt/F");
    //    outTr->Branch("evtwtZpt",&wtnom_zpt_weight,"evtwtZPt/F");
    outTr->Branch("lep1Pt",&lepPt_,"lep1Pt/F");
    outTr->Branch("lep2Pt",&taupt_,"lep2Pt/F");
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
        bool HLT_Mu50 = ((HLTEleMuX >> 21 & 1)==1); // else if (name.find("HLT_Mu50_v")  != string::npos) bitEleMuX = 21;
        bool HLT_Mu27 = ((HLTEleMuX >> 19 & 1)==1); // else if (name.find("HLT_IsoMu27_v") != string::npos) bitEleMuX = 19;
        
        //=========================================================================================================
        // MET Filters
        // Here we apply MET Filters
        // Here we apply prefire weights
    float MuIdCorrection=1;
    float MuIsoCorrection=1;
    float MuTrgCorrection=1;
    float LepCorrection=1;
    float LumiWeight = 1;
    float PUWeight = 1;

        //=========================================================================================================
        //MET Shape systematics
        Met=pfMET;
        Metphi=pfMETPhi;
        if (syst == "met_JESUp") {Met = met_JESUp; Metphi=metphi_JESUp;}
        if (syst == "met_JESDown") {Met = met_JESDown;  Metphi=metphi_JESDown;}
        if (syst == "met_UESUp") {Met = met_UESUp;  Metphi=metphi_UESUp;}
        if (syst == "met_UESDown") {Met = met_UESDown;  Metphi=metphi_UESDown;}
        
        TLorentzVector Mu4Momentum,Tau4Momentum, Z4Momentum, Met4Momentum;
        //=========================================================================================================
        // Muon selection
        int idx_lep= lepIndex;
        Mu4Momentum.SetPtEtaPhiM(muPt->at(idx_lep),muEta->at(idx_lep),muPhi->at(idx_lep),MuMass);
        
        bool selectMuon_1= false;
        bool selectMuon_2= false;
        
        float IsoLep1Value=muPFChIso->at(idx_lep)/muPt->at(idx_lep);
        if ( (muPFNeuIso->at(idx_lep) + muPFPhoIso->at(idx_lep) - 0.5* muPFPUIso->at(idx_lep) )  > 0.0)
            IsoLep1Value= ( muPFChIso->at(idx_lep) + muPFNeuIso->at(idx_lep) + muPFPhoIso->at(idx_lep) - 0.5* muPFPUIso->at(idx_lep))/muPt->at(idx_lep);
        
        
        if (muPt->at(idx_lep) < 30 || fabs(muEta->at(idx_lep)) > 2.4) continue;
        
        plotFill("cutFlowTable",2 ,15,0,15);
        
        bool MuId=( (muIDbit->at(idx_lep) >> 1 & 1)  && fabs(muD0->at(idx_lep)) < 0.045 && fabs(muDz->at(idx_lep)) < 0.2);
        MuIdCorrection = getCorrFactorMuonId(year, isData,  Mu4Momentum.Pt(), Mu4Momentum.Eta() ,HistoMuId);
        
        if (! MuId) continue;
        
        plotFill("cutFlowTable",3 ,15,0,15);
        
//        if (muPt->at(idx_lep) < 52  && HLT_Mu27 && IsoLep1Value < LeptonIsoCut && pfMET > 40 ){
        if (muPt->at(idx_lep) < 55  && HLT_Mu27 && pfMET > 40 ){
            selectMuon_1 = true;
            MuTrgCorrection = getCorrFactorMuonTrg(isData,  Mu4Momentum.Pt(), Mu4Momentum.Eta() ,HistoMuTrg27);
            MuIsoCorrection = getCorrFactorMuonIso(year, isData,  Mu4Momentum.Pt(), Mu4Momentum.Eta() ,HistoMuIso);
            
        }
        if (muPt->at(idx_lep) >= 55  && HLT_Mu50 ) {
            selectMuon_2 = true;
            MuTrgCorrection = getCorrFactorMuonTrg(isData,  Mu4Momentum.Pt(), Mu4Momentum.Eta() ,HistoMuTrg50);
        }
        
        if (!selectMuon_1 && !selectMuon_2) continue;
        LepCorrection= MuIdCorrection * MuIsoCorrection * MuTrgCorrection;
        
        
        plotFill("cutFlowTable",4 ,15,0,15);
        //=========================================================================================================
        // Tau selection
        int idx_tau= tauIndex;
        
        if (boostedTauPt->at(idx_tau) <= 30 || fabs(boostedTauEta->at(idx_tau)) >= 2.3 ) continue;
        if (boostedTaupfTausDiscriminationByDecayModeFinding->at(idx_tau) < 0.5 ) continue;
        //        if (boostedTauagainstElectronVLooseMVA62018->at(idx_tau) < 0.5) continue;
        if (boostedTauByLooseMuonRejection3->at(idx_tau) < 0.5) continue;
        Tau4Momentum.SetPtEtaPhiM(boostedTauPt->at(idx_tau),boostedTauEta->at(idx_tau),boostedTauPhi->at(idx_tau),boostedTauMass->at(idx_tau));
        plotFill("cutFlowTable",5 ,15,0,15);
        //=========================================================================================================
        // Event Selection
        Met4Momentum.SetPtEtaPhiM(pfMET, 0, pfMETPhi, 0);
        Z4Momentum=Tau4Momentum+Mu4Momentum;
        TLorentzVector higgs = Tau4Momentum+Mu4Momentum +Met4Momentum;
        
        dR_lep_lep= Tau4Momentum.DeltaR(Mu4Momentum);
        if( dR_lep_lep > 0.8 || dR_lep_lep < 0.1) continue;
        plotFill("cutFlowTable",6 ,15,0,15);
        
        tmass = TMass_F(Mu4Momentum.Pt(), Mu4Momentum.Px(), Mu4Momentum.Py(),  Met,  Metphi);
        if (tmass > 80) continue;
        plotFill("cutFlowTable",7 ,15,0,15);
        
        if (m_sv < 50) continue;
        plotFill("cutFlowTable",8 ,15,0,15);
        
        // BJet veto
        int numBJet=numBJets(BJetPtCut,DeepCSVCut);
        if (numBJet > 0) continue;
        plotFill("cutFlowTable",9 ,15,0,15);
        
        // HT cut
        ht= getHT(JetPtCut, Mu4Momentum, Tau4Momentum);
        if (ht < 200) continue;
        plotFill("cutFlowTable",10 ,15,0,15);
        
        // ST definition
        st= getST(JetPtCut);
        
        //electron veto
        int numele =getNumElectron();
        if (numele > 0) continue;
        plotFill("cutFlowTable",11 ,15,0,15);
        
        if (higgs.Pt() < 280) continue;
        plotFill("cutFlowTable",14 ,15,0,15);


        //Leading jet
        TLorentzVector LeadJet= getLeadJet(Mu4Momentum, Tau4Momentum);
        
        //=========================================================================================================
        // Separate Drell-Yan processes
        //        int Zcateg = ZCategory(Tau4Momentum);
        //        if (name == "ZLL" && Zcateg > 4) {
        //            continue;
        //        } else if ((name == "ZTT") &&Zcateg != 5) {
        //            continue;
        //        } else if (name == "ZJ" && Zcateg != 6) {
        //            continue;
        //        }
        
        //=========================================================================================================
        // Weights & Correction

        if (!isData){
            
            // Lumi weight
            LumiWeight = getLuminsoity(year) * XSection(sample)*1.0 / HistoTot->GetBinContent(2);
            
            float PUMC_=HistoPUMC->GetBinContent(puTrue->at(0)+1);
            float PUData_=HistoPUData->GetBinContent(puTrue->at(0)+1);
            
            if (PUMC_ ==0)
                cout<<"PUMC_ is zero!!! & num pileup= "<< puTrue->at(0)<<"\n";
            else
                PUWeight= PUData_/PUMC_;
            
            
            
            // give inputs to workspace
//            htt_sf->var("m_pt")->setVal(muPt->at(idx_lep));
//            htt_sf->var("m_eta")->setVal(muEta->at(idx_lep));
//            htt_sf->var("z_gen_mass")->setVal(ZBosonMass);
//            htt_sf->var("z_gen_pt")->setVal(ZBosonPt);
            
                    //        float nom_zpt_weight=1.0;
        //  GenInfo
//        vector<float>  genInfo=GeneratorInfo();
//        float ZBosonPt=genInfo[3];
//        float ZBosonMass=genInfo[4];

            
            //            if (name == "EWKZ" || name == "ZL" || name == "ZTT" || name == "ZLL") {
            //
            //                // Z-pT Reweighting
            //                nom_zpt_weight = htt_sf->function("zptmass_weight_nom")->getVal();
            //                if (syst == "dyShape_Up") {
            //                    nom_zpt_weight = 1.1 * nom_zpt_weight - 0.1;
            //                } else if (syst == "dyShape_Down") {
            //                    nom_zpt_weight = 0.9 * nom_zpt_weight + 0.1;
            //                }
            ////                cout<<"ZBosonMass= "<<ZBosonMass << "  ZBosonPt= "<<ZBosonPt <<"  nom_zpt_weight= "<<nom_zpt_weight<<"\n";
            //
            //            }
        }
        
        plotFill("LumiWeight",LumiWeight ,1000,0,10000);
        plotFill("LepCorrection",LepCorrection ,100,0,2);
        //        plotFill("nom_zpt_weight",nom_zpt_weight ,100,0,2);
        plotFill("PUWeight",PUWeight ,200,0,2);
        
        //###############################################################################################
        //  tree branches
        //###############################################################################################
        
        
        
        higgs_pT = higgs.Pt();
        higgs_m = higgs.M();
        OS = muCharge->at(idx_lep) * boostedTauCharge->at(idx_tau) < 0;
        SS =  muCharge->at(idx_lep) * boostedTauCharge->at(idx_tau) > 0;
        lep1IsoPass= selectMuon_1? IsoLep1Value < LeptonIsoCut : 1;
        lep2IsoPass= boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNew->at(idx_tau) > 0.5 ;
        lepPt_=muPt->at(idx_lep);
        taupt_=boostedTauPt->at(idx_tau);
        vis_mass=Z4Momentum.M();
        LeadJetPt = LeadJet.Pt();
        dR_Z_jet=LeadJet.DeltaR(Z4Momentum);
        BoostedTauRawIso=boostedTauByIsolationMVArun2v1DBoldDMwLTraw->at(idx_tau);
        m_sv_=m_sv;
        //  Weights
        FullWeight = LumiWeight*LepCorrection;
        //        FullWeight = LumiWeight*LepCorrection*nom_zpt_weight;
        //        wtnom_zpt_weight=nom_zpt_weight;
        
        // Fill the tree
        outTr->Fill();
        
        
        //    plotFill("PUWeight",PUWeight ,200,0,2);
        
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


