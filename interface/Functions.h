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






TTree *  Xttree( TFile * f_Double, string channel){
    
    TTree *Run_Tree = (TTree*) f_Double->Get(channel.c_str());
    
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(6);
    
    
    //       Run_Tree->SetBranchAddress("run", &run, &b_run);
    //       Run_Tree->SetBranchAddress("event", &event, &b_event);
    //       Run_Tree->SetBranchAddress("lumis", &lumis, &b_lumis);
    //       Run_Tree->SetBranchAddress("isData", &isData, &b_isData);
    //       Run_Tree->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
    //       Run_Tree->SetBranchAddress("nGoodVtx", &nGoodVtx, &b_nGoodVtx);
    //       Run_Tree->SetBranchAddress("isPVGood", &isPVGood, &b_isPVGood);
    //       Run_Tree->SetBranchAddress("vtx", &vtx, &b_vtx);
    //       Run_Tree->SetBranchAddress("vty", &vty, &b_vty);
    //       Run_Tree->SetBranchAddress("vtz", &vtz, &b_vtz);
    //       Run_Tree->SetBranchAddress("rho", &rho, &b_rho);
    //       Run_Tree->SetBranchAddress("rhoCentral", &rhoCentral, &b_rhoCentral);
           Run_Tree->SetBranchAddress("L1ECALPrefire", &L1ECALPrefire, &b_L1ECALPrefire);
           Run_Tree->SetBranchAddress("L1ECALPrefireUp", &L1ECALPrefireUp, &b_L1ECALPrefireUp);
           Run_Tree->SetBranchAddress("L1ECALPrefireDown", &L1ECALPrefireDown, &b_L1ECALPrefireDown);
    //       Run_Tree->SetBranchAddress("HLTEleMuX", &HLTEleMuX, &b_HLTEleMuX);
    //       Run_Tree->SetBranchAddress("HLTPho", &HLTPho, &b_HLTPho);
    //       Run_Tree->SetBranchAddress("HLTPhoRejectedByPS", &HLTPhoRejectedByPS, &b_HLTPhoRejectedByPS);
    //       Run_Tree->SetBranchAddress("HLTJet", &HLTJet, &b_HLTJet);
    //       Run_Tree->SetBranchAddress("HLTEleMuXIsPrescaled", &HLTEleMuXIsPrescaled, &b_HLTEleMuXIsPrescaled);
    //       Run_Tree->SetBranchAddress("HLTPhoIsPrescaled", &HLTPhoIsPrescaled, &b_HLTPhoIsPrescaled);
    //       Run_Tree->SetBranchAddress("HLTJetIsPrescaled", &HLTJetIsPrescaled, &b_HLTJetIsPrescaled);
    //       Run_Tree->SetBranchAddress("pdf", &pdf, &b_pdf);
    //       Run_Tree->SetBranchAddress("pthat", &pthat, &b_pthat);
    //       Run_Tree->SetBranchAddress("processID", &processID, &b_processID);
    //       Run_Tree->SetBranchAddress("genWeight", &genWeight, &b_genWeight);
    //       Run_Tree->SetBranchAddress("genHT", &genHT, &b_genHT);
    //       Run_Tree->SetBranchAddress("genPho1", &genPho1, &b_genPho1);
    //       Run_Tree->SetBranchAddress("genPho2", &genPho2, &b_genPho2);
    //       Run_Tree->SetBranchAddress("EventTag", &EventTag, &b_EventTag);
    //       Run_Tree->SetBranchAddress("nPUInfo", &nPUInfo, &b_nPUInfo);
    //       Run_Tree->SetBranchAddress("nPU", &nPU, &b_nPU);
    //       Run_Tree->SetBranchAddress("puBX", &puBX, &b_puBX);
    //       Run_Tree->SetBranchAddress("puTrue", &puTrue, &b_puTrue);
    //       Run_Tree->SetBranchAddress("nLHE", &nLHE, &b_nLHE);
    //       Run_Tree->SetBranchAddress("lhePID", &lhePID, &b_lhePID);
    //       Run_Tree->SetBranchAddress("lhePx", &lhePx, &b_lhePx);
    //       Run_Tree->SetBranchAddress("lhePy", &lhePy, &b_lhePy);
    //       Run_Tree->SetBranchAddress("lhePz", &lhePz, &b_lhePz);
    //       Run_Tree->SetBranchAddress("lheE", &lheE, &b_lheE);
    //       Run_Tree->SetBranchAddress("nMC", &nMC, &b_nMC);
    //       Run_Tree->SetBranchAddress("mcPID", &mcPID, &b_mcPID);
    //       Run_Tree->SetBranchAddress("mcVtx", &mcVtx, &b_mcVtx);
    //       Run_Tree->SetBranchAddress("mcVty", &mcVty, &b_mcVty);
    //       Run_Tree->SetBranchAddress("mcVtz", &mcVtz, &b_mcVtz);
    //       Run_Tree->SetBranchAddress("mcPt", &mcPt, &b_mcPt);
    //       Run_Tree->SetBranchAddress("mcMass", &mcMass, &b_mcMass);
    //       Run_Tree->SetBranchAddress("mcEta", &mcEta, &b_mcEta);
    //       Run_Tree->SetBranchAddress("mcPhi", &mcPhi, &b_mcPhi);
    //       Run_Tree->SetBranchAddress("mcE", &mcE, &b_mcE);
    //       Run_Tree->SetBranchAddress("mcEt", &mcEt, &b_mcEt);
    //       Run_Tree->SetBranchAddress("mcGMomPID", &mcGMomPID, &b_mcGMomPID);
    //       Run_Tree->SetBranchAddress("mcMomPID", &mcMomPID, &b_mcMomPID);
    //       Run_Tree->SetBranchAddress("mcMomPt", &mcMomPt, &b_mcMomPt);
    //       Run_Tree->SetBranchAddress("mcMomMass", &mcMomMass, &b_mcMomMass);
    //       Run_Tree->SetBranchAddress("mcMomEta", &mcMomEta, &b_mcMomEta);
    //       Run_Tree->SetBranchAddress("mcMomPhi", &mcMomPhi, &b_mcMomPhi);
    //       Run_Tree->SetBranchAddress("mcStatusFlag", &mcStatusFlag, &b_mcStatusFlag);
    //       Run_Tree->SetBranchAddress("mcParentage", &mcParentage, &b_mcParentage);
    //       Run_Tree->SetBranchAddress("mcStatus", &mcStatus, &b_mcStatus);
    //       Run_Tree->SetBranchAddress("mcCalIsoDR03", &mcCalIsoDR03, &b_mcCalIsoDR03);
    //       Run_Tree->SetBranchAddress("mcTrkIsoDR03", &mcTrkIsoDR03, &b_mcTrkIsoDR03);
    //       Run_Tree->SetBranchAddress("mcCalIsoDR04", &mcCalIsoDR04, &b_mcCalIsoDR04);
    //       Run_Tree->SetBranchAddress("mcTrkIsoDR04", &mcTrkIsoDR04, &b_mcTrkIsoDR04);
    //       Run_Tree->SetBranchAddress("genMET", &genMET, &b_genMET);
    //       Run_Tree->SetBranchAddress("genMETPhi", &genMETPhi, &b_genMETPhi);
    //       Run_Tree->SetBranchAddress("metFilters", &metFilters, &b_metFilters);
    //       Run_Tree->SetBranchAddress("pfMET", &pfMET, &b_pfMET);
    //       Run_Tree->SetBranchAddress("pfMETPhi", &pfMETPhi, &b_pfMETPhi);
    //       Run_Tree->SetBranchAddress("recoil", &recoil, &b_recoil);
    //       Run_Tree->SetBranchAddress("pfMetNoRecoil", &pfMetNoRecoil, &b_pfMetNoRecoil);
    //       Run_Tree->SetBranchAddress("pfMetPhiNoRecoil", &pfMetPhiNoRecoil, &b_pfMetPhiNoRecoil);
    //       Run_Tree->SetBranchAddress("met_px", &met_px, &b_met_px);
    //       Run_Tree->SetBranchAddress("met_py", &met_py, &b_met_py);
    //       Run_Tree->SetBranchAddress("metcov00", &metcov00, &b_metcov00);
    //       Run_Tree->SetBranchAddress("metcov01", &metcov01, &b_metcov01);
    //       Run_Tree->SetBranchAddress("metcov10", &metcov10, &b_metcov10);
    //       Run_Tree->SetBranchAddress("metcov11", &metcov11, &b_metcov11);
    //       Run_Tree->SetBranchAddress("pfMET_T1JESUp", &pfMET_T1JESUp, &b_pfMET_T1JESUp);
    //       Run_Tree->SetBranchAddress("pfMET_T1JESDo", &pfMET_T1JESDo, &b_pfMET_T1JESDo);
    //       Run_Tree->SetBranchAddress("pfMET_T1UESUp", &pfMET_T1UESUp, &b_pfMET_T1UESUp);
    //       Run_Tree->SetBranchAddress("pfMET_T1UESDo", &pfMET_T1UESDo, &b_pfMET_T1UESDo);
    //       Run_Tree->SetBranchAddress("pfMETPhi_T1JESUp", &pfMETPhi_T1JESUp, &b_pfMETPhi_T1JESUp);
    //       Run_Tree->SetBranchAddress("pfMETPhi_T1JESDo", &pfMETPhi_T1JESDo, &b_pfMETPhi_T1JESDo);
    //       Run_Tree->SetBranchAddress("pfMETPhi_T1UESUp", &pfMETPhi_T1UESUp, &b_pfMETPhi_T1UESUp);
    //       Run_Tree->SetBranchAddress("pfMETPhi_T1UESDo", &pfMETPhi_T1UESDo, &b_pfMETPhi_T1UESDo);
    //       Run_Tree->SetBranchAddress("met_JESUp", &met_JESUp, &b_met_JESUp);
    //       Run_Tree->SetBranchAddress("met_JESDown", &met_JESDown, &b_met_JESDown);
    //       Run_Tree->SetBranchAddress("met_UESUp", &met_UESUp, &b_met_UESUp);
    //       Run_Tree->SetBranchAddress("met_UESDown", &met_UESDown, &b_met_UESDown);
    //       Run_Tree->SetBranchAddress("metphi_JESUp", &metphi_JESUp, &b_metphi_JESUp);
    //       Run_Tree->SetBranchAddress("metphi_JESDown", &metphi_JESDown, &b_metphi_JESDown);
    //       Run_Tree->SetBranchAddress("metphi_UESUp", &metphi_UESUp, &b_metphi_UESUp);
    //       Run_Tree->SetBranchAddress("metphi_UESDown", &metphi_UESDown, &b_metphi_UESDown);
    Run_Tree->SetBranchAddress("pfmetcorr_ex_UESUp", &pfmetcorr_ex_UESUp, &b_pfmetcorr_ex_UESUp);
    Run_Tree->SetBranchAddress("pfmetcorr_ey_UESUp", &pfmetcorr_ey_UESUp, &b_pfmetcorr_ey_UESUp);
    Run_Tree->SetBranchAddress("pfmetcorr_ex_UESDown", &pfmetcorr_ex_UESDown, &b_pfmetcorr_ex_UESDown);
    Run_Tree->SetBranchAddress("pfmetcorr_ey_UESDown", &pfmetcorr_ey_UESDown, &b_pfmetcorr_ey_UESDown);
    Run_Tree->SetBranchAddress("pfmetcorr_ex_JESUp", &pfmetcorr_ex_JESUp, &b_pfmetcorr_ex_JESUp);
    Run_Tree->SetBranchAddress("pfmetcorr_ey_JESUp", &pfmetcorr_ey_JESUp, &b_pfmetcorr_ey_JESUp);
    Run_Tree->SetBranchAddress("pfmetcorr_ex_JESDown", &pfmetcorr_ex_JESDown, &b_pfmetcorr_ex_JESDown);
    Run_Tree->SetBranchAddress("pfmetcorr_ey_JESDown", &pfmetcorr_ey_JESDown, &b_pfmetcorr_ey_JESDown);
    //       Run_Tree->SetBranchAddress("nEle", &nEle, &b_nEle);
    //       Run_Tree->SetBranchAddress("eleCharge", &eleCharge, &b_eleCharge);
    //       Run_Tree->SetBranchAddress("eleChargeConsistent", &eleChargeConsistent, &b_eleChargeConsistent);
    //       Run_Tree->SetBranchAddress("eleEn", &eleEn, &b_eleEn);
    //       Run_Tree->SetBranchAddress("eleSCEn", &eleSCEn, &b_eleSCEn);
    //       Run_Tree->SetBranchAddress("eleEcalEn", &eleEcalEn, &b_eleEcalEn);
    //       Run_Tree->SetBranchAddress("eleESEnP1", &eleESEnP1, &b_eleESEnP1);
    //       Run_Tree->SetBranchAddress("eleESEnP2", &eleESEnP2, &b_eleESEnP2);
    //       Run_Tree->SetBranchAddress("eleD0", &eleD0, &b_eleD0);
    //       Run_Tree->SetBranchAddress("eleDz", &eleDz, &b_eleDz);
    //       Run_Tree->SetBranchAddress("eleSIP", &eleSIP, &b_eleSIP);
    //       Run_Tree->SetBranchAddress("elePt", &elePt, &b_elePt);
    //       Run_Tree->SetBranchAddress("elePtError", &elePtError, &b_elePtError);
    //       Run_Tree->SetBranchAddress("eleEta", &eleEta, &b_eleEta);
    //       Run_Tree->SetBranchAddress("elePhi", &elePhi, &b_elePhi);
    //       Run_Tree->SetBranchAddress("eleR9", &eleR9, &b_eleR9);
    //       Run_Tree->SetBranchAddress("eleCalibPt", &eleCalibPt, &b_eleCalibPt);
    //       Run_Tree->SetBranchAddress("eleCalibEn", &eleCalibEn, &b_eleCalibEn);
    //       Run_Tree->SetBranchAddress("eleSCEta", &eleSCEta, &b_eleSCEta);
    //       Run_Tree->SetBranchAddress("eleSCPhi", &eleSCPhi, &b_eleSCPhi);
    //       Run_Tree->SetBranchAddress("eleSCRawEn", &eleSCRawEn, &b_eleSCRawEn);
    //       Run_Tree->SetBranchAddress("eleSCEtaWidth", &eleSCEtaWidth, &b_eleSCEtaWidth);
    //       Run_Tree->SetBranchAddress("eleSCPhiWidth", &eleSCPhiWidth, &b_eleSCPhiWidth);
    //       Run_Tree->SetBranchAddress("eleHoverE", &eleHoverE, &b_eleHoverE);
    //       Run_Tree->SetBranchAddress("eleEoverP", &eleEoverP, &b_eleEoverP);
    //       Run_Tree->SetBranchAddress("eleEoverPout", &eleEoverPout, &b_eleEoverPout);
    //       Run_Tree->SetBranchAddress("eleEoverPInv", &eleEoverPInv, &b_eleEoverPInv);
    //       Run_Tree->SetBranchAddress("eleBrem", &eleBrem, &b_eleBrem);
    //       Run_Tree->SetBranchAddress("eledEtaAtVtx", &eledEtaAtVtx, &b_eledEtaAtVtx);
    //       Run_Tree->SetBranchAddress("eledPhiAtVtx", &eledPhiAtVtx, &b_eledPhiAtVtx);
    //       Run_Tree->SetBranchAddress("eleSigmaIEtaIEtaFull5x5", &eleSigmaIEtaIEtaFull5x5, &b_eleSigmaIEtaIEtaFull5x5);
    //       Run_Tree->SetBranchAddress("eleSigmaIPhiIPhiFull5x5", &eleSigmaIPhiIPhiFull5x5, &b_eleSigmaIPhiIPhiFull5x5);
    //       Run_Tree->SetBranchAddress("eleConvVeto", &eleConvVeto, &b_eleConvVeto);
    //       Run_Tree->SetBranchAddress("eleMissHits", &eleMissHits, &b_eleMissHits);
    //       Run_Tree->SetBranchAddress("eleESEffSigmaRR", &eleESEffSigmaRR, &b_eleESEffSigmaRR);
    //       Run_Tree->SetBranchAddress("elePFChIso", &elePFChIso, &b_elePFChIso);
    //       Run_Tree->SetBranchAddress("elePFPhoIso", &elePFPhoIso, &b_elePFPhoIso);
    //       Run_Tree->SetBranchAddress("elePFNeuIso", &elePFNeuIso, &b_elePFNeuIso);
    //       Run_Tree->SetBranchAddress("elePFPUIso", &elePFPUIso, &b_elePFPUIso);
    //       Run_Tree->SetBranchAddress("elePFClusEcalIso", &elePFClusEcalIso, &b_elePFClusEcalIso);
    //       Run_Tree->SetBranchAddress("elePFClusHcalIso", &elePFClusHcalIso, &b_elePFClusHcalIso);
    //       Run_Tree->SetBranchAddress("eleIDMVAIso", &eleIDMVAIso, &b_eleIDMVAIso);
    //       Run_Tree->SetBranchAddress("eleIDMVANoIso", &eleIDMVANoIso, &b_eleIDMVANoIso);
    //       Run_Tree->SetBranchAddress("eleR9Full5x5", &eleR9Full5x5, &b_eleR9Full5x5);
    //       Run_Tree->SetBranchAddress("eleEcalDrivenSeed", &eleEcalDrivenSeed, &b_eleEcalDrivenSeed);
    //       Run_Tree->SetBranchAddress("eleTrkdxy", &eleTrkdxy, &b_eleTrkdxy);
    //       Run_Tree->SetBranchAddress("eleKFHits", &eleKFHits, &b_eleKFHits);
    //       Run_Tree->SetBranchAddress("eleKFChi2", &eleKFChi2, &b_eleKFChi2);
    //       Run_Tree->SetBranchAddress("eleGSFChi2", &eleGSFChi2, &b_eleGSFChi2);
    //       Run_Tree->SetBranchAddress("eleGSFPt", &eleGSFPt, &b_eleGSFPt);
    //       Run_Tree->SetBranchAddress("eleGSFEta", &eleGSFEta, &b_eleGSFEta);
    //       Run_Tree->SetBranchAddress("eleGSFPhi", &eleGSFPhi, &b_eleGSFPhi);
    //       Run_Tree->SetBranchAddress("eleGSFCharge", &eleGSFCharge, &b_eleGSFCharge);
    ////       Run_Tree->SetBranchAddress("eleGSFHits", &eleGSFHits, &b_eleGSFHits);
    ////       Run_Tree->SetBranchAddress("eleGSFMissHits", &eleGSFMissHits, &b_eleGSFMissHits);
    ////       Run_Tree->SetBranchAddress("eleGSFNHitsMax", &eleGSFNHitsMax, &b_eleGSFNHitsMax);
    ////       Run_Tree->SetBranchAddress("eleGSFVtxProb", &eleGSFVtxProb, &b_eleGSFVtxProb);
    ////       Run_Tree->SetBranchAddress("eleGSFlxyPV", &eleGSFlxyPV, &b_eleGSFlxyPV);
    ////       Run_Tree->SetBranchAddress("eleGSFlxyBS", &eleGSFlxyBS, &b_eleGSFlxyBS);
    //       Run_Tree->SetBranchAddress("eleFiredSingleTrgs", &eleFiredSingleTrgs, &b_eleFiredSingleTrgs);
    //       Run_Tree->SetBranchAddress("eleFiredDoubleTrgs", &eleFiredDoubleTrgs, &b_eleFiredDoubleTrgs);
    //       Run_Tree->SetBranchAddress("eleFiredL1Trgs", &eleFiredL1Trgs, &b_eleFiredL1Trgs);
    //       Run_Tree->SetBranchAddress("eleIDbit", &eleIDbit, &b_eleIDbit);
    //       Run_Tree->SetBranchAddress("eleScale_stat_up", &eleScale_stat_up, &b_eleScale_stat_up);
    //       Run_Tree->SetBranchAddress("eleScale_stat_dn", &eleScale_stat_dn, &b_eleScale_stat_dn);
    //       Run_Tree->SetBranchAddress("eleScale_syst_up", &eleScale_syst_up, &b_eleScale_syst_up);
    //       Run_Tree->SetBranchAddress("eleScale_syst_dn", &eleScale_syst_dn, &b_eleScale_syst_dn);
    //       Run_Tree->SetBranchAddress("eleScale_gain_up", &eleScale_gain_up, &b_eleScale_gain_up);
    //       Run_Tree->SetBranchAddress("eleScale_gain_dn", &eleScale_gain_dn, &b_eleScale_gain_dn);
    //       Run_Tree->SetBranchAddress("eleResol_rho_up", &eleResol_rho_up, &b_eleResol_rho_up);
    //       Run_Tree->SetBranchAddress("eleResol_rho_dn", &eleResol_rho_dn, &b_eleResol_rho_dn);
    //       Run_Tree->SetBranchAddress("eleResol_phi_up", &eleResol_phi_up, &b_eleResol_phi_up);
    //       Run_Tree->SetBranchAddress("eleResol_phi_dn", &eleResol_phi_dn, &b_eleResol_phi_dn);
    //       Run_Tree->SetBranchAddress("nMu", &nMu, &b_nMu);
    //       Run_Tree->SetBranchAddress("muPt", &muPt, &b_muPt);
    //       Run_Tree->SetBranchAddress("muEn", &muEn, &b_muEn);
    //       Run_Tree->SetBranchAddress("muEta", &muEta, &b_muEta);
    //       Run_Tree->SetBranchAddress("muPhi", &muPhi, &b_muPhi);
    //       Run_Tree->SetBranchAddress("muCharge", &muCharge, &b_muCharge);
    //       Run_Tree->SetBranchAddress("muType", &muType, &b_muType);
    //       Run_Tree->SetBranchAddress("muIDbit", &muIDbit, &b_muIDbit);
    //       Run_Tree->SetBranchAddress("muD0", &muD0, &b_muD0);
    //       Run_Tree->SetBranchAddress("muDz", &muDz, &b_muDz);
    //       Run_Tree->SetBranchAddress("muSIP", &muSIP, &b_muSIP);
    //       Run_Tree->SetBranchAddress("muChi2NDF", &muChi2NDF, &b_muChi2NDF);
    //       Run_Tree->SetBranchAddress("muInnerD0", &muInnerD0, &b_muInnerD0);
    //       Run_Tree->SetBranchAddress("muInnerDz", &muInnerDz, &b_muInnerDz);
    //       Run_Tree->SetBranchAddress("muTrkLayers", &muTrkLayers, &b_muTrkLayers);
    //       Run_Tree->SetBranchAddress("muPixelLayers", &muPixelLayers, &b_muPixelLayers);
    //       Run_Tree->SetBranchAddress("muPixelHits", &muPixelHits, &b_muPixelHits);
    //       Run_Tree->SetBranchAddress("muMuonHits", &muMuonHits, &b_muMuonHits);
    //       Run_Tree->SetBranchAddress("muStations", &muStations, &b_muStations);
    //       Run_Tree->SetBranchAddress("muMatches", &muMatches, &b_muMatches);
    //       Run_Tree->SetBranchAddress("muTrkQuality", &muTrkQuality, &b_muTrkQuality);
    //       Run_Tree->SetBranchAddress("muIsoTrk", &muIsoTrk, &b_muIsoTrk);
    //       Run_Tree->SetBranchAddress("muPFChIso", &muPFChIso, &b_muPFChIso);
    //       Run_Tree->SetBranchAddress("muPFPhoIso", &muPFPhoIso, &b_muPFPhoIso);
    //       Run_Tree->SetBranchAddress("muPFNeuIso", &muPFNeuIso, &b_muPFNeuIso);
    //       Run_Tree->SetBranchAddress("muPFPUIso", &muPFPUIso, &b_muPFPUIso);
    //       Run_Tree->SetBranchAddress("muPFChIso03", &muPFChIso03, &b_muPFChIso03);
    //       Run_Tree->SetBranchAddress("muPFPhoIso03", &muPFPhoIso03, &b_muPFPhoIso03);
    //       Run_Tree->SetBranchAddress("muPFNeuIso03", &muPFNeuIso03, &b_muPFNeuIso03);
    //       Run_Tree->SetBranchAddress("muPFPUIso03", &muPFPUIso03, &b_muPFPUIso03);
    //       Run_Tree->SetBranchAddress("muFiredTrgs", &muFiredTrgs, &b_muFiredTrgs);
    //       Run_Tree->SetBranchAddress("muFiredL1Trgs", &muFiredL1Trgs, &b_muFiredL1Trgs);
    //       Run_Tree->SetBranchAddress("muInnervalidFraction", &muInnervalidFraction, &b_muInnervalidFraction);
    //       Run_Tree->SetBranchAddress("musegmentCompatibility", &musegmentCompatibility, &b_musegmentCompatibility);
    //       Run_Tree->SetBranchAddress("muchi2LocalPosition", &muchi2LocalPosition, &b_muchi2LocalPosition);
    //       Run_Tree->SetBranchAddress("mutrkKink", &mutrkKink, &b_mutrkKink);
    //       Run_Tree->SetBranchAddress("muBestTrkPtError", &muBestTrkPtError, &b_muBestTrkPtError);
    //       Run_Tree->SetBranchAddress("muBestTrkPt", &muBestTrkPt, &b_muBestTrkPt);
    //       Run_Tree->SetBranchAddress("muBestTrkType", &muBestTrkType, &b_muBestTrkType);
    //       Run_Tree->SetBranchAddress("nJet", &nJet, &b_nJet);
    //       Run_Tree->SetBranchAddress("jetPt", &jetPt, &b_jetPt);
    //       Run_Tree->SetBranchAddress("jetEn", &jetEn, &b_jetEn);
    //       Run_Tree->SetBranchAddress("jetEta", &jetEta, &b_jetEta);
    //       Run_Tree->SetBranchAddress("jetPhi", &jetPhi, &b_jetPhi);
    //       Run_Tree->SetBranchAddress("jetRawPt", &jetRawPt, &b_jetRawPt);
    //       Run_Tree->SetBranchAddress("jetRawEn", &jetRawEn, &b_jetRawEn);
    //       Run_Tree->SetBranchAddress("jetMt", &jetMt, &b_jetMt);
    //       Run_Tree->SetBranchAddress("jetArea", &jetArea, &b_jetArea);
    //       Run_Tree->SetBranchAddress("jetLeadTrackPt", &jetLeadTrackPt, &b_jetLeadTrackPt);
    //       Run_Tree->SetBranchAddress("jetLeadTrackEta", &jetLeadTrackEta, &b_jetLeadTrackEta);
    //       Run_Tree->SetBranchAddress("jetLeadTrackPhi", &jetLeadTrackPhi, &b_jetLeadTrackPhi);
    //       Run_Tree->SetBranchAddress("jetLepTrackPID", &jetLepTrackPID, &b_jetLepTrackPID);
    //       Run_Tree->SetBranchAddress("jetLepTrackPt", &jetLepTrackPt, &b_jetLepTrackPt);
    //       Run_Tree->SetBranchAddress("jetLepTrackEta", &jetLepTrackEta, &b_jetLepTrackEta);
    //       Run_Tree->SetBranchAddress("jetLepTrackPhi", &jetLepTrackPhi, &b_jetLepTrackPhi);
    //       Run_Tree->SetBranchAddress("jetCSV2BJetTags", &jetCSV2BJetTags, &b_jetCSV2BJetTags);
    //       Run_Tree->SetBranchAddress("jetDeepCSVTags_b", &jetDeepCSVTags_b, &b_jetDeepCSVTags_b);
    //       Run_Tree->SetBranchAddress("jetDeepCSVTags_bb", &jetDeepCSVTags_bb, &b_jetDeepCSVTags_bb);
    //       Run_Tree->SetBranchAddress("jetDeepCSVTags_c", &jetDeepCSVTags_c, &b_jetDeepCSVTags_c);
    //       Run_Tree->SetBranchAddress("jetDeepCSVTags_udsg", &jetDeepCSVTags_udsg, &b_jetDeepCSVTags_udsg);
    //       Run_Tree->SetBranchAddress("jetPartonID", &jetPartonID, &b_jetPartonID);
    //       Run_Tree->SetBranchAddress("jetHadFlvr", &jetHadFlvr, &b_jetHadFlvr);
    //       Run_Tree->SetBranchAddress("jetGenJetEn", &jetGenJetEn, &b_jetGenJetEn);
    //       Run_Tree->SetBranchAddress("jetGenJetPt", &jetGenJetPt, &b_jetGenJetPt);
    //       Run_Tree->SetBranchAddress("jetGenJetEta", &jetGenJetEta, &b_jetGenJetEta);
    //       Run_Tree->SetBranchAddress("jetGenJetPhi", &jetGenJetPhi, &b_jetGenJetPhi);
    //       Run_Tree->SetBranchAddress("jetGenPartonID", &jetGenPartonID, &b_jetGenPartonID);
    //       Run_Tree->SetBranchAddress("jetGenEn", &jetGenEn, &b_jetGenEn);
    //       Run_Tree->SetBranchAddress("jetGenPt", &jetGenPt, &b_jetGenPt);
    //       Run_Tree->SetBranchAddress("jetGenEta", &jetGenEta, &b_jetGenEta);
    //       Run_Tree->SetBranchAddress("jetGenPhi", &jetGenPhi, &b_jetGenPhi);
    //       Run_Tree->SetBranchAddress("jetGenPartonMomID", &jetGenPartonMomID, &b_jetGenPartonMomID);
    //       Run_Tree->SetBranchAddress("jetP4Smear", &jetP4Smear, &b_jetP4Smear);
    //       Run_Tree->SetBranchAddress("jetP4SmearUp", &jetP4SmearUp, &b_jetP4SmearUp);
    //       Run_Tree->SetBranchAddress("jetP4SmearDo", &jetP4SmearDo, &b_jetP4SmearDo);
    //       Run_Tree->SetBranchAddress("jetPFLooseId", &jetPFLooseId, &b_jetPFLooseId);
    //       Run_Tree->SetBranchAddress("jetID", &jetID, &b_jetID);
    //       Run_Tree->SetBranchAddress("jetPUID", &jetPUID, &b_jetPUID);
    //       Run_Tree->SetBranchAddress("jetPUFullID", &jetPUFullID, &b_jetPUFullID);
    //       Run_Tree->SetBranchAddress("jetJECUnc", &jetJECUnc, &b_jetJECUnc);
    //       Run_Tree->SetBranchAddress("jetFiredTrgs", &jetFiredTrgs, &b_jetFiredTrgs);
    //       Run_Tree->SetBranchAddress("jetCHF", &jetCHF, &b_jetCHF);
    //       Run_Tree->SetBranchAddress("jetNHF", &jetNHF, &b_jetNHF);
    //       Run_Tree->SetBranchAddress("jetCEF", &jetCEF, &b_jetCEF);
    //       Run_Tree->SetBranchAddress("jetNEF", &jetNEF, &b_jetNEF);
    //       Run_Tree->SetBranchAddress("jetNCH", &jetNCH, &b_jetNCH);
    //       Run_Tree->SetBranchAddress("jetNNP", &jetNNP, &b_jetNNP);
    //       Run_Tree->SetBranchAddress("jetMUF", &jetMUF, &b_jetMUF);
    //       Run_Tree->SetBranchAddress("jetVtxPt", &jetVtxPt, &b_jetVtxPt);
    //       Run_Tree->SetBranchAddress("jetVtxMass", &jetVtxMass, &b_jetVtxMass);
    //       Run_Tree->SetBranchAddress("jetVtxNtrks", &jetVtxNtrks, &b_jetVtxNtrks);
    //       Run_Tree->SetBranchAddress("jetVtx3DVal", &jetVtx3DVal, &b_jetVtx3DVal);
    //       Run_Tree->SetBranchAddress("jetVtx3DSig", &jetVtx3DSig, &b_jetVtx3DSig);
    
    Run_Tree->SetBranchAddress("nBoostedTau", &nBoostedTau);
    Run_Tree->SetBranchAddress("nBoostedTauOrig", &nBoostedTauOrig);
    Run_Tree->SetBranchAddress("boostedTaupfTausDiscriminationByDecayModeFinding", &boostedTaupfTausDiscriminationByDecayModeFinding);
    Run_Tree->SetBranchAddress("boostedTaupfTausDiscriminationByDecayModeFindingNewDMs", &boostedTaupfTausDiscriminationByDecayModeFindingNewDMs);
    Run_Tree->SetBranchAddress("boostedTauByMVA6LooseElectronRejection", &boostedTauByMVA6LooseElectronRejection);
    Run_Tree->SetBranchAddress("boostedTauByMVA6TightElectronRejection", &boostedTauByMVA6TightElectronRejection);
    Run_Tree->SetBranchAddress("boostedTauByLooseMuonRejection3", &boostedTauByLooseMuonRejection3);
    Run_Tree->SetBranchAddress("boostedTauByTightMuonRejection3", &boostedTauByTightMuonRejection3);
    Run_Tree->SetBranchAddress("boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits", &boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits);
    Run_Tree->SetBranchAddress("boostedTauByTightCombinedIsolationDeltaBetaCorr3Hits", &boostedTauByTightCombinedIsolationDeltaBetaCorr3Hits);
    Run_Tree->SetBranchAddress("boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits", &boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits);
    Run_Tree->SetBranchAddress("boostedTauByIsolationMVArun2v1DBoldDMwLTraw", &boostedTauByIsolationMVArun2v1DBoldDMwLTraw);
    Run_Tree->SetBranchAddress("boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew", &boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew);
    Run_Tree->SetBranchAddress("boostedTauByTightIsolationMVArun2v1DBoldDMwLT", &boostedTauByTightIsolationMVArun2v1DBoldDMwLT);
    Run_Tree->SetBranchAddress("boostedTauByTightIsolationMVArun2v1DBoldDMwLTNew", &boostedTauByTightIsolationMVArun2v1DBoldDMwLTNew);
    Run_Tree->SetBranchAddress("boostedTauByVLooseIsolationMVArun2v1DBoldDMwLTNew", &boostedTauByVLooseIsolationMVArun2v1DBoldDMwLTNew);
    Run_Tree->SetBranchAddress("boostedTauByMediumIsolationMVArun2v1DBoldDMwLTNew", &boostedTauByMediumIsolationMVArun2v1DBoldDMwLTNew);
    Run_Tree->SetBranchAddress("boostedTauByVTightIsolationMVArun2v1DBoldDMwLTNew", &boostedTauByVTightIsolationMVArun2v1DBoldDMwLTNew);
    Run_Tree->SetBranchAddress("boostedTauByLooseIsolationMVArun2v1DBoldDMwLT", &boostedTauByLooseIsolationMVArun2v1DBoldDMwLT);
    Run_Tree->SetBranchAddress("boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNew", &boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNew);
    Run_Tree->SetBranchAddress("boostedTauEta", &boostedTauEta);
    Run_Tree->SetBranchAddress("boostedTauPhi", &boostedTauPhi);
    Run_Tree->SetBranchAddress("boostedTauPt", &boostedTauPt);
    Run_Tree->SetBranchAddress("boostedTauEt", &boostedTauEt);
    Run_Tree->SetBranchAddress("boostedTauCharge", &boostedTauCharge);
    Run_Tree->SetBranchAddress("boostedTauP", &boostedTauP);
    Run_Tree->SetBranchAddress("boostedTauPx", &boostedTauPx);
    Run_Tree->SetBranchAddress("boostedTauPy", &boostedTauPy);
    Run_Tree->SetBranchAddress("boostedTauPz", &boostedTauPz);
    Run_Tree->SetBranchAddress("boostedTauVz", &boostedTauVz);
    Run_Tree->SetBranchAddress("boostedTauEnergy", &boostedTauEnergy);
    Run_Tree->SetBranchAddress("boostedTauMass", &boostedTauMass);
    Run_Tree->SetBranchAddress("boostedTauDxy", &boostedTauDxy);
    Run_Tree->SetBranchAddress("boostedTauZImpact", &boostedTauZImpact);
    Run_Tree->SetBranchAddress("boostedTauDecayMode", &boostedTauDecayMode);
    Run_Tree->SetBranchAddress("boostedTauLeadChargedHadronExists", &boostedTauLeadChargedHadronExists);
    Run_Tree->SetBranchAddress("boostedTauLeadChargedHadronEta", &boostedTauLeadChargedHadronEta);
    Run_Tree->SetBranchAddress("boostedTauLeadChargedHadronPhi", &boostedTauLeadChargedHadronPhi);
    Run_Tree->SetBranchAddress("boostedTauLeadChargedHadronPt", &boostedTauLeadChargedHadronPt);
    Run_Tree->SetBranchAddress("boostedTauChargedIsoPtSum", &boostedTauChargedIsoPtSum);
    Run_Tree->SetBranchAddress("boostedTauChargedIsoPtSumNoOverLap", &boostedTauChargedIsoPtSumNoOverLap);
    Run_Tree->SetBranchAddress("boostedTauNeutralIsoPtSum", &boostedTauNeutralIsoPtSum);
    Run_Tree->SetBranchAddress("boostedTauNeutralIsoPtSumNoOverLap", &boostedTauNeutralIsoPtSumNoOverLap);
    Run_Tree->SetBranchAddress("boostedTauPuCorrPtSum", &boostedTauPuCorrPtSum);
    Run_Tree->SetBranchAddress("boostedTauNumSignalPFChargedHadrCands", &boostedTauNumSignalPFChargedHadrCands);
    Run_Tree->SetBranchAddress("boostedTauNumSignalPFNeutrHadrCands", &boostedTauNumSignalPFNeutrHadrCands);
    Run_Tree->SetBranchAddress("boostedTauNumSignalPFGammaCands", &boostedTauNumSignalPFGammaCands);
    Run_Tree->SetBranchAddress("boostedTauNumSignalPFCands", &boostedTauNumSignalPFCands);
    Run_Tree->SetBranchAddress("boostedTauNumIsolationPFChargedHadrCands", &boostedTauNumIsolationPFChargedHadrCands);
    Run_Tree->SetBranchAddress("boostedTauNumIsolationPFNeutrHadrCands", &boostedTauNumIsolationPFNeutrHadrCands);
    Run_Tree->SetBranchAddress("boostedTauNumIsolationPFGammaCands", &boostedTauNumIsolationPFGammaCands);
    Run_Tree->SetBranchAddress("boostedTauNumIsolationPFCands", &boostedTauNumIsolationPFCands);
    Run_Tree->SetBranchAddress("boostedTaufootprintCorrection", &boostedTaufootprintCorrection);
    Run_Tree->SetBranchAddress("boostedTauphotonPtSumOutsideSignalCone", &boostedTauphotonPtSumOutsideSignalCone);
    Run_Tree->SetBranchAddress("boostedTaudz", &boostedTaudz);
    Run_Tree->SetBranchAddress("boostedTaudxy", &boostedTaudxy);
    Run_Tree->SetBranchAddress("boostedTauSignalPFCands", &boostedTauSignalPFCands);
    Run_Tree->SetBranchAddress("boostedTauSignalPFGammaCands", &boostedTauSignalPFGammaCands);
    Run_Tree->SetBranchAddress("boostedTauIsolationPFCands", &boostedTauIsolationPFCands);
    Run_Tree->SetBranchAddress("boostedTauIsolationPFGammaCands", &boostedTauIsolationPFGammaCands);
    //       Run_Tree->SetBranchAddress("boostedTauByDeepTau2017v1VSjetraw", &boostedTauByDeepTau2017v1VSjetraw, &b_boostedTauByDeepTau2017v1VSjetraw);
    //       Run_Tree->SetBranchAddress("boostedTauByDeepTau2017v1VSeraw", &boostedTauByDeepTau2017v1VSeraw, &b_boostedTauByDeepTau2017v1VSeraw);
    //       Run_Tree->SetBranchAddress("boostedTauByDeepTau2017v1VSmuraw", &boostedTauByDeepTau2017v1VSmuraw, &b_boostedTauByDeepTau2017v1VSmuraw);
    //       Run_Tree->SetBranchAddress("boostedTaubyVVVLooseDeepTau2017v1VSjet", &boostedTaubyVVVLooseDeepTau2017v1VSjet, &b_boostedTaubyVVVLooseDeepTau2017v1VSjet);
    //       Run_Tree->SetBranchAddress("boostedTaubyVLooseDeepTau2017v1VSjet", &boostedTaubyVLooseDeepTau2017v1VSjet, &b_boostedTaubyVLooseDeepTau2017v1VSjet);
    //       Run_Tree->SetBranchAddress("boostedTaubyLooseDeepTau2017v1VSjet", &boostedTaubyLooseDeepTau2017v1VSjet, &b_boostedTaubyLooseDeepTau2017v1VSjet);
    //       Run_Tree->SetBranchAddress("boostedTaubyMediumDeepTau2017v1VSjet", &boostedTaubyMediumDeepTau2017v1VSjet, &b_boostedTaubyMediumDeepTau2017v1VSjet);
    //       Run_Tree->SetBranchAddress("boostedTaubyTightDeepTau2017v1VSjet", &boostedTaubyTightDeepTau2017v1VSjet, &b_boostedTaubyTightDeepTau2017v1VSjet);
    //       Run_Tree->SetBranchAddress("boostedTaubyVVTightDeepTau2017v1VSjet", &boostedTaubyVVTightDeepTau2017v1VSjet, &b_boostedTaubyVVTightDeepTau2017v1VSjet);
    //       Run_Tree->SetBranchAddress("boostedTaubyVVVLooseDeepTau2017v1VSe", &boostedTaubyVVVLooseDeepTau2017v1VSe, &b_boostedTaubyVVVLooseDeepTau2017v1VSe);
    //       Run_Tree->SetBranchAddress("boostedTaubyLooseDeepTau2017v1VSe", &boostedTaubyLooseDeepTau2017v1VSe, &b_boostedTaubyLooseDeepTau2017v1VSe);
    //       Run_Tree->SetBranchAddress("boostedTaubyTightDeepTau2017v1VSe", &boostedTaubyTightDeepTau2017v1VSe, &b_boostedTaubyTightDeepTau2017v1VSe);
    //       Run_Tree->SetBranchAddress("boostedTaubyVVTightDeepTau2017v1VSe", &boostedTaubyVVTightDeepTau2017v1VSe, &b_boostedTaubyVVTightDeepTau2017v1VSe);
    //       Run_Tree->SetBranchAddress("boostedTaubyVVVLooseDeepTau2017v1VSmu", &boostedTaubyVVVLooseDeepTau2017v1VSmu, &b_boostedTaubyVVVLooseDeepTau2017v1VSmu);
    //       Run_Tree->SetBranchAddress("boostedTaubyLooseDeepTau2017v1VSmu", &boostedTaubyLooseDeepTau2017v1VSmu, &b_boostedTaubyLooseDeepTau2017v1VSmu);
    //       Run_Tree->SetBranchAddress("boostedTaubyTightDeepTau2017v1VSmu", &boostedTaubyTightDeepTau2017v1VSmu, &b_boostedTaubyTightDeepTau2017v1VSmu);
    //       Run_Tree->SetBranchAddress("boostedTaubyVVTightDeepTau2017v1VSmu", &boostedTaubyVVTightDeepTau2017v1VSmu, &b_boostedTaubyVVTightDeepTau2017v1VSmu);
    Run_Tree->SetBranchAddress("boostedTauagainstElectronVLooseMVA62018", &boostedTauagainstElectronVLooseMVA62018);
    Run_Tree->SetBranchAddress("boostedTauagainstElectronLooseMVA62018", &boostedTauagainstElectronLooseMVA62018);
    Run_Tree->SetBranchAddress("boostedTauagainstElectronTightMVA62018", &boostedTauagainstElectronTightMVA62018);
    //
    
    
    
    
    
    //########################################   General Info
    Run_Tree->SetBranchAddress("isData", &isData);
    Run_Tree->SetBranchAddress("run", &run);
    Run_Tree->SetBranchAddress("lumis", &lumis);
    Run_Tree->SetBranchAddress("event", &event);
    Run_Tree->SetBranchAddress("genWeight",&genWeight);
    Run_Tree->SetBranchAddress("HLTEleMuX", &HLTEleMuX);
    Run_Tree->SetBranchAddress("HLTJet", &HLTJet);
    Run_Tree->SetBranchAddress("puTrue", &puTrue);
    Run_Tree->SetBranchAddress("nVtx",&nVtx);
    
    //########################################   MC Info
    Run_Tree->SetBranchAddress("nMC", &nMC);
    Run_Tree->SetBranchAddress("mcPID", &mcPID);
    Run_Tree->SetBranchAddress("mcStatus", &mcStatus);
    Run_Tree->SetBranchAddress("mcPt", &mcPt );
    Run_Tree->SetBranchAddress("mcEta", &mcEta );
    Run_Tree->SetBranchAddress("mcPhi", &mcPhi );
    Run_Tree->SetBranchAddress("mcE", &mcE );
    Run_Tree->SetBranchAddress("mcMass", &mcMass );
    Run_Tree->SetBranchAddress("mcMomPID", &mcMomPID );
    Run_Tree->SetBranchAddress("mcGMomPID", &mcGMomPID );
    Run_Tree->SetBranchAddress("mcStatusFlag",&mcStatusFlag);
    
    //########################################   Tau Info
    //       Run_Tree->SetBranchAddress("nTau", &nTau);
    //       Run_Tree->SetBranchAddress("tauPt"  ,&tauPt);
    //       Run_Tree->SetBranchAddress("tauEta"  ,&tauEta);
    //       Run_Tree->SetBranchAddress("tauPhi"  ,&tauPhi);
    //       Run_Tree->SetBranchAddress("tauMass"  ,&tauMass);
    //       Run_Tree->SetBranchAddress("tauCharge"  ,&tauCharge);
    //       Run_Tree->SetBranchAddress("taupfTausDiscriminationByDecayModeFinding", &taupfTausDiscriminationByDecayModeFinding);
    //       Run_Tree->SetBranchAddress("tauByTightMuonRejection3", &tauByTightMuonRejection3);
    //       Run_Tree->SetBranchAddress("tauByLooseMuonRejection3", &tauByLooseMuonRejection3);
    //       Run_Tree->SetBranchAddress("tauByMVA6MediumElectronRejection"  ,&tauByMVA6MediumElectronRejection);
    //       Run_Tree->SetBranchAddress("tauByLooseCombinedIsolationDeltaBetaCorr3Hits",&tauByLooseCombinedIsolationDeltaBetaCorr3Hits);
    //       Run_Tree->SetBranchAddress("tauByMediumCombinedIsolationDeltaBetaCorr3Hits",&tauByMediumCombinedIsolationDeltaBetaCorr3Hits);
    //       Run_Tree->SetBranchAddress("tauByMVA6LooseElectronRejection", &tauByMVA6LooseElectronRejection);
    //       Run_Tree->SetBranchAddress("tauDxy",&tauDxy);
    //       Run_Tree->SetBranchAddress("tauDecayMode",&tauDecayMode);
    //       Run_Tree->SetBranchAddress("tauByLooseIsolationMVArun2v1DBoldDMwLT",&tauByLooseIsolationMVArun2v1DBoldDMwLT);
    //       Run_Tree->SetBranchAddress("tauByVLooseIsolationMVArun2v1DBoldDMwLT",&tauByVLooseIsolationMVArun2v1DBoldDMwLT);
    //       Run_Tree->SetBranchAddress("tauByIsolationMVArun2v1DBoldDMwLTraw",&tauByIsolationMVArun2v1DBoldDMwLTraw);
    //       Run_Tree->SetBranchAddress("tauByIsolationMVArun2v2DBoldDMwLTraw",&tauByIsolationMVArun2v2DBoldDMwLTraw);
    //       Run_Tree->SetBranchAddress("tauCombinedIsolationDeltaBetaCorrRaw3Hits",&tauCombinedIsolationDeltaBetaCorrRaw3Hits);
    //    Run_Tree->SetBranchAddress("tauByLooseCombinedIsolationDeltaBetaCorr3Hits",&tauByLooseCombinedIsolationDeltaBetaCorr3Hits);
    //       Run_Tree->SetBranchAddress("boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNoOverLap",&boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNoOverLap);
    //       Run_Tree->SetBranchAddress("boostedTauByTightIsolationMVArun2v1DBoldDMwLTNoOverLap",&boostedTauByTightIsolationMVArun2v1DBoldDMwLTNoOverLap);
    //       Run_Tree->SetBranchAddress("boostedTauByIsolationMVArun2v1DBoldDMwLTrawNoOverLap",&boostedTauByIsolationMVArun2v1DBoldDMwLTrawNoOverLap);
    //       Run_Tree->SetBranchAddress("boostedTauChargedIsoPtSumNoOverLap",&boostedTauChargedIsoPtSumNoOverLap);
    //       Run_Tree->SetBranchAddress("boostedTauNeutralIsoPtSumNoOverLap",&boostedTauNeutralIsoPtSumNoOverLap);
    
    Run_Tree->SetBranchAddress("boostedTauNumIsolationPFChargedHadrCands"  ,&boostedTauNumIsolationPFChargedHadrCands);
    Run_Tree->SetBranchAddress("boostedTauNumIsolationPFNeutrHadrCands"  ,&boostedTauNumIsolationPFNeutrHadrCands);
    Run_Tree->SetBranchAddress("boostedTauNumIsolationPFGammaCands"  ,&boostedTauNumIsolationPFGammaCands);
    Run_Tree->SetBranchAddress("boostedTauNumIsolationPFCands"  ,&boostedTauNumIsolationPFCands);
    //       Run_Tree->SetBranchAddress("boostedTauNumIsolationPFChargedHadrCandsOrig"  ,&boostedTauNumIsolationPFChargedHadrCandsOrig);
    //       Run_Tree->SetBranchAddress("boostedTauNumIsolationPFNeutrHadrCandsOrig"  ,&boostedTauNumIsolationPFNeutrHadrCandsOrig);
    //       Run_Tree->SetBranchAddress("boostedTauNumIsolationPFGammaCandsOrig"  ,&boostedTauNumIsolationPFGammaCandsOrig);
    //       Run_Tree->SetBranchAddress("boostedTauNumIsolationPFCandsOrig"  ,&boostedTauNumIsolationPFCandsOrig);
    
    //########################################   Mu Info
    Run_Tree->SetBranchAddress("nMu", &nMu);
    Run_Tree->SetBranchAddress("muPt"  ,&muPt);
    Run_Tree->SetBranchAddress("muEta"  ,&muEta);
    Run_Tree->SetBranchAddress("muPhi"  ,&muPhi);
    Run_Tree->SetBranchAddress("muIsoTrk", &muIsoTrk);
    Run_Tree->SetBranchAddress("muCharge",&muCharge);
    Run_Tree->SetBranchAddress("muIDbit",&muIDbit);//NEW
    Run_Tree->SetBranchAddress("muPFChIso", &muPFChIso);
    Run_Tree->SetBranchAddress("muPFPhoIso", &muPFPhoIso);
    Run_Tree->SetBranchAddress("muPFNeuIso", &muPFNeuIso);
    Run_Tree->SetBranchAddress("muPFPUIso", &muPFPUIso);
    Run_Tree->SetBranchAddress("muPFChIso03", &muPFChIso03);
    Run_Tree->SetBranchAddress("muPFPhoIso03", &muPFPhoIso03);
    Run_Tree->SetBranchAddress("muPFNeuIso03", &muPFNeuIso03);
    Run_Tree->SetBranchAddress("muPFPUIso03", &muPFPUIso03);
    
    Run_Tree->SetBranchAddress("muD0",&muD0);
    Run_Tree->SetBranchAddress("muDz",&muDz);
    
    //########################################   Ele Info
    Run_Tree->SetBranchAddress("nEle", &nEle);
    Run_Tree->SetBranchAddress("eleCharge", &eleCharge);
    Run_Tree->SetBranchAddress("eleChargeConsistent", &eleChargeConsistent);
    Run_Tree->SetBranchAddress("eleEn", &eleEn);
    Run_Tree->SetBranchAddress("eleSCEn", &eleSCEn);
    //    Run_Tree->SetBranchAddress("eleESEn", &eleESEn);
    Run_Tree->SetBranchAddress("eleESEnP1", &eleESEnP1);
    Run_Tree->SetBranchAddress("eleESEnP2", &eleESEnP2);
    Run_Tree->SetBranchAddress("eleD0", &eleD0);
    Run_Tree->SetBranchAddress("eleDz", &eleDz);
    Run_Tree->SetBranchAddress("eleSIP", &eleSIP);
    Run_Tree->SetBranchAddress("elePt", &elePt);
    Run_Tree->SetBranchAddress("eleEta", &eleEta);
    Run_Tree->SetBranchAddress("elePhi", &elePhi);
    //    Run_Tree->SetBranchAddress("eleR9", &eleR9);
    //    Run_Tree->SetBranchAddress("eleCalibPt", &eleCalibPt);
    //    Run_Tree->SetBranchAddress("eleCalibEn", &eleCalibEn);
    Run_Tree->SetBranchAddress("eleSCEta", &eleSCEta);
    //    Run_Tree->SetBranchAddress("eleSCPhi", &eleSCPhi);
    //    Run_Tree->SetBranchAddress("eleSCRawEn", &eleSCRawEn);
    //    Run_Tree->SetBranchAddress("eleSCEtaWidth", &eleSCEtaWidth);
    //    Run_Tree->SetBranchAddress("eleSCPhiWidth", &eleSCPhiWidth);
    //    Run_Tree->SetBranchAddress("eleHoverE", &eleHoverE);
    //    Run_Tree->SetBranchAddress("eleEoverP", &eleEoverP);
    //    Run_Tree->SetBranchAddress("eleEoverPout", &eleEoverPout);
    //    Run_Tree->SetBranchAddress("eleEoverPInv", &eleEoverPInv);
    //    Run_Tree->SetBranchAddress("eleBrem", &eleBrem);
    //    Run_Tree->SetBranchAddress("eledEtaAtVtx", &eledEtaAtVtx);
    //    Run_Tree->SetBranchAddress("eledPhiAtVtx", &eledPhiAtVtx);
    ////    Run_Tree->SetBranchAddress("eledEtaAtCalo", &eledEtaAtCalo);
    //    Run_Tree->SetBranchAddress("eleSigmaIEtaIEtaFull5x5", &eleSigmaIEtaIEtaFull5x5);
    //    Run_Tree->SetBranchAddress("eleSigmaIPhiIPhiFull5x5", &eleSigmaIPhiIPhiFull5x5);
    Run_Tree->SetBranchAddress("eleConvVeto", &eleConvVeto);
    Run_Tree->SetBranchAddress("eleMissHits", &eleMissHits);
    Run_Tree->SetBranchAddress("eleESEffSigmaRR", &eleESEffSigmaRR);
    Run_Tree->SetBranchAddress("elePFChIso", &elePFChIso);
    Run_Tree->SetBranchAddress("elePFPhoIso", &elePFPhoIso);
    Run_Tree->SetBranchAddress("elePFNeuIso", &elePFNeuIso);
    Run_Tree->SetBranchAddress("elePFPUIso", &elePFPUIso);
    Run_Tree->SetBranchAddress("elePFClusEcalIso", &elePFClusEcalIso);
    Run_Tree->SetBranchAddress("elePFClusHcalIso", &elePFClusHcalIso);
    //    Run_Tree->SetBranchAddress("elePFMiniIso", &elePFMiniIso);
    Run_Tree->SetBranchAddress("eleIDMVAIso", &eleIDMVAIso);
    Run_Tree->SetBranchAddress("eleIDMVANoIso", &eleIDMVANoIso);
    //    Run_Tree->SetBranchAddress("eledEtaseedAtVtx", &eledEtaseedAtVtx);
    //    Run_Tree->SetBranchAddress("eleE1x5", &eleE1x5);
    //    Run_Tree->SetBranchAddress("eleE2x5", &eleE2x5);
    //    Run_Tree->SetBranchAddress("eleE5x5", &eleE5x5);
    //    Run_Tree->SetBranchAddress("eleE1x5Full5x5", &eleE1x5Full5x5);
    //    Run_Tree->SetBranchAddress("eleE2x5Full5x5", &eleE2x5Full5x5);
    //    Run_Tree->SetBranchAddress("eleE5x5Full5x5", &eleE5x5Full5x5);
    //    Run_Tree->SetBranchAddress("eleR9Full5x5", &eleR9Full5x5);
    //    Run_Tree->SetBranchAddress("eleEcalDrivenSeed", &eleEcalDrivenSeed);
    //    Run_Tree->SetBranchAddress("eleDr03EcalRecHitSumEt", &eleDr03EcalRecHitSumEt);
    //    Run_Tree->SetBranchAddress("eleDr03HcalDepth1TowerSumEt", &eleDr03HcalDepth1TowerSumEt);
    //    Run_Tree->SetBranchAddress("eleDr03HcalDepth2TowerSumEt", &eleDr03HcalDepth2TowerSumEt);
    //    Run_Tree->SetBranchAddress("eleDr03HcalTowerSumEt", &eleDr03HcalTowerSumEt);
    //    Run_Tree->SetBranchAddress("eleDr03TkSumPt", &eleDr03TkSumPt);
    //    Run_Tree->SetBranchAddress("elecaloEnergy", &elecaloEnergy);
    //    Run_Tree->SetBranchAddress("eleTrkdxy", &eleTrkdxy);
    //    Run_Tree->SetBranchAddress("eleKFHits", &eleKFHits);
    //    Run_Tree->SetBranchAddress("eleKFChi2", &eleKFChi2);
    //    Run_Tree->SetBranchAddress("eleIDbit", &eleIDbit);
    
    //########################################   Jet Info
    Run_Tree->SetBranchAddress("nJet",&nJet);
    Run_Tree->SetBranchAddress("jetPt",&jetPt);
    Run_Tree->SetBranchAddress("jetEta",&jetEta);
    Run_Tree->SetBranchAddress("jetPhi",&jetPhi);
    Run_Tree->SetBranchAddress("jetEn",&jetEn);
    Run_Tree->SetBranchAddress("jetCSV2BJetTags",&jetCSV2BJetTags);
    Run_Tree->SetBranchAddress("jetDeepCSVTags_b", &jetDeepCSVTags_b);
    Run_Tree->SetBranchAddress("jetPFLooseId",&jetPFLooseId);
    Run_Tree->SetBranchAddress("jetPUID",&jetPUID);
    Run_Tree->SetBranchAddress("jetRawPt",&jetRawPt);
    Run_Tree->SetBranchAddress("jetJECUnc",&jetJECUnc);
    Run_Tree->SetBranchAddress("jetRawEn",&jetRawEn);
    Run_Tree->SetBranchAddress("jetHadFlvr",&jetHadFlvr);
    //    Run_Tree->SetBranchAddress("jetP4Smear",&jetP4Smear);
    //    Run_Tree->SetBranchAddress("jetP4SmearUp",&jetP4SmearUp);
    //    Run_Tree->SetBranchAddress("jetP4SmearDo",&jetP4SmearDo);
    
    
    //       Run_Tree->SetBranchAddress("pfMET_T1JESUp", &pfMET_T1JESUp, &b_pfMET_T1JESUp);
    //       Run_Tree->SetBranchAddress("pfMET_T1JESDo", &pfMET_T1JESDo, &b_pfMET_T1JESDo);
    //       Run_Tree->SetBranchAddress("pfMET_T1UESUp", &pfMET_T1UESUp, &b_pfMET_T1UESUp);
    //       Run_Tree->SetBranchAddress("pfMET_T1UESDo", &pfMET_T1UESDo, &b_pfMET_T1UESDo);
    //       Run_Tree->SetBranchAddress("pfMETPhi_T1JESUp", &pfMETPhi_T1JESUp, &b_pfMETPhi_T1JESUp);
    //       Run_Tree->SetBranchAddress("pfMETPhi_T1JESDo", &pfMETPhi_T1JESDo, &b_pfMETPhi_T1JESDo);
    //       Run_Tree->SetBranchAddress("pfMETPhi_T1UESUp", &pfMETPhi_T1UESUp, &b_pfMETPhi_T1UESUp);
    //       Run_Tree->SetBranchAddress("pfMETPhi_T1UESDo", &pfMETPhi_T1UESDo, &b_pfMETPhi_T1UESDo);
    
    
    //########################################   AK8 Info
    
    Run_Tree->SetBranchAddress("nAK8Jet", &nAK8Jet, &b_nAK8Jet);
    Run_Tree->SetBranchAddress("AK8JetPt", &AK8JetPt, &b_AK8JetPt);
    Run_Tree->SetBranchAddress("AK8JetEn", &AK8JetEn, &b_AK8JetEn);
    Run_Tree->SetBranchAddress("AK8JetRawPt", &AK8JetRawPt, &b_AK8JetRawPt);
    Run_Tree->SetBranchAddress("AK8JetRawEn", &AK8JetRawEn, &b_AK8JetRawEn);
    Run_Tree->SetBranchAddress("AK8JetEta", &AK8JetEta, &b_AK8JetEta);
    Run_Tree->SetBranchAddress("AK8JetPhi", &AK8JetPhi, &b_AK8JetPhi);
    Run_Tree->SetBranchAddress("AK8JetMass", &AK8JetMass, &b_AK8JetMass);
    Run_Tree->SetBranchAddress("AK8Jet_tau1", &AK8Jet_tau1, &b_AK8Jet_tau1);
    Run_Tree->SetBranchAddress("AK8Jet_tau2", &AK8Jet_tau2, &b_AK8Jet_tau2);
    Run_Tree->SetBranchAddress("AK8Jet_tau3", &AK8Jet_tau3, &b_AK8Jet_tau3);
    Run_Tree->SetBranchAddress("AK8Jetnconstituents", &AK8Jetnconstituents, &b_AK8Jetnconstituents);
    Run_Tree->SetBranchAddress("AK8JetPFLooseId", &AK8JetPFLooseId, &b_AK8JetPFLooseId);
    Run_Tree->SetBranchAddress("AK8JetPFTightLepVetoId", &AK8JetPFTightLepVetoId, &b_AK8JetPFTightLepVetoId);
    Run_Tree->SetBranchAddress("AK8JetSoftDropMass", &AK8JetSoftDropMass, &b_AK8JetSoftDropMass);
    Run_Tree->SetBranchAddress("AK8JetSoftDropMassCorr", &AK8JetSoftDropMassCorr, &b_AK8JetSoftDropMassCorr);
    Run_Tree->SetBranchAddress("AK8JetPrunedMass", &AK8JetPrunedMass, &b_AK8JetPrunedMass);
    Run_Tree->SetBranchAddress("AK8JetPrunedMassCorr", &AK8JetPrunedMassCorr, &b_AK8JetPrunedMassCorr);
    Run_Tree->SetBranchAddress("AK8JetpfBoostedDSVBTag", &AK8JetpfBoostedDSVBTag, &b_AK8JetpfBoostedDSVBTag);
    Run_Tree->SetBranchAddress("AK8JetCSV", &AK8JetCSV, &b_AK8JetCSV);
    Run_Tree->SetBranchAddress("AK8JetJECUnc", &AK8JetJECUnc, &b_AK8JetJECUnc);
    Run_Tree->SetBranchAddress("AK8JetL2L3corr", &AK8JetL2L3corr, &b_AK8JetL2L3corr);
    Run_Tree->SetBranchAddress("AK8puppiPt", &AK8puppiPt, &b_AK8puppiPt);
    Run_Tree->SetBranchAddress("AK8puppiMass", &AK8puppiMass, &b_AK8puppiMass);
    Run_Tree->SetBranchAddress("AK8puppiEta", &AK8puppiEta, &b_AK8puppiEta);
    Run_Tree->SetBranchAddress("AK8puppiPhi", &AK8puppiPhi, &b_AK8puppiPhi);
    Run_Tree->SetBranchAddress("AK8puppiSDL2L3corr", &AK8puppiSDL2L3corr, &b_AK8puppiSDL2L3corr);
    Run_Tree->SetBranchAddress("AK8puppiSDMass", &AK8puppiSDMass, &b_AK8puppiSDMass);
    Run_Tree->SetBranchAddress("AK8puppiSDMassL2L3Corr", &AK8puppiSDMassL2L3Corr, &b_AK8puppiSDMassL2L3Corr);
    Run_Tree->SetBranchAddress("AK8JetPartonID", &AK8JetPartonID, &b_AK8JetPartonID);
    Run_Tree->SetBranchAddress("AK8JetHadFlvr", &AK8JetHadFlvr, &b_AK8JetHadFlvr);
    Run_Tree->SetBranchAddress("nAK8SDSJ", &nAK8SDSJ, &b_nAK8SDSJ);
    Run_Tree->SetBranchAddress("AK8SDSJPt", &AK8SDSJPt, &b_AK8SDSJPt);
    Run_Tree->SetBranchAddress("AK8SDSJEta", &AK8SDSJEta, &b_AK8SDSJEta);
    Run_Tree->SetBranchAddress("AK8SDSJPhi", &AK8SDSJPhi, &b_AK8SDSJPhi);
    Run_Tree->SetBranchAddress("AK8SDSJMass", &AK8SDSJMass, &b_AK8SDSJMass);
    Run_Tree->SetBranchAddress("AK8SDSJE", &AK8SDSJE, &b_AK8SDSJE);
    Run_Tree->SetBranchAddress("AK8SDSJCharge", &AK8SDSJCharge, &b_AK8SDSJCharge);
    Run_Tree->SetBranchAddress("AK8SDSJFlavour", &AK8SDSJFlavour, &b_AK8SDSJFlavour);
    Run_Tree->SetBranchAddress("AK8SDSJCSV", &AK8SDSJCSV, &b_AK8SDSJCSV);
    Run_Tree->SetBranchAddress("nAK8puppiSDSJ", &nAK8puppiSDSJ, &b_nAK8puppiSDSJ);
    Run_Tree->SetBranchAddress("AK8puppiSDSJPt", &AK8puppiSDSJPt, &b_AK8puppiSDSJPt);
    Run_Tree->SetBranchAddress("AK8puppiSDSJEta", &AK8puppiSDSJEta, &b_AK8puppiSDSJEta);
    Run_Tree->SetBranchAddress("AK8puppiSDSJPhi", &AK8puppiSDSJPhi, &b_AK8puppiSDSJPhi);
    Run_Tree->SetBranchAddress("AK8puppiSDSJMass", &AK8puppiSDSJMass, &b_AK8puppiSDSJMass);
    Run_Tree->SetBranchAddress("AK8puppiSDSJE", &AK8puppiSDSJE, &b_AK8puppiSDSJE);
    Run_Tree->SetBranchAddress("AK8puppiSDSJCharge", &AK8puppiSDSJCharge, &b_AK8puppiSDSJCharge);
    Run_Tree->SetBranchAddress("AK8puppiSDSJFlavour", &AK8puppiSDSJFlavour, &b_AK8puppiSDSJFlavour);
    Run_Tree->SetBranchAddress("AK8puppiSDSJCSV", &AK8puppiSDSJCSV, &b_AK8puppiSDSJCSV);
    
    
    //########################################   MET Info
    Run_Tree->SetBranchAddress("pfMET",&pfMET);
    //       Run_Tree->SetBranchAddress("pfMET_T1JESUp",&met_JESUp);
    //       Run_Tree->SetBranchAddress("pfMET_T1JESDo",&met_JESDown);
    //       Run_Tree->SetBranchAddress("pfMET_T1UESUp",&met_UESUp);
    //       Run_Tree->SetBranchAddress("pfMET_T1UESDo",&met_UESDown);
    Run_Tree->SetBranchAddress("met_JESUp",&met_JESUp);
    Run_Tree->SetBranchAddress("met_JESDown",&met_JESDown);
    Run_Tree->SetBranchAddress("met_UESUp",&met_UESUp);
    Run_Tree->SetBranchAddress("met_UESDown",&met_UESDown);
    
    
    Run_Tree->SetBranchAddress("pfMETPhi",&pfMETPhi);
    //       Run_Tree->SetBranchAddress("pfMETPhi_T1JESUp",&metphi_JESUp);
    //       Run_Tree->SetBranchAddress("pfMETPhi_T1JESDo",&metphi_JESDown);
    //       Run_Tree->SetBranchAddress("pfMETPhi_T1UESUp",&metphi_UESUp);
    //       Run_Tree->SetBranchAddress("pfMETPhi_T1UESDo",&metphi_UESDown);
    Run_Tree->SetBranchAddress("metphi_JESUp",&metphi_JESUp);
    Run_Tree->SetBranchAddress("metphi_JESDown",&metphi_JESDown);
    Run_Tree->SetBranchAddress("metphi_UESUp",&metphi_UESUp);
    Run_Tree->SetBranchAddress("metphi_UESDown",&metphi_UESDown);
    
    
   Run_Tree->SetBranchAddress("met_reso_Up", &met_reso_Up);
   Run_Tree->SetBranchAddress("met_reso_Down", &met_reso_Down);
   Run_Tree->SetBranchAddress("met_resp_Up", &met_resp_Up);
   Run_Tree->SetBranchAddress("met_resp_Down", &met_resp_Down);
   Run_Tree->SetBranchAddress("metphi_reso_Up", &metphi_reso_Up);
   Run_Tree->SetBranchAddress("metphi_reso_Down", &metphi_reso_Down);
   Run_Tree->SetBranchAddress("metphi_resp_Up", &metphi_resp_Up);
   Run_Tree->SetBranchAddress("metphi_resp_Down", &metphi_resp_Down);
   
    
    Run_Tree->SetBranchAddress("metFilters",&metFilters);
    Run_Tree->SetBranchAddress("genHT",&genHT);
    
    //    Run_Tree->SetBranchAddress("pdfSystWeight",&pdfSystWeight);
    //    Run_Tree->SetBranchAddress("pdfSystWeightId",&pdfSystWeightId);
    //    Run_Tree->SetBranchAddress("pdfWeight",&pdfWeight);
    
    
    
    //########################################   Boosted Tau
    //       Run_Tree->SetBranchAddress("nBoostedTau",&nBoostedTau);
    //       Run_Tree->SetBranchAddress("boostedTauPt",&boostedTauPt);
    //       Run_Tree->SetBranchAddress("boostedTauEta",&boostedTauEta);
    //       Run_Tree->SetBranchAddress("boostedTauPhi",&boostedTauPhi);
    //       Run_Tree->SetBranchAddress("boostedTauMass",&boostedTauMass);
    //       Run_Tree->SetBranchAddress("boostedTauDecayMode",&boostedTauDecayMode);
    //       Run_Tree->SetBranchAddress("boostedTauCharge",&boostedTauCharge);
    //       Run_Tree->SetBranchAddress("boostedTauByLooseIsolationMVArun2v2DBoldDMwLT",&boostedTauByLooseIsolationMVArun2v2DBoldDMwLT);
    //
    //       Run_Tree->SetBranchAddress("boostedTaupfTausDiscriminationByDecayModeFinding",&boostedTaupfTausDiscriminationByDecayModeFinding);
    //       Run_Tree->SetBranchAddress("boostedTauByMVA6VLooseElectronRejection",&boostedTauByMVA6VLooseElectronRejection);
    //       Run_Tree->SetBranchAddress("boostedTauByMVA6TightElectronRejection",&boostedTauByMVA6TightElectronRejection);
    //       Run_Tree->SetBranchAddress("boostedTauByTightMuonRejection3",&boostedTauByTightMuonRejection3);
    //       Run_Tree->SetBranchAddress("boostedTauByLooseMuonRejection3",&boostedTauByLooseMuonRejection3);
    //
    //
    //       Run_Tree->SetBranchAddress("boostedTauByTightIsolationMVArun2v1DBoldDMwLT",&boostedTauByTightIsolationMVArun2v1DBoldDMwLT);
    //       Run_Tree->SetBranchAddress("boostedTauByMediumIsolationMVArun2v1DBoldDMwLT",&boostedTauByMediumIsolationMVArun2v1DBoldDMwLT);
    //       Run_Tree->SetBranchAddress("boostedTauByLooseIsolationMVArun2v1DBoldDMwLT",&boostedTauByLooseIsolationMVArun2v1DBoldDMwLT);
    //       Run_Tree->SetBranchAddress("boostedTauByVLooseIsolationMVArun2v1DBoldDMwLT",&boostedTauByVLooseIsolationMVArun2v1DBoldDMwLT);
    //
    //       Run_Tree->SetBranchAddress("boostedTauByIsolationMVArun2v1DBoldDMwLTraw",&boostedTauByIsolationMVArun2v1DBoldDMwLTraw);
    //       Run_Tree->SetBranchAddress("boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits",&boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits);
    //
    //       Run_Tree->SetBranchAddress("boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits",&boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits);
    //       Run_Tree->SetBranchAddress("boostedTauChargedIsoPtSum",&boostedTauChargedIsoPtSum);
    //
    //       Run_Tree->SetBranchAddress("boostedTauNeutralIsoPtSum"  ,&boostedTauNeutralIsoPtSum);
    
    
    //       Run_Tree->SetBranchAddress("taudaugPt",&taudaugPt);
    //       Run_Tree->SetBranchAddress("taudaugEta",&taudaugEta);
    //       Run_Tree->SetBranchAddress("taudaugPhi",&taudaugPhi);
    //       Run_Tree->SetBranchAddress("taudaugMass",&taudaugMass);
    //       Run_Tree->SetBranchAddress("numGenTau",&numGenTau);
    //
    //
    //
    Run_Tree->SetBranchAddress("era", &era);
    Run_Tree->SetBranchAddress("met_px", &met_px);
    Run_Tree->SetBranchAddress("met_py", &met_py);
    //    Run_Tree->SetBranchAddress("met", &met);
    //    Run_Tree->SetBranchAddress("metphi", &metphi);
    Run_Tree->SetBranchAddress("m_1", &m_1);
    Run_Tree->SetBranchAddress("px_1", &px_1);
    Run_Tree->SetBranchAddress("py_1", &py_1);
    Run_Tree->SetBranchAddress("pz_1", &pz_1);
    Run_Tree->SetBranchAddress("e_1", &e_1);
    Run_Tree->SetBranchAddress("pt_1", &pt_1);
    Run_Tree->SetBranchAddress("phi_1", &phi_1);
    Run_Tree->SetBranchAddress("eta_1", &eta_1);
    Run_Tree->SetBranchAddress("m_2", &m_2);
    Run_Tree->SetBranchAddress("px_2", &px_2);
    Run_Tree->SetBranchAddress("py_2", &py_2);
    Run_Tree->SetBranchAddress("pz_2", &pz_2);
    Run_Tree->SetBranchAddress("e_2", &e_2);
    Run_Tree->SetBranchAddress("pt_2", &pt_2);
    Run_Tree->SetBranchAddress("phi_2", &phi_2);
    Run_Tree->SetBranchAddress("eta_2", &eta_2);
    Run_Tree->SetBranchAddress("metcov00", &metcov00);
    Run_Tree->SetBranchAddress("metcov01", &metcov01);
    Run_Tree->SetBranchAddress("metcov10", &metcov10);
    Run_Tree->SetBranchAddress("metcov11", &metcov11);
    Run_Tree->SetBranchAddress("decayMode2", &decayMode2);
    Run_Tree->SetBranchAddress("m_sv", &m_sv);
    Run_Tree->SetBranchAddress("pt_sv", &pt_sv);
    
    Run_Tree->SetBranchAddress("lepIndex", &lepIndex);
    Run_Tree->SetBranchAddress("tauIndex", &tauIndex);
    Run_Tree->SetBranchAddress("decayMode1", &decayMode1);
    Run_Tree->SetBranchAddress("leadtauIndex", &leadtauIndex);
    Run_Tree->SetBranchAddress("subtauIndex", &subtauIndex);
    //
    //
    //    Run_Tree->SetBranchAddress("boostedTauSignalPFCands"  ,&boostedTauSignalPFCands);
    //    Run_Tree->SetBranchAddress("boostedTauSignalPFGammaCands"  ,&boostedTauSignalPFGammaCands);
    //    Run_Tree->SetBranchAddress("boostedTauIsolationPFCands"  ,&boostedTauIsolationPFCands);
    //    Run_Tree->SetBranchAddress("boostedTauIsolationPFGammaCands"  ,&boostedTauIsolationPFGammaCands);
    //
    
    return Run_Tree;
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
                
                if (syst == "ttbarShape_Up") {
                    return (2 * ttbar_scale - 1);  // 2*√[e^(..)*e^(..)] - 1
                } else if (syst == "ttbarShape_Down") {
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
int numBJets( float BJetPtCut, float CSVCut){
    int numBJet=0;
    for (int ijet= 0 ; ijet < nJet ; ijet++){
        if (jetPFLooseId->at(ijet) > 0.5 && jetPt->at(ijet) > BJetPtCut && fabs(jetEta->at(ijet)) < 2.4  &&
            jetDeepCSVTags_b->at(ijet) >  CSVCut)
            //         jetCSV2BJetTags->at(ijet) >  CSVCut)
            numBJet++;
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
float getST( float SimpleJetPtCut){
    float ST=0;
    for (int ijet= 0 ; ijet < nJet ; ijet++){
        if (jetPFLooseId->at(ijet) > 0.5 && jetPt->at(ijet) > SimpleJetPtCut && fabs(jetEta->at(ijet)) < 3.0 )
            ST += jetPt->at(ijet);
    }
    return ST;
}

//###########       MHT   ###########################################################
float getMHT( float SimpleJetPtCut){
    float MHT_x=0;
    float MHT_y=0;
    for (int ijet= 0 ; ijet < nJet ; ijet++){
        if (jetPFLooseId->at(ijet) > 0.5 && jetPt->at(ijet) > SimpleJetPtCut && fabs(jetEta->at(ijet)) < 5.0 )
            MHT_x += jetPt->at(ijet)*cos(jetPhi->at(ijet));
        MHT_y += jetPt->at(ijet)*sin(jetPhi->at(ijet));
    }
    
    return sqrt(MHT_x*MHT_x + MHT_y*MHT_y);
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


#endif
