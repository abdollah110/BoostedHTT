#ifndef Functions_h
#define Functions_h

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH1.h"
#include "TH2.h"
#include "TH1F.h"
#include "TF1.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "math.h"
#include "TGaxis.h"
#include "TLegend.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TInterpreter.h"
#include "TSystem.h"
#include "TNtuple.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TFrame.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <utility>
#include <iostream>
#include <map>
#include "TLorentzVector.h"
#include "../interface/boostHTT.h"
#include "../interface/WeightCalculator.h"
#include "../interface/Corrector.h"
#include "../interface/makeHisto.h"
#include "../interface/event_info.h"
#include "../interface/ComputeWG1Unc.h"


float MuMass= 0.10565837;
float eleMass= 0.000511;


float deltaPhi(float a, float b) {
    float result = a - b;
    while (result > M_PI) result -= 2 * M_PI;
    while (result <= -M_PI) result += 2 * M_PI;
    return fabs(result);
}

float TMass_F(float pt3lep, float px3lep, float py3lep, float met, float metPhi) {
    return sqrt(pow(pt3lep + met, 2) - pow(px3lep + met * cos(metPhi), 2) - pow(py3lep + met * sin(metPhi), 2));
}

float TMass_FNew(float pt3lep, float philep, float met, float metPhi) {
    return sqrt(2*pt3lep * met *(1-cos(deltaPhi(metPhi,philep))));
}



float dR_(float ieta, float iphi, float jeta, float jphi){
    
    float deta=ieta-jeta;
    float dphi=deltaPhi(iphi,jphi);
    return sqrt(pow(deta,2)+pow(dphi,2));
}


struct findDr{
    int order;
    float dR;
};

findDr FindClosetDr(TLorentzVector TauCand, vector<TLorentzVector> Collection){
    
    struct findDr fd;
    fd.dR=1000.;
    fd.order=-1;
    int i =0;
    float minVal = 1000;
    for (auto cand : Collection){
        
        if (TauCand.DeltaR(cand) < minVal){
            fd.order = i;
            fd.dR=TauCand.DeltaR(cand);
            minVal=TauCand.DeltaR(cand);
        }
        i++;
    }
    return fd;
}

//########################################
// Pileup files
//########################################


TH1F *  HistPUData(string year_str){
    //    TFile * PUData= TFile::Open("data/Data_nPU_new.root");
    TFile * PUData= TFile::Open(("data/pu_distributions_data_"+year_str+".root").c_str());
    TH1F * HistoPUData= (TH1F *) PUData->Get("pileup");
    //    HistoPUData->Rebin(2); No need to rebin anymore
    stringstream yearstream(year_str);
    int year=0;
    yearstream >> year;
    
    if (year == 2016 || year == 2017)
        HistoPUData->Rebin(10);
    HistoPUData->Scale(1.0/HistoPUData->Integral());
    return HistoPUData;
}

TH1F *  HistPUMC(TFile *f_Double){
    //    TFile * PUMC= TFile::Open("../interface/pileup-hists/mcMoriondPU.root"); // Not valid for 2017 yet
    //    TH1F * HistoPUMC= (TH1F *) PUMC->Get("pileup");
    TFile * PUMC= TFile::Open(f_Double->GetName());
    TH1F * HistoPUMC= (TH1F *) PUMC->Get("hPUTrue");
    HistoPUMC->Rebin(5);
    HistoPUMC->Scale(1.0/HistoPUMC->Integral());
    //        cout << "HistoPUMC integral= "<<HistoPUMC->Integral()<<"\n";
    return HistoPUMC;
}


//########################################
// Muon Id, Iso, Trigger and Tracker Eff files
//########################################
TH2F**  FuncHistMuTrigger_50(int year){
    if (year == 2016){
        TFile * FileMuTrg= TFile::Open(("data/SF_Muon_Trg_2016_BCDEF.root"));
        TH2F * HistoMuTrg= (TH2F *) FileMuTrg->Get("Mu50_OR_TkMu50_PtEtaBins/pt_abseta_ratio");
        static TH2F* HistoMuTrg_arr[1]={HistoMuTrg};
        return  HistoMuTrg_arr;
    }
    else if (year == 2017){
        TFile * FileMuTrg= TFile::Open(("data/SF_Muon_Trg_2017.root"));
        TH2F * HistoMuTrg= (TH2F *) FileMuTrg->Get("Mu50_PtEtaBins/pt_abseta_ratio");
        static TH2F* HistoMuTrg_arr[1]={HistoMuTrg};
        return  HistoMuTrg_arr;
    }
    else if (year == 2018){
        TFile * FileMuTrg= TFile::Open(("data/SF_Muon_Trg_2018.root"));
        TH2F * HistoMuTrg= (TH2F *) FileMuTrg->Get("Mu50_OR_OldMu100_OR_TkMu100_PtEtaBins/pt_abseta_ratio");
        static TH2F* HistoMuTrg_arr[1]={HistoMuTrg};
        return  HistoMuTrg_arr;
    }
    else
        std::cout<< "which year\n";
    return 0;
}

TH2F**  FuncHistMuTrigger_27(int year){
    if (year == 2016){
        TFile * FileMuTrg= TFile::Open(("data/SF_Muon_Trg_2016_BCDEF.root"));
        TH2F * HistoMuTrg= (TH2F *) FileMuTrg->Get("IsoMu24_OR_IsoTkMu24_PtEtaBins/pt_abseta_ratio");
        static TH2F* HistoMuTrg_arr[1]={HistoMuTrg};
        return  HistoMuTrg_arr;
    }
    else if (year == 2017){
        TFile * FileMuTrg= TFile::Open(("data/SF_Muon_Trg_2017.root"));
        TH2F * HistoMuTrg= (TH2F *) FileMuTrg->Get("IsoMu27_PtEtaBins/pt_abseta_ratio");
        static TH2F* HistoMuTrg_arr[1]={HistoMuTrg};
        return  HistoMuTrg_arr;
    }
    else if (year == 2018){
        TFile * FileMuTrg= TFile::Open(("data/SF_Muon_Trg_2018.root"));
        TH2F * HistoMuTrg= (TH2F *) FileMuTrg->Get("IsoMu24_PtEtaBins/pt_abseta_ratio");
        static TH2F* HistoMuTrg_arr[1]={HistoMuTrg};
        return  HistoMuTrg_arr;
    }
    else
        std::cout<< "which year\n";
    return 0;
}


//}
//
//
//
//    TFile * MuCorrTrg_BCDEF= TFile::Open(("../interface/MuSF/EfficienciesAndSF_RunBtoF_Nov17Nov2017.root"));
//    //    TH1F * HistoMuTrg_BCDEF= (TH1F *) MuCorrTrg_BCDEF->Get("Mu50_EtaBins/eta_ratio");
//    //    TH1F * HistoMuTrg_BCDEF= (TH1F *) MuCorrTrg_BCDEF->Get("Mu50_EtaBins/pt_abseta_ratio");
//    TH2F * HistoMuTrg_BCDEF= (TH2F *) MuCorrTrg_BCDEF->Get("IsoMu27_PtEtaBins/pt_abseta_ratio");
//
//    static TH2F* HistoMuTrg_arr[2]={HistoMuTrg_BCDEF};
//    return HistoMuTrg;
//}


TGraphAsymmErrors * FuncHistMuTrack(){
    
    TFile * MuCorrTrack= TFile::Open(("../interface/pileup-hists/Tracking_EfficienciesAndSF_BCDEFGH.root"));
    TGraphAsymmErrors * HistoMuTrack= (TGraphAsymmErrors *) MuCorrTrack->Get("ratio_eff_eta3_dr030e030_corr");
    
    return HistoMuTrack;
}


TH2F**  FuncHistMuId(int year){
    if (year == 2016){
        TFile * FileMuId= TFile::Open(("data/SF_Muon_Id_2016_BCDEF.root"));
        TH2F * HistoMuId= (TH2F *) FileMuId->Get("NUM_MediumID_DEN_genTracks_eta_pt");
        static TH2F* HistoMuId_arr[1]={HistoMuId};
        return  HistoMuId_arr;
    }
    else if (year == 2017){
        TFile * FileMuId= TFile::Open(("data/SF_Muon_Id_2017.root"));
        TH2F * HistoMuId= (TH2F *) FileMuId->Get("NUM_MediumID_DEN_genTracks_pt_abseta");
        static TH2F* HistoMuId_arr[1]={HistoMuId};
        return  HistoMuId_arr;
    }
    else if (year == 2018){
        TFile * FileMuId= TFile::Open(("data/SF_Muon_Id_2018.root"));
        TH2F * HistoMuId= (TH2F *) FileMuId->Get("NUM_MediumID_DEN_TrackerMuons_pt_abseta");
        static TH2F* HistoMuId_arr[1]={HistoMuId};
        return  HistoMuId_arr;
    }
    else
        std::cout<< "which year\n";
    return 0;
}


TH2F**  FuncHistMuIso(int year){
    if (year == 2016){
        TFile * FileMuIso= TFile::Open(("data/SF_Muon_Iso_2016_BCDEF.root"));
        TH2F * HistoMuIso= (TH2F *) FileMuIso->Get("NUM_LooseRelIso_DEN_MediumID_eta_pt");
        static TH2F* HistoMuIso_arr[1]={HistoMuIso};
        return  HistoMuIso_arr;
    }
    else if (year == 2017){
        TFile * FileMuIso= TFile::Open(("data/SF_Muon_Iso_2017.root"));
        TH2F * HistoMuIso= (TH2F *) FileMuIso->Get("NUM_LooseRelIso_DEN_MediumID_pt_abseta");
        static TH2F* HistoMuIso_arr[1]={HistoMuIso};
        return  HistoMuIso_arr;
    }
    else if (year == 2018){
        TFile * FileMuIso= TFile::Open(("data/SF_Muon_Iso_2018.root"));
        TH2F * HistoMuIso= (TH2F *) FileMuIso->Get("NUM_LooseRelIso_DEN_MediumID_pt_abseta");
        static TH2F* HistoMuIso_arr[1]={HistoMuIso};
        return  HistoMuIso_arr;
    }
    else
        std::cout<< "which year\n";
    return 0;
}




