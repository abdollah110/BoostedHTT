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
    std::string year_str = parser.Option("-y");
    
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
    
    TTree * outTr=  new TTree("mutau_tree","mutau_tree");
    
    
    // H->tau tau scale factors
    TFile*  htt_sf_file = TFile::Open(("data/htt_scalefactors_legacy_"+year_str+".root").c_str(), "READ");
    RooWorkspace *htt_sf = reinterpret_cast<RooWorkspace*>(htt_sf_file->Get("w"));
    htt_sf_file->Close();

    // Z-pT reweighting
    TFile *zpt_file = new TFile("data/zpt_weights_2016_BtoH.root");
    auto zpt_hist = reinterpret_cast<TH2F*>(zpt_file->Get("zptmass_histo"));
    //###############################################################################################
    //  Fix Parameters
    //###############################################################################################
    float MuMass= 0.10565837;
    float eleMass= 0.000511;
    float JetPtCut=30;
    float BJetPtCut=20;
    float muonPtCut=30;
    if (year==2018) muonPtCut=35;
    
    //    float CSVCut=   0.9535   ;                  //  https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation80XReReco
    float CSVCut=   0.8838   ;                  //  medium  https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
    float LeptonIsoCut=0.20;
    bool debug= false;
    //    float luminosity=    35867;
