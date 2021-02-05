//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Mar 23 19:33:46 2020 by ROOT version 6.16/00
// from TTree mutau_tree/Event data (tag V09_04_13_01)
// found on file: ggH125.root
//////////////////////////////////////////////////////////

#ifndef boostHTT_h
#define boostHTT_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "TString.h"
#include "vector"
#include "vector"
#include "vector"
#include "vector"

using namespace std;
// Fixed size dimensions of array or collections stored in the TTree if any.

// Declaration of leaf types
Int_t           run;
Long64_t        event;
Int_t           lumis;
Bool_t          isData;
Int_t           nVtx;
Int_t           nGoodVtx;
Bool_t          isPVGood;
Float_t         vtx;
Float_t         vty;
Float_t         vtz;
Float_t         rho;
Float_t         rhoCentral;
Double_t        L1ECALPrefire;
Double_t        L1ECALPrefireUp;
Double_t        L1ECALPrefireDown;
ULong64_t       HLTEleMuX;
ULong64_t       HLTPho;
ULong64_t       HLTPhoRejectedByPS;
ULong64_t       HLTJet;
ULong64_t       HLTEleMuXIsPrescaled;
ULong64_t       HLTPhoIsPrescaled;
ULong64_t       HLTJetIsPrescaled;
vector<float>   *pdf;
Float_t         pthat;
Float_t         processID;
Float_t         genWeight;
Float_t         genHT;
Float_t         genPho1;
Float_t         genPho2;
TString         *EventTag;
Int_t           nPUInfo;
vector<int>     *nPU;
vector<int>     *puBX;
vector<float>   *puTrue;
Int_t           nLHE;
vector<int>     *lhePID;
vector<float>   *lhePx;
vector<float>   *lhePy;
vector<float>   *lhePz;
vector<float>   *lheE;
Int_t           nMC;
vector<int>     *mcPID;
vector<float>   *mcVtx;
vector<float>   *mcVty;
vector<float>   *mcVtz;
vector<float>   *mcPt;
vector<float>   *mcMass;
vector<float>   *mcEta;
vector<float>   *mcPhi;
vector<float>   *mcE;
vector<float>   *mcEt;
vector<int>     *mcGMomPID;
vector<int>     *mcMomPID;
vector<float>   *mcMomPt;
vector<float>   *mcMomMass;
vector<float>   *mcMomEta;
vector<float>   *mcMomPhi;
vector<unsigned short> *mcStatusFlag;
vector<int>     *mcParentage;
vector<int>     *mcStatus;
vector<float>   *mcCalIsoDR03;
vector<float>   *mcTrkIsoDR03;
vector<float>   *mcCalIsoDR04;
vector<float>   *mcTrkIsoDR04;
Float_t         genMET;
Float_t         genMETPhi;
Int_t           metFilters;
Float_t         pfMET;
Float_t         pfMETPhi;
Int_t           recoil;
Float_t         pfMetNoRecoil;
Float_t         pfMetPhiNoRecoil;
Float_t         met_px;
Float_t         met_py;
Float_t         metcov00;
Float_t         metcov01;
Float_t         metcov10;
Float_t         metcov11;
Float_t         pfMET_T1JESUp;
Float_t         pfMET_T1JESDo;
Float_t         pfMET_T1UESUp;
Float_t         pfMET_T1UESDo;
Float_t         pfMETPhi_T1JESUp;
Float_t         pfMETPhi_T1JESDo;
Float_t         pfMETPhi_T1UESUp;
Float_t         pfMETPhi_T1UESDo;
Float_t         met_JESUp;
Float_t         met_JESDown;
Float_t         met_UESUp;
Float_t         met_UESDown;
Float_t         metphi_JESUp;
Float_t         metphi_JESDown;
Float_t         metphi_UESUp;
Float_t         metphi_UESDown;
Float_t         pfmetcorr_ex_UESUp;
Float_t         pfmetcorr_ey_UESUp;
Float_t         pfmetcorr_ex_UESDown;
Float_t         pfmetcorr_ey_UESDown;
Float_t         pfmetcorr_ex_JESUp;
Float_t         pfmetcorr_ey_JESUp;
Float_t         pfmetcorr_ex_JESDown;
Float_t         pfmetcorr_ey_JESDown;
Int_t           nEle;
vector<int>     *eleCharge;
vector<int>     *eleChargeConsistent;
vector<float>   *eleEn;
vector<float>   *eleSCEn;
vector<float>   *eleEcalEn;
vector<float>   *eleESEnP1;
vector<float>   *eleESEnP2;
vector<float>   *eleD0;
vector<float>   *eleDz;
vector<float>   *eleSIP;
vector<float>   *elePt;
vector<float>   *elePtError;
vector<float>   *eleEta;
vector<float>   *elePhi;
vector<float>   *eleR9;
vector<float>   *eleCalibPt;
vector<float>   *eleCalibEn;
vector<float>   *eleSCEta;
vector<float>   *eleSCPhi;
vector<float>   *eleSCRawEn;
vector<float>   *eleSCEtaWidth;
vector<float>   *eleSCPhiWidth;
vector<float>   *eleHoverE;
vector<float>   *eleEoverP;
vector<float>   *eleEoverPout;
vector<float>   *eleEoverPInv;
vector<float>   *eleBrem;
vector<float>   *eledEtaAtVtx;
vector<float>   *eledPhiAtVtx;
vector<float>   *eleSigmaIEtaIEtaFull5x5;
vector<float>   *eleSigmaIPhiIPhiFull5x5;
vector<int>     *eleConvVeto;
vector<int>     *eleMissHits;
vector<float>   *eleESEffSigmaRR;
vector<float>   *elePFChIso;
vector<float>   *elePFPhoIso;
vector<float>   *elePFNeuIso;
vector<float>   *elePFPUIso;
vector<float>   *elePFClusEcalIso;
vector<float>   *elePFClusHcalIso;
vector<float>   *eleIDMVAIso;
vector<float>   *eleIDMVANoIso;
vector<float>   *eleR9Full5x5;
vector<int>     *eleEcalDrivenSeed;
vector<float>   *eleTrkdxy;
vector<float>   *eleKFHits;
vector<float>   *eleKFChi2;
vector<float>   *eleGSFChi2;
vector<vector<float> > *eleGSFPt;
vector<vector<float> > *eleGSFEta;
vector<vector<float> > *eleGSFPhi;
vector<vector<float> > *eleGSFCharge;
vector<vector<int> > *eleGSFHits;
vector<vector<int> > *eleGSFMissHits;
vector<vector<int> > *eleGSFNHitsMax;
vector<vector<float> > *eleGSFVtxProb;
vector<vector<float> > *eleGSFlxyPV;
vector<vector<float> > *eleGSFlxyBS;
vector<ULong64_t> *eleFiredSingleTrgs;
vector<ULong64_t> *eleFiredDoubleTrgs;
vector<ULong64_t> *eleFiredL1Trgs;
vector<unsigned short> *eleIDbit;
vector<float>   *eleScale_stat_up;
vector<float>   *eleScale_stat_dn;
vector<float>   *eleScale_syst_up;
vector<float>   *eleScale_syst_dn;
vector<float>   *eleScale_gain_up;
vector<float>   *eleScale_gain_dn;
vector<float>   *eleResol_rho_up;
vector<float>   *eleResol_rho_dn;
vector<float>   *eleResol_phi_up;
vector<float>   *eleResol_phi_dn;
Int_t           nMu;
vector<float>   *muPt;
vector<float>   *muEn;
vector<float>   *muEta;
vector<float>   *muPhi;
vector<int>     *muCharge;
vector<int>     *muType;
vector<int>     *muIDbit;
vector<float>   *muD0;
vector<float>   *muDz;
vector<float>   *muSIP;
vector<float>   *muChi2NDF;
vector<float>   *muInnerD0;
vector<float>   *muInnerDz;
vector<int>     *muTrkLayers;
vector<int>     *muPixelLayers;
vector<int>     *muPixelHits;
vector<int>     *muMuonHits;
vector<int>     *muStations;
vector<int>     *muMatches;
vector<int>     *muTrkQuality;
vector<float>   *muIsoTrk;
vector<float>   *muPFChIso;
vector<float>   *muPFPhoIso;
vector<float>   *muPFNeuIso;
vector<float>   *muPFPUIso;
vector<float>   *muPFChIso03;
vector<float>   *muPFPhoIso03;
vector<float>   *muPFNeuIso03;
vector<float>   *muPFPUIso03;
vector<ULong64_t> *muFiredTrgs;
vector<ULong64_t> *muFiredL1Trgs;
vector<float>   *muInnervalidFraction;
vector<float>   *musegmentCompatibility;
vector<float>   *muchi2LocalPosition;
vector<float>   *mutrkKink;
vector<float>   *muBestTrkPtError;
vector<float>   *muBestTrkPt;
vector<int>     *muBestTrkType;
Int_t           nJet;
vector<float>   *jetPt;
vector<float>   *jetEn;
vector<float>   *jetEta;
vector<float>   *jetPhi;
vector<float>   *jetRawPt;
vector<float>   *jetRawEn;
vector<float>   *jetMt;
vector<float>   *jetArea;
vector<float>   *jetLeadTrackPt;
vector<float>   *jetLeadTrackEta;
vector<float>   *jetLeadTrackPhi;
vector<int>     *jetLepTrackPID;
vector<float>   *jetLepTrackPt;
vector<float>   *jetLepTrackEta;
vector<float>   *jetLepTrackPhi;
vector<float>   *jetCSV2BJetTags;
vector<float>   *jetDeepCSVTags_b;
vector<float>   *jetDeepCSVTags_bb;
vector<float>   *jetDeepCSVTags_c;
vector<float>   *jetDeepCSVTags_udsg;
vector<int>     *jetPartonID;
vector<int>     *jetHadFlvr;
vector<float>   *jetGenJetEn;
vector<float>   *jetGenJetPt;
vector<float>   *jetGenJetEta;
vector<float>   *jetGenJetPhi;
vector<int>     *jetGenPartonID;
vector<float>   *jetGenEn;
vector<float>   *jetGenPt;
vector<float>   *jetGenEta;
vector<float>   *jetGenPhi;
vector<int>     *jetGenPartonMomID;
vector<float>   *jetP4Smear;
vector<float>   *jetP4SmearUp;
vector<float>   *jetP4SmearDo;
vector<bool>    *jetPFLooseId;
vector<int>     *jetID;
vector<float>   *jetPUID;
vector<int>     *jetPUFullID;
vector<float>   *jetJECUnc;
vector<ULong64_t> *jetFiredTrgs;
vector<float>   *jetCHF;
vector<float>   *jetNHF;
vector<float>   *jetCEF;
vector<float>   *jetNEF;
vector<int>     *jetNCH;
vector<int>     *jetNNP;
vector<float>   *jetMUF;
vector<float>   *jetVtxPt;
vector<float>   *jetVtxMass;
vector<float>   *jetVtxNtrks;
vector<float>   *jetVtx3DVal;
vector<float>   *jetVtx3DSig;
Int_t           nBoostedTau;
Int_t           nBoostedTauOrig;
vector<bool>    *boostedTaupfTausDiscriminationByDecayModeFinding;
vector<bool>    *boostedTaupfTausDiscriminationByDecayModeFindingNewDMs;
vector<bool>    *boostedTauByMVA6LooseElectronRejection;
vector<bool>    *boostedTauByMVA6TightElectronRejection;
vector<bool>    *boostedTauByLooseMuonRejection3;
vector<bool>    *boostedTauByTightMuonRejection3;
vector<bool>    *boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits;
vector<bool>    *boostedTauByTightCombinedIsolationDeltaBetaCorr3Hits;
vector<float>   *boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits;
vector<float>   *boostedTauByIsolationMVArun2v1DBoldDMwLTraw;
vector<float>   *boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew;
vector<bool>    *boostedTauByTightIsolationMVArun2v1DBoldDMwLT;
vector<bool>    *boostedTauByTightIsolationMVArun2v1DBoldDMwLTNew;
vector<bool>    *boostedTauByVLooseIsolationMVArun2v1DBoldDMwLTNew;
vector<bool>    *boostedTauByMediumIsolationMVArun2v1DBoldDMwLTNew;
vector<bool>    *boostedTauByVTightIsolationMVArun2v1DBoldDMwLTNew;
vector<bool>    *boostedTauByLooseIsolationMVArun2v1DBoldDMwLT;
vector<bool>    *boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNew;
vector<float>   *boostedTauEta;
vector<float>   *boostedTauPhi;
vector<float>   *boostedTauPt;
vector<float>   *boostedTauEt;
vector<float>   *boostedTauCharge;
vector<float>   *boostedTauP;
vector<float>   *boostedTauPx;
vector<float>   *boostedTauPy;
vector<float>   *boostedTauPz;
vector<float>   *boostedTauVz;
vector<float>   *boostedTauEnergy;
vector<float>   *boostedTauMass;
vector<float>   *boostedTauDxy;
vector<float>   *boostedTauZImpact;
vector<int>     *boostedTauDecayMode;
vector<bool>    *boostedTauLeadChargedHadronExists;
vector<float>   *boostedTauLeadChargedHadronEta;
vector<float>   *boostedTauLeadChargedHadronPhi;
vector<float>   *boostedTauLeadChargedHadronPt;
vector<float>   *boostedTauChargedIsoPtSum;
vector<float>   *boostedTauChargedIsoPtSumNoOverLap;
vector<float>   *boostedTauNeutralIsoPtSum;
vector<float>   *boostedTauNeutralIsoPtSumNoOverLap;
vector<float>   *boostedTauPuCorrPtSum;
vector<int>     *boostedTauNumSignalPFChargedHadrCands;
vector<int>     *boostedTauNumSignalPFNeutrHadrCands;
vector<int>     *boostedTauNumSignalPFGammaCands;
vector<int>     *boostedTauNumSignalPFCands;
vector<int>     *boostedTauNumIsolationPFChargedHadrCands;
vector<int>     *boostedTauNumIsolationPFNeutrHadrCands;
vector<int>     *boostedTauNumIsolationPFGammaCands;
vector<int>     *boostedTauNumIsolationPFCands;
vector<float>   *boostedTaufootprintCorrection;
vector<float>   *boostedTauphotonPtSumOutsideSignalCone;
vector<float>   *boostedTaudz;
vector<float>   *boostedTaudxy;
vector<vector<float> > *boostedTauSignalPFCands;
vector<vector<float> > *boostedTauSignalPFGammaCands;
vector<vector<float> > *boostedTauIsolationPFCands;
vector<vector<float> > *boostedTauIsolationPFGammaCands;
vector<float>   *boostedTauByDeepTau2017v1VSjetraw;
vector<float>   *boostedTauByDeepTau2017v1VSeraw;
vector<float>   *boostedTauByDeepTau2017v1VSmuraw;
vector<bool>    *boostedTaubyVVVLooseDeepTau2017v1VSjet;
vector<bool>    *boostedTaubyVLooseDeepTau2017v1VSjet;
vector<bool>    *boostedTaubyLooseDeepTau2017v1VSjet;
vector<bool>    *boostedTaubyMediumDeepTau2017v1VSjet;
vector<bool>    *boostedTaubyTightDeepTau2017v1VSjet;
vector<bool>    *boostedTaubyVVTightDeepTau2017v1VSjet;
vector<bool>    *boostedTaubyVVVLooseDeepTau2017v1VSe;
vector<bool>    *boostedTaubyLooseDeepTau2017v1VSe;
vector<bool>    *boostedTaubyTightDeepTau2017v1VSe;
vector<bool>    *boostedTaubyVVTightDeepTau2017v1VSe;
vector<bool>    *boostedTaubyVVVLooseDeepTau2017v1VSmu;
vector<bool>    *boostedTaubyLooseDeepTau2017v1VSmu;
vector<bool>    *boostedTaubyTightDeepTau2017v1VSmu;
vector<bool>    *boostedTaubyVVTightDeepTau2017v1VSmu;
vector<bool>    *boostedTauagainstElectronVLooseMVA62018;
vector<bool>    *boostedTauagainstElectronLooseMVA62018;
vector<bool>    *boostedTauagainstElectronTightMVA62018;
    Int_t           nAK8Jet;
   vector<float>   *AK8JetPt;
   vector<float>   *AK8JetEn;
   vector<float>   *AK8JetRawPt;
   vector<float>   *AK8JetRawEn;
   vector<float>   *AK8JetEta;
   vector<float>   *AK8JetPhi;
   vector<float>   *AK8JetMass;
   vector<float>   *AK8Jet_tau1;
   vector<float>   *AK8Jet_tau2;
   vector<float>   *AK8Jet_tau3;
   vector<int>     *AK8Jetnconstituents;
   vector<bool>    *AK8JetPFLooseId;
   vector<bool>    *AK8JetPFTightLepVetoId;
   vector<float>   *AK8JetSoftDropMass;
   vector<float>   *AK8JetSoftDropMassCorr;
   vector<float>   *AK8JetPrunedMass;
   vector<float>   *AK8JetPrunedMassCorr;
   vector<float>   *AK8JetpfBoostedDSVBTag;
   vector<float>   *AK8JetCSV;
   vector<float>   *AK8JetJECUnc;
   vector<float>   *AK8JetL2L3corr;
   vector<float>   *AK8puppiPt;
   vector<float>   *AK8puppiMass;
   vector<float>   *AK8puppiEta;
   vector<float>   *AK8puppiPhi;
   vector<float>   *AK8puppiSDL2L3corr;
   vector<float>   *AK8puppiSDMass;
   vector<float>   *AK8puppiSDMassL2L3Corr;
   vector<int>     *AK8JetPartonID;
   vector<int>     *AK8JetHadFlvr;
   vector<int>     *nAK8SDSJ;
   vector<vector<float> > *AK8SDSJPt;
   vector<vector<float> > *AK8SDSJEta;
   vector<vector<float> > *AK8SDSJPhi;
   vector<vector<float> > *AK8SDSJMass;
   vector<vector<float> > *AK8SDSJE;
   vector<vector<int> > *AK8SDSJCharge;
   vector<vector<int> > *AK8SDSJFlavour;
   vector<vector<float> > *AK8SDSJCSV;
   vector<int>     *nAK8puppiSDSJ;
   vector<vector<float> > *AK8puppiSDSJPt;
   vector<vector<float> > *AK8puppiSDSJEta;
   vector<vector<float> > *AK8puppiSDSJPhi;
   vector<vector<float> > *AK8puppiSDSJMass;
   vector<vector<float> > *AK8puppiSDSJE;
   vector<vector<int> > *AK8puppiSDSJCharge;
   vector<vector<int> > *AK8puppiSDSJFlavour;
   vector<vector<float> > *AK8puppiSDSJCSV;
   Float_t         met_reso_Up;
   Float_t         met_reso_Down;
   Float_t         met_resp_Up;
   Float_t         met_resp_Down;
   Float_t         metphi_reso_Up;
   Float_t         metphi_reso_Down;
   Float_t         metphi_resp_Up;
   Float_t         metphi_resp_Down;