//########################################
// Ele Id, Iso, Trigger and Tracker Eff files
//########################################

//
//
////    TFile * EleCorrMVAIdIso90= TFile::Open(("../interface/pileup-hists/egammaEffi.txt_EGM2D.root"));
//    TFile * EleCorrMVAIdIso90= TFile::Open(("data/2017_ElectronMVA90noiso.root"));
//    TH2F * HistoEleMVAIdIso90= (TH2F *) EleCorrMVAIdIso90->Get("EGamma_SF2D");
////    TH2F * HistoEleMVAIdIso90_EffMC= (TH2F *) EleCorrMVAIdIso90->Get("EGamma_EffMC2D");
////    TH2F * HistoEleMVAIdIso90_EffData= (TH2F *) EleCorrMVAIdIso90->Get("EGamma_EffData2D");
//
//    TFile * EleCorrReco= TFile::Open(("data/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root"));
//    TH2F * HistoEleReco= (TH2F *) EleCorrReco->Get("EGamma_SF2D");
//
//
//



TH2F** FuncHistEleReco(){
    
    TFile * eleF= TFile::Open(("../interface/EleSF/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root"));
    TH2F * HistoEle= (TH2F *) eleF->Get("EGamma_SF2D");
    
    static  TH2F* HistoElReco[1]={HistoEle};
    
    return HistoElReco;
    
    
    
}

TH2F**  FuncHistEleId(int year){
    if (year == 2016){
        TFile * FileEleId= TFile::Open(("data/SF_Electron_Id_2016.root"));
        TH2F * HistoEleId= (TH2F *) FileEleId->Get("EGamma_SF2D");
        static TH2F* HistoEleId_arr[1]={HistoEleId};
        return  HistoEleId_arr;
    }
    else if (year == 2017){
        TFile * FileEleId= TFile::Open(("data/SF_Electron_Id_2017.root"));
        TH2F * HistoEleId= (TH2F *) FileEleId->Get("EGamma_SF2D");
        static TH2F* HistoEleId_arr[1]={HistoEleId};
        return  HistoEleId_arr;
    }
    else if (year == 2018){
        TFile * FileEleId= TFile::Open(("data/SF_Electron_Id_2018.root"));
        TH2F * HistoEleId= (TH2F *) FileEleId->Get("EGamma_SF2D");
        static TH2F* HistoEleId_arr[1]={HistoEleId};
        return  HistoEleId_arr;
    }
    else
        std::cout<< "which year\n";
    return 0;
}


TH2F**  FuncHistEleTrigger(int year){
    
    TFile * FileEleTrg= TFile::Open(("data/SF_Electron_Trg_2016.root"));
    TH2F * HistoEleTrg= (TH2F *) FileEleTrg->Get("Ele27_WPTight_Gsf");
    static TH2F* HistoEleTrg_arr[1]={HistoEleTrg};
    return  HistoEleTrg_arr;
}

//########################################
// Electron MVA IdIso files
//########################################
TH2F * FuncHistEleMVAId(std::string type){
    
    
    //    TFile * EleCorrMVAIdIso90= TFile::Open(("../interface/pileup-hists/egammaEffi.txt_EGM2D.root")); //This is for 2016
    TFile * EleCorrMVAIdIso90= TFile::Open(("../interface/pileup-hists/gammaEffi.txt_EGM2D_runBCDEF_passingMVA94Xwp90iso.root"));
    TH2F * HistoEleMVAIdIso90= (TH2F *) EleCorrMVAIdIso90->Get("EGamma_SF2D");
    TH2F * HistoEleMVAIdIso90_EffMC= (TH2F *) EleCorrMVAIdIso90->Get("EGamma_EffMC2D");
    TH2F * HistoEleMVAIdIso90_EffData= (TH2F *) EleCorrMVAIdIso90->Get("EGamma_EffData2D");
    
    if (type.find("Tot") != string::npos)
        return HistoEleMVAIdIso90;
    else if (type.find("MC") != string::npos)
        return HistoEleMVAIdIso90_EffMC;
    else if (type.find("Data") != string::npos)
        return HistoEleMVAIdIso90_EffData;
    else
        return 0;
    
}




// Not Used anymore
//    TFile * KFactor= TFile::Open("../interface/NewKFactor/kfactor_vjet_qcd/kfactor_24bins.root");
//
//    TH1F * WLO= (TH1F *) KFactor->Get("WJets_LO/inv_pt");
//    TH1F * WNLO_ewk= (TH1F *) KFactor->Get("EWKcorr/W");
//    TH1F * WNLO_qcd= (TH1F *) KFactor->Get("WJets_012j_NLO/nominal");
//
//    TH1F * ZLO= (TH1F *) KFactor->Get("DYJets_LO/inv_pt");
//    TH1F * ZNLO_ewk= (TH1F *) KFactor->Get("EWKcorr/DY");
//    TH1F * ZNLO_qcd= (TH1F *) KFactor->Get("DYJets_012j_NLO/nominal");






//########################################
// W and DY K-factor files  (FIT-based K-factor)
//########################################

TFile * kfactorW=TFile::Open("../interface/kfactor_W.root");
TH1F* HistkfactorW= (TH1F*) kfactorW->Get("KFcator");
float kf_W_1=HistkfactorW->GetBinContent(1);
float kf_W_2=HistkfactorW->GetBinContent(2);


TFile * kfactorWUp=TFile::Open("../interface/kfactor_monoJet_WUp.root");
TH1F* HistkfactorWUp= (TH1F*) kfactorWUp->Get("KFcator");
float kf_W_1Up=HistkfactorWUp->GetBinContent(1);
float kf_W_2Up=HistkfactorWUp->GetBinContent(2);

TFile * kfactorWDown=TFile::Open("../interface/kfactor_monoJet_WDown.root");
TH1F* HistkfactorWDown= (TH1F*) kfactorWDown->Get("KFcator");
float kf_W_1Down=HistkfactorWDown->GetBinContent(1);
float kf_W_2Down=HistkfactorWDown->GetBinContent(2);



TFile * kfactorZ=TFile::Open("../interface/kfactor_Z.root");
TH1F* HistkfactorZ= (TH1F*) kfactorZ->Get("KFcator");
float kf_Z_1=HistkfactorZ->GetBinContent(1);
float kf_Z_2=HistkfactorZ->GetBinContent(2);


TFile * kfactorZUp=TFile::Open("../interface/kfactor_monoJet_ZUp.root");
TH1F* HistkfactorZUp= (TH1F*) kfactorZUp->Get("KFcator");
float kf_Z_1Up=HistkfactorZUp->GetBinContent(1);
float kf_Z_2Up=HistkfactorZUp->GetBinContent(2);

TFile * kfactorZDown=TFile::Open("../interface/kfactor_monoJet_ZDown.root");
TH1F* HistkfactorZDown= (TH1F*) kfactorZDown->Get("KFcator");
float kf_Z_1Down=HistkfactorZDown->GetBinContent(1);
float kf_Z_2Down=HistkfactorZDown->GetBinContent(2);


// Load Cecile's 2016 Top pT root file
//std::string fTop2016corrName = "data/toppt_correction_to_2016.root";
TFile * fTop2016corr = TFile::Open("data/toppt_correction_to_2016.root");
TF1 * TF_Top2016corr = (TF1*) fTop2016corr->Get("toppt_ratio_to_2016");
//fTop2016corr->Close();


float FuncBosonKFactor(std::string X){
    
    if (X.find("W1Cen") != string::npos)
        return kf_W_1;
    else if (X.find("W2Cen") != string::npos)
        return kf_W_2;
    else if (X.find("W1Up") != string::npos)
        return kf_W_1Up;
    else if (X.find("W2Up") != string::npos)
        return kf_W_2Up;
    else if (X.find("W1Down") != string::npos)
        return kf_W_1Down;
    else if (X.find("W2Down") != string::npos)
        return kf_W_2Down;
    
    else if (X.find("Z1Cen") != string::npos)
        return kf_Z_1;
    else if (X.find("Z2Cen") != string::npos)
        return kf_Z_2;
    else if (X.find("Z1Up") != string::npos)
        return kf_Z_1Up;
    else if (X.find("Z2Up") != string::npos)
        return kf_Z_2Up;
    else if (X.find("Z1Down") != string::npos)
        return kf_Z_1Down;
    else if (X.find("Z2Down") != string::npos)
        return kf_Z_2Down;
    
    
    else
        return 0;
}




//int getNumTau(){
//
//
//    int numTau=0;
//    for  (int itau=0 ; itau < nTau; itau++){
//
//        if (tauPt->at(itau) < 20  || fabs(tauEta->at(itau)) > 2.3 ) continue;
//
//        bool TauIdIso =  taupfTausDiscriminationByDecayModeFinding->at(itau) > 0.5 && tauByLooseMuonRejection3->at(itau) > 0 && tauByMVA6LooseElectronRejection->at(itau) > 0 && tauByLooseIsolationMVArun2v1DBnewDMwLT->at(itau) > 0;
//
//        if (!TauIdIso) continue;
//        numTau++;
//    }
//    return numTau;
//}



//###########       Lepton  Veto   ###########################################################


bool MatchedBoostedTauId(TLorentzVector Object4Momentum){
    
    bool passVLooseIsolation = false;
    TLorentzVector BoostTau4Mom;
    float dR_=100;
    for (int ibtau = 0; ibtau < nBoostedTau; ++ibtau){
        BoostTau4Mom.SetPtEtaPhiM(boostedTauPt->at(ibtau),boostedTauEta->at(ibtau),boostedTauPhi->at(ibtau),boostedTauMass->at(ibtau));
        if(BoostTau4Mom.DeltaR(Object4Momentum) < dR_ ){
            passVLooseIsolation = boostedTauByVLooseIsolationMVArun2v1DBnewDMwLTNew->at(ibtau);
            dR_=BoostTau4Mom.DeltaR(Object4Momentum);
        }
    }
    return passVLooseIsolation;
    }

