#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH1.h"
#include "TH2.h"
#include "TH1F.h"
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




//########################################
// Pileup files
//########################################


TH1F *  HistPUData(){
    TFile * PUData= TFile::Open("data/Data_nPU_new.root");
    TH1F * HistoPUData= (TH1F *) PUData->Get("pileup");
    HistoPUData->Rebin(2);
    HistoPUData->Scale(1.0/HistoPUData->Integral());
    return HistoPUData;
}

TH1F *  HistPUMC(TFile *f_Double){
    //    TFile * PUMC= TFile::Open("../interface/pileup-hists/mcMoriondPU.root"); // Not valid for 2017 yet
    //    TH1F * HistoPUMC= (TH1F *) PUMC->Get("pileup");
    TFile * PUMC= TFile::Open(f_Double->GetName());
    TH1F * HistoPUMC= (TH1F *) PUMC->Get("hPUTrue");
    HistoPUMC->Scale(1.0/HistoPUMC->Integral());
    //        cout << "HistoPUMC integral= "<<HistoPUMC->Integral()<<"\n";
    return HistoPUMC;
}


//########################################
// Muon Id, Iso, Trigger and Tracker Eff files
//########################################
TH2F**  FuncHistMuTrigger(){
    
    TFile * MuCorrTrg_BCDEF= TFile::Open(("../interface/MuSF/EfficienciesAndSF_RunBtoF_Nov17Nov2017.root"));
    //    TH1F * HistoMuTrg_BCDEF= (TH1F *) MuCorrTrg_BCDEF->Get("Mu50_EtaBins/eta_ratio");
    //    TH1F * HistoMuTrg_BCDEF= (TH1F *) MuCorrTrg_BCDEF->Get("Mu50_EtaBins/pt_abseta_ratio");
    TH2F * HistoMuTrg_BCDEF= (TH2F *) MuCorrTrg_BCDEF->Get("IsoMu27_PtEtaBins/pt_abseta_ratio");
    
    static TH2F* HistoMuTrg[2]={HistoMuTrg_BCDEF};
    return HistoMuTrg;
}


TGraphAsymmErrors * FuncHistMuTrack(){
    
    TFile * MuCorrTrack= TFile::Open(("../interface/pileup-hists/Tracking_EfficienciesAndSF_BCDEFGH.root"));
    TGraphAsymmErrors * HistoMuTrack= (TGraphAsymmErrors *) MuCorrTrack->Get("ratio_eff_eta3_dr030e030_corr");
    
    return HistoMuTrack;
}


TH2F**  FuncHistMuId(){
    
    
    
    TFile * MuCorrId_BCDEF= TFile::Open(("../interface/pileup-hists/RunBCDEF_SF_ID.root"));
    TH2F * HistoMuId_BCDEF= (TH2F *) MuCorrId_BCDEF->Get("NUM_MediumID_DEN_genTracks_pt_abseta");
    
    static TH2F* HistoMuId[1]={HistoMuId_BCDEF};
    
    return  HistoMuId;
}


TH2F**  FuncHistMuIso(){
    
    TFile * MuCorrIso_BCDEF= TFile::Open(("../interface/pileup-hists/RunBCDEF_SF_ISO.root"));
    TH2F * HistoMuIso_BCDEF= (TH2F *) MuCorrIso_BCDEF->Get("NUM_LooseRelIso_DEN_MediumID_pt_abseta");
    
    static  TH2F* HistoMuIso[1]={HistoMuIso_BCDEF};
    
    return HistoMuIso;
}



//########################################
// Ele Id, Iso, Trigger and Tracker Eff files
//########################################



TH2F** FuncHistEleReco(){
    
    TFile * eleF= TFile::Open(("../interface/EleSF/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root"));
    TH2F * HistoEle= (TH2F *) eleF->Get("EGamma_SF2D");
    
    static  TH2F* HistoElReco[1]={HistoEle};
    
    return HistoElReco;
    
    
    
}