// List of branches
TBranch        *b_run;   //!
TBranch        *b_event;   //!
TBranch        *b_lumis;   //!
TBranch        *b_isData;   //!
TBranch        *b_nVtx;   //!
TBranch        *b_nGoodVtx;   //!
TBranch        *b_isPVGood;   //!
TBranch        *b_vtx;   //!
TBranch        *b_vty;   //!
TBranch        *b_vtz;   //!
TBranch        *b_rho;   //!
TBranch        *b_rhoCentral;   //!
TBranch        *b_L1ECALPrefire;   //!
TBranch        *b_L1ECALPrefireUp;   //!
TBranch        *b_L1ECALPrefireDown;   //!
TBranch        *b_HLTEleMuX;   //!
TBranch        *b_HLTPho;   //!
TBranch        *b_HLTPhoRejectedByPS;   //!
TBranch        *b_HLTJet;   //!
TBranch        *b_HLTEleMuXIsPrescaled;   //!
TBranch        *b_HLTPhoIsPrescaled;   //!
TBranch        *b_HLTJetIsPrescaled;   //!
TBranch        *b_pdf;   //!
TBranch        *b_pthat;   //!
TBranch        *b_processID;   //!
TBranch        *b_genWeight;   //!
TBranch        *b_genHT;   //!
TBranch        *b_genPho1;   //!
TBranch        *b_genPho2;   //!
TBranch        *b_EventTag;   //!
TBranch        *b_nPUInfo;   //!
TBranch        *b_nPU;   //!
TBranch        *b_puBX;   //!
TBranch        *b_puTrue;   //!
TBranch        *b_nLHE;   //!
TBranch        *b_lhePID;   //!
TBranch        *b_lhePx;   //!
TBranch        *b_lhePy;   //!
TBranch        *b_lhePz;   //!
TBranch        *b_lheE;   //!
TBranch        *b_nMC;   //!
TBranch        *b_mcPID;   //!
TBranch        *b_mcVtx;   //!
TBranch        *b_mcVty;   //!
TBranch        *b_mcVtz;   //!
TBranch        *b_mcPt;   //!
TBranch        *b_mcMass;   //!
TBranch        *b_mcEta;   //!
TBranch        *b_mcPhi;   //!
TBranch        *b_mcE;   //!
TBranch        *b_mcEt;   //!
TBranch        *b_mcGMomPID;   //!
TBranch        *b_mcMomPID;   //!
TBranch        *b_mcMomPt;   //!
TBranch        *b_mcMomMass;   //!
TBranch        *b_mcMomEta;   //!
TBranch        *b_mcMomPhi;   //!
TBranch        *b_mcStatusFlag;   //!
TBranch        *b_mcParentage;   //!
TBranch        *b_mcStatus;   //!
TBranch        *b_mcCalIsoDR03;   //!
TBranch        *b_mcTrkIsoDR03;   //!
TBranch        *b_mcCalIsoDR04;   //!
TBranch        *b_mcTrkIsoDR04;   //!
TBranch        *b_genMET;   //!
TBranch        *b_genMETPhi;   //!
TBranch        *b_metFilters;   //!
TBranch        *b_pfMET;   //!
TBranch        *b_pfMETPhi;   //!
TBranch        *b_recoil;   //!
TBranch        *b_pfMetNoRecoil;   //!
TBranch        *b_pfMetPhiNoRecoil;   //!
TBranch        *b_met_px;   //!
TBranch        *b_met_py;   //!
TBranch        *b_metcov00;   //!
TBranch        *b_metcov01;   //!
TBranch        *b_metcov10;   //!
TBranch        *b_metcov11;   //!
TBranch        *b_pfMET_T1JESUp;   //!
TBranch        *b_pfMET_T1JESDo;   //!
TBranch        *b_pfMET_T1UESUp;   //!
TBranch        *b_pfMET_T1UESDo;   //!
TBranch        *b_pfMETPhi_T1JESUp;   //!
TBranch        *b_pfMETPhi_T1JESDo;   //!
TBranch        *b_pfMETPhi_T1UESUp;   //!
TBranch        *b_pfMETPhi_T1UESDo;   //!
TBranch        *b_met_JESUp;   //!
TBranch        *b_met_JESDown;   //!
TBranch        *b_met_UESUp;   //!
TBranch        *b_met_UESDown;   //!
TBranch        *b_metphi_JESUp;   //!
TBranch        *b_metphi_JESDown;   //!
TBranch        *b_metphi_UESUp;   //!
TBranch        *b_metphi_UESDown;   //!
TBranch        *b_pfmetcorr_ex_UESUp;   //!
TBranch        *b_pfmetcorr_ey_UESUp;   //!
TBranch        *b_pfmetcorr_ex_UESDown;   //!
TBranch        *b_pfmetcorr_ey_UESDown;   //!
TBranch        *b_pfmetcorr_ex_JESUp;   //!
TBranch        *b_pfmetcorr_ey_JESUp;   //!
TBranch        *b_pfmetcorr_ex_JESDown;   //!
TBranch        *b_pfmetcorr_ey_JESDown;   //!
TBranch        *b_nEle;   //!
TBranch        *b_eleCharge;   //!
TBranch        *b_eleChargeConsistent;   //!
TBranch        *b_eleEn;   //!
TBranch        *b_eleSCEn;   //!
TBranch        *b_eleEcalEn;   //!
TBranch        *b_eleESEnP1;   //!
TBranch        *b_eleESEnP2;   //!
TBranch        *b_eleD0;   //!
TBranch        *b_eleDz;   //!
TBranch        *b_eleSIP;   //!
TBranch        *b_elePt;   //!
TBranch        *b_elePtError;   //!
TBranch        *b_eleEta;   //!
TBranch        *b_elePhi;   //!
TBranch        *b_eleR9;   //!
TBranch        *b_eleCalibPt;   //!
TBranch        *b_eleCalibEn;   //!
TBranch        *b_eleSCEta;   //!
TBranch        *b_eleSCPhi;   //!
TBranch        *b_eleSCRawEn;   //!
TBranch        *b_eleSCEtaWidth;   //!
TBranch        *b_eleSCPhiWidth;   //!
TBranch        *b_eleHoverE;   //!
TBranch        *b_eleEoverP;   //!
TBranch        *b_eleEoverPout;   //!
TBranch        *b_eleEoverPInv;   //!
TBranch        *b_eleBrem;   //!
TBranch        *b_eledEtaAtVtx;   //!
TBranch        *b_eledPhiAtVtx;   //!
TBranch        *b_eleSigmaIEtaIEtaFull5x5;   //!
TBranch        *b_eleSigmaIPhiIPhiFull5x5;   //!
TBranch        *b_eleConvVeto;   //!
TBranch        *b_eleMissHits;   //!
TBranch        *b_eleESEffSigmaRR;   //!
TBranch        *b_elePFChIso;   //!
TBranch        *b_elePFPhoIso;   //!
TBranch        *b_elePFNeuIso;   //!
TBranch        *b_elePFPUIso;   //!
TBranch        *b_elePFClusEcalIso;   //!
TBranch        *b_elePFClusHcalIso;   //!
TBranch        *b_eleIDMVAIso;   //!
TBranch        *b_eleIDMVANoIso;   //!
TBranch        *b_eleR9Full5x5;   //!
TBranch        *b_eleEcalDrivenSeed;   //!
TBranch        *b_eleTrkdxy;   //!
TBranch        *b_eleKFHits;   //!
TBranch        *b_eleKFChi2;   //!
TBranch        *b_eleGSFChi2;   //!
TBranch        *b_eleGSFPt;   //!
TBranch        *b_eleGSFEta;   //!
TBranch        *b_eleGSFPhi;   //!
TBranch        *b_eleGSFCharge;   //!
TBranch        *b_eleGSFHits;   //!
TBranch        *b_eleGSFMissHits;   //!
TBranch        *b_eleGSFNHitsMax;   //!
TBranch        *b_eleGSFVtxProb;   //!
TBranch        *b_eleGSFlxyPV;   //!
TBranch        *b_eleGSFlxyBS;   //!
TBranch        *b_eleFiredSingleTrgs;   //!
TBranch        *b_eleFiredDoubleTrgs;   //!
TBranch        *b_eleFiredL1Trgs;   //!
TBranch        *b_eleIDbit;   //!
TBranch        *b_eleScale_stat_up;   //!
TBranch        *b_eleScale_stat_dn;   //!
TBranch        *b_eleScale_syst_up;   //!
TBranch        *b_eleScale_syst_dn;   //!
TBranch        *b_eleScale_gain_up;   //!
TBranch        *b_eleScale_gain_dn;   //!
TBranch        *b_eleResol_rho_up;   //!
TBranch        *b_eleResol_rho_dn;   //!
TBranch        *b_eleResol_phi_up;   //!
TBranch        *b_eleResol_phi_dn;   //!
TBranch        *b_nMu;   //!
TBranch        *b_muPt;   //!
TBranch        *b_muEn;   //!
TBranch        *b_muEta;   //!
TBranch        *b_muPhi;   //!
TBranch        *b_muCharge;   //!
TBranch        *b_muType;   //!
TBranch        *b_muIDbit;   //!
TBranch        *b_muD0;   //!
TBranch        *b_muDz;   //!
TBranch        *b_muSIP;   //!
TBranch        *b_muChi2NDF;   //!
TBranch        *b_muInnerD0;   //!
TBranch        *b_muInnerDz;   //!
TBranch        *b_muTrkLayers;   //!
TBranch        *b_muPixelLayers;   //!
TBranch        *b_muPixelHits;   //!
TBranch        *b_muMuonHits;   //!
TBranch        *b_muStations;   //!
TBranch        *b_muMatches;   //!
TBranch        *b_muTrkQuality;   //!
TBranch        *b_muIsoTrk;   //!
TBranch        *b_muPFChIso;   //!
TBranch        *b_muPFPhoIso;   //!
TBranch        *b_muPFNeuIso;   //!
TBranch        *b_muPFPUIso;   //!
TBranch        *b_muPFChIso03;   //!
TBranch        *b_muPFPhoIso03;   //!
TBranch        *b_muPFNeuIso03;   //!
TBranch        *b_muPFPUIso03;   //!
TBranch        *b_muFiredTrgs;   //!
TBranch        *b_muFiredL1Trgs;   //!
TBranch        *b_muInnervalidFraction;   //!
TBranch        *b_musegmentCompatibility;   //!
TBranch        *b_muchi2LocalPosition;   //!
TBranch        *b_mutrkKink;   //!
TBranch        *b_muBestTrkPtError;   //!
TBranch        *b_muBestTrkPt;   //!
TBranch        *b_muBestTrkType;   //!
TBranch        *b_nJet;   //!
TBranch        *b_jetPt;   //!
TBranch        *b_jetEn;   //!
TBranch        *b_jetEta;   //!
TBranch        *b_jetPhi;   //!
TBranch        *b_jetRawPt;   //!
TBranch        *b_jetRawEn;   //!
TBranch        *b_jetMt;   //!
TBranch        *b_jetArea;   //!
TBranch        *b_jetLeadTrackPt;   //!
TBranch        *b_jetLeadTrackEta;   //!
TBranch        *b_jetLeadTrackPhi;   //!
TBranch        *b_jetLepTrackPID;   //!
TBranch        *b_jetLepTrackPt;   //!
TBranch        *b_jetLepTrackEta;   //!
TBranch        *b_jetLepTrackPhi;   //!
TBranch        *b_jetCSV2BJetTags;   //!
TBranch        *b_jetDeepCSVTags_b;   //!
TBranch        *b_jetDeepCSVTags_bb;   //!
TBranch        *b_jetDeepCSVTags_c;   //!
TBranch        *b_jetDeepCSVTags_udsg;   //!
TBranch        *b_jetPartonID;   //!
TBranch        *b_jetHadFlvr;   //!
TBranch        *b_jetGenJetEn;   //!
TBranch        *b_jetGenJetPt;   //!
TBranch        *b_jetGenJetEta;   //!
TBranch        *b_jetGenJetPhi;   //!
TBranch        *b_jetGenPartonID;   //!
TBranch        *b_jetGenEn;   //!
TBranch        *b_jetGenPt;   //!
TBranch        *b_jetGenEta;   //!
TBranch        *b_jetGenPhi;   //!
TBranch        *b_jetGenPartonMomID;   //!
TBranch        *b_jetP4Smear;   //!
TBranch        *b_jetP4SmearUp;   //!
TBranch        *b_jetP4SmearDo;   //!
TBranch        *b_jetPFLooseId;   //!
TBranch        *b_jetID;   //!
TBranch        *b_jetPUID;   //!
TBranch        *b_jetPUFullID;   //!
TBranch        *b_jetJECUnc;   //!
TBranch        *b_jetFiredTrgs;   //!
TBranch        *b_jetCHF;   //!
TBranch        *b_jetNHF;   //!
TBranch        *b_jetCEF;   //!
TBranch        *b_jetNEF;   //!
TBranch        *b_jetNCH;   //!
TBranch        *b_jetNNP;   //!
TBranch        *b_jetMUF;   //!
TBranch        *b_jetVtxPt;   //!
TBranch        *b_jetVtxMass;   //!
TBranch        *b_jetVtxNtrks;   //!
TBranch        *b_jetVtx3DVal;   //!
TBranch        *b_jetVtx3DSig;   //!
TBranch        *b_nBoostedTau;   //!
TBranch        *b_nBoostedTauOrig;   //!
TBranch        *b_boostedTaupfTausDiscriminationByDecayModeFinding;   //!
TBranch        *b_boostedTaupfTausDiscriminationByDecayModeFindingNewDMs;   //!
TBranch        *b_boostedTauByMVA6LooseElectronRejection;   //!
TBranch        *b_boostedTauByMVA6TightElectronRejection;   //!
TBranch        *b_boostedTauByLooseMuonRejection3;   //!
TBranch        *b_boostedTauByTightMuonRejection3;   //!
TBranch        *b_boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits;   //!
TBranch        *b_boostedTauByTightCombinedIsolationDeltaBetaCorr3Hits;   //!
TBranch        *b_boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits;   //!
TBranch        *b_boostedTauByIsolationMVArun2v1DBoldDMwLTraw;   //!
TBranch        *b_boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew;   //!
TBranch        *b_boostedTauByTightIsolationMVArun2v1DBoldDMwLT;   //!
TBranch        *b_boostedTauByTightIsolationMVArun2v1DBoldDMwLTNew;   //!
TBranch        *b_boostedTauByVLooseIsolationMVArun2v1DBoldDMwLTNew;   //!
TBranch        *b_boostedTauByMediumIsolationMVArun2v1DBoldDMwLTNew;   //!
TBranch        *b_boostedTauByVTightIsolationMVArun2v1DBoldDMwLTNew;   //!
TBranch        *b_boostedTauByLooseIsolationMVArun2v1DBoldDMwLT;   //!
TBranch        *b_boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNew;   //!
TBranch        *b_boostedTauEta;   //!
TBranch        *b_boostedTauPhi;   //!
TBranch        *b_boostedTauPt;   //!
TBranch        *b_boostedTauEt;   //!
TBranch        *b_boostedTauCharge;   //!
TBranch        *b_boostedTauP;   //!
TBranch        *b_boostedTauPx;   //!
TBranch        *b_boostedTauPy;   //!
TBranch        *b_boostedTauPz;   //!
TBranch        *b_boostedTauVz;   //!
TBranch        *b_boostedTauEnergy;   //!
TBranch        *b_boostedTauMass;   //!
TBranch        *b_boostedTauDxy;   //!
TBranch        *b_boostedTauZImpact;   //!
TBranch        *b_boostedTauDecayMode;   //!
TBranch        *b_boostedTauLeadChargedHadronExists;   //!
TBranch        *b_boostedTauLeadChargedHadronEta;   //!
TBranch        *b_boostedTauLeadChargedHadronPhi;   //!
TBranch        *b_boostedTauLeadChargedHadronPt;   //!
TBranch        *b_boostedTauChargedIsoPtSum;   //!
TBranch        *b_boostedTauChargedIsoPtSumNoOverLap;   //!
TBranch        *b_boostedTauNeutralIsoPtSum;   //!
TBranch        *b_boostedTauNeutralIsoPtSumNoOverLap;   //!
TBranch        *b_boostedTauPuCorrPtSum;   //!
TBranch        *b_boostedTauNumSignalPFChargedHadrCands;   //!
TBranch        *b_boostedTauNumSignalPFNeutrHadrCands;   //!
TBranch        *b_boostedTauNumSignalPFGammaCands;   //!
TBranch        *b_boostedTauNumSignalPFCands;   //!
TBranch        *b_boostedTauNumIsolationPFChargedHadrCands;   //!
TBranch        *b_boostedTauNumIsolationPFNeutrHadrCands;   //!
TBranch        *b_boostedTauNumIsolationPFGammaCands;   //!
TBranch        *b_boostedTauNumIsolationPFCands;   //!
TBranch        *b_boostedTaufootprintCorrection;   //!
TBranch        *b_boostedTauphotonPtSumOutsideSignalCone;   //!
TBranch        *b_boostedTaudz;   //!
TBranch        *b_boostedTaudxy;   //!
TBranch        *b_boostedTauSignalPFCands;   //!
TBranch        *b_boostedTauSignalPFGammaCands;   //!
TBranch        *b_boostedTauIsolationPFCands;   //!
TBranch        *b_boostedTauIsolationPFGammaCands;   //!
TBranch        *b_boostedTauByDeepTau2017v1VSjetraw;   //!
TBranch        *b_boostedTauByDeepTau2017v1VSeraw;   //!
TBranch        *b_boostedTauByDeepTau2017v1VSmuraw;   //!
TBranch        *b_boostedTaubyVVVLooseDeepTau2017v1VSjet;   //!
TBranch        *b_boostedTaubyVLooseDeepTau2017v1VSjet;   //!
TBranch        *b_boostedTaubyLooseDeepTau2017v1VSjet;   //!
TBranch        *b_boostedTaubyMediumDeepTau2017v1VSjet;   //!
TBranch        *b_boostedTaubyTightDeepTau2017v1VSjet;   //!
TBranch        *b_boostedTaubyVVTightDeepTau2017v1VSjet;   //!
TBranch        *b_boostedTaubyVVVLooseDeepTau2017v1VSe;   //!
TBranch        *b_boostedTaubyLooseDeepTau2017v1VSe;   //!
TBranch        *b_boostedTaubyTightDeepTau2017v1VSe;   //!
TBranch        *b_boostedTaubyVVTightDeepTau2017v1VSe;   //!
TBranch        *b_boostedTaubyVVVLooseDeepTau2017v1VSmu;   //!
TBranch        *b_boostedTaubyLooseDeepTau2017v1VSmu;   //!
TBranch        *b_boostedTaubyTightDeepTau2017v1VSmu;   //!
TBranch        *b_boostedTaubyVVTightDeepTau2017v1VSmu;   //!
TBranch        *b_boostedTauagainstElectronVLooseMVA62018;   //!
TBranch        *b_boostedTauagainstElectronLooseMVA62018;   //!
TBranch        *b_boostedTauagainstElectronTightMVA62018;   //!
   TBranch        *b_nAK8Jet;   //!
   TBranch        *b_AK8JetPt;   //!
   TBranch        *b_AK8JetEn;   //!
   TBranch        *b_AK8JetRawPt;   //!
   TBranch        *b_AK8JetRawEn;   //!
   TBranch        *b_AK8JetEta;   //!
   TBranch        *b_AK8JetPhi;   //!
   TBranch        *b_AK8JetMass;   //!
   TBranch        *b_AK8Jet_tau1;   //!
   TBranch        *b_AK8Jet_tau2;   //!
   TBranch        *b_AK8Jet_tau3;   //!
   TBranch        *b_AK8Jetnconstituents;   //!
   TBranch        *b_AK8JetPFLooseId;   //!
   TBranch        *b_AK8JetPFTightLepVetoId;   //!
   TBranch        *b_AK8JetSoftDropMass;   //!
   TBranch        *b_AK8JetSoftDropMassCorr;   //!
   TBranch        *b_AK8JetPrunedMass;   //!
   TBranch        *b_AK8JetPrunedMassCorr;   //!
   TBranch        *b_AK8JetpfBoostedDSVBTag;   //!
   TBranch        *b_AK8JetCSV;   //!
   TBranch        *b_AK8JetJECUnc;   //!
   TBranch        *b_AK8JetL2L3corr;   //!
   TBranch        *b_AK8puppiPt;   //!
   TBranch        *b_AK8puppiMass;   //!
   TBranch        *b_AK8puppiEta;   //!
   TBranch        *b_AK8puppiPhi;   //!
   TBranch        *b_AK8puppiSDL2L3corr;   //!
   TBranch        *b_AK8puppiSDMass;   //!
   TBranch        *b_AK8puppiSDMassL2L3Corr;   //!
   TBranch        *b_AK8JetPartonID;   //!
   TBranch        *b_AK8JetHadFlvr;   //!
   TBranch        *b_nAK8SDSJ;   //!
   TBranch        *b_AK8SDSJPt;   //!
   TBranch        *b_AK8SDSJEta;   //!
   TBranch        *b_AK8SDSJPhi;   //!
   TBranch        *b_AK8SDSJMass;   //!
   TBranch        *b_AK8SDSJE;   //!
   TBranch        *b_AK8SDSJCharge;   //!
   TBranch        *b_AK8SDSJFlavour;   //!
   TBranch        *b_AK8SDSJCSV;   //!
   TBranch        *b_nAK8puppiSDSJ;   //!
   TBranch        *b_AK8puppiSDSJPt;   //!
   TBranch        *b_AK8puppiSDSJEta;   //!
   TBranch        *b_AK8puppiSDSJPhi;   //!
   TBranch        *b_AK8puppiSDSJMass;   //!
   TBranch        *b_AK8puppiSDSJE;   //!
   TBranch        *b_AK8puppiSDSJCharge;   //!
   TBranch        *b_AK8puppiSDSJFlavour;   //!
   TBranch        *b_AK8puppiSDSJCSV;   //!