float MatchedBoostedTauIsolation(TLorentzVector Object4Momentum){
    
    float BoostTauIsoVar = -1;
    TLorentzVector BoostTau4Mom;
    float dR_=100;
    for (int ibtau = 0; ibtau < nBoostedTau; ++ibtau){
        BoostTau4Mom.SetPtEtaPhiM(boostedTauPt->at(ibtau),boostedTauEta->at(ibtau),boostedTauPhi->at(ibtau),boostedTauMass->at(ibtau));
        if(BoostTau4Mom.DeltaR(Object4Momentum) < dR_ ){
            BoostTauIsoVar = boostedTauByIsolationMVArun2v1DBnewDMwLTrawNew->at(ibtau);
            dR_=BoostTau4Mom.DeltaR(Object4Momentum);
        }
    }
    return BoostTauIsoVar;
    }
    
    
int getNumElectron(){
    
    
    //            https://twiki.cern.ch/twiki/bin/view/CMS/MultivariateElectronIdentificationRun2#Recommended_MVA_recipes_for_2016
    int numElectron=0;
    for  (int jele=0 ; jele < nEle; jele++){
        
        if ( elePt->at(jele) < 40 || fabs(eleEta->at(jele)) > 2.5) continue;
        
        bool eleMVAIdExtra= false;
        if (fabs (eleSCEta->at(jele)) <= 0.8 && eleIDMVANoIso->at(jele) >    0.837   ) eleMVAIdExtra= true;
        else if (fabs (eleSCEta->at(jele)) >  0.8 &&fabs (eleSCEta->at(jele)) <=  1.5 && eleIDMVANoIso->at(jele) >    0.715   ) eleMVAIdExtra= true;
        else if ( fabs (eleSCEta->at(jele)) >=  1.5 && eleIDMVANoIso->at(jele) >   0.357   ) eleMVAIdExtra= true;
        else eleMVAIdExtra= false;
        
        
        if (!eleMVAIdExtra) continue;
        
        float IsoEle=elePFChIso->at(jele)/elePt->at(jele);
        if ( (elePFNeuIso->at(jele) + elePFPhoIso->at(jele) - 0.5* elePFPUIso->at(jele) )  > 0.0)
            IsoEle= ( elePFChIso->at(jele) + elePFNeuIso->at(jele) + elePFPhoIso->at(jele) - 0.5* elePFPUIso->at(jele))/elePt->at(jele);
        
        if (elePt->at(jele) >= 120 ){
            numElectron++;
        }
        else if (elePt->at(jele) >= 40  && IsoEle < 0.30 ){
            numElectron++;
        }
    }
    return numElectron;
}


int getNumElectron(TLorentzVector Object4Momentum){
    
    
    //            https://twiki.cern.ch/twiki/bin/view/CMS/MultivariateElectronIdentificationRun2#Recommended_MVA_recipes_for_2016
    int numElectron=0;
    for  (int jele=0 ; jele < nEle; jele++){
        
        TLorentzVector Lep4Momentum;
        Lep4Momentum.SetPtEtaPhiM(elePt->at(jele),eleEta->at(jele),elePhi->at(jele),eleMass);
        if (Object4Momentum.DeltaR(Lep4Momentum) > 0.8) continue;
        
        if ( elePt->at(jele) < 40 || fabs(eleEta->at(jele)) > 2.5) continue;
        
        bool eleMVAIdExtra= false;
        if (fabs (eleSCEta->at(jele)) <= 0.8 && eleIDMVANoIso->at(jele) >    0.837   ) eleMVAIdExtra= true;
        else if (fabs (eleSCEta->at(jele)) >  0.8 &&fabs (eleSCEta->at(jele)) <=  1.5 && eleIDMVANoIso->at(jele) >    0.715   ) eleMVAIdExtra= true;
        else if ( fabs (eleSCEta->at(jele)) >=  1.5 && eleIDMVANoIso->at(jele) >   0.357   ) eleMVAIdExtra= true;
        else eleMVAIdExtra= false;
        
        
        if (!eleMVAIdExtra) continue;
        
        float IsoEle=elePFChIso->at(jele)/elePt->at(jele);
        if ( (elePFNeuIso->at(jele) + elePFPhoIso->at(jele) - 0.5* elePFPUIso->at(jele) )  > 0.0)
            IsoEle= ( elePFChIso->at(jele) + elePFNeuIso->at(jele) + elePFPhoIso->at(jele) - 0.5* elePFPUIso->at(jele))/elePt->at(jele);
        
        if (elePt->at(jele) >= 120 ){
            numElectron++;
        }
        else if (elePt->at(jele) >= 40  && IsoEle < 0.30 ){
            numElectron++;
        }
    }
    return numElectron;
}






int getNumMuon(){
    
    int numMuon=0;
    for  (int jmu=0 ; jmu < nMu; jmu++){
        
        if ( muPt->at(jmu) < 30 || fabs(muEta->at(jmu)) > 2.4) continue;
        bool MuId=( (muIDbit->at(jmu) >> 1 & 1)  && fabs(muD0->at(jmu)) < 0.045 && fabs(muDz->at(jmu)) < 0.2);
        if (!MuId) continue;
        
        float IsoMu=muPFChIso->at(jmu)/muPt->at(jmu);
        if ( (muPFNeuIso->at(jmu) + muPFPhoIso->at(jmu) - 0.5* muPFPUIso->at(jmu) )  > 0.0)
            IsoMu= ( muPFChIso->at(jmu) + muPFNeuIso->at(jmu) + muPFPhoIso->at(jmu) - 0.5* muPFPUIso->at(jmu))/muPt->at(jmu);
        
        if (muPt->at(jmu) >= 55){
            numMuon++;
        }
        else if (muPt->at(jmu) >= 30 && IsoMu < 0.3){
            numMuon++;
        }
    }
    return numMuon;
}

int getNumMuon(TLorentzVector Object4Momentum){
    
    int numMuon=0;
    for  (int jmu=0 ; jmu < nMu; jmu++){
        
        TLorentzVector Lep4Momentum;
        Lep4Momentum.SetPtEtaPhiM(muPt->at(jmu),muEta->at(jmu),muPhi->at(jmu),MuMass);
        if (Object4Momentum.DeltaR(Lep4Momentum) > 0.8) continue;
        
        if ( muPt->at(jmu) < 30 || fabs(muEta->at(jmu)) > 2.4) continue;
        bool MuId=( (muIDbit->at(jmu) >> 1 & 1)  && fabs(muD0->at(jmu)) < 0.045 && fabs(muDz->at(jmu)) < 0.2);
        if (!MuId) continue;
        
        float IsoMu=muPFChIso->at(jmu)/muPt->at(jmu);
        if ( (muPFNeuIso->at(jmu) + muPFPhoIso->at(jmu) - 0.5* muPFPUIso->at(jmu) )  > 0.0)
            IsoMu= ( muPFChIso->at(jmu) + muPFNeuIso->at(jmu) + muPFPhoIso->at(jmu) - 0.5* muPFPUIso->at(jmu))/muPt->at(jmu);
        
        if (muPt->at(jmu) >= 55){
            numMuon++;
        }
        else if (muPt->at(jmu) >= 30 && IsoMu < 0.3){
            numMuon++;
        }
    }
    return numMuon;
}


//###########       electron  correction factor   ###########################################################

//float getElectronCor(TH2F * HistoEleMVAIdIso90){
//    
//    float ElectronCor=1;
//    for  (int jele=0 ; jele < nEle; jele++){
//        
//        if ( elePt->at(jele) < 15 || fabs(eleEta->at(jele)) > 2.5) continue;
//        
//        bool eleMVAIdExtra= false;
//        if (fabs (eleSCEta->at(jele)) <= 0.8 && eleIDMVAIso->at(jele) >   -0.83  ) eleMVAIdExtra= true;
//        else if (fabs (eleSCEta->at(jele)) >  0.8 &&fabs (eleSCEta->at(jele)) <=  1.5 && eleIDMVAIso->at(jele) >   -0.77  ) eleMVAIdExtra= true;
//        else if ( fabs (eleSCEta->at(jele)) >=  1.5 && eleIDMVAIso->at(jele) >  -0.69  ) eleMVAIdExtra= true;
//        else eleMVAIdExtra= false;
//        
//        
//        if (eleMVAIdExtra)
//            ElectronCor=getCorrFactorMVA90WPElectron94X(isData,  elePt->at(jele),eleSCEta->at(jele),    HistoEleMVAIdIso90 );
//        
//        break;
//    }
//    return ElectronCor;
//}

//###########       Z boson Veto   ###########################################################


int getNumZBoson(){
    
    
    
    
    int numZboson=0;
    for (int xmu=0; xmu< nMu; xmu++){
        for (int ymu=xmu+1; ymu< nMu; ymu++){
            
            TLorentzVector Mu4Momentum_0,Mu4Momentum_1,Z4Momentum;
            Mu4Momentum_0.SetPtEtaPhiM(muPt->at(xmu),muEta->at(xmu),muPhi->at(xmu),MuMass);
            Mu4Momentum_1.SetPtEtaPhiM(muPt->at(ymu),muEta->at(ymu),muPhi->at(ymu),MuMass);
            Z4Momentum=Mu4Momentum_1+Mu4Momentum_0;
            
            float IsoMu1=muPFChIso->at(xmu)/muPt->at(xmu);
            if ( (muPFNeuIso->at(xmu) + muPFPhoIso->at(xmu) - 0.5* muPFPUIso->at(xmu) )  > 0.0)
                IsoMu1= ( muPFChIso->at(xmu)/muPt->at(xmu) + muPFNeuIso->at(xmu) + muPFPhoIso->at(xmu) - 0.5* muPFPUIso->at(xmu))/muPt->at(xmu);
            
            float IsoMu2=muPFChIso->at(ymu)/muPt->at(ymu);
            if ( (muPFNeuIso->at(ymu) + muPFPhoIso->at(ymu) - 0.5* muPFPUIso->at(ymu) )  > 0.0)
                IsoMu2= ( muPFChIso->at(ymu)/muPt->at(ymu) + muPFNeuIso->at(ymu) + muPFPhoIso->at(ymu) - 0.5* muPFPUIso->at(ymu))/muPt->at(ymu);
            
            if ( muPt->at(xmu) > 60 && muPt->at(ymu) > 15 &&  (muIDbit->at(xmu) >> 1 & 1) & (muIDbit->at(ymu) >> 1 & 1) & IsoMu1 < 0.25  && IsoMu2 < 0.25 && Z4Momentum.M() > 80 && Z4Momentum.M()< 100  && (muCharge->at(xmu) * muCharge->at(ymu) < 0))
                numZboson++;
        }
    }
    
    return numZboson;
    
}

