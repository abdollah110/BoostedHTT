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
                
                bool MuId=( (muIDbit->at(imu) >> 2 & 1)  && fabs(muD0->at(imu)) < 0.045 && fabs(muDz->at(imu)) < 0.2); //Tight Muon Id
                
                
                if (!MuId ) continue;
                if (IsoMu > 0.2 ) continue;
                
                
                for (int jmu = imu+1; jmu < nMu; ++jmu){
                    if (muPt->at(jmu) <= 10 || fabs(muEta->at(jmu)) >= 2.4) continue;
                    
                    Mu4Momentum_sub.SetPtEtaPhiM(muPt->at(jmu),muEta->at(jmu),muPhi->at(jmu),MuMass);
                    
                    
                    float IsoMu_sub=muPFChIso->at(jmu)/muPt->at(jmu);
                    if ( (muPFNeuIso->at(jmu) + muPFPhoIso->at(jmu) - 0.5* muPFPUIso->at(jmu) )  > 0.0)
                        IsoMu_sub= ( muPFChIso->at(jmu) + muPFNeuIso->at(jmu) + muPFPhoIso->at(jmu) - 0.5* muPFPUIso->at(jmu))/muPt->at(jmu);
                    
                    bool MuId_sub=( (muIDbit->at(jmu) >> 2 & 1)  && fabs(muD0->at(jmu)) < 0.045 && fabs(muDz->at(jmu)) < 0.2); //Tight Muon Id
                    
                    
                    if (!MuId_sub ) continue;
                    if (IsoMu_sub > 0.2 ) continue;
                    
                    if(Mu4Momentum_sub.DeltaR(Mu4Momentum) > 1.0 ) continue;
                    ZCandida=Mu4Momentum_sub+Mu4Momentum;
            
            

            
            
            
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
