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
    Run_Tree= Xttree(fin);
    
    //    auto HistoTot = reinterpret_cast<TH1D*>(fin->Get("ggNtuplizer/hEvents"));
    TH1F * HistoTot = (TH1F*) fin->Get("hcount");
    auto fout = new TFile(filename.c_str(), "RECREATE");
    
    myMap1 = new std::map<std::string, TH1F*>();
    myMap2 = new map<string, TH2F*>();
    
    TTree * outTr=  new TTree("mutau_tree","mutau_tree");
    
    
    // H->tau tau scale factors
    TFile htt_sf_file("data/htt_scalefactors_2017_v2.root");
    RooWorkspace *htt_sf = reinterpret_cast<RooWorkspace*>(htt_sf_file.Get("w"));
    htt_sf_file.Close();
    
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
    
    //    float CSVCut=   0.9535   ;                  //  https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation80XReReco
    float CSVCut=   0.8838   ;                  //  medium  https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
    float LeptonIsoCut=0.20;
    bool debug= false;
    //    float luminosity=    35867;
    float luminosity=    41530;
    
    
    float mupt_=-10;
    float taupt_=-10;
    float vis_mass=-10;
    float LeadJetPt = -10;
    float dR_Z_jet=-10;
    bool Fail,Pass,OS,SS,Isolation,AntiIsolation;
    float tmass,ht,Met,FullWeight, dR_mu_tau, Metphi,IsoMu,BoostedTauRawIso, higgs_pT, higgs_m;
    
    
    
    outTr->Branch("muPt",&mupt_,"muPt/F");
    outTr->Branch("taupt",&taupt_,"taupt/F");
    outTr->Branch("Pass",&Pass,"Pass/O");
    outTr->Branch("Fail",&Fail,"Fail/O");
    outTr->Branch("OS",&OS,"OS/O");
    outTr->Branch("SS",&SS,"SS/O");
    outTr->Branch("lepIso",&Isolation,"lepIso/O");
    outTr->Branch("lepAntiIso",&AntiIsolation,"lepAntiIso/O");
    outTr->Branch("vis_mass",&vis_mass,"vis_mass/F");
    outTr->Branch("tmass",&tmass,"tmass/F");
    outTr->Branch("ht",&ht,"ht/F");
    outTr->Branch("Met",&Met,"Met/F");
    outTr->Branch("LeadJetPt",&LeadJetPt,"LeadJetPt/F");
    outTr->Branch("dR_mu_tau",&dR_mu_tau,"dR_mu_tau/F");
    outTr->Branch("evtwt",&FullWeight,"evtwt/F");
    outTr->Branch("IsoMu",&IsoMu,"IsoMu/F");
    outTr->Branch("BoostedTauRawIso",&BoostedTauRawIso,"BoostedTauRawIso/F");
    outTr->Branch("higgs_pT",&higgs_pT,"higgs_pT/F");
    outTr->Branch("higgs_m",&higgs_m,"higgs_m/F");
    
    
    
    
    Int_t nentries_wtn = (Int_t) Run_Tree->GetEntries();
    cout<<"nentries_wtn===="<<nentries_wtn<<"\n";
    for (Int_t i = 0; i < nentries_wtn; i++) {
        
        Run_Tree->GetEntry(i);
        if (i % 1000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);
        
        // Trigger
        bool PassTrigger = ((HLTEleMuX >> 21 & 1)==1);
        //              else if (name.find("HLT_Mu50_v")                                          != string::npos) bitEleMuX = 21;
        // else if (name.find("HLT_IsoMu27_v") != string::npos) bitEleMuX = 19; // 2017
        if (! PassTrigger) continue;
        
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
            LumiWeight = luminosity * XSection(sample)*1.0 / HistoTot->GetBinContent(2);
        }
        
        // Pilu up weights
        float PUWeight = 1;
        
        
        // BJet veto
        int numBJet=numBJets(BJetPtCut,CSVCut);
        if (numBJet > 0) continue;
        
        // HT cut
        ht= getHT(JetPtCut);
        //        cout<<"ht = "<<ht<<"\n";
        if (ht < 200) continue;
        
        //electron veto
        int numele =getNumElectron();
        if (numele > 0) continue;
        
        //Leading jet
        TLorentzVector LeadJet= getLeadJet();
        
        
        //        //MET Shape systematics
        Met=pfMET;
        Metphi=pfMETPhi;
        //        cout<<"MET = "<<Met<<   "    Metphi = "<<pfMETPhi << "\n";
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
            
            if (muPt->at(imu) <= 30 || fabs(muEta->at(imu)) >= 2.4) continue;
            
            float IsoMu=muPFChIso->at(imu)/muPt->at(imu);
            if ( (muPFNeuIso->at(imu) + muPFPhoIso->at(imu) - 0.5* muPFPUIso->at(imu) )  > 0.0)
                IsoMu= ( muPFChIso->at(imu) + muPFNeuIso->at(imu) + muPFPhoIso->at(imu) - 0.5* muPFPUIso->at(imu))/muPt->at(imu);
            
            bool MuId=( (muIDbit->at(imu) >> 2 & 1)  && fabs(muD0->at(imu)) < 0.045 && fabs(muDz->at(imu)) < 0.2); //CutBasedIdMediumPrompt)) pow(2,  2);
            
            if (!MuId ) continue;
            Mu4Momentum.SetPtEtaPhiM(muPt->at(imu),muEta->at(imu),muPhi->at(imu),MuMass);
            
            float MuonCor=1;
            if (!isData){
            
            
                // give inputs to workspace
                htt_sf->var("m_pt")->setVal(muPt->at(imu));
                htt_sf->var("m_eta")->setVal(muEta->at(imu));
                htt_sf->var("z_gen_mass")->setVal(ZBosonMass);
                htt_sf->var("z_gen_pt")->setVal(ZBosonPt);
                
                
                // muon ID SF
                MuonCor *= htt_sf->function("m_id_kit_ratio")->getVal();
//                // muon Iso SF
//                MuonCor *= htt_sf->function("m_iso_kit_ratio")->getVal();
//                //Tracker
//                MuonCor *= htt_sf->function("m_trk_ratio")->getVal();
//                // Trigger
//                auto single_data_eff = htt_sf->function("m_trg24_27_kit_data")->getVal();
//                auto single_mc_eff = htt_sf->function("m_trg24_27_kit_mc")->getVal();
//                auto single_eff = single_data_eff / single_mc_eff;
//                MuonCor *=single_eff;
                
                
                //                if (InputROOT.find("DY") != string::npos) MuonCor *= htt_sf->function("zptmass_weight_nom")->getVal();
                //                if (name.find("DY") != string::npos) MuonCor *= htt_sf->function("zptmass_weight_nom")->getVal();
                
            }
            plotFill("MuonCor",MuonCor ,100,0,2);
            
            float nom_zpt_weight=1.0;
            float zmumuWeight=1.0;
            
            if (name == "EWKZ" || name == "ZL" || name == "ZTT" || name == "ZLL") {
                
                
                // Z-pT Reweighting
                nom_zpt_weight = zpt_hist->GetBinContent(zpt_hist->GetXaxis()->FindBin(ZBosonMass), zpt_hist->GetYaxis()->FindBin(ZBosonPt));
                if (syst == "dyShape_Up") {
                    nom_zpt_weight = 1.1 * nom_zpt_weight - 0.1;
                } else if (syst == "dyShape_Down") {
                    nom_zpt_weight = 0.9 * nom_zpt_weight + 0.1;
                }
                
//                if (syst == "zmumuShape_Up") {
//                    zmumuWeight= htt_sf->function("zptmass_weight_nom")->getVal() * htt_sf->function("zptmass_weight_nom")->getVal();
//                } else if (syst == "zmumuShape_Down") {
//                    // no weight for shift down
//                }
//                else{
//                    zmumuWeight= htt_sf->function("zptmass_weight_nom")->getVal();
//                }
            }
            
            float ZCorrection=nom_zpt_weight*zmumuWeight;
            plotFill("nom_zpt_weight",nom_zpt_weight ,100,0,2);