//    float luminosity=    41530;
    
    bool FailL,PassL,FailM,PassM,FailT,PassT,OS,SS,lepIsoPass,IsoLepValue, q_SS, q_OS;
    float tmass,ht,st,Met,FullWeight, dR_lep_tau, Metphi,BoostedTauRawIso, higgs_pT, higgs_m, m_sv_, wtnom_zpt_weight, LeadJetPt;
    bool Isolation, AntiIsolation;
    float mupt_,taupt_, ZMass, LeptonIso;


    outTr->Branch("muPt",&mupt_,"muPt/F");
    outTr->Branch("taupt",&taupt_,"taupt/F");
    outTr->Branch("PassL",&PassL,"PassL/O");
    outTr->Branch("FailL",&FailL,"FailL/O");
    outTr->Branch("PassM",&PassM,"PassM/O");
    outTr->Branch("FailM",&FailM,"FailM/O");
    outTr->Branch("PassT",&PassT,"PassT/O");
    outTr->Branch("FailT",&FailT,"FailT/O");
    outTr->Branch("q_OS",&q_OS,"q_OS/O");
    outTr->Branch("q_SS",&q_SS,"q_SS/O");
    outTr->Branch("lepIso",&Isolation,"lepIso/O");
    outTr->Branch("lepAntiIso",&AntiIsolation,"lepAntiIso/O");
    outTr->Branch("ZMass",&ZMass,"ZMass/F");
    outTr->Branch("tmass",&tmass,"tmass/F");
    outTr->Branch("ht",&ht,"ht/F");
    outTr->Branch("Met",&Met,"Met/F");
    outTr->Branch("LeadJetPt",&LeadJetPt,"LeadJetPt/F");
    outTr->Branch("dR_lep_tau",&dR_lep_tau,"dR_lep_tau/F");
    outTr->Branch("evtwt",&FullWeight,"evtwt/F");
    outTr->Branch("LeptonIso",&LeptonIso,"LeptonIso/F");
    
                    
                    
    plotFill("cutFlowTable",1 ,15,0,15);
    
    Int_t nentries_wtn = (Int_t) Run_Tree->GetEntries();
    cout<<"nentries_wtn===="<<nentries_wtn<<"\n";
    for (Int_t i = 0; i < nentries_wtn; i++) {
        plotFill("cutFlowTable",2 ,15,0,15);
        Run_Tree->GetEntry(i);
        if (i % 1000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);
        
        // Trigger
        bool PassTrigger = ((HLTEleMuX >> 19 & 1)==1); // else if (name.find("HLT_IsoMu27_v") != string::npos) bitEleMuX = 19; // 2017
        if (year==2017 && ! PassTrigger) continue;
        plotFill("cutFlowTable",3 ,15,0,15);
        
        //  This part is to avoid of the duplicate of mu-tau pair from one events
        std::vector<string> HistNamesFilled;
        HistNamesFilled.clear();
        
        
        //###############################################################################################
        //  GenInfo
        //###############################################################################################
        vector<float>  genInfo=GeneratorInfo();
        float ZBosonPt=genInfo[2];
        float ZBosonMass=genInfo[4];
        
        // Lumi weight
        float LumiWeight = 1;
        if (!isData){
            LumiWeight = getLuminsoity(year) * XSection(sample)*1.0 / HistoTot->GetBinContent(2);
        }
        
        // Pilu up weights
        float PUWeight = 1;
        
        
        // BJet veto
        int numBJet=numBJets(BJetPtCut,CSVCut);
        if (numBJet > 0) continue;
        plotFill("cutFlowTable",4 ,15,0,15);

        
        //electron veto
        int numele =getNumElectron();
        if (numele > 0) continue;
        plotFill("cutFlowTable",5 ,15,0,15);
        
        
        //MET Shape systematics
         Met=pfMET;
         float Metphi=pfMETPhi;
         if (syst == "met_JESUp") {Met = met_JESUp; Metphi=metphi_JESUp;}
         if (syst == "met_JESDown") {Met = met_JESDown;  Metphi=metphi_JESDown;}
         if (syst == "met_UESUp") {Met = met_UESUp;  Metphi=metphi_UESUp;}
         if (syst == "met_UESDown") {Met = met_UESDown;  Metphi=metphi_UESDown;}
         if (Met < 50 ) continue ;
        
        //############################################################################################
        //###########       Loop over MuTau events   #################################################
        //############################################################################################
        bool isFilledOnce = false;
        TLorentzVector Mu4Momentum,BoostedTau4Momentum, Z4Momentum;
        
        for (int imu = 0; imu < nMu; ++imu){
            
            if (muPt->at(imu) <= muonPtCut || fabs(muEta->at(imu)) >= 2.4) continue;
            plotFill("cutFlowTable",6 ,15,0,15);
            float IsoMu=muPFChIso03->at(imu)/muPt->at(imu);
            if ( (muPFNeuIso03->at(imu) + muPFPhoIso03->at(imu) - 0.5* muPFPUIso03->at(imu) )  > 0.0)
                IsoMu= ( muPFChIso03->at(imu) + muPFNeuIso03->at(imu) + muPFPhoIso03->at(imu) - 0.5* muPFPUIso03->at(imu))/muPt->at(imu);
            
            bool MuId=( (muIDbit->at(imu) >> 2 & 1)  && fabs(muD0->at(imu)) < 0.045 && fabs(muDz->at(imu)) < 0.2); //CutBasedIdMediumPrompt)) pow(2,  2);
            
            if (!MuId ) continue;
            Mu4Momentum.SetPtEtaPhiM(muPt->at(imu),muEta->at(imu),muPhi->at(imu),MuMass);
            //                float MuonCor=getCorrFactorMuon94X(isData,  muPt->at(imu), muEta->at(imu) , HistoMuId,HistoMuIso,HistoMuTrg,HistoMuTrack);
            plotFill("cutFlowTable",7 ,15,0,15);
            
            float MuonCor=1;
            if (!isData){
                // give inputs to workspace
                htt_sf->var("m_pt")->setVal(muPt->at(imu));
                htt_sf->var("m_eta")->setVal(muEta->at(imu));
                htt_sf->var("m_iso")->setVal(IsoMu);
                
                htt_sf->var("z_gen_mass")->setVal(ZBosonMass);
                htt_sf->var("z_gen_pt")->setVal(ZBosonPt);
                //                cout<<"\t\t ZBosonMass= "<<ZBosonMass <<"  ZBosonPt "<<ZBosonPt<<"\n";
                
                
                MuonCor *= htt_sf->function("m_trk_ratio")->getVal();
                MuonCor *= htt_sf->function("m_idiso_ic_ratio")->getVal();
                                            
                
                auto single_data_eff = htt_sf->function("m_trg24_27_kit_data")->getVal();
                auto single_mc_eff = htt_sf->function("m_trg24_27_kit_mc")->getVal();
                auto single_eff = single_data_eff / single_mc_eff;
                MuonCor *=single_eff;
                
                //                if (InputROOT.find("DY") != string::npos) MuonCor *= htt_sf->function("zptmass_weight_nom")->getVal();
                //                if (name.find("DY") != string::npos) MuonCor *= htt_sf->function("zptmass_weight_nom")->getVal();
                
            }
            plotFill("MuonCor",MuonCor ,100,0,2);
            
            
//            
//            
//            float nom_zpt_weight=1.0;
//            float zmumuWeight=1.0;
//            
//            if (name == "EWKZ" || name == "ZL" || name == "ZTT" || name == "ZLL") {
//                
//                
//                // Z-pT Reweighting
//                nom_zpt_weight = zpt_hist->GetBinContent(zpt_hist->GetXaxis()->FindBin(ZBosonMass), zpt_hist->GetYaxis()->FindBin(ZBosonPt));
//                if (syst == "dyShape_Up") {
//                    nom_zpt_weight = 1.1 * nom_zpt_weight - 0.1;
//                } else if (syst == "dyShape_Down") {
//                    nom_zpt_weight = 0.9 * nom_zpt_weight + 0.1;
//                }
//                
//                
//                
//                if (syst == "zmumuShape_Up") {
//                    zmumuWeight= htt_sf->function("zptmass_weight_nom")->getVal() * htt_sf->function("zptmass_weight_nom")->getVal();
//                } else if (syst == "zmumuShape_Down") {
//                    // no weight for shift down
//                }
//                else{
//                    zmumuWeight= htt_sf->function("zptmass_weight_nom")->getVal();
//                }
//            }
//            plotFill("nom_zpt_weight",nom_zpt_weight ,100,0,2);
//            plotFill("zmumuWeight",zmumuWeight ,100,0,2);
//            float ZCorrection=nom_zpt_weight*zmumuWeight;
//            plotFill("ZCorrection",ZCorrection ,100,0,2);
            
            
            
            
            
            tmass = TMass_F(Mu4Momentum.Pt(), Mu4Momentum.Px(), Mu4Momentum.Py(),  Met,  Metphi);
            if (tmass > 40) continue;
            plotFill("cutFlowTable",8 ,15,0,15);
            for (int ibtau = 0; ibtau < nBoostedTau; ++ibtau){
                
                if (boostedTauPt->at(ibtau) <= 20 || fabs(boostedTauEta->at(ibtau)) >= 2.3 ) continue;
                plotFill("cutFlowTable",9 ,15,0,15);
                if (boostedTaupfTausDiscriminationByDecayModeFinding->at(ibtau) < 0.5 ) continue;
                plotFill("cutFlowTable",10 ,15,0,15);
//                if (boostedTauByMVA6VLooseElectronRejection->at(ibtau) < 0.5) continue;
                if (boostedTauagainstElectronVLooseMVA62018->at(ibtau) < 0.5) continue;
                plotFill("cutFlowTable",11 ,15,0,15);
                if (boostedTauByTightMuonRejection3->at(ibtau) < 0.5) continue;
                plotFill("cutFlowTable",12 ,15,0,15);
                BoostedTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(ibtau),boostedTauEta->at(ibtau),boostedTauPhi->at(ibtau),boostedTauMass->at(ibtau));
                dR_lep_tau= BoostedTau4Momentum.DeltaR(Mu4Momentum);
//                if( dR_lep_tau > 0.8 || dR_lep_tau < 0.3) continue;
                if( dR_lep_tau > 0.8 || dR_lep_tau < 0.4) continue;
                Z4Momentum=BoostedTau4Momentum+Mu4Momentum;
                plotFill("cutFlowTable",13 ,15,0,15);
                
//                // Separate Drell-Yan
//                int Zcateg = ZCategory(BoostedTau4Momentum);
//                if (name == "ZLL" && Zcateg > 4) {
//                    continue;
//                } else if ((name == "ZTT") &&Zcateg != 5) {
//                    continue;
//                } else if (name == "ZJ" && Zcateg != 6) {
//                    continue;
//                }
                
                
                // HT cut
                 ht= getHT(JetPtCut, Mu4Momentum, BoostedTau4Momentum);
                if (ht < 250) continue;
                plotFill("cutFlowTable",15 ,15,0,15);
                //Leading jet
                TLorentzVector LeadJet= getLeadJet(Mu4Momentum, BoostedTau4Momentum);

                //###############################################################################################
                //  BoostedTau Isolation Categorization
                //###############################################################################################
                
                const int size_tauCat = 6;
//                bool Pass = boostedTauByLooseIsolationMVArun2v1DBoldDMwLT->at(ibtau) > 0.5 ;
//                bool Fail = boostedTauByLooseIsolationMVArun2v1DBoldDMwLT->at(ibtau) < 0.5 ;
//                bool PassM = boostedTauByMediumIsolationMVArun2v1DBoldDMwLT->at(ibtau) > 0.5 ;
//                bool FailM = boostedTauByMediumIsolationMVArun2v1DBoldDMwLT->at(ibtau) < 0.5 ;
//                bool PassT = boostedTauByTightIsolationMVArun2v1DBoldDMwLT->at(ibtau) > 0.5 ;
//                bool FailT = boostedTauByTightIsolationMVArun2v1DBoldDMwLT->at(ibtau) < 0.5 ;

                 PassL = boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNew->at(ibtau) > 0.5 ;
                 FailL = boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNew->at(ibtau) < 0.5 ;
                 PassM = boostedTauByMediumIsolationMVArun2v1DBoldDMwLTNew->at(ibtau) > 0.5 ;
                 FailM = boostedTauByMediumIsolationMVArun2v1DBoldDMwLTNew->at(ibtau) < 0.5 ;
                 PassT = boostedTauByTightIsolationMVArun2v1DBoldDMwLTNew->at(ibtau) > 0.5 ;
                 FailT = boostedTauByTightIsolationMVArun2v1DBoldDMwLTNew->at(ibtau) < 0.5 ;

                
                bool Tau_category[size_tauCat] = {PassL, FailL,PassM, FailM,PassT, FailT};
                std::string Tau_Cat[size_tauCat] = {"_PassL", "_FailL","_PassM", "_FailM","_PassT", "_FailT"};
                
                //###############################################################################################
                //  lepton Isolation Categorization
                //###############################################################################################
                bool LepPassIsolation= IsoMu < LeptonIsoCut;
                
                const int size_isoCat = 2;
                Isolation = LepPassIsolation;
                AntiIsolation =  !LepPassIsolation;
                
                bool Iso_category[size_isoCat] = {Isolation, AntiIsolation};
                std::string iso_Cat[size_isoCat] = {"_Iso", "_AntiIso"};
                
                //###############################################################################################
                //  Charge Categorization
                //###############################################################################################
                float chargelt= muCharge->at(imu) * boostedTauCharge->at(ibtau);
                
                const int size_q = 2;
                q_OS = chargelt < 0;
                q_SS =  chargelt > 0;
                
                bool Q_category[size_q] = {q_OS, q_SS};
                std::string Q_Cat[size_q] = {"_OS", "_SS"};
                
                
                //###############################################################################################
                //  Weights
                //###############################################################################################

//                FullWeight = LumiWeight*MuonCor *ZCorrection;
                FullWeight = LumiWeight*MuonCor * 1;
                if (isData) FullWeight=1;

                //###############################################################################################
                //  make Tree
                //###############################################################################################
                
                mupt_=muPt->at(imu);
                 taupt_=boostedTauPt->at(ibtau);
                 ZMass=Z4Momentum.M();
                LeadJetPt = LeadJet.Pt();
                float dR_Z_jet=LeadJet.DeltaR(Z4Momentum);
                LeptonIso=IsoMu;
                
                //###############################################################################################
                // Fill Histograms
                //###############################################################################################
                
                for (int tt = 0; tt < size_tauCat; tt++) {
                    if (Tau_category[tt]) {
                        for (int iso = 0; iso < size_isoCat; iso++) {
                            if (Iso_category[iso]) {
                                for (int iq = 0; iq < size_q; iq++) {
                                    if (Q_category[iq]) {


                                        std::string FullStringName = Tau_Cat[tt] +iso_Cat[iso] + Q_Cat[iq] ;

                                        //                                This check is used to make sure that each event is just filled once for any of the categories ==> No doube-counting of events  (this is specially important for ttbar events where we have many jets and leptons)
                                        if (!( std::find(HistNamesFilled.begin(), HistNamesFilled.end(), FullStringName) != HistNamesFilled.end())){
                                            HistNamesFilled.push_back(FullStringName);

                                            //1 D histograms
                                            plotFill("ZMass"+FullStringName,Z4Momentum.M() ,20,0,100,FullWeight);
                                            plotFill("tmass"+FullStringName,tmass ,25,0,50,FullWeight);
                                            plotFill("ht"+FullStringName,ht ,25,0,1000,FullWeight);
                                            plotFill("lepPt"+FullStringName,muPt->at(imu) ,20,0,200,FullWeight);
                                            plotFill("tauPt"+FullStringName,boostedTauPt->at(ibtau) ,20,0,200,FullWeight);
                                            plotFill("MET"+FullStringName,Met ,30,0,300,FullWeight);
                                            plotFill("LeadJetPt"+FullStringName,LeadJet.Pt() ,25,0,1000,FullWeight);
                                            plotFill("dR_Z_jet"+FullStringName,LeadJet.DeltaR(Z4Momentum) ,25,0,5,FullWeight);


                                            //2 D histograms
                                            plotFill("LepDR_MET"+FullStringName, dR_lep_tau, Met, 20,0.4,0.8 ,30,0,300,FullWeight);
                                            plotFill("LepDR_HT"+FullStringName, dR_lep_tau, ht, 20,0.4,0.8 ,25,0,1000,FullWeight);
                                            plotFill("LepDR_LeadJet"+FullStringName, dR_lep_tau, LeadJet.Pt(), 20,0.4,0.8 ,25,0,1000,FullWeight);

                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                
            }//boostedTau loop
        }//muon loop

        if (! isFilledOnce ){
        outTr->Fill();
        isFilledOnce= true;
        }


    } //End of Tree
    
//    outTr->Fill();
    
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


