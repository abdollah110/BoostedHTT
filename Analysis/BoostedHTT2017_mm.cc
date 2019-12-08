//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////  This code is to pre-select the events. This ise used as a base for background estimation, ...
//// To run this code one first needs to compile it:
////1) ./Mask.sh   CodexAnalyzer_Preselection.cc
////2)  ./CodexAnalyzer_Preselection.exe  output.root   input.root
//// To run this on all data and MC samples run the following:
//// source RunFullSamples_PreSelection.sh
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#include "../interface/Functions.h"
//#include <string>
//#include <ostream>
//#include <vector>
//
//
//int main(int argc, char** argv) {
//    using namespace std;
//
//    std::string out = *(argv + 1);
//
//    cout << "\n\n\n OUTPUT NAME IS:    " << out << endl;     //PRINTING THE OUTPUT name
//    TFile *fout = TFile::Open(out.c_str(), "RECREATE");
//
//    myMap1 = new std::map<std::string, TH1F*>();
//    myMap2 = new map<string, TH2F*>();
//
//    std::vector<string> input;
//    for (int f = 2; f < argc; f++) {
//        input.push_back(*(argv + f));
//        cout <<"INPUT NAME IS:   " << input[f - 2] << "\n";
//    }
//
//    //###############################################################################################
//    //  Fix Parameters
//    //###############################################################################################
//    float MuMass= 0.10565837;
//    float eleMass= 0.000511;
//    float LeptonPtCut_=60;
//    float TauPtCut_=20;
//    float JetPtCut=30;
//    float BJetPtCut=20;
//
//    float ElectronPtCut_=15;
//    //    float CSVCut=   0.9535   ;                  //  https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation80XReReco
//    float CSVCut=   0.8838   ;                  //  medium  https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
//    float LeptonIsoCut=0.20;
    