//            plotFill("zmumuWeight",zmumuWeight ,100,0,2);
            plotFill("ZCorrection",ZCorrection ,100,0,2);
            
            tmass = TMass_F(Mu4Momentum.Pt(), Mu4Momentum.Px(), Mu4Momentum.Py(),  Met,  Metphi);
            if (tmass > 40) continue;
            
            for (int ibtau = 0; ibtau < nBoostedTau; ++ibtau){
                
                if (boostedTauPt->at(ibtau) <= 20 || fabs(boostedTauEta->at(ibtau)) >= 2.3 ) continue;
                if (boostedTaupfTausDiscriminationByDecayModeFinding->at(ibtau) < 0.5 ) continue;
                if (boostedTauByMVA6VLooseElectronRejection->at(ibtau) < 0.5) continue;
                if (boostedTauByTightMuonRejection3->at(ibtau) < 0.5) continue;
                
                BoostedTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(ibtau),boostedTauEta->at(ibtau),boostedTauPhi->at(ibtau),boostedTauMass->at(ibtau));
                dR_mu_tau= BoostedTau4Momentum.DeltaR(Mu4Momentum);
                
                if( dR_mu_tau > 0.8 || dR_mu_tau < 0.1) continue;
                
                // Separate Drell-Yan
                int Zcateg = ZCategory(BoostedTau4Momentum);
                if (name == "ZLL" && Zcateg > 4) {
                    continue;
                } else if ((name == "ZTT") &&Zcateg != 5) {
                    continue;
                } else if (name == "ZJ" && Zcateg != 6) {
                    continue;
                }

                
                //###############################################################################################
                //  tree branches
                //###############################################################################################
                
                Z4Momentum=BoostedTau4Momentum+Mu4Momentum;
                TLorentzVector Met4Momentum;
                Met4Momentum.SetPtEtaPhiM(pfMET, 0, pfMETPhi, 0);
                TLorentzVector higgs = BoostedTau4Momentum+Mu4Momentum +Met4Momentum;
                higgs_pT = higgs.Pt();
                higgs_m = higgs.M();
                OS = muCharge->at(imu) * boostedTauCharge->at(ibtau) < 0;
                SS =  muCharge->at(imu) * boostedTauCharge->at(ibtau) > 0;
                Pass = boostedTauByLooseIsolationMVArun2v1DBoldDMwLT->at(ibtau) > 0.5 ;
                Fail = boostedTauByLooseIsolationMVArun2v1DBoldDMwLT->at(ibtau) < 0.5 ;
                Isolation= IsoMu < LeptonIsoCut;
                mupt_=muPt->at(imu);
                taupt_=boostedTauPt->at(ibtau);
                vis_mass=Z4Momentum.M();
                LeadJetPt = LeadJet.Pt();
                dR_Z_jet=LeadJet.DeltaR(Z4Momentum);
                BoostedTauRawIso=boostedTauByIsolationMVArun2v1DBoldDMwLTraw->at(ibtau);
                
                //###############################################################################################
                //  Weights
                //###############################################################################################
                FullWeight = LumiWeight*MuonCor *ZCorrection;
                if (isData) FullWeight=1;
                
                
                if (! isFilledOnce ){
                    outTr->Fill();
                    isFilledOnce= true;
                }
            }//boostedTau loop
        }//muon loop
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


