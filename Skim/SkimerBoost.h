//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Aug  5 10:18:18 2021 by ROOT version 6.12/07
// from TTree EventTree/Event data (tag V10_02_10_04)
// found on file: /eos/uscms/store/group/lpcggntuples/ggNtuples/13TeV/BoostH/2016/MC/ggZH_HToTauTau_ZToNuNu_M125_13TeV_powheg_pythia8/crab_ggZHTT_ZNuNu_M125/210730_221204/0000/ggtree_mc_12.root
//////////////////////////////////////////////////////////

#ifndef SkimerBoost_h
#define SkimerBoost_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"
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
   Int_t           year;
   Int_t           nVtx;
   Int_t           nGoodVtx;
   Bool_t          isPVGood;
   Float_t         rho;
   Float_t         rhoCentral;
   Double_t        L1ECALPrefire;
   Double_t        L1ECALPrefireUp;
   Double_t        L1ECALPrefireDown;
   ULong64_t       HLTEleMuX;
   ULong64_t       HLTJet;
   ULong64_t       HLTEleMuXIsPrescaled;
   ULong64_t       HLTJetIsPrescaled;
   Float_t         processID;
   Float_t         genWeight;
   Float_t         genHT;
   Int_t           nPUInfo;
   vector<float>   *puTrue;
   Int_t           nLHE;
   Float_t         Rivet_VEta;
   Float_t         Rivet_VPt;
   Float_t         Rivet_errorCode;
   Float_t         Rivet_higgsEta;
   Float_t         Rivet_higgsPt;
   Float_t         Rivet_higgsRapidity;
   Float_t         Rivet_nJets25;
   Float_t         Rivet_nJets30;
   Float_t         Rivet_p4decay_VEta;
   Float_t         Rivet_p4decay_VPt;
   Float_t         Rivet_prodMode;
   Float_t         Rivet_stage0_cat;
   Float_t         Rivet_stage1_cat_pTjet30GeV;
   Float_t         Rivet_stage1_cat_pTjet25GeV;
   Float_t         Rivet_stage1_1_cat_pTjet30GeV;
   Float_t         Rivet_stage1_1_cat_pTjet25GeV;
   Float_t         Rivet_j1pt;
   Float_t         Rivet_j1eta;
   Float_t         Rivet_j1phi;
   Float_t         Rivet_j1m;
   Float_t         Rivet_j2pt;
   Float_t         Rivet_j2eta;
   Float_t         Rivet_j2phi;
   Float_t         Rivet_j2m;
   Int_t           nMC;
   vector<int>     *mcPID;
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
   Float_t         met_reso_Up;
   Float_t         met_reso_Down;
   Float_t         met_resp_Up;
   Float_t         met_resp_Down;
   Float_t         metphi_reso_Up;
   Float_t         metphi_reso_Down;
   Float_t         metphi_resp_Up;
   Float_t         metphi_resp_Down;
   Int_t           nEle;
   vector<int>     *eleCharge;
   vector<float>   *eleEn;
   vector<float>   *eleSCEn;
   vector<float>   *eleD0;
   vector<float>   *eleDz;
   vector<float>   *eleSIP;
   vector<float>   *elePt;
   vector<float>   *eleEta;
   vector<float>   *elePhi;
   vector<float>   *eleSCEta;
   vector<float>   *eleSCPhi;
   vector<int>     *eleMissHits;
   vector<float>   *elePFChIso;
   vector<float>   *elePFPhoIso;
   vector<float>   *elePFNeuIso;
   vector<float>   *elePFPUIso;
   vector<float>   *elePFClusEcalIso;
   vector<float>   *elePFClusHcalIso;
   vector<float>   *eleIDMVAIso;
   vector<float>   *eleIDMVANoIso;
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
   Int_t           nMu;
   vector<float>   *muPt;
   vector<float>   *muEn;
   vector<float>   *muEta;
   vector<float>   *muPhi;
   vector<int>     *muCharge;
   vector<int>     *muIDbit;
   vector<float>   *muD0;
   vector<float>   *muDz;
   vector<float>   *muSIP;
   vector<int>     *muMuonHits;
   vector<float>   *muIsoTrk;
   vector<float>   *muPFChIso;
   vector<float>   *muPFPhoIso;
   vector<float>   *muPFNeuIso;
   vector<float>   *muPFPUIso;
   vector<float>   *muPFChIso03;
   vector<float>   *muPFPhoIso03;
   vector<float>   *muPFNeuIso03;
   vector<float>   *muPFPUIso03;
   vector<float>   *muBestTrkPt;
   vector<int>     *muBestTrkType;
   Int_t           nJet;
   vector<float>   *jetPt;
   vector<float>   *jetPtTotUncUp;
   vector<float>   *jetPtTotUncDown;
   vector<float>   *jetEn;
   vector<float>   *jetEta;
   vector<float>   *jetPhi;
   vector<float>   *jetRawPt;
   vector<float>   *jetRawEn;
   vector<float>   *jetMt;
   vector<float>   *jetArea;
   vector<float>   *jetCSV2BJetTags;
   vector<float>   *jetDeepCSVTags_b;
   vector<float>   *jetDeepCSVTags_bb;
   vector<float>   *jetDeepCSVTags_c;
   vector<float>   *jetDeepCSVTags_udsg;
   vector<float>   *jetprobb;
   vector<float>   *jetprobbb;
   vector<float>   *jetproblepb;
   vector<float>   *jetprobc;
   vector<float>   *jetprobuds;
   vector<float>   *jetprobg;
   vector<int>     *jetPartonID;
   vector<int>     *jetHadFlvr;
   vector<bool>    *jetPFLooseId;
   vector<int>     *jetID;
   vector<float>   *jetPUID;
   vector<int>     *jetPUFullID;
   vector<float>   *jetJECUnc;
   vector<float>   *jetTotal;
   vector<ULong64_t> *jetFiredTrgs;
   Int_t           nBoostedTau;
   Int_t           nBoostedTauOrig;
   vector<bool>    *boostedTaupfTausDiscriminationByDecayModeFinding;
   vector<bool>    *boostedTaupfTausDiscriminationByDecayModeFindingNewDMs;
   vector<bool>    *boostedTauByMVA6LooseElectronRejection;
   vector<bool>    *boostedTauByMVA6TightElectronRejection;
   vector<bool>    *boostedTauByLooseMuonRejection3;
   vector<bool>    *boostedTauByTightMuonRejection3;
   vector<float>   *boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits;
   vector<float>   *boostedTauByIsolationMVArun2v1DBoldDMwLTraw;
   vector<bool>    *boostedTauByLooseIsolationMVArun2v1DBoldDMwLT;
   vector<bool>    *boostedTauByTightIsolationMVArun2v1DBoldDMwLT;
   vector<float>   *boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew;
   vector<bool>    *boostedTauByVLooseIsolationMVArun2v1DBoldDMwLTNew;
   vector<bool>    *boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNew;
   vector<bool>    *boostedTauByMediumIsolationMVArun2v1DBoldDMwLTNew;
   vector<bool>    *boostedTauByTightIsolationMVArun2v1DBoldDMwLTNew;
   vector<bool>    *boostedTauByVTightIsolationMVArun2v1DBoldDMwLTNew;
   vector<float>   *boostedTauByIsolationMVArun2v1DBnewDMwLTrawNew;
   vector<bool>    *boostedTauByVLooseIsolationMVArun2v1DBnewDMwLTNew;
   vector<bool>    *boostedTauByLooseIsolationMVArun2v1DBnewDMwLTNew;
   vector<bool>    *boostedTauByMediumIsolationMVArun2v1DBnewDMwLTNew;
   vector<bool>    *boostedTauByTightIsolationMVArun2v1DBnewDMwLTNew;
   vector<bool>    *boostedTauByVTightIsolationMVArun2v1DBnewDMwLTNew;
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
   vector<bool>    *boostedTauagainstElectronVLooseMVA62018;
   vector<bool>    *boostedTauagainstElectronLooseMVA62018;
   vector<bool>    *boostedTauagainstElectronTightMVA62018;
   Int_t           nAK8Jet;
   vector<float>   *AK8JetPt;
   vector<float>   *AK8JetPtTotUncUp;
   vector<float>   *AK8JetPtTotUncDown;
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
   vector<float>   *AK8puppiTau1;
   vector<float>   *AK8puppiTau2;
   vector<float>   *AK8puppiTau3;
   vector<float>   *ak8PFJetsCHSValueMapPt;
   vector<float>   *ak8PFJetsCHSValueMapMass;
   vector<float>   *AK8puppiSDL2L3corr;
   vector<float>   *AK8puppiSDMass;
   vector<float>   *AK8puppiSDMassL2L3Corr;
   vector<int>     *AK8JetPartonID;
   vector<int>     *AK8JetHadFlvr;
   vector<float>   *AK8JetGenJetPt;
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

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_lumis;   //!
   TBranch        *b_isData;   //!
   TBranch        *b_year;   //!
   TBranch        *b_nVtx;   //!
   TBranch        *b_nGoodVtx;   //!
   TBranch        *b_isPVGood;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_rhoCentral;   //!
   TBranch        *b_L1ECALPrefire;   //!
   TBranch        *b_L1ECALPrefireUp;   //!
   TBranch        *b_L1ECALPrefireDown;   //!
   TBranch        *b_HLTEleMuX;   //!
   TBranch        *b_HLTJet;   //!
   TBranch        *b_HLTEleMuXIsPrescaled;   //!
   TBranch        *b_HLTJetIsPrescaled;   //!
   TBranch        *b_processID;   //!
   TBranch        *b_genWeight;   //!
   TBranch        *b_genHT;   //!
   TBranch        *b_nPUInfo;   //!
   TBranch        *b_puTrue;   //!
   TBranch        *b_nLHE;   //!
   TBranch        *b_Rivet_VEta;   //!
   TBranch        *b_Rivet_VPt;   //!
   TBranch        *b_Rivet_errorCode;   //!
   TBranch        *b_Rivet_higgsEta;   //!
   TBranch        *b_Rivet_higgsPt;   //!
   TBranch        *b_Rivet_higgsRapidity;   //!
   TBranch        *b_Rivet_nJets25;   //!
   TBranch        *b_Rivet_nJets30;   //!
   TBranch        *b_Rivet_p4decay_VEta;   //!
   TBranch        *b_Rivet_p4decay_VPt;   //!
   TBranch        *b_Rivet_prodMode;   //!
   TBranch        *b_Rivet_stage0_cat;   //!
   TBranch        *b_Rivet_stage1_cat_pTjet30GeV;   //!
   TBranch        *b_Rivet_stage1_cat_pTjet25GeV;   //!
   TBranch        *b_Rivet_stage1_1_cat_pTjet30GeV;   //!
   TBranch        *b_Rivet_stage1_1_cat_pTjet25GeV;   //!
   TBranch        *b_Rivet_j1pt;   //!
   TBranch        *b_Rivet_j1eta;   //!
   TBranch        *b_Rivet_j1phi;   //!
   TBranch        *b_Rivet_j1m;   //!
   TBranch        *b_Rivet_j2pt;   //!
   TBranch        *b_Rivet_j2eta;   //!
   TBranch        *b_Rivet_j2phi;   //!
   TBranch        *b_Rivet_j2m;   //!
   TBranch        *b_nMC;   //!
   TBranch        *b_mcPID;   //!
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
   TBranch        *b_met_reso_Up;   //!
   TBranch        *b_met_reso_Down;   //!
   TBranch        *b_met_resp_Up;   //!
   TBranch        *b_met_resp_Down;   //!
   TBranch        *b_metphi_reso_Up;   //!
   TBranch        *b_metphi_reso_Down;   //!
   TBranch        *b_metphi_resp_Up;   //!
   TBranch        *b_metphi_resp_Down;   //!
   TBranch        *b_nEle;   //!
   TBranch        *b_eleCharge;   //!
   TBranch        *b_eleEn;   //!
   TBranch        *b_eleSCEn;   //!
   TBranch        *b_eleD0;   //!
   TBranch        *b_eleDz;   //!
   TBranch        *b_eleSIP;   //!
   TBranch        *b_elePt;   //!
   TBranch        *b_eleEta;   //!
   TBranch        *b_elePhi;   //!
   TBranch        *b_eleSCEta;   //!
   TBranch        *b_eleSCPhi;   //!
   TBranch        *b_eleMissHits;   //!
   TBranch        *b_elePFChIso;   //!
   TBranch        *b_elePFPhoIso;   //!
   TBranch        *b_elePFNeuIso;   //!
   TBranch        *b_elePFPUIso;   //!
   TBranch        *b_elePFClusEcalIso;   //!
   TBranch        *b_elePFClusHcalIso;   //!
   TBranch        *b_eleIDMVAIso;   //!
   TBranch        *b_eleIDMVANoIso;   //!
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
   TBranch        *b_nMu;   //!
   TBranch        *b_muPt;   //!
   TBranch        *b_muEn;   //!
   TBranch        *b_muEta;   //!
   TBranch        *b_muPhi;   //!
   TBranch        *b_muCharge;   //!
   TBranch        *b_muIDbit;   //!
   TBranch        *b_muD0;   //!
   TBranch        *b_muDz;   //!
   TBranch        *b_muSIP;   //!
   TBranch        *b_muMuonHits;   //!
   TBranch        *b_muIsoTrk;   //!
   TBranch        *b_muPFChIso;   //!
   TBranch        *b_muPFPhoIso;   //!
   TBranch        *b_muPFNeuIso;   //!
   TBranch        *b_muPFPUIso;   //!
   TBranch        *b_muPFChIso03;   //!
   TBranch        *b_muPFPhoIso03;   //!
   TBranch        *b_muPFNeuIso03;   //!
   TBranch        *b_muPFPUIso03;   //!
   TBranch        *b_muBestTrkPt;   //!
   TBranch        *b_muBestTrkType;   //!
   TBranch        *b_nJet;   //!
   TBranch        *b_jetPt;   //!
   TBranch        *b_jetPtTotUncUp;   //!
   TBranch        *b_jetPtTotUncDown;   //!
   TBranch        *b_jetEn;   //!
   TBranch        *b_jetEta;   //!
   TBranch        *b_jetPhi;   //!
   TBranch        *b_jetRawPt;   //!
   TBranch        *b_jetRawEn;   //!
   TBranch        *b_jetMt;   //!
   TBranch        *b_jetArea;   //!
   TBranch        *b_jetCSV2BJetTags;   //!
   TBranch        *b_jetDeepCSVTags_b;   //!
   TBranch        *b_jetDeepCSVTags_bb;   //!
   TBranch        *b_jetDeepCSVTags_c;   //!
   TBranch        *b_jetDeepCSVTags_udsg;   //!
   TBranch        *b_jetprobb;   //!
   TBranch        *b_jetprobbb;   //!
   TBranch        *b_jetproblepb;   //!
   TBranch        *b_jetprobc;   //!
   TBranch        *b_jetprobuds;   //!
   TBranch        *b_jetprobg;   //!
   TBranch        *b_jetPartonID;   //!
   TBranch        *b_jetHadFlvr;   //!
   TBranch        *b_jetPFLooseId;   //!
   TBranch        *b_jetID;   //!
   TBranch        *b_jetPUID;   //!
   TBranch        *b_jetPUFullID;   //!
   TBranch        *b_jetJECUnc;   //!
   TBranch        *b_jetTotal;   //!
   TBranch        *b_jetFiredTrgs;   //!
   TBranch        *b_nBoostedTau;   //!
   TBranch        *b_nBoostedTauOrig;   //!
   TBranch        *b_boostedTaupfTausDiscriminationByDecayModeFinding;   //!
   TBranch        *b_boostedTaupfTausDiscriminationByDecayModeFindingNewDMs;   //!
   TBranch        *b_boostedTauByMVA6LooseElectronRejection;   //!
   TBranch        *b_boostedTauByMVA6TightElectronRejection;   //!
   TBranch        *b_boostedTauByLooseMuonRejection3;   //!
   TBranch        *b_boostedTauByTightMuonRejection3;   //!
   TBranch        *b_boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits;   //!
   TBranch        *b_boostedTauByIsolationMVArun2v1DBoldDMwLTraw;   //!
   TBranch        *b_boostedTauByLooseIsolationMVArun2v1DBoldDMwLT;   //!
   TBranch        *b_boostedTauByTightIsolationMVArun2v1DBoldDMwLT;   //!
   TBranch        *b_boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew;   //!
   TBranch        *b_boostedTauByVLooseIsolationMVArun2v1DBoldDMwLTNew;   //!
   TBranch        *b_boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNew;   //!
   TBranch        *b_boostedTauByMediumIsolationMVArun2v1DBoldDMwLTNew;   //!
   TBranch        *b_boostedTauByTightIsolationMVArun2v1DBoldDMwLTNew;   //!
   TBranch        *b_boostedTauByVTightIsolationMVArun2v1DBoldDMwLTNew;   //!
   TBranch        *b_boostedTauByIsolationMVArun2v1DBnewDMwLTrawNew;   //!
   TBranch        *b_boostedTauByVLooseIsolationMVArun2v1DBnewDMwLTNew;   //!
   TBranch        *b_boostedTauByLooseIsolationMVArun2v1DBnewDMwLTNew;   //!
   TBranch        *b_boostedTauByMediumIsolationMVArun2v1DBnewDMwLTNew;   //!
   TBranch        *b_boostedTauByTightIsolationMVArun2v1DBnewDMwLTNew;   //!
   TBranch        *b_boostedTauByVTightIsolationMVArun2v1DBnewDMwLTNew;   //!
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
   TBranch        *b_boostedTauagainstElectronVLooseMVA62018;   //!
   TBranch        *b_boostedTauagainstElectronLooseMVA62018;   //!
   TBranch        *b_boostedTauagainstElectronTightMVA62018;   //!
   TBranch        *b_nAK8Jet;   //!
   TBranch        *b_AK8JetPt;   //!
   TBranch        *b_AK8JetPtTotUncUp;   //!
   TBranch        *b_AK8JetPtTotUncDown;   //!
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
   TBranch        *b_AK8puppiTau1;   //!
   TBranch        *b_AK8puppiTau2;   //!
   TBranch        *b_AK8puppiTau3;   //!
   TBranch        *b_ak8PFJetsCHSValueMapPt;   //!
   TBranch        *b_ak8PFJetsCHSValueMapMass;   //!
   TBranch        *b_AK8puppiSDL2L3corr;   //!
   TBranch        *b_AK8puppiSDMass;   //!
   TBranch        *b_AK8puppiSDMassL2L3Corr;   //!
   TBranch        *b_AK8JetPartonID;   //!
   TBranch        *b_AK8JetHadFlvr;   //!
   TBranch        *b_AK8JetGenJetPt;   //!
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

   SkimerBoost(TString fileNamem);
   virtual ~SkimerBoost();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(TString outputFile);
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
//    TTree* tree = (TTree*)gDirectory->Get("EventTree");
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
   puTrue = 0;
   mcPID = 0;
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
   eleCharge = 0;
   eleEn = 0;
   eleSCEn = 0;
   eleD0 = 0;
   eleDz = 0;
   eleSIP = 0;
   elePt = 0;
   eleEta = 0;
   elePhi = 0;
   eleSCEta = 0;
   eleSCPhi = 0;
   eleMissHits = 0;
   elePFChIso = 0;
   elePFPhoIso = 0;
   elePFNeuIso = 0;
   elePFPUIso = 0;
   elePFClusEcalIso = 0;
   elePFClusHcalIso = 0;
   eleIDMVAIso = 0;
   eleIDMVANoIso = 0;
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
   muPt = 0;
   muEn = 0;
   muEta = 0;
   muPhi = 0;
   muCharge = 0;
   muIDbit = 0;
   muD0 = 0;
   muDz = 0;
   muSIP = 0;
   muMuonHits = 0;
   muIsoTrk = 0;
   muPFChIso = 0;
   muPFPhoIso = 0;
   muPFNeuIso = 0;
   muPFPUIso = 0;
   muPFChIso03 = 0;
   muPFPhoIso03 = 0;
   muPFNeuIso03 = 0;
   muPFPUIso03 = 0;
   muBestTrkPt = 0;
   muBestTrkType = 0;
   jetPt = 0;
   jetPtTotUncUp = 0;
   jetPtTotUncDown = 0;
   jetEn = 0;
   jetEta = 0;
   jetPhi = 0;
   jetRawPt = 0;
   jetRawEn = 0;
   jetMt = 0;
   jetArea = 0;
   jetCSV2BJetTags = 0;
   jetDeepCSVTags_b = 0;
   jetDeepCSVTags_bb = 0;
   jetDeepCSVTags_c = 0;
   jetDeepCSVTags_udsg = 0;
   jetprobb = 0;
   jetprobbb = 0;
   jetproblepb = 0;
   jetprobc = 0;
   jetprobuds = 0;
   jetprobg = 0;
   jetPartonID = 0;
   jetHadFlvr = 0;
   jetPFLooseId = 0;
   jetID = 0;
   jetPUID = 0;
   jetPUFullID = 0;
   jetJECUnc = 0;
   jetTotal = 0;
   jetFiredTrgs = 0;
   boostedTaupfTausDiscriminationByDecayModeFinding = 0;
   boostedTaupfTausDiscriminationByDecayModeFindingNewDMs = 0;
   boostedTauByMVA6LooseElectronRejection = 0;
   boostedTauByMVA6TightElectronRejection = 0;
   boostedTauByLooseMuonRejection3 = 0;
   boostedTauByTightMuonRejection3 = 0;
   boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits = 0;
   boostedTauByIsolationMVArun2v1DBoldDMwLTraw = 0;
   boostedTauByLooseIsolationMVArun2v1DBoldDMwLT = 0;
   boostedTauByTightIsolationMVArun2v1DBoldDMwLT = 0;
   boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew = 0;
   boostedTauByVLooseIsolationMVArun2v1DBoldDMwLTNew = 0;
   boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNew = 0;
   boostedTauByMediumIsolationMVArun2v1DBoldDMwLTNew = 0;
   boostedTauByTightIsolationMVArun2v1DBoldDMwLTNew = 0;
   boostedTauByVTightIsolationMVArun2v1DBoldDMwLTNew = 0;
   boostedTauByIsolationMVArun2v1DBnewDMwLTrawNew = 0;
   boostedTauByVLooseIsolationMVArun2v1DBnewDMwLTNew = 0;
   boostedTauByLooseIsolationMVArun2v1DBnewDMwLTNew = 0;
   boostedTauByMediumIsolationMVArun2v1DBnewDMwLTNew = 0;
   boostedTauByTightIsolationMVArun2v1DBnewDMwLTNew = 0;
   boostedTauByVTightIsolationMVArun2v1DBnewDMwLTNew = 0;
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
   boostedTauChargedIsoPtSumNoOverLap = 0;
   boostedTauNeutralIsoPtSum = 0;
   boostedTauNeutralIsoPtSumNoOverLap = 0;
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
   boostedTauagainstElectronVLooseMVA62018 = 0;
   boostedTauagainstElectronLooseMVA62018 = 0;
   boostedTauagainstElectronTightMVA62018 = 0;
   AK8JetPt = 0;
   AK8JetPtTotUncUp = 0;
   AK8JetPtTotUncDown = 0;
   AK8JetEn = 0;
   AK8JetRawPt = 0;
   AK8JetRawEn = 0;
   AK8JetEta = 0;
   AK8JetPhi = 0;
   AK8JetMass = 0;
   AK8Jet_tau1 = 0;
   AK8Jet_tau2 = 0;
   AK8Jet_tau3 = 0;
   AK8Jetnconstituents = 0;
   AK8JetPFLooseId = 0;
   AK8JetPFTightLepVetoId = 0;
   AK8JetSoftDropMass = 0;
   AK8JetSoftDropMassCorr = 0;
   AK8JetPrunedMass = 0;
   AK8JetPrunedMassCorr = 0;
   AK8JetpfBoostedDSVBTag = 0;
   AK8JetCSV = 0;
   AK8JetJECUnc = 0;
   AK8JetL2L3corr = 0;
   AK8puppiPt = 0;
   AK8puppiMass = 0;
   AK8puppiEta = 0;
   AK8puppiPhi = 0;
   AK8puppiTau1 = 0;
   AK8puppiTau2 = 0;
   AK8puppiTau3 = 0;
   ak8PFJetsCHSValueMapPt = 0;
   ak8PFJetsCHSValueMapMass = 0;
   AK8puppiSDL2L3corr = 0;
   AK8puppiSDMass = 0;
   AK8puppiSDMassL2L3Corr = 0;
   AK8JetPartonID = 0;
   AK8JetHadFlvr = 0;
   AK8JetGenJetPt = 0;
   nAK8SDSJ = 0;
   AK8SDSJPt = 0;
   AK8SDSJEta = 0;
   AK8SDSJPhi = 0;
   AK8SDSJMass = 0;
   AK8SDSJE = 0;
   AK8SDSJCharge = 0;
   AK8SDSJFlavour = 0;
   AK8SDSJCSV = 0;
   nAK8puppiSDSJ = 0;
   AK8puppiSDSJPt = 0;
   AK8puppiSDSJEta = 0;
   AK8puppiSDSJPhi = 0;
   AK8puppiSDSJMass = 0;
   AK8puppiSDSJE = 0;
   AK8puppiSDSJCharge = 0;
   AK8puppiSDSJFlavour = 0;
   AK8puppiSDSJCSV = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("lumis", &lumis, &b_lumis);
   fChain->SetBranchAddress("isData", &isData, &b_isData);
   fChain->SetBranchAddress("year", &year, &b_year);
   fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
   fChain->SetBranchAddress("nGoodVtx", &nGoodVtx, &b_nGoodVtx);
   fChain->SetBranchAddress("isPVGood", &isPVGood, &b_isPVGood);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("rhoCentral", &rhoCentral, &b_rhoCentral);
   fChain->SetBranchAddress("L1ECALPrefire", &L1ECALPrefire, &b_L1ECALPrefire);
   fChain->SetBranchAddress("L1ECALPrefireUp", &L1ECALPrefireUp, &b_L1ECALPrefireUp);
   fChain->SetBranchAddress("L1ECALPrefireDown", &L1ECALPrefireDown, &b_L1ECALPrefireDown);
   fChain->SetBranchAddress("HLTEleMuX", &HLTEleMuX, &b_HLTEleMuX);
   fChain->SetBranchAddress("HLTJet", &HLTJet, &b_HLTJet);
   fChain->SetBranchAddress("HLTEleMuXIsPrescaled", &HLTEleMuXIsPrescaled, &b_HLTEleMuXIsPrescaled);
   fChain->SetBranchAddress("HLTJetIsPrescaled", &HLTJetIsPrescaled, &b_HLTJetIsPrescaled);
   fChain->SetBranchAddress("processID", &processID, &b_processID);
   fChain->SetBranchAddress("genWeight", &genWeight, &b_genWeight);
   fChain->SetBranchAddress("genHT", &genHT, &b_genHT);
   fChain->SetBranchAddress("nPUInfo", &nPUInfo, &b_nPUInfo);
   fChain->SetBranchAddress("puTrue", &puTrue, &b_puTrue);
   fChain->SetBranchAddress("nLHE", &nLHE, &b_nLHE);
   fChain->SetBranchAddress("Rivet_VEta", &Rivet_VEta, &b_Rivet_VEta);
   fChain->SetBranchAddress("Rivet_VPt", &Rivet_VPt, &b_Rivet_VPt);
   fChain->SetBranchAddress("Rivet_errorCode", &Rivet_errorCode, &b_Rivet_errorCode);
   fChain->SetBranchAddress("Rivet_higgsEta", &Rivet_higgsEta, &b_Rivet_higgsEta);
   fChain->SetBranchAddress("Rivet_higgsPt", &Rivet_higgsPt, &b_Rivet_higgsPt);
   fChain->SetBranchAddress("Rivet_higgsRapidity", &Rivet_higgsRapidity, &b_Rivet_higgsRapidity);
   fChain->SetBranchAddress("Rivet_nJets25", &Rivet_nJets25, &b_Rivet_nJets25);
   fChain->SetBranchAddress("Rivet_nJets30", &Rivet_nJets30, &b_Rivet_nJets30);
   fChain->SetBranchAddress("Rivet_p4decay_VEta", &Rivet_p4decay_VEta, &b_Rivet_p4decay_VEta);
   fChain->SetBranchAddress("Rivet_p4decay_VPt", &Rivet_p4decay_VPt, &b_Rivet_p4decay_VPt);
   fChain->SetBranchAddress("Rivet_prodMode", &Rivet_prodMode, &b_Rivet_prodMode);
   fChain->SetBranchAddress("Rivet_stage0_cat", &Rivet_stage0_cat, &b_Rivet_stage0_cat);
   fChain->SetBranchAddress("Rivet_stage1_cat_pTjet30GeV", &Rivet_stage1_cat_pTjet30GeV, &b_Rivet_stage1_cat_pTjet30GeV);
   fChain->SetBranchAddress("Rivet_stage1_cat_pTjet25GeV", &Rivet_stage1_cat_pTjet25GeV, &b_Rivet_stage1_cat_pTjet25GeV);
   fChain->SetBranchAddress("Rivet_stage1_1_cat_pTjet30GeV", &Rivet_stage1_1_cat_pTjet30GeV, &b_Rivet_stage1_1_cat_pTjet30GeV);
   fChain->SetBranchAddress("Rivet_stage1_1_cat_pTjet25GeV", &Rivet_stage1_1_cat_pTjet25GeV, &b_Rivet_stage1_1_cat_pTjet25GeV);
   fChain->SetBranchAddress("Rivet_j1pt", &Rivet_j1pt, &b_Rivet_j1pt);
   fChain->SetBranchAddress("Rivet_j1eta", &Rivet_j1eta, &b_Rivet_j1eta);
   fChain->SetBranchAddress("Rivet_j1phi", &Rivet_j1phi, &b_Rivet_j1phi);
   fChain->SetBranchAddress("Rivet_j1m", &Rivet_j1m, &b_Rivet_j1m);
   fChain->SetBranchAddress("Rivet_j2pt", &Rivet_j2pt, &b_Rivet_j2pt);
   fChain->SetBranchAddress("Rivet_j2eta", &Rivet_j2eta, &b_Rivet_j2eta);
   fChain->SetBranchAddress("Rivet_j2phi", &Rivet_j2phi, &b_Rivet_j2phi);
   fChain->SetBranchAddress("Rivet_j2m", &Rivet_j2m, &b_Rivet_j2m);
   fChain->SetBranchAddress("nMC", &nMC, &b_nMC);
   fChain->SetBranchAddress("mcPID", &mcPID, &b_mcPID);
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
   fChain->SetBranchAddress("genMET", &genMET, &b_genMET);
   fChain->SetBranchAddress("genMETPhi", &genMETPhi, &b_genMETPhi);
   fChain->SetBranchAddress("metFilters", &metFilters, &b_metFilters);
   fChain->SetBranchAddress("pfMET", &pfMET, &b_pfMET);
   fChain->SetBranchAddress("pfMETPhi", &pfMETPhi, &b_pfMETPhi);
   fChain->SetBranchAddress("recoil", &recoil, &b_recoil);
   fChain->SetBranchAddress("pfMetNoRecoil", &pfMetNoRecoil, &b_pfMetNoRecoil);
   fChain->SetBranchAddress("pfMetPhiNoRecoil", &pfMetPhiNoRecoil, &b_pfMetPhiNoRecoil);
   fChain->SetBranchAddress("met_px", &met_px, &b_met_px);
   fChain->SetBranchAddress("met_py", &met_py, &b_met_py);
   fChain->SetBranchAddress("metcov00", &metcov00, &b_metcov00);
   fChain->SetBranchAddress("metcov01", &metcov01, &b_metcov01);
   fChain->SetBranchAddress("metcov10", &metcov10, &b_metcov10);
   fChain->SetBranchAddress("metcov11", &metcov11, &b_metcov11);
   fChain->SetBranchAddress("pfMET_T1JESUp", &pfMET_T1JESUp, &b_pfMET_T1JESUp);
   fChain->SetBranchAddress("pfMET_T1JESDo", &pfMET_T1JESDo, &b_pfMET_T1JESDo);
   fChain->SetBranchAddress("pfMET_T1UESUp", &pfMET_T1UESUp, &b_pfMET_T1UESUp);
   fChain->SetBranchAddress("pfMET_T1UESDo", &pfMET_T1UESDo, &b_pfMET_T1UESDo);
   fChain->SetBranchAddress("pfMETPhi_T1JESUp", &pfMETPhi_T1JESUp, &b_pfMETPhi_T1JESUp);
   fChain->SetBranchAddress("pfMETPhi_T1JESDo", &pfMETPhi_T1JESDo, &b_pfMETPhi_T1JESDo);
   fChain->SetBranchAddress("pfMETPhi_T1UESUp", &pfMETPhi_T1UESUp, &b_pfMETPhi_T1UESUp);
   fChain->SetBranchAddress("pfMETPhi_T1UESDo", &pfMETPhi_T1UESDo, &b_pfMETPhi_T1UESDo);
   fChain->SetBranchAddress("met_JESUp", &met_JESUp, &b_met_JESUp);
   fChain->SetBranchAddress("met_JESDown", &met_JESDown, &b_met_JESDown);
   fChain->SetBranchAddress("met_UESUp", &met_UESUp, &b_met_UESUp);
   fChain->SetBranchAddress("met_UESDown", &met_UESDown, &b_met_UESDown);
   fChain->SetBranchAddress("metphi_JESUp", &metphi_JESUp, &b_metphi_JESUp);
   fChain->SetBranchAddress("metphi_JESDown", &metphi_JESDown, &b_metphi_JESDown);
   fChain->SetBranchAddress("metphi_UESUp", &metphi_UESUp, &b_metphi_UESUp);
   fChain->SetBranchAddress("metphi_UESDown", &metphi_UESDown, &b_metphi_UESDown);
   fChain->SetBranchAddress("pfmetcorr_ex_UESUp", &pfmetcorr_ex_UESUp, &b_pfmetcorr_ex_UESUp);
   fChain->SetBranchAddress("pfmetcorr_ey_UESUp", &pfmetcorr_ey_UESUp, &b_pfmetcorr_ey_UESUp);
   fChain->SetBranchAddress("pfmetcorr_ex_UESDown", &pfmetcorr_ex_UESDown, &b_pfmetcorr_ex_UESDown);
   fChain->SetBranchAddress("pfmetcorr_ey_UESDown", &pfmetcorr_ey_UESDown, &b_pfmetcorr_ey_UESDown);
   fChain->SetBranchAddress("pfmetcorr_ex_JESUp", &pfmetcorr_ex_JESUp, &b_pfmetcorr_ex_JESUp);
   fChain->SetBranchAddress("pfmetcorr_ey_JESUp", &pfmetcorr_ey_JESUp, &b_pfmetcorr_ey_JESUp);
   fChain->SetBranchAddress("pfmetcorr_ex_JESDown", &pfmetcorr_ex_JESDown, &b_pfmetcorr_ex_JESDown);
   fChain->SetBranchAddress("pfmetcorr_ey_JESDown", &pfmetcorr_ey_JESDown, &b_pfmetcorr_ey_JESDown);
   fChain->SetBranchAddress("met_reso_Up", &met_reso_Up, &b_met_reso_Up);
   fChain->SetBranchAddress("met_reso_Down", &met_reso_Down, &b_met_reso_Down);
   fChain->SetBranchAddress("met_resp_Up", &met_resp_Up, &b_met_resp_Up);
   fChain->SetBranchAddress("met_resp_Down", &met_resp_Down, &b_met_resp_Down);
   fChain->SetBranchAddress("metphi_reso_Up", &metphi_reso_Up, &b_metphi_reso_Up);
   fChain->SetBranchAddress("metphi_reso_Down", &metphi_reso_Down, &b_metphi_reso_Down);
   fChain->SetBranchAddress("metphi_resp_Up", &metphi_resp_Up, &b_metphi_resp_Up);
   fChain->SetBranchAddress("metphi_resp_Down", &metphi_resp_Down, &b_metphi_resp_Down);
   fChain->SetBranchAddress("nEle", &nEle, &b_nEle);
   fChain->SetBranchAddress("eleCharge", &eleCharge, &b_eleCharge);
   fChain->SetBranchAddress("eleEn", &eleEn, &b_eleEn);
   fChain->SetBranchAddress("eleSCEn", &eleSCEn, &b_eleSCEn);
   fChain->SetBranchAddress("eleD0", &eleD0, &b_eleD0);
   fChain->SetBranchAddress("eleDz", &eleDz, &b_eleDz);
   fChain->SetBranchAddress("eleSIP", &eleSIP, &b_eleSIP);
   fChain->SetBranchAddress("elePt", &elePt, &b_elePt);
   fChain->SetBranchAddress("eleEta", &eleEta, &b_eleEta);
   fChain->SetBranchAddress("elePhi", &elePhi, &b_elePhi);
   fChain->SetBranchAddress("eleSCEta", &eleSCEta, &b_eleSCEta);
   fChain->SetBranchAddress("eleSCPhi", &eleSCPhi, &b_eleSCPhi);
   fChain->SetBranchAddress("eleMissHits", &eleMissHits, &b_eleMissHits);
   fChain->SetBranchAddress("elePFChIso", &elePFChIso, &b_elePFChIso);
   fChain->SetBranchAddress("elePFPhoIso", &elePFPhoIso, &b_elePFPhoIso);
   fChain->SetBranchAddress("elePFNeuIso", &elePFNeuIso, &b_elePFNeuIso);
   fChain->SetBranchAddress("elePFPUIso", &elePFPUIso, &b_elePFPUIso);
   fChain->SetBranchAddress("elePFClusEcalIso", &elePFClusEcalIso, &b_elePFClusEcalIso);
   fChain->SetBranchAddress("elePFClusHcalIso", &elePFClusHcalIso, &b_elePFClusHcalIso);
   fChain->SetBranchAddress("eleIDMVAIso", &eleIDMVAIso, &b_eleIDMVAIso);
   fChain->SetBranchAddress("eleIDMVANoIso", &eleIDMVANoIso, &b_eleIDMVANoIso);
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
   fChain->SetBranchAddress("nMu", &nMu, &b_nMu);
   fChain->SetBranchAddress("muPt", &muPt, &b_muPt);
   fChain->SetBranchAddress("muEn", &muEn, &b_muEn);
   fChain->SetBranchAddress("muEta", &muEta, &b_muEta);
   fChain->SetBranchAddress("muPhi", &muPhi, &b_muPhi);
   fChain->SetBranchAddress("muCharge", &muCharge, &b_muCharge);
   fChain->SetBranchAddress("muIDbit", &muIDbit, &b_muIDbit);
   fChain->SetBranchAddress("muD0", &muD0, &b_muD0);
   fChain->SetBranchAddress("muDz", &muDz, &b_muDz);
   fChain->SetBranchAddress("muSIP", &muSIP, &b_muSIP);
   fChain->SetBranchAddress("muMuonHits", &muMuonHits, &b_muMuonHits);
   fChain->SetBranchAddress("muIsoTrk", &muIsoTrk, &b_muIsoTrk);
   fChain->SetBranchAddress("muPFChIso", &muPFChIso, &b_muPFChIso);
   fChain->SetBranchAddress("muPFPhoIso", &muPFPhoIso, &b_muPFPhoIso);
   fChain->SetBranchAddress("muPFNeuIso", &muPFNeuIso, &b_muPFNeuIso);
   fChain->SetBranchAddress("muPFPUIso", &muPFPUIso, &b_muPFPUIso);
   fChain->SetBranchAddress("muPFChIso03", &muPFChIso03, &b_muPFChIso03);
   fChain->SetBranchAddress("muPFPhoIso03", &muPFPhoIso03, &b_muPFPhoIso03);
   fChain->SetBranchAddress("muPFNeuIso03", &muPFNeuIso03, &b_muPFNeuIso03);
   fChain->SetBranchAddress("muPFPUIso03", &muPFPUIso03, &b_muPFPUIso03);
   fChain->SetBranchAddress("muBestTrkPt", &muBestTrkPt, &b_muBestTrkPt);
   fChain->SetBranchAddress("muBestTrkType", &muBestTrkType, &b_muBestTrkType);
   fChain->SetBranchAddress("nJet", &nJet, &b_nJet);
   fChain->SetBranchAddress("jetPt", &jetPt, &b_jetPt);
   fChain->SetBranchAddress("jetPtTotUncUp", &jetPtTotUncUp, &b_jetPtTotUncUp);
   fChain->SetBranchAddress("jetPtTotUncDown", &jetPtTotUncDown, &b_jetPtTotUncDown);
   fChain->SetBranchAddress("jetEn", &jetEn, &b_jetEn);
   fChain->SetBranchAddress("jetEta", &jetEta, &b_jetEta);
   fChain->SetBranchAddress("jetPhi", &jetPhi, &b_jetPhi);
   fChain->SetBranchAddress("jetRawPt", &jetRawPt, &b_jetRawPt);
   fChain->SetBranchAddress("jetRawEn", &jetRawEn, &b_jetRawEn);
   fChain->SetBranchAddress("jetMt", &jetMt, &b_jetMt);
   fChain->SetBranchAddress("jetArea", &jetArea, &b_jetArea);
   fChain->SetBranchAddress("jetCSV2BJetTags", &jetCSV2BJetTags, &b_jetCSV2BJetTags);
   fChain->SetBranchAddress("jetDeepCSVTags_b", &jetDeepCSVTags_b, &b_jetDeepCSVTags_b);
   fChain->SetBranchAddress("jetDeepCSVTags_bb", &jetDeepCSVTags_bb, &b_jetDeepCSVTags_bb);
   fChain->SetBranchAddress("jetDeepCSVTags_c", &jetDeepCSVTags_c, &b_jetDeepCSVTags_c);
   fChain->SetBranchAddress("jetDeepCSVTags_udsg", &jetDeepCSVTags_udsg, &b_jetDeepCSVTags_udsg);
   fChain->SetBranchAddress("jetprobb", &jetprobb, &b_jetprobb);
   fChain->SetBranchAddress("jetprobbb", &jetprobbb, &b_jetprobbb);
   fChain->SetBranchAddress("jetproblepb", &jetproblepb, &b_jetproblepb);
   fChain->SetBranchAddress("jetprobc", &jetprobc, &b_jetprobc);
   fChain->SetBranchAddress("jetprobuds", &jetprobuds, &b_jetprobuds);
   fChain->SetBranchAddress("jetprobg", &jetprobg, &b_jetprobg);
   fChain->SetBranchAddress("jetPartonID", &jetPartonID, &b_jetPartonID);
   fChain->SetBranchAddress("jetHadFlvr", &jetHadFlvr, &b_jetHadFlvr);
   fChain->SetBranchAddress("jetPFLooseId", &jetPFLooseId, &b_jetPFLooseId);
   fChain->SetBranchAddress("jetID", &jetID, &b_jetID);
   fChain->SetBranchAddress("jetPUID", &jetPUID, &b_jetPUID);
   fChain->SetBranchAddress("jetPUFullID", &jetPUFullID, &b_jetPUFullID);
   fChain->SetBranchAddress("jetJECUnc", &jetJECUnc, &b_jetJECUnc);
   fChain->SetBranchAddress("jetTotal", &jetTotal, &b_jetTotal);
   fChain->SetBranchAddress("jetFiredTrgs", &jetFiredTrgs, &b_jetFiredTrgs);
   fChain->SetBranchAddress("nBoostedTau", &nBoostedTau, &b_nBoostedTau);
   fChain->SetBranchAddress("nBoostedTauOrig", &nBoostedTauOrig, &b_nBoostedTauOrig);
   fChain->SetBranchAddress("boostedTaupfTausDiscriminationByDecayModeFinding", &boostedTaupfTausDiscriminationByDecayModeFinding, &b_boostedTaupfTausDiscriminationByDecayModeFinding);
   fChain->SetBranchAddress("boostedTaupfTausDiscriminationByDecayModeFindingNewDMs", &boostedTaupfTausDiscriminationByDecayModeFindingNewDMs, &b_boostedTaupfTausDiscriminationByDecayModeFindingNewDMs);
   fChain->SetBranchAddress("boostedTauByMVA6LooseElectronRejection", &boostedTauByMVA6LooseElectronRejection, &b_boostedTauByMVA6LooseElectronRejection);
   fChain->SetBranchAddress("boostedTauByMVA6TightElectronRejection", &boostedTauByMVA6TightElectronRejection, &b_boostedTauByMVA6TightElectronRejection);
   fChain->SetBranchAddress("boostedTauByLooseMuonRejection3", &boostedTauByLooseMuonRejection3, &b_boostedTauByLooseMuonRejection3);
   fChain->SetBranchAddress("boostedTauByTightMuonRejection3", &boostedTauByTightMuonRejection3, &b_boostedTauByTightMuonRejection3);
   fChain->SetBranchAddress("boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits", &boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits, &b_boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits);
   fChain->SetBranchAddress("boostedTauByIsolationMVArun2v1DBoldDMwLTraw", &boostedTauByIsolationMVArun2v1DBoldDMwLTraw, &b_boostedTauByIsolationMVArun2v1DBoldDMwLTraw);
   fChain->SetBranchAddress("boostedTauByLooseIsolationMVArun2v1DBoldDMwLT", &boostedTauByLooseIsolationMVArun2v1DBoldDMwLT, &b_boostedTauByLooseIsolationMVArun2v1DBoldDMwLT);
   fChain->SetBranchAddress("boostedTauByTightIsolationMVArun2v1DBoldDMwLT", &boostedTauByTightIsolationMVArun2v1DBoldDMwLT, &b_boostedTauByTightIsolationMVArun2v1DBoldDMwLT);
   fChain->SetBranchAddress("boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew", &boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew, &b_boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew);
   fChain->SetBranchAddress("boostedTauByVLooseIsolationMVArun2v1DBoldDMwLTNew", &boostedTauByVLooseIsolationMVArun2v1DBoldDMwLTNew, &b_boostedTauByVLooseIsolationMVArun2v1DBoldDMwLTNew);
   fChain->SetBranchAddress("boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNew", &boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNew, &b_boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNew);
   fChain->SetBranchAddress("boostedTauByMediumIsolationMVArun2v1DBoldDMwLTNew", &boostedTauByMediumIsolationMVArun2v1DBoldDMwLTNew, &b_boostedTauByMediumIsolationMVArun2v1DBoldDMwLTNew);
   fChain->SetBranchAddress("boostedTauByTightIsolationMVArun2v1DBoldDMwLTNew", &boostedTauByTightIsolationMVArun2v1DBoldDMwLTNew, &b_boostedTauByTightIsolationMVArun2v1DBoldDMwLTNew);
   fChain->SetBranchAddress("boostedTauByVTightIsolationMVArun2v1DBoldDMwLTNew", &boostedTauByVTightIsolationMVArun2v1DBoldDMwLTNew, &b_boostedTauByVTightIsolationMVArun2v1DBoldDMwLTNew);
   fChain->SetBranchAddress("boostedTauByIsolationMVArun2v1DBnewDMwLTrawNew", &boostedTauByIsolationMVArun2v1DBnewDMwLTrawNew, &b_boostedTauByIsolationMVArun2v1DBnewDMwLTrawNew);
   fChain->SetBranchAddress("boostedTauByVLooseIsolationMVArun2v1DBnewDMwLTNew", &boostedTauByVLooseIsolationMVArun2v1DBnewDMwLTNew, &b_boostedTauByVLooseIsolationMVArun2v1DBnewDMwLTNew);
   fChain->SetBranchAddress("boostedTauByLooseIsolationMVArun2v1DBnewDMwLTNew", &boostedTauByLooseIsolationMVArun2v1DBnewDMwLTNew, &b_boostedTauByLooseIsolationMVArun2v1DBnewDMwLTNew);
   fChain->SetBranchAddress("boostedTauByMediumIsolationMVArun2v1DBnewDMwLTNew", &boostedTauByMediumIsolationMVArun2v1DBnewDMwLTNew, &b_boostedTauByMediumIsolationMVArun2v1DBnewDMwLTNew);
   fChain->SetBranchAddress("boostedTauByTightIsolationMVArun2v1DBnewDMwLTNew", &boostedTauByTightIsolationMVArun2v1DBnewDMwLTNew, &b_boostedTauByTightIsolationMVArun2v1DBnewDMwLTNew);
   fChain->SetBranchAddress("boostedTauByVTightIsolationMVArun2v1DBnewDMwLTNew", &boostedTauByVTightIsolationMVArun2v1DBnewDMwLTNew, &b_boostedTauByVTightIsolationMVArun2v1DBnewDMwLTNew);
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
   fChain->SetBranchAddress("boostedTauChargedIsoPtSumNoOverLap", &boostedTauChargedIsoPtSumNoOverLap, &b_boostedTauChargedIsoPtSumNoOverLap);
   fChain->SetBranchAddress("boostedTauNeutralIsoPtSum", &boostedTauNeutralIsoPtSum, &b_boostedTauNeutralIsoPtSum);
   fChain->SetBranchAddress("boostedTauNeutralIsoPtSumNoOverLap", &boostedTauNeutralIsoPtSumNoOverLap, &b_boostedTauNeutralIsoPtSumNoOverLap);
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
   fChain->SetBranchAddress("boostedTauagainstElectronVLooseMVA62018", &boostedTauagainstElectronVLooseMVA62018, &b_boostedTauagainstElectronVLooseMVA62018);
   fChain->SetBranchAddress("boostedTauagainstElectronLooseMVA62018", &boostedTauagainstElectronLooseMVA62018, &b_boostedTauagainstElectronLooseMVA62018);
   fChain->SetBranchAddress("boostedTauagainstElectronTightMVA62018", &boostedTauagainstElectronTightMVA62018, &b_boostedTauagainstElectronTightMVA62018);
   fChain->SetBranchAddress("nAK8Jet", &nAK8Jet, &b_nAK8Jet);
   fChain->SetBranchAddress("AK8JetPt", &AK8JetPt, &b_AK8JetPt);
   fChain->SetBranchAddress("AK8JetPtTotUncUp", &AK8JetPtTotUncUp, &b_AK8JetPtTotUncUp);
   fChain->SetBranchAddress("AK8JetPtTotUncDown", &AK8JetPtTotUncDown, &b_AK8JetPtTotUncDown);
   fChain->SetBranchAddress("AK8JetEn", &AK8JetEn, &b_AK8JetEn);
   fChain->SetBranchAddress("AK8JetRawPt", &AK8JetRawPt, &b_AK8JetRawPt);
   fChain->SetBranchAddress("AK8JetRawEn", &AK8JetRawEn, &b_AK8JetRawEn);
   fChain->SetBranchAddress("AK8JetEta", &AK8JetEta, &b_AK8JetEta);
   fChain->SetBranchAddress("AK8JetPhi", &AK8JetPhi, &b_AK8JetPhi);
   fChain->SetBranchAddress("AK8JetMass", &AK8JetMass, &b_AK8JetMass);
   fChain->SetBranchAddress("AK8Jet_tau1", &AK8Jet_tau1, &b_AK8Jet_tau1);
   fChain->SetBranchAddress("AK8Jet_tau2", &AK8Jet_tau2, &b_AK8Jet_tau2);
   fChain->SetBranchAddress("AK8Jet_tau3", &AK8Jet_tau3, &b_AK8Jet_tau3);
   fChain->SetBranchAddress("AK8Jetnconstituents", &AK8Jetnconstituents, &b_AK8Jetnconstituents);
   fChain->SetBranchAddress("AK8JetPFLooseId", &AK8JetPFLooseId, &b_AK8JetPFLooseId);
   fChain->SetBranchAddress("AK8JetPFTightLepVetoId", &AK8JetPFTightLepVetoId, &b_AK8JetPFTightLepVetoId);
   fChain->SetBranchAddress("AK8JetSoftDropMass", &AK8JetSoftDropMass, &b_AK8JetSoftDropMass);
   fChain->SetBranchAddress("AK8JetSoftDropMassCorr", &AK8JetSoftDropMassCorr, &b_AK8JetSoftDropMassCorr);
   fChain->SetBranchAddress("AK8JetPrunedMass", &AK8JetPrunedMass, &b_AK8JetPrunedMass);
   fChain->SetBranchAddress("AK8JetPrunedMassCorr", &AK8JetPrunedMassCorr, &b_AK8JetPrunedMassCorr);
   fChain->SetBranchAddress("AK8JetpfBoostedDSVBTag", &AK8JetpfBoostedDSVBTag, &b_AK8JetpfBoostedDSVBTag);
   fChain->SetBranchAddress("AK8JetCSV", &AK8JetCSV, &b_AK8JetCSV);
   fChain->SetBranchAddress("AK8JetJECUnc", &AK8JetJECUnc, &b_AK8JetJECUnc);
   fChain->SetBranchAddress("AK8JetL2L3corr", &AK8JetL2L3corr, &b_AK8JetL2L3corr);
   fChain->SetBranchAddress("AK8puppiPt", &AK8puppiPt, &b_AK8puppiPt);
   fChain->SetBranchAddress("AK8puppiMass", &AK8puppiMass, &b_AK8puppiMass);
   fChain->SetBranchAddress("AK8puppiEta", &AK8puppiEta, &b_AK8puppiEta);
   fChain->SetBranchAddress("AK8puppiPhi", &AK8puppiPhi, &b_AK8puppiPhi);
   fChain->SetBranchAddress("AK8puppiTau1", &AK8puppiTau1, &b_AK8puppiTau1);
   fChain->SetBranchAddress("AK8puppiTau2", &AK8puppiTau2, &b_AK8puppiTau2);
   fChain->SetBranchAddress("AK8puppiTau3", &AK8puppiTau3, &b_AK8puppiTau3);
   fChain->SetBranchAddress("ak8PFJetsCHSValueMapPt", &ak8PFJetsCHSValueMapPt, &b_ak8PFJetsCHSValueMapPt);
   fChain->SetBranchAddress("ak8PFJetsCHSValueMapMass", &ak8PFJetsCHSValueMapMass, &b_ak8PFJetsCHSValueMapMass);
   fChain->SetBranchAddress("AK8puppiSDL2L3corr", &AK8puppiSDL2L3corr, &b_AK8puppiSDL2L3corr);
   fChain->SetBranchAddress("AK8puppiSDMass", &AK8puppiSDMass, &b_AK8puppiSDMass);
   fChain->SetBranchAddress("AK8puppiSDMassL2L3Corr", &AK8puppiSDMassL2L3Corr, &b_AK8puppiSDMassL2L3Corr);
   fChain->SetBranchAddress("AK8JetPartonID", &AK8JetPartonID, &b_AK8JetPartonID);
   fChain->SetBranchAddress("AK8JetHadFlvr", &AK8JetHadFlvr, &b_AK8JetHadFlvr);
   fChain->SetBranchAddress("AK8JetGenJetPt", &AK8JetGenJetPt, &b_AK8JetGenJetPt);
   fChain->SetBranchAddress("nAK8SDSJ", &nAK8SDSJ, &b_nAK8SDSJ);
   fChain->SetBranchAddress("AK8SDSJPt", &AK8SDSJPt, &b_AK8SDSJPt);
   fChain->SetBranchAddress("AK8SDSJEta", &AK8SDSJEta, &b_AK8SDSJEta);
   fChain->SetBranchAddress("AK8SDSJPhi", &AK8SDSJPhi, &b_AK8SDSJPhi);
   fChain->SetBranchAddress("AK8SDSJMass", &AK8SDSJMass, &b_AK8SDSJMass);
   fChain->SetBranchAddress("AK8SDSJE", &AK8SDSJE, &b_AK8SDSJE);
   fChain->SetBranchAddress("AK8SDSJCharge", &AK8SDSJCharge, &b_AK8SDSJCharge);
   fChain->SetBranchAddress("AK8SDSJFlavour", &AK8SDSJFlavour, &b_AK8SDSJFlavour);
   fChain->SetBranchAddress("AK8SDSJCSV", &AK8SDSJCSV, &b_AK8SDSJCSV);
   fChain->SetBranchAddress("nAK8puppiSDSJ", &nAK8puppiSDSJ, &b_nAK8puppiSDSJ);
   fChain->SetBranchAddress("AK8puppiSDSJPt", &AK8puppiSDSJPt, &b_AK8puppiSDSJPt);
   fChain->SetBranchAddress("AK8puppiSDSJEta", &AK8puppiSDSJEta, &b_AK8puppiSDSJEta);
   fChain->SetBranchAddress("AK8puppiSDSJPhi", &AK8puppiSDSJPhi, &b_AK8puppiSDSJPhi);
   fChain->SetBranchAddress("AK8puppiSDSJMass", &AK8puppiSDSJMass, &b_AK8puppiSDSJMass);
   fChain->SetBranchAddress("AK8puppiSDSJE", &AK8puppiSDSJE, &b_AK8puppiSDSJE);
   fChain->SetBranchAddress("AK8puppiSDSJCharge", &AK8puppiSDSJCharge, &b_AK8puppiSDSJCharge);
   fChain->SetBranchAddress("AK8puppiSDSJFlavour", &AK8puppiSDSJFlavour, &b_AK8puppiSDSJFlavour);
   fChain->SetBranchAddress("AK8puppiSDSJCSV", &AK8puppiSDSJCSV, &b_AK8puppiSDSJCSV);
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


//for i in em et mt me tt ; do for j in 2016 2017 2018 ; do echo python makeSubmissionPackage.py -x SkimerBoost_$i -n File_$i\_mc\_$j -i InputSample_$j\_mc.txt -o /store/user/abdollah/SkimBoostedH2/$j/$i/v3/ ; done ; done
