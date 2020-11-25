//./BoostedHTT2017_pogTau.exe -p ROOTFiles/ -s Zprime_94X_bug_Full -n zprime_bug
#include "../interface/Functions.h"
#include <string>
#include <ostream>
#include <vector>
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooFunctor.h"
#include "RooMsgService.h"
#include "../interface/CLParser.h"
//#include "../interface/LumiReweightingStandAlone.h"


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
    auto InputFile = TFile::Open(fname.c_str());
    std::cout << "Loading Ntuple..." << std::endl;
    TTree *  Run_Tree;
    Run_Tree= Xttree(InputFile,"tautau_tree");
    
    //    auto HistoTot = reinterpret_cast<TH1D*>(InputFile->Get("ggNtuplizer/hEvents"));
    TH1F * HistoTot = (TH1F*) InputFile->Get("hcount");
    auto fout = new TFile(filename.c_str(), "RECREATE");
    
    myMap1 = new std::map<std::string, TH1F*>();
    myMap2 = new map<string, TH2F*>();
    
    TTree * outTr=  new TTree("tautau_tree","tautau_tree");
    
    //###############################################################################################
    // Parameters
    //###############################################################################################
    float MuMass= 0.10565837;
    float eleMass= 0.000511;
    float JetPtCut=30;
    float BJetPtCut=20;
    
    //    float CSVCut=   0.9535   ;                  //  https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation80XReReco
    float CSVCut=   0.8838   ;                  //  medium  https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
    float LeptonIsoCut=0.15;
    bool debug= false;
    //    float luminosity=    35867;
    float luminosity=    41530;
    
    
    float leadPt_=-10;
    float subPt_=-10;
    float vis_mass=-10;
    float LeadJetPt = -10;
    float dR_Z_jet=-10;
    bool PassLead,PassSub,PassLeadCombined,PassSubCombined,PassLeadCharged,PassSubCharged,OS,SS;
    float tmass,ht,st,Met,FullWeight, dR_tau_tau, Metphi,BoostedTauRawIso, higgs_pT, higgs_m, m_sv_, wtnom_zpt_weight;
    
//    outTr->Branch("evtwt",&FullWeight,"evtwt/F");
////    outTr->Branch("evtwtZpt",&wtnom_zpt_weight,"evtwtZPt/F");
//    outTr->Branch("leadPt",&leadPt_,"leadPt/F");
//    outTr->Branch("subPt",&subPt_,"subPt/F");
//    outTr->Branch("PassLead",&PassLead,"PassLead/O");
//    outTr->Branch("PassSub",&PassSub,"PassSub/O");
//    outTr->Branch("PassLeadCombined",&PassLeadCombined,"PassLeadCombined/O");
//    outTr->Branch("PassSubCombined",&PassSubCombined,"PassSubCombined/O");
//    outTr->Branch("PassLeadCharged",&PassLeadCharged,"PassLeadCharged/O");
//    outTr->Branch("PassSubCharged",&PassSubCharged,"PassSubCharged/O");
//    outTr->Branch("OS",&OS,"OS/O");
//    outTr->Branch("SS",&SS,"SS/O");
//    outTr->Branch("vis_mass",&vis_mass,"vis_mass/F");
//    outTr->Branch("tmass",&tmass,"tmass/F");
//    outTr->Branch("ht",&ht,"ht/F");
//    outTr->Branch("st",&st,"st/F");
//    outTr->Branch("Met",&Met,"Met/F");
//    outTr->Branch("LeadJetPt",&LeadJetPt,"LeadJetPt/F");
//    outTr->Branch("dR_tau_tau",&dR_tau_tau,"dR_tau_tau/F");
////    outTr->Branch("IsoLepValue",&IsoLepValue,"IsoLepValue/F");
//    outTr->Branch("BoostedTauRawIso",&BoostedTauRawIso,"BoostedTauRawIso/F");
//    outTr->Branch("higgs_pT",&higgs_pT,"higgs_pT/F");
//    outTr->Branch("higgs_m",&higgs_m,"higgs_m/F");
//    outTr->Branch("m_sv",&m_sv_,"m_sv/F");
    
    
    Int_t nentries_wtn = (Int_t) Run_Tree->GetEntries();
    cout<<"nentries_wtn===="<<nentries_wtn<<"\n";
    for (Int_t i = 0; i < nentries_wtn; i++) {
        
        Run_Tree->GetEntry(i);
        if (i % 1000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);
        
        
        TLorentzVector LeadTau4Momentum,SubTau4Momentum, Z4Momentum, Met4Momentum;
        //=========================================================================================================
        // Lead tau selection
        int idx_leadtau= leadtauIndex;
                
        if (boostedTauPt->at(idx_leadtau) <= 40 || fabs(boostedTauEta->at(idx_leadtau)) >= 2.3 ) continue;
//        if (boostedTaupfTausDiscriminationByDecayModeFinding->at(idx_leadtau) < 0.5 ) continue;
//        if (boostedTauByMVA6LooseElectronRejection->at(idx_leadtau) < 0.5) continue;
//        if (boostedTauByLooseMuonRejection3->at(idx_leadtau) < 0.5) continue;
    LeadTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(idx_leadtau),boostedTauEta->at(idx_leadtau),boostedTauPhi->at(idx_leadtau),boostedTauMass->at(idx_leadtau));
        plotFill("cutFlowTable",3 ,15,0,15);
        
