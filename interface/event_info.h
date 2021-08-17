#ifndef EVENT_INFO_H
#define EVENT_INFO_H

#include "TTree.h"
#include <regex>
#include <unordered_map>
using namespace std;

/////////////////////////////////////////
// Purpose: To hold general event data //
/////////////////////////////////////////
class event_info {
private:
//    Float_t genpX, genpY, genM, genpT, numGenJets, GenWeight, genDR; // gen
//    Float_t npv, npu, rho;        // event
//    Float_t matchEle25, filterEle25, passEle25;                   // 2016 etau trigger
//    Float_t matchEle27, filterEle27, passEle27;                   // 2017 single el 27 trigger
//    Float_t matchEle32, filterEle32, passEle32;                   // 2017 single el 32 trigger
//    Float_t matchEle35, filterEle35, passEle35;                   // 2017 single el 35 trigger
//    Float_t matchEle24Tau30, filterEle24Tau30, passEle24Tau30;    // 2017 etau cross trigger
//    Float_t passDoubleTauCmbIso35, matchDoubleTauCmbIso35_1, filterDoubleTauCmbIso35_1, matchDoubleTauCmbIso35_2, filterDoubleTauCmbIso35_2; // tt trigger
//    Float_t passDoubleTau35, matchDoubleTau35_1, filterDoubleTau35_1, matchDoubleTau35_2, filterDoubleTau35_2;                               // tt trigger
//    Float_t matchIsoMu19Tau20_1, matchIsoMu19Tau20_2, filterIsoMu19Tau20_1, filterIsoMu19Tau20_2, passIsoMu19Tau20; // cross trigger
//    Float_t matchIsoMu22_1, filterIsoMu22_1, passIsoMu22;                         // single muon trigger
//    Float_t matchIsoTkMu22_1, filterIsoTkMu22_1, passIsoTkMu22;                   // single muon trigger
//    Float_t matchIsoMu22eta2p1_1, filterIsoMu22eta2p1_1, passIsoMu22eta2p1;       // single muon trigger
//    Float_t matchIsoTkMu22eta2p1_1, filterIsoTkMu22eta2p1_1, passIsoTkMu22eta2p1; // single muon trigger
//    Float_t mMatchesIsoMu20Tau27Path, mMatchesIsoMu20Tau27Filter, tMatchesIsoMu20Tau27Path, tMatchesIsoMu20Tau27Filter, Mu20Tau27Pass; // 2017 single muon trigger
//    Float_t mMatchesIsoMu24Path, mMatchesIsoMu24Filter, IsoMu24Pass, mMatchesIsoMu27Path, mMatchesIsoMu27Filter, IsoMu27Pass;          // 2017 single muon trigger
//    Bool_t PassEle25, PassEle27, PassEle32, PassEle35, PassEle24Tau30, PassDoubleTauCmbIso35, PassDoubleTau35, PassIsoMu19Tau20, PassIsoMu22, PassIsoTkMu22, PassIsoMu22eta2p1, PassIsoTkMu22eta2p1;
//    Bool_t PassMu24, PassMu27, PassMu20Tau27;
//    Float_t m_sv, pt_sv; // SVFit
//    Float_t Dbkg_VBF, Dbkg_ggH, Dbkg_ZH, Dbkg_WH, Phi, Phi1,Phi0, costheta1, costheta2, costhetastar, Q2V1, Q2V2;  // MELA
//    Float_t ME_sm_VBF, ME_sm_ggH, ME_sm_WH, ME_sm_ZH, ME_bkg, ME_bkg1, ME_bkg2, ME_ps_VBF, ME_ps_ggH,ME_a2_VBF;
//    //new
//    Float_t D_PS_VBF, D_PS_ggH, D_PS_ggH_qqInit, ME_ps_VBF_norm, ME_a1a2int_VBF, ME_L1_VBF ,ME_L1_VBF_norm,ME_a1L1int_VBF , ME_L1Zg_VBF,ME_L1Zg_VBF_norm, ME_a1L1Zgint_VBF, ME_sm_ggH_qqInit, ME_a1a3int_VBF, ME_a1a3int_ggH, D_CP_VBF, D_CP_ggH;
//    // MELA
//    Float_t Rivet_nJets30, Rivet_higgsPt, Rivet_stage1_cat_pTjet30GeV, Rivet_stage1_1_fine_cat_pTjet30GeV;
//    Float_t Flag_BadChargedCandidateFilter, Flag_BadPFMuonFilter, Flag_EcalDeadCellTriggerPrimitiveFilter, Flag_HBHENoiseFilter, Flag_HBHENoiseIsoFilter, Flag_badMuons, Flag_duplicateMuons,
//    Flag_ecalBadCalibFilter, Flag_eeBadScFilter, Flag_globalSuperTightHalo2016Filter, Flag_globalTightHalo2016Filter, Flag_goodVertices;
//
//    Float_t mu8e23Pass, mu8e23DZPass, mu23e12Pass, mu23e12DZPass;
//    Bool_t  Passmu23e12, Passmu8e23;
//
//    float bweight_2016,bweight_2017,bweight_2018,prefiring_weight,prefiring_weight_up,prefiring_weight_down;
//    float mm_weight_nlo, ps_weight_nlo, sm_weight_nlo;
//
//
//
//    Int_t run, lumi;
//    ULong64_t evt;
//    UInt_t convert_evt;
//    int year_;
//    bool isEmbed;
    std::unordered_map<std::string, int> unc_map;
    
public:
    event_info (std::string);
    virtual ~event_info () {};
//    void setEmbed() {isEmbed = true;}
//    void setRivets(TTree*);
//
//    // tautau Trigger Info
//    Bool_t getPassEle25();
//    Bool_t getPassEle27();
//    Bool_t getPassEle32();
//    Bool_t getPassEle35();
//    Bool_t getPassEle24Tau30();
//    Bool_t getPassMu19Tau20();
//    Bool_t getPassIsoMu22();
//    Bool_t getPassIsoTkMu22();
//    Bool_t getPassIsoMu22eta2p1();
//    Bool_t getPassIsoTkMu22eta2p1();
//    Bool_t getPassMu20Tau27();
//    Bool_t getPassMu24();
//    Bool_t getPassMu27();
//    Bool_t getPassDoubleTauCmbIso35();
//    Bool_t getPassDoubleTau35();
//    Bool_t getPassFlags();
//
//    Bool_t getmu23e12Pass();
//    Bool_t getmu8e23Pass();
//
//    Bool_t getmu23e12Pass_noDZreq();
//    Bool_t getmu8e23Pass_noDZreq();
//
//    // Event Info
//    //  Float_t getNPV()          { return npv;             };
//    Float_t getNPU()          { return npu;             };
//    Float_t getRho()          { return rho;             };
//    Int_t getRun()           { return run;             };
//    Int_t getLumi()          { return lumi;            };
//    ULong64_t getEvt()        { return evt;             };
//
//    // Generator Info
//    Float_t getGenPx()        { return genpX;           };
//    Float_t getGenPy()        { return genpY;           };
//    Float_t getGenM()         { return genM;            };
//    Float_t getGenPt()        { return genpT;           };
//    Float_t getNumGenJets()   { return numGenJets;      };
//    Float_t getGenWeight()    { return GenWeight;       };
//    Float_t getTauGenDR()     { return genDR;           };
//
//    // SVFit Info
//    Float_t getMSV()          { return m_sv;            };
//    Float_t getPtSV()         { return pt_sv;           };
//
//    // MELA Info
//    Float_t getDbkg_VBF()     { return Dbkg_VBF;        };
//    Float_t getDbkg_ggH()     { return Dbkg_ggH;        };
//    Float_t getDbkg_ZH()      { return Dbkg_ZH;         };
//    Float_t getDbkg_WH()      { return Dbkg_WH;         };
////    Float_t getPhi()          { return Phi;             };
//    Float_t getPhi0()          { return Phi0;             };
//    Float_t getPhi1()         { return Phi1;            };
//    Float_t getCosTheta1()    { return costheta1;       };
//    Float_t getCosTheta2()    { return costheta2;       };
//    Float_t getCosThetaStar() { return costhetastar;    };
//    Float_t getQ2V1()         { return Q2V1;            };
//    Float_t getQ2V2()         { return Q2V2;            };
//    Float_t getME_sm_VBF()    { return ME_sm_VBF;       };
//    Float_t getME_sm_ggH()    { return ME_sm_ggH;       };
//    Float_t getME_sm_WH()     { return ME_sm_WH;        };
//    Float_t getME_sm_ZH()     { return ME_sm_ZH;        };
//    Float_t getME_bkg()       { return ME_bkg;          };
//    Float_t getME_bkg1()      { return ME_bkg1;         };
//    Float_t getME_bkg2()      { return ME_bkg2;         };
//
//
//    Float_t getD_PS_VBF()         { return D_PS_VBF;         };
//    Float_t getD_PS_ggH()         { return D_PS_ggH;         };
//    Float_t getD_PS_ggH_qqInit()         { return D_PS_ggH_qqInit;         };
//    Float_t getME_ps_VBF_norm()         { return ME_ps_VBF_norm;         };
//    Float_t getME_a1a2int_VBF()         { return ME_a1a2int_VBF;     };
//    Float_t getME_L1_VBF()         { return ME_L1_VBF;         };
//    Float_t getME_L1_VBF_norm()         { return ME_L1_VBF_norm;         };
//    Float_t getME_a1L1int_VBF()         { return ME_a1L1int_VBF;         };
//    Float_t getME_L1Zg_VBF()         { return ME_L1Zg_VBF;         };
//    Float_t getME_L1Zg_VBF_norm()         { return ME_L1Zg_VBF_norm;         };
//    Float_t getME_a1L1Zgint_VBF()         { return ME_a1L1Zgint_VBF;         };
//    Float_t getME_sm_ggH_qqInit()         { return ME_sm_ggH_qqInit;         };
//    Float_t getME_a1a3int_VBF()         { return ME_a1a3int_VBF;         };
//    Float_t getME_a1a3int_ggH()         { return ME_a1a3int_ggH;         };
//    Float_t getD_CP_VBF()         { return D_CP_VBF;         };
//    Float_t getD_CP_ggH()         { return D_CP_ggH;         };
//
//
//
//
//
//    Float_t getME_ps_ggH()      { return ME_ps_ggH;         };
//    Float_t getME_ps_VBF()      { return ME_ps_VBF;         };
//    Float_t getME_a2_VBF()      { return ME_a2_VBF;         };
//
//
//    // ggH NNLOPS Info
//    Float_t getNjetsRivet()   { return Rivet_nJets30;   };
//    Float_t getHiggsPtRivet() { return Rivet_higgsPt;   };
//    Float_t getJetPtRivet() { return Rivet_stage1_cat_pTjet30GeV; }
//    Float_t getJetPt_stage1_1Rivet() { return Rivet_stage1_1_fine_cat_pTjet30GeV; }//Rivet_stage1_1_fine_cat_pTjet30GeV
    Float_t getRivetUnc(std::vector<double>, std::string);
    
    
//    Float_t  getbweight_2016() { return bweight_2016;   };
//    Float_t  getbweight_2017() { return bweight_2017;   };
//    Float_t  getbweight_2018() { return bweight_2018;   };
    
//    Float_t  getprefiring_weight() { return prefiring_weight;   };
//    Float_t  getprefiring_weight_down() { return prefiring_weight_down;   };
//    Float_t  getprefiring_weight_up() { return prefiring_weight_up;   };
    
//    Float_t  getmm_weight_nlo() { return mm_weight_nlo;   };
//    Float_t  getps_weight_nlo() { return ps_weight_nlo;   };
//    Float_t  getsm_weight_nlo() { return sm_weight_nlo;   };
    
    
};

