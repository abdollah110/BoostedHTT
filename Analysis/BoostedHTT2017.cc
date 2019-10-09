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
    
    //###############################################################################################
    //  Fix Parameters
    //###############################################################################################
    float MuMass= 0.10565837;
    float eleMass= 0.000511;
    float LeptonPtCut_=60;
    float TauPtCut_=20;
    float JetPtCut=500;
    float BJetPtCut=20;
    float SimpleJetPtCut=30;
    float ElectronPtCut_=15;
    //    float CSVCut=   0.9535   ;                  //  https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation80XReReco
    float CSVCut=   0.9693   ;                  //  https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
    float LeptonIsoCut=0.15;
    bool debug= false;
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
            
            
            //###############################################################################################
            //  This part is to avoid of the duplicate of mu-j pair from one events
            //###############################################################################################
            std::vector<string> HistNamesFilled;
            HistNamesFilled.clear();
            
            //            //###############################################################################################
            //            //  Lumi, GEN & PileUp Weight
            //            //###############################################################################################
            //
            float LumiWeight = 1;
            float GetGenWeight=1;
            float PUWeight = 1;
            
            //            if (!isData){
            //                //
            //                //                //######################## Lumi Weight
            //                if (HistoTot) LumiWeight = weightCalc(HistoTot, InputROOT,genHT, W_HTBinROOTFiles, WBosonMass, WMuNu_MassBinROOTFiles,WTauNu_MassBinROOTFiles);
            //                //                //######################## Gen Weight
            //            }
            for (int qq=0; qq < 60;qq++){
                if ((HLTEleMuX >> qq & 1) == 1)
                    plotFill("_HLT",qq,60,0,60);
            }
            
//            int numBJet=numBJets(BJetPtCut,CSVCut);
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
                if (muPt->at(imu) > 30 && fabs(muEta->at(imu)) < 2.4){
                    
                    Mu4Momentum.SetPtEtaPhiM(muPt->at(imu),muEta->at(imu),muPhi->at(imu),MuMass);
                    if (debug) cout<< "test 2\n";
                    float IsoMu=muPFChIso->at(imu)/muPt->at(imu);
                    if ( (muPFNeuIso->at(imu) + muPFPhoIso->at(imu) - 0.5* muPFPUIso->at(imu) )  > 0.0)
                        IsoMu= ( muPFChIso->at(imu) + muPFNeuIso->at(imu) + muPFPhoIso->at(imu) - 0.5* muPFPUIso->at(imu))/muPt->at(imu);
                    //
                    bool MuPtCut = muPt->at(imu) > LeptonPtCut_ && fabs(muEta->at(imu)) < 2.4 ;
                    bool MuId=( (muIDbit->at(imu) >> 2 & 1)  && fabs(muD0->at(imu)) < 0.045 && fabs(muDz->at(imu)) < 0.2); //Tight Muon Id
                    
                    if (!MuId || !IsoMu) continue;
                    
                    
                    float tmass = TMass_F(muPt->at(imu), muPt->at(imu)* cos(muPhi->at(imu)), muPt->at(imu)* sin(muPhi->at(imu)),  pfMET,  pfMETPhi);
                    if (tmass > 40)  continue;
                    
                    
                    
                    for (int ibtau = 0; ibtau < nBoostedTau; ++ibtau){
                        if (boostedTauPt->at(ibtau) > 20 && fabs(boostedTauEta->at(ibtau)) < 2.3 ){
                            if (debug) cout<< "test 3\n";
                                                        
                            if (boostedTaupfTausDiscriminationByDecayModeFinding->at(ibtau)  ) continue;
                            if (boostedTauByMVA6VLooseElectronRejection->at(ibtau) ) continue;
                            if (boostedTauByTightMuonRejection3->at(ibtau) ) continue;
                            if (boostedTauByLooseIsolationMVArun2v1DBoldDMwLT->at(ibtau) ) continue;
                            
                            
                            BoostedTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(ibtau),boostedTauEta->at(ibtau),boostedTauPhi->at(ibtau),boostedTauMass->at(ibtau));
                            if(BoostedTau4Momentum.DeltaR(Mu4Momentum) < 0.8 && BoostedTau4Momentum.DeltaR(Mu4Momentum) > 0.4){
                                
                                if (debug) cout<< "test 3.5\n";
                                ZCandida=BoostedTau4Momentum+Mu4Momentum;
                                numMuTau++;
                                
                                if (debug) cout<< "test 4\n";
                                plotFill("dR",BoostedTau4Momentum.DeltaR(Mu4Momentum) ,100,0,1);
                                plotFill("IsoMu",IsoMu ,100,0,2);
                                plotFill("MuId",MuId ,2,0,2);
                                plotFill("muD0",fabs(muD0->at(imu)) ,100,0,1);
                                plotFill("muDz",fabs(muDz->at(imu)) ,100,0,2);
                                plotFill("ZMass",ZCandida.M() ,30,0,300);
                                plotFill("tmass",tmass ,10,0,100);
                                
                                if (debug) cout<< "test 5\n";
                                
                                EventPass= true;
                                break;
                            }
                        }
                    }
                }
            }
            
            
            
            //            std::string CHL="";
            //
            //
            //            plotFill(CHL+"_boostedTauPt",leadingBoostedTauPt,200,0,2000,1);
            
            
            
            //###############################################################################################
            //  Doing EleTau Analysis
            //###############################################################################################
            //                }
            
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
