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
            
            bool PassTrigger_35 = ((HLTEleMuX >> 3 & 1)==1); //(name.find("HLT_Ele35_WPTight_Gsf_v") != string::npos) bitEleMuX =  3; // 2017
            bool PassTrigger_27 = ((HLTEleMuX >> 4 & 1)==1); //(name.find("HLT_Ele27_WPTight_Gsf_v")!= string::npos) bitEleMuX =  4; // 2017
            if (! PassTrigger_35 || !PassTrigger_27) continue;
            
            
            //###############################################################################################
            //  This part is to avoid of the duplicate of ele-j pair from one events
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
            
            TLorentzVector Ele4Momentum, Jet4Momentum,KJet4Momentum,BoostedTau4Momentum, ZCandida;
            
            if (debug) cout<< "test 1\n";
            
            bool EventPass= false;
            auto numeleTau(0);
            
            
            
            for  (int iele=0 ; iele < nEle; iele++){
                if (EventPass) break;
                
                if (elePt->at(iele) <= 40 || fabs(eleEta->at(iele)) >= 2.5) continue;
                
                bool eleMVAIdExtra_i= false;
                if (fabs (eleSCEta->at(iele)) <= 0.8 && eleIDMVAIso->at(iele) >    0.837   ) eleMVAIdExtra_i= true;
                else if (fabs (eleSCEta->at(iele)) >  0.8 &&fabs (eleSCEta->at(iele)) <=  1.5 && eleIDMVAIso->at(iele) >    0.715   ) eleMVAIdExtra_i= true;
                else if ( fabs (eleSCEta->at(iele)) >=  1.5 && eleIDMVAIso->at(iele) >   0.357   ) eleMVAIdExtra_i= true;
                else eleMVAIdExtra_i= false;
                
                bool EleIdIso=eleMVAIdExtra_i; //Tight  Id
                
                
                
                
                
                float tmass = TMass_F(Ele4Momentum.Pt(), Ele4Momentum.Px(), Ele4Momentum.Py(),  pfMET,  pfMETPhi);
                
                
                
                for (int ibtau = 0; ibtau < nBoostedTau; ++ibtau){
                    if (boostedTauPt->at(ibtau) <= 20 || fabs(boostedTauEta->at(ibtau)) >= 2.3 ) continue;
                    plotFill("cutFlow",8 ,15,0,15);
                    
                    if (debug) cout<< "test 3\n";
                    
                    
                    
                    
                    if (boostedTaupfTausDiscriminationByDecayModeFinding->at(ibtau) < 0.5 ) continue;
                    if (debug) cout<< "test 3.3\n";
                    if (boostedTauByMVA6TightElectronRejection->at(ibtau) < 0.5) continue;
                    if (debug) cout<< "test 3.1\n";
                    if (boostedTauByLooseMuonRejection3->at(ibtau) < 0.5) continue;
                    if (debug) cout<< "test 3.2\n";
                    
                    if (debug) cout<< "test 4\n";
                    BoostedTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(ibtau),boostedTauEta->at(ibtau),boostedTauPhi->at(ibtau),boostedTauMass->at(ibtau));
                    
                    if(BoostedTau4Momentum.DeltaR(Ele4Momentum) > 0.8 || BoostedTau4Momentum.DeltaR(Ele4Momentum) < 0.4) continue;
                    
                    
                    ZCandida=BoostedTau4Momentum+Ele4Momentum;
                    
                    
                    plotFill("ZMass",ZCandida.M() ,30,0,300);
                    
                    if (debug) cout<< "test 5\n";
                    //###############################################################################################
                    //  BoostedTau Isolation Categorization
                    //###############################################################################################
                    
                    const int size_tauCat = 2;
                    bool Pass = boostedTauByLooseIsolationMVArun2v1DBoldDMwLT->at(ibtau) > 0.5 ;
                    bool Fail = boostedTauByLooseIsolationMVArun2v1DBoldDMwLT->at(ibtau) < 0.5 ;
                    
                    bool Tau_category[size_tauCat] = {Pass, Fail};
                    std::string Tau_Cat[size_tauCat] = {"_Pass", "_Fail"};
                    
                    //###############################################################################################
                    //  lepton Isolation Categorization
                    //###############################################################################################
//                    bool LepPassIsolation= Isoele < LeptonIsoCut;
                    
                    const int size_isoCat = 2;
                    bool Isolation = EleIdIso;
                    bool AntiIsolation =  !EleIdIso;
                    
                    bool Iso_category[size_isoCat] = {Isolation, AntiIsolation};
                    std::string iso_Cat[size_isoCat] = {"_Iso", "_AntiIso"};
                    
                    if (debug) cout<< "test 6\n";
                    
                    //###############################################################################################
                    //  Charge Categorization
                    //###############################################################################################
                    float chargelt= eleCharge->at(iele) * boostedTauCharge->at(ibtau);
                    
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
                                            
                                            
                                            float FullWeight = LumiWeight;
                                            std::string FullStringName = Tau_Cat[tt] +iso_Cat[iso] + Q_Cat[iq] ;
                                            
                                            //                                This check is used to make sure that each event is just filled once for any of the categories ==> No doube-counting of events  (this is specially important for ttbar events where we have many jets and leptons)
                                            if (!( std::find(HistNamesFilled.begin(), HistNamesFilled.end(), FullStringName) != HistNamesFilled.end())){
                                                HistNamesFilled.push_back(FullStringName);
                                                
                                                
                                                
                                                plotFill("dR"+FullStringName,BoostedTau4Momentum.DeltaR(Ele4Momentum) ,100,0,1,FullWeight);
                                                plotFill("ZMass"+FullStringName,ZCandida.M() ,40,0,200,FullWeight);
                                                plotFill("tmass"+FullStringName,tmass ,5,0,50,FullWeight);
                                                plotFill("ht"+FullStringName,ht ,100,0,1000,FullWeight);
                                                
                                                
                                                
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    
                    
                }//boostedTau loop
            }//eleon loop
            
            
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
