//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Apr 11 15:21:02 2019 by ROOT version 6.06/04
// from TTree EventTree/Event data (tag V09_04_13_01)
// found on file: DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8.root
//////////////////////////////////////////////////////////

#ifndef SkimerBoost_h
#define SkimerBoost_h

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


class SkimerBoost {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

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
   Float_t         pfMET_T1JERUp;
   Float_t         pfMET_T1JERDo;
   Float_t         pfMET_T1JESUp;
   Float_t         pfMET_T1JESDo;
   Float_t         pfMET_T1UESUp;
   Float_t         pfMET_T1UESDo;
   Float_t         pfMETPhi_T1JESUp;
   Float_t         pfMETPhi_T1JESDo;
   Float_t         pfMETPhi_T1UESUp;
   Float_t         pfMETPhi_T1UESDo;
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
   Int_t           nTau;
   vector<bool>    *taupfTausDiscriminationByDecayModeFinding;
   vector<bool>    *taupfTausDiscriminationByDecayModeFindingNewDMs;
   vector<bool>    *tauByMVA6VLooseElectronRejection;
   vector<bool>    *tauByMVA6LooseElectronRejection;
   vector<bool>    *tauByMVA6MediumElectronRejection;
   vector<bool>    *tauByMVA6TightElectronRejection;
   vector<bool>    *tauByMVA6VTightElectronRejection;
   vector<bool>    *tauByLooseMuonRejection3;
   vector<bool>    *tauByTightMuonRejection3;
   vector<bool>    *tauByLooseCombinedIsolationDeltaBetaCorr3Hits;
   vector<bool>    *tauByMediumCombinedIsolationDeltaBetaCorr3Hits;
   vector<bool>    *tauByTightCombinedIsolationDeltaBetaCorr3Hits;
   vector<float>   *tauCombinedIsolationDeltaBetaCorrRaw3Hits;
   vector<float>   *tauByIsolationMVArun2v1DBnewDMwLTraw;
   vector<float>   *tauByIsolationMVArun2v1DBoldDMwLTraw;
   vector<float>   *tauByIsolationMVArun2v1PWnewDMwLTraw;
   vector<float>   *tauByIsolationMVArun2v1PWoldDMwLTraw;
   vector<bool>    *tauByVTightIsolationMVArun2v1DBnewDMwLT;
   vector<bool>    *tauByVTightIsolationMVArun2v1DBoldDMwLT;
   vector<bool>    *tauByVTightIsolationMVArun2v1PWnewDMwLT;
   vector<bool>    *tauByVTightIsolationMVArun2v1PWoldDMwLT;
   vector<bool>    *tauByTightIsolationMVArun2v1DBnewDMwLT;
   vector<bool>    *tauByTightIsolationMVArun2v1DBoldDMwLT;
   vector<bool>    *tauByTightIsolationMVArun2v1PWnewDMwLT;
   vector<bool>    *tauByTightIsolationMVArun2v1PWoldDMwLT;
   vector<bool>    *tauByMediumIsolationMVArun2v1DBnewDMwLT;
   vector<bool>    *tauByMediumIsolationMVArun2v1DBoldDMwLT;
   vector<bool>    *tauByMediumIsolationMVArun2v1PWnewDMwLT;
   vector<bool>    *tauByMediumIsolationMVArun2v1PWoldDMwLT;
   vector<bool>    *tauByLooseIsolationMVArun2v1DBnewDMwLT;
   vector<bool>    *tauByLooseIsolationMVArun2v1DBoldDMwLT;
   vector<bool>    *tauByLooseIsolationMVArun2v1PWnewDMwLT;
   vector<bool>    *tauByLooseIsolationMVArun2v1PWoldDMwLT;
   vector<bool>    *tauByVLooseIsolationMVArun2v1DBnewDMwLT;
   vector<bool>    *tauByVLooseIsolationMVArun2v1DBoldDMwLT;
   vector<bool>    *tauByVLooseIsolationMVArun2v1PWnewDMwLT;
   vector<bool>    *tauByVLooseIsolationMVArun2v1PWoldDMwLT;
   vector<float>   *tauEta;
   vector<float>   *tauPhi;
   vector<float>   *tauPt;
   vector<float>   *tauEt;
   vector<float>   *tauCharge;
   vector<float>   *tauP;
   vector<float>   *tauPx;
   vector<float>   *tauPy;
   vector<float>   *tauPz;
   vector<float>   *tauVz;
   vector<float>   *tauEnergy;
   vector<float>   *tauMass;
   vector<float>   *tauDxy;
   vector<float>   *tauZImpact;
   vector<int>     *tauDecayMode;
   vector<bool>    *tauLeadChargedHadronExists;
   vector<float>   *tauLeadChargedHadronEta;
   vector<float>   *tauLeadChargedHadronPhi;
   vector<float>   *tauLeadChargedHadronPt;
   vector<float>   *tauChargedIsoPtSum;
   vector<float>   *tauNeutralIsoPtSum;
   vector<float>   *tauPuCorrPtSum;
   vector<int>     *tauNumSignalPFChargedHadrCands;
   vector<int>     *tauNumSignalPFNeutrHadrCands;
   vector<int>     *tauNumSignalPFGammaCands;
   vector<int>     *tauNumSignalPFCands;
   vector<int>     *tauNumIsolationPFChargedHadrCands;
   vector<int>     *tauNumIsolationPFNeutrHadrCands;
   vector<int>     *tauNumIsolationPFGammaCands;
   vector<int>     *tauNumIsolationPFCands;
   vector<float>   *taufootprintCorrection;
   vector<float>   *tauphotonPtSumOutsideSignalCone;
   vector<float>   *taudz;
   vector<float>   *taudxy;
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
   vector<bool>    *boostedTaupfTausDiscriminationByDecayModeFinding;
   vector<bool>    *boostedTaupfTausDiscriminationByDecayModeFindingNewDMs;
   vector<bool>    *boostedTauByMVA6VLooseElectronRejection;
   vector<bool>    *boostedTauByMVA6LooseElectronRejection;
   vector<bool>    *boostedTauByMVA6MediumElectronRejection;
   vector<bool>    *boostedTauByMVA6TightElectronRejection;
   vector<bool>    *boostedTauByMVA6VTightElectronRejection;
   vector<bool>    *boostedTauByLooseMuonRejection3;
   vector<bool>    *boostedTauByTightMuonRejection3;
   vector<bool>    *boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits;
   vector<bool>    *boostedTauByMediumCombinedIsolationDeltaBetaCorr3Hits;
   vector<bool>    *boostedTauByTightCombinedIsolationDeltaBetaCorr3Hits;
   vector<float>   *boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits;
   vector<float>   *boostedTauByIsolationMVArun2v1DBnewDMwLTraw;
   vector<float>   *boostedTauByIsolationMVArun2v1DBoldDMwLTraw;
   vector<float>   *boostedTauByIsolationMVArun2v1PWnewDMwLTraw;
   vector<float>   *boostedTauByIsolationMVArun2v1PWoldDMwLTraw;
   vector<bool>    *boostedTauByVTightIsolationMVArun2v1DBnewDMwLT;
   vector<bool>    *boostedTauByVTightIsolationMVArun2v1DBoldDMwLT;
   vector<bool>    *boostedTauByVTightIsolationMVArun2v1PWnewDMwLT;
   vector<bool>    *boostedTauByVTightIsolationMVArun2v1PWoldDMwLT;
   vector<bool>    *boostedTauByTightIsolationMVArun2v1DBnewDMwLT;
   vector<bool>    *boostedTauByTightIsolationMVArun2v1DBoldDMwLT;
   vector<bool>    *boostedTauByTightIsolationMVArun2v1PWnewDMwLT;
   vector<bool>    *boostedTauByTightIsolationMVArun2v1PWoldDMwLT;
   vector<bool>    *boostedTauByMediumIsolationMVArun2v1DBnewDMwLT;
   vector<bool>    *boostedTauByMediumIsolationMVArun2v1DBoldDMwLT;
   vector<bool>    *boostedTauByMediumIsolationMVArun2v1PWnewDMwLT;
   vector<bool>    *boostedTauByMediumIsolationMVArun2v1PWoldDMwLT;
   vector<bool>    *boostedTauByLooseIsolationMVArun2v1DBnewDMwLT;
   vector<bool>    *boostedTauByLooseIsolationMVArun2v1DBoldDMwLT;
   vector<bool>    *boostedTauByLooseIsolationMVArun2v1PWnewDMwLT;
   vector<bool>    *boostedTauByLooseIsolationMVArun2v1PWoldDMwLT;
   vector<bool>    *boostedTauByVLooseIsolationMVArun2v1DBnewDMwLT;
   vector<bool>    *boostedTauByVLooseIsolationMVArun2v1DBoldDMwLT;
   vector<bool>    *boostedTauByVLooseIsolationMVArun2v1PWnewDMwLT;
   vector<bool>    *boostedTauByVLooseIsolationMVArun2v1PWoldDMwLT;
   vector<float>   *boostedTauByIsolationMVArun2v2DBoldDMwLTraw;
   vector<bool>    *boostedTauByVTightIsolationMVArun2v2DBoldDMwLT;
   vector<bool>    *boostedTauByTightIsolationMVArun2v2DBoldDMwLT;
   vector<bool>    *boostedTauByMediumIsolationMVArun2v2DBoldDMwLT;
   vector<bool>    *boostedTauByLooseIsolationMVArun2v2DBoldDMwLT;
   vector<bool>    *boostedTauByVLooseIsolationMVArun2v2DBoldDMwLT;
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
   vector<float>   *boostedTauNeutralIsoPtSum;
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
   TBranch        *b_pfMET_T1JERUp;   //!
   TBranch        *b_pfMET_T1JERDo;   //!
   TBranch        *b_pfMET_T1JESUp;   //!
   TBranch        *b_pfMET_T1JESDo;   //!
   TBranch        *b_pfMET_T1UESUp;   //!
   TBranch        *b_pfMET_T1UESDo;   //!
   TBranch        *b_pfMETPhi_T1JESUp;   //!
   TBranch        *b_pfMETPhi_T1JESDo;   //!
   TBranch        *b_pfMETPhi_T1UESUp;   //!
   TBranch        *b_pfMETPhi_T1UESDo;   //!
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
   TBranch        *b_nTau;   //!
   TBranch        *b_taupfTausDiscriminationByDecayModeFinding;   //!
   TBranch        *b_taupfTausDiscriminationByDecayModeFindingNewDMs;   //!
   TBranch        *b_tauByMVA6VLooseElectronRejection;   //!
   TBranch        *b_tauByMVA6LooseElectronRejection;   //!
   TBranch        *b_tauByMVA6MediumElectronRejection;   //!
   TBranch        *b_tauByMVA6TightElectronRejection;   //!
   TBranch        *b_tauByMVA6VTightElectronRejection;   //!
   TBranch        *b_tauByLooseMuonRejection3;   //!
   TBranch        *b_tauByTightMuonRejection3;   //!
   TBranch        *b_tauByLooseCombinedIsolationDeltaBetaCorr3Hits;   //!
   TBranch        *b_tauByMediumCombinedIsolationDeltaBetaCorr3Hits;   //!
   TBranch        *b_tauByTightCombinedIsolationDeltaBetaCorr3Hits;   //!
   TBranch        *b_tauCombinedIsolationDeltaBetaCorrRaw3Hits;   //!
   TBranch        *b_tauByIsolationMVArun2v1DBnewDMwLTraw;   //!
   TBranch        *b_tauByIsolationMVArun2v1DBoldDMwLTraw;   //!
   TBranch        *b_tauByIsolationMVArun2v1PWnewDMwLTraw;   //!
   TBranch        *b_tauByIsolationMVArun2v1PWoldDMwLTraw;   //!
   TBranch        *b_tauByVTightIsolationMVArun2v1DBnewDMwLT;   //!
   TBranch        *b_tauByVTightIsolationMVArun2v1DBoldDMwLT;   //!
   TBranch        *b_tauByVTightIsolationMVArun2v1PWnewDMwLT;   //!
   TBranch        *b_tauByVTightIsolationMVArun2v1PWoldDMwLT;   //!
   TBranch        *b_tauByTightIsolationMVArun2v1DBnewDMwLT;   //!
   TBranch        *b_tauByTightIsolationMVArun2v1DBoldDMwLT;   //!
   TBranch        *b_tauByTightIsolationMVArun2v1PWnewDMwLT;   //!
   TBranch        *b_tauByTightIsolationMVArun2v1PWoldDMwLT;   //!
   TBranch        *b_tauByMediumIsolationMVArun2v1DBnewDMwLT;   //!
   TBranch        *b_tauByMediumIsolationMVArun2v1DBoldDMwLT;   //!
   TBranch        *b_tauByMediumIsolationMVArun2v1PWnewDMwLT;   //!
   TBranch        *b_tauByMediumIsolationMVArun2v1PWoldDMwLT;   //!
   TBranch        *b_tauByLooseIsolationMVArun2v1DBnewDMwLT;   //!
   TBranch        *b_tauByLooseIsolationMVArun2v1DBoldDMwLT;   //!
   TBranch        *b_tauByLooseIsolationMVArun2v1PWnewDMwLT;   //!
   TBranch        *b_tauByLooseIsolationMVArun2v1PWoldDMwLT;   //!
   TBranch        *b_tauByVLooseIsolationMVArun2v1DBnewDMwLT;   //!
   TBranch        *b_tauByVLooseIsolationMVArun2v1DBoldDMwLT;   //!
   TBranch        *b_tauByVLooseIsolationMVArun2v1PWnewDMwLT;   //!
   TBranch        *b_tauByVLooseIsolationMVArun2v1PWoldDMwLT;   //!
   TBranch        *b_tauEta;   //!
   TBranch        *b_tauPhi;   //!
   TBranch        *b_tauPt;   //!
   TBranch        *b_tauEt;   //!
   TBranch        *b_tauCharge;   //!
   TBranch        *b_tauP;   //!
   TBranch        *b_tauPx;   //!
   TBranch        *b_tauPy;   //!
   TBranch        *b_tauPz;   //!
   TBranch        *b_tauVz;   //!
   TBranch        *b_tauEnergy;   //!
   TBranch        *b_tauMass;   //!
   TBranch        *b_tauDxy;   //!
   TBranch        *b_tauZImpact;   //!
   TBranch        *b_tauDecayMode;   //!
   TBranch        *b_tauLeadChargedHadronExists;   //!
   TBranch        *b_tauLeadChargedHadronEta;   //!
   TBranch        *b_tauLeadChargedHadronPhi;   //!
   TBranch        *b_tauLeadChargedHadronPt;   //!
   TBranch        *b_tauChargedIsoPtSum;   //!
   TBranch        *b_tauNeutralIsoPtSum;   //!
   TBranch        *b_tauPuCorrPtSum;   //!
   TBranch        *b_tauNumSignalPFChargedHadrCands;   //!
   TBranch        *b_tauNumSignalPFNeutrHadrCands;   //!
   TBranch        *b_tauNumSignalPFGammaCands;   //!
   TBranch        *b_tauNumSignalPFCands;   //!
   TBranch        *b_tauNumIsolationPFChargedHadrCands;   //!
   TBranch        *b_tauNumIsolationPFNeutrHadrCands;   //!
   TBranch        *b_tauNumIsolationPFGammaCands;   //!
   TBranch        *b_tauNumIsolationPFCands;   //!
   TBranch        *b_taufootprintCorrection;   //!
   TBranch        *b_tauphotonPtSumOutsideSignalCone;   //!
   TBranch        *b_taudz;   //!
   TBranch        *b_taudxy;   //!
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
   TBranch        *b_boostedTaupfTausDiscriminationByDecayModeFinding;   //!
   TBranch        *b_boostedTaupfTausDiscriminationByDecayModeFindingNewDMs;   //!
   TBranch        *b_boostedTauByMVA6VLooseElectronRejection;   //!
   TBranch        *b_boostedTauByMVA6LooseElectronRejection;   //!
   TBranch        *b_boostedTauByMVA6MediumElectronRejection;   //!
   TBranch        *b_boostedTauByMVA6TightElectronRejection;   //!
   TBranch        *b_boostedTauByMVA6VTightElectronRejection;   //!
   TBranch        *b_boostedTauByLooseMuonRejection3;   //!
   TBranch        *b_boostedTauByTightMuonRejection3;   //!
   TBranch        *b_boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits;   //!
   TBranch        *b_boostedTauByMediumCombinedIsolationDeltaBetaCorr3Hits;   //!
   TBranch        *b_boostedTauByTightCombinedIsolationDeltaBetaCorr3Hits;   //!
   TBranch        *b_boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits;   //!
   TBranch        *b_boostedTauByIsolationMVArun2v1DBnewDMwLTraw;   //!
   TBranch        *b_boostedTauByIsolationMVArun2v1DBoldDMwLTraw;   //!
   TBranch        *b_boostedTauByIsolationMVArun2v1PWnewDMwLTraw;   //!
   TBranch        *b_boostedTauByIsolationMVArun2v1PWoldDMwLTraw;   //!
   TBranch        *b_boostedTauByVTightIsolationMVArun2v1DBnewDMwLT;   //!
   TBranch        *b_boostedTauByVTightIsolationMVArun2v1DBoldDMwLT;   //!
   TBranch        *b_boostedTauByVTightIsolationMVArun2v1PWnewDMwLT;   //!
   TBranch        *b_boostedTauByVTightIsolationMVArun2v1PWoldDMwLT;   //!
   TBranch        *b_boostedTauByTightIsolationMVArun2v1DBnewDMwLT;   //!
   TBranch        *b_boostedTauByTightIsolationMVArun2v1DBoldDMwLT;   //!
   TBranch        *b_boostedTauByTightIsolationMVArun2v1PWnewDMwLT;   //!
   TBranch        *b_boostedTauByTightIsolationMVArun2v1PWoldDMwLT;   //!
   TBranch        *b_boostedTauByMediumIsolationMVArun2v1DBnewDMwLT;   //!
   TBranch        *b_boostedTauByMediumIsolationMVArun2v1DBoldDMwLT;   //!
   TBranch        *b_boostedTauByMediumIsolationMVArun2v1PWnewDMwLT;   //!
   TBranch        *b_boostedTauByMediumIsolationMVArun2v1PWoldDMwLT;   //!
   TBranch        *b_boostedTauByLooseIsolationMVArun2v1DBnewDMwLT;   //!
   TBranch        *b_boostedTauByLooseIsolationMVArun2v1DBoldDMwLT;   //!
   TBranch        *b_boostedTauByLooseIsolationMVArun2v1PWnewDMwLT;   //!
   TBranch        *b_boostedTauByLooseIsolationMVArun2v1PWoldDMwLT;   //!
   TBranch        *b_boostedTauByVLooseIsolationMVArun2v1DBnewDMwLT;   //!
   TBranch        *b_boostedTauByVLooseIsolationMVArun2v1DBoldDMwLT;   //!
   TBranch        *b_boostedTauByVLooseIsolationMVArun2v1PWnewDMwLT;   //!
   TBranch        *b_boostedTauByVLooseIsolationMVArun2v1PWoldDMwLT;   //!
   TBranch        *b_boostedTauByIsolationMVArun2v2DBoldDMwLTraw;   //!
   TBranch        *b_boostedTauByVTightIsolationMVArun2v2DBoldDMwLT;   //!
   TBranch        *b_boostedTauByTightIsolationMVArun2v2DBoldDMwLT;   //!
   TBranch        *b_boostedTauByMediumIsolationMVArun2v2DBoldDMwLT;   //!
   TBranch        *b_boostedTauByLooseIsolationMVArun2v2DBoldDMwLT;   //!
   TBranch        *b_boostedTauByVLooseIsolationMVArun2v2DBoldDMwLT;   //!
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
   TBranch        *b_boostedTauNeutralIsoPtSum;   //!
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

