#include <math.h>
#include <limits>
#include <string>
#include <vector>
#include "PhysicsTools/FWLite/interface/CommandLineParser.h"
#include "TF1.h"
#include "TFile.h"
#include "TH1F.h"
#include "TKey.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TTree.h"

#include "FWCore/ParameterSet/interface/FileInPath.h"

#include "TauAnalysis/ClassicSVfit/interface/FastMTT.h"
#include "TauAnalysis/ClassicSVfit/interface/MeasuredTauLepton.h"
#include "TauAnalysis/ClassicSVfit/interface/svFitHistogramAdapter.h"

#include "TFile.h"
#include "TH1.h"
#include "TTree.h"


//        _met_JESUp = met_JESUp ;
//        _met_JESDown = met_JESDown ;
//        _met_UESUp = met_UESUp ;
//        _met_UESDown = met_UESDown ;
//        _metphi_JESUp = metphi_JESUp ;
//        _metphi_JESDown = metphi_JESDown ;
//        _metphi_UESUp = metphi_UESUp ;
//        _metphi_UESDown = metphi_UESDown ;
//
//        _met_reso_Up = met_reso_Up;
//        _met_reso_Down = met_reso_Down;
//        _met_resp_Up = met_resp_Up;
//        _met_resp_Down = met_resp_Down;
//        _metphi_reso_Up = metphi_reso_Up;
//        _metphi_reso_Down = metphi_reso_Down;
//        _metphi_resp_Up = metphi_resp_Up;
//        _metphi_resp_Down = metphi_resp_Down;



// If doES       0 does not apply any ES shifts
//              1 applies ES shifts to TT channel, no effect on other channels
//
// If isWJets    0 no shift in number of jets used for recoil corrections
//              1 shifts njets + 1 for recoil corrections
//
// If metType    1 use mvamet
//        -1 use pf met

FastMTT svfitAlgorithm;

int copyFiles(optutl::CommandLineParser parser, TFile *fOld, TFile *fNew);
void readdir(TDirectory *dir, optutl::CommandLineParser parser, char TreeToUse[], int doES, int isWJets, int metType);
int CopyFile(const char *fname, optutl::CommandLineParser parser);
void CopyDir(TDirectory *source, optutl::CommandLineParser parser);
double tesUncertainties(unsigned int year, float decaymode);
double pt_shifted(float pt, double tesUnc, bool isDM, int updown);
double metcorr_shifted(double metcorr, float pt1, float phi1, bool isDM1, double tesUnc1, float pt2, float phi2, bool isDM2, double tesUnc2, int xory,
                       int updown);
void runFastMTT(const std::vector<classic_svFit::MeasuredTauLepton> &, double, double, const TMatrixD &, float &, float &);

int main(int argc, char *argv[]) {
    optutl::CommandLineParser parser("Sets Event Weights in the ntuple");
    parser.addOption("branch", optutl::CommandLineParser::kString, "Branch", "__svFit__");
    parser.addOption("newFile", optutl::CommandLineParser::kString, "newFile", "newFile.root");
    parser.addOption("inputFile", optutl::CommandLineParser::kString, "input File");
    parser.addOption("doES", optutl::CommandLineParser::kDouble, "doES", 0.0);
    parser.addOption("isWJets", optutl::CommandLineParser::kDouble, "isWJets", 0.0);
    parser.addOption("metType", optutl::CommandLineParser::kDouble, "metType", -1.0);  // 1 = mvamet, -1 = pf met
    parser.addOption("numEvents", optutl::CommandLineParser::kInteger, "numEvents", -1);
    parser.parseArguments(argc, argv);
    
    std::cout << "EXTRA COMMANDS:"
    << "\n --- numEvents: " << parser.integerValue("numEvents") << "\n --- doES: " << parser.doubleValue("doES")
    << "\n --- isWJets: " << parser.doubleValue("isWJets") << "\n --- metType: " << parser.doubleValue("metType") << std::endl;
    
    // Make sure a proper Met Type is chosen
    assert(parser.doubleValue("metType") == 1.0 || parser.doubleValue("metType") == -1.0);
    
    char TreeToUse[180] = "first";
    
    TFile *fProduce;  //= new TFile(parser.stringValue("newFile").c_str(),"UPDATE");
    
    TFile *f = new TFile(parser.stringValue("inputFile").c_str(), "READ");
    std::cout << "Creating new outputfile" << std::endl;
    std::string newFileName = parser.stringValue("newFile");
    
    fProduce = new TFile(newFileName.c_str(), "RECREATE");
    
    if (copyFiles(parser, f, fProduce) == 0) return -1;
    
    fProduce = new TFile(newFileName.c_str(), "UPDATE");
    fProduce->ls();
    readdir(fProduce, parser, TreeToUse, parser.doubleValue("doES"), parser.doubleValue("isWJets"), parser.doubleValue("metType"));
    fProduce->Close();
    f->Close();
}