TH2F** FuncHistEleId(){
    
    TFile * eleIdF= TFile::Open(("../interface/EleSF/2017_ElectronMVA80.root"));
    TH2F * eleIdHisto= (TH2F *) eleIdF->Get("EGamma_SF2D");
    
    static  TH2F* HistoElId[1]={eleIdHisto};
    
    return HistoElId;
    
    
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
//        bool TauIdIso =  taupfTausDiscriminationByDecayModeFinding->at(itau) > 0.5 && tauByLooseMuonRejection3->at(itau) > 0 && tauByMVA6LooseElectronRejection->at(itau) > 0 && tauByLooseIsolationMVArun2v1DBoldDMwLT->at(itau) > 0;
//
//        if (!TauIdIso) continue;
//        numTau++;
//    }
//    return numTau;
//}



//###########       Lepton  Veto   ###########################################################

int getNumElectron(){
    
    
    //            https://twiki.cern.ch/twiki/bin/view/CMS/MultivariateElectronIdentificationRun2#Recommended_MVA_recipes_for_2016
    int numElectron=0;
    for  (int jele=0 ; jele < nEle; jele++){
        
        if ( elePt->at(jele) < 15 || fabs(eleEta->at(jele)) > 2.5) continue;
        
        bool eleMVAIdExtra= false;
        if (fabs (eleSCEta->at(jele)) <= 0.8 && eleIDMVAIso->at(jele) >   -0.83  ) eleMVAIdExtra= true;
        else if (fabs (eleSCEta->at(jele)) >  0.8 &&fabs (eleSCEta->at(jele)) <=  1.5 && eleIDMVAIso->at(jele) >   -0.77  ) eleMVAIdExtra= true;
        else if ( fabs (eleSCEta->at(jele)) >=  1.5 && eleIDMVAIso->at(jele) >  -0.69  ) eleMVAIdExtra= true;
        else eleMVAIdExtra= false;
        
        
        if (eleMVAIdExtra)
            numElectron++;
    }
    return numElectron;
    
}

int getNumMuon(){
    
    int numMuon=0;
    for  (int jmu=0 ; jmu < nMu; jmu++){
        
        if ( muPt->at(jmu) < 15 || fabs(muEta->at(jmu)) > 2.4) continue;
        
        float IsoMu=muPFChIso->at(jmu)/muPt->at(jmu);
        if ( (muPFNeuIso->at(jmu) + muPFPhoIso->at(jmu) - 0.5* muPFPUIso->at(jmu) )  > 0.0)
            IsoMu= ( muPFChIso->at(jmu) + muPFNeuIso->at(jmu) + muPFPhoIso->at(jmu) - 0.5* muPFPUIso->at(jmu))/muPt->at(jmu);
        
        bool MuId=( (muIDbit->at(jmu) >> 2 & 1)  && fabs(muD0->at(jmu)) < 0.045 && fabs(muDz->at(jmu)) < 0.2);
        bool MuIso = IsoMu < 0.15;
        
        
        if (MuId && MuIso)
            numMuon++;
    }
    return numMuon;
}

//###########       electron  correction factor   ###########################################################

float getElectronCor(TH2F * HistoEleMVAIdIso90){
    
    float ElectronCor=1;
    for  (int jele=0 ; jele < nEle; jele++){
        
        if ( elePt->at(jele) < 15 || fabs(eleEta->at(jele)) > 2.5) continue;
        
        bool eleMVAIdExtra= false;
        if (fabs (eleSCEta->at(jele)) <= 0.8 && eleIDMVAIso->at(jele) >   -0.83  ) eleMVAIdExtra= true;
        else if (fabs (eleSCEta->at(jele)) >  0.8 &&fabs (eleSCEta->at(jele)) <=  1.5 && eleIDMVAIso->at(jele) >   -0.77  ) eleMVAIdExtra= true;
        else if ( fabs (eleSCEta->at(jele)) >=  1.5 && eleIDMVAIso->at(jele) >  -0.69  ) eleMVAIdExtra= true;
        else eleMVAIdExtra= false;
        
        
        if (eleMVAIdExtra)
            ElectronCor=getCorrFactorMVA90WPElectron94X(isData,  elePt->at(jele),eleSCEta->at(jele),    HistoEleMVAIdIso90 );
        
        break;
    }
    return ElectronCor;
}

//###########       Z boson Veto   ###########################################################
float MuMass= 0.10565837;
float eleMass= 0.000511;

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
//    matcdedRecoTau.push_back(tauByIsolationMVArun2v1DBoldDMwLTraw->at(index));
//    matcdedRecoTau.push_back(tauByIsolationMVArun2v2DBoldDMwLTraw->at(index));
//    matcdedRecoTau.push_back(tauPt->at(index));
//    matcdedRecoTau.push_back(tauEta->at(index));
//    matcdedRecoTau.push_back(tauCombinedIsolationDeltaBetaCorrRaw3Hits->at(index));
//
//    return matcdedRecoTau;
//}



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
        if (mcPID->at(igen) == 6 && mcStatus->at(igen) ==62) GenTopPt=mcPt->at(igen) ;
        if (mcPID->at(igen) == -6 && mcStatus->at(igen) ==62) GenAntiTopPt=mcPt->at(igen);
        
        
        
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
int numBJets( float BJetPtCut, float CSVCut){
    int numBJet=0;
    for (int ijet= 0 ; ijet < nJet ; ijet++){
        if (jetPFLooseId->at(ijet) > 0.5 && jetPt->at(ijet) > BJetPtCut && fabs(jetEta->at(ijet)) < 2.4  && jetCSV2BJetTags->at(ijet) >  CSVCut)
            numBJet++;
    }
    return numBJet;
}

//###########       Jet multiplicity   ###########################################################
int numJets( float SimpleJetPtCut){
    int numJet=0;
    for (int ijet= 0 ; ijet < nJet ; ijet++){
        if (jetPFLooseId->at(ijet) > 0.5 && jetPt->at(ijet) > SimpleJetPtCut && fabs(jetEta->at(ijet)) < 2.4 )
            numJet++;
    }
    return numJet;
}

//###########       HT   ###########################################################
float getHT( float SimpleJetPtCut, TLorentzVector lep4Mom, TLorentzVector tau4Mom){
    TLorentzVector  Jet;
    float HT=0;
    for (int ijet= 0 ; ijet < nJet ; ijet++){
        Jet.SetPtEtaPhiE(jetPt->at(ijet),jetEta->at(ijet),jetPhi->at(ijet),jetEn->at(ijet));
        if (Jet.DeltaR(lep4Mom) < 0.1) continue;
        if (Jet.DeltaR(tau4Mom) < 0.1) continue;
        if (jetPFLooseId->at(ijet) > 0.5 && jetPt->at(ijet) > SimpleJetPtCut && fabs(jetEta->at(ijet)) < 3.0 )
            HT += jetPt->at(ijet);
    }
    return HT;
}

//###########       ST   ###########################################################
float getST( float SimpleJetPtCut){
    float ST=0;
    for (int ijet= 0 ; ijet < nJet ; ijet++){
        if (jetPFLooseId->at(ijet) > 0.5 && jetPt->at(ijet) > SimpleJetPtCut && fabs(jetEta->at(ijet)) < 3.0 )
            ST += jetPt->at(ijet);
    }
    return ST;
}


TLorentzVector getLeadJet(TLorentzVector lep4Mom, TLorentzVector tau4Mom){
    TLorentzVector leadJet, Jet;
    float MaxJetPt=0;
    int leadJetPtIndex=0;
    for (int ijet= 0 ; ijet < nJet ; ijet++){
        Jet.SetPtEtaPhiE(jetPt->at(ijet),jetEta->at(ijet),jetPhi->at(ijet),jetEn->at(ijet));
        if (Jet.DeltaR(lep4Mom) < 0.1) continue;
        if (Jet.DeltaR(tau4Mom) < 0.1) continue;
        if (jetPFLooseId->at(ijet) > 0.5 && fabs(jetEta->at(ijet)) < 3.0  && jetPt->at(ijet) > MaxJetPt ){
            MaxJetPt=jetPt->at(ijet);
            leadJetPtIndex=ijet;
        }
    }
    leadJet.SetPtEtaPhiE(jetPt->at(leadJetPtIndex),jetEta->at(leadJetPtIndex),jetPhi->at(leadJetPtIndex),jetEn->at(leadJetPtIndex));
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