//
//   // Declaration of leaf types
//   Int_t           run;
//   Long64_t        event;
//   Int_t           lumis;
//   Bool_t          isData;
//   Int_t           nVtx;
//   Int_t           nGoodVtx;
//   Bool_t          isPVGood;
//   Float_t         vtx;
//   Float_t         vty;
//   Float_t         vtz;
//   Float_t         rho;
//   Float_t         rhoCentral;
//   ULong64_t       HLTEleMuX;
//   ULong64_t       HLTPho;
//   ULong64_t       HLTPhoRejectedByPS;
//   ULong64_t       HLTJet;
//   ULong64_t       HLTEleMuXIsPrescaled;
//   ULong64_t       HLTPhoIsPrescaled;
//   ULong64_t       HLTJetIsPrescaled;
//   vector<float>   *pdf;
//   Float_t         pthat;
//   Float_t         processID;
//   Float_t         genWeight;
//   Float_t         genHT;
//   Float_t         genPho1;
//   Float_t         genPho2;
//   TString         *EventTag;
//   Int_t           nPUInfo;
//   vector<int>     *nPU;
//   vector<int>     *puBX;
//   vector<float>   *puTrue;
//   Int_t           nMC;
//   Int_t           numGenTau;
//   vector<int>     *mcPID;
//   vector<float>   *mcPt;
//   vector<float>   *mcMass;
//   vector<float>   *mcEta;
//   vector<float>   *mcPhi;
//   vector<float>   *mcE;
//   vector<float>   *mcEt;
//   vector<int>     *mcGMomPID;
//   vector<int>     *mcMomPID;
//   vector<float>   *mcMomPt;
//   vector<float>   *mcMomMass;
//   vector<float>   *mcMomEta;
//   vector<float>   *mcMomPhi;
//   vector<unsigned short> *mcStatusFlag;
//   vector<int>     *mcParentage;
//   vector<int>     *mcStatus;
//   vector<float>   *taudaugPt;
//   vector<float>   *taudaugEta;
//   vector<float>   *taudaugPhi;
//   vector<float>   *taudaugMass;
//   Float_t         genMET;
//   Float_t         genMETPhi;
//   Int_t           metFilters;
//   Float_t         pfMET;
//   Float_t         pfMETPhi;
//   Int_t           recoil;
//   Float_t         pfMetNoRecoil;
//   Float_t         pfMetPhiNoRecoil;
//   Float_t         met_px;
//   Float_t         met_py;
//   Float_t         metcov00;
//   Float_t         metcov01;
//   Float_t         metcov10;
//   Float_t         metcov11;
//   Float_t         met_JESUp;
//   Float_t         met_JESDown;
//   Float_t         met_UESUp;
//   Float_t         met_UESDown;
//   Float_t         metphi_JESUp;
//   Float_t         metphi_JESDown;
//   Float_t         metphi_UESUp;
//   Float_t         metphi_UESDown;
//   Float_t         pfmetcorr_ex_UESUp;
//   Float_t         pfmetcorr_ey_UESUp;
//   Float_t         pfmetcorr_ex_UESDown;
//   Float_t         pfmetcorr_ey_UESDown;
//   Float_t         pfmetcorr_ex_JESUp;
//   Float_t         pfmetcorr_ey_JESUp;
//   Float_t         pfmetcorr_ex_JESDown;
//   Float_t         pfmetcorr_ey_JESDown;
//   Int_t           nEle;
//   vector<int>     *eleCharge;
//   vector<int>     *eleChargeConsistent;
//   vector<float>   *eleEn;
//   vector<float>   *eleSCEn;
//   vector<float>   *eleEcalEn;
//   vector<float>   *eleESEnP1;
//   vector<float>   *eleESEnP2;
//   vector<float>   *eleD0;
//   vector<float>   *eleDz;
//   vector<float>   *eleSIP;
//   vector<float>   *elePt;
//   vector<float>   *elePtError;
//   vector<float>   *eleEta;
//   vector<float>   *elePhi;
//   vector<float>   *eleSCEta;
//   vector<float>   *eleSCPhi;
//   vector<int>     *eleConvVeto;
//   vector<int>     *eleMissHits;
//   vector<float>   *eleESEffSigmaRR;
//   vector<float>   *elePFChIso;
//   vector<float>   *elePFPhoIso;
//   vector<float>   *elePFNeuIso;
//   vector<float>   *elePFPUIso;
//   vector<float>   *elePFClusEcalIso;
//   vector<float>   *elePFClusHcalIso;
//   vector<float>   *eleIDMVAIso;
//   vector<float>   *eleIDMVANoIso;
//   vector<ULong64_t> *eleFiredSingleTrgs;
//   vector<ULong64_t> *eleFiredDoubleTrgs;
//   vector<ULong64_t> *eleFiredL1Trgs;
//   vector<unsigned short> *eleIDbit;
//   Int_t           nMu;
//   vector<float>   *muPt;
//   vector<float>   *muEn;
//   vector<float>   *muEta;
//   vector<float>   *muPhi;
//   vector<int>     *muCharge;
//   vector<int>     *muType;
//   vector<int>     *muIDbit;
//   vector<float>   *muD0;
//   vector<float>   *muDz;
//   vector<float>   *muSIP;
//   vector<float>   *muChi2NDF;
//   vector<float>   *muInnerD0;
//   vector<float>   *muInnerDz;
//   vector<int>     *muMuonHits;
//   vector<int>     *muStations;
//   vector<int>     *muMatches;
//   vector<int>     *muTrkQuality;
//   vector<float>   *muIsoTrk;
//   vector<float>   *muPFChIso;
//   vector<float>   *muPFPhoIso;
//   vector<float>   *muPFNeuIso;
//   vector<float>   *muPFPUIso;
//   vector<float>   *muPFChIso03;
//   vector<float>   *muPFPhoIso03;
//   vector<float>   *muPFNeuIso03;
//   vector<float>   *muPFPUIso03;
//   vector<ULong64_t> *muFiredTrgs;
//   vector<ULong64_t> *muFiredL1Trgs;
//   Int_t           nTau;
//   vector<bool>    *taupfTausDiscriminationByDecayModeFinding;
//   vector<bool>    *taupfTausDiscriminationByDecayModeFindingNewDMs;
//   vector<bool>    *tauByMVA6VLooseElectronRejection;
//   vector<bool>    *tauByMVA6LooseElectronRejection;
//   vector<bool>    *tauByMVA6MediumElectronRejection;
//   vector<bool>    *tauByMVA6TightElectronRejection;
//   vector<bool>    *tauByMVA6VTightElectronRejection;
//   vector<bool>    *tauByLooseMuonRejection3;
//   vector<bool>    *tauByTightMuonRejection3;
//   vector<bool>    *tauByLooseCombinedIsolationDeltaBetaCorr3Hits;
//   vector<bool>    *tauByMediumCombinedIsolationDeltaBetaCorr3Hits;
//   vector<bool>    *tauByTightCombinedIsolationDeltaBetaCorr3Hits;
//   vector<float>   *tauCombinedIsolationDeltaBetaCorrRaw3Hits;
//   vector<float>   *tauByIsolationMVArun2v1DBnewDMwLTraw;
//   vector<float>   *tauByIsolationMVArun2v1DBoldDMwLTraw;
//   vector<bool>    *tauByVTightIsolationMVArun2v1DBnewDMwLT;
//   vector<bool>    *tauByVTightIsolationMVArun2v1DBoldDMwLT;
//   vector<bool>    *tauByTightIsolationMVArun2v1DBnewDMwLT;
//   vector<bool>    *tauByTightIsolationMVArun2v1DBoldDMwLT;
//   vector<bool>    *tauByMediumIsolationMVArun2v1DBnewDMwLT;
//   vector<bool>    *tauByMediumIsolationMVArun2v1DBoldDMwLT;
//   vector<bool>    *tauByLooseIsolationMVArun2v1DBnewDMwLT;
//   vector<bool>    *tauByLooseIsolationMVArun2v1DBoldDMwLT;
//   vector<bool>    *tauByVLooseIsolationMVArun2v1DBnewDMwLT;
//   vector<bool>    *tauByVLooseIsolationMVArun2v1DBoldDMwLT;
//   vector<float>   *tauEta;
//   vector<float>   *tauPhi;
//   vector<float>   *tauPt;
//   vector<float>   *tauEt;
//   vector<float>   *tauCharge;
//   vector<float>   *tauP;
//   vector<float>   *tauPx;
//   vector<float>   *tauPy;
//   vector<float>   *tauPz;
//   vector<float>   *tauVz;
//   vector<float>   *tauEnergy;
//   vector<float>   *tauMass;
//   vector<float>   *tauDxy;
//   vector<float>   *tauZImpact;
//   vector<int>     *tauDecayMode;
//   vector<bool>    *tauLeadChargedHadronExists;
//   vector<float>   *tauLeadChargedHadronEta;
//   vector<float>   *tauLeadChargedHadronPhi;
//   vector<float>   *tauLeadChargedHadronPt;
//   vector<float>   *tauChargedIsoPtSum;
//   vector<float>   *tauNeutralIsoPtSum;
//   vector<float>   *tauPuCorrPtSum;
//   vector<int>     *tauNumSignalPFChargedHadrCands;
//   vector<int>     *tauNumSignalPFNeutrHadrCands;
//   vector<int>     *tauNumSignalPFGammaCands;
//   vector<int>     *tauNumSignalPFCands;
//   vector<int>     *tauNumIsolationPFChargedHadrCands;
//   vector<int>     *tauNumIsolationPFNeutrHadrCands;
//   vector<int>     *tauNumIsolationPFGammaCands;
//   vector<int>     *tauNumIsolationPFCands;
//   vector<float>   *taufootprintCorrection;
//   vector<float>   *tauphotonPtSumOutsideSignalCone;
//   vector<float>   *taudz;
//   vector<float>   *taudxy;
//   vector<float>   *tauByIsolationMVArun2v2DBoldDMwLTraw;
//   vector<bool>    *tauByVTightIsolationMVArun2v2DBoldDMwLT;
//   vector<bool>    *tauByTightIsolationMVArun2v2DBoldDMwLT;
//   vector<bool>    *tauByMediumIsolationMVArun2v2DBoldDMwLT;
//   vector<bool>    *tauByLooseIsolationMVArun2v2DBoldDMwLT;
//   vector<bool>    *tauByVLooseIsolationMVArun2v2DBoldDMwLT;
//   Int_t           nJet;
//   vector<float>   *jetPt;
//   vector<float>   *jetEn;
//   vector<float>   *jetEta;
//   vector<float>   *jetPhi;
//   vector<float>   *jetRawPt;
//   vector<float>   *jetRawEn;
//   vector<float>   *jetMt;
//   vector<float>   *jetArea;
//   vector<float>   *jetLeadTrackPt;
//   vector<float>   *jetLeadTrackEta;
//   vector<float>   *jetLeadTrackPhi;
//   vector<int>     *jetLepTrackPID;
//   vector<float>   *jetLepTrackPt;
//   vector<float>   *jetLepTrackEta;
//   vector<float>   *jetLepTrackPhi;
//   vector<float>   *jetCSV2BJetTags;
//   vector<float>   *jetDeepCSVTags_b;
//   vector<float>   *jetDeepCSVTags_bb;
//   vector<float>   *jetDeepCSVTags_c;
//   vector<float>   *jetDeepCSVTags_udsg;
//   vector<int>     *jetPartonID;
//   vector<int>     *jetHadFlvr;
//   vector<bool>    *jetPFLooseId;
//   vector<int>     *jetID;
//   vector<float>   *jetPUID;
//   vector<int>     *jetPUFullID;
//   vector<float>   *jetJECUnc;
//   vector<ULong64_t> *jetFiredTrgs;
//   vector<float>   *jetCHF;
//   vector<float>   *jetNHF;
//   vector<float>   *jetCEF;
//   vector<float>   *jetNEF;
//   vector<int>     *jetNCH;
//   vector<int>     *jetNNP;
//   vector<float>   *jetMUF;
//   Int_t           nAK8Jet;
//   vector<float>   *AK8JetPt;
//   vector<float>   *AK8JetEn;
//   vector<float>   *AK8JetRawPt;
//   vector<float>   *AK8JetRawEn;
//   vector<float>   *AK8JetEta;
//   vector<float>   *AK8JetPhi;
//   vector<float>   *AK8JetMass;
//   vector<float>   *AK8Jet_tau1;
//   vector<float>   *AK8Jet_tau2;
//   vector<float>   *AK8Jet_tau3;
//   vector<float>   *AK8JetCHF;
//   vector<float>   *AK8JetNHF;
//   vector<float>   *AK8JetCEF;
//   vector<float>   *AK8JetNEF;
//   vector<int>     *AK8JetNCH;
//   vector<int>     *AK8JetNNP;
//   vector<float>   *AK8JetMUF;
//   vector<int>     *AK8Jetnconstituents;
//   vector<bool>    *AK8JetPFLooseId;
//   vector<bool>    *AK8JetPFTightLepVetoId;
//   vector<float>   *AK8JetSoftDropMass;
//   vector<float>   *AK8JetSoftDropMassCorr;
//   vector<float>   *AK8JetPrunedMass;
//   vector<float>   *AK8JetPrunedMassCorr;
//   vector<float>   *AK8JetpfBoostedDSVBTag;
//   vector<float>   *AK8JetCSV;
//   vector<float>   *AK8JetJECUnc;
//   vector<float>   *AK8JetL2L3corr;
//   vector<float>   *AK8puppiPt;
//   vector<float>   *AK8puppiMass;
//   vector<float>   *AK8puppiEta;
//   vector<float>   *AK8puppiPhi;
//   vector<float>   *AK8puppiSDL2L3corr;
//   vector<float>   *AK8puppiSDMass;
//   vector<float>   *AK8puppiSDMassL2L3Corr;
//   vector<int>     *AK8JetPartonID;
//   vector<int>     *AK8JetHadFlvr;
//   vector<int>     *AK8JetGenJetIndex;
//   vector<float>   *AK8JetGenJetEn;
//   vector<float>   *AK8JetGenJetPt;
//   vector<float>   *AK8JetGenJetEta;
//   vector<float>   *AK8JetGenJetPhi;
//   vector<int>     *AK8JetGenPartonID;
//   vector<float>   *AK8JetGenEn;
//   vector<float>   *AK8JetGenPt;
//   vector<float>   *AK8JetGenEta;
//   vector<float>   *AK8JetGenPhi;
//   vector<int>     *AK8JetGenPartonMomID;
//   vector<int>     *nAK8SDSJ;
//   vector<vector<float> > *AK8SDSJPt;
//   vector<vector<float> > *AK8SDSJEta;
//   vector<vector<float> > *AK8SDSJPhi;
//   vector<vector<float> > *AK8SDSJMass;
//   vector<vector<float> > *AK8SDSJE;
//   vector<vector<int> > *AK8SDSJCharge;
//   vector<vector<int> > *AK8SDSJFlavour;
//   vector<vector<float> > *AK8SDSJCSV;
//   vector<int>     *nAK8puppiSDSJ;
//   vector<vector<float> > *AK8puppiSDSJPt;
//   vector<vector<float> > *AK8puppiSDSJEta;
//   vector<vector<float> > *AK8puppiSDSJPhi;
//   vector<vector<float> > *AK8puppiSDSJMass;
//   vector<vector<float> > *AK8puppiSDSJE;
//   vector<vector<int> > *AK8puppiSDSJCharge;
//   vector<vector<int> > *AK8puppiSDSJFlavour;
//   vector<vector<float> > *AK8puppiSDSJCSV;
//   Int_t           nBoostedTau;
//   vector<bool>    *boostedTaupfTausDiscriminationByDecayModeFinding;
//   vector<bool>    *boostedTaupfTausDiscriminationByDecayModeFindingNewDMs;
//   vector<bool>    *boostedTauByMVA6VLooseElectronRejection;
//   vector<bool>    *boostedTauByMVA6LooseElectronRejection;
//   vector<bool>    *boostedTauByMVA6MediumElectronRejection;
//   vector<bool>    *boostedTauByMVA6TightElectronRejection;
//   vector<bool>    *boostedTauByMVA6VTightElectronRejection;
//   vector<bool>    *boostedTauByLooseMuonRejection3;
//   vector<bool>    *boostedTauByTightMuonRejection3;
//   vector<bool>    *boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits;
//   vector<bool>    *boostedTauByMediumCombinedIsolationDeltaBetaCorr3Hits;
//   vector<bool>    *boostedTauByTightCombinedIsolationDeltaBetaCorr3Hits;
//   vector<float>   *boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits;
//   vector<float>   *boostedTauByIsolationMVArun2v1DBnewDMwLTraw;
//   vector<float>   *boostedTauByIsolationMVArun2v1DBoldDMwLTraw;
//   vector<float>   *boostedTauByIsolationMVArun2v1PWnewDMwLTraw;
//   vector<float>   *boostedTauByIsolationMVArun2v1PWoldDMwLTraw;
//   vector<bool>    *boostedTauByVTightIsolationMVArun2v1DBnewDMwLT;
//   vector<bool>    *boostedTauByVTightIsolationMVArun2v1DBoldDMwLT;
//   vector<bool>    *boostedTauByVTightIsolationMVArun2v1PWnewDMwLT;
//   vector<bool>    *boostedTauByVTightIsolationMVArun2v1PWoldDMwLT;
//   vector<bool>    *boostedTauByTightIsolationMVArun2v1DBnewDMwLT;
//   vector<bool>    *boostedTauByTightIsolationMVArun2v1DBoldDMwLT;
//   vector<bool>    *boostedTauByTightIsolationMVArun2v1PWnewDMwLT;
//   vector<bool>    *boostedTauByTightIsolationMVArun2v1PWoldDMwLT;
//   vector<bool>    *boostedTauByMediumIsolationMVArun2v1DBnewDMwLT;
//   vector<bool>    *boostedTauByMediumIsolationMVArun2v1DBoldDMwLT;
//   vector<bool>    *boostedTauByMediumIsolationMVArun2v1PWnewDMwLT;
//   vector<bool>    *boostedTauByMediumIsolationMVArun2v1PWoldDMwLT;
//   vector<bool>    *boostedTauByLooseIsolationMVArun2v1DBnewDMwLT;
//   vector<bool>    *boostedTauByLooseIsolationMVArun2v1DBoldDMwLT;
//   vector<bool>    *boostedTauByLooseIsolationMVArun2v1PWnewDMwLT;
//   vector<bool>    *boostedTauByLooseIsolationMVArun2v1PWoldDMwLT;
//   vector<bool>    *boostedTauByVLooseIsolationMVArun2v1DBnewDMwLT;
//   vector<bool>    *boostedTauByVLooseIsolationMVArun2v1DBoldDMwLT;
//   vector<bool>    *boostedTauByVLooseIsolationMVArun2v1PWnewDMwLT;
//   vector<bool>    *boostedTauByVLooseIsolationMVArun2v1PWoldDMwLT;
//   vector<float>   *boostedTauByIsolationMVArun2v2DBoldDMwLTraw;
//   vector<bool>    *boostedTauByVTightIsolationMVArun2v2DBoldDMwLT;
//   vector<bool>    *boostedTauByTightIsolationMVArun2v2DBoldDMwLT;
//   vector<bool>    *boostedTauByMediumIsolationMVArun2v2DBoldDMwLT;
//   vector<bool>    *boostedTauByLooseIsolationMVArun2v2DBoldDMwLT;
//   vector<bool>    *boostedTauByVLooseIsolationMVArun2v2DBoldDMwLT;
//
//   vector<bool>    *boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNoOverLap;
//   vector<bool>    *boostedTauByTightIsolationMVArun2v1DBoldDMwLTNoOverLap;
//   vector<float>    *boostedTauByIsolationMVArun2v1DBoldDMwLTrawNoOverLap;
//   vector<float>    *boostedTauChargedIsoPtSumNoOverLap;
//   vector<float>    *boostedTauNeutralIsoPtSumNoOverLap;
//
//
//   vector<float>   *boostedTauEta;
//   vector<float>   *boostedTauPhi;
//   vector<float>   *boostedTauPt;
//   vector<float>   *boostedTauEt;
//   vector<float>   *boostedTauCharge;
//   vector<float>   *boostedTauP;
//   vector<float>   *boostedTauPx;
//   vector<float>   *boostedTauPy;
//   vector<float>   *boostedTauPz;
//   vector<float>   *boostedTauVz;
//   vector<float>   *boostedTauEnergy;
//   vector<float>   *boostedTauMass;
//   vector<float>   *boostedTauDxy;
//   vector<float>   *boostedTauZImpact;
//   vector<int>     *boostedTauDecayMode;
//   vector<bool>    *boostedTauLeadChargedHadronExists;
//   vector<float>   *boostedTauLeadChargedHadronEta;
//   vector<float>   *boostedTauLeadChargedHadronPhi;
//   vector<float>   *boostedTauLeadChargedHadronPt;
//   vector<float>   *boostedTauChargedIsoPtSum;
//   vector<float>   *boostedTauNeutralIsoPtSum;
//   vector<float>   *boostedTauPuCorrPtSum;
//   vector<int>     *boostedTauNumSignalPFChargedHadrCands;
//   vector<int>     *boostedTauNumSignalPFNeutrHadrCands;
//   vector<int>     *boostedTauNumSignalPFGammaCands;
//   vector<int>     *boostedTauNumSignalPFCands;
//   vector<int>     *boostedTauNumIsolationPFChargedHadrCands;
//   vector<int>     *boostedTauNumIsolationPFNeutrHadrCands;
//   vector<int>     *boostedTauNumIsolationPFGammaCands;
//   vector<int>     *boostedTauNumIsolationPFCands;
//   vector<float>   *boostedTaufootprintCorrection;
//   vector<float>   *boostedTauphotonPtSumOutsideSignalCone;
//   vector<float>   *boostedTaudz;
//   vector<float>   *boostedTaudxy;
//
//   vector<vector<float>> *boostedTauSignalPFCands;
//   vector<vector<float>> *boostedTauSignalPFGammaCands;
//    vector<vector<float>> *boostedTauIsolationPFCands;
//    vector<vector<float>> *boostedTauIsolationPFGammaCands;
//
//
////    vector<int>   boostedTauNumIsolationPFChargedHadrCands;
////    vector<int>   boostedTauNumIsolationPFNeutrHadrCands;
////    vector<int>   boostedTauNumIsolationPFGammaCands;
////    vector<int>   boostedTauNumIsolationPFCands;
//    vector<int>   *boostedTauNumIsolationPFChargedHadrCandsOrig;
//    vector<int>   *boostedTauNumIsolationPFNeutrHadrCandsOrig;
//    vector<int>   *boostedTauNumIsolationPFGammaCandsOrig;
//    vector<int>   *boostedTauNumIsolationPFCandsOrig;