//================================================================================================
// top-pT Reweighting
//================================================================================================

float newTopPtReweight(float top1Pt, float top2Pt, int year, std::string syst){
    
    // Christian's way
    float pttop1 = std::min(static_cast<float>(472.0), top1Pt);
    float pttop2 = std::min(static_cast<float>(472.0), top2Pt);
    float a = 0.088, b = -0.00087, c = 0.00000092;
    float ttbar_scale = sqrt(exp(a+b*pttop1+c*pttop1*pttop1)*exp(a+b*pttop2+c*pttop2*pttop2));
    //you need to multiply the weight by (1.0/fct_tt->Eval(pttop1))*(1.0/fct_tt->Eval(pttop2))
    if (year==2016) ttbar_scale*=(1.0/TF_Top2016corr->Eval(pttop1))*(1.0/TF_Top2016corr->Eval(pttop2));
    
    if (syst.find("ttbarShape_Up") != string::npos) {
        return (2 * ttbar_scale - 1);  // 2*√[e^(..)*e^(..)] - 1
    } else if (syst.find("ttbarShape_Down") != string::npos) {
        return 1; // no weight for shift down
    } else {
        return ttbar_scale;  // √[e^(..)*e^(..)]
    }
    return -1000;
}

//-----------------------------------------------------------------------------
// AM: recipe for top quark Pt reweighting taken from https://twiki.cern.ch/twiki/bin/viewauth/CMS/TopPtReweighting

float compTopPtWeight(float topPt) {
    //Updated values for 13 TeV
    const float a =  0.0615  ;
    const float b =  -0.0005 ;
    //    const float a =  0.148 ;
    //    const float b =  -0.00129;
    //    const float a = 0.156;
    //    const float b = -0.00137;
    return TMath::Exp(a + b * topPt);
}

float compTopPtWeight(float top1Pt, float top2Pt) {
    //std::cout << "<compTopPtWeight>:" << std::endl;
    float topPtWeight2 = compTopPtWeight(top1Pt) * compTopPtWeight(top2Pt);
    //std::cout << " top1Pt = " << top1Pt << ", top2Pt = " << top2Pt << ": topPtWeight2 = " << topPtWeight2 << std::endl;
    return ( topPtWeight2 > 0.) ? TMath::Sqrt(topPtWeight2) : 0.;
}



//vector<float> getMatchedRecoTau(TLorentzVector recoTau){
//
//
//    vector<float> matcdedRecoTau;
//
//    float LowestDR=100;
//    TLorentzVector tau;
//    int index=0;
//    for (int itau=0; itau < nTau; itau++){
//
//        tau.SetPtEtaPhiM(tauPt->at(itau),tauEta->at(itau),tauPhi->at(itau),tauMass->at(itau));
//        float dr_boost_reco= recoTau.DeltaR(tau);
//        if (dr_boost_reco < LowestDR)  {
//            LowestDR= dr_boost_reco;
//            index=itau;
//        }
//    }
//    matcdedRecoTau.push_back(LowestDR);
//    matcdedRecoTau.push_back(tauByIsolationMVArun2v1DBnewDMwLTraw->at(index));
//    matcdedRecoTau.push_back(tauByIsolationMVArun2v2DBnewDMwLTraw->at(index));
//    matcdedRecoTau.push_back(tauPt->at(index));
//    matcdedRecoTau.push_back(tauEta->at(index));
//    matcdedRecoTau.push_back(tauCombinedIsolationDeltaBetaCorrRaw3Hits->at(index));
//
//    return matcdedRecoTau;
//}




TLorentzVector getMatchedGenEle(TLorentzVector recoEle){
    
    TLorentzVector genTau;
    TLorentzVector SelectedGenEle;
    float LowestDR=100;
    for (int igen=0; igen < nMC; igen++){
        
        if ( fabs(mcPID->at(igen)) ==11 && fabs(mcMomPID->at(igen)) ==15 ){
            genTau.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
            float dr_gen_reco= recoEle.DeltaR(genTau);
            if (dr_gen_reco < LowestDR)  {
                LowestDR= dr_gen_reco;
                SelectedGenEle.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
                //                cout<<"\t\t found a match, dR= "<<LowestDR<<"\n";
            }
        }
    }
    return SelectedGenEle;
}


TLorentzVector getMatchedGenMu(TLorentzVector recoMu){
    
    TLorentzVector genTau;
    TLorentzVector SelectedGenMu;
    float LowestDR=100;
    for (int igen=0; igen < nMC; igen++){
        
        if ( fabs(mcPID->at(igen)) ==13 && fabs(mcMomPID->at(igen)) ==15 ){
            genTau.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
            float dr_gen_reco= recoMu.DeltaR(genTau);
            if (dr_gen_reco < LowestDR)  {
                LowestDR= dr_gen_reco;
                SelectedGenMu.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
                //                cout<<"\t\t found a match, dR= "<<LowestDR<<"\n";
            }
        }
    }
    return SelectedGenMu;
}

TLorentzVector getMatchedGenTau(TLorentzVector recoTau){
    
    TLorentzVector genTau;
    TLorentzVector SelectedGenTau;
    float LowestDR=100;
    for (int igen=0; igen < nMC; igen++){
        
        if ( fabs(mcPID->at(igen)) ==15){
            genTau.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
            float dr_gen_reco= recoTau.DeltaR(genTau);
            if (dr_gen_reco < LowestDR)  {
                LowestDR= dr_gen_reco;
                SelectedGenTau.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
                //                cout<<"\t\t found a match, dR= "<<LowestDR<<"\n";
            }
        }
    }
    return SelectedGenTau;
}

bool isMatchedToGenTau(TLorentzVector recoTau){
    
    bool hasMatchedToGenTau = false;
    TLorentzVector genTau;
    TLorentzVector SelectedGenTau;
    float LowestDR=0.5;
    for (int igen=0; igen < nMC; igen++){
        
        if ( fabs(mcPID->at(igen)) ==15){
            genTau.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
            float dr_gen_reco= recoTau.DeltaR(genTau);
            if (dr_gen_reco < LowestDR)
                hasMatchedToGenTau= true;
        }
    }
    return hasMatchedToGenTau;
}



float GetHiggsPt(){
    float Higgspt=0;
    for (int igen=0;igen < nMC; igen++){
        if (mcPID->at(igen) == 25){
            Higgspt = mcPt->at(igen) ;
            return Higgspt;
        }
    }
    return Higgspt;
}

