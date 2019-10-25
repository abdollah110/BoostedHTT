////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  This code is to pre-select the events. This ise used as a base for background estimation, ...
// To run this code one first needs to compile it:
//1) ./Mask.sh   CodexAnalyzer_Preselection.cc
//2)  ./CodexAnalyzer_Preselection.exe  output.root   input.root
// To run this on all data and MC samples run the following:
// source RunFullSamples_PreSelection.sh
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../interface/Functions.h"
#include <string>
#include <ostream>
#include <vector>


int main(int argc, char** argv) {
    using namespace std;
    
    std::string out = *(argv + 1);
    
    cout << "\n\n\n OUTPUT NAME IS:    " << out << endl;     //PRINTING THE OUTPUT name
    TFile *fout = TFile::Open(out.c_str(), "RECREATE");
    
    myMap1 = new std::map<std::string, TH1F*>();
    myMap2 = new map<string, TH2F*>();
    
    std::vector<string> input;
    for (int f = 2; f < argc; f++) {
        input.push_back(*(argv + f));
        cout <<"INPUT NAME IS:   " << input[f - 2] << "\n";
    }
    
    
    
    //########################################
    // Muon Id, Iso, Trigger and Tracker Eff files
    //########################################
    TH2F** HistoMuId=FuncHistMuId();
    TH2F** HistoMuIso=FuncHistMuIso();
//    TH1F** HistoMuTrg=FuncHistMuTrigger();
    TH2F** HistoMuTrg=FuncHistMuTrigger();
    TGraphAsymmErrors * HistoMuTrack=FuncHistMuTrack();
    
    //########################################
    // Electron MVA IdIso files
    //########################################
//    TH2F * HistoEleMVAIdIso90= FuncHistEleMVAId("Tot");
//    TH2F * HistoEleMVAIdIso90_EffMC= FuncHistEleMVAId("MC");
//    TH2F * HistoEleMVAIdIso90_EffData= FuncHistEleMVAId("Data");
    
    // Tight WP of MVA Ele
    float getCorrFactorMVA80WPElectron94X(bool isData, float pt, float eta,    TH2F * HistoEleSF , TGraphAsymmErrors ** Ele25Trg){
        if (isData)
            return 1;
        else
            return Cor94X_IDIso_Ele(pt,eta,HistoEleSF)*Cor94X_Trg_Ele25(pt,eta,Ele25Trg);
    }
    
    
    //########################################
    // Btagging scale factor and uncertainties
    //########################################
    TH2F ** Btagg_TT=FuncHistBTagSF();
    
    
    
    //###############################################################################################
    //  Fix Parameters
    //###############################################################################################
    float MuMass= 0.10565837;
    float eleMass= 0.000511;
    float LeptonPtCut_=60;
    float TauPtCut_=20;
    float JetPtCut=30;
    float BJetPtCut=20;
    
    float ElectronPtCut_=15;
    //    float CSVCut=   0.9535   ;                  //  https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation80XReReco
    float CSVCut=   0.8838   ;                  //  medium  https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
    float LeptonIsoCut=0.20;
    bool debug= false;
    float luminosity=    35867;
    //########################################################################################################################################################
    //########################################################################################################################################################
    //########################################################################################################################################################
    //                                                  Loop over inout ROOT files
    //########################################################################################################################################################
    //########################################################################################################################################################
    //########################################################################################################################################################
    for (int k = 0; k < input.size(); k++) {
        
        TFile *f_Double = TFile::Open(input[k].c_str());
        cout << "\n  Now is running on ------->   " << std::string(f_Double->GetName()) << "\n";
        
        std::string InputROOT= std::string(f_Double->GetName());
        TFile * myFile = TFile::Open(f_Double->GetName());
        TH1F * HistoTot = (TH1F*) myFile->Get("hcount");
        
        TTree *  Run_Tree;
        Run_Tree= Xttree(f_Double);
        
        
        
        //#####################################################################
        //#####################################################################
        //                           Loop over Events in each ROOT files
        //#####################################################################
        //#####################################################################
        Int_t nentries_wtn = (Int_t) Run_Tree->GetEntries();
        cout<<"nentries_wtn===="<<nentries_wtn<<"\n";
        for (Int_t i = 0; i < nentries_wtn; i++) {
            //                    for (Int_t i = 0; i < 10000; i++) {
            Run_Tree->GetEntry(i);
            if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
            fflush(stdout);
            
            bool PassTrigger = ((HLTEleMuX >> 19 & 1)==1); //         else if (name.find("HLT_IsoMu24_v")   != string::npos) bitEleMuX = 19;
            if (! PassTrigger) continue;
            
            
            //###############################################################################################
            //  This part is to avoid of the duplicate of mu-j pair from one events
            //###############################################################################################
            std::vector<string> HistNamesFilled;
            HistNamesFilled.clear();
            if (debug) cout<< "test 0\n";
            //            //###############################################################################################
            //            //  Lumi, GEN & PileUp Weight
            //            //###############################################################################################
            //
            float LumiWeight = 1;
            float GetGenWeight=1;
            float PUWeight = 1;
            
            if (!isData){
                //                //
                //                //                //######################## Lumi Weight
                
                stringstream ss(InputROOT);
                
                string token;
                string M;
                while (getline(ss,token, '/'))  M=token;
                
                std::string FirstPart = "";
                std::string LastPart = ".root";
                std::string newOut = M.substr(FirstPart.size());
                newOut = newOut.substr(0, newOut.size() - LastPart.size());
                
                LumiWeight = luminosity * XSection(newOut)*1.0 / HistoTot->GetBinContent(2);
                //  weightCalc(HistoTot, InputROOT,genHT, W_HTBinROOTFiles, WBosonMass, WMuNu_MassBinROOTFiles,WTauNu_MassBinROOTFiles);
                //                //                //######################## Gen Weight
            }
            for (int qq=0; qq < 60;qq++){
                if ((HLTEleMuX >> qq & 1) == 1)
                    plotFill("_HLT",qq,60,0,60);
            }
            plotFill("cutFlow",1 ,15,0,15);
            int numBJet=numBJets(BJetPtCut,CSVCut);
            if (numBJet > 0) continue;
            plotFill("cutFlow",2 ,15,0,15);
            float ht= getHT(JetPtCut);
            if (ht < 200) continue;
            plotFill("cutFlow",3 ,15,0,15);
            //############################################################################################
            //###########       Loop over MuJet events   #################################################
            //############################################################################################
            float leadingBoostedTauPt=0;
            bool onLeadTau = false;
            
            TLorentzVector Mu4Momentum, Jet4Momentum,KJet4Momentum,BoostTau4Momentum,Mu24Momentum,BoostedTau4Momentum, ZCandida;
            
            if (debug) cout<< "test 1\n";
            
            bool EventPass= false;
            auto numMuTau(0);
            for (int imu = 0; imu < nMu; ++imu){
                if (EventPass) break;
                
                //                plotFill("cutFlow",3 ,15,0,15);
                
                if (muPt->at(imu) <= 30 || fabs(muEta->at(imu)) >= 2.4) continue;
                plotFill("cutFlow",4 ,15,0,15);
                
                Mu4Momentum.SetPtEtaPhiM(muPt->at(imu),muEta->at(imu),muPhi->at(imu),MuMass);
                
                
                float IsoMu=muPFChIso->at(imu)/muPt->at(imu);
                if ( (muPFNeuIso->at(imu) + muPFPhoIso->at(imu) - 0.5* muPFPUIso->at(imu) )  > 0.0)
                    IsoMu= ( muPFChIso->at(imu) + muPFNeuIso->at(imu) + muPFPhoIso->at(imu) - 0.5* muPFPUIso->at(imu))/muPt->at(imu);
                
                bool MuId=( (muIDbit->at(imu) >> 2 & 1)  && fabs(muD0->at(imu)) < 0.045 && fabs(muDz->at(imu)) < 0.2); //Tight Muon Id
                
                
                if (!MuId ) continue;
                plotFill("cutFlow",5 ,15,0,15);
                
                float MuonCor=getCorrFactorMuon94X(isData,  muPt->at(imu), muEta->at(imu) , HistoMuId,HistoMuIso,HistoMuTrg,HistoMuTrack);
//                cout <<"MuonCor= "<<MuonCor<<"\n";
                
                
                float tmass = TMass_F(Mu4Momentum.Pt(), Mu4Momentum.Px(), Mu4Momentum.Py(),  pfMET,  pfMETPhi);
                
                
                
                for (int ibtau = 0; ibtau < nBoostedTau; ++ibtau){
                    if (boostedTauPt->at(ibtau) <= 20 || fabs(boostedTauEta->at(ibtau)) >= 2.3 ) continue;
                    plotFill("cutFlow",8 ,15,0,15);
                    
                    if (debug) cout<< "test 3\n";
                    
                    
                    
                    
                    if (boostedTaupfTausDiscriminationByDecayModeFinding->at(ibtau) < 0.5 ) continue;
                    plotFill("cutFlow",9 ,15,0,15);
                    //                    if (boostedTauByLooseIsolationMVArun2v1DBoldDMwLT->at(ibtau) < 0.5 ) continue;
                    //                    plotFill("cutFlow",10 ,15,0,15);
                    if (boostedTauByMVA6VLooseElectronRejection->at(ibtau) < 0.5) continue;
                    plotFill("cutFlow",11 ,15,0,15);
                    if (boostedTauByTightMuonRejection3->at(ibtau) < 0.5) continue;
                    plotFill("cutFlow",12 ,15,0,15);
                    
                    
                    BoostedTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(ibtau),boostedTauEta->at(ibtau),boostedTauPhi->at(ibtau),boostedTauMass->at(ibtau));
                    
                    if(BoostedTau4Momentum.DeltaR(Mu4Momentum) > 0.8 || BoostedTau4Momentum.DeltaR(Mu4Momentum) < 0.4) continue;
                    
                    
                    ZCandida=BoostedTau4Momentum+Mu4Momentum;
                    
                    
                    plotFill("ZMass",ZCandida.M() ,30,0,300);
                    plotFill("MuonCor",MuonCor ,100,0,2);
                    
                    //###############################################################################################
                    //  BoostedTau Isolation Categorization
                    //###############################################################################################
                    
                    const int size_tauCat = 6;
                    bool Pass = boostedTauByLooseIsolationMVArun2v1DBoldDMwLT->at(ibtau) > 0.5 ;
                    bool Fail = boostedTauByLooseIsolationMVArun2v1DBoldDMwLT->at(ibtau) < 0.5 ;
                    bool PassM = boostedTauByMediumIsolationMVArun2v1DBoldDMwLT->at(ibtau) > 0.5 ;
                    bool FailM = boostedTauByMediumIsolationMVArun2v1DBoldDMwLT->at(ibtau) < 0.5 ;
                    bool PassT = boostedTauByTightIsolationMVArun2v1DBoldDMwLT->at(ibtau) > 0.5 ;
                    bool FailT = boostedTauByTightIsolationMVArun2v1DBoldDMwLT->at(ibtau) < 0.5 ;


                    bool Tau_category[size_tauCat] = {Pass, Fail,PassM, FailM,PassT, FailT};
                    std::string Tau_Cat[size_tauCat] = {"_Pass", "_Fail","_PassM", "_FailM","_PassT", "_FailT"};
                    
                    //###############################################################################################
                    //  lepton Isolation Categorization
                    //###############################################################################################
                    bool LepPassIsolation= IsoMu < LeptonIsoCut;
                    
                    const int size_isoCat = 2;
                    bool Isolation = LepPassIsolation;
                    bool AntiIsolation =  !LepPassIsolation;
                    
                    bool Iso_category[size_isoCat] = {Isolation, AntiIsolation};
                    std::string iso_Cat[size_isoCat] = {"_Iso", "_AntiIso"};
                    
                    
                    
                    //###############################################################################################
                    //  Charge Categorization
                    //###############################################################################################
                    float chargelt= muCharge->at(imu) * boostedTauCharge->at(ibtau);
                    
                    const int size_q = 2;
                    bool q_OS = chargelt < 0;
                    bool q_SS =  chargelt > 0;
                    
                    bool Q_category[size_q] = {q_OS, q_SS};
                    std::string Q_Cat[size_q] = {"_OS", "_SS"};
                    
                    
                    //###############################################################################################
                    
                    for (int tt = 0; tt < size_tauCat; tt++) {
                        if (Tau_category[tt]) {
                            for (int iso = 0; iso < size_isoCat; iso++) {
                                if (Iso_category[iso]) {
                                    for (int iq = 0; iq < size_q; iq++) {
                                        if (Q_category[iq]) {
                                            
                                            
                                            float FullWeight = LumiWeight*MuonCor;
                                            std::string FullStringName = Tau_Cat[tt] +iso_Cat[iso] + Q_Cat[iq] ;
                                            
                                            //                                This check is used to make sure that each event is just filled once for any of the categories ==> No doube-counting of events  (this is specially important for ttbar events where we have many jets and leptons)
                                            if (!( std::find(HistNamesFilled.begin(), HistNamesFilled.end(), FullStringName) != HistNamesFilled.end())){
                                                HistNamesFilled.push_back(FullStringName);
                                                
                                                
                                                
                                                plotFill("ZMass"+FullStringName,ZCandida.M() ,24,0,120,FullWeight);
                                                plotFill("tmass"+FullStringName,tmass ,10,0,50,FullWeight);
                                                plotFill("ht"+FullStringName,ht ,100,0,1000,FullWeight);
                                                plotFill("lepPt"+FullStringName,muPt->at(imu) ,40,0,400,FullWeight);
                                                plotFill("tauPt"+FullStringName,boostedTauPt->at(ibtau) ,40,0,400,FullWeight);
                                                plotFill("MET"+FullStringName,pfMET ,40,0,400,FullWeight);
                                                
                                                
                                                
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    
                    
                }//boostedTau loop
            }//muon loop
            
            
            //###############################################################################################
            //  Doing EleTau Analysis
            //###############################################################################################
        } //End of Tree
    }//End of file
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