//        TLorentzVector leadMatch= getMatchedGenTau(LeadTau4Momentum);
//        plotFill("GenMatchedLeadTau",leadMatch.DeltaR(LeadTau4Momentum) ,20,0,1);
//        vector<float> leadRecoMatch= getMatchedRecoTau(LeadTau4Momentum);

        //=========================================================================================================
        // sublead Tau selection
        int idx_subleadtau= subtauIndex;
        
        if (boostedTauPt->at(idx_subleadtau) <= 40 || fabs(boostedTauEta->at(idx_subleadtau)) >= 2.3 ) continue;
//        if (boostedTaupfTausDiscriminationByDecayModeFinding->at(idx_subleadtau) < 0.5 ) continue;
//        if (boostedTauByMVA6LooseElectronRejection->at(idx_subleadtau) < 0.5) continue;
//        if (boostedTauByLooseMuonRejection3->at(idx_subleadtau) < 0.5) continue;
        
    SubTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(idx_subleadtau),boostedTauEta->at(idx_subleadtau),boostedTauPhi->at(idx_subleadtau),boostedTauMass->at(idx_subleadtau));
        plotFill("cutFlowTable",4 ,15,0,15);
        
//        TLorentzVector subMatch= getMatchedGenTau(SubTau4Momentum);
//        plotFill("GenMatchedSubTau",subMatch.DeltaR(SubTau4Momentum) ,20,0,1);
//        vector<float> subRecoMatch= getMatchedRecoTau(SubTau4Momentum);


        plotFill("chargedIsoPtSum",boostedTauChargedIsoPtSum->at(idx_leadtau),500,0,500);
        plotFill("chargedIsoPtSumNoOverLap",boostedTauChargedIsoPtSumNoOverLap->at(idx_leadtau),500,0,500);

        plotFill("NeutralIsoPtSum",boostedTauNeutralIsoPtSum->at(idx_leadtau),500,0,500);
        plotFill("NeutralIsoPtSumNoOverLap",boostedTauNeutralIsoPtSumNoOverLap->at(idx_leadtau),500,0,500);

        plotFill("NeutralIsoPtSum",boostedTauNeutralIsoPtSum->at(idx_leadtau),500,0,500);
        plotFill("NeutralIsoPtSumNoOverLap",boostedTauNeutralIsoPtSumNoOverLap->at(idx_leadtau),500,0,500);
        
        
        plotFill("boostedTauNumIsolationPFChargedHadrCands"  ,boostedTauNumIsolationPFChargedHadrCands->at(idx_leadtau),30,0,30);
        plotFill("boostedTauNumIsolationPFNeutrHadrCands"  ,boostedTauNumIsolationPFNeutrHadrCands->at(idx_leadtau),30,0,30);
        plotFill("boostedTauNumIsolationPFGammaCands"  ,boostedTauNumIsolationPFGammaCands->at(idx_leadtau),30,0,30);
        plotFill("boostedTauNumIsolationPFCands"  ,boostedTauNumIsolationPFCands->at(idx_leadtau),30,0,30);
        
        plotFill("boostedTauNumIsolationPFChargedHadrCandsOrig"  ,boostedTauNumIsolationPFChargedHadrCandsOrig->at(idx_leadtau),30,0,30);
        plotFill("boostedTauNumIsolationPFNeutrHadrCandsOrig"  ,boostedTauNumIsolationPFNeutrHadrCandsOrig->at(idx_leadtau),30,0,30);
        plotFill("boostedTauNumIsolationPFGammaCandsOrig"  ,boostedTauNumIsolationPFGammaCandsOrig->at(idx_leadtau),30,0,30);
        plotFill("boostedTauNumIsolationPFCandsOrig"  ,boostedTauNumIsolationPFCandsOrig->at(idx_leadtau),30,0,30);
        
        
        
        plotFill("boostedTauByIsolationMVArun2v1DBoldDMwLTraw_lead",boostedTauByIsolationMVArun2v1DBoldDMwLTraw->at(idx_leadtau),20,-1,1);
        plotFill("boostedTauByIsolationMVArun2v1DBoldDMwLTraw_sublead",boostedTauByIsolationMVArun2v1DBoldDMwLTraw->at(idx_subleadtau),20,-1,1);
        
        plotFill("boostedTauByLooseIsolationMVArun2v1DBoldDMwLT_lead",boostedTauByLooseIsolationMVArun2v1DBoldDMwLT->at(idx_leadtau),2,0,1);
        plotFill("boostedTauByLooseIsolationMVArun2v1DBoldDMwLT_sublead",boostedTauByLooseIsolationMVArun2v1DBoldDMwLT->at(idx_subleadtau),2,0,1);

        plotFill("boostedTauByIsolationMVArun2v1DBoldDMwLTraw_leadNoOverLap",boostedTauByIsolationMVArun2v1DBoldDMwLTrawNoOverLap->at(idx_leadtau),20,-1,1);
        plotFill("boostedTauByIsolationMVArun2v1DBoldDMwLTraw_subleadNoOverLap",boostedTauByIsolationMVArun2v1DBoldDMwLTrawNoOverLap->at(idx_subleadtau),20,-1,1);
        
        plotFill("boostedTauByLooseIsolationMVArun2v1DBoldDMwLT_leadNoOverLap",boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNoOverLap->at(idx_leadtau),2,0,1);
        plotFill("boostedTauByLooseIsolationMVArun2v1DBoldDMwLT_subleadNoOverLap",boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNoOverLap->at(idx_subleadtau),2,0,1);


        dR_tau_tau= SubTau4Momentum.DeltaR(LeadTau4Momentum);
        
        //=========================================================================================================
        //  Efficiency plot
        //=========================================================================================================
        bool passNumerator= false;
        bool passDeNumerator= false;
        bool passNumeratorNoOverLap= false;
        float HiggsPt= GetHiggsPt();