void readdir(TDirectory *dir, optutl::CommandLineParser parser, char TreeToUse[], int doES, int isWJets, int metType) {
    TLorentzVector tau1, tau2;
    
    classic_svFit::MeasuredTauLepton::kDecayType decayType1 = classic_svFit::MeasuredTauLepton::kUndefinedDecayType;
    classic_svFit::MeasuredTauLepton::kDecayType decayType2 = classic_svFit::MeasuredTauLepton::kUndefinedDecayType;
    
    // Both masses should depend on decay mode and particle?
    float mass1;
    float mass2;
    std::string channel = "x";
    
    TDirectory *dirsav = gDirectory;
    TKey *key;
    dir->cd();
    
    std::vector<TString> processedNames;
    
    TIter next(dir->GetListOfKeys());
    while ((key = (TKey *)next())) {
        printf("Found key=%s \n", key->GetName());
        
        TObject *obj = key->ReadObj();
        if (obj->IsA()->InheritsFrom(TDirectory::Class())) {
            std::cout << "This is a directory, diving in!" << std::endl;
            // zero the processedNames vector, to allow processing trees with duplicate names in separate directories
            processedNames.clear();
            
            dir->cd(key->GetName());
            TDirectory *subdir = gDirectory;
            sprintf(TreeToUse, "%s", key->GetName());
            readdir(subdir, parser, TreeToUse, parser.doubleValue("doES"), parser.doubleValue("isWJets"), parser.doubleValue("metType"));
            
            dirsav->cd();
        } else if (obj->IsA()->InheritsFrom(TTree::Class())) {
            // check  if this tree was already processed
            std::vector<TString>::const_iterator it = find(processedNames.begin(), processedNames.end(), key->GetName());
            if (it != processedNames.end()) {
                std::cout << "This tree was already processed, skipping..." << std::endl;
                continue;
            }
            std::cout << "This is the tree! Start processing" << std::endl;
            processedNames.push_back(key->GetName());
            
            // Identify the process
            if (std::string(key->GetName()).find("tt") != std::string::npos || std::string(key->GetName()).find("tautau") != std::string::npos) {
                decayType1 = classic_svFit::MeasuredTauLepton::kTauToHadDecay;
                decayType2 = classic_svFit::MeasuredTauLepton::kTauToHadDecay;
                mass1 = 0.13957;
                mass2 = 0.13957;
                channel = "tt";
                std::cout << "Identified channel tt and using kappa = 5" << std::endl;
            } else if (std::string(key->GetName()).find("em") != std::string::npos) {
                std::cout << "EMu sample" << std::endl;
                decayType1 = classic_svFit::MeasuredTauLepton::kTauToElecDecay;
                decayType2 = classic_svFit::MeasuredTauLepton::kTauToMuDecay;
                mass1 = 0.00051100;
                mass2 = 0.105658;
                channel = "em";
                std::cout << "Identified channel em and using kappa = 3" << std::endl;
            } else if (std::string(key->GetName()).find("mue") != std::string::npos) {
                std::cout << "MuE sample" << std::endl;
                decayType1 = classic_svFit::MeasuredTauLepton::kTauToMuDecay;
                decayType2 = classic_svFit::MeasuredTauLepton::kTauToElecDecay;
                mass1 = 0.105658;
                mass2 = 0.00051100;
                channel = "me";
                std::cout << "Identified channel em and using kappa = 3" << std::endl;
            } else if (std::string(key->GetName()).find("et") != std::string::npos || std::string(key->GetName()).find("etau") != std::string::npos) {
                std::cout << "eleTauTree" << std::endl;
                decayType1 = classic_svFit::MeasuredTauLepton::kTauToElecDecay;
                decayType2 = classic_svFit::MeasuredTauLepton::kTauToHadDecay;
                mass1 = 0.00051100;
                mass2 = 0;
                channel = "et";
                std::cout << "Identified channel et and using kappa = 4" << std::endl;
            } else if (std::string(key->GetName()).find("mt") != std::string::npos ||
                       std::string(key->GetName()).find("mutau") != std::string::npos||
                       std::string(key->GetName()).find("Event") != std::string::npos) {
                std::cout << "muTauEvent" << std::endl;
                decayType1 = classic_svFit::MeasuredTauLepton::kTauToMuDecay;
                decayType2 = classic_svFit::MeasuredTauLepton::kTauToHadDecay;
                mass1 = 0.105658;
                mass2 = 0;
                channel = "mt";
                std::cout << "Identified channel mt and using kappa = 4" << std::endl;
            } else {
                std::cout << "Tree " << key->GetName() << " does not match ... Skipping!!" << std::endl;
                return;
            }
            
            TTree *t = reinterpret_cast<TTree*>(obj);
            float svFitMass = -10;
            float svFitPt = -10;
            //            float svFitEta = -10;
            //            float svFitPhi = -10;
            //            float svFitMET = -10;
            //            float svFitTransverseMass = -10;
            
            float metcorr_ex = -10;  // corrected met px (float)
            float metcorr_ey = -10;  // corrected met py (float)
            
            // recoil
//            float metcorrRecoilResoUp_ex = -10;
//            float metcorrRecoilResoUp_ey = -10;
//            float metcorrRecoilResoDown_ex = -10;
//            float metcorrRecoilResoDown_ey = -10;
//            float metcorrRecoilRespUp_ex = -10;
//            float metcorrRecoilRespUp_ey = -10;
//            float metcorrRecoilRespDown_ex = -10;
//            float metcorrRecoilRespDown_ey = -10;
            float metcorrJESUp_ex = -10;
            float metcorrJESUp_ey = -10;
            float metcorrJESDown_ex = -10;
            float metcorrJESDown_ey = -10;
            float metcorrUESUp_ex = -10;
            float metcorrUESUp_ey = -10;
            float metcorrUESDown_ex = -10;
            float metcorrUESDown_ey = -10;
            
            // If doing ES shifts, we need extra ouput branches
            
            float svFitMass_JES_Up = -10;
            float svFitPt_JES_Up = -10;
            float svFitMass_JES_Down = -10;
            float svFitPt_JES_Down = -10;
            
            float svFitMass_UES_Up = -10;
            float svFitPt_UES_Up = -10;
            float svFitMass_UES_Down = -10;
            float svFitPt_UES_Down = -10;
            
            float svFitMass_TES_Up = -10;
            float svFitPt_TES_Up = -10;
            float svFitMass_TES_Down = -10;
            float svFitPt_TES_Down = -10;


//            float svFitMass_reso_Up = -10;
//            float svFitPt_reso_Up = -10;
//            float svFitMass_reso_Down = -10;
//            float svFitPt_reso_Down = -10;
//
//            float svFitMass_resp_Up = -10;
//            float svFitPt_resp_Up = -10;
//            float svFitMass_resp_Down = -10;
//            float svFitPt_resp_Down = -10;
            
            
            // tau leptons
            
            //            float tau1_pt = -10;
            //            float tau1_eta = -10;
            //            float tau1_phi = -10;
            //            float tau1_m = -10;
            //            float tau2_pt = -10;
            //            float tau2_eta = -10;
            //            float tau2_phi = -10;
            //            float tau2_m = -10;
            
            std::vector<TBranch*> new_branches = {
                //                t->Branch("tau1_pt", &tau1_pt, "tau1_pt/F"),
                //                t->Branch("tau1_eta", &tau1_eta, "tau1_eta/F"),
                //                t->Branch("tau1_phi", &tau1_phi, "tau1_phi/F"),
                //                t->Branch("tau1_m", &tau1_m, "tau1_m/F"),
                //                t->Branch("tau2_pt", &tau2_pt, "tau2_pt/F"),
                //                t->Branch("tau2_eta", &tau2_eta, "tau2_eta/F"),
                //                t->Branch("tau2_phi", &tau2_phi, "tau2_phi/F"),
                //                t->Branch("tau2_m", &tau2_m, "tau2_m/F"),
                
                t->Branch("m_sv", &svFitMass, "m_sv/F"),
                t->Branch("pt_sv", &svFitPt, "pt_sv/F"),
                
                t->Branch("m_sv_JES_Up", &svFitMass_JES_Up, "m_sv_JES_Up/F"),
                t->Branch("pt_sv_JES_Up", &svFitPt_JES_Up, "pt_sv_JES_Up/F"),
                t->Branch("m_sv_JES_Down", &svFitMass_JES_Down, "m_sv_JES_Down/F"),
                t->Branch("pt_sv_JES_Down", &svFitPt_JES_Down, "pt_sv_JES_Down/F"),
                
                t->Branch("m_sv_UES_Up", &svFitMass_UES_Up, "m_sv_UES_Up/F"),
                t->Branch("pt_sv_UES_Up", &svFitPt_UES_Up, "pt_sv_UES_Up/F"),
                t->Branch("m_sv_UES_Down", &svFitMass_UES_Down, "m_sv_UES_Down/F"),
                t->Branch("pt_sv_UES_Down", &svFitPt_UES_Down, "pt_sv_UES_Down/F"),


                t->Branch("m_sv_TES_Up", &svFitMass_TES_Up, "m_sv_TES_Up/F"),
                t->Branch("pt_sv_TES_Up", &svFitPt_TES_Up, "pt_sv_TES_Up/F"),
                t->Branch("m_sv_TES_Down", &svFitMass_TES_Down, "m_sv_TES_Down/F"),
                t->Branch("pt_sv_TES_Down", &svFitPt_TES_Down, "pt_sv_TES_Down/F"),




//                t->Branch("m_sv_reso_Up", &svFitMass_reso_Up, "m_sv_reso_Up/F"),
//                t->Branch("pt_sv_reso_Up", &svFitPt_reso_Up, "pt_sv_reso_Up/F"),
//                t->Branch("m_sv_reso_Down", &svFitMass_reso_Down, "m_sv_reso_Down/F"),
//                t->Branch("pt_sv_reso_Down", &svFitPt_reso_Down, "pt_sv_reso_Down/F"),
//
//                t->Branch("m_sv_resp_Up", &svFitMass_resp_Up, "m_sv_resp_Up/F"),
//                t->Branch("pt_sv_resp_Up", &svFitPt_resp_Up, "pt_sv_resp_Up/F"),
//                t->Branch("m_sv_resp_Down", &svFitMass_resp_Down, "m_sv_resp_Down/F"),
//                t->Branch("pt_sv_resp_Down", &svFitPt_resp_Down, "pt_sv_resp_Down/F"),
                
            };
            
            
            Int_t era;
            unsigned long long evt;
            unsigned int run, lumi, NtupleVer;
            float isData;
            float pt1;
            float eta1;
            float phi1;
            //            int gen_match_1;
            float pt2;
            float eta2;
            float phi2;
            float m2;
            float m1;
            //            int gen_match_2;
            int decayMode1 = -999.;
            int decayMode2 = -999.;
            //            float mvaCovMatrix00;
            //            float mvaCovMatrix10;
            //            float mvaCovMatrix01;
            //            float mvaCovMatrix11;
            float pfCovMatrix00;
            float pfCovMatrix10;
            float pfCovMatrix01;
            float pfCovMatrix11;
            // float mvamet_ex, // uncorrected mva met px (float)
            //  mvamet_ey, // uncorrected mva met py (float)
            
            int njets = -999.;  // number of jets (hadronic jet multiplicity) (int)
            
            // define MET
            //            float mvamet;
            //            float mvametphi;
            float pfmet;
            float pfmetphi;
            
            float  met_JESUp = 0 ;
            float  met_JESDown = 0 ;
            float  met_UESUp = 0 ;
            float  met_UESDown = 0 ;
            float  metphi_JESUp = 0 ;
            float  metphi_JESDown = 0 ;
            float  metphi_UESUp = 0 ;
            float  metphi_UESDown = 0 ;
            
//            float  met_reso_Up = 0;
//            float  met_reso_Down = 0;
//            float  met_resp_Up = 0;
//            float  met_resp_Down = 0;
//            float  metphi_reso_Up = 0;
//            float  metphi_reso_Down = 0;
//            float  metphi_resp_Up = 0;
//            float  metphi_resp_Down = 0;
            
            TLorentzVector TMet(0, 0, 0, 0);
            // define MET covariance
            TMatrixD covMET(2, 2);
            
            
            //            float eCorrectedEt = 0., eEnergyScaleUp = 0., eEnergyScaleDown = 0., eEnergySigmaUp = 0., eEnergySigmaDown = 0.;
            
            // ele/mu variables
            TBranch *pt1branch;
            
            t->SetBranchAddress("era", &era);
            t->SetBranchAddress("NtupleVer", &NtupleVer);
            t->SetBranchAddress("evt", &evt);
            t->SetBranchAddress("run", &run);
            t->SetBranchAddress("lumi", &lumi);
            t->SetBranchAddress("isData", &isData);
            //            t->SetBranchAddress("gen_match_1", &gen_match_1);
            //            t->SetBranchAddress("gen_match_2", &gen_match_2);
            //            if (channel == "tt") t->SetBranchAddress("t1_decayMode", &decayMode1);
            //            if (channel == "tt") t->SetBranchAddress("t2_decayMode", &decayMode2);
            t->SetBranchAddress("decayMode1", &decayMode1);
            t->SetBranchAddress("decayMode2", &decayMode2);
            
            //            if (channel == "et") {
            //                t->SetBranchAddress("eCorrectedEt", &eCorrectedEt);
            //                t->SetBranchAddress("eEnergyScaleUp", &eEnergyScaleUp);
            //                t->SetBranchAddress("eEnergyScaleDown", &eEnergyScaleDown);
            //                t->SetBranchAddress("eEnergySigmaUp", &eEnergySigmaUp);
            //                t->SetBranchAddress("eEnergySigmaDown", &eEnergySigmaDown);
            //            }
            t->SetBranchAddress("pt_1", &pt1, &pt1branch);
            t->SetBranchAddress("eta_1", &eta1);
            t->SetBranchAddress("phi_1", &phi1);
            t->SetBranchAddress("pt_2", &pt2);
            t->SetBranchAddress("eta_2", &eta2);
            t->SetBranchAddress("phi_2", &phi2);
            t->SetBranchAddress("m_2", &m2);
            t->SetBranchAddress("m_1", &m1);
            // t->SetBranchAddress("l1_decayMode",&decayMode);
            //            if (channel != "tt") t->SetBranchAddress("l2_decayMode", &decayMode2);
            t->SetBranchAddress("njets", &njets);
            //            t->SetBranchAddress("met", &pfmet);
            //            t->SetBranchAddress("metphi", &pfmetphi);
            //
            //
            //            t->SetBranchAddress("met_JESUp", &met_JESUp);
            //            t->SetBranchAddress("met_JESDown", &met_JESDown);
            //            t->SetBranchAddress("met_UESUp", &met_UESUp);
            //            t->SetBranchAddress("met_UESDown", &met_UESDown);
            //            t->SetBranchAddress("metphi_JESUp", &metphi_JESUp);
            //            t->SetBranchAddress("metphi_JESDown", &metphi_JESDown);
            //            t->SetBranchAddress("metphi_UESUp", &metphi_UESUp);
            //            t->SetBranchAddress("metphi_UESDown", &metphi_UESDown);
            
            
            //  tree->Branch("met_px",         &met_px);
            //  tree->Branch("met_py",         &met_py);
            t->SetBranchAddress("pfMetNoRecoil", &pfmet);
            t->SetBranchAddress("pfMetPhiNoRecoil", &pfmetphi);
            
            t->SetBranchAddress("pfMET_T1JESUp", &met_JESUp);
            t->SetBranchAddress("pfMET_T1JESDo", &met_JESDown);
            t->SetBranchAddress("pfMET_T1UESUp", &met_UESUp);
            t->SetBranchAddress("pfMET_T1UESDo", &met_UESDown);
            t->SetBranchAddress("pfMETPhi_T1JESUp", &metphi_JESUp);
            t->SetBranchAddress("pfMETPhi_T1JESDo", &metphi_JESDown);
            t->SetBranchAddress("pfMETPhi_T1UESUp", &metphi_UESUp);
            t->SetBranchAddress("pfMETPhi_T1UESDo", &metphi_UESDown);
            
            
//            t->SetBranchAddress("met_reso_Up", &met_reso_Up);
//            t->SetBranchAddress("met_reso_Down", &met_reso_Down);
//            t->SetBranchAddress("met_resp_Up", &met_resp_Up);
//            t->SetBranchAddress("met_resp_Down", &met_resp_Down);
//            t->SetBranchAddress("metphi_reso_Up", &metphi_reso_Up);
//            t->SetBranchAddress("metphi_reso_Down", &metphi_reso_Down);
//            t->SetBranchAddress("metphi_resp_Up", &metphi_resp_Up);
//            t->SetBranchAddress("metphi_resp_Down", &metphi_resp_Down);
            
            
            
            
            // FOR PF MET ANALYSIS
            t->SetBranchAddress("metcov00", &pfCovMatrix00);
            t->SetBranchAddress("metcov01", &pfCovMatrix01);
            t->SetBranchAddress("metcov10", &pfCovMatrix10);
            t->SetBranchAddress("metcov11", &pfCovMatrix11);
            
            
            
            printf("Found tree -> weighting\n");
            
            int nevents = t->GetEntries();
            if (parser.integerValue("numEvents") != -1) nevents = parser.integerValue("numEvents");
            for (Int_t i = 0; i < nevents; ++i) {
                t->GetEntry(i);
                
                // Using PF Met or Mva Met?
                if (metType == 1) {  // 1 = Mva Met
                    std::cerr << "Only PF Met is currently supported. You're in for a world full of problems if you continue." << std::endl;
                    //                    TMet.SetPtEtaPhiM(mvamet, 0, mvametphi, 0);
                    
                    //                    covMET[0][0] = mvaCovMatrix00;
                    //                    covMET[1][0] = mvaCovMatrix10;
                    //                    covMET[0][1] = mvaCovMatrix01;
                    //                    covMET[1][1] = mvaCovMatrix11;
                }                     // mva met
                if (metType == -1) {  // -1 = PF Met
                    TMet.SetPtEtaPhiM(pfmet, 0, pfmetphi, 0);
                    metcorr_ex = pfmet * TMath::Cos(pfmetphi);
                    metcorr_ey = pfmet * TMath::Sin(pfmetphi);
                    // Shifted METs
                    
//                    metcorrRecoilResoUp_ex = met_reso_Up*TMath::Cos(metphi_reso_Up);
//                    metcorrRecoilResoUp_ey = met_reso_Up*TMath::Sin(metphi_reso_Up);
//
//                    metcorrRecoilResoDown_ex = met_reso_Down*TMath::Cos(metphi_reso_Down);
//                    metcorrRecoilResoDown_ey = met_reso_Down*TMath::Sin(metphi_reso_Down);
//
//                    metcorrRecoilRespUp_ex = met_resp_Up*TMath::Cos(metphi_resp_Up);
//                    metcorrRecoilRespUp_ey = met_resp_Up*TMath::Sin(metphi_resp_Up);
//
//                    metcorrRecoilRespDown_ex = met_resp_Down*TMath::Cos(metphi_resp_Down);
//                    metcorrRecoilRespDown_ey = met_resp_Down*TMath::Sin(metphi_resp_Down);
                    
                    metcorrJESUp_ex = met_JESUp*TMath::Cos(metphi_JESUp);
                    metcorrJESUp_ey = met_JESUp*TMath::Sin(metphi_JESUp);
                    
                    metcorrJESDown_ex = met_JESDown*TMath::Cos(metphi_JESDown);
                    metcorrJESDown_ey = met_JESDown*TMath::Sin(metphi_JESDown);
                    
                    metcorrUESUp_ex = met_UESUp*TMath::Cos(metphi_UESUp);
                    metcorrUESUp_ey = met_UESUp*TMath::Sin(metphi_UESUp);
                    
                    metcorrUESDown_ex = met_UESDown*TMath::Cos(metphi_UESDown);
                    metcorrUESDown_ey = met_UESDown*TMath::Sin(metphi_UESDown);
                    
                    
                    covMET[0][0] = pfCovMatrix00;
                    covMET[1][0] = pfCovMatrix10;
                    covMET[0][1] = pfCovMatrix01;
                    covMET[1][1] = pfCovMatrix11;
                }  // pf met
                
                if (channel == "tt" ) {
                    mass1 = m1;
                    mass2 = m2;
                    std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptons{
                        
                        classic_svFit::MeasuredTauLepton(decayType1, pt1, eta1, phi1, mass1, decayMode1),
                        classic_svFit::MeasuredTauLepton(decayType2, pt2, eta2, phi2, mass2, decayMode2)};
                    
                    runFastMTT(measuredTauLeptons, metcorr_ex, metcorr_ey, covMET, svFitMass, svFitPt);
                    

if (!isData){
                    
                    //                    runFastMTT(measuredTauLeptons, metcorrRecoilResoUp_ex, metcorrRecoilResoUp_ey, covMET, svFitMass_reso_Up, svFitPt_reso_Up);
                    //                    runFastMTT(measuredTauLeptons, metcorrRecoilResoDown_ex, metcorrRecoilResoDown_ey, covMET, svFitMass_reso_Down, svFitPt_reso_Down);
                    //                    runFastMTT(measuredTauLeptons, metcorrRecoilRespUp_ex, metcorrRecoilRespUp_ey, covMET, svFitMass_resp_Up, svFitPt_resp_Up);
                    //                    runFastMTT(measuredTauLeptons, metcorrRecoilRespDown_ex, metcorrRecoilRespDown_ey, covMET, svFitMass_resp_Down, svFitPt_resp_Down);
                    runFastMTT(measuredTauLeptons, metcorrJESUp_ex, metcorrJESUp_ey, covMET, svFitMass_JES_Up, svFitPt_JES_Up);
                    runFastMTT(measuredTauLeptons, metcorrJESDown_ex, metcorrJESDown_ey, covMET, svFitMass_JES_Down, svFitPt_JES_Down);
                    runFastMTT(measuredTauLeptons, metcorrUESUp_ex, metcorrUESUp_ey, covMET, svFitMass_UES_Up, svFitPt_UES_Up);
                    runFastMTT(measuredTauLeptons, metcorrUESDown_ex, metcorrUESDown_ey, covMET, svFitMass_UES_Down, svFitPt_UES_Down);
                    
                TLorentzVector orig_tau1,orig_tau2;
                orig_tau1.SetPtEtaPhiM(pt1, eta1, phi1, mass1;
                orig_tau2.SetPtEtaPhiM(pt2, eta2, phi2, mass2;
                TLorentzVector scaled_tau1_up = orig_tau1;
                TLorentzVector scaled_tau1_dn = orig_tau1;
                scaled_tau_up1 *= 1 + 0.03;
                scaled_tau_dn1 *= 1 - 0.03;
                TLorentzVector scaled_tau2_up = orig_tau2;
                TLorentzVector scaled_tau2_dn = orig_tau2;
                scaled_tau_up2 *= 1 + 0.03;
                scaled_tau_dn2 *= 1 - 0.03;
                    


                std::vector<classic_svFit::MeasuredTauLepton> measuredTauUp{
                    classic_svFit::MeasuredTauLepton(decayType2, scaled_tau1_up.Pt(), scaled_tau1_up.Eta(), scaled_tau1_up.Phi(), mass1, decayMode1),
                    classic_svFit::MeasuredTauLepton(decayType2, scaled_tau2_up.Pt(), scaled_tau2_up.Eta(), scaled_tau2_up.Phi(), mass2, decayMode2)};

                std::vector<classic_svFit::MeasuredTauLepton> measuredTauDn{
                    classic_svFit::MeasuredTauLepton(decayType2, scaled_tau1_dn.Pt(), scaled_tau1_dn.Eta(), scaled_tau1_dn.Phi(), mass1, decayMode1),
                    classic_svFit::MeasuredTauLepton(decayType2, scaled_tau2_dn.Pt(), scaled_tau2_dn.Eta(), scaled_tau2_dn.Phi(), mass2, decayMode2)};
                    

                runFastMTT(measuredTauUp, metcorr_ex, metcorr_ey, covMET, svFitMass_TES_Up, svFitPt_TES_Up);
                runFastMTT(measuredTauDn, metcorr_ex, metcorr_ey, covMET, svFitMass_TES_Down, svFitPt_TES_Down);


}



                }
                else if (channel == "em" || channel == "me" ) {
                    std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptons{
                        
                        classic_svFit::MeasuredTauLepton(decayType1, pt1, eta1, phi1, mass1),
                        classic_svFit::MeasuredTauLepton(decayType2, pt2, eta2, phi2, mass2)};
                    
                    runFastMTT(measuredTauLeptons, metcorr_ex, metcorr_ey, covMET, svFitMass, svFitPt);
                    if (!isData){
                    
                    //                    runFastMTT(measuredTauLeptons, metcorrRecoilResoUp_ex, metcorrRecoilResoUp_ey, covMET, svFitMass_reso_Up, svFitPt_reso_Up);
                    //                    runFastMTT(measuredTauLeptons, metcorrRecoilResoDown_ex, metcorrRecoilResoDown_ey, covMET, svFitMass_reso_Down, svFitPt_reso_Down);
                    //                    runFastMTT(measuredTauLeptons, metcorrRecoilRespUp_ex, metcorrRecoilRespUp_ey, covMET, svFitMass_resp_Up, svFitPt_resp_Up);
                    //                    runFastMTT(measuredTauLeptons, metcorrRecoilRespDown_ex, metcorrRecoilRespDown_ey, covMET, svFitMass_resp_Down, svFitPt_resp_Down);
                    runFastMTT(measuredTauLeptons, metcorrJESUp_ex, metcorrJESUp_ey, covMET, svFitMass_JES_Up, svFitPt_JES_Up);
                    runFastMTT(measuredTauLeptons, metcorrJESDown_ex, metcorrJESDown_ey, covMET, svFitMass_JES_Down, svFitPt_JES_Down);
                    runFastMTT(measuredTauLeptons, metcorrUESUp_ex, metcorrUESUp_ey, covMET, svFitMass_UES_Up, svFitPt_UES_Up);
                    runFastMTT(measuredTauLeptons, metcorrUESDown_ex, metcorrUESDown_ey, covMET, svFitMass_UES_Down, svFitPt_UES_Down);
                    }
                    
                }
                else if (channel == "mt" || channel == "et" ) {
                    mass2 = m2;
                    std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptons{
                        classic_svFit::MeasuredTauLepton(decayType1, pt1, eta1, phi1, mass1),
                        classic_svFit::MeasuredTauLepton(decayType2, pt2, eta2, phi2, mass2, decayMode2)};
                    
                    runFastMTT(measuredTauLeptons, metcorr_ex, metcorr_ey, covMET, svFitMass, svFitPt);
                    if (!isData){
                    //                    runFastMTT(measuredTauLeptons, metcorrRecoilResoUp_ex, metcorrRecoilResoUp_ey, covMET, svFitMass_reso_Up, svFitPt_reso_Up);
                    //                    runFastMTT(measuredTauLeptons, metcorrRecoilResoDown_ex, metcorrRecoilResoDown_ey, covMET, svFitMass_reso_Down, svFitPt_reso_Down);
                    //                    runFastMTT(measuredTauLeptons, metcorrRecoilRespUp_ex, metcorrRecoilRespUp_ey, covMET, svFitMass_resp_Up, svFitPt_resp_Up);
                    //                    runFastMTT(measuredTauLeptons, metcorrRecoilRespDown_ex, metcorrRecoilRespDown_ey, covMET, svFitMass_resp_Down, svFitPt_resp_Down);
                    runFastMTT(measuredTauLeptons, metcorrJESUp_ex, metcorrJESUp_ey, covMET, svFitMass_JES_Up, svFitPt_JES_Up);
                    runFastMTT(measuredTauLeptons, metcorrJESDown_ex, metcorrJESDown_ey, covMET, svFitMass_JES_Down, svFitPt_JES_Down);
                    runFastMTT(measuredTauLeptons, metcorrUESUp_ex, metcorrUESUp_ey, covMET, svFitMass_UES_Up, svFitPt_UES_Up);
                    runFastMTT(measuredTauLeptons, metcorrUESDown_ex, metcorrUESDown_ey, covMET, svFitMass_UES_Down, svFitPt_UES_Down);
                    
                    
                    
                TLorentzVector orig_tau;
                orig_tau.SetPtEtaPhiM(pt2, eta2, phi2, mass2;
                TLorentzVector scaled_tau_up = orig_tau;
                TLorentzVector scaled_tau_dn = orig_tau;
                scaled_tau_up *= 1 + 0.03;
                scaled_tau_dn *= 1 - 0.03;
                    


                std::vector<classic_svFit::MeasuredTauLepton> measuredTauUp{
                    classic_svFit::MeasuredTauLepton(decayType1, pt1, eta1, phi1, mass1),
                    classic_svFit::MeasuredTauLepton(decayType2, scaled_tau_up.Pt(), scaled_tau_up.Eta(), scaled_tau_up.Phi(), mass2, decayMode2)};

                std::vector<classic_svFit::MeasuredTauLepton> measuredTauDn{
                    classic_svFit::MeasuredTauLepton(decayType1, pt1, eta1, phi1, mass1),
                    classic_svFit::MeasuredTauLepton(decayType2, scaled_tau_dn.Pt(), scaled_tau_dn.Eta(), scaled_tau_dn.Phi(), mass2, decayMode2)};
                    

                runFastMTT(measuredTauUp, metcorr_ex, metcorr_ey, covMET, svFitMass_TES_Up, svFitPt_TES_Up);
                runFastMTT(measuredTauDn, metcorr_ex, metcorr_ey, covMET, svFitMass_TES_Down, svFitPt_TES_Down);


}
                    
                    
                    
                    
                    
                    //                    if (doES) {
                    //                        // corrections only need to be done once
                    //                        float ES_Up(1.), ES_Down(1.);  // shift TES
                    //                        if (gen_match_2 == 5) {        // 0.6% uncertainty on hadronic tau
                    //                            ES_Up = 1 + tesUncertainties(era, decayMode2);
                    //                            ES_Down = 1 - tesUncertainties(era, decayMode2);
                    //                        } else if (gen_match_2 < 5) {  // flat 2% on el/mu -> tau energy scale systematics
                    //                            ES_Up = 1.02;
                    //                            ES_Down = 0.98;
                    //                        }
                    
                    //                        if (channel == "et") {
                    //                            TLorentzVector orig_el;
                    //                            orig_el.SetPtEtaPhiM(pt1, eta1, phi1, mass1);
                    //                            TLorentzVector scale_up = orig_el * (eEnergyScaleUp / eCorrectedEt);
                    //                            TLorentzVector scale_dn = orig_el * (eEnergyScaleDown / eCorrectedEt);
                    //                            TLorentzVector sigma_up = orig_el * (eEnergySigmaUp / eCorrectedEt);
                    //                            TLorentzVector sigma_dn = orig_el * (eEnergySigmaDown / eCorrectedEt);
                    //
                    //                            std::vector<classic_svFit::MeasuredTauLepton> measuredTauScaleUp{
                    //                                classic_svFit::MeasuredTauLepton(decayType1, scale_up.Pt(), scale_up.Eta(), scale_up.Phi(), scale_up.M()),
                    //                                classic_svFit::MeasuredTauLepton(decayType2, pt2, eta2, phi2, mass2, decayMode2)};
                    //                            runFastMTT(measuredTauScaleUp, metcorr_ex, metcorr_ey, covMET, svFitMass_EEScale_Up, svFitPt_EEScale_Up);
                    //
                    //                            std::vector<classic_svFit::MeasuredTauLepton> measuredTauScaleDn{
                    //                                classic_svFit::MeasuredTauLepton(decayType1, scale_dn.Pt(), scale_dn.Eta(), scale_dn.Phi(), scale_dn.M()),
                    //                                classic_svFit::MeasuredTauLepton(decayType2, pt2, eta2, phi2, mass2, decayMode2)};
                    //                            runFastMTT(measuredTauScaleDn, metcorr_ex, metcorr_ey, covMET, svFitMass_EEScale_Down, svFitPt_EEScale_Down);
                    //
                    //                            std::vector<classic_svFit::MeasuredTauLepton> measuredTauSigmaUp{
                    //                                classic_svFit::MeasuredTauLepton(decayType1, sigma_up.Pt(), sigma_up.Eta(), sigma_up.Phi(), sigma_up.M()),
                    //                                classic_svFit::MeasuredTauLepton(decayType2, pt2, eta2, phi2, mass2, decayMode2)};
                    //                            runFastMTT(measuredTauSigmaUp, metcorr_ex, metcorr_ey, covMET, svFitMass_EESigma_Up, svFitPt_EESigma_Up);
                    //
                    //                            std::vector<classic_svFit::MeasuredTauLepton> measuredTauSigmaDn{
                    //                                classic_svFit::MeasuredTauLepton(decayType1, sigma_dn.Pt(), sigma_dn.Eta(), sigma_dn.Phi(), sigma_dn.M()),
                    //                                classic_svFit::MeasuredTauLepton(decayType2, pt2, eta2, phi2, mass2, decayMode2)};
                    //                            runFastMTT(measuredTauSigmaDn, metcorr_ex, metcorr_ey, covMET, svFitMass_EESigma_Down, svFitPt_EESigma_Down);
                    //                        } else if (channel == "mt") {
                    //                            TLorentzVector orig_mu;
                    //                            orig_mu.SetPtEtaPhiM(pt1, eta1, phi1, mass1);
                    //                            TLorentzVector scaled_mu_up = orig_mu;
                    //                            TLorentzVector scaled_mu_dn = orig_mu;
                    //                            if (orig_mu.Eta() > -2.4 && orig_mu.Eta() < -2.1) {
                    //                                scaled_mu_up *= 1 + 0.027;
                    //                                scaled_mu_dn *= 1 - 0.027;
                    //                            } else if (orig_mu.Eta() > -2.1 && orig_mu.Eta() < -1.2) {
                    //                                scaled_mu_up *= 1 + 0.009;
                    //                                scaled_mu_dn *= 1 - 0.009;
                    //                            } else if (orig_mu.Eta() > -1.2 && orig_mu.Eta() < 1.2) {
                    //                                scaled_mu_up *= 1 + 0.004;
                    //                                scaled_mu_dn *= 1 - 0.004;
                    //                            } else if (orig_mu.Eta() > 1.2 && orig_mu.Eta() < 2.1) {
                    //                                scaled_mu_up *= 1 + 0.009;
                    //                                scaled_mu_dn *= 1 - 0.009;
                    //                            } else if (orig_mu.Eta() > 2.1 && orig_mu.Eta() < 2.4) {
                    //                                scaled_mu_up *= 1 + 0.017;
                    //                                scaled_mu_dn *= 1 - 0.017;
                    //                            }
                    //
                    //                            std::vector<classic_svFit::MeasuredTauLepton> measuredTauUp{
                    //                                classic_svFit::MeasuredTauLepton(decayType1, scaled_mu_up.Pt(), scaled_mu_up.Eta(), scaled_mu_up.Phi(),
                    //                                                                 scaled_mu_up.M()),
                    //                                classic_svFit::MeasuredTauLepton(decayType2, pt2, eta2, phi2, mass2, decayMode2)};
                    //                            std::vector<classic_svFit::MeasuredTauLepton> measuredTauDn{
                    //                                classic_svFit::MeasuredTauLepton(decayType1, scaled_mu_dn.Pt(), scaled_mu_dn.Eta(), scaled_mu_dn.Phi(),
                    //                                                                 scaled_mu_dn.M()),
                    //                                classic_svFit::MeasuredTauLepton(decayType2, pt2, eta2, phi2, mass2, decayMode2)};
                    //
                    //                            runFastMTT(measuredTauUp, metcorr_ex, metcorr_ey, covMET, svFitMass_MES_Up, svFitPt_MES_Up);
                    //                            runFastMTT(measuredTauDn, metcorr_ex, metcorr_ey, covMET, svFitMass_MES_Down, svFitPt_MES_Down);
                    //                        }
                    
                    //                        double pt_Up(pt2 * ES_Up), pt_Down(pt2 * ES_Down);  // shift tau pT by energy scale
                    //                        double dx_Up(pt2 * TMath::Cos(phi2) * ((1. / ES_Up) - 1.)), dy_Up(pt2 * TMath::Sin(phi2) * ((1. / ES_Up) - 1.)),
                    //                            dx_Down(pt2 * TMath::Cos(phi2) * ((1. / ES_Down) - 1.)), dy_Down(pt2 * TMath::Sin(phi2) * ((1. / ES_Down) - 1.));
                    //                        double metcorr_ex_Up(metcorr_ex + dx_Up), metcorr_ey_Up(metcorr_ey + dy_Up), metcorr_ex_Down(metcorr_ex + dx_Down),
                    //                            metcorr_ey_Down(metcorr_ey + dy_Down);
                    
                    //                        // leptons shifted up
                    //                        std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptonsUp{
                    //                            classic_svFit::MeasuredTauLepton(decayType1, pt1, eta1, phi1, mass1),
                    //                            classic_svFit::MeasuredTauLepton(decayType2, pt_Up, eta2, phi2, mass2, decayMode2)};
                    //
                    //                        // leptons shifted down
                    //                        std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptonsDown{
                    //                            classic_svFit::MeasuredTauLepton(decayType1, pt1, eta1, phi1, mass1),
                    //                            classic_svFit::MeasuredTauLepton(decayType2, pt_Down, eta2, phi2, mass2, decayMode2)};
                    
                    /////////////////////////////
                    // All upward shifts below //
                    /////////////////////////////
                    
                    //                        // tau DM0 shifted up
                    //                        if (gen_match_2 == 5 && decayMode2 == 0) {
                    //                            runFastMTT(measuredTauLeptonsUp, metcorr_ex_Up, metcorr_ey_Up, covMET, svFitMass_JES_Up, svFitPt_JES_Up);
                    //
                    //                        } else {
                    //                            svFitMass_JES_Up = svFitMass;
                    //                            svFitPt_JES_Up = svFitPt;
                    //                        }
                    //
                    //                        // tau DM1 shifted up
                    //                        if (gen_match_2 == 5 && decayMode2 == 1) {
                    //                            runFastMTT(measuredTauLeptonsUp, metcorr_ex_Up, metcorr_ey_Up, covMET, svFitMass_UES_Up, svFitPt_UES_Up);
                    //                        } else {
                    //                            svFitMass_UES_Up = svFitMass;
                    //                            svFitPt_UES_Up = svFitPt;
                    //                        }
                    //
                    //                        // tau DM10 shifted up
                    //                        if (gen_match_2 == 5 && decayMode2 == 10) {
                    //                            runFastMTT(measuredTauLeptonsUp, metcorr_ex_Up, metcorr_ey_Up, covMET, svFitMass_reso_Up, svFitPt_reso_Up);
                    //                        } else {
                    //                            svFitMass_reso_Up = svFitMass;
                    //                            svFitPt_reso_Up = svFitPt;
                    //                        }
                    
                    //                        // lep->tau DM0 shifted up
                    //                        if (gen_match_2 < 5 && decayMode2 == 0) {
                    //                            runFastMTT(measuredTauLeptonsUp, metcorr_ex_Up, metcorr_ey_Up, covMET, svFitMass_LES_JES_Up, svFitPt_LES_JES_Up);
                    //
                    //                        } else {
                    //                            svFitMass_LES_JES_Up = svFitMass;
                    //                            svFitPt_LES_JES_Up = svFitPt;
                    //                        }
                    //
                    //                        // lep->tau DM1 shifted up
                    //                        if (gen_match_2 < 5 && decayMode2 == 1) {
                    //                            runFastMTT(measuredTauLeptonsUp, metcorr_ex_Up, metcorr_ey_Up, covMET, svFitMass_LES_UES_Up, svFitPt_LES_UES_Up);
                    //                        } else {
                    //                            svFitMass_LES_UES_Up = svFitMass;
                    //                            svFitPt_LES_UES_Up = svFitPt;
                    //                        }
                    
                    ///////////////////////////////
                    // All downward shifts below //
                    ///////////////////////////////
                    
                    //                        // tau DM0 shifted down
                    //                        if (gen_match_2 == 5 && decayMode2 == 0) {
                    //                            runFastMTT(measuredTauLeptonsDown, metcorr_ex_Down, metcorr_ey_Down, covMET, svFitMass_JES_Down, svFitPt_JES_Down);
                    //                        } else {
                    //                            svFitMass_JES_Down = svFitMass;
                    //                            svFitPt_JES_Down = svFitPt;
                    //                        }
                    //
                    //                        // tau DM1 shifted down
                    //                        if (gen_match_2 == 5 && decayMode2 == 1) {
                    //                            runFastMTT(measuredTauLeptonsDown, metcorr_ex_Down, metcorr_ey_Down, covMET, svFitMass_UES_Down, svFitPt_UES_Down);
                    //                        } else {
                    //                            svFitMass_UES_Down = svFitMass;
                    //                            svFitPt_UES_Down = svFitPt;
                    //                        }
                    //
                    //                        // tau DM10 shifted down
                    //                        if (gen_match_2 == 5 && decayMode2 == 10) {
                    //                            runFastMTT(measuredTauLeptonsDown, metcorr_ex_Down, metcorr_ey_Down, covMET, svFitMass_reso_Down, svFitPt_reso_Down);
                    //                        } else {
                    //                            svFitMass_reso_Down = svFitMass;
                    //                            svFitPt_reso_Down = svFitPt;
                    //                        }
                    //
                    //                        // lep->tau DM0 shifted down
                    //                        if (gen_match_2 < 5 && decayMode2 == 0) {
                    //                            runFastMTT(measuredTauLeptonsDown, metcorr_ex_Down, metcorr_ey_Down, covMET, svFitMass_LES_JES_Down,
                    //                                       svFitPt_LES_JES_Down);
                    //                        } else {
                    //                            svFitMass_LES_JES_Down = svFitMass;
                    //                            svFitPt_LES_JES_Down = svFitPt;
                    //                        }
                    //
                    //                        // lep->tau DM1 shifted down
                    //                        if (gen_match_2 < 5 && decayMode2 == 1) {
                    //                            runFastMTT(measuredTauLeptonsDown, metcorr_ex_Down, metcorr_ey_Down, covMET, svFitMass_LES_UES_Down,
                    //                                       svFitPt_LES_UES_Down);
                    //                        } else {
                    //                            svFitMass_LES_UES_Down = svFitMass;
                    //                            svFitPt_LES_UES_Down = svFitPt;
                    //                        }
                    //                    }  // end doES
                } else {
                    svFitMass = -100;
                    svFitPt = -100;
                }
                
                // fill all output branches
                for (auto& branch : new_branches) {
                    branch->Fill();
                }
            }
            dir->cd();
            t->Write("", TObject::kOverwrite);
            delete t;
        }  // if the iterator of the key is a TTree
    }
}

void runFastMTT(const std::vector<classic_svFit::MeasuredTauLepton> &measuredTauLeptons, double measuredMETx, double measuredMETy,
                const TMatrixD &covMET, float &svFitMass_result, float &svFitPt_result) {
    svfitAlgorithm.run(measuredTauLeptons, measuredMETx, measuredMETy, covMET);
    svFitMass_result = svfitAlgorithm.getBestP4().M();
    svFitPt_result = svfitAlgorithm.getBestP4().Pt();
}

// Thank you Renee Brun :)
void CopyDir(TDirectory *source, optutl::CommandLineParser parser) {
    // copy all objects and subdirs of directory source as a subdir of the current directory
    TDirectory *savdir = gDirectory;
    TDirectory *adir = savdir;
    if (source->GetName() != parser.stringValue("inputFile")) {
        adir = savdir->mkdir(source->GetName());
        std::cout << "Source name is not outputfile name" << std::endl;
        adir->cd();
    } else {
        // adir = savdir->mkdir("input");
        adir->cd();
    }
    
    // loop on all entries of this directory
    TKey *key;
    TIter nextkey(source->GetListOfKeys());
    while ((key = reinterpret_cast<TKey*>(nextkey()))) {
        const char *classname = key->GetClassName();
        TClass *cl = gROOT->GetClass(classname);
        if (!cl) continue;
        if (cl->InheritsFrom(TDirectory::Class())) {
            source->cd(key->GetName());
            TDirectory *subdir = gDirectory;
            adir->cd();
            CopyDir(subdir, parser);
            adir->cd();
        } else if (cl->InheritsFrom(TTree::Class())) {
            TTree *T = reinterpret_cast<TTree*>(source->Get(key->GetName()));
            adir->cd();
            //            TTree *newT = T->CloneTree(-1, "fast");
            TTree *newT = T->CloneTree(-1);
            newT->Write();
        } else {
            source->cd();
            TObject *obj = key->ReadObj();
            adir->cd();
            obj->Write();
            delete obj;
        }
    }
    adir->SaveSelf(kTRUE);
    savdir->cd();
}

int CopyFile(const char *fname, optutl::CommandLineParser parser) {
    // Copy all objects and subdirs of file fname as a subdir of the current directory
    TDirectory *target = gDirectory;
    TFile *f = TFile::Open(fname);
    if (!f || f->IsZombie()) {
        printf("Cannot copy file: %s\n", fname);
        target->cd();
        return 0;
    }
    target->cd();
    CopyDir(f, parser);
    delete f;
    target->cd();
    return 1;
}

int copyFiles(optutl::CommandLineParser parser, TFile *fOld, TFile *fNew) {
    // prepare files to be copied
    if (gSystem->AccessPathName(parser.stringValue("inputFile").c_str())) {
        gSystem->CopyFile("hsimple.root", parser.stringValue("inputFile").c_str());
    }
    fNew->cd();
    if (CopyFile(parser.stringValue("inputFile").c_str(), parser) == 0) return 0;
    fNew->ls();
    fNew->Close();
    return 1;
}

double tesUncertainties(unsigned int year, float decaymode) {
    // https://twiki.cern.ch/twiki/bin/viewauth/CMS/HiggsToTauTauWorkingLegacyRun2#Tau_energy_scale_uncertainty
    double tesSize = -1000;
    if (year == 2016) {
        if (decaymode == 0)
            tesSize = 0.010;
        else if (decaymode == 1)
            tesSize = 0.009;
        else if (decaymode == 10)
            tesSize = 0.011;
    }
    if (year == 2017) {
        if (decaymode == 0)
            tesSize = 0.008;
        else if (decaymode == 1)
            tesSize = 0.008;
        else if (decaymode == 10)
            tesSize = 0.009;
    }
    if (year == 2018) {
        if (decaymode == 0)
            tesSize = 0.011;
        else if (decaymode == 1)
            tesSize = 0.008;
        else if (decaymode == 10)
            tesSize = 0.009;
    }
    
    return tesSize;
}

double pt_shifted(float pt, double tesUnc, bool isDM, int updown) {
    double shifted_pT = pt;
    if (isDM) {
        if (updown > 0)
            shifted_pT = pt * (1.0 + tesUnc);
        else if (updown < 0)
            shifted_pT = pt * (1.0 - tesUnc);
    }
    return shifted_pT;
}

double metcorr_shifted(double metcorr, float pt1, float phi1, bool isDM1, double tesUnc1, float pt2, float phi2, bool isDM2, double tesUnc2, int xory,
                       int updown) {
    double dx1 = 0.0, dx2 = 0.0;
    double shifted_metcorr = metcorr;
    if (isDM1 || isDM2) {
        double tesScale1 = 0.0, tesScale2 = 0.0;
        if (updown > 0) {
            tesScale1 = 1.0 + tesUnc1;
            tesScale2 = 1.0 + tesUnc2;
        } else if (updown < 0) {
            tesScale1 = 1.0 - tesUnc1;
            tesScale2 = 1.0 - tesUnc2;
        }
        if (xory > 0) {
            dx1 = pt1 * TMath::Cos(phi1) * ((1. / tesScale1) - 1.);
            dx2 = pt2 * TMath::Cos(phi2) * ((1. / tesScale2) - 1.);
        } else if (xory < 0) {
            dx1 = pt1 * TMath::Sin(phi1) * ((1. / tesScale1) - 1.);
            dx2 = pt2 * TMath::Sin(phi2) * ((1. / tesScale2) - 1.);
        }
        shifted_metcorr = metcorr + dx1 + dx2;
    }
    return shifted_metcorr;
}