vector<float>  GeneratorInfo(){
    
    vector<float>    infoGen;
    infoGen.clear();
    
    
    
    float GenTopPt=0;
    float GenAntiTopPt=0;
    float TopPtReweighting = 1;
    float WBosonPt=0;
    float WBosonKFactor=1;
    float ZBosonPt=0;
    float ZBosonKFactor=1;
    int modPDGId=-10;
    int AntimodPDGId=-10;
    float WBosonMass=0;
    float ZBosonMass=0;
    float ZmumuMass=0;
    float ZeeMass=0;
    float ZttMass=0;
    
    TLorentzVector GenMu4Momentum,GenAntiMu4Momentum, WGEN4Momentum, MUGEN4Momentum, NUGEN4Momentum, GenLep4Momentum,GenAntiLep4Momentum, GenTau4Momentum, GenAntiTau4Momentum;
    
    
    for (int igen=0;igen < nMC; igen++){
        
        // Status 62 means: isLastCopy=1 and fromHardProcess=1
        
        //Top Pt
        if (mcPID->at(igen) == 6 && mcStatus->at(igen) ==22) GenTopPt=mcPt->at(igen) ;
        if (mcPID->at(igen) == -6 && mcStatus->at(igen) ==22) GenAntiTopPt=mcPt->at(igen);
        
        
        //W Pt
        if (fabs(mcPID->at(igen)) ==24   && mcStatus->at(igen) ==22)  {WBosonPt= mcPt->at(igen); WBosonMass=mcMass->at(igen);}
        if ( fabs(mcPID->at(igen)) ==13 && mcStatus->at(igen) ==1 )  {MUGEN4Momentum.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));}
        if ( fabs(mcPID->at(igen)) ==14  && mcStatus->at(igen) ==1)  {NUGEN4Momentum.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));}
        
        //Z Pt
        if (fabs(mcPID->at(igen)) ==23)  {ZBosonPt= mcPt->at(igen); ZBosonMass= mcMass->at(igen);}
        // Lepton from Z
        if (mcStatusFlag->at(igen) > 760 && mcStatusFlag->at(igen) < 780  &&  (mcPID->at(igen) ==11 || mcPID->at(igen) ==13  || mcPID->at(igen) ==15))  {GenLep4Momentum.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
        }
        // antiLepton from Z
        if (mcStatusFlag->at(igen) > 760 && mcStatusFlag->at(igen) < 780  &&  (mcPID->at(igen) == -11 || mcPID->at(igen) == -13  || mcPID->at(igen) == -15))  {GenAntiLep4Momentum.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
        }
    }
    
    //
    //
    //
    //
    //
    ////        cout<<"\n Z boson  status is "<<mcStatus->at(igen)<<"\n";
    //
    //        } //FIXME somethime we do not have Z in the DY events
    //        if ( mcPID->at(igen) ==13   )  {
    //        GenMu4Momentum.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
    //            //        modPDGId=mcMomPID->at(igen);
    ////            cout<<"\n muon  status is "<< mcPID->at(igen) << " "<<mcStatus->at(igen)<<"\n";
    //        }
    //        if ( mcPID->at(igen) ==-13) {GenAntiMu4Momentum.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
    //            //         AntimodPDGId=mcMomPID->at(igen);
    ////            cout<<"\n ANTI muon  status is "<<mcPID->at(igen) << " "<<mcStatus->at(igen)<<"\n";
    //        }
    //
    //        if (mcPt->at(igen) > 10 &&  (mcPID->at(igen) ==11 || mcPID->at(igen) ==13  || mcPID->at(igen) ==15))  {GenLep4Momentum.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
    //        cout<<"electron id "<<mcPID->at(igen) << " status "<<mcStatusFlag->at(igen)<< " pt "<< mcPt->at(igen) <<" mom "<<mcMomPID->at(igen)<<"\n";
    //        }
    //        if (mcPt->at(igen) > 10 &&  (mcPID->at(igen) == -11 || mcPID->at(igen) == -13  || mcPID->at(igen) == -15))  {GenAntiLep4Momentum.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
    //        cout<<"\t ANTI electron id "<<mcPID->at(igen) << " status "<<mcStatusFlag->at(igen)<< " pt "<< mcPt->at(igen)<<" mom "<<mcMomPID->at(igen)<<"\n";
    //        }
    //
    //                if ( mcPID->at(igen) ==15)  {GenTau4Momentum.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
    //                }
    //                if ( mcPID->at(igen) ==-15)  {GenAntiTau4Momentum.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
    //                }
    //
    //    }
    //
    //    ZmumuMass=(GenMu4Momentum+GenAntiMu4Momentum).M();
    //    ZeeMass= (GenLep4Momentum+GenAntiLep4Momentum).M();
    
    TopPtReweighting=compTopPtWeight(GenTopPt, GenAntiTopPt);
    
    if (ZBosonMass < 10){
        ZBosonPt=(GenLep4Momentum+GenAntiLep4Momentum).Pt();  //This is a temp solution to the above problem
        ZBosonMass=(GenLep4Momentum+GenAntiLep4Momentum).M();  //This is a temp solution to the above problem
    }
    
    if (WBosonPt==0)
        WBosonPt = (MUGEN4Momentum+NUGEN4Momentum).Pt();
    
    //######################## Top Pt Reweighting
    infoGen.push_back(TopPtReweighting);
    
    //######################## W Pt/Mass
    infoGen.push_back(WBosonPt);
    infoGen.push_back(WBosonMass);
    infoGen.push_back(ZBosonPt);
    infoGen.push_back(ZBosonMass);
    infoGen.push_back(GenTopPt);
    infoGen.push_back(GenAntiTopPt);
    
    //    //######################## Z Pt
    //    infoGen.push_back(ZBosonPt);
    //    infoGen.push_back((GenMu4Momentum+GenAntiMu4Momentum).Pt());
    //    infoGen.push_back((GenLep4Momentum+GenAntiLep4Momentum).Pt());
    //    infoGen.push_back((GenTau4Momentum+GenAntiTau4Momentum).Pt());
    //
    //    //######################## Z Mass
    //    infoGen.push_back(ZBosonMass);
    //    infoGen.push_back((GenMu4Momentum+GenAntiMu4Momentum).M());
    //    infoGen.push_back((GenLep4Momentum+GenAntiLep4Momentum).M());
    //    infoGen.push_back((GenTau4Momentum+GenAntiTau4Momentum).M());
    
    return infoGen;
    
}


//########################################
// Btagging scale factor This part is the outcome of the CodexAnalyzer_BTagEff.cc
//########################################

TH2F **  FuncHistBTagSF(){
    TFile * TTEff= TFile::Open(("../interface/OutFiles_BTagSF/TTJets.root"));
    TH2F * TTSF0_btagged= (TH2F *) TTEff->Get("BSF_FLV0_Btagged");
    TH2F * TTSF0_total= (TH2F *) TTEff->Get("BSF_FLV0_Total");
    TH2F * TTSF5_btagged= (TH2F *) TTEff->Get("BSF_FLV5_Btagged");
    TH2F * TTSF5_total= (TH2F*) TTEff->Get("BSF_FLV5_Total");
    
    static TH2F * Btagg_TT[4]={TTSF0_btagged,TTSF0_total,TTSF5_btagged,TTSF5_total};
    
    return Btagg_TT;
}

//        TFile * DataEff= TFile::Open(("OutFiles_BTagSF/Data.root"));
//        TH2F * DataSF0_btagged= (TH2F *) DataEff->Get("BSF_FLV0_Btagged");
//        TH2F * DataSF0_total= (TH2F *) DataEff->Get("BSF_FLV0_Total");
//        TH2F * DataSF5_btagged= (TH2F *) DataEff->Get("BSF_FLV5_Btagged");
//        TH2F * DataSF5_total= (TH2F *) DataEff->Get("BSF_FLV5_Total");


//###########       getBtagEfficiency using TTbar samples from CodexAnalyzer_BTagEff.cc   ###########################################################

float getBtagEfficiency(bool isData, bool passCSV, float pt, float eta, TH2F ** Btagg_TT){
    
    
    if ( isData) return 1;
    
    
    
    int ptBIN;
    if ( pt < 50 ) ptBIN=1;
    if (pt >= 50 && pt < 70 ) ptBIN=2;
    if (pt >= 70 && pt < 100 ) ptBIN=3;
    if (pt >= 100 && pt < 140) ptBIN=4;
    if (pt >= 140 && pt < 200) ptBIN=5;
    if (pt >= 200 && pt < 300) ptBIN=6;
    if (pt >= 300 && pt < 600) ptBIN=7;
    if (pt >= 600 ) ptBIN=8;
    
    int etaBIN;
    if (eta >= 0 && eta < 0.8 ) etaBIN=1;
    if (eta >= 0.8 && eta < 1.5 ) etaBIN=2;
    if (eta >= 1.5 ) etaBIN=3;
    
    
    
    TH2F * TTSF0_btagged=Btagg_TT[0];
    TH2F * TTSF0_total=Btagg_TT[1];
    TH2F * TTSF5_btagged=Btagg_TT[2];
    TH2F * TTSF5_total=Btagg_TT[3];
    
    //    cout << "Btag efficiency is = "<< pt << " ptBIN " <<ptBIN << "   "<<eta << " etaBIN " << etaBIN <<"  ratio=  " <<TTSF0_btagged->GetBinContent(ptBIN,etaBIN) << "    "<<TTSF0_total->GetBinContent(ptBIN,etaBIN) <<"\n";
    
    
    if (passCSV)
        return  TTSF5_btagged->GetBinContent(ptBIN,etaBIN)*1.0/TTSF5_total->GetBinContent(ptBIN,etaBIN);
    else
        return  TTSF0_btagged->GetBinContent(ptBIN,etaBIN)*1.0/TTSF0_total->GetBinContent(ptBIN,etaBIN);
    
    
}
//###########       bJet Veto   ###########################################################

float FuncFinalBTagSF(bool isData, TH2F ** Btagg_TT, float BJetPtCut, float CSVCut){
    
    
    float EffJet =1;
    float SF=1;
    float P_Data_P_mc=1;
    float FinalBTagSF=1;
    
    if (isData) return 1;
    for (int ijet= 0 ; ijet < nJet ; ijet++){
        
        float HadronFlavor= isData ? 1 : jetHadFlvr->at(ijet);
        
        if (jetPFLooseId->at(ijet) > 0.5 && jetPt->at(ijet) > BJetPtCut && fabs(jetEta->at(ijet)) < 2.4 ){
            
            
            if ( jetCSV2BJetTags->at(ijet) >  CSVCut ){
                //            if ( jetDeepCSVTags_b->at(ijet) >  CSVCut ){
                EffJet= getBtagEfficiency( isData, 1,  jetPt->at(ijet), fabs(jetEta->at(ijet)), Btagg_TT);
                SF= GetBJetSF(isData, jetPt->at(ijet), jetPt->at(ijet), HadronFlavor);
                P_Data_P_mc=SF*EffJet/EffJet;
                
                
            }
            else{
                EffJet= getBtagEfficiency( isData, 0,  jetPt->at(ijet), fabs(jetEta->at(ijet)), Btagg_TT);
                SF=GetBJetSF(isData,jetPt->at(ijet), jetPt->at(ijet), HadronFlavor);
                P_Data_P_mc=(1-SF*EffJet)/(1-EffJet);
                
            }
            FinalBTagSF *=P_Data_P_mc;
        }
        
        //        FinalBTagSF *=P_Data_P_mc; //  Seemd to ve a BUGGGGGGG  May16
    }
    return FinalBTagSF;
}




//###########       bJet multiplicity   ###########################################################
int numBJets( float BJetPtCut, float CSVCut, string JetSys){
    int numBJet=0;
    
    if (JetSys.find("Nominal")!=string::npos){
        for (int ijet= 0 ; ijet < nJet ; ijet++){
            if (jetPFLooseId->at(ijet) > 0.5 && jetPt->at(ijet) > BJetPtCut && fabs(jetEta->at(ijet)) < 2.4  &&
                jetDeepCSVTags_b->at(ijet) >  CSVCut)
                numBJet++;
        }
    }
    else if (JetSys.find("JetTotUp")!=string::npos){
        for (int ijet= 0 ; ijet < nJet ; ijet++){
            if (jetPFLooseId->at(ijet) > 0.5 && jetPtTotUncUp->at(ijet) > BJetPtCut && fabs(jetEta->at(ijet)) < 2.4  &&
                jetDeepCSVTags_b->at(ijet) >  CSVCut)
                numBJet++;
        }
    }
    else if (JetSys.find("JetTotDown")!=string::npos){
        for (int ijet= 0 ; ijet < nJet ; ijet++){
            if (jetPFLooseId->at(ijet) > 0.5 && jetPtTotUncDown->at(ijet) > BJetPtCut && fabs(jetEta->at(ijet)) < 2.4  &&
                jetDeepCSVTags_b->at(ijet) >  CSVCut)
                numBJet++;
        }
    }
    
    
    return numBJet;
}