//        cout<<"HiggsPt  "<<HiggsPt<<"\n";

        TLorentzVector leadMatch= getMatchedGenTau(LeadTau4Momentum);
        plotFill("GenMatchedLeadTau",leadMatch.DeltaR(LeadTau4Momentum) ,100,0,10);

        TLorentzVector subMatch= getMatchedGenTau(SubTau4Momentum);
        plotFill("GenMatchedSubTau",subMatch.DeltaR(SubTau4Momentum) ,100,0,10);


        if (leadMatch.DeltaR(LeadTau4Momentum)<0.1 and  subMatch.DeltaR(SubTau4Momentum)<0.1)
            passDeNumerator= true;

        if (passDeNumerator and boostedTauByLooseIsolationMVArun2v1DBoldDMwLT->at(idx_leadtau) and boostedTauByLooseIsolationMVArun2v1DBoldDMwLT->at(idx_subleadtau)){
            passNumerator= true;
            }

        if (passDeNumerator and boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNoOverLap->at(idx_leadtau) and boostedTauByLooseIsolationMVArun2v1DBoldDMwLTNoOverLap->at(idx_subleadtau)){
            passNumeratorNoOverLap= true;
            }

        if (passNumerator) plotFill("HiggsPt_num",HiggsPt,40,0,2000);
        if (passNumeratorNoOverLap) plotFill("HiggsPt_numNoOverLap",HiggsPt,40,0,2000);
        if (passDeNumerator) plotFill("HiggsPt_denum",HiggsPt,40,0,2000);
        
        if (passNumerator) plotFill("dR_tau_tau_num",dR_tau_tau,30,0,1.5);
        if (passNumeratorNoOverLap) plotFill("dR_tau_tau_numNoOverLap",dR_tau_tau,30,0,1.5);
        if (passDeNumerator) plotFill("dR_tau_tau_denum",dR_tau_tau,30,0,1.5);

        
        
        //=========================================================================================================
        //  Tau POG tests
        //=========================================================================================================
        int numIso=0;
        int numIsoOverLap=0;
        float EnergyIso=0;
        float EnergyIsoOverLap=0;
        //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        // What we mean here by PFCandidates we mean ChargedPFCandidates
        //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        
        //=========== All Isolation PFChargedCandidates of leading tau with signal and isolation PFCandidates of subleading tau ==========
        for (int i=0; i< boostedTauIsolationPFCands->at(idx_leadtau).size(); i++){
            numIso++;
            EnergyIso +=boostedTauIsolationPFCands->at(idx_leadtau)[i];
            
            // overlap with subleading SignalPFCandidates
            for (int j=0; j< boostedTauSignalPFCands->at(idx_subleadtau).size(); j++){
                if (boostedTauIsolationPFCands->at(idx_leadtau)[i] ==  boostedTauSignalPFCands->at(idx_subleadtau)[j]) {
                    numIsoOverLap++;
                    EnergyIsoOverLap +=boostedTauIsolationPFCands->at(idx_leadtau)[i];
                }
            }
//            // overlap with subleading IsoPFCandidates  NO NEED ISO ISO
//            for (int j=0; j< boostedTauIsolationPFCands->at(idx_subleadtau).size(); j++){
//                if (boostedTauIsolationPFCands->at(idx_leadtau)[i] ==  boostedTauIsolationPFCands->at(idx_subleadtau)[j]) {
//                    numIsoOverLap++;
//                    EnergyIsoOverLap +=boostedTauIsolationPFCands->at(idx_leadtau)[i];
//                }
//            }
        }
        
        //=========== All Isolation PFGammaCandidates of leading tau with signal and isolation PFGammaCandidates of subleading tau ==========
        for (int i=0; i< boostedTauIsolationPFGammaCands->at(idx_leadtau).size(); i++){
            numIso++;
            EnergyIso +=boostedTauIsolationPFGammaCands->at(idx_leadtau)[i];
            // overlap with subleading SignalPFCandidates
            for (int j=0; j< boostedTauSignalPFGammaCands->at(idx_subleadtau).size(); j++){
                if (boostedTauIsolationPFGammaCands->at(idx_leadtau)[i] == boostedTauSignalPFGammaCands->at(idx_subleadtau)[j]) {
                    numIsoOverLap++;
                    EnergyIsoOverLap +=boostedTauIsolationPFGammaCands->at(idx_leadtau)[i];
                }
            }
//            // overlap with subleading IsoPFCandidates  NO NEED ISO ISO
//            for (int j=0; j< boostedTauIsolationPFGammaCands->at(idx_subleadtau).size(); j++){
//                if (boostedTauIsolationPFGammaCands->at(idx_leadtau)[i] == boostedTauIsolationPFGammaCands->at(idx_subleadtau)[j]) {
//                    numIsoOverLap++;
//                    EnergyIsoOverLap +=boostedTauIsolationPFGammaCands->at(idx_leadtau)[i];
//                }
//            }
        }

        
        int NumSubLeadSigGamma(0),NumSubLeadSigCharged(0),NumSubLeadSigGammaOverLap(0),NumSubLeadSigChargedOverLap(0);
        float EnergySubLeadSigGamma(0),EnergySubLeadSigGammaOverLap(0),EnergySubLeadSigCharged(0),EnergySubLeadSigChargedOverLap(0);
        
        
        //=========== All signal PFCandidates of subleading tau with isolation PFCandidates of leading tau ==========
        for (vector<float>::iterator it=boostedTauSignalPFCands->at(idx_subleadtau).begin(); it != boostedTauSignalPFCands->at(idx_subleadtau).end(); it++){
            NumSubLeadSigCharged++;
            EnergySubLeadSigCharged +=*it;
            for (vector<float>::iterator itLead=boostedTauIsolationPFCands->at(idx_leadtau).begin(); itLead != boostedTauIsolationPFCands->at(idx_leadtau).end(); itLead++){
                if (*it==*itLead){
                    NumSubLeadSigChargedOverLap++;
                    EnergySubLeadSigChargedOverLap +=*it;
                }
            }
        }
        
        //=========== All signal PFGammaCandidates of subleading tau with isolation PFGammaCandidates of leading tau ==========
        for (int i=0; i< boostedTauSignalPFGammaCands->at(idx_subleadtau).size(); i++){
            NumSubLeadSigGamma++;
            EnergySubLeadSigGamma +=boostedTauSignalPFGammaCands->at(idx_subleadtau)[i];
            // overlap with leading IsoPFGammaCandidates
            for (int j=0; j< boostedTauIsolationPFGammaCands->at(idx_leadtau).size(); j++){
                if (boostedTauSignalPFGammaCands->at(idx_subleadtau)[i] == boostedTauIsolationPFGammaCands->at(idx_leadtau)[j]) {
                    NumSubLeadSigGammaOverLap++;
                    EnergySubLeadSigGammaOverLap +=boostedTauSignalPFGammaCands->at(idx_subleadtau)[i];
                }
            }
        }
        


        plotFill("dR_ratio_num_Gamma",dR_tau_tau,NumSubLeadSigGammaOverLap*1.0/NumSubLeadSigGamma,15,0,1.5,11,-0.05,1.05);
        plotFill("dR_ratio_energy_Gammas",dR_tau_tau,EnergySubLeadSigGammaOverLap*1.0/EnergySubLeadSigGamma,15,0,1.5,11,-0.05,1.05);
        
        plotFill("dR_ratio_num_Charged",dR_tau_tau,NumSubLeadSigChargedOverLap*1.0/NumSubLeadSigCharged,15,0,1.5,11,-0.05,1.05);
        plotFill("dR_ratio_energy_Charged",dR_tau_tau,EnergySubLeadSigChargedOverLap*1.0/EnergySubLeadSigCharged,15,0,1.5,11,-0.05,1.05);
        
    plotFill("dR_ratio_num_Tot",dR_tau_tau,(NumSubLeadSigChargedOverLap+NumSubLeadSigGammaOverLap)*1.0/(NumSubLeadSigCharged+NumSubLeadSigGamma),15,0,1.5,11,-0.05,1.05);
    plotFill("dR_ratio_energy_Tot",dR_tau_tau,(EnergySubLeadSigChargedOverLap+EnergySubLeadSigGammaOverLap)*1.0/(EnergySubLeadSigCharged+EnergySubLeadSigGamma),15,0,1.5,11,-0.05,1.05);


                
                
                