// read data from trees into member variables
//event_info::event_info(TTree* input, std::string syst, std::string analyzer, int year) :
event_info::event_info(std::string syst) :
//year_(year),
//isEmbed(false),
unc_map{
{"_THU_ggH_Mu",0},{"_THU_ggH_Res",1},{"_THU_ggH_Mig01",2},{"_THU_ggH_Mig12",3},{"_THU_ggH_VBF2j",4},{"_THU_ggH_VBF3j",5},{"_THU_ggH_PT60",6},{"_THU_ggH_PT120",7},{"_THU_ggH_qmtop",8}
//    {"Rivet0_Up", 0}, {"Rivet0_Down", 0}, {"Rivet1_Up", 1}, {"Rivet1_Down", 1},
//    {"Rivet2_Up", 2}, {"Rivet2_Down", 2}, {"Rivet3_Up", 3}, {"Rivet3_Down", 3},
//    {"Rivet4_Up", 4}, {"Rivet4_Down", 4}, {"Rivet5_Up", 5}, {"Rivet5_Down", 5},
//    {"Rivet6_Up", 6}, {"Rivet6_Down", 6}, {"Rivet7_Up", 7}, {"Rivet7_Down", 7},
//    {"Rivet8_Up", 8}, {"Rivet8_Down", 8}
}