int leadingCSV (){
    float highestCSV=-10;
    float highestCSV_Id=-10;
    for (int ijet= 0 ; ijet < nJet ; ijet++){
        if (jetPFLooseId->at(ijet) > 0.5 && jetPt->at(ijet) > 20 && fabs(jetEta->at(ijet)) < 2.4){
            if ( jetDeepCSVTags_b->at(ijet) > highestCSV ){
                highestCSV = jetDeepCSVTags_b->at(ijet);
                highestCSV_Id=ijet;
            }
        }
    }
    return highestCSV_Id;
}

int subLeadingCSV (){
    int leadCSV=leadingCSV();
    float highestCSV=-10;
    float highestCSV_Id=-10;
    for (int ijet= 0 ; ijet < nJet ; ijet++){
        if (ijet == leadCSV) continue;
        if (jetPFLooseId->at(ijet) > 0.5 && jetPt->at(ijet) > 20 && fabs(jetEta->at(ijet)) < 2.4){
            if ( jetDeepCSVTags_b->at(ijet) > highestCSV ){
                highestCSV = jetDeepCSVTags_b->at(ijet);
                highestCSV_Id=ijet;
            }
        }
    }
    return highestCSV_Id;
}
int subLeadingCSV (int leadCSV){
    float highestCSV=-10;
    float highestCSV_Id=-10;
    for (int ijet= 0 ; ijet < nJet ; ijet++){
        if (ijet == leadCSV) continue;
        if (jetPFLooseId->at(ijet) > 0.5 && jetPt->at(ijet) > 20 && fabs(jetEta->at(ijet)) < 2.4){
            if ( jetDeepCSVTags_b->at(ijet) > highestCSV ){
                highestCSV = jetDeepCSVTags_b->at(ijet);
                highestCSV_Id=ijet;
            }
        }
    }
    return highestCSV_Id;
}

//###########       Jet multiplicity   ###########################################################
int numJets( float SimpleJetPtCut, string JetSys){
    int numJet=0;
    if (JetSys.find("Nominal")!=string::npos){
        for (int ijet= 0 ; ijet < nJet ; ijet++){
            if (jetPFLooseId->at(ijet) > 0.5 && jetPt->at(ijet) > SimpleJetPtCut && fabs(jetEta->at(ijet)) < 2.4 )
                numJet++;
        }
    }
    else if (JetSys.find("JetTotUp")!=string::npos){
        for (int ijet= 0 ; ijet < nJet ; ijet++){
            if (jetPFLooseId->at(ijet) > 0.5 && jetPtTotUncUp->at(ijet) > SimpleJetPtCut && fabs(jetEta->at(ijet)) < 2.4 )
                numJet++;
        }
    }
    else if (JetSys.find("JetTotDown")!=string::npos){
        for (int ijet= 0 ; ijet < nJet ; ijet++){
            if (jetPFLooseId->at(ijet) > 0.5 && jetPtTotUncDown->at(ijet) > SimpleJetPtCut && fabs(jetEta->at(ijet)) < 2.4 )
                numJet++;
        }
    }
    
    return numJet;
}

//###########       HT   ###########################################################
float getHT( float SimpleJetPtCut, TLorentzVector lep4Mom, TLorentzVector tau4Mom, string JetSys){
    TLorentzVector  Jet;
    float HT=0;
    if (JetSys.find("Nominal")!=string::npos){
        for (int ijet= 0 ; ijet < nJet ; ijet++){
            Jet.SetPtEtaPhiE(jetPt->at(ijet),jetEta->at(ijet),jetPhi->at(ijet),jetEn->at(ijet));
            if (Jet.DeltaR(lep4Mom) < 0.5) continue;
            if (Jet.DeltaR(tau4Mom) < 0.5) continue;
            if (jetPFLooseId->at(ijet) > 0.5 && jetPt->at(ijet) > SimpleJetPtCut && fabs(jetEta->at(ijet)) < 3.0 )
                HT += jetPt->at(ijet);
        }
    }
    else if (JetSys.find("JetTotUp")!=string::npos){
        for (int ijet= 0 ; ijet < nJet ; ijet++){
            Jet.SetPtEtaPhiE(jetPtTotUncUp->at(ijet),jetEta->at(ijet),jetPhi->at(ijet),jetEn->at(ijet));
            if (Jet.DeltaR(lep4Mom) < 0.5) continue;
            if (Jet.DeltaR(tau4Mom) < 0.5) continue;
            if (jetPFLooseId->at(ijet) > 0.5 && jetPtTotUncUp->at(ijet) > SimpleJetPtCut && fabs(jetEta->at(ijet)) < 3.0 )
                HT += jetPtTotUncUp->at(ijet);
        }
    }
    else if (JetSys.find("JetTotDown")!=string::npos){
        for (int ijet= 0 ; ijet < nJet ; ijet++){
            Jet.SetPtEtaPhiE(jetPtTotUncDown->at(ijet),jetEta->at(ijet),jetPhi->at(ijet),jetEn->at(ijet));
            if (Jet.DeltaR(lep4Mom) < 0.5) continue;
            if (Jet.DeltaR(tau4Mom) < 0.5) continue;
            if (jetPFLooseId->at(ijet) > 0.5 && jetPtTotUncDown->at(ijet) > SimpleJetPtCut && fabs(jetEta->at(ijet)) < 3.0 )
                HT += jetPtTotUncDown->at(ijet);
        }
    }
    
    return HT;
}


float getHTInc( float SimpleJetPtCut){
    TLorentzVector  Jet;
    float HT=0;
    for (int ijet= 0 ; ijet < nJet ; ijet++){
        Jet.SetPtEtaPhiE(jetPt->at(ijet),jetEta->at(ijet),jetPhi->at(ijet),jetEn->at(ijet));
        //        if (Jet.DeltaR(lep4Mom) < 0.1) continue;
        //        if (Jet.DeltaR(tau4Mom) < 0.1) continue;
        if (jetPFLooseId->at(ijet) > 0.5 && jetPt->at(ijet) > SimpleJetPtCut && fabs(jetEta->at(ijet)) < 3.0 )
            HT += jetPt->at(ijet);
    }
    return HT;
}
//###########       ST   ###########################################################
float getST( float SimpleJetPtCut, string JetSys){
    float ST=0;
    
    if (JetSys.find("Nominal")!=string::npos){
        for (int ijet= 0 ; ijet < nJet ; ijet++){
            if (jetPFLooseId->at(ijet) > 0.5 && jetPt->at(ijet) > SimpleJetPtCut && fabs(jetEta->at(ijet)) < 3.0 )
                ST += jetPt->at(ijet);
        }
    }
    else if (JetSys.find("JetTotUp")!=string::npos){
        for (int ijet= 0 ; ijet < nJet ; ijet++){
            if (jetPFLooseId->at(ijet) > 0.5 && jetPtTotUncUp->at(ijet) > SimpleJetPtCut && fabs(jetEta->at(ijet)) < 3.0 )
                ST += jetPtTotUncUp->at(ijet);
        }
    }
    else if (JetSys.find("JetTotDown")!=string::npos){
        for (int ijet= 0 ; ijet < nJet ; ijet++){
            if (jetPFLooseId->at(ijet) > 0.5 && jetPtTotUncDown->at(ijet) > SimpleJetPtCut && fabs(jetEta->at(ijet)) < 3.0 )
                ST += jetPtTotUncDown->at(ijet);
        }
    }
    
    return ST;
}

//###########       MHT   ###########################################################
float getMHT( float SimpleJetPtCut, string JetSys){
    float MHT_x=0;
    float MHT_y=0;
    
    if (JetSys.find("Nominal")!=string::npos){
        for (int ijet= 0 ; ijet < nJet ; ijet++){
            if (jetPFLooseId->at(ijet) > 0.5 && jetPt->at(ijet) > SimpleJetPtCut && fabs(jetEta->at(ijet)) < 5.0 )
                MHT_x += jetPt->at(ijet)*cos(jetPhi->at(ijet));
            MHT_y += jetPt->at(ijet)*sin(jetPhi->at(ijet));
        }
    }
    else if (JetSys.find("JetTotUp")!=string::npos){
        for (int ijet= 0 ; ijet < nJet ; ijet++){
            if (jetPFLooseId->at(ijet) > 0.5 && jetPtTotUncUp->at(ijet) > SimpleJetPtCut && fabs(jetEta->at(ijet)) < 5.0 )
                MHT_x += jetPtTotUncUp->at(ijet)*cos(jetPhi->at(ijet));
            MHT_y += jetPtTotUncUp->at(ijet)*sin(jetPhi->at(ijet));
        }
    }
    else if (JetSys.find("JetTotDown")!=string::npos){
        for (int ijet= 0 ; ijet < nJet ; ijet++){
            if (jetPFLooseId->at(ijet) > 0.5 && jetPtTotUncDown->at(ijet) > SimpleJetPtCut && fabs(jetEta->at(ijet)) < 5.0 )
                MHT_x += jetPtTotUncDown->at(ijet)*cos(jetPhi->at(ijet));
            MHT_y += jetPtTotUncDown->at(ijet)*sin(jetPhi->at(ijet));
        }
    }
    return sqrt(MHT_x*MHT_x + MHT_y*MHT_y);
}



TLorentzVector getLeadJet(TLorentzVector lep4Mom, TLorentzVector tau4Mom, string JetSys){
    TLorentzVector leadJet, Jet;
    float MaxJetPt=0;
    int leadJetPtIndex=0;
    if (JetSys.find("Nominal")!=string::npos){
        leadJet.SetPtEtaPhiE(jetPt->at(leadJetPtIndex),jetEta->at(leadJetPtIndex),jetPhi->at(leadJetPtIndex),jetEn->at(leadJetPtIndex));
    }
    else if (JetSys.find("JetTotUp")!=string::npos){
        leadJet.SetPtEtaPhiE(jetPtTotUncUp->at(leadJetPtIndex),jetEta->at(leadJetPtIndex),jetPhi->at(leadJetPtIndex),jetEn->at(leadJetPtIndex));
    }
    else if (JetSys.find("JetTotDown")!=string::npos){
        leadJet.SetPtEtaPhiE(jetPtTotUncDown->at(leadJetPtIndex),jetEta->at(leadJetPtIndex),jetPhi->at(leadJetPtIndex),jetEn->at(leadJetPtIndex));
    }
    return leadJet;
}