//    vector<vector<float>> *boostedTauNeutralIsoPtSum;

   Float_t         tmass;
   Int_t           era;
//   Float_t         met_px;
//   Float_t         met_py;
//   Float_t         met;
//   Float_t         metphi;
   Float_t         m_1;
   Float_t         px_1;
   Float_t         py_1;
   Float_t         pz_1;
   Float_t         e_1;
   Float_t         pt_1;
   Float_t         phi_1;
   Float_t         eta_1;
   Float_t         m_2;
   Float_t         px_2;
   Float_t         py_2;
   Float_t         pz_2;
   Float_t         e_2;
   Float_t         pt_2;
   Float_t         phi_2;
   Float_t         eta_2;
//   Float_t         metcov00;
//   Float_t         metcov01;
//   Float_t         metcov10;
//   Float_t         metcov11;
   Int_t           decayMode2;
   Int_t           decayMode1;
   Int_t tauIndex;
   Int_t lepIndex;
   Int_t leadtauIndex;
   Int_t subtauIndex;

//   Float_t         tmass;
//   Int_t           era;
//   Float_t         met_px;
//   Float_t         met_py;
//   Float_t         met;
//   Float_t         metphi;
//   Float_t         m_1;
//   Float_t         px_1;
//   Float_t         py_1;
//   Float_t         pz_1;
//   Float_t         e_1;
//   Float_t         pt_1;
//   Float_t         phi_1;
//   Float_t         eta_1;
//   Float_t         m_2;
//   Float_t         px_2;
//   Float_t         py_2;
//   Float_t         pz_2;
//   Float_t         e_2;
//   Float_t         pt_2;
//   Float_t         phi_2;
//   Float_t         eta_2;
//   Float_t         metcov00;
//   Float_t         metcov01;
//   Float_t         metcov10;
//   Float_t         metcov11;
//   Int_t           decayMode2;
//   Float_t         tmass;
//   Int_t           era;
//   Float_t         met_px;
//   Float_t         met_py;
//   Float_t         met;
//   Float_t         metphi;
//   Float_t         m_1;
//   Float_t         px_1;
//   Float_t         py_1;
//   Float_t         pz_1;
//   Float_t         e_1;
//   Float_t         pt_1;
//   Float_t         phi_1;
//   Float_t         eta_1;
//   Float_t         m_2;
//   Float_t         px_2;
//   Float_t         py_2;
//   Float_t         pz_2;
//   Float_t         e_2;
//   Float_t         pt_2;
//   Float_t         phi_2;
//   Float_t         eta_2;
//   Float_t         metcov00;
//   Float_t         metcov01;
//   Float_t         metcov10;
//   Float_t         metcov11;
//   Int_t           decayMode2;
//   Float_t         tmass;
//   Int_t           era;
//   Float_t         met_px;
//   Float_t         met_py;
//   Float_t         met;
//   Float_t         metphi;
//   Float_t         m_1;
//   Float_t         px_1;
//   Float_t         py_1;
//   Float_t         pz_1;
//   Float_t         e_1;
//   Float_t         pt_1;
//   Float_t         phi_1;
//   Float_t         eta_1;
//   Float_t         m_2;
//   Float_t         px_2;
//   Float_t         py_2;
//   Float_t         pz_2;
//   Float_t         e_2;
//   Float_t         pt_2;
//   Float_t         phi_2;
//   Float_t         eta_2;
//   Float_t         metcov00;
//   Float_t         metcov01;
//   Float_t         metcov10;
//   Float_t         metcov11;
//   Int_t           decayMode2;
//   Float_t         tmass;
//   Int_t           era;
//   Float_t         met_px;
//   Float_t         met_py;
//   Float_t         met;
//   Float_t         metphi;
//   Float_t         m_1;
//   Float_t         px_1;
//   Float_t         py_1;
//   Float_t         pz_1;
//   Float_t         e_1;
//   Float_t         pt_1;
//   Float_t         phi_1;
//   Float_t         eta_1;
//   Float_t         m_2;
//   Float_t         px_2;
//   Float_t         py_2;
//   Float_t         pz_2;
//   Float_t         e_2;
//   Float_t         pt_2;
//   Float_t         phi_2;
//   Float_t         eta_2;
//   Float_t         metcov00;
//   Float_t         metcov01;
//   Float_t         metcov10;
//   Float_t         metcov11;
//   Int_t           decayMode2;
//   Float_t         tmass;
//   Int_t           era;
//   Float_t         met_px;
//   Float_t         met_py;
//   Float_t         met;
//   Float_t         metphi;
//   Float_t         m_1;
//   Float_t         px_1;
//   Float_t         py_1;
//   Float_t         pz_1;
//   Float_t         e_1;
//   Float_t         pt_1;
//   Float_t         phi_1;
//   Float_t         eta_1;
//   Float_t         m_2;
//   Float_t         px_2;
//   Float_t         py_2;
//   Float_t         pz_2;
//   Float_t         e_2;
//   Float_t         pt_2;
//   Float_t         phi_2;
//   Float_t         eta_2;
//   Float_t         metcov00;
//   Float_t         metcov01;
//   Float_t         metcov10;
//   Float_t         metcov11;
//   Int_t           decayMode2;
//   Float_t         tmass;
//   Int_t           era;
//   Float_t         met_px;
//   Float_t         met_py;
//   Float_t         met;
//   Float_t         metphi;
//   Float_t         m_1;
//   Float_t         px_1;
//   Float_t         py_1;
//   Float_t         pz_1;
//   Float_t         e_1;
//   Float_t         pt_1;
//   Float_t         phi_1;
//   Float_t         eta_1;
//   Float_t         m_2;
//   Float_t         px_2;
//   Float_t         py_2;
//   Float_t         pz_2;
//   Float_t         e_2;
//   Float_t         pt_2;
//   Float_t         phi_2;
//   Float_t         eta_2;
//   Float_t         metcov00;
//   Float_t         metcov01;
//   Float_t         metcov10;
//   Float_t         metcov11;
//   Int_t           decayMode2;
//   Float_t         tmass;
//   Int_t           era;
//   Float_t         met_px;
//   Float_t         met_py;
//   Float_t         met;
//   Float_t         metphi;
//   Float_t         m_1;
//   Float_t         px_1;
//   Float_t         py_1;
//   Float_t         pz_1;
//   Float_t         e_1;
//   Float_t         pt_1;
//   Float_t         phi_1;
//   Float_t         eta_1;
//   Float_t         m_2;
//   Float_t         px_2;
//   Float_t         py_2;
//   Float_t         pz_2;
//   Float_t         e_2;
//   Float_t         pt_2;
//   Float_t         phi_2;
//   Float_t         eta_2;
//   Float_t         metcov00;
//   Float_t         metcov01;
//   Float_t         metcov10;
//   Float_t         metcov11;
//   Int_t           decayMode2;
//   Float_t         tmass;
//   Int_t           era;
//   Float_t         met_px;
//   Float_t         met_py;
//   Float_t         met;
//   Float_t         metphi;
//   Float_t         m_1;
//   Float_t         px_1;
//   Float_t         py_1;
//   Float_t         pz_1;
//   Float_t         e_1;
//   Float_t         pt_1;
//   Float_t         phi_1;
//   Float_t         eta_1;
//   Float_t         m_2;
//   Float_t         px_2;
//   Float_t         py_2;
//   Float_t         pz_2;
//   Float_t         e_2;
//   Float_t         pt_2;
//   Float_t         phi_2;
//   Float_t         eta_2;
//   Float_t         metcov00;
//   Float_t         metcov01;
//   Float_t         metcov10;
//   Float_t         metcov11;
//   Int_t           decayMode2;
//   Float_t         tmass;
//   Int_t           era;
//   Float_t         met_px;
//   Float_t         met_py;
//   Float_t         met;
//   Float_t         metphi;
//   Float_t         m_1;
//   Float_t         px_1;
//   Float_t         py_1;
//   Float_t         pz_1;
//   Float_t         e_1;
//   Float_t         pt_1;
//   Float_t         phi_1;
//   Float_t         eta_1;
//   Float_t         m_2;
//   Float_t         px_2;
//   Float_t         py_2;
//   Float_t         pz_2;
//   Float_t         e_2;
//   Float_t         pt_2;
//   Float_t         phi_2;
//   Float_t         eta_2;
//   Float_t         metcov00;
//   Float_t         metcov01;
//   Float_t         metcov10;
//   Float_t         metcov11;
//   Int_t           decayMode2;
//   Float_t         tau1_pt;
//   Float_t         tau1_eta;
//   Float_t         tau1_phi;
//   Float_t         tau1_m;
//   Float_t         tau2_pt;
//   Float_t         tau2_eta;
//   Float_t         tau2_phi;
//   Float_t         tau2_m;
   Float_t         m_sv;
   Float_t         pt_sv;
   
   