{
//    auto end = std::string::npos;
//    std::string m_sv_name("m_sv"), pt_sv_name("pt_sv");
//
//    // m_sv names for systematics
//
//    if (syst.find("Recoil") != std::string::npos ) {
//        syst = std::regex_replace(syst, std::regex("\\YEAR"), "");
//        syst = std::regex_replace(syst, std::regex("\\YEAR"), "");
//        m_sv_name += "_" + syst ;
//        pt_sv_name += "_" + syst;
//    }
//
//    else if (syst.find("Jet") != std::string::npos) {
//        m_sv_name += "_" + syst;
//        pt_sv_name += "_" + syst;
//    }
//    else if (syst.find("EES") != std::string::npos || syst.find("MES") != std::string::npos) {
//        m_sv_name += "_" + syst;
//        pt_sv_name += "_" + syst;
//    }
//
//
//    input -> SetBranchAddress( m_sv_name.c_str() , &m_sv            );
//    input -> SetBranchAddress( pt_sv_name.c_str(), &pt_sv           );
//
////     input -> SetBranchAddress( "Phi"             , &Phi             );
//     input -> SetBranchAddress( "Phi0"             , &Phi0             );
//     input -> SetBranchAddress( "Phi1"            , &Phi1            );
//     input -> SetBranchAddress( "costheta1"       , &costheta1       );
//     input -> SetBranchAddress( "costheta2"       , &costheta2       );
//     input -> SetBranchAddress( "costhetastar"    , &costhetastar    );
//     input -> SetBranchAddress( "Q2V1"            , &Q2V1            );
//     input -> SetBranchAddress( "Q2V2"            , &Q2V2            );
//
//
//    input -> SetBranchAddress( "run"             , &run             );
//    input -> SetBranchAddress( "lumi"            , &lumi            );
//    //  input -> SetBranchAddress( "npv"             , &npv             );
//    input -> SetBranchAddress( "nTruePU"             , &npu             );
//    input -> SetBranchAddress( "genpX"           , &genpX           );
//    input -> SetBranchAddress( "genpY"           , &genpY           );
//    input -> SetBranchAddress( "genM"            , &genM            );
//    input -> SetBranchAddress( "genpT"           , &genpT           );
//    input -> SetBranchAddress( "numGenJets"      , &numGenJets      );
//    input -> SetBranchAddress( "GenWeight"       , &GenWeight       );
//
//    input -> SetBranchAddress( "Dbkg_VBF"        , &Dbkg_VBF        );
//    input -> SetBranchAddress( "Dbkg_ggH"        , &Dbkg_ggH        );
//    input -> SetBranchAddress( "Dbkg_ZH"         , &Dbkg_ZH         );
//    input -> SetBranchAddress( "Dbkg_WH"         , &Dbkg_WH         );
//
//
//    input -> SetBranchAddress( "ME_sm_VBF"       , &ME_sm_VBF       );
//    input -> SetBranchAddress( "ME_sm_ggH"       , &ME_sm_ggH       );
//    input -> SetBranchAddress( "ME_sm_WH"        , &ME_sm_WH        );
//    input -> SetBranchAddress( "ME_sm_ZH"        , &ME_sm_ZH        );
//    input -> SetBranchAddress( "ME_bkg"          , &ME_bkg          );
//    input -> SetBranchAddress( "ME_bkg1"         , &ME_bkg1         );
//    input -> SetBranchAddress( "ME_bkg2"         , &ME_bkg2         );
//    input -> SetBranchAddress( "ME_bkg"          , &ME_bkg          );
//    input -> SetBranchAddress( "ME_ps_VBF"       , &ME_ps_VBF       );
//    input -> SetBranchAddress( "ME_a2_VBF"       , &ME_a2_VBF       );
//    input -> SetBranchAddress( "ME_ps_ggH"       , &ME_ps_ggH       );
//    //new
//    input -> SetBranchAddress( "D_PS_VBF"       , &D_PS_VBF       );
//    input -> SetBranchAddress( "D_PS_ggH"       , &D_PS_ggH       );
//    input -> SetBranchAddress( "D_PS_ggH_qqInit"       , &D_PS_ggH_qqInit       );
//    input -> SetBranchAddress( "ME_ps_VBF_norm"       , &ME_ps_VBF_norm       );
//    input -> SetBranchAddress( "ME_a1a2int_VBF"       , &ME_a1a2int_VBF      );
//    input -> SetBranchAddress( "ME_L1_VBF"       , &ME_L1_VBF       );
//    input -> SetBranchAddress( "ME_L1_VBF_norm"       , &ME_L1_VBF_norm       );
//    input -> SetBranchAddress( "ME_a1L1int_VBF"       , &ME_a1L1int_VBF       );
//    input -> SetBranchAddress( "ME_L1Zg_VBF"       , &ME_L1Zg_VBF       );
//    input -> SetBranchAddress( "ME_L1Zg_VBF_norm"       , &ME_L1Zg_VBF_norm       );
//    input -> SetBranchAddress( "ME_a1L1Zgint_VBF"       , &ME_a1L1Zgint_VBF       );
//    input -> SetBranchAddress( "ME_sm_ggH_qqInit"       , &ME_sm_ggH_qqInit       );
//    input -> SetBranchAddress( "ME_a1a3int_VBF"       , &ME_a1a3int_VBF       );
//    input -> SetBranchAddress( "ME_a1a3int_ggH"       , &ME_a1a3int_ggH       );
//    input -> SetBranchAddress( "D_CP_VBF"       , &D_CP_VBF       );
//    input -> SetBranchAddress( "D_CP_ggH"       , &D_CP_ggH       );
//
//
//    input -> SetBranchAddress("Flag_BadChargedCandidateFilter"         , &Flag_BadChargedCandidateFilter         );
//    input -> SetBranchAddress("Flag_BadPFMuonFilter"                   , &Flag_BadPFMuonFilter                   );
//    input -> SetBranchAddress("Flag_EcalDeadCellTriggerPrimitiveFilter", &Flag_EcalDeadCellTriggerPrimitiveFilter);
//    input -> SetBranchAddress("Flag_HBHENoiseFilter"                   , &Flag_HBHENoiseFilter                   );
//    input -> SetBranchAddress("Flag_HBHENoiseIsoFilter"                , &Flag_HBHENoiseIsoFilter                );
//    input -> SetBranchAddress("Flag_badMuons"                          , &Flag_badMuons                          );
//    input -> SetBranchAddress("Flag_duplicateMuons"                    , &Flag_duplicateMuons                    );
//    input -> SetBranchAddress("Flag_ecalBadCalibFilter"                , &Flag_ecalBadCalibFilter                );
//    input -> SetBranchAddress("Flag_eeBadScFilter"                     , &Flag_eeBadScFilter                     );
//    input -> SetBranchAddress("Flag_globalSuperTightHalo2016Filter"    , &Flag_globalSuperTightHalo2016Filter    );
//    input -> SetBranchAddress("Flag_globalTightHalo2016Filter"         , &Flag_globalTightHalo2016Filter         );
//    input -> SetBranchAddress("Flag_goodVertices"                      , &Flag_goodVertices                      );
//
////    input->SetBranchAddress("bweight_2016", &bweight_2016);
////    input->SetBranchAddress("bweight_2017", &bweight_2017);
////    input->SetBranchAddress("bweight_2018", &bweight_2018);
//    input->SetBranchAddress("prefiring_weight", &prefiring_weight);
//    input->SetBranchAddress("prefiring_weight_up", &prefiring_weight_up);
//    input->SetBranchAddress("prefiring_weight_down", &prefiring_weight_down);
//
////    input->SetBranchAddress("mm_weight_nlo", &mm_weight_nlo);
////    input->SetBranchAddress("ps_weight_nlo", &ps_weight_nlo);
////    input->SetBranchAddress("sm_weight_nlo", &sm_weight_nlo);
//
//    input -> SetBranchAddress( "evt"                     , &evt              );
//    input -> SetBranchAddress("mu8e23Pass", &mu8e23Pass);
//    input -> SetBranchAddress("mu8e23DZPass", &mu8e23DZPass);
//    input -> SetBranchAddress("mu23e12Pass", &mu23e12Pass);
//    input -> SetBranchAddress("mu23e12DZPass", &mu23e12DZPass);

    }
        