//###########       W PDF + alpha s   ###########################################################


float W_PDFAlphaS(float wMass, float sign){
    
    if (wMass < 400) return (1+sign/100.*1.734);
    if (wMass < 600) return (1+sign/100.*1.906);
    if (wMass < 800) return (1+sign/100.*2.279);
    if (wMass < 1000) return (1+sign/100.*2.679);
    if (wMass < 1200) return (1+sign/100.*3.284);
    if (wMass < 1400) return (1+sign/100.* 3.669);
    if (wMass < 1600) return (1+sign/100.* 4.046);
    if (wMass < 1800) return (1+sign/100.* 4.801);
    if (wMass < 2000) return (1+sign/100.* 5.088);
    if (wMass < 2200) return (1+sign/100.* 5.562);
    if (wMass < 2400) return (1+sign/100.* 5.825);
    if (wMass < 2600) return (1+sign/100.* 6.238);
    if (wMass < 2800) return (1+sign/100.* 6.684);
    if (wMass < 3000) return (1+sign/100.* 7.268);
    if (wMass < 3200) return (1+sign/100.* 7.743);
    if (wMass < 3400) return (1+sign/100.* 8.547);
    if (wMass < 3600) return (1+sign/100.* 9.326);
    if (wMass < 3800) return (1+sign/100.* 10.05);
    if (wMass < 4000) return (1+sign/100.* 9.782);
    else return (1+sign/100.* 10.00);
    
}




//bool checkGenRecodR(myGenobject const& Gen1, myGenobject const& Gen2, myobject const& Reco1, myobject const& Reco2) {
//
//    bool check_11_22 = dR(Gen1.eta, Gen1.phi, Reco1.eta, Reco1.phi) < 0.5 && dR(Gen2.eta, Gen2.phi, Reco2.eta, Reco2.phi) < 0.5;
//    bool check_12_21 = dR(Gen1.eta, Gen1.phi, Reco2.eta, Reco2.phi) < 0.5 && dR(Gen2.eta, Gen2.phi, Reco1.eta, Reco1.phi) < 0.5;
//
//    if (check_11_22 || check_12_21)
//        return true;
//    else return false;
//
//}
//

////
////                    gen4Momentum.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
////
////                    if (mcPt->at(igen) > 8 && fabs(mcPID->at(igen)) == 13 && gen4Momentum.DeltaR( Mu4Momentum) < 0.5) cout << "matched reco muon: pdgid= "<<mcPID->at(igen) <<" moder= "<<mcMomPID->at(igen)<< "  mcStatusFlag "<<mcStatusFlag->at(igen)<<"  "<<    (mcStatusFlag->at(igen) >> 0 & 1)<<(mcStatusFlag->at(igen) >> 1 & 1)<<(mcStatusFlag->at(igen) >> 2 & 1)<<(mcStatusFlag->at(igen) >> 3 & 1)<<(mcStatusFlag->at(igen) >> 4 & 1)<<(mcStatusFlag->at(igen) >> 5 & 1)<<(mcStatusFlag->at(igen) >> 6 & 1)<<(mcStatusFlag->at(igen) >> 7 & 1)<<(mcStatusFlag->at(igen) >> 8 & 1)<<"\n";
////
////                        if (mcPt->at(igen) > 8 && fabs(mcPID->at(igen)) == 15 && gen4Momentum.DeltaR( BoostedTau4Momentum) < 0.5) cout << "\t matched reco muon: pdgid= "<<mcPID->at(igen) <<" moder= "<<mcMomPID->at(igen)<<"  mcStatusFlag "<<mcStatusFlag->at(igen)<< "  "<<    (mcStatusFlag->at(igen) >> 0 & 1)<<(mcStatusFlag->at(igen) >> 1 & 1)<<(mcStatusFlag->at(igen) >> 2 & 1)<<(mcStatusFlag->at(igen) >> 3 & 1)<<(mcStatusFlag->at(igen) >> 4 & 1)<<(mcStatusFlag->at(igen) >> 5 & 1)<<(mcStatusFlag->at(igen) >> 6 & 1)<<(mcStatusFlag->at(igen) >> 7 & 1)<<(mcStatusFlag->at(igen) >> 8 & 1)<<"\n";
////
////
////                    }
//



int ZCategory(TLorentzVector tauCandidate) {
    
    for (int igen=0; igen < nMC; igen++){
        TLorentzVector gen4Mom;
        gen4Mom.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
        if (tauCandidate.DeltaR(gen4Mom) > 0.2 ) continue;
        cout<<mcPt->at(igen) <<  "  PID  "<< fabs(mcPID->at(igen)) <<  " flag " <<  mcStatusFlag->at(igen)  <<"  dr= "<<tauCandidate.DeltaR(gen4Mom)<<"\n";
        
        if (mcPt->at(igen) > 8 && fabs(mcPID->at(igen)) == 11 && mcStatusFlag->at(igen) >> 9 & 1) return 1;
        if (mcPt->at(igen) > 8 && fabs(mcPID->at(igen)) == 13 && mcStatusFlag->at(igen) >> 9 & 1) return 2;
        if (mcPt->at(igen) > 8 && fabs(mcPID->at(igen)) == 11 && mcStatusFlag->at(igen) >> 10 & 1) return 3;
        if (mcPt->at(igen) > 8 && fabs(mcPID->at(igen)) == 13 && mcStatusFlag->at(igen) >> 10 & 1) return 4;
    }
    TLorentzVector genTau;
    //    for (int i=0; i < numGenTau  ; i++){
    //        //        cout<<taudaugPt->at(i)<<" "<<taudaugEta->at(i)<<" "<<taudaugPhi->at(i)<<" "<<taudaugMass->at(i)<<"\n";
    //        //        cout<<taudaugMass->at(i)<<"\n";
    //        genTau.SetPtEtaPhiM(taudaugPt->at(i),taudaugEta->at(i),taudaugPhi->at(i),taudaugMass->at(i));
    //        if (tauCandidate.DeltaR(genTau) < 0.2  && taudaugPt->at(i) > 15)
    //            return 5;
    //    }
    //    return 6;
    return 5;
}

//
//    if (genID == 11 && closest.pt() > 8 && closest.statusFlags().isPrompt() ) return 1.0;
//    else if (genID == 13 && closest.pt() > 8 && closest.statusFlags().isPrompt() ) return 2.0;
//    else if (genID == 11 && closest.pt() > 8 && closest.statusFlags().isDirectPromptTauDecayProduct() ) return 3.0;
//    else if (genID == 13 && closest.pt() > 8 && closest.statusFlags().isDirectPromptTauDecayProduct() ) return 4.0;
//    // If closest wasn't E / Mu, we need to rebuild taus and check them
//    else {
//
//    taudaugPt.push_back(vec.Pt());
//    taudaugEta.push_back(vec.Eta());
//    taudaugPhi.push_back(vec.Phi());
//    taudaugMass.push_back(vec.mass());
//
//
//        // Get rebuilt gen taus w/o neutrino energy
//        std::vector<reco::Candidate::LorentzVector> genTaus = buildGenTaus();
//
//        for ( auto vec : genTaus ) {
//            double tmpDR2 = reco::DeltaR( daughter(i)->p4(), vec );
//            //std::cout << "DR: " << tmpDR2 << "   genTauPt: " << vec.Pt() <<std::endl;
//            //std::cout << "DR: " << tmpDR2 << std::endl;
//            if (tmpDR2 < 0.2) {
//                //std::cout << " ~~~~~ Found Gen Tau " << std::endl;
//
//        }
//        //std::cout << " - - - - No Gen Tau " << std::endl;
//        return 6.0;
//    }



//int ZCategory(myevent *m, myobject const& obj1, myobject const& obj2) {
//
//    vector<myGenobject> genTausFromZ;
//    vector<myGenobject> genMuFromZ;
//    vector<myGenobject> genEleFromZ;
//    vector<myGenobject> genLepFromTaus;
//    genTausFromZ.clear();
//    genMuFromZ.clear();
//    genEleFromZ.clear();
//    genLepFromTaus.clear();
//    vector<myGenobject> genPar = m->RecGenParticle;
//    int gen_ditau = 6;
//    bool TherIsZGamma= 0;
//    if (genPar.size() != 0) {
//        for (int a = 0; a < genPar.size(); ++a) {
//            if ((fabs(genPar[a].mod_pdgId) == 23 || fabs(genPar[a].mod_pdgId) == 22) && fabs(genPar[a].pdgId) == 15) genTausFromZ.push_back(genPar[a]);
//            if (genPar[a].pt > 8.0 && (fabs(genPar[a].mod_pdgId) == 23 || fabs(genPar[a].mod_pdgId) == 22) && fabs(genPar[a].pdgId) == 13) genMuFromZ.push_back(genPar[a]);
//            if (genPar[a].pt > 8.0 && (fabs(genPar[a].mod_pdgId) == 23 || fabs(genPar[a].mod_pdgId) == 22) && fabs(genPar[a].pdgId) == 11) genEleFromZ.push_back(genPar[a]);
//            if (genPar[a].pt > 8.0 && fabs(genPar[a].mod_pdgId) == 15 &&  (fabs(genPar[a].Gmod_pdgId) == 15 || fabs(genPar[a].Gmod_pdgId) == 22|| fabs(genPar[a].Gmod_pdgId) == 23) &&(fabs(genPar[a].pdgId) == 11 || fabs(genPar[a].pdgId) == 13)) genLepFromTaus.push_back(genPar[a]);
//            if (fabs(genPar[a].mod_pdgId) == 23 || fabs(genPar[a].mod_pdgId) == 22)  TherIsZGamma=1;
//
////    if(fabs(genPar[a].mod_pdgId) == 15) cout << "-------> genPar[a].pdgId "<<genPar[a].pdgId << "   genPar[a].Gmod_pdgId "<< genPar[a].Gmod_pdgId <<"\n";
//        
//    }
//    }
//    
//
//    
//    if (genMuFromZ.size() == 2 && checkGenRecodR(genMuFromZ[0], genMuFromZ[1], obj1, obj2)) gen_ditau = 1; // THis is ZLL (ZMuMU)
//    
//    else if (genEleFromZ.size() == 2 && checkGenRecodR(genEleFromZ[0], genEleFromZ[1], obj1, obj2)) gen_ditau = 2; // THis is ZLL (ZEE)
//    
//    else if (genTausFromZ.size() == 2 && genLepFromTaus.size() == 1 && checkGenRecodR(genTausFromZ[0], genTausFromZ[1], obj1, obj2)) gen_ditau = 3; //This is ZTT (ZLepTau)
//    
//    else if (genTausFromZ.size() == 2 && genLepFromTaus.size() == 2 && checkGenRecodR(genLepFromTaus[0], genLepFromTaus[1], obj1, obj2)) gen_ditau = 4; //This is ZL (ZTauTau_LepLep)
////    else if (genTausFromZ.size() == 2 && genLepFromTaus.size() == 2 && checkGenRecodR(genTausFromZ[0], genTausFromZ[1], obj1, obj2)) gen_ditau = 4; //This is ZL (ZTauTau_LepLep) BUG Found December 5th
//    else gen_ditau = 5; //This is ZJ (ZTauTau_LepLep)
//    return gen_ditau;
//    // 1 or 2 will be  ZLL
//    // 3 or  will be  ZTT
//    // 4 or  will be  ZL
//    //  5 will be  ZJ
//}
//