   SkimerBoost(TString fileNamem);
   virtual ~SkimerBoost();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(TString outputFile,int split);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef SkimerBoost_cxx
SkimerBoost::SkimerBoost(TString fileName) : fChain(0)
{
    // if parameter tree is not specified (or zero), connect the file
    // used to generate this class and read the Tree.
    TFile* file = TFile::Open(fileName);
    //    file->cd(fileName + ":/ggNtuplizer");
    //    lllll
    //TTree* tree = (TTree*)gDirectory->Get("EventTree");
    TTree* tree = (TTree*)gDirectory->Get("ggNtuplizer/EventTree");
    Init(tree);
}



SkimerBoost::~SkimerBoost()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t SkimerBoost::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t SkimerBoost::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void SkimerBoost::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   pdf = 0;
   EventTag = 0;
   nPU = 0;
   puBX = 0;
   puTrue = 0;
   mcPID = 0;
   mcVtx = 0;
   mcVty = 0;
   mcVtz = 0;
   mcPt = 0;
   mcMass = 0;
   mcEta = 0;
   mcPhi = 0;
   mcE = 0;
   mcEt = 0;
   mcGMomPID = 0;
   mcMomPID = 0;
   mcMomPt = 0;
   mcMomMass = 0;
   mcMomEta = 0;
   mcMomPhi = 0;
   mcStatusFlag = 0;
   mcParentage = 0;
   mcStatus = 0;
   mcCalIsoDR03 = 0;
   mcTrkIsoDR03 = 0;
   mcCalIsoDR04 = 0;
   mcTrkIsoDR04 = 0;
   eleCharge = 0;
   eleChargeConsistent = 0;
   eleEn = 0;
   eleSCEn = 0;
   eleEcalEn = 0;
   eleESEnP1 = 0;
   eleESEnP2 = 0;
   eleD0 = 0;
   eleDz = 0;
   eleSIP = 0;
   elePt = 0;
   elePtError = 0;
   eleEta = 0;
   elePhi = 0;
   eleR9 = 0;
   eleCalibPt = 0;
   eleCalibEn = 0;
   eleSCEta = 0;
   eleSCPhi = 0;
   eleSCRawEn = 0;
   eleSCEtaWidth = 0;
   eleSCPhiWidth = 0;
   eleHoverE = 0;
   eleEoverP = 0;
   eleEoverPout = 0;
   eleEoverPInv = 0;
   eleBrem = 0;
   eledEtaAtVtx = 0;
   eledPhiAtVtx = 0;
   eleSigmaIEtaIEtaFull5x5 = 0;
   eleSigmaIPhiIPhiFull5x5 = 0;
   eleConvVeto = 0;
   eleMissHits = 0;
   eleESEffSigmaRR = 0;
   elePFChIso = 0;
   elePFPhoIso = 0;
   elePFNeuIso = 0;
   elePFPUIso = 0;
   elePFClusEcalIso = 0;
   elePFClusHcalIso = 0;
   eleIDMVAIso = 0;
   eleIDMVANoIso = 0;
   eleR9Full5x5 = 0;
   eleEcalDrivenSeed = 0;
   eleTrkdxy = 0;
   eleKFHits = 0;
   eleKFChi2 = 0;
   eleGSFChi2 = 0;
   eleGSFPt = 0;
   eleGSFEta = 0;
   eleGSFPhi = 0;
   eleGSFCharge = 0;
   eleGSFHits = 0;
   eleGSFMissHits = 0;
   eleGSFNHitsMax = 0;
   eleGSFVtxProb = 0;
   eleGSFlxyPV = 0;
   eleGSFlxyBS = 0;
   eleFiredSingleTrgs = 0;
   eleFiredDoubleTrgs = 0;
   eleFiredL1Trgs = 0;
   eleIDbit = 0;
   eleScale_stat_up = 0;
   eleScale_stat_dn = 0;
   eleScale_syst_up = 0;
   eleScale_syst_dn = 0;
   eleScale_gain_up = 0;
   eleScale_gain_dn = 0;
   eleResol_rho_up = 0;
   eleResol_rho_dn = 0;
   eleResol_phi_up = 0;
   eleResol_phi_dn = 0;
   muPt = 0;
   muEn = 0;
   muEta = 0;
   muPhi = 0;
   muCharge = 0;
   muType = 0;
   muIDbit = 0;
   muD0 = 0;
   muDz = 0;
   muSIP = 0;
   muChi2NDF = 0;
   muInnerD0 = 0;
   muInnerDz = 0;
   muTrkLayers = 0;
   muPixelLayers = 0;
   muPixelHits = 0;
   muMuonHits = 0;
   muStations = 0;
   muMatches = 0;
   muTrkQuality = 0;
   muIsoTrk = 0;
   muPFChIso = 0;
   muPFPhoIso = 0;
   muPFNeuIso = 0;
   muPFPUIso = 0;
   muPFChIso03 = 0;
   muPFPhoIso03 = 0;
   muPFNeuIso03 = 0;
   muPFPUIso03 = 0;
   muFiredTrgs = 0;
   muFiredL1Trgs = 0;
   muInnervalidFraction = 0;
   musegmentCompatibility = 0;
   muchi2LocalPosition = 0;
   mutrkKink = 0;
   muBestTrkPtError = 0;
   muBestTrkPt = 0;
   muBestTrkType = 0;
   taupfTausDiscriminationByDecayModeFinding = 0;
   taupfTausDiscriminationByDecayModeFindingNewDMs = 0;
   tauByMVA6VLooseElectronRejection = 0;
   tauByMVA6LooseElectronRejection = 0;
   tauByMVA6MediumElectronRejection = 0;
   tauByMVA6TightElectronRejection = 0;
   tauByMVA6VTightElectronRejection = 0;
   tauByLooseMuonRejection3 = 0;
   tauByTightMuonRejection3 = 0;
   tauByLooseCombinedIsolationDeltaBetaCorr3Hits = 0;
   tauByMediumCombinedIsolationDeltaBetaCorr3Hits = 0;
   tauByTightCombinedIsolationDeltaBetaCorr3Hits = 0;
   tauCombinedIsolationDeltaBetaCorrRaw3Hits = 0;
   tauByIsolationMVArun2v1DBnewDMwLTraw = 0;
   tauByIsolationMVArun2v1DBoldDMwLTraw = 0;
   tauByIsolationMVArun2v1PWnewDMwLTraw = 0;
   tauByIsolationMVArun2v1PWoldDMwLTraw = 0;
   tauByVTightIsolationMVArun2v1DBnewDMwLT = 0;
   tauByVTightIsolationMVArun2v1DBoldDMwLT = 0;
   tauByVTightIsolationMVArun2v1PWnewDMwLT = 0;
   tauByVTightIsolationMVArun2v1PWoldDMwLT = 0;
   tauByTightIsolationMVArun2v1DBnewDMwLT = 0;
   tauByTightIsolationMVArun2v1DBoldDMwLT = 0;
   tauByTightIsolationMVArun2v1PWnewDMwLT = 0;
   tauByTightIsolationMVArun2v1PWoldDMwLT = 0;
   tauByMediumIsolationMVArun2v1DBnewDMwLT = 0;
   tauByMediumIsolationMVArun2v1DBoldDMwLT = 0;
   tauByMediumIsolationMVArun2v1PWnewDMwLT = 0;
   tauByMediumIsolationMVArun2v1PWoldDMwLT = 0;
   tauByLooseIsolationMVArun2v1DBnewDMwLT = 0;
   tauByLooseIsolationMVArun2v1DBoldDMwLT = 0;
   tauByLooseIsolationMVArun2v1PWnewDMwLT = 0;
   tauByLooseIsolationMVArun2v1PWoldDMwLT = 0;
   tauByVLooseIsolationMVArun2v1DBnewDMwLT = 0;
   tauByVLooseIsolationMVArun2v1DBoldDMwLT = 0;
   tauByVLooseIsolationMVArun2v1PWnewDMwLT = 0;
   tauByVLooseIsolationMVArun2v1PWoldDMwLT = 0;
   tauEta = 0;
   tauPhi = 0;
   tauPt = 0;
   tauEt = 0;
   tauCharge = 0;
   tauP = 0;
   tauPx = 0;
   tauPy = 0;
   tauPz = 0;
   tauVz = 0;
   tauEnergy = 0;
   tauMass = 0;
   tauDxy = 0;
   tauZImpact = 0;
   tauDecayMode = 0;
   tauLeadChargedHadronExists = 0;
   tauLeadChargedHadronEta = 0;
   tauLeadChargedHadronPhi = 0;
   tauLeadChargedHadronPt = 0;
   tauChargedIsoPtSum = 0;
   tauNeutralIsoPtSum = 0;
   tauPuCorrPtSum = 0;
   tauNumSignalPFChargedHadrCands = 0;
   tauNumSignalPFNeutrHadrCands = 0;
   tauNumSignalPFGammaCands = 0;
   tauNumSignalPFCands = 0;
   tauNumIsolationPFChargedHadrCands = 0;
   tauNumIsolationPFNeutrHadrCands = 0;
   tauNumIsolationPFGammaCands = 0;
   tauNumIsolationPFCands = 0;
   taufootprintCorrection = 0;
   tauphotonPtSumOutsideSignalCone = 0;
   taudz = 0;
   taudxy = 0;
   jetPt = 0;
   jetEn = 0;
   jetEta = 0;
   jetPhi = 0;
   jetRawPt = 0;
   jetRawEn = 0;
   jetMt = 0;
   jetArea = 0;
   jetLeadTrackPt = 0;
   jetLeadTrackEta = 0;
   jetLeadTrackPhi = 0;
   jetLepTrackPID = 0;
   jetLepTrackPt = 0;
   jetLepTrackEta = 0;
   jetLepTrackPhi = 0;
   jetCSV2BJetTags = 0;
   jetDeepCSVTags_b = 0;
   jetDeepCSVTags_bb = 0;
   jetDeepCSVTags_c = 0;
   jetDeepCSVTags_udsg = 0;
   jetPartonID = 0;
   jetHadFlvr = 0;
   jetGenJetEn = 0;
   jetGenJetPt = 0;
   jetGenJetEta = 0;
   jetGenJetPhi = 0;
   jetGenPartonID = 0;
   jetGenEn = 0;
   jetGenPt = 0;
   jetGenEta = 0;
   jetGenPhi = 0;
   jetGenPartonMomID = 0;
   jetP4Smear = 0;
   jetP4SmearUp = 0;
   jetP4SmearDo = 0;
   jetPFLooseId = 0;
   jetID = 0;
   jetPUID = 0;
   jetPUFullID = 0;
   jetJECUnc = 0;
   jetFiredTrgs = 0;
   jetCHF = 0;
   jetNHF = 0;
   jetCEF = 0;
   jetNEF = 0;
   jetNCH = 0;
   jetNNP = 0;
   jetMUF = 0;
   jetVtxPt = 0;
   jetVtxMass = 0;
   jetVtxNtrks = 0;
   jetVtx3DVal = 0;
   jetVtx3DSig = 0;
   boostedTaupfTausDiscriminationByDecayModeFinding = 0;
   boostedTaupfTausDiscriminationByDecayModeFindingNewDMs = 0;
   boostedTauByMVA6VLooseElectronRejection = 0;
   boostedTauByMVA6LooseElectronRejection = 0;
   boostedTauByMVA6MediumElectronRejection = 0;
   boostedTauByMVA6TightElectronRejection = 0;
   boostedTauByMVA6VTightElectronRejection = 0;
   boostedTauByLooseMuonRejection3 = 0;
   boostedTauByTightMuonRejection3 = 0;
   boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits = 0;
   boostedTauByMediumCombinedIsolationDeltaBetaCorr3Hits = 0;
   boostedTauByTightCombinedIsolationDeltaBetaCorr3Hits = 0;
   boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits = 0;
   boostedTauByIsolationMVArun2v1DBnewDMwLTraw = 0;
   boostedTauByIsolationMVArun2v1DBoldDMwLTraw = 0;
   boostedTauByIsolationMVArun2v1PWnewDMwLTraw = 0;
   boostedTauByIsolationMVArun2v1PWoldDMwLTraw = 0;
   boostedTauByVTightIsolationMVArun2v1DBnewDMwLT = 0;
   boostedTauByVTightIsolationMVArun2v1DBoldDMwLT = 0;
   boostedTauByVTightIsolationMVArun2v1PWnewDMwLT = 0;
   boostedTauByVTightIsolationMVArun2v1PWoldDMwLT = 0;
   boostedTauByTightIsolationMVArun2v1DBnewDMwLT = 0;
   boostedTauByTightIsolationMVArun2v1DBoldDMwLT = 0;
   boostedTauByTightIsolationMVArun2v1PWnewDMwLT = 0;
   boostedTauByTightIsolationMVArun2v1PWoldDMwLT = 0;
   boostedTauByMediumIsolationMVArun2v1DBnewDMwLT = 0;
   boostedTauByMediumIsolationMVArun2v1DBoldDMwLT = 0;
   boostedTauByMediumIsolationMVArun2v1PWnewDMwLT = 0;
   boostedTauByMediumIsolationMVArun2v1PWoldDMwLT = 0;
   boostedTauByLooseIsolationMVArun2v1DBnewDMwLT = 0;
   boostedTauByLooseIsolationMVArun2v1DBoldDMwLT = 0;
   boostedTauByLooseIsolationMVArun2v1PWnewDMwLT = 0;
   boostedTauByLooseIsolationMVArun2v1PWoldDMwLT = 0;
   boostedTauByVLooseIsolationMVArun2v1DBnewDMwLT = 0;
   boostedTauByVLooseIsolationMVArun2v1DBoldDMwLT = 0;
   boostedTauByVLooseIsolationMVArun2v1PWnewDMwLT = 0;
   boostedTauByVLooseIsolationMVArun2v1PWoldDMwLT = 0;
   boostedTauByIsolationMVArun2v2DBoldDMwLTraw = 0;
   boostedTauByVTightIsolationMVArun2v2DBoldDMwLT = 0;
   boostedTauByTightIsolationMVArun2v2DBoldDMwLT = 0;
   boostedTauByMediumIsolationMVArun2v2DBoldDMwLT = 0;
   boostedTauByLooseIsolationMVArun2v2DBoldDMwLT = 0;
   boostedTauByVLooseIsolationMVArun2v2DBoldDMwLT = 0;
   boostedTauEta = 0;
   boostedTauPhi = 0;
   boostedTauPt = 0;
   boostedTauEt = 0;
   boostedTauCharge = 0;
   boostedTauP = 0;
   boostedTauPx = 0;
   boostedTauPy = 0;
   boostedTauPz = 0;
   boostedTauVz = 0;
   boostedTauEnergy = 0;
   boostedTauMass = 0;
   boostedTauDxy = 0;
   boostedTauZImpact = 0;
   boostedTauDecayMode = 0;
   boostedTauLeadChargedHadronExists = 0;
   boostedTauLeadChargedHadronEta = 0;
   boostedTauLeadChargedHadronPhi = 0;
   boostedTauLeadChargedHadronPt = 0;
   boostedTauChargedIsoPtSum = 0;
   boostedTauNeutralIsoPtSum = 0;
   boostedTauPuCorrPtSum = 0;
   boostedTauNumSignalPFChargedHadrCands = 0;
   boostedTauNumSignalPFNeutrHadrCands = 0;
   boostedTauNumSignalPFGammaCands = 0;
   boostedTauNumSignalPFCands = 0;
   boostedTauNumIsolationPFChargedHadrCands = 0;
   boostedTauNumIsolationPFNeutrHadrCands = 0;
   boostedTauNumIsolationPFGammaCands = 0;
   boostedTauNumIsolationPFCands = 0;
   boostedTaufootprintCorrection = 0;
   boostedTauphotonPtSumOutsideSignalCone = 0;
   boostedTaudz = 0;
   boostedTaudxy = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("lumis", &lumis, &b_lumis);
   fChain->SetBranchAddress("isData", &isData, &b_isData);
   fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
   fChain->SetBranchAddress("nGoodVtx", &nGoodVtx, &b_nGoodVtx);
   fChain->SetBranchAddress("isPVGood", &isPVGood, &b_isPVGood);
   fChain->SetBranchAddress("vtx", &vtx, &b_vtx);
   fChain->SetBranchAddress("vty", &vty, &b_vty);
   fChain->SetBranchAddress("vtz", &vtz, &b_vtz);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("rhoCentral", &rhoCentral, &b_rhoCentral);
   fChain->SetBranchAddress("HLTEleMuX", &HLTEleMuX, &b_HLTEleMuX);
   fChain->SetBranchAddress("HLTPho", &HLTPho, &b_HLTPho);
   fChain->SetBranchAddress("HLTPhoRejectedByPS", &HLTPhoRejectedByPS, &b_HLTPhoRejectedByPS);
   fChain->SetBranchAddress("HLTJet", &HLTJet, &b_HLTJet);
   fChain->SetBranchAddress("HLTEleMuXIsPrescaled", &HLTEleMuXIsPrescaled, &b_HLTEleMuXIsPrescaled);
   fChain->SetBranchAddress("HLTPhoIsPrescaled", &HLTPhoIsPrescaled, &b_HLTPhoIsPrescaled);
   fChain->SetBranchAddress("HLTJetIsPrescaled", &HLTJetIsPrescaled, &b_HLTJetIsPrescaled);
   fChain->SetBranchAddress("pdf", &pdf, &b_pdf);
   fChain->SetBranchAddress("pthat", &pthat, &b_pthat);
   fChain->SetBranchAddress("processID", &processID, &b_processID);
   fChain->SetBranchAddress("genWeight", &genWeight, &b_genWeight);
   fChain->SetBranchAddress("genHT", &genHT, &b_genHT);
   fChain->SetBranchAddress("genPho1", &genPho1, &b_genPho1);
   fChain->SetBranchAddress("genPho2", &genPho2, &b_genPho2);
   fChain->SetBranchAddress("EventTag", &EventTag, &b_EventTag);
   fChain->SetBranchAddress("nPUInfo", &nPUInfo, &b_nPUInfo);
   fChain->SetBranchAddress("nPU", &nPU, &b_nPU);
   fChain->SetBranchAddress("puBX", &puBX, &b_puBX);
   fChain->SetBranchAddress("puTrue", &puTrue, &b_puTrue);
   fChain->SetBranchAddress("nMC", &nMC, &b_nMC);
   fChain->SetBranchAddress("mcPID", &mcPID, &b_mcPID);
   fChain->SetBranchAddress("mcVtx", &mcVtx, &b_mcVtx);
   fChain->SetBranchAddress("mcVty", &mcVty, &b_mcVty);
   fChain->SetBranchAddress("mcVtz", &mcVtz, &b_mcVtz);
   fChain->SetBranchAddress("mcPt", &mcPt, &b_mcPt);
   fChain->SetBranchAddress("mcMass", &mcMass, &b_mcMass);
   fChain->SetBranchAddress("mcEta", &mcEta, &b_mcEta);
   fChain->SetBranchAddress("mcPhi", &mcPhi, &b_mcPhi);
   fChain->SetBranchAddress("mcE", &mcE, &b_mcE);
   fChain->SetBranchAddress("mcEt", &mcEt, &b_mcEt);
   fChain->SetBranchAddress("mcGMomPID", &mcGMomPID, &b_mcGMomPID);
   fChain->SetBranchAddress("mcMomPID", &mcMomPID, &b_mcMomPID);
   fChain->SetBranchAddress("mcMomPt", &mcMomPt, &b_mcMomPt);
   fChain->SetBranchAddress("mcMomMass", &mcMomMass, &b_mcMomMass);
   fChain->SetBranchAddress("mcMomEta", &mcMomEta, &b_mcMomEta);
   fChain->SetBranchAddress("mcMomPhi", &mcMomPhi, &b_mcMomPhi);
   fChain->SetBranchAddress("mcStatusFlag", &mcStatusFlag, &b_mcStatusFlag);
   fChain->SetBranchAddress("mcParentage", &mcParentage, &b_mcParentage);
   fChain->SetBranchAddress("mcStatus", &mcStatus, &b_mcStatus);
   fChain->SetBranchAddress("mcCalIsoDR03", &mcCalIsoDR03, &b_mcCalIsoDR03);
   fChain->SetBranchAddress("mcTrkIsoDR03", &mcTrkIsoDR03, &b_mcTrkIsoDR03);
   fChain->SetBranchAddress("mcCalIsoDR04", &mcCalIsoDR04, &b_mcCalIsoDR04);
   fChain->SetBranchAddress("mcTrkIsoDR04", &mcTrkIsoDR04, &b_mcTrkIsoDR04);
   fChain->SetBranchAddress("genMET", &genMET, &b_genMET);
   fChain->SetBranchAddress("genMETPhi", &genMETPhi, &b_genMETPhi);
   fChain->SetBranchAddress("metFilters", &metFilters, &b_metFilters);
   fChain->SetBranchAddress("pfMET", &pfMET, &b_pfMET);
   fChain->SetBranchAddress("pfMETPhi", &pfMETPhi, &b_pfMETPhi);
   fChain->SetBranchAddress("pfMET_T1JERUp", &pfMET_T1JERUp, &b_pfMET_T1JERUp);
   fChain->SetBranchAddress("pfMET_T1JERDo", &pfMET_T1JERDo, &b_pfMET_T1JERDo);
   fChain->SetBranchAddress("pfMET_T1JESUp", &pfMET_T1JESUp, &b_pfMET_T1JESUp);
   fChain->SetBranchAddress("pfMET_T1JESDo", &pfMET_T1JESDo, &b_pfMET_T1JESDo);
   fChain->SetBranchAddress("pfMET_T1UESUp", &pfMET_T1UESUp, &b_pfMET_T1UESUp);
   fChain->SetBranchAddress("pfMET_T1UESDo", &pfMET_T1UESDo, &b_pfMET_T1UESDo);
   fChain->SetBranchAddress("pfMETPhi_T1JESUp", &pfMETPhi_T1JESUp, &b_pfMETPhi_T1JESUp);
   fChain->SetBranchAddress("pfMETPhi_T1JESDo", &pfMETPhi_T1JESDo, &b_pfMETPhi_T1JESDo);
   fChain->SetBranchAddress("pfMETPhi_T1UESUp", &pfMETPhi_T1UESUp, &b_pfMETPhi_T1UESUp);
   fChain->SetBranchAddress("pfMETPhi_T1UESDo", &pfMETPhi_T1UESDo, &b_pfMETPhi_T1UESDo);
   fChain->SetBranchAddress("nEle", &nEle, &b_nEle);
   fChain->SetBranchAddress("eleCharge", &eleCharge, &b_eleCharge);
   fChain->SetBranchAddress("eleChargeConsistent", &eleChargeConsistent, &b_eleChargeConsistent);
   fChain->SetBranchAddress("eleEn", &eleEn, &b_eleEn);
   fChain->SetBranchAddress("eleSCEn", &eleSCEn, &b_eleSCEn);
   fChain->SetBranchAddress("eleEcalEn", &eleEcalEn, &b_eleEcalEn);
   fChain->SetBranchAddress("eleESEnP1", &eleESEnP1, &b_eleESEnP1);
   fChain->SetBranchAddress("eleESEnP2", &eleESEnP2, &b_eleESEnP2);
   fChain->SetBranchAddress("eleD0", &eleD0, &b_eleD0);
   fChain->SetBranchAddress("eleDz", &eleDz, &b_eleDz);
   fChain->SetBranchAddress("eleSIP", &eleSIP, &b_eleSIP);
   fChain->SetBranchAddress("elePt", &elePt, &b_elePt);
   fChain->SetBranchAddress("elePtError", &elePtError, &b_elePtError);
   fChain->SetBranchAddress("eleEta", &eleEta, &b_eleEta);
   fChain->SetBranchAddress("elePhi", &elePhi, &b_elePhi);
   fChain->SetBranchAddress("eleR9", &eleR9, &b_eleR9);
   fChain->SetBranchAddress("eleCalibPt", &eleCalibPt, &b_eleCalibPt);
   fChain->SetBranchAddress("eleCalibEn", &eleCalibEn, &b_eleCalibEn);
   fChain->SetBranchAddress("eleSCEta", &eleSCEta, &b_eleSCEta);
   fChain->SetBranchAddress("eleSCPhi", &eleSCPhi, &b_eleSCPhi);
   fChain->SetBranchAddress("eleSCRawEn", &eleSCRawEn, &b_eleSCRawEn);
   fChain->SetBranchAddress("eleSCEtaWidth", &eleSCEtaWidth, &b_eleSCEtaWidth);
   fChain->SetBranchAddress("eleSCPhiWidth", &eleSCPhiWidth, &b_eleSCPhiWidth);
   fChain->SetBranchAddress("eleHoverE", &eleHoverE, &b_eleHoverE);
   fChain->SetBranchAddress("eleEoverP", &eleEoverP, &b_eleEoverP);
   fChain->SetBranchAddress("eleEoverPout", &eleEoverPout, &b_eleEoverPout);
   fChain->SetBranchAddress("eleEoverPInv", &eleEoverPInv, &b_eleEoverPInv);
   fChain->SetBranchAddress("eleBrem", &eleBrem, &b_eleBrem);
   fChain->SetBranchAddress("eledEtaAtVtx", &eledEtaAtVtx, &b_eledEtaAtVtx);
   fChain->SetBranchAddress("eledPhiAtVtx", &eledPhiAtVtx, &b_eledPhiAtVtx);
   fChain->SetBranchAddress("eleSigmaIEtaIEtaFull5x5", &eleSigmaIEtaIEtaFull5x5, &b_eleSigmaIEtaIEtaFull5x5);
   fChain->SetBranchAddress("eleSigmaIPhiIPhiFull5x5", &eleSigmaIPhiIPhiFull5x5, &b_eleSigmaIPhiIPhiFull5x5);
   fChain->SetBranchAddress("eleConvVeto", &eleConvVeto, &b_eleConvVeto);
   fChain->SetBranchAddress("eleMissHits", &eleMissHits, &b_eleMissHits);
   fChain->SetBranchAddress("eleESEffSigmaRR", &eleESEffSigmaRR, &b_eleESEffSigmaRR);
   fChain->SetBranchAddress("elePFChIso", &elePFChIso, &b_elePFChIso);
   fChain->SetBranchAddress("elePFPhoIso", &elePFPhoIso, &b_elePFPhoIso);
   fChain->SetBranchAddress("elePFNeuIso", &elePFNeuIso, &b_elePFNeuIso);
   fChain->SetBranchAddress("elePFPUIso", &elePFPUIso, &b_elePFPUIso);
   fChain->SetBranchAddress("elePFClusEcalIso", &elePFClusEcalIso, &b_elePFClusEcalIso);
   fChain->SetBranchAddress("elePFClusHcalIso", &elePFClusHcalIso, &b_elePFClusHcalIso);
   fChain->SetBranchAddress("eleIDMVAIso", &eleIDMVAIso, &b_eleIDMVAIso);
   fChain->SetBranchAddress("eleIDMVANoIso", &eleIDMVANoIso, &b_eleIDMVANoIso);
   fChain->SetBranchAddress("eleR9Full5x5", &eleR9Full5x5, &b_eleR9Full5x5);
   fChain->SetBranchAddress("eleEcalDrivenSeed", &eleEcalDrivenSeed, &b_eleEcalDrivenSeed);
   fChain->SetBranchAddress("eleTrkdxy", &eleTrkdxy, &b_eleTrkdxy);
   fChain->SetBranchAddress("eleKFHits", &eleKFHits, &b_eleKFHits);
   fChain->SetBranchAddress("eleKFChi2", &eleKFChi2, &b_eleKFChi2);
   fChain->SetBranchAddress("eleGSFChi2", &eleGSFChi2, &b_eleGSFChi2);
   fChain->SetBranchAddress("eleGSFPt", &eleGSFPt, &b_eleGSFPt);
   fChain->SetBranchAddress("eleGSFEta", &eleGSFEta, &b_eleGSFEta);
   fChain->SetBranchAddress("eleGSFPhi", &eleGSFPhi, &b_eleGSFPhi);
   fChain->SetBranchAddress("eleGSFCharge", &eleGSFCharge, &b_eleGSFCharge);
   fChain->SetBranchAddress("eleGSFHits", &eleGSFHits, &b_eleGSFHits);
   fChain->SetBranchAddress("eleGSFMissHits", &eleGSFMissHits, &b_eleGSFMissHits);
   fChain->SetBranchAddress("eleGSFNHitsMax", &eleGSFNHitsMax, &b_eleGSFNHitsMax);
   fChain->SetBranchAddress("eleGSFVtxProb", &eleGSFVtxProb, &b_eleGSFVtxProb);
   fChain->SetBranchAddress("eleGSFlxyPV", &eleGSFlxyPV, &b_eleGSFlxyPV);
   fChain->SetBranchAddress("eleGSFlxyBS", &eleGSFlxyBS, &b_eleGSFlxyBS);
   fChain->SetBranchAddress("eleFiredSingleTrgs", &eleFiredSingleTrgs, &b_eleFiredSingleTrgs);
   fChain->SetBranchAddress("eleFiredDoubleTrgs", &eleFiredDoubleTrgs, &b_eleFiredDoubleTrgs);
   fChain->SetBranchAddress("eleFiredL1Trgs", &eleFiredL1Trgs, &b_eleFiredL1Trgs);
   fChain->SetBranchAddress("eleIDbit", &eleIDbit, &b_eleIDbit);
   fChain->SetBranchAddress("eleScale_stat_up", &eleScale_stat_up, &b_eleScale_stat_up);
   fChain->SetBranchAddress("eleScale_stat_dn", &eleScale_stat_dn, &b_eleScale_stat_dn);
   fChain->SetBranchAddress("eleScale_syst_up", &eleScale_syst_up, &b_eleScale_syst_up);
   fChain->SetBranchAddress("eleScale_syst_dn", &eleScale_syst_dn, &b_eleScale_syst_dn);
   fChain->SetBranchAddress("eleScale_gain_up", &eleScale_gain_up, &b_eleScale_gain_up);
   fChain->SetBranchAddress("eleScale_gain_dn", &eleScale_gain_dn, &b_eleScale_gain_dn);
   fChain->SetBranchAddress("eleResol_rho_up", &eleResol_rho_up, &b_eleResol_rho_up);
   fChain->SetBranchAddress("eleResol_rho_dn", &eleResol_rho_dn, &b_eleResol_rho_dn);
   fChain->SetBranchAddress("eleResol_phi_up", &eleResol_phi_up, &b_eleResol_phi_up);
   fChain->SetBranchAddress("eleResol_phi_dn", &eleResol_phi_dn, &b_eleResol_phi_dn);
   fChain->SetBranchAddress("nMu", &nMu, &b_nMu);
   fChain->SetBranchAddress("muPt", &muPt, &b_muPt);
   fChain->SetBranchAddress("muEn", &muEn, &b_muEn);
   fChain->SetBranchAddress("muEta", &muEta, &b_muEta);
   fChain->SetBranchAddress("muPhi", &muPhi, &b_muPhi);
   fChain->SetBranchAddress("muCharge", &muCharge, &b_muCharge);
   fChain->SetBranchAddress("muType", &muType, &b_muType);
   fChain->SetBranchAddress("muIDbit", &muIDbit, &b_muIDbit);
   fChain->SetBranchAddress("muD0", &muD0, &b_muD0);
   fChain->SetBranchAddress("muDz", &muDz, &b_muDz);
   fChain->SetBranchAddress("muSIP", &muSIP, &b_muSIP);
   fChain->SetBranchAddress("muChi2NDF", &muChi2NDF, &b_muChi2NDF);
   fChain->SetBranchAddress("muInnerD0", &muInnerD0, &b_muInnerD0);
   fChain->SetBranchAddress("muInnerDz", &muInnerDz, &b_muInnerDz);
   fChain->SetBranchAddress("muTrkLayers", &muTrkLayers, &b_muTrkLayers);
   fChain->SetBranchAddress("muPixelLayers", &muPixelLayers, &b_muPixelLayers);
   fChain->SetBranchAddress("muPixelHits", &muPixelHits, &b_muPixelHits);
   fChain->SetBranchAddress("muMuonHits", &muMuonHits, &b_muMuonHits);
   fChain->SetBranchAddress("muStations", &muStations, &b_muStations);
   fChain->SetBranchAddress("muMatches", &muMatches, &b_muMatches);
   fChain->SetBranchAddress("muTrkQuality", &muTrkQuality, &b_muTrkQuality);
   fChain->SetBranchAddress("muIsoTrk", &muIsoTrk, &b_muIsoTrk);
   fChain->SetBranchAddress("muPFChIso", &muPFChIso, &b_muPFChIso);
   fChain->SetBranchAddress("muPFPhoIso", &muPFPhoIso, &b_muPFPhoIso);
   fChain->SetBranchAddress("muPFNeuIso", &muPFNeuIso, &b_muPFNeuIso);
   fChain->SetBranchAddress("muPFPUIso", &muPFPUIso, &b_muPFPUIso);
   fChain->SetBranchAddress("muPFChIso03", &muPFChIso03, &b_muPFChIso03);
   fChain->SetBranchAddress("muPFPhoIso03", &muPFPhoIso03, &b_muPFPhoIso03);
   fChain->SetBranchAddress("muPFNeuIso03", &muPFNeuIso03, &b_muPFNeuIso03);
   fChain->SetBranchAddress("muPFPUIso03", &muPFPUIso03, &b_muPFPUIso03);
   fChain->SetBranchAddress("muFiredTrgs", &muFiredTrgs, &b_muFiredTrgs);
   fChain->SetBranchAddress("muFiredL1Trgs", &muFiredL1Trgs, &b_muFiredL1Trgs);
   fChain->SetBranchAddress("muInnervalidFraction", &muInnervalidFraction, &b_muInnervalidFraction);
   fChain->SetBranchAddress("musegmentCompatibility", &musegmentCompatibility, &b_musegmentCompatibility);
   fChain->SetBranchAddress("muchi2LocalPosition", &muchi2LocalPosition, &b_muchi2LocalPosition);
   fChain->SetBranchAddress("mutrkKink", &mutrkKink, &b_mutrkKink);
   fChain->SetBranchAddress("muBestTrkPtError", &muBestTrkPtError, &b_muBestTrkPtError);
   fChain->SetBranchAddress("muBestTrkPt", &muBestTrkPt, &b_muBestTrkPt);
   fChain->SetBranchAddress("muBestTrkType", &muBestTrkType, &b_muBestTrkType);
   fChain->SetBranchAddress("nTau", &nTau, &b_nTau);
   fChain->SetBranchAddress("taupfTausDiscriminationByDecayModeFinding", &taupfTausDiscriminationByDecayModeFinding, &b_taupfTausDiscriminationByDecayModeFinding);
   fChain->SetBranchAddress("taupfTausDiscriminationByDecayModeFindingNewDMs", &taupfTausDiscriminationByDecayModeFindingNewDMs, &b_taupfTausDiscriminationByDecayModeFindingNewDMs);
   fChain->SetBranchAddress("tauByMVA6VLooseElectronRejection", &tauByMVA6VLooseElectronRejection, &b_tauByMVA6VLooseElectronRejection);
   fChain->SetBranchAddress("tauByMVA6LooseElectronRejection", &tauByMVA6LooseElectronRejection, &b_tauByMVA6LooseElectronRejection);
   fChain->SetBranchAddress("tauByMVA6MediumElectronRejection", &tauByMVA6MediumElectronRejection, &b_tauByMVA6MediumElectronRejection);
   fChain->SetBranchAddress("tauByMVA6TightElectronRejection", &tauByMVA6TightElectronRejection, &b_tauByMVA6TightElectronRejection);
   fChain->SetBranchAddress("tauByMVA6VTightElectronRejection", &tauByMVA6VTightElectronRejection, &b_tauByMVA6VTightElectronRejection);
   fChain->SetBranchAddress("tauByLooseMuonRejection3", &tauByLooseMuonRejection3, &b_tauByLooseMuonRejection3);
   fChain->SetBranchAddress("tauByTightMuonRejection3", &tauByTightMuonRejection3, &b_tauByTightMuonRejection3);
   fChain->SetBranchAddress("tauByLooseCombinedIsolationDeltaBetaCorr3Hits", &tauByLooseCombinedIsolationDeltaBetaCorr3Hits, &b_tauByLooseCombinedIsolationDeltaBetaCorr3Hits);
   fChain->SetBranchAddress("tauByMediumCombinedIsolationDeltaBetaCorr3Hits", &tauByMediumCombinedIsolationDeltaBetaCorr3Hits, &b_tauByMediumCombinedIsolationDeltaBetaCorr3Hits);
   fChain->SetBranchAddress("tauByTightCombinedIsolationDeltaBetaCorr3Hits", &tauByTightCombinedIsolationDeltaBetaCorr3Hits, &b_tauByTightCombinedIsolationDeltaBetaCorr3Hits);
   fChain->SetBranchAddress("tauCombinedIsolationDeltaBetaCorrRaw3Hits", &tauCombinedIsolationDeltaBetaCorrRaw3Hits, &b_tauCombinedIsolationDeltaBetaCorrRaw3Hits);
   fChain->SetBranchAddress("tauByIsolationMVArun2v1DBnewDMwLTraw", &tauByIsolationMVArun2v1DBnewDMwLTraw, &b_tauByIsolationMVArun2v1DBnewDMwLTraw);
   fChain->SetBranchAddress("tauByIsolationMVArun2v1DBoldDMwLTraw", &tauByIsolationMVArun2v1DBoldDMwLTraw, &b_tauByIsolationMVArun2v1DBoldDMwLTraw);
   fChain->SetBranchAddress("tauByIsolationMVArun2v1PWnewDMwLTraw", &tauByIsolationMVArun2v1PWnewDMwLTraw, &b_tauByIsolationMVArun2v1PWnewDMwLTraw);
   fChain->SetBranchAddress("tauByIsolationMVArun2v1PWoldDMwLTraw", &tauByIsolationMVArun2v1PWoldDMwLTraw, &b_tauByIsolationMVArun2v1PWoldDMwLTraw);
   fChain->SetBranchAddress("tauByVTightIsolationMVArun2v1DBnewDMwLT", &tauByVTightIsolationMVArun2v1DBnewDMwLT, &b_tauByVTightIsolationMVArun2v1DBnewDMwLT);
   fChain->SetBranchAddress("tauByVTightIsolationMVArun2v1DBoldDMwLT", &tauByVTightIsolationMVArun2v1DBoldDMwLT, &b_tauByVTightIsolationMVArun2v1DBoldDMwLT);
   fChain->SetBranchAddress("tauByVTightIsolationMVArun2v1PWnewDMwLT", &tauByVTightIsolationMVArun2v1PWnewDMwLT, &b_tauByVTightIsolationMVArun2v1PWnewDMwLT);
   fChain->SetBranchAddress("tauByVTightIsolationMVArun2v1PWoldDMwLT", &tauByVTightIsolationMVArun2v1PWoldDMwLT, &b_tauByVTightIsolationMVArun2v1PWoldDMwLT);
   fChain->SetBranchAddress("tauByTightIsolationMVArun2v1DBnewDMwLT", &tauByTightIsolationMVArun2v1DBnewDMwLT, &b_tauByTightIsolationMVArun2v1DBnewDMwLT);
   fChain->SetBranchAddress("tauByTightIsolationMVArun2v1DBoldDMwLT", &tauByTightIsolationMVArun2v1DBoldDMwLT, &b_tauByTightIsolationMVArun2v1DBoldDMwLT);
   fChain->SetBranchAddress("tauByTightIsolationMVArun2v1PWnewDMwLT", &tauByTightIsolationMVArun2v1PWnewDMwLT, &b_tauByTightIsolationMVArun2v1PWnewDMwLT);
   fChain->SetBranchAddress("tauByTightIsolationMVArun2v1PWoldDMwLT", &tauByTightIsolationMVArun2v1PWoldDMwLT, &b_tauByTightIsolationMVArun2v1PWoldDMwLT);
   fChain->SetBranchAddress("tauByMediumIsolationMVArun2v1DBnewDMwLT", &tauByMediumIsolationMVArun2v1DBnewDMwLT, &b_tauByMediumIsolationMVArun2v1DBnewDMwLT);
   fChain->SetBranchAddress("tauByMediumIsolationMVArun2v1DBoldDMwLT", &tauByMediumIsolationMVArun2v1DBoldDMwLT, &b_tauByMediumIsolationMVArun2v1DBoldDMwLT);
   fChain->SetBranchAddress("tauByMediumIsolationMVArun2v1PWnewDMwLT", &tauByMediumIsolationMVArun2v1PWnewDMwLT, &b_tauByMediumIsolationMVArun2v1PWnewDMwLT);
   fChain->SetBranchAddress("tauByMediumIsolationMVArun2v1PWoldDMwLT", &tauByMediumIsolationMVArun2v1PWoldDMwLT, &b_tauByMediumIsolationMVArun2v1PWoldDMwLT);
   fChain->SetBranchAddress("tauByLooseIsolationMVArun2v1DBnewDMwLT", &tauByLooseIsolationMVArun2v1DBnewDMwLT, &b_tauByLooseIsolationMVArun2v1DBnewDMwLT);
   fChain->SetBranchAddress("tauByLooseIsolationMVArun2v1DBoldDMwLT", &tauByLooseIsolationMVArun2v1DBoldDMwLT, &b_tauByLooseIsolationMVArun2v1DBoldDMwLT);
   fChain->SetBranchAddress("tauByLooseIsolationMVArun2v1PWnewDMwLT", &tauByLooseIsolationMVArun2v1PWnewDMwLT, &b_tauByLooseIsolationMVArun2v1PWnewDMwLT);
   fChain->SetBranchAddress("tauByLooseIsolationMVArun2v1PWoldDMwLT", &tauByLooseIsolationMVArun2v1PWoldDMwLT, &b_tauByLooseIsolationMVArun2v1PWoldDMwLT);
   fChain->SetBranchAddress("tauByVLooseIsolationMVArun2v1DBnewDMwLT", &tauByVLooseIsolationMVArun2v1DBnewDMwLT, &b_tauByVLooseIsolationMVArun2v1DBnewDMwLT);
   fChain->SetBranchAddress("tauByVLooseIsolationMVArun2v1DBoldDMwLT", &tauByVLooseIsolationMVArun2v1DBoldDMwLT, &b_tauByVLooseIsolationMVArun2v1DBoldDMwLT);
   fChain->SetBranchAddress("tauByVLooseIsolationMVArun2v1PWnewDMwLT", &tauByVLooseIsolationMVArun2v1PWnewDMwLT, &b_tauByVLooseIsolationMVArun2v1PWnewDMwLT);
   fChain->SetBranchAddress("tauByVLooseIsolationMVArun2v1PWoldDMwLT", &tauByVLooseIsolationMVArun2v1PWoldDMwLT, &b_tauByVLooseIsolationMVArun2v1PWoldDMwLT);
   fChain->SetBranchAddress("tauEta", &tauEta, &b_tauEta);
   fChain->SetBranchAddress("tauPhi", &tauPhi, &b_tauPhi);
   fChain->SetBranchAddress("tauPt", &tauPt, &b_tauPt);
   fChain->SetBranchAddress("tauEt", &tauEt, &b_tauEt);
   fChain->SetBranchAddress("tauCharge", &tauCharge, &b_tauCharge);
   fChain->SetBranchAddress("tauP", &tauP, &b_tauP);
   fChain->SetBranchAddress("tauPx", &tauPx, &b_tauPx);
   fChain->SetBranchAddress("tauPy", &tauPy, &b_tauPy);
   fChain->SetBranchAddress("tauPz", &tauPz, &b_tauPz);
   fChain->SetBranchAddress("tauVz", &tauVz, &b_tauVz);
   fChain->SetBranchAddress("tauEnergy", &tauEnergy, &b_tauEnergy);
   fChain->SetBranchAddress("tauMass", &tauMass, &b_tauMass);
   fChain->SetBranchAddress("tauDxy", &tauDxy, &b_tauDxy);
   fChain->SetBranchAddress("tauZImpact", &tauZImpact, &b_tauZImpact);
   fChain->SetBranchAddress("tauDecayMode", &tauDecayMode, &b_tauDecayMode);
   fChain->SetBranchAddress("tauLeadChargedHadronExists", &tauLeadChargedHadronExists, &b_tauLeadChargedHadronExists);
   fChain->SetBranchAddress("tauLeadChargedHadronEta", &tauLeadChargedHadronEta, &b_tauLeadChargedHadronEta);
   fChain->SetBranchAddress("tauLeadChargedHadronPhi", &tauLeadChargedHadronPhi, &b_tauLeadChargedHadronPhi);
   fChain->SetBranchAddress("tauLeadChargedHadronPt", &tauLeadChargedHadronPt, &b_tauLeadChargedHadronPt);
   fChain->SetBranchAddress("tauChargedIsoPtSum", &tauChargedIsoPtSum, &b_tauChargedIsoPtSum);
   fChain->SetBranchAddress("tauNeutralIsoPtSum", &tauNeutralIsoPtSum, &b_tauNeutralIsoPtSum);
   fChain->SetBranchAddress("tauPuCorrPtSum", &tauPuCorrPtSum, &b_tauPuCorrPtSum);
   fChain->SetBranchAddress("tauNumSignalPFChargedHadrCands", &tauNumSignalPFChargedHadrCands, &b_tauNumSignalPFChargedHadrCands);
   fChain->SetBranchAddress("tauNumSignalPFNeutrHadrCands", &tauNumSignalPFNeutrHadrCands, &b_tauNumSignalPFNeutrHadrCands);
   fChain->SetBranchAddress("tauNumSignalPFGammaCands", &tauNumSignalPFGammaCands, &b_tauNumSignalPFGammaCands);
   fChain->SetBranchAddress("tauNumSignalPFCands", &tauNumSignalPFCands, &b_tauNumSignalPFCands);
   fChain->SetBranchAddress("tauNumIsolationPFChargedHadrCands", &tauNumIsolationPFChargedHadrCands, &b_tauNumIsolationPFChargedHadrCands);
   fChain->SetBranchAddress("tauNumIsolationPFNeutrHadrCands", &tauNumIsolationPFNeutrHadrCands, &b_tauNumIsolationPFNeutrHadrCands);
   fChain->SetBranchAddress("tauNumIsolationPFGammaCands", &tauNumIsolationPFGammaCands, &b_tauNumIsolationPFGammaCands);
   fChain->SetBranchAddress("tauNumIsolationPFCands", &tauNumIsolationPFCands, &b_tauNumIsolationPFCands);
   fChain->SetBranchAddress("taufootprintCorrection", &taufootprintCorrection, &b_taufootprintCorrection);
   fChain->SetBranchAddress("tauphotonPtSumOutsideSignalCone", &tauphotonPtSumOutsideSignalCone, &b_tauphotonPtSumOutsideSignalCone);
   fChain->SetBranchAddress("taudz", &taudz, &b_taudz);
   fChain->SetBranchAddress("taudxy", &taudxy, &b_taudxy);
   fChain->SetBranchAddress("nJet", &nJet, &b_nJet);
   fChain->SetBranchAddress("jetPt", &jetPt, &b_jetPt);
   fChain->SetBranchAddress("jetEn", &jetEn, &b_jetEn);
   fChain->SetBranchAddress("jetEta", &jetEta, &b_jetEta);
   fChain->SetBranchAddress("jetPhi", &jetPhi, &b_jetPhi);
   fChain->SetBranchAddress("jetRawPt", &jetRawPt, &b_jetRawPt);
   fChain->SetBranchAddress("jetRawEn", &jetRawEn, &b_jetRawEn);
   fChain->SetBranchAddress("jetMt", &jetMt, &b_jetMt);
   fChain->SetBranchAddress("jetArea", &jetArea, &b_jetArea);
   fChain->SetBranchAddress("jetLeadTrackPt", &jetLeadTrackPt, &b_jetLeadTrackPt);
   fChain->SetBranchAddress("jetLeadTrackEta", &jetLeadTrackEta, &b_jetLeadTrackEta);
   fChain->SetBranchAddress("jetLeadTrackPhi", &jetLeadTrackPhi, &b_jetLeadTrackPhi);
   fChain->SetBranchAddress("jetLepTrackPID", &jetLepTrackPID, &b_jetLepTrackPID);
   fChain->SetBranchAddress("jetLepTrackPt", &jetLepTrackPt, &b_jetLepTrackPt);
   fChain->SetBranchAddress("jetLepTrackEta", &jetLepTrackEta, &b_jetLepTrackEta);
   fChain->SetBranchAddress("jetLepTrackPhi", &jetLepTrackPhi, &b_jetLepTrackPhi);
   fChain->SetBranchAddress("jetCSV2BJetTags", &jetCSV2BJetTags, &b_jetCSV2BJetTags);
   fChain->SetBranchAddress("jetDeepCSVTags_b", &jetDeepCSVTags_b, &b_jetDeepCSVTags_b);
   fChain->SetBranchAddress("jetDeepCSVTags_bb", &jetDeepCSVTags_bb, &b_jetDeepCSVTags_bb);
   fChain->SetBranchAddress("jetDeepCSVTags_c", &jetDeepCSVTags_c, &b_jetDeepCSVTags_c);
   fChain->SetBranchAddress("jetDeepCSVTags_udsg", &jetDeepCSVTags_udsg, &b_jetDeepCSVTags_udsg);
   fChain->SetBranchAddress("jetPartonID", &jetPartonID, &b_jetPartonID);
   fChain->SetBranchAddress("jetHadFlvr", &jetHadFlvr, &b_jetHadFlvr);
   fChain->SetBranchAddress("jetGenJetEn", &jetGenJetEn, &b_jetGenJetEn);
   fChain->SetBranchAddress("jetGenJetPt", &jetGenJetPt, &b_jetGenJetPt);
   fChain->SetBranchAddress("jetGenJetEta", &jetGenJetEta, &b_jetGenJetEta);
   fChain->SetBranchAddress("jetGenJetPhi", &jetGenJetPhi, &b_jetGenJetPhi);
   fChain->SetBranchAddress("jetGenPartonID", &jetGenPartonID, &b_jetGenPartonID);
   fChain->SetBranchAddress("jetGenEn", &jetGenEn, &b_jetGenEn);
   fChain->SetBranchAddress("jetGenPt", &jetGenPt, &b_jetGenPt);
   fChain->SetBranchAddress("jetGenEta", &jetGenEta, &b_jetGenEta);
   fChain->SetBranchAddress("jetGenPhi", &jetGenPhi, &b_jetGenPhi);
   fChain->SetBranchAddress("jetGenPartonMomID", &jetGenPartonMomID, &b_jetGenPartonMomID);
   fChain->SetBranchAddress("jetP4Smear", &jetP4Smear, &b_jetP4Smear);
   fChain->SetBranchAddress("jetP4SmearUp", &jetP4SmearUp, &b_jetP4SmearUp);
   fChain->SetBranchAddress("jetP4SmearDo", &jetP4SmearDo, &b_jetP4SmearDo);
   fChain->SetBranchAddress("jetPFLooseId", &jetPFLooseId, &b_jetPFLooseId);
   fChain->SetBranchAddress("jetID", &jetID, &b_jetID);
   fChain->SetBranchAddress("jetPUID", &jetPUID, &b_jetPUID);
   fChain->SetBranchAddress("jetPUFullID", &jetPUFullID, &b_jetPUFullID);
   fChain->SetBranchAddress("jetJECUnc", &jetJECUnc, &b_jetJECUnc);
   fChain->SetBranchAddress("jetFiredTrgs", &jetFiredTrgs, &b_jetFiredTrgs);
   fChain->SetBranchAddress("jetCHF", &jetCHF, &b_jetCHF);
   fChain->SetBranchAddress("jetNHF", &jetNHF, &b_jetNHF);
   fChain->SetBranchAddress("jetCEF", &jetCEF, &b_jetCEF);
   fChain->SetBranchAddress("jetNEF", &jetNEF, &b_jetNEF);
   fChain->SetBranchAddress("jetNCH", &jetNCH, &b_jetNCH);
   fChain->SetBranchAddress("jetNNP", &jetNNP, &b_jetNNP);
   fChain->SetBranchAddress("jetMUF", &jetMUF, &b_jetMUF);
   fChain->SetBranchAddress("jetVtxPt", &jetVtxPt, &b_jetVtxPt);
   fChain->SetBranchAddress("jetVtxMass", &jetVtxMass, &b_jetVtxMass);
   fChain->SetBranchAddress("jetVtxNtrks", &jetVtxNtrks, &b_jetVtxNtrks);
   fChain->SetBranchAddress("jetVtx3DVal", &jetVtx3DVal, &b_jetVtx3DVal);
   fChain->SetBranchAddress("jetVtx3DSig", &jetVtx3DSig, &b_jetVtx3DSig);
   fChain->SetBranchAddress("nBoostedTau", &nBoostedTau, &b_nBoostedTau);
   fChain->SetBranchAddress("boostedTaupfTausDiscriminationByDecayModeFinding", &boostedTaupfTausDiscriminationByDecayModeFinding, &b_boostedTaupfTausDiscriminationByDecayModeFinding);
   fChain->SetBranchAddress("boostedTaupfTausDiscriminationByDecayModeFindingNewDMs", &boostedTaupfTausDiscriminationByDecayModeFindingNewDMs, &b_boostedTaupfTausDiscriminationByDecayModeFindingNewDMs);
   fChain->SetBranchAddress("boostedTauByMVA6VLooseElectronRejection", &boostedTauByMVA6VLooseElectronRejection, &b_boostedTauByMVA6VLooseElectronRejection);
   fChain->SetBranchAddress("boostedTauByMVA6LooseElectronRejection", &boostedTauByMVA6LooseElectronRejection, &b_boostedTauByMVA6LooseElectronRejection);
   fChain->SetBranchAddress("boostedTauByMVA6MediumElectronRejection", &boostedTauByMVA6MediumElectronRejection, &b_boostedTauByMVA6MediumElectronRejection);
   fChain->SetBranchAddress("boostedTauByMVA6TightElectronRejection", &boostedTauByMVA6TightElectronRejection, &b_boostedTauByMVA6TightElectronRejection);
   fChain->SetBranchAddress("boostedTauByMVA6VTightElectronRejection", &boostedTauByMVA6VTightElectronRejection, &b_boostedTauByMVA6VTightElectronRejection);
   fChain->SetBranchAddress("boostedTauByLooseMuonRejection3", &boostedTauByLooseMuonRejection3, &b_boostedTauByLooseMuonRejection3);
   fChain->SetBranchAddress("boostedTauByTightMuonRejection3", &boostedTauByTightMuonRejection3, &b_boostedTauByTightMuonRejection3);
   fChain->SetBranchAddress("boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits", &boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits, &b_boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits);
   fChain->SetBranchAddress("boostedTauByMediumCombinedIsolationDeltaBetaCorr3Hits", &boostedTauByMediumCombinedIsolationDeltaBetaCorr3Hits, &b_boostedTauByMediumCombinedIsolationDeltaBetaCorr3Hits);
   fChain->SetBranchAddress("boostedTauByTightCombinedIsolationDeltaBetaCorr3Hits", &boostedTauByTightCombinedIsolationDeltaBetaCorr3Hits, &b_boostedTauByTightCombinedIsolationDeltaBetaCorr3Hits);
   fChain->SetBranchAddress("boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits", &boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits, &b_boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits);
   fChain->SetBranchAddress("boostedTauByIsolationMVArun2v1DBnewDMwLTraw", &boostedTauByIsolationMVArun2v1DBnewDMwLTraw, &b_boostedTauByIsolationMVArun2v1DBnewDMwLTraw);
   fChain->SetBranchAddress("boostedTauByIsolationMVArun2v1DBoldDMwLTraw", &boostedTauByIsolationMVArun2v1DBoldDMwLTraw, &b_boostedTauByIsolationMVArun2v1DBoldDMwLTraw);
   fChain->SetBranchAddress("boostedTauByIsolationMVArun2v1PWnewDMwLTraw", &boostedTauByIsolationMVArun2v1PWnewDMwLTraw, &b_boostedTauByIsolationMVArun2v1PWnewDMwLTraw);
   fChain->SetBranchAddress("boostedTauByIsolationMVArun2v1PWoldDMwLTraw", &boostedTauByIsolationMVArun2v1PWoldDMwLTraw, &b_boostedTauByIsolationMVArun2v1PWoldDMwLTraw);
   fChain->SetBranchAddress("boostedTauByVTightIsolationMVArun2v1DBnewDMwLT", &boostedTauByVTightIsolationMVArun2v1DBnewDMwLT, &b_boostedTauByVTightIsolationMVArun2v1DBnewDMwLT);
   fChain->SetBranchAddress("boostedTauByVTightIsolationMVArun2v1DBoldDMwLT", &boostedTauByVTightIsolationMVArun2v1DBoldDMwLT, &b_boostedTauByVTightIsolationMVArun2v1DBoldDMwLT);
   fChain->SetBranchAddress("boostedTauByVTightIsolationMVArun2v1PWnewDMwLT", &boostedTauByVTightIsolationMVArun2v1PWnewDMwLT, &b_boostedTauByVTightIsolationMVArun2v1PWnewDMwLT);
   fChain->SetBranchAddress("boostedTauByVTightIsolationMVArun2v1PWoldDMwLT", &boostedTauByVTightIsolationMVArun2v1PWoldDMwLT, &b_boostedTauByVTightIsolationMVArun2v1PWoldDMwLT);
   fChain->SetBranchAddress("boostedTauByTightIsolationMVArun2v1DBnewDMwLT", &boostedTauByTightIsolationMVArun2v1DBnewDMwLT, &b_boostedTauByTightIsolationMVArun2v1DBnewDMwLT);
   fChain->SetBranchAddress("boostedTauByTightIsolationMVArun2v1DBoldDMwLT", &boostedTauByTightIsolationMVArun2v1DBoldDMwLT, &b_boostedTauByTightIsolationMVArun2v1DBoldDMwLT);
   fChain->SetBranchAddress("boostedTauByTightIsolationMVArun2v1PWnewDMwLT", &boostedTauByTightIsolationMVArun2v1PWnewDMwLT, &b_boostedTauByTightIsolationMVArun2v1PWnewDMwLT);
   fChain->SetBranchAddress("boostedTauByTightIsolationMVArun2v1PWoldDMwLT", &boostedTauByTightIsolationMVArun2v1PWoldDMwLT, &b_boostedTauByTightIsolationMVArun2v1PWoldDMwLT);
   fChain->SetBranchAddress("boostedTauByMediumIsolationMVArun2v1DBnewDMwLT", &boostedTauByMediumIsolationMVArun2v1DBnewDMwLT, &b_boostedTauByMediumIsolationMVArun2v1DBnewDMwLT);
   fChain->SetBranchAddress("boostedTauByMediumIsolationMVArun2v1DBoldDMwLT", &boostedTauByMediumIsolationMVArun2v1DBoldDMwLT, &b_boostedTauByMediumIsolationMVArun2v1DBoldDMwLT);
   fChain->SetBranchAddress("boostedTauByMediumIsolationMVArun2v1PWnewDMwLT", &boostedTauByMediumIsolationMVArun2v1PWnewDMwLT, &b_boostedTauByMediumIsolationMVArun2v1PWnewDMwLT);
   fChain->SetBranchAddress("boostedTauByMediumIsolationMVArun2v1PWoldDMwLT", &boostedTauByMediumIsolationMVArun2v1PWoldDMwLT, &b_boostedTauByMediumIsolationMVArun2v1PWoldDMwLT);
   fChain->SetBranchAddress("boostedTauByLooseIsolationMVArun2v1DBnewDMwLT", &boostedTauByLooseIsolationMVArun2v1DBnewDMwLT, &b_boostedTauByLooseIsolationMVArun2v1DBnewDMwLT);
   fChain->SetBranchAddress("boostedTauByLooseIsolationMVArun2v1DBoldDMwLT", &boostedTauByLooseIsolationMVArun2v1DBoldDMwLT, &b_boostedTauByLooseIsolationMVArun2v1DBoldDMwLT);
   fChain->SetBranchAddress("boostedTauByLooseIsolationMVArun2v1PWnewDMwLT", &boostedTauByLooseIsolationMVArun2v1PWnewDMwLT, &b_boostedTauByLooseIsolationMVArun2v1PWnewDMwLT);
   fChain->SetBranchAddress("boostedTauByLooseIsolationMVArun2v1PWoldDMwLT", &boostedTauByLooseIsolationMVArun2v1PWoldDMwLT, &b_boostedTauByLooseIsolationMVArun2v1PWoldDMwLT);
   fChain->SetBranchAddress("boostedTauByVLooseIsolationMVArun2v1DBnewDMwLT", &boostedTauByVLooseIsolationMVArun2v1DBnewDMwLT, &b_boostedTauByVLooseIsolationMVArun2v1DBnewDMwLT);
   fChain->SetBranchAddress("boostedTauByVLooseIsolationMVArun2v1DBoldDMwLT", &boostedTauByVLooseIsolationMVArun2v1DBoldDMwLT, &b_boostedTauByVLooseIsolationMVArun2v1DBoldDMwLT);
   fChain->SetBranchAddress("boostedTauByVLooseIsolationMVArun2v1PWnewDMwLT", &boostedTauByVLooseIsolationMVArun2v1PWnewDMwLT, &b_boostedTauByVLooseIsolationMVArun2v1PWnewDMwLT);
   fChain->SetBranchAddress("boostedTauByVLooseIsolationMVArun2v1PWoldDMwLT", &boostedTauByVLooseIsolationMVArun2v1PWoldDMwLT, &b_boostedTauByVLooseIsolationMVArun2v1PWoldDMwLT);
   fChain->SetBranchAddress("boostedTauByIsolationMVArun2v2DBoldDMwLTraw", &boostedTauByIsolationMVArun2v2DBoldDMwLTraw, &b_boostedTauByIsolationMVArun2v2DBoldDMwLTraw);
   fChain->SetBranchAddress("boostedTauByVTightIsolationMVArun2v2DBoldDMwLT", &boostedTauByVTightIsolationMVArun2v2DBoldDMwLT, &b_boostedTauByVTightIsolationMVArun2v2DBoldDMwLT);
   fChain->SetBranchAddress("boostedTauByTightIsolationMVArun2v2DBoldDMwLT", &boostedTauByTightIsolationMVArun2v2DBoldDMwLT, &b_boostedTauByTightIsolationMVArun2v2DBoldDMwLT);
   fChain->SetBranchAddress("boostedTauByMediumIsolationMVArun2v2DBoldDMwLT", &boostedTauByMediumIsolationMVArun2v2DBoldDMwLT, &b_boostedTauByMediumIsolationMVArun2v2DBoldDMwLT);
   fChain->SetBranchAddress("boostedTauByLooseIsolationMVArun2v2DBoldDMwLT", &boostedTauByLooseIsolationMVArun2v2DBoldDMwLT, &b_boostedTauByLooseIsolationMVArun2v2DBoldDMwLT);
   fChain->SetBranchAddress("boostedTauByVLooseIsolationMVArun2v2DBoldDMwLT", &boostedTauByVLooseIsolationMVArun2v2DBoldDMwLT, &b_boostedTauByVLooseIsolationMVArun2v2DBoldDMwLT);
   fChain->SetBranchAddress("boostedTauEta", &boostedTauEta, &b_boostedTauEta);
   fChain->SetBranchAddress("boostedTauPhi", &boostedTauPhi, &b_boostedTauPhi);
   fChain->SetBranchAddress("boostedTauPt", &boostedTauPt, &b_boostedTauPt);
   fChain->SetBranchAddress("boostedTauEt", &boostedTauEt, &b_boostedTauEt);
   fChain->SetBranchAddress("boostedTauCharge", &boostedTauCharge, &b_boostedTauCharge);
   fChain->SetBranchAddress("boostedTauP", &boostedTauP, &b_boostedTauP);
   fChain->SetBranchAddress("boostedTauPx", &boostedTauPx, &b_boostedTauPx);
   fChain->SetBranchAddress("boostedTauPy", &boostedTauPy, &b_boostedTauPy);
   fChain->SetBranchAddress("boostedTauPz", &boostedTauPz, &b_boostedTauPz);
   fChain->SetBranchAddress("boostedTauVz", &boostedTauVz, &b_boostedTauVz);
   fChain->SetBranchAddress("boostedTauEnergy", &boostedTauEnergy, &b_boostedTauEnergy);
   fChain->SetBranchAddress("boostedTauMass", &boostedTauMass, &b_boostedTauMass);
   fChain->SetBranchAddress("boostedTauDxy", &boostedTauDxy, &b_boostedTauDxy);
   fChain->SetBranchAddress("boostedTauZImpact", &boostedTauZImpact, &b_boostedTauZImpact);
   fChain->SetBranchAddress("boostedTauDecayMode", &boostedTauDecayMode, &b_boostedTauDecayMode);
   fChain->SetBranchAddress("boostedTauLeadChargedHadronExists", &boostedTauLeadChargedHadronExists, &b_boostedTauLeadChargedHadronExists);
   fChain->SetBranchAddress("boostedTauLeadChargedHadronEta", &boostedTauLeadChargedHadronEta, &b_boostedTauLeadChargedHadronEta);
   fChain->SetBranchAddress("boostedTauLeadChargedHadronPhi", &boostedTauLeadChargedHadronPhi, &b_boostedTauLeadChargedHadronPhi);
   fChain->SetBranchAddress("boostedTauLeadChargedHadronPt", &boostedTauLeadChargedHadronPt, &b_boostedTauLeadChargedHadronPt);
   fChain->SetBranchAddress("boostedTauChargedIsoPtSum", &boostedTauChargedIsoPtSum, &b_boostedTauChargedIsoPtSum);
   fChain->SetBranchAddress("boostedTauNeutralIsoPtSum", &boostedTauNeutralIsoPtSum, &b_boostedTauNeutralIsoPtSum);
   fChain->SetBranchAddress("boostedTauPuCorrPtSum", &boostedTauPuCorrPtSum, &b_boostedTauPuCorrPtSum);
   fChain->SetBranchAddress("boostedTauNumSignalPFChargedHadrCands", &boostedTauNumSignalPFChargedHadrCands, &b_boostedTauNumSignalPFChargedHadrCands);
   fChain->SetBranchAddress("boostedTauNumSignalPFNeutrHadrCands", &boostedTauNumSignalPFNeutrHadrCands, &b_boostedTauNumSignalPFNeutrHadrCands);
   fChain->SetBranchAddress("boostedTauNumSignalPFGammaCands", &boostedTauNumSignalPFGammaCands, &b_boostedTauNumSignalPFGammaCands);
   fChain->SetBranchAddress("boostedTauNumSignalPFCands", &boostedTauNumSignalPFCands, &b_boostedTauNumSignalPFCands);
   fChain->SetBranchAddress("boostedTauNumIsolationPFChargedHadrCands", &boostedTauNumIsolationPFChargedHadrCands, &b_boostedTauNumIsolationPFChargedHadrCands);
   fChain->SetBranchAddress("boostedTauNumIsolationPFNeutrHadrCands", &boostedTauNumIsolationPFNeutrHadrCands, &b_boostedTauNumIsolationPFNeutrHadrCands);
   fChain->SetBranchAddress("boostedTauNumIsolationPFGammaCands", &boostedTauNumIsolationPFGammaCands, &b_boostedTauNumIsolationPFGammaCands);
   fChain->SetBranchAddress("boostedTauNumIsolationPFCands", &boostedTauNumIsolationPFCands, &b_boostedTauNumIsolationPFCands);
   fChain->SetBranchAddress("boostedTaufootprintCorrection", &boostedTaufootprintCorrection, &b_boostedTaufootprintCorrection);
   fChain->SetBranchAddress("boostedTauphotonPtSumOutsideSignalCone", &boostedTauphotonPtSumOutsideSignalCone, &b_boostedTauphotonPtSumOutsideSignalCone);
   fChain->SetBranchAddress("boostedTaudz", &boostedTaudz, &b_boostedTaudz);
   fChain->SetBranchAddress("boostedTaudxy", &boostedTaudxy, &b_boostedTaudxy);
   Notify();
}

Bool_t SkimerBoost::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void SkimerBoost::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t SkimerBoost::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef SkimerBoost_cxx