//                NumSubLeadSigGamma++;
//                EnergySubLeadSigGamma +=boostedTauSignalPFGammaCands->at(idx_subleadtau)[i];
//                // overlap with leading IsoPFGammaCandidates
//                for (int j=0; j< boostedTauIsolationPFGammaCands->at(idx_leadtau).size(); j++){
//                    if (boostedTauSignalPFGammaCands->at(idx_subleadtau)[i] == boostedTauIsolationPFGammaCands->at(idx_subleadtau)[j]) {
//                        NumSubLeadSigGammaOverLap++;
//                        EnergySubLeadSigGammaOverLap +=boostedTauSignalPFGammaCands->at(idx_subleadtau)[i];
//                    }
//                }
                
//
//            for (int i=0; i< boostedTauSignalPFGammaCands->at(idx_subleadtau).size(); i++){
//                NumSubLeadSigGamma++;
//                EnergySubLeadSigGamma +=boostedTauSignalPFGammaCands->at(idx_subleadtau)[i];
//                // overlap with leading IsoPFGammaCandidates
//                for (int j=0; j< boostedTauIsolationPFGammaCands->at(idx_leadtau).size(); j++){
//                    if (boostedTauSignalPFGammaCands->at(idx_subleadtau)[i] == boostedTauIsolationPFGammaCands->at(idx_subleadtau)[j]) {
//                        NumSubLeadSigGammaOverLap++;
//                        EnergySubLeadSigGammaOverLap +=boostedTauSignalPFGammaCands->at(idx_subleadtau)[i];
//                    }
//                }
//
            
            
//
//
//            // overlap with subleading IsoPFCandidates
//            for (int j=0; j< boostedTauIsolationPFGammaCands->at(idx_subleadtau).size(); j++){
//                if (boostedTauIsolationPFGammaCands->at(idx_leadtau)[i] == boostedTauIsolationPFGammaCands->at(idx_subleadtau)[j]) {
//                    numIsoOverLap++;
//                    EnergyIsoOverLap +=boostedTauIsolationPFGammaCands->at(idx_leadtau)[i];
//                }
//            }
//        }

        
        
        
                