//        void event_info::setRivets(TTree* input) {
//            input -> SetBranchAddress("Rivet_nJets30", &Rivet_nJets30 );
//            input -> SetBranchAddress("Rivet_higgsPt", &Rivet_higgsPt );
//            input->SetBranchAddress("Rivet_stage1_cat_pTjet30GeV", &Rivet_stage1_cat_pTjet30GeV);
//            input->SetBranchAddress("Rivet_stage1_1_fine_cat_pTjet30GeV", &Rivet_stage1_1_fine_cat_pTjet30GeV); //tmp solution
//        }
        
        Float_t event_info::getRivetUnc(std::vector<double> uncs, std::string syst) {
            if (syst.find("_THU_ggH") != std::string::npos) {
                int index = unc_map[syst];
                return uncs.at(index);
//
//                if (syst.find("Up") != std::string::npos) {
//                    return uncs.at(index);
//                } else {
//                    return -1 * uncs.at(index);
//                }
            }
            else {
        return 1;
        }
        }
        
        
        
//        Bool_t event_info::getPassFlags() {
//            if (year_ == 2016) {
//                return !(Flag_goodVertices || Flag_globalSuperTightHalo2016Filter || Flag_HBHENoiseIsoFilter
//                         || Flag_HBHENoiseFilter || Flag_EcalDeadCellTriggerPrimitiveFilter || Flag_BadPFMuonFilter);
//
//            } else if (year_ == 2017) {
//                return !(Flag_goodVertices || Flag_globalSuperTightHalo2016Filter || Flag_HBHENoiseFilter
//                         || Flag_HBHENoiseIsoFilter || Flag_EcalDeadCellTriggerPrimitiveFilter || Flag_BadPFMuonFilter
//                         || Flag_BadChargedCandidateFilter || Flag_eeBadScFilter || Flag_ecalBadCalibFilter);
//            } else {
//                return !(Flag_goodVertices || Flag_globalSuperTightHalo2016Filter || Flag_HBHENoiseFilter
//                         || Flag_HBHENoiseIsoFilter || Flag_EcalDeadCellTriggerPrimitiveFilter || Flag_BadPFMuonFilter
//                         || Flag_eeBadScFilter || Flag_ecalBadCalibFilter);
//            }
//        }
//
//
//        Bool_t event_info::getmu23e12Pass() {
//            Passmu23e12= mu23e12Pass || mu23e12DZPass;
//            return Passmu23e12;
//        }
//
//        Bool_t event_info::getmu8e23Pass() {
//            Passmu8e23=   mu8e23Pass || mu8e23DZPass;
//            return Passmu8e23;
//        }
//
//        Bool_t event_info::getmu23e12Pass_noDZreq() {
//            Passmu23e12= mu23e12Pass;
//            return Passmu23e12;
//        }
//
//        Bool_t event_info::getmu8e23Pass_noDZreq() {
//            Passmu8e23=   mu8e23Pass ;
//            return Passmu8e23;
//        }
        
        
#endif
