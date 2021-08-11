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
    Run_Tree= Xttree(InputFile,"etau_tree");
    
    //    auto HistoTot = reinterpret_cast<TH1D*>(InputFile->Get("ggNtuplizer/hEvents"));
    TH1F * HistoTot = (TH1F*) InputFile->Get("hcount");
    auto fout = new TFile(filename.c_str(), "RECREATE");
    
    myMap1 = new std::map<std::string, TH1F*>();
    myMap2 = new map<string, TH2F*>();
    
    TTree * outTr=  new TTree("etau_tree","etau_tree");
    
    
    //########################################
    // Electron MVA IdIso files
    //########################################
    TH2F** HistoEleId=FuncHistEleId(year);
    //        TH2F** HistoEleTrg=FuncHistEleTrigger(year); // Not available yet
    
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
    float EleIdCorrection=1;
    float LumiWeight = 1;
    float PUWeight = 1;
    float LeptonIdCor=1;
    float LeptonTrgCor=1;
    float LepCorrection=1;
    float zmasspt_weight=1.0;
    float WBosonKFactor=1;
    float preFireWeight=1;
    float ttbar_rwt=1;
    float zmasspt_weight_err=0;
    float zmasspt_weight_nom=1;
    
    
    float lepPt_=-10;
    float taupt_=-10;
    float vis_mass=-10;
    float LeadJetPt = -10;
    float dR_Z_jet=-10;
    bool OS,SS,lep1IsoPass,lep2IsoPassL,lep2IsoPassV;
    float tmass,ht,st,Met,FullWeight, dR_lep_lep, Metphi,BoostedTauRawIso, higgs_pT, higgs_m, m_sv_, nom_zpt_weight, eleIDMVA, gen_higgs_pT;
    int nbjet;
    
    outTr->Branch("evtwt",&FullWeight,"evtwt/F");
    outTr->Branch("zmasspt_weight",&zmasspt_weight,"zmasspt_weight/F");
    outTr->Branch("lep1Pt",&lepPt_,"lep1Pt/F");
    outTr->Branch("lep2Pt",&taupt_,"lep2Pt/F");
    outTr->Branch("OS",&OS,"OS/O");
    outTr->Branch("SS",&SS,"SS/O");
    outTr->Branch("lep1IsoPass",&lep1IsoPass,"lep1IsoPass/O");
    outTr->Branch("lep2IsoPassL",&lep2IsoPassL,"lep2IsoPassL/O");
    outTr->Branch("lep2IsoPassV",&lep2IsoPassV,"lep2IsoPassV/O");
    outTr->Branch("vis_mass",&vis_mass,"vis_mass/F");
    outTr->Branch("tmass",&tmass,"tmass/F");
    outTr->Branch("ht",&ht,"ht/F");
    outTr->Branch("st",&st,"st/F");
    outTr->Branch("Met",&Met,"Met/F");
    outTr->Branch("LeadJetPt",&LeadJetPt,"LeadJetPt/F");
    outTr->Branch("dR_lep_lep",&dR_lep_lep,"dR_lep_lep/F");
    outTr->Branch("eleIDMVA",&eleIDMVA,"eleIDMVA/F");
    outTr->Branch("BoostedTauRawIso",&BoostedTauRawIso,"BoostedTauRawIso/F");
    outTr->Branch("higgs_pT",&higgs_pT,"higgs_pT/F");
    outTr->Branch("higgs_m",&higgs_m,"higgs_m/F");
    outTr->Branch("m_sv",&m_sv_,"m_sv/F");
    outTr->Branch("nbjet",&nbjet,"nbjet/I");
    outTr->Branch("gen_higgs_pT",&gen_higgs_pT,"gen_higgs_pT/F");
    
    
    Int_t nentries_wtn = (Int_t) Run_Tree->GetEntries();
    cout<<"nentries_wtn===="<<nentries_wtn<<"\n";
    for (Int_t i = 0; i < nentries_wtn; i++) {
        
        Run_Tree->GetEntry(i);
        if (i % 1000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);
        
        plotFill("cutFlowTable",1 ,15,0,15);
        //=========================================================================================================
        // Trigger
        bool HLT_Ele35 = ((HLTEleMuX >> 3 & 1)==1);//else if (name.find("HLT_Ele35_WPTight_Gsf_v")!= string::npos) bitEleMuX =  3;
        bool HLT_Ele115 = ((HLTEleMuX >> 38 & 1)==1);//else if (name.find("HLT_Ele115_CaloIdVT_GsfTrkIdT_v")!= string::npos) bitEleMuX = 38;
        
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
        if (syst == "met_JESUp") {Met = met_JESUp; Metphi=metphi_JESUp; m_sv=m_sv_JES_Up ;}
        if (syst == "met_JESDown") {Met = met_JESDown;  Metphi=metphi_JESDown; m_sv=m_sv_JES_Down ;}
        if (syst == "met_UESUp") {Met = met_UESUp;  Metphi=metphi_UESUp; m_sv=m_sv_UES_Up ;}
        if (syst == "met_UESDown") {Met = met_UESDown;  Metphi=metphi_UESDown; m_sv=m_sv_UES_Down ;}
        
        if (syst == "met_reso_Up") {Met = met_reso_Up; Metphi=metphi_reso_Up;}
        if (syst == "met_resp_Up") {Met = met_resp_Up; Metphi=metphi_resp_Up;}
        if (syst == "met_reso_Down") {Met = met_reso_Down; Metphi=metphi_reso_Down;}
        if (syst == "met_resp_Down") {Met = met_resp_Down; Metphi=metphi_resp_Down;}

        
        TLorentzVector Ele4Momentum,Tau4Momentum, Z4Momentum, Met4Momentum;
        //=========================================================================================================
        // Lepton selection
        int idx_lep= lepIndex;
        Ele4Momentum.SetPtEtaPhiM(elePt->at(idx_lep),eleEta->at(idx_lep),elePhi->at(idx_lep),eleMass);
        
        bool selectElectron_1= false;
        bool selectElectron_2= false;
        
        bool eleMVAId= false;
        if (fabs (eleSCEta->at(idx_lep)) <= 0.8 && eleIDMVANoIso->at(idx_lep) >    0.837   ) eleMVAId= true;
        else if (fabs (eleSCEta->at(idx_lep)) >  0.8 &&fabs (eleSCEta->at(idx_lep)) <=  1.5 && eleIDMVANoIso->at(idx_lep) >    0.715   ) eleMVAId= true;
        else if ( fabs (eleSCEta->at(idx_lep)) >=  1.5 && eleIDMVANoIso->at(idx_lep) >   0.357   ) eleMVAId= true;
        else eleMVAId= false;
        
        if (!eleMVAId) continue;
        plotFill("cutFlowTable",2 ,15,0,15);
        
        EleIdCorrection = getCorrFactorEleId(isData,  Ele4Momentum.Pt(), eleSCEta->at(idx_lep) ,HistoEleId);
        float IsoLep1Value=elePFChIso->at(idx_lep)/elePt->at(idx_lep);
        if ( (elePFNeuIso->at(idx_lep) + elePFPhoIso->at(idx_lep) - 0.5* elePFPUIso->at(idx_lep) )  > 0.0)
            IsoLep1Value= ( elePFChIso->at(idx_lep) + elePFNeuIso->at(idx_lep) + elePFPhoIso->at(idx_lep) - 0.5* elePFPUIso->at(idx_lep))/elePt->at(idx_lep);
        
        
        if (elePt->at(idx_lep) < 38 || fabs(eleEta->at(idx_lep)) > 2.5) continue;
        plotFill("cutFlowTable",3 ,15,0,15);
        // met from 40 to 30
        if (elePt->at(idx_lep) < 120  && HLT_Ele35 && Met > 30 ){
            selectElectron_1 = true;
        }
        if (elePt->at(idx_lep) >= 120  && HLT_Ele115 ) {
            selectElectron_2 = true;
        }
        
        if (!selectElectron_1 && !selectElectron_2) continue;
        
        plotFill("cutFlowTable",4 ,15,0,15);
        LepCorrection = EleIdCorrection;
        
        
        //=========================================================================================================
        // Tau selection
        int idx_tau= tauIndex;
        // pt from 30 to 20
        if (boostedTauPt->at(idx_tau) <= 30 || fabs(boostedTauEta->at(idx_tau)) >= 2.3 ) continue;
        if (boostedTaupfTausDiscriminationByDecayModeFinding->at(idx_tau) < 0.5 ) continue;
        //        if (boostedTauagainstElectronTightMVA62018->at(idx_tau) < 0.5) continue;
        if (boostedTauagainstElectronLooseMVA62018->at(idx_tau) < 0.5) continue;
        if (boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(idx_tau) < -0.5) continue;
        //        if (boostedTauByLooseMuonRejection3->at(idx_tau) < 0.5) continue;
        //        if (boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(ibtau) < 0) continue;
        
        Tau4Momentum.SetPtEtaPhiM(boostedTauPt->at(idx_tau),boostedTauEta->at(idx_tau),boostedTauPhi->at(idx_tau),boostedTauMass->at(idx_tau));
        plotFill("cutFlowTable",5 ,15,0,15);
        //=========================================================================================================
        // Event Selection
        Met4Momentum.SetPtEtaPhiM(Met, 0, Metphi, 0);
        Z4Momentum=Tau4Momentum+Ele4Momentum;
        TLorentzVector higgs = Tau4Momentum+Ele4Momentum +Met4Momentum;
        TLorentzVector LeadJet= getLeadJet(Ele4Momentum, Tau4Momentum);
        
        dR_lep_lep= Tau4Momentum.DeltaR(Ele4Momentum);
        if( dR_lep_lep > 0.8 || dR_lep_lep < 0.1) continue;
        plotFill("cutFlowTable",6 ,15,0,15);
        
        tmass = TMass_F(Ele4Momentum.Pt(), Ele4Momentum.Px(), Ele4Momentum.Py(),  Met,  Metphi);
        if (tmass > 80) continue;
        plotFill("cutFlowTable",7 ,15,0,15);
        
        if (m_sv < 50) continue;
        plotFill("cutFlowTable",8 ,15,0,15);
        
        // BJet veto
        int numBJet=numBJets(BJetPtCut,DeepCSVCut);
        if (numBJet > 0) continue;
        plotFill("cutFlowTable",9 ,15,0,15);
        
        // HT cut
        ht= getHT(JetPtCut, Ele4Momentum, Tau4Momentum);
        if (ht < 200) continue;
        plotFill("cutFlowTable",10 ,15,0,15);
        
        // ST definition
        st= getST(JetPtCut);
        
        //muon veto
        int numMu =getNumMuon();
        if (numMu > 0) continue;
        plotFill("cutFlowTable",11 ,15,0,15);
        
        if (higgs.Pt() < 250) continue;
        plotFill("cutFlowTable",12 ,15,0,15);
        
        //        //=========================================================================================================
        //        // Separate Drell-Yan processes
        //        int Zcateg = ZCategory(Tau4Momentum);
        //        if (name == "ZLL" && Zcateg > 4) {
        //            continue;
        //        } else if ((name == "ZTT") &&Zcateg != 5) {
        //            continue;
        //        } else if (name == "ZJ" && Zcateg != 6) {
        //            continue;
        //        }
        
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
            
            //prefire
            preFireWeight = L1ECALPrefire;
            if (syst == "prefireUp") {preFireWeight = L1ECALPrefireUp;}
            if (syst == "prefireDown") {preFireWeight = L1ECALPrefireDown;}
            
            
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
        
        plotFill("LepCorrection",LepCorrection ,100,0,2);
        plotFill("LumiWeight",LumiWeight ,1000,0,10000);
        plotFill("PUWeight",PUWeight ,200,0,2);
        plotFill("zmasspt_weight",zmasspt_weight ,200,0,2);
        plotFill("preFireWeight",preFireWeight ,200,0,2);
        plotFill("WBosonKFactor",WBosonKFactor ,200,0,2);
        plotFill("ttbar_rwt",ttbar_rwt ,200,0,2);        
        
        //###############################################################################################
        //  tree branches
        //###############################################################################################
        
        higgs_pT = higgs.Pt();
        higgs_m = higgs.M();
        OS = eleCharge->at(idx_lep) * boostedTauCharge->at(idx_tau) < 0;
        SS =  eleCharge->at(idx_lep) * boostedTauCharge->at(idx_tau) > 0;
        lep1IsoPass= selectElectron_1? IsoLep1Value < LeptonIsoCut : 1;
        lep2IsoPassL= boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNew->at(idx_tau) > 0.5 ;
        lep2IsoPassV= boostedTauByVLooseIsolationMVArun2v1DBoldDMwLTNew->at(idx_tau) > 0.5 ;
        eleIDMVA=eleIDMVANoIso->at(idx_lep);
        lepPt_=elePt->at(idx_lep);
        taupt_=boostedTauPt->at(idx_tau);
        vis_mass=Z4Momentum.M();
        LeadJetPt = LeadJet.Pt();
        dR_Z_jet=LeadJet.DeltaR(Z4Momentum);
        BoostedTauRawIso=boostedTauByIsolationMVArun2v1DBoldDMwLTraw->at(idx_tau);
        m_sv_=m_sv;
        FullWeight = LumiWeight*LepCorrection*PUWeight*zmasspt_weight * preFireWeight * WBosonKFactor * ttbar_rwt;
        nbjet= numBJet;
        gen_higgs_pT = GetHiggsPt();
        
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