//   
//
//
//   TTree *  Xttree( TFile * f_Double, string channel){
//       
//       TTree *Run_Tree = (TTree*) f_Double->Get(channel.c_str());
//       
//       cout.setf(ios::fixed, ios::floatfield);
//       cout.precision(6);
//       
//       
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
//       Run_Tree->SetBranchAddress("L1ECALPrefire", &L1ECALPrefire, &b_L1ECALPrefire);
//       Run_Tree->SetBranchAddress("L1ECALPrefireUp", &L1ECALPrefireUp, &b_L1ECALPrefireUp);
//       Run_Tree->SetBranchAddress("L1ECALPrefireDown", &L1ECALPrefireDown, &b_L1ECALPrefireDown);
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
//       Run_Tree->SetBranchAddress("pfmetcorr_ex_UESUp", &pfmetcorr_ex_UESUp, &b_pfmetcorr_ex_UESUp);
//       Run_Tree->SetBranchAddress("pfmetcorr_ey_UESUp", &pfmetcorr_ey_UESUp, &b_pfmetcorr_ey_UESUp);
//       Run_Tree->SetBranchAddress("pfmetcorr_ex_UESDown", &pfmetcorr_ex_UESDown, &b_pfmetcorr_ex_UESDown);
//       Run_Tree->SetBranchAddress("pfmetcorr_ey_UESDown", &pfmetcorr_ey_UESDown, &b_pfmetcorr_ey_UESDown);
//       Run_Tree->SetBranchAddress("pfmetcorr_ex_JESUp", &pfmetcorr_ex_JESUp, &b_pfmetcorr_ex_JESUp);
//       Run_Tree->SetBranchAddress("pfmetcorr_ey_JESUp", &pfmetcorr_ey_JESUp, &b_pfmetcorr_ey_JESUp);
//       Run_Tree->SetBranchAddress("pfmetcorr_ex_JESDown", &pfmetcorr_ex_JESDown, &b_pfmetcorr_ex_JESDown);
//       Run_Tree->SetBranchAddress("pfmetcorr_ey_JESDown", &pfmetcorr_ey_JESDown, &b_pfmetcorr_ey_JESDown);
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
//       Run_Tree->SetBranchAddress("nBoostedTau", &nBoostedTau, &b_nBoostedTau);
//       Run_Tree->SetBranchAddress("nBoostedTauOrig", &nBoostedTauOrig, &b_nBoostedTauOrig);
//       Run_Tree->SetBranchAddress("boostedTaupfTausDiscriminationByDecayModeFinding", &boostedTaupfTausDiscriminationByDecayModeFinding, &b_boostedTaupfTausDiscriminationByDecayModeFinding);
//       Run_Tree->SetBranchAddress("boostedTaupfTausDiscriminationByDecayModeFindingNewDMs", &boostedTaupfTausDiscriminationByDecayModeFindingNewDMs, &b_boostedTaupfTausDiscriminationByDecayModeFindingNewDMs);
//       Run_Tree->SetBranchAddress("boostedTauByMVA6LooseElectronRejection", &boostedTauByMVA6LooseElectronRejection, &b_boostedTauByMVA6LooseElectronRejection);
//       Run_Tree->SetBranchAddress("boostedTauByMVA6TightElectronRejection", &boostedTauByMVA6TightElectronRejection, &b_boostedTauByMVA6TightElectronRejection);
//       Run_Tree->SetBranchAddress("boostedTauByLooseMuonRejection3", &boostedTauByLooseMuonRejection3, &b_boostedTauByLooseMuonRejection3);
//       Run_Tree->SetBranchAddress("boostedTauByTightMuonRejection3", &boostedTauByTightMuonRejection3, &b_boostedTauByTightMuonRejection3);
//       Run_Tree->SetBranchAddress("boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits", &boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits, &b_boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits);
//       Run_Tree->SetBranchAddress("boostedTauByTightCombinedIsolationDeltaBetaCorr3Hits", &boostedTauByTightCombinedIsolationDeltaBetaCorr3Hits, &b_boostedTauByTightCombinedIsolationDeltaBetaCorr3Hits);
//       Run_Tree->SetBranchAddress("boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits", &boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits, &b_boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits);
//       Run_Tree->SetBranchAddress("boostedTauByIsolationMVArun2v1DBoldDMwLTraw", &boostedTauByIsolationMVArun2v1DBoldDMwLTraw, &b_boostedTauByIsolationMVArun2v1DBoldDMwLTraw);
//       Run_Tree->SetBranchAddress("boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew", &boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew, &b_boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew);
//       Run_Tree->SetBranchAddress("boostedTauByTightIsolationMVArun2v1DBoldDMwLT", &boostedTauByTightIsolationMVArun2v1DBoldDMwLT, &b_boostedTauByTightIsolationMVArun2v1DBoldDMwLT);
//       Run_Tree->SetBranchAddress("boostedTauByTightIsolationMVArun2v1DBoldDMwLTNew", &boostedTauByTightIsolationMVArun2v1DBoldDMwLTNew, &b_boostedTauByTightIsolationMVArun2v1DBoldDMwLTNew);
//       Run_Tree->SetBranchAddress("boostedTauByVLooseIsolationMVArun2v1DBoldDMwLTNew", &boostedTauByVLooseIsolationMVArun2v1DBoldDMwLTNew, &b_boostedTauByVLooseIsolationMVArun2v1DBoldDMwLTNew);
//       Run_Tree->SetBranchAddress("boostedTauByMediumIsolationMVArun2v1DBoldDMwLTNew", &boostedTauByMediumIsolationMVArun2v1DBoldDMwLTNew, &b_boostedTauByMediumIsolationMVArun2v1DBoldDMwLTNew);
//       Run_Tree->SetBranchAddress("boostedTauByVTightIsolationMVArun2v1DBoldDMwLTNew", &boostedTauByVTightIsolationMVArun2v1DBoldDMwLTNew, &b_boostedTauByVTightIsolationMVArun2v1DBoldDMwLTNew);
//       Run_Tree->SetBranchAddress("boostedTauByLooseIsolationMVArun2v1DBoldDMwLT", &boostedTauByLooseIsolationMVArun2v1DBoldDMwLT, &b_boostedTauByLooseIsolationMVArun2v1DBoldDMwLT);
//       Run_Tree->SetBranchAddress("boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNew", &boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNew, &b_boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNew);
//       Run_Tree->SetBranchAddress("boostedTauEta", &boostedTauEta, &b_boostedTauEta);
//       Run_Tree->SetBranchAddress("boostedTauPhi", &boostedTauPhi, &b_boostedTauPhi);
//       Run_Tree->SetBranchAddress("boostedTauPt", &boostedTauPt, &b_boostedTauPt);
//       Run_Tree->SetBranchAddress("boostedTauEt", &boostedTauEt, &b_boostedTauEt);
//       Run_Tree->SetBranchAddress("boostedTauCharge", &boostedTauCharge, &b_boostedTauCharge);
//       Run_Tree->SetBranchAddress("boostedTauP", &boostedTauP, &b_boostedTauP);
//       Run_Tree->SetBranchAddress("boostedTauPx", &boostedTauPx, &b_boostedTauPx);
//       Run_Tree->SetBranchAddress("boostedTauPy", &boostedTauPy, &b_boostedTauPy);
//       Run_Tree->SetBranchAddress("boostedTauPz", &boostedTauPz, &b_boostedTauPz);
//       Run_Tree->SetBranchAddress("boostedTauVz", &boostedTauVz, &b_boostedTauVz);
//       Run_Tree->SetBranchAddress("boostedTauEnergy", &boostedTauEnergy, &b_boostedTauEnergy);
//       Run_Tree->SetBranchAddress("boostedTauMass", &boostedTauMass, &b_boostedTauMass);
//       Run_Tree->SetBranchAddress("boostedTauDxy", &boostedTauDxy, &b_boostedTauDxy);
//       Run_Tree->SetBranchAddress("boostedTauZImpact", &boostedTauZImpact, &b_boostedTauZImpact);
//       Run_Tree->SetBranchAddress("boostedTauDecayMode", &boostedTauDecayMode, &b_boostedTauDecayMode);
//       Run_Tree->SetBranchAddress("boostedTauLeadChargedHadronExists", &boostedTauLeadChargedHadronExists, &b_boostedTauLeadChargedHadronExists);
//       Run_Tree->SetBranchAddress("boostedTauLeadChargedHadronEta", &boostedTauLeadChargedHadronEta, &b_boostedTauLeadChargedHadronEta);
//       Run_Tree->SetBranchAddress("boostedTauLeadChargedHadronPhi", &boostedTauLeadChargedHadronPhi, &b_boostedTauLeadChargedHadronPhi);
//       Run_Tree->SetBranchAddress("boostedTauLeadChargedHadronPt", &boostedTauLeadChargedHadronPt, &b_boostedTauLeadChargedHadronPt);
//       Run_Tree->SetBranchAddress("boostedTauChargedIsoPtSum", &boostedTauChargedIsoPtSum, &b_boostedTauChargedIsoPtSum);
//       Run_Tree->SetBranchAddress("boostedTauChargedIsoPtSumNoOverLap", &boostedTauChargedIsoPtSumNoOverLap, &b_boostedTauChargedIsoPtSumNoOverLap);
//       Run_Tree->SetBranchAddress("boostedTauNeutralIsoPtSum", &boostedTauNeutralIsoPtSum, &b_boostedTauNeutralIsoPtSum);
//       Run_Tree->SetBranchAddress("boostedTauNeutralIsoPtSumNoOverLap", &boostedTauNeutralIsoPtSumNoOverLap, &b_boostedTauNeutralIsoPtSumNoOverLap);
//       Run_Tree->SetBranchAddress("boostedTauPuCorrPtSum", &boostedTauPuCorrPtSum, &b_boostedTauPuCorrPtSum);
//       Run_Tree->SetBranchAddress("boostedTauNumSignalPFChargedHadrCands", &boostedTauNumSignalPFChargedHadrCands, &b_boostedTauNumSignalPFChargedHadrCands);
//       Run_Tree->SetBranchAddress("boostedTauNumSignalPFNeutrHadrCands", &boostedTauNumSignalPFNeutrHadrCands, &b_boostedTauNumSignalPFNeutrHadrCands);
//       Run_Tree->SetBranchAddress("boostedTauNumSignalPFGammaCands", &boostedTauNumSignalPFGammaCands, &b_boostedTauNumSignalPFGammaCands);
//       Run_Tree->SetBranchAddress("boostedTauNumSignalPFCands", &boostedTauNumSignalPFCands, &b_boostedTauNumSignalPFCands);
//       Run_Tree->SetBranchAddress("boostedTauNumIsolationPFChargedHadrCands", &boostedTauNumIsolationPFChargedHadrCands, &b_boostedTauNumIsolationPFChargedHadrCands);
//       Run_Tree->SetBranchAddress("boostedTauNumIsolationPFNeutrHadrCands", &boostedTauNumIsolationPFNeutrHadrCands, &b_boostedTauNumIsolationPFNeutrHadrCands);
//       Run_Tree->SetBranchAddress("boostedTauNumIsolationPFGammaCands", &boostedTauNumIsolationPFGammaCands, &b_boostedTauNumIsolationPFGammaCands);
//       Run_Tree->SetBranchAddress("boostedTauNumIsolationPFCands", &boostedTauNumIsolationPFCands, &b_boostedTauNumIsolationPFCands);
//       Run_Tree->SetBranchAddress("boostedTaufootprintCorrection", &boostedTaufootprintCorrection, &b_boostedTaufootprintCorrection);
//       Run_Tree->SetBranchAddress("boostedTauphotonPtSumOutsideSignalCone", &boostedTauphotonPtSumOutsideSignalCone, &b_boostedTauphotonPtSumOutsideSignalCone);
//       Run_Tree->SetBranchAddress("boostedTaudz", &boostedTaudz, &b_boostedTaudz);
//       Run_Tree->SetBranchAddress("boostedTaudxy", &boostedTaudxy, &b_boostedTaudxy);
//       Run_Tree->SetBranchAddress("boostedTauSignalPFCands", &boostedTauSignalPFCands, &b_boostedTauSignalPFCands);
//       Run_Tree->SetBranchAddress("boostedTauSignalPFGammaCands", &boostedTauSignalPFGammaCands, &b_boostedTauSignalPFGammaCands);
//       Run_Tree->SetBranchAddress("boostedTauIsolationPFCands", &boostedTauIsolationPFCands, &b_boostedTauIsolationPFCands);
//       Run_Tree->SetBranchAddress("boostedTauIsolationPFGammaCands", &boostedTauIsolationPFGammaCands, &b_boostedTauIsolationPFGammaCands);
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
//       Run_Tree->SetBranchAddress("boostedTauagainstElectronVLooseMVA62018", &boostedTauagainstElectronVLooseMVA62018, &b_boostedTauagainstElectronVLooseMVA62018);
//       Run_Tree->SetBranchAddress("boostedTauagainstElectronLooseMVA62018", &boostedTauagainstElectronLooseMVA62018, &b_boostedTauagainstElectronLooseMVA62018);
//       Run_Tree->SetBranchAddress("boostedTauagainstElectronTightMVA62018", &boostedTauagainstElectronTightMVA62018, &b_boostedTauagainstElectronTightMVA62018);
//       
//       
//   //
//   //
//   //    //########################################   General Info
//   //    Run_Tree->SetBranchAddress("isData", &isData);
//   //    Run_Tree->SetBranchAddress("run", &run);
//   //    Run_Tree->SetBranchAddress("lumis", &lumis);
//   //    Run_Tree->SetBranchAddress("event", &event);
//   //    Run_Tree->SetBranchAddress("genWeight",&genWeight);
//   //    Run_Tree->SetBranchAddress("HLTEleMuX", &HLTEleMuX);
//   //    Run_Tree->SetBranchAddress("HLTJet", &HLTJet);
//   //    Run_Tree->SetBranchAddress("puTrue", &puTrue);
//   //    Run_Tree->SetBranchAddress("nVtx",&nVtx);
//   //
//   //    //########################################   MC Info
//   //    Run_Tree->SetBranchAddress("nMC", &nMC);
//   //    Run_Tree->SetBranchAddress("mcPID", &mcPID);
//   //    Run_Tree->SetBranchAddress("mcStatus", &mcStatus);
//   //    Run_Tree->SetBranchAddress("mcPt", &mcPt );
//   //    Run_Tree->SetBranchAddress("mcEta", &mcEta );
//   //    Run_Tree->SetBranchAddress("mcPhi", &mcPhi );
//   //    Run_Tree->SetBranchAddress("mcE", &mcE );
//   //    Run_Tree->SetBranchAddress("mcMass", &mcMass );
//   //    Run_Tree->SetBranchAddress("mcMomPID", &mcMomPID );
//   //    Run_Tree->SetBranchAddress("mcGMomPID", &mcGMomPID );
//   //    Run_Tree->SetBranchAddress("mcStatusFlag",&mcStatusFlag);
//   //
//   //    //########################################   Tau Info
//   //    Run_Tree->SetBranchAddress("nTau", &nTau);
//   //    Run_Tree->SetBranchAddress("tauPt"  ,&tauPt);
//   //    Run_Tree->SetBranchAddress("tauEta"  ,&tauEta);
//   //    Run_Tree->SetBranchAddress("tauPhi"  ,&tauPhi);
//   //    Run_Tree->SetBranchAddress("tauMass"  ,&tauMass);
//   //    Run_Tree->SetBranchAddress("tauCharge"  ,&tauCharge);
//   //    Run_Tree->SetBranchAddress("taupfTausDiscriminationByDecayModeFinding", &taupfTausDiscriminationByDecayModeFinding);
//   //    Run_Tree->SetBranchAddress("tauByTightMuonRejection3", &tauByTightMuonRejection3);
//   //    Run_Tree->SetBranchAddress("tauByLooseMuonRejection3", &tauByLooseMuonRejection3);
//   //    Run_Tree->SetBranchAddress("tauByMVA6MediumElectronRejection"  ,&tauByMVA6MediumElectronRejection);
//   //    Run_Tree->SetBranchAddress("tauByLooseCombinedIsolationDeltaBetaCorr3Hits",&tauByLooseCombinedIsolationDeltaBetaCorr3Hits);
//   //    Run_Tree->SetBranchAddress("tauByMediumCombinedIsolationDeltaBetaCorr3Hits",&tauByMediumCombinedIsolationDeltaBetaCorr3Hits);
//   //    Run_Tree->SetBranchAddress("tauByMVA6LooseElectronRejection", &tauByMVA6LooseElectronRejection);
//   //    Run_Tree->SetBranchAddress("tauDxy",&tauDxy);
//   //    Run_Tree->SetBranchAddress("tauDecayMode",&tauDecayMode);
//   //    Run_Tree->SetBranchAddress("tauByLooseIsolationMVArun2v1DBoldDMwLT",&tauByLooseIsolationMVArun2v1DBoldDMwLT);
//   //    Run_Tree->SetBranchAddress("tauByVLooseIsolationMVArun2v1DBoldDMwLT",&tauByVLooseIsolationMVArun2v1DBoldDMwLT);
//   //    Run_Tree->SetBranchAddress("tauByIsolationMVArun2v1DBoldDMwLTraw",&tauByIsolationMVArun2v1DBoldDMwLTraw);
//   //    Run_Tree->SetBranchAddress("tauByIsolationMVArun2v2DBoldDMwLTraw",&tauByIsolationMVArun2v2DBoldDMwLTraw);
//   //    Run_Tree->SetBranchAddress("tauCombinedIsolationDeltaBetaCorrRaw3Hits",&tauCombinedIsolationDeltaBetaCorrRaw3Hits);
//   ////    Run_Tree->SetBranchAddress("tauByLooseCombinedIsolationDeltaBetaCorr3Hits",&tauByLooseCombinedIsolationDeltaBetaCorr3Hits);
//   //    Run_Tree->SetBranchAddress("boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNoOverLap",&boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNoOverLap);
//   //    Run_Tree->SetBranchAddress("boostedTauByTightIsolationMVArun2v1DBoldDMwLTNoOverLap",&boostedTauByTightIsolationMVArun2v1DBoldDMwLTNoOverLap);
//   //    Run_Tree->SetBranchAddress("boostedTauByIsolationMVArun2v1DBoldDMwLTrawNoOverLap",&boostedTauByIsolationMVArun2v1DBoldDMwLTrawNoOverLap);
//   //    Run_Tree->SetBranchAddress("boostedTauChargedIsoPtSumNoOverLap",&boostedTauChargedIsoPtSumNoOverLap);
//   //    Run_Tree->SetBranchAddress("boostedTauNeutralIsoPtSumNoOverLap",&boostedTauNeutralIsoPtSumNoOverLap);
//   //
//   //    Run_Tree->SetBranchAddress("boostedTauNumIsolationPFChargedHadrCands"  ,&boostedTauNumIsolationPFChargedHadrCands);
//   //    Run_Tree->SetBranchAddress("boostedTauNumIsolationPFNeutrHadrCands"  ,&boostedTauNumIsolationPFNeutrHadrCands);
//   //    Run_Tree->SetBranchAddress("boostedTauNumIsolationPFGammaCands"  ,&boostedTauNumIsolationPFGammaCands);
//   //    Run_Tree->SetBranchAddress("boostedTauNumIsolationPFCands"  ,&boostedTauNumIsolationPFCands);
//   //    Run_Tree->SetBranchAddress("boostedTauNumIsolationPFChargedHadrCandsOrig"  ,&boostedTauNumIsolationPFChargedHadrCandsOrig);
//   //    Run_Tree->SetBranchAddress("boostedTauNumIsolationPFNeutrHadrCandsOrig"  ,&boostedTauNumIsolationPFNeutrHadrCandsOrig);
//   //    Run_Tree->SetBranchAddress("boostedTauNumIsolationPFGammaCandsOrig"  ,&boostedTauNumIsolationPFGammaCandsOrig);
//   //    Run_Tree->SetBranchAddress("boostedTauNumIsolationPFCandsOrig"  ,&boostedTauNumIsolationPFCandsOrig);
//   //
//   //    //########################################   Mu Info
//   //    Run_Tree->SetBranchAddress("nMu", &nMu);
//   //    Run_Tree->SetBranchAddress("muPt"  ,&muPt);
//   //    Run_Tree->SetBranchAddress("muEta"  ,&muEta);
//   //    Run_Tree->SetBranchAddress("muPhi"  ,&muPhi);
//   //    Run_Tree->SetBranchAddress("muIsoTrk", &muIsoTrk);
//   //    Run_Tree->SetBranchAddress("muCharge",&muCharge);
//   //    Run_Tree->SetBranchAddress("muIDbit",&muIDbit);//NEW
//   //    Run_Tree->SetBranchAddress("muPFChIso", &muPFChIso);
//   //    Run_Tree->SetBranchAddress("muPFPhoIso", &muPFPhoIso);
//   //    Run_Tree->SetBranchAddress("muPFNeuIso", &muPFNeuIso);
//   //    Run_Tree->SetBranchAddress("muPFPUIso", &muPFPUIso);
//   //    Run_Tree->SetBranchAddress("muD0",&muD0);
//   //    Run_Tree->SetBranchAddress("muDz",&muDz);
//   //
//   //    //########################################   Ele Info
//   //    Run_Tree->SetBranchAddress("nEle", &nEle);
//   //    Run_Tree->SetBranchAddress("eleCharge", &eleCharge);
//   //    Run_Tree->SetBranchAddress("eleChargeConsistent", &eleChargeConsistent);
//   //    Run_Tree->SetBranchAddress("eleEn", &eleEn);
//   //    Run_Tree->SetBranchAddress("eleSCEn", &eleSCEn);
//   //    //    Run_Tree->SetBranchAddress("eleESEn", &eleESEn);
//   //    Run_Tree->SetBranchAddress("eleESEnP1", &eleESEnP1);
//   //    Run_Tree->SetBranchAddress("eleESEnP2", &eleESEnP2);
//   //    Run_Tree->SetBranchAddress("eleD0", &eleD0);
//   //    Run_Tree->SetBranchAddress("eleDz", &eleDz);
//   //    Run_Tree->SetBranchAddress("eleSIP", &eleSIP);
//   //    Run_Tree->SetBranchAddress("elePt", &elePt);
//   //    Run_Tree->SetBranchAddress("eleEta", &eleEta);
//   //    Run_Tree->SetBranchAddress("elePhi", &elePhi);
//   //    //    Run_Tree->SetBranchAddress("eleR9", &eleR9);
//   //    //    Run_Tree->SetBranchAddress("eleCalibPt", &eleCalibPt);
//   //    //    Run_Tree->SetBranchAddress("eleCalibEn", &eleCalibEn);
//   //    Run_Tree->SetBranchAddress("eleSCEta", &eleSCEta);
//   //    //    Run_Tree->SetBranchAddress("eleSCPhi", &eleSCPhi);
//   //    //    Run_Tree->SetBranchAddress("eleSCRawEn", &eleSCRawEn);
//   //    //    Run_Tree->SetBranchAddress("eleSCEtaWidth", &eleSCEtaWidth);
//   //    //    Run_Tree->SetBranchAddress("eleSCPhiWidth", &eleSCPhiWidth);
//   //    //    Run_Tree->SetBranchAddress("eleHoverE", &eleHoverE);
//   //    //    Run_Tree->SetBranchAddress("eleEoverP", &eleEoverP);
//   //    //    Run_Tree->SetBranchAddress("eleEoverPout", &eleEoverPout);
//   //    //    Run_Tree->SetBranchAddress("eleEoverPInv", &eleEoverPInv);
//   //    //    Run_Tree->SetBranchAddress("eleBrem", &eleBrem);
//   //    //    Run_Tree->SetBranchAddress("eledEtaAtVtx", &eledEtaAtVtx);
//   //    //    Run_Tree->SetBranchAddress("eledPhiAtVtx", &eledPhiAtVtx);
//   //    ////    Run_Tree->SetBranchAddress("eledEtaAtCalo", &eledEtaAtCalo);
//   //    //    Run_Tree->SetBranchAddress("eleSigmaIEtaIEtaFull5x5", &eleSigmaIEtaIEtaFull5x5);
//   //    //    Run_Tree->SetBranchAddress("eleSigmaIPhiIPhiFull5x5", &eleSigmaIPhiIPhiFull5x5);
//   //    Run_Tree->SetBranchAddress("eleConvVeto", &eleConvVeto);
//   //    Run_Tree->SetBranchAddress("eleMissHits", &eleMissHits);
//   //    Run_Tree->SetBranchAddress("eleESEffSigmaRR", &eleESEffSigmaRR);
//   //    Run_Tree->SetBranchAddress("elePFChIso", &elePFChIso);
//   //    Run_Tree->SetBranchAddress("elePFPhoIso", &elePFPhoIso);
//   //    Run_Tree->SetBranchAddress("elePFNeuIso", &elePFNeuIso);
//   //    Run_Tree->SetBranchAddress("elePFPUIso", &elePFPUIso);
//   //    Run_Tree->SetBranchAddress("elePFClusEcalIso", &elePFClusEcalIso);
//   //    Run_Tree->SetBranchAddress("elePFClusHcalIso", &elePFClusHcalIso);
//   //    //    Run_Tree->SetBranchAddress("elePFMiniIso", &elePFMiniIso);
//   //    Run_Tree->SetBranchAddress("eleIDMVAIso", &eleIDMVAIso);
//   //    Run_Tree->SetBranchAddress("eleIDMVANoIso", &eleIDMVANoIso);
//   //    //    Run_Tree->SetBranchAddress("eledEtaseedAtVtx", &eledEtaseedAtVtx);
//   //    //    Run_Tree->SetBranchAddress("eleE1x5", &eleE1x5);
//   //    //    Run_Tree->SetBranchAddress("eleE2x5", &eleE2x5);
//   //    //    Run_Tree->SetBranchAddress("eleE5x5", &eleE5x5);
//   //    //    Run_Tree->SetBranchAddress("eleE1x5Full5x5", &eleE1x5Full5x5);
//   //    //    Run_Tree->SetBranchAddress("eleE2x5Full5x5", &eleE2x5Full5x5);
//   //    //    Run_Tree->SetBranchAddress("eleE5x5Full5x5", &eleE5x5Full5x5);
//   //    //    Run_Tree->SetBranchAddress("eleR9Full5x5", &eleR9Full5x5);
//   //    //    Run_Tree->SetBranchAddress("eleEcalDrivenSeed", &eleEcalDrivenSeed);
//   //    //    Run_Tree->SetBranchAddress("eleDr03EcalRecHitSumEt", &eleDr03EcalRecHitSumEt);
//   //    //    Run_Tree->SetBranchAddress("eleDr03HcalDepth1TowerSumEt", &eleDr03HcalDepth1TowerSumEt);
//   //    //    Run_Tree->SetBranchAddress("eleDr03HcalDepth2TowerSumEt", &eleDr03HcalDepth2TowerSumEt);
//   //    //    Run_Tree->SetBranchAddress("eleDr03HcalTowerSumEt", &eleDr03HcalTowerSumEt);
//   //    //    Run_Tree->SetBranchAddress("eleDr03TkSumPt", &eleDr03TkSumPt);
//   //    //    Run_Tree->SetBranchAddress("elecaloEnergy", &elecaloEnergy);
//   //    //    Run_Tree->SetBranchAddress("eleTrkdxy", &eleTrkdxy);
//   //    //    Run_Tree->SetBranchAddress("eleKFHits", &eleKFHits);
//   //    //    Run_Tree->SetBranchAddress("eleKFChi2", &eleKFChi2);
//   //    //    Run_Tree->SetBranchAddress("eleIDbit", &eleIDbit);
//   //
//   //    //########################################   Jet Info
//   //    Run_Tree->SetBranchAddress("nJet",&nJet);
//   //    Run_Tree->SetBranchAddress("jetPt",&jetPt);
//   //    Run_Tree->SetBranchAddress("jetEta",&jetEta);
//   //    Run_Tree->SetBranchAddress("jetPhi",&jetPhi);
//   //    Run_Tree->SetBranchAddress("jetEn",&jetEn);
//   //    Run_Tree->SetBranchAddress("jetCSV2BJetTags",&jetCSV2BJetTags);
//   //    Run_Tree->SetBranchAddress("jetPFLooseId",&jetPFLooseId);
//   //    Run_Tree->SetBranchAddress("jetPUID",&jetPUID);
//   //    Run_Tree->SetBranchAddress("jetRawPt",&jetRawPt);
//   //    Run_Tree->SetBranchAddress("jetJECUnc",&jetJECUnc);
//   //    Run_Tree->SetBranchAddress("jetRawEn",&jetRawEn);
//   //    Run_Tree->SetBranchAddress("jetHadFlvr",&jetHadFlvr);
//   //    //    Run_Tree->SetBranchAddress("jetP4Smear",&jetP4Smear);
//   //    //    Run_Tree->SetBranchAddress("jetP4SmearUp",&jetP4SmearUp);
//   //    //    Run_Tree->SetBranchAddress("jetP4SmearDo",&jetP4SmearDo);
//   //
//   //
//   //
//   //    //########################################   MET Info
//   //    Run_Tree->SetBranchAddress("pfMET",&pfMET);
//   //    Run_Tree->SetBranchAddress("met_JESUp",&met_JESUp);
//   //    Run_Tree->SetBranchAddress("met_JESDown",&met_JESDown);
//   //    Run_Tree->SetBranchAddress("met_UESUp",&met_UESUp);
//   //    Run_Tree->SetBranchAddress("met_UESDown",&met_UESDown);
//   //
//   //
//   //    Run_Tree->SetBranchAddress("pfMETPhi",&pfMETPhi);
//   //    Run_Tree->SetBranchAddress("metphi_JESUp",&metphi_JESUp);
//   //    Run_Tree->SetBranchAddress("metphi_JESDown",&metphi_JESDown);
//   //    Run_Tree->SetBranchAddress("metphi_UESUp",&metphi_UESUp);
//   //    Run_Tree->SetBranchAddress("metphi_UESDown",&metphi_UESDown);
//   //
//   //    Run_Tree->SetBranchAddress("metFilters",&metFilters);
//   //    Run_Tree->SetBranchAddress("genHT",&genHT);
//   //
//   //    //    Run_Tree->SetBranchAddress("pdfSystWeight",&pdfSystWeight);
//   //    //    Run_Tree->SetBranchAddress("pdfSystWeightId",&pdfSystWeightId);
//   //    //    Run_Tree->SetBranchAddress("pdfWeight",&pdfWeight);
//   //
//   //
//   //
//   //    //########################################   Boosted Tau
//   //    Run_Tree->SetBranchAddress("nBoostedTau",&nBoostedTau);
//   //    Run_Tree->SetBranchAddress("boostedTauPt",&boostedTauPt);
//   //    Run_Tree->SetBranchAddress("boostedTauEta",&boostedTauEta);
//   //    Run_Tree->SetBranchAddress("boostedTauPhi",&boostedTauPhi);
//   //    Run_Tree->SetBranchAddress("boostedTauMass",&boostedTauMass);
//   //    Run_Tree->SetBranchAddress("boostedTauDecayMode",&boostedTauDecayMode);
//   //    Run_Tree->SetBranchAddress("boostedTauCharge",&boostedTauCharge);
//   //    Run_Tree->SetBranchAddress("boostedTauByLooseIsolationMVArun2v2DBoldDMwLT",&boostedTauByLooseIsolationMVArun2v2DBoldDMwLT);
//   //
//   //    Run_Tree->SetBranchAddress("boostedTaupfTausDiscriminationByDecayModeFinding",&boostedTaupfTausDiscriminationByDecayModeFinding);
//   //    Run_Tree->SetBranchAddress("boostedTauByMVA6VLooseElectronRejection",&boostedTauByMVA6VLooseElectronRejection);
//   //    Run_Tree->SetBranchAddress("boostedTauByMVA6TightElectronRejection",&boostedTauByMVA6TightElectronRejection);
//   //    Run_Tree->SetBranchAddress("boostedTauByTightMuonRejection3",&boostedTauByTightMuonRejection3);
//   //    Run_Tree->SetBranchAddress("boostedTauByLooseMuonRejection3",&boostedTauByLooseMuonRejection3);
//   //
//   //
//   //    Run_Tree->SetBranchAddress("boostedTauByTightIsolationMVArun2v1DBoldDMwLT",&boostedTauByTightIsolationMVArun2v1DBoldDMwLT);
//   //    Run_Tree->SetBranchAddress("boostedTauByMediumIsolationMVArun2v1DBoldDMwLT",&boostedTauByMediumIsolationMVArun2v1DBoldDMwLT);
//   //    Run_Tree->SetBranchAddress("boostedTauByLooseIsolationMVArun2v1DBoldDMwLT",&boostedTauByLooseIsolationMVArun2v1DBoldDMwLT);
//   //    Run_Tree->SetBranchAddress("boostedTauByVLooseIsolationMVArun2v1DBoldDMwLT",&boostedTauByVLooseIsolationMVArun2v1DBoldDMwLT);
//   //
//   //    Run_Tree->SetBranchAddress("boostedTauByIsolationMVArun2v1DBoldDMwLTraw",&boostedTauByIsolationMVArun2v1DBoldDMwLTraw);
//   //    Run_Tree->SetBranchAddress("boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits",&boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits);
//   //
//   //    Run_Tree->SetBranchAddress("boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits",&boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits);
//   //    Run_Tree->SetBranchAddress("boostedTauChargedIsoPtSum",&boostedTauChargedIsoPtSum);
//   //
//   //    Run_Tree->SetBranchAddress("boostedTauNeutralIsoPtSum"  ,&boostedTauNeutralIsoPtSum);
//   //
//   //
//   //    Run_Tree->SetBranchAddress("taudaugPt",&taudaugPt);
//   //    Run_Tree->SetBranchAddress("taudaugEta",&taudaugEta);
//   //    Run_Tree->SetBranchAddress("taudaugPhi",&taudaugPhi);
//   //    Run_Tree->SetBranchAddress("taudaugMass",&taudaugMass);
//   //    Run_Tree->SetBranchAddress("numGenTau",&numGenTau);
//   //
//   //
//   //
//       Run_Tree->SetBranchAddress("era", &era);
//       Run_Tree->SetBranchAddress("met_px", &met_px);
//       Run_Tree->SetBranchAddress("met_py", &met_py);
//       //    Run_Tree->SetBranchAddress("met", &met);
//       //    Run_Tree->SetBranchAddress("metphi", &metphi);
//       Run_Tree->SetBranchAddress("m_1", &m_1);
//       Run_Tree->SetBranchAddress("px_1", &px_1);
//       Run_Tree->SetBranchAddress("py_1", &py_1);
//       Run_Tree->SetBranchAddress("pz_1", &pz_1);
//       Run_Tree->SetBranchAddress("e_1", &e_1);
//       Run_Tree->SetBranchAddress("pt_1", &pt_1);
//       Run_Tree->SetBranchAddress("phi_1", &phi_1);
//       Run_Tree->SetBranchAddress("eta_1", &eta_1);
//       Run_Tree->SetBranchAddress("m_2", &m_2);
//       Run_Tree->SetBranchAddress("px_2", &px_2);
//       Run_Tree->SetBranchAddress("py_2", &py_2);
//       Run_Tree->SetBranchAddress("pz_2", &pz_2);
//       Run_Tree->SetBranchAddress("e_2", &e_2);
//       Run_Tree->SetBranchAddress("pt_2", &pt_2);
//       Run_Tree->SetBranchAddress("phi_2", &phi_2);
//       Run_Tree->SetBranchAddress("eta_2", &eta_2);
//       Run_Tree->SetBranchAddress("metcov00", &metcov00);
//       Run_Tree->SetBranchAddress("metcov01", &metcov01);
//       Run_Tree->SetBranchAddress("metcov10", &metcov10);
//       Run_Tree->SetBranchAddress("metcov11", &metcov11);
//       Run_Tree->SetBranchAddress("decayMode2", &decayMode2);
//       Run_Tree->SetBranchAddress("m_sv", &m_sv);
//       Run_Tree->SetBranchAddress("pt_sv", &pt_sv);
//   
//       Run_Tree->SetBranchAddress("lepIndex", &lepIndex);
//       Run_Tree->SetBranchAddress("tauIndex", &tauIndex);
//       Run_Tree->SetBranchAddress("decayMode1", &decayMode1);
//       Run_Tree->SetBranchAddress("leadtauIndex", &leadtauIndex);
//       Run_Tree->SetBranchAddress("subtauIndex", &subtauIndex);
//   //
//   //
//   //    Run_Tree->SetBranchAddress("boostedTauSignalPFCands"  ,&boostedTauSignalPFCands);
//   //    Run_Tree->SetBranchAddress("boostedTauSignalPFGammaCands"  ,&boostedTauSignalPFGammaCands);
//   //    Run_Tree->SetBranchAddress("boostedTauIsolationPFCands"  ,&boostedTauIsolationPFCands);
//   //    Run_Tree->SetBranchAddress("boostedTauIsolationPFGammaCands"  ,&boostedTauIsolationPFGammaCands);
//   //
//
//       return Run_Tree;
//   }
//






#endif // #ifdef boostHTT_cxx