struct FidSelection{
    bool emu;
    bool mutau;
    bool etau;
    bool tautau;
    bool emu_fid;
    bool mutau_fid;
    bool etau_fid;
    bool tautau_fid;
};

FidSelection PassFoducial(){

    struct FidSelection fid;
    fid.emu = false;
    fid.mutau = false;
    fid.etau = false;
    fid.tautau = false;
    fid.emu_fid = false;
    fid.mutau_fid = false;
    fid.etau_fid = false;
    fid.tautau_fid = false;
    
        
        TLorentzVector Mu4Momentum,Tau4Momentum, Z4Momentum, Met4Momentum,Ele4Momentum;
        TLorentzVector LeadTau4Momentum,SubTau4Momentum;
        
        //=========================================================================================================
        Met4Momentum.SetPtEtaPhiM(genMET, 0, genMETPhi, 0);
      
        TLorentzVector genTau,genTau2, genMu, genEle, genNuTau, genNuMu, genNuEle;
        vector<TLorentzVector> genTauVec,genTauVec2, genMuVec, genEleVec, genNuTauVec, genNuEleVec, genNuMuVec;
        
        for (int igen=0;igen < nMC; igen++){
            
            
            if ( fabs(mcPID->at(igen)) ==11 && fabs(mcMomPID->at(igen))==15 && fabs(mcGMomPID->at(igen))==25){
                genEle.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
                genEleVec.push_back(genEle);
            }
            if ( fabs(mcPID->at(igen)) ==12 && fabs(mcMomPID->at(igen))==15 && fabs(mcGMomPID->at(igen))==25){
                genNuEle.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
                genNuEleVec.push_back(genNuEle);
            }
            if ( fabs(mcPID->at(igen)) ==13 && fabs(mcMomPID->at(igen))==15 && fabs(mcGMomPID->at(igen))==25){
                genMu.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
                genMuVec.push_back(genMu);
            }
            if ( fabs(mcPID->at(igen)) ==14 && fabs(mcMomPID->at(igen))==15 && fabs(mcGMomPID->at(igen))==25){
                genNuMu.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
                genNuMuVec.push_back(genNuMu);
            }
            if ( fabs(mcPID->at(igen)) ==15 && fabs(mcMomPID->at(igen))==25){
                genTau.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
                genTauVec.push_back(genTau);
            }
            if ( fabs(mcPID->at(igen)) ==15){
                genTau2.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
                genTauVec2.push_back(genTau2);
            }
            if ( fabs(mcPID->at(igen)) ==16 && fabs(mcMomPID->at(igen))==15){
                genNuTau.SetPtEtaPhiM(mcPt->at(igen),mcEta->at(igen),mcPhi->at(igen),mcMass->at(igen));
                genNuTauVec.push_back(genNuTau);
            }
            
        }
        
        if (genTauVec.size() > 1 ) {
                        
        //emu
        if (genMuVec.size() ==1  && genEleVec.size() ==1 ) {
                      
            fid.emu = true;
          
            bool dRcuts =  (genMuVec[0].DeltaR(genEleVec[0]) < 0.8 && genMuVec[0].DeltaR(genEleVec[0]) > 0.1) ;
            bool etacuts = (fabs(genMuVec[0].Eta()) < 2.4 && fabs(genEleVec[0].Eta()) < 2.5) ;
            bool higgsPtCut = Rivet_higgsPt > 250;
            
            bool me_loose = genMuVec[0].Pt() < 52 && genMuVec[0].Pt() > 28 && genEleVec[0].Pt() > 10 && genMET > 30 ;
            bool me_tight = genMuVec[0].Pt() >= 52 && genEleVec[0].Pt() > 10;
            bool em_loose = genEleVec[0].Pt()< 115 && genEleVec[0].Pt()> 38 && genMuVec[0].Pt()  > 10 && genMET > 30 ;
            bool em_tight = genEleVec[0].Pt()>= 115 && genMuVec[0].Pt()  > 10;
        
            
            if ( dRcuts && etacuts && higgsPtCut && (me_loose || me_tight || em_loose || em_tight ))
                fid.emu_fid = true;
        }
        
        //mutau
        else if (genMuVec.size() ==1 &&  genEleVec.size() ==0 ){
            

            fid.mutau = true;
            
            findDr fdMatch0 = FindClosetDr(genTauVec[0],genMuVec);
            findDr fdMatch1 = FindClosetDr(genTauVec[1],genMuVec);
            int tauCandOrder=fdMatch0.dR < fdMatch1.dR ?  1:0;
            findDr fdMatchNu = FindClosetDr(genTauVec[tauCandOrder],genNuTauVec);
            TLorentzVector VisibleTau = genTauVec[tauCandOrder] - genNuTauVec[fdMatchNu.order];

            bool dRcuts=  (genMuVec[0].DeltaR(VisibleTau) < 0.8 && genMuVec[0].DeltaR(VisibleTau) > 0.1) ;
            bool etacuts = (fabs(genMuVec[0].Eta()) < 2.4 && fabs(VisibleTau.Eta()) < 2.3) ;
            bool tauPtcuts =  VisibleTau.Pt() > 30 ;
            bool higgsPtCut = Rivet_higgsPt > 250;
            
            bool looseMu = genMuVec[0].Pt() > 28 && genMuVec[0].Pt() < 52 && genMET > 30 ;
            bool tightMu = genMuVec[0].Pt() >= 52;
            
            if ( dRcuts && etacuts && tauPtcuts && higgsPtCut && (looseMu || tightMu ) )
                fid.mutau_fid = true;

        }
        
        //etau
        else if (genMuVec.size() ==0 &&  genEleVec.size() ==1 ){
        
        fid.etau = true;

            findDr fdMatch0 = FindClosetDr(genTauVec[0],genEleVec);
            findDr fdMatch1 = FindClosetDr(genTauVec[1],genEleVec);
            
            int tauCandOrder=fdMatch0.dR < fdMatch1.dR ?  1:0;
            
            findDr fdMatchNu = FindClosetDr(genTauVec[tauCandOrder],genNuTauVec);
            TLorentzVector VisibleTau = genTauVec[tauCandOrder] - genNuTauVec[fdMatchNu.order];
            
            bool dRcuts=  (genEleVec[0].DeltaR(VisibleTau) < 0.8 && genEleVec[0].DeltaR(VisibleTau) > 0.1) ;
            bool etacuts = (fabs(genEleVec[0].Eta()) < 2.5 && fabs(VisibleTau.Eta()) < 2.3) ;
            bool tauPtcuts =  VisibleTau.Pt() > 30 ;
            bool higgsPtCut = Rivet_higgsPt > 250;

            bool looseEle = genEleVec[0].Pt() > 38 && genEleVec[0].Pt() < 115 && genMET > 30 ;
            bool tightEle = genEleVec[0].Pt() >= 115;

            if ( dRcuts && etacuts && tauPtcuts && higgsPtCut && (looseEle || tightEle ) )
                fid.etau_fid = true;
        }
        else if (genMuVec.size() ==0  && genEleVec.size() ==0 )
        {
            fid.tautau = true;
            findDr fdMatchNu0 = FindClosetDr(genTauVec[0],genNuTauVec);
            findDr fdMatchNu1 = FindClosetDr(genTauVec[1],genNuTauVec);

            TLorentzVector VisibleTau0 = genTauVec[0] - genNuTauVec[fdMatchNu0.order];
            TLorentzVector VisibleTau1 = genTauVec[1] - genNuTauVec[fdMatchNu1.order];

            bool dRcuts=  (VisibleTau0.DeltaR(VisibleTau1) < 0.8 && VisibleTau0.DeltaR(VisibleTau1) > 0.1) ;
            bool etacuts = (fabs(VisibleTau0.Eta()) < 2.5 && fabs(VisibleTau1.Eta()) < 2.3) ;
            bool ptcuts = (fabs(VisibleTau0.Pt()) > 30 && fabs(VisibleTau1.Pt()) > 30) ;
            bool higgsPtCut = Rivet_higgsPt > 250;
            
                        
//            bool tt_ht = AK8LeadJet.Pt() > 100 ;
//            bool tt_met = genHT > 500 && genMET > 120;

            if ( dRcuts && etacuts && ptcuts && higgsPtCut )
                fid.tautau_fid = true;
        }
        }
        return fid;
    }
    
#endif