//
//        if (dR_tau_tau > 1.2 and dR_tau_tau < 1.3 and NumSubLeadSigChargedOverLap !=0){
//        cout <<"\n\n **** dR_tau_tau = "<<dR_tau_tau<<"\n\n\n\n";
//        cout <<"\t leading Tau pt is "<<boostedTauPt->at(idx_leadtau)<<"\n";
//        for (int i=0; i< boostedTauSignalPFCands->at(idx_leadtau).size(); i++)
//            cout<<"boostedTauSignalPFCands->at(idx_leadtau)["<<i<<"] " <<boostedTauSignalPFCands->at(idx_leadtau)[i]<<"\n";
//        for (int i=0; i< boostedTauSignalPFGammaCands->at(idx_leadtau).size(); i++)
//            cout<<"boostedTauSignalPFGammaCands->at(idx_leadtau)["<<i<<"] " <<boostedTauSignalPFGammaCands->at(idx_leadtau)[i]<<"\n";
//        for (int i=0; i< boostedTauIsolationPFCands->at(idx_leadtau).size(); i++)
//            cout<<"boostedTauIsolationPFCands->at(idx_leadtau)["<<i<<"] " <<boostedTauIsolationPFCands->at(idx_leadtau)[i]<<"\n";
//        for (int i=0; i< boostedTauIsolationPFGammaCands->at(idx_leadtau).size(); i++)
//            cout<<"boostedTauIsolationPFGammaCands->at(idx_leadtau)["<<i<<"] " <<boostedTauIsolationPFGammaCands->at(idx_leadtau)[i]<<"\n";
//
//        cout <<"\t Subleading Tau pt is "<<boostedTauPt->at(idx_subleadtau)<<"\n";
//        for (int i=0; i< boostedTauSignalPFCands->at(idx_subleadtau).size(); i++)
//            cout<<"boostedTauSignalPFCands->at(idx_subleadtau)["<<i<<"] " <<boostedTauSignalPFCands->at(idx_subleadtau)[i]<<"\n";
//        for (int i=0; i< boostedTauSignalPFGammaCands->at(idx_subleadtau).size(); i++)
//            cout<<"boostedTauSignalPFGammaCands->at(idx_subleadtau)["<<i<<"] " <<boostedTauSignalPFGammaCands->at(idx_subleadtau)[i]<<"\n";
//        for (int i=0; i< boostedTauIsolationPFCands->at(idx_subleadtau).size(); i++)
//            cout<<"boostedTauIsolationPFCands->at(idx_subleadtau)["<<i<<"] " <<boostedTauIsolationPFCands->at(idx_subleadtau)[i]<<"\n";
//        for (int i=0; i< boostedTauIsolationPFGammaCands->at(idx_subleadtau).size(); i++)
//            cout<<"boostedTauIsolationPFGammaCands->at(idx_subleadtau)["<<i<<"] " <<boostedTauIsolationPFGammaCands->at(idx_subleadtau)[i]<<"\n";
//}
        
        plotFill("dR_ratio_multiplicity",dR_tau_tau,numIsoOverLap*1.0/numIso,15,0,1.5,11,-0.05,1.05);
        plotFill("dR_ratio_energy",dR_tau_tau,EnergyIsoOverLap*1.0/EnergyIso,15,0,1.5,11,-0.05,1.05);




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