//    float luminosity=    33000;
//    //########################################################################################################################################################
//    //########################################################################################################################################################
//    //########################################################################################################################################################
//    //                                                  Loop over inout ROOT files
//    //########################################################################################################################################################
//    //########################################################################################################################################################
//    //########################################################################################################################################################
//    for (int k = 0; k < input.size(); k++) {
//
//        TFile *f_Double = TFile::Open(input[k].c_str());
//        cout << "\n  Now is running on ------->   " << std::string(f_Double->GetName()) << "\n";
//
//        std::string InputROOT= std::string(f_Double->GetName());
//        TFile * myFile = TFile::Open(f_Double->GetName());
//        TH1F * HistoTot = (TH1F*) myFile->Get("hcount");
//
//        TTree *  Run_Tree;
//        Run_Tree= Xttree(f_Double);
//
//
        
        
#include "../interface/Functions.h"
#include <string>
#include <ostream>
#include <vector>
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooFunctor.h"
#include "RooMsgService.h"
#include "../interface/CLParser.h"


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
    auto fin = TFile::Open(fname.c_str());
    std::cout << "Loading Ntuple..." << std::endl;
    TTree *  Run_Tree;
    Run_Tree= Xttree(fin);
    
    //    auto HistoTot = reinterpret_cast<TH1D*>(fin->Get("ggNtuplizer/hEvents"));
    TH1F * HistoTot = (TH1F*) fin->Get("hcount");
    auto fout = new TFile(filename.c_str(), "RECREATE");
    
    myMap1 = new std::map<std::string, TH1F*>();
    myMap2 = new map<string, TH2F*>();
    
    
    // H->tau tau scale factors
    TFile htt_sf_file("data/htt_scalefactors_2017_v2.root");
    RooWorkspace *htt_sf = reinterpret_cast<RooWorkspace*>(htt_sf_file.Get("w"));
    htt_sf_file.Close();
    
    //    // Z-pT reweighting
    //    TFile *zpt_file = new TFile("data/zpt_weights_2016_BtoH.root");
    //    auto zpt_hist = reinterpret_cast<TH2F*>(zpt_file->Get("zptmass_histo"));
    //###############################################################################################
    //  Fix Parameters
    //###############################################################################################
    float MuMass= 0.10565837;
    float eleMass= 0.000511;
    float JetPtCut=30;
    float BJetPtCut=20;
    
    //    float CSVCut=   0.9535   ;                  //  https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation80XReReco
    float CSVCut=   0.8838   ;                  //  medium  https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
    float LeptonIsoCut=0.20;
    bool debug= false;
    //    float luminosity=    35867;
    float luminosity=    41530;
    
    
    Int_t nentries_wtn = (Int_t) Run_Tree->GetEntries();
    cout<<"nentries_wtn===="<<nentries_wtn<<"\n";
    for (Int_t i = 0; i < nentries_wtn; i++) {
        //                    for (Int_t i = 0; i < 10000; i++) {
        
        Run_Tree->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);
        
        // Trigger
        bool PassTrigger = ((HLTEleMuX >> 19 & 1)==1); // else if (name.find("HLT_IsoMu27_v") != string::npos) bitEleMuX = 19; // 2017
        if (! PassTrigger) continue;
        
        //  This part is to avoid of the duplicate of mu-tau pair from one events
        std::vector<string> HistNamesFilled;
        HistNamesFilled.clear();
        
        
        //###############################################################################################
        //  GenInfo
        //###############################################################################################
        vector<float>  genInfo=GeneratorInfo();
        float ZBosonPt=genInfo[2];
        float ZBosonMass=genInfo[4];
        
        // Lumi weight
        float LumiWeight = 1;
        if (!isData){
            LumiWeight = luminosity * XSection(sample)*1.0 / HistoTot->GetBinContent(2);
        }
        
        // Pilu up weights
        float PUWeight = 1;
        
        
        // BJet veto
        int numBJet=numBJets(BJetPtCut,CSVCut);
        if (numBJet > 0) continue;
        
        // HT cut
        float ht= getHT(JetPtCut);
        if (ht < 200) continue;
        
        //electron veto
        int numele =getNumElectron();
        if (numele > 0) continue;
        
        //Leading jet
        TLorentzVector LeadJet= getLeadJet();
        
        
        

            //############################################################################################
            //###########       Loop over MuJet events   #################################################
            //############################################################################################
            float leadingBoostedTauPt=0;
            bool onLeadTau = false;
            
            TLorentzVector Mu4Momentum, Mu4Momentum_sub, ZCandida;
            
            if (debug) cout<< "test 1\n";
            
            bool EventPass= false;
            auto numMuTau(0);
            for (int imu = 0; imu < nMu; ++imu){
                if (EventPass) break;
                
                
                if (muPt->at(imu) <= 30 || fabs(muEta->at(imu)) >= 2.4) continue;
                
                Mu4Momentum.SetPtEtaPhiM(muPt->at(imu),muEta->at(imu),muPhi->at(imu),MuMass);
                                
                float IsoMu=muPFChIso->at(imu)/muPt->at(imu);
                if ( (muPFNeuIso->at(imu) + muPFPhoIso->at(imu) - 0.5* muPFPUIso->at(imu) )  > 0.0)
                    IsoMu= ( muPFChIso->at(imu) + muPFNeuIso->at(imu) + muPFPhoIso->at(imu) - 0.5* muPFPUIso->at(imu))/muPt->at(imu);
                
                bool MuId=( (muIDbit->at(imu) >> 2 & 1)  && fabs(muD0->at(imu)) < 0.045 && fabs(muDz->at(imu)) < 0.2); //Medium Muon Id
                
                
                if (!MuId ) continue;
                if (IsoMu > 0.2 ) continue;
                
                
                
                float MuonCor=1;
                if (!isData){
                    // give inputs to workspace
                    htt_sf->var("m_pt")->setVal(muPt->at(imu));
                    htt_sf->var("m_eta")->setVal(muEta->at(imu));
                    htt_sf->var("z_gen_mass")->setVal(ZBosonMass);
                    htt_sf->var("z_gen_pt")->setVal(ZBosonPt);
                    //                cout<<"\t\t ZBosonMass= "<<ZBosonMass <<"  ZBosonPt "<<ZBosonPt<<"\n";
                    
                    
                    // muon ID SF
                    MuonCor *= htt_sf->function("m_id_kit_ratio")->getVal();
                    // muon Iso SF
                    MuonCor *= htt_sf->function("m_iso_kit_ratio")->getVal();
                    
                    auto single_data_eff = htt_sf->function("m_trg24_27_kit_data")->getVal();
                    auto single_mc_eff = htt_sf->function("m_trg24_27_kit_mc")->getVal();
                    auto single_eff = single_data_eff / single_mc_eff;
                    MuonCor *=single_eff;
                    MuonCor *= htt_sf->function("m_trk_ratio")->getVal();
                    
                    //                if (InputROOT.find("DY") != string::npos) MuonCor *= htt_sf->function("zptmass_weight_nom")->getVal();
                    if (name.find("DY") != string::npos) MuonCor *= htt_sf->function("zptmass_weight_nom")->getVal();
                    
                }
                
                
                
                
                
                
                
                for (int jmu = imu+1; jmu < nMu; ++jmu){
                    if (muPt->at(jmu) <= 10 || fabs(muEta->at(jmu)) >= 2.4) continue;
                    
                    Mu4Momentum_sub.SetPtEtaPhiM(muPt->at(jmu),muEta->at(jmu),muPhi->at(jmu),MuMass);
                    
                    
                    float IsoMu_sub=muPFChIso->at(jmu)/muPt->at(jmu);
                    if ( (muPFNeuIso->at(jmu) + muPFPhoIso->at(jmu) - 0.5* muPFPUIso->at(jmu) )  > 0.0)
                        IsoMu_sub= ( muPFChIso->at(jmu) + muPFNeuIso->at(jmu) + muPFPhoIso->at(jmu) - 0.5* muPFPUIso->at(jmu))/muPt->at(jmu);
                    
                    bool MuId_sub=( (muIDbit->at(jmu) >> 2 & 1)  && fabs(muD0->at(jmu)) < 0.045 && fabs(muDz->at(jmu)) < 0.2); //Tight Muon Id
                    
                    
                    if (!MuId_sub ) continue;
                    if (IsoMu_sub > 0.2 ) continue;
                    
                    
//                    float MuonCor=1;
                    if (!isData){
                        // give inputs to workspace
                        htt_sf->var("m_pt")->setVal(muPt->at(jmu));
                        htt_sf->var("m_eta")->setVal(muEta->at(jmu));

                        // muon ID SF
                        MuonCor *= htt_sf->function("m_id_kit_ratio")->getVal();
                        // muon Iso SF
                        MuonCor *= htt_sf->function("m_iso_kit_ratio")->getVal();
                        //  muon trk
                        MuonCor *= htt_sf->function("m_trk_ratio")->getVal();
                        }
                        
                        plotFill("MuonCor",MuonCor ,100,0,2);
                        

                    if(Mu4Momentum_sub.DeltaR(Mu4Momentum) > 1.0 ) continue;
                    ZCandida=Mu4Momentum_sub+Mu4Momentum;
            
            
                    if (ZCandida.M() < 40) continue;

            
            
            
            //###############################################################################################
            //  Charge Categorization
            //###############################################################################################
            float chargelt= muCharge->at(imu) * muCharge->at(jmu);
            
            const int size_q = 2;
            bool q_OS = chargelt < 0;
            bool q_SS =  chargelt > 0;
            
            bool Q_category[size_q] = {q_OS, q_SS};
            std::string Q_Cat[size_q] = {"_OS", "_SS"};
            
            
            //###############################################################################################
            
                            for (int iq = 0; iq < size_q; iq++) {
                                if (Q_category[iq]) {
                                    
                                    
                                    float FullWeight = LumiWeight;
                                    std::string FullStringName = Q_Cat[iq] ;
                                    
                                    //                                This check is used to make sure that each event is just filled once for any of the categories ==> No doube-counting of events  (this is specially important for ttbar events where we have many jets and leptons)
                                    if (!( std::find(HistNamesFilled.begin(), HistNamesFilled.end(), FullStringName) != HistNamesFilled.end())){
                                        HistNamesFilled.push_back(FullStringName);
                                        
                                        
                                        
                                        plotFill("dR"+FullStringName,Mu4Momentum_sub.DeltaR(Mu4Momentum) ,100,0,1,FullWeight);
                                        plotFill("IsoMu"+FullStringName,IsoMu ,100,0,2,FullWeight);
                                        plotFill("ZMass"+FullStringName,ZCandida.M() ,40,0,200,FullWeight);
                                        plotFill("ht"+FullStringName,ht ,100,0,1000,FullWeight);
                                        
                                        
                                        }
                                    
                }
            }
            
            
        }//boostedTau loop
    }//muon loop
    
    
    //###############################################################################################
    //  Doing EleTau Analysis
    //###############################################################################################
} //End of Tree
//##############  end of dielectron


fout->cd();

map<string, TH1F*>::const_iterator iMap1 = myMap1->begin();
map<string, TH1F*>::const_iterator jMap1 = myMap1->end();

for (; iMap1 != jMap1; ++iMap1)
nplot1(iMap1->first)->Write();

map<string, TH2F*>::const_iterator iMap2 = myMap2->begin();
map<string, TH2F*>::const_iterator jMap2 = myMap2->end();

for (; iMap2 != jMap2; ++iMap2)
nplot2(iMap2->first)->Write();

fout->Close();


}
