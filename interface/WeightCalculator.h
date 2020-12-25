#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <map>
#include <string>
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include "TF1.h"
#include "TSystem.h"
#include "TMath.h" //M_PI is in TMath
#include "TRandom3.h"
#include <TLorentzVector.h>
using namespace std;


float WScaleFactor= 1.21 ;
float DYScaleFactor=1.23;
//float TTScaleFactor=0.91;
//float WScaleFactor=1.22;
//float TTScaleFactor=0.856;



float TT_FulLep_BR= 0.1061;
float TT_SemiLep_BR= 0.4392;
float TT_Had_BR= 0.4544;

float getLuminsoity(int year) {
    if (year == 2016) return 35900.;
    else if (year == 2017) return 41500.;
    else if (year == 2018) return 59610.;
    else return 0;
}

float XSection(std::string OutName) {

    if (OutName.find("Data") != string::npos) return 1;   // As we have large cut at Skim, this one is not
    else if (OutName.find("SingleMuon") != string::npos) return 1;   // As we have large cut at Skim, this one is not
    
    //Di Boson
    else if (OutName.find("ZZ4l") != string::npos) return   1.212;
    else if (OutName.find("ZZ2l2q") != string::npos) return  3.22;
    else if (OutName.find("WZ3l1nu") != string::npos) return  4.708;
    else if (OutName.find("WZ2l2Q") != string::npos) return  5.595;
    else if (OutName.find("WZ2l2q") != string::npos) return  5.595;
    else if (OutName.find("WZ1l1nu2q") != string::npos) return  10.71;
    else if (OutName.find("VV2l2nu") != string::npos) return  11.95;
    
    //Other Di Boson
    else if (OutName.find("ZZTo2L2Nu_powheg") != string::npos) return  0.564 ;
    //    else if (OutName.find("ZZTo2L2Q_powheg") != string::npos) return  3.22 ;
    else if (OutName.find("ZZTo2L2Q_amcNLO") != string::npos) return  3.22 ;
    //    else if (OutName.find("ZZTo2Q2Nu_powheg") != string::npos) return  4.04 ;
    else if (OutName.find("ZZTo4L_powheg") != string::npos) return  1.212 ;
    else if (OutName.find("WWTo2L2Nu_powheg") != string::npos) return  12.178 ;
    else if (OutName.find("WWTo4Q_powheg") != string::npos) return  51.723 ;
    else if (OutName.find("WWTo1LNuQQ_powheg") != string::npos) return  49.997 ;
    //    else if (OutName.find("WWTo1L1Nu2Q_amcatnloFXFX_madspin") != string::npos) return 49.997  ;
    else if (OutName.find("WZTo1L3Nu_amcatnloFXFX") != string::npos) return 3.033e+00;  //Not available  Just added after CWR
    else if (OutName.find("WZTo2L2Q_amcNLO") != string::npos) return  5.595 ;
    //    else if (OutName.find("WZTo2Q2Nu_amcatnloFXFX") != string::npos) return 10.000; // NOTE THIS IS JUST MY ESTIMATION small effect Not available
    else if (OutName.find("WZTo3LNu_amcNLO") != string::npos) return  4.42965 ;
    //       else if (OutName.find("WZToLNu2Q_powheg") != string::npos) return  10.71 ;
    else if (OutName.find("WZTo1L1Nu2Q_amcNLO") != string::npos) return  10.71 ;
    else if (OutName.find("WW1l1nu2q") != string::npos) return  49.997 ;
    else if (OutName.find("WZ1l3nu") != string::npos) return  3.05 ;

    // The missing one is WZto4Q
    //else if (OutName.find("ZZ") != string::npos) return  12.14 ;
    //else if (OutName.find("WZ") != string::npos) return  27.57 ;
    //else if (OutName.find("WW") != string::npos) return  75.88 ;
    
    
    //Single Top
    else if (OutName.find("Tbar-tchan") != string::npos) return  26.23;
    else if (OutName.find("T-tchan") != string::npos) return  44.07;
    else if (OutName.find("Tbar-tW") != string::npos) return  35.6;
    else if (OutName.find("T-tW") != string::npos) return  35.6;
    
    //Other SingleTop
    else if (OutName.find("ST_t-channel_antitop") != string::npos) return 80.95;
    else if (OutName.find("ST_t-channel_top") != string::npos) return 136.02;
    else if (OutName.find("ST_tW_antitop") != string::npos) return 35.6;
    else if (OutName.find("ST_tW_top") != string::npos) return 35.6;
    else if (OutName.find("ST_s_channel") != string::npos) return 3.36 ;
    
    // Top
    else if (OutName.find("TTTo2L2Nu") != string::npos) return (831.76*TT_FulLep_BR);
    else if (OutName.find("TTToHadronic") != string::npos) return (831.76*TT_Had_BR);
    else if (OutName.find("TTToSemiLeptonic") != string::npos) return (831.76*TT_SemiLep_BR);
    else if (OutName.find("TT") != string::npos) return (831.76);
    
    else if (OutName.find("EWK_DYToLL") != string::npos ) return      3.987;
    else if (OutName.find("QCD_Pt-20toInf_MuEnrichedPt15") != string::npos) return     720648000  * 0.00042 ;
    else if (OutName.find("QCD") != string::npos) return     720648000  * 0.00042 ;
    
    //    https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#W_jets
//    https://cms-gen-dev.cern.ch/xsdb/?searchQuery=DAS=DYJetsToLL_Pt-100To250_TuneCP5_13TeV-amcatnloFXFX-pythia8
    //    else if (OutName.find("WJetsToLNu") != string::npos) return  61526.7   ;
//    else if (OutName.find("WJetsToLNu_Pt-50To100") != string::npos) return  8053   ;
//    else if (OutName.find("WJetsToLNu_Pt-100To250") != string::npos) return  676.3   ;
//    else if (OutName.find("WJetsToLNu_Pt-250To400") != string::npos) return  23.94   ;
//    else if (OutName.find("WJetsToLNu_Pt-400To600") != string::npos) return  3.031   ;
//    else if (OutName.find("WJetsToLNu_Pt-600ToInf") != string::npos) return  0.4524   ;
    else if (OutName.find("WJetsToLNu_Pt-0To50") != string::npos) return  61850.0   ;
    else if (OutName.find("WJetsToLNu_Pt-50To100") != string::npos) return  3570.0   ;
    else if (OutName.find("WJetsToLNu_Pt-100To250") != string::npos) return  779.1   ;
    else if (OutName.find("WJetsToLNu_Pt-250To400") != string::npos) return  27.98   ;
    else if (OutName.find("WJetsToLNu_Pt-400To600") != string::npos) return  3.604   ;
    else if (OutName.find("WJetsToLNu_Pt-600ToInf") != string::npos) return  0.5545   ;

    //    else if (OutName.find("DYJetsToLL_M-50") != string::npos) return          5765.4 ;
//    else if (OutName.find("DYJetsToLL_Pt-50To100") != string::npos) return  354.3   ; $$$$ Wrong XS
//    else if (OutName.find("DYJetsToLL_Pt-100To250") != string::npos) return   83.12 ; $$$$ Wrong XS
//    else if (OutName.find("DYJetsToLL_Pt-250To400") != string::npos) return   3.047 ; $$$$ Wrong XS
//    else if (OutName.find("DYJetsToLL_Pt-400To650") != string::npos) return   0.3921 ; $$$$ Wrong XS
//    else if (OutName.find("DYJetsToLL_Pt-650ToInf") != string::npos) return   0.03636 ; $$$$ Wrong XS
    else if (OutName.find("DYJetsToLL_Pt-0To50") != string::npos) return  106300.0 / 12.8  ;// 12.8 is what I found by looking at the lower tail of the ht distribution between data and MC
    else if (OutName.find("DYJetsToLL_Pt-50To100") != string::npos) return  407.9   ;
    else if (OutName.find("DYJetsToLL_Pt-100To250") != string::npos) return   96.8 ;
    else if (OutName.find("DYJetsToLL_Pt-250To400") != string::npos) return   3.774 ;
    else if (OutName.find("DYJetsToLL_Pt-400To650") != string::npos) return   0.5164 ;
    else if (OutName.find("DYJetsToLL_Pt-650ToInf") != string::npos) return   0.04796 ;



    // SM Higgs
    else if (OutName.find("ggH125") != string::npos) return 48.58* 0.0627;
    else if (OutName.find("qqH125") != string::npos) return 3.782 * 0.0627;
    else if (OutName.find("WPlusH125") != string::npos) return 0.840 * 0.0627;
    else if (OutName.find("WMinusH125") != string::npos) return 0.5328 * 0.0627;
    else if (OutName.find("ZH125") != string::npos) return 0.8839 * 0.062;
    
    else if (OutName.find("JJH0PMToTauTauPlusTwoJets") != string::npos) return     0.1383997884      ;
    else if (OutName.find("JJH0PMToTauTauPlusOneJets") != string::npos) return       0.2270577971    ;
    else if (OutName.find("JJH0PMToTauTauPlusZeroJets") != string::npos) return     0.3989964912      ;
    
    else {
        cout<<"\n\n*********\nNot Listed in XSection menu !!!! Watch cout    "<<OutName<< "\n\n*********\n";
        return 0;
    }
}


//##################################################################
//   Needed for Stitching for LO W and Z
//##################################################################



//FIXME
vector <float> W_HTBin(std::string FileLoc){
    
    const int WSize=9;
    std::string W_ROOTFiles[WSize]={"WJetsToLNu_Inc.root","WJetsToLNu_Inc.root", "WJetsToLNu_HT-100to200.root","WJetsToLNu_HT-200to400.root","WJetsToLNu_HT-400to600.root", "WJetsToLNu_HT-600to800.root","WJetsToLNu_HT-800to1200.root","WJetsToLNu_HT-1200to2500.root","WJetsToLNu_HT-2500toInf.root"};
    
    //    std::string W_ROOTFiles[WSize]={"WJetsToLNu_Inc.root","WJetsToLNu_HT-70to100.root", "WJetsToLNu_HT-100to200.root","WJetsToLNu_HT-200to400.root","WJetsToLNu_HT-400to600.root", "WJetsToLNu_HT-600to800.root","WJetsToLNu_HT-800to1200.root","WJetsToLNu_HT-1200to2500.root","WJetsToLNu_HT-2500toInf.root"};
    
    
    //    const int WSize=1;
    //    std::string W_ROOTFiles[WSize]={"WJetsToLNu_Inc.root"};
    
    vector<float> W_events;
    W_events.clear();
    
    for (int i=0; i <WSize;i++){
        
        TFile * File_W = new TFile((FileLoc+W_ROOTFiles[i]).c_str());
        TH1F * Histo_W = (TH1F*) File_W->Get("hcount");
        W_events.push_back(Histo_W->GetBinContent(2));
        cout<<"Number of proccessed evenets for "<<W_ROOTFiles[i]<<" = "<<Histo_W->GetBinContent(2)<<"\n";
    }
    
    return W_events ;
    
}



//vector <float> W_HTBin(std::string FileLoc){
//    
//        const int WSize=5;
//        std::string W_ROOTFiles[WSize]={"WJetsToLNu_Inc.root","W1JetsToLNu.root", "W2JetsToLNu.root","W3JetsToLNu.root","W4JetsToLNu.root"};
//    
//    
//    vector<float> W_events;
//    W_events.clear();
//    
//    for (int i=0; i <WSize;i++){
//        
//        TFile * File_W = new TFile((FileLoc+W_ROOTFiles[i]).c_str());
//        TH1F * Histo_W = (TH1F*) File_W->Get("hcount");
//        W_events.push_back(Histo_W->GetBinContent(2));
//        cout<<"Number of proccessed evenets for "<<W_ROOTFiles[i]<<" = "<<Histo_W->GetBinContent(2)<<"\n";
//    }
//    
//    return W_events ;
//    
//}



vector <float> WMuNu_MassBin(std::string FileLoc){
    
    const int WSize=5;
    std::string W_ROOTFiles[WSize]={"WToMuNu_M-100_.root","WToMuNu_M-200_.root","WToMuNu_M-500_.root","WToMuNu_M-1000_.root","WToMuNu_M-2000_.root"};
    
    vector<float> W_events;
    W_events.clear();
    
    for (int i=0; i <WSize;i++){
        
        TFile * File_W = new TFile((FileLoc+W_ROOTFiles[i]).c_str());
        TH1F * Histo_W = (TH1F*) File_W->Get("hcount");
        W_events.push_back(Histo_W->GetBinContent(2));
        cout<<"Number of proccessed evenets for "<<W_ROOTFiles[i]<<" = "<<Histo_W->GetBinContent(2)<<"\n";
    }
    
    return W_events ;
    
}



vector <float> WTauNu_MassBin(std::string FileLoc){
    
    const int WSize=4;
    //    std::string W_ROOTFiles[WSize]={"WToTauNu_M-100_.root","WToTauNu_M-200_.root", "WToTauNu_M-500_.root","WToTauNu_M-1000_.root","WToTauNu_M-2000_.root"};
    std::string W_ROOTFiles[WSize]={"WToTauNu_M-100_.root","WToTauNu_M-200_.root","WToTauNu_M-1000_.root","WToTauNu_M-2000_.root"};
    
    vector<float> WTauNu_events;
    WTauNu_events.clear();
    
    for (int i=0; i <WSize;i++){
        
        TFile * File_W = new TFile((FileLoc+W_ROOTFiles[i]).c_str());
        TH1F * Histo_W = (TH1F*) File_W->Get("hcount");
        WTauNu_events.push_back(Histo_W->GetBinContent(2));
        cout<<"Number of proccessed evenets for "<<W_ROOTFiles[i]<<" = "<<Histo_W->GetBinContent(2)<<"\n";
    }
    
    return WTauNu_events ;
    
}




//vector <float> DY_HTBin(std::string FileLoc){
//
//    const int DYSize=5;
//    std::string DY_ROOTFiles[DYSize]={"DYJetsToLL_M-50_Inc.root", "DYJetsToLL_M-50_HT-100to200.root","DYJetsToLL_M-50_HT-200to400.root","DYJetsToLL_M-50_HT-400to600.root", "DYJetsToLL_M-50_HT-600toInf.root"};
//
//    vector<float> DY_events;
//    DY_events.clear();
//
//    for (int i=0; i < DYSize;i++){
//
//        TFile * File_DY = new TFile((FileLoc+DY_ROOTFiles[i]).c_str());
//        TH1F * Histo_DY= (TH1F*) File_DY->Get("hcount");
//        DY_events.push_back(Histo_DY->GetBinContent(2));
//        cout<<"Number of proccessed evenets for "<<DY_ROOTFiles[i]<<" = "<<Histo_DY->GetBinContent(2)<<"\n";
//    }
//
//    return DY_events ;
//
//}



//##################################################################
//   Fill out a vector with the lumi weight for each FXFX W sample
//##################################################################

vector <float> W_PTBinNLO(std::string FileLoc){
    
    const int WSizeNLO=5;
    std::string W_ROOTFilesNLO[WSizeNLO]={"WJetsToLNu.root",  "WJetsToLNu_Pt-100to250.root","WJetsToLNu_Pt-250to400.root","WJetsToLNu_Pt-400to600.root", "WJetsToLNu_Pt-600toInf.root"};
    
    vector<float> W_eventsNLO;
    W_eventsNLO.clear();
    
    for (int i=0; i <WSizeNLO;i++){
        
        TFile * File_WNLO = new TFile((FileLoc+W_ROOTFilesNLO[i]).c_str());
        TH1F * Histo_WNLO = (TH1F*) File_WNLO->Get("hcount");
        W_eventsNLO.push_back(Histo_WNLO->GetBinContent(2));
        cout<<"Number of proccessed evenets for "<<W_ROOTFilesNLO[i]<<" = "<<Histo_WNLO->GetBinContent(2)<<"\n";
    }
    
    return W_eventsNLO ;
    
}




//##################################################################
//   Fill out a vector with the lumi weight for each FXFX DY sample
//##################################################################

vector <float> Z_PTBinNLO(std::string FileLoc){
    
    const int ZSizeNLO=5;
    std::string Z_ROOTFilesNLO[ZSizeNLO]={"DYJetsToLL_M-50.root", "DYJetsToLL_Pt-100to250.root", "DYJetsToLL_Pt-250to400.root","DYJetsToLL_Pt-400to650.root","DYJetsToLL_Pt-650toInf.root"};
    
    vector<float> Z_eventsNLO;
    Z_eventsNLO.clear();
    
    for (int i=0; i <ZSizeNLO;i++){
        
        TFile * File_ZNLO = new TFile((FileLoc+Z_ROOTFilesNLO[i]).c_str());
        TH1F * Histo_ZNLO = (TH1F*) File_ZNLO->Get("hcount");
        Z_eventsNLO.push_back(Histo_ZNLO->GetBinContent(2));
        cout<<"Number of proccessed evenets for "<<Z_ROOTFilesNLO[i]<<" = "<<Histo_ZNLO->GetBinContent(2)<<"\n";
    }
    
    return Z_eventsNLO ;
    
}








//####################################################################################################################################
//####################################################################################################################################
//####################################################################################################################################
//     For Analysis
//####################################################################################################################################
//####################################################################################################################################
//####################################################################################################################################



float weightCalc(TH1F *Histo,std::string outputName, float genHT,vector<float> W_HTbin, float WMass, vector<float> WMuNu_MassBin, vector<float> WTauNu_Massbin) {
    
    stringstream ss(outputName);
    
    string token;
    string M;
    while (getline(ss,token, '/'))  M=token;
    
    std::string FirstPart = "";
    std::string LastPart = ".root";
    std::string newOut = M.substr(FirstPart.size());
    newOut = newOut.substr(0, newOut.size() - LastPart.size());
    
    
    //    float LOtoNLO_DY = 1.230888662;
    float LOtoNLO_DY = 1; // Now we boson have pt dependent SF
    //    float LOtoNLO_W = 1.213783784;
    float LOtoNLO_W = 1;  // Now we boson have pt dependent SF
    //    float luminosity=    12900;
    //    float luminosity=    35867;
    float luminosity=    41530; //May 15th
    
    
    size_t isSingleMu = outputName.find("SingleMu");
    size_t isSingleEle = outputName.find("SingleEle");
    size_t isData = outputName.find("Data");
    
    
    if (isSingleMu != string::npos || isSingleEle!= string::npos || isData !=string::npos)   return 1;
    
    
    //    size_t isWjet = outputName.find("WJets");
    size_t isWjet = outputName.find("JetsToLNu");
    size_t isWToMuNu = outputName.find("WToMuNu");
    size_t isWToTauNu = outputName.find("WToTauNu");
    
    
    
    //##################################################################
    //   Stitching for  W sample
    //##################################################################
    
    if (isWjet != string::npos && WMass <= 100){  //FIXME
        if (genHT <= 70)  return  luminosity * XSection("WJetsToLNu_Inc") / W_HTbin[0];
        else if (genHT > 70 && genHT <= 100)  return   luminosity * XSection("WJetsToLNu_Inc") / W_HTbin[1];
        else if (genHT > 100 && genHT <= 200)  return   luminosity * XSection("WJetsToLNu_HT-100to200") / W_HTbin[2];
        else if (genHT > 200 && genHT <= 400)  return   luminosity * XSection("WJetsToLNu_HT-200to400") / W_HTbin[3];
        else if (genHT > 400 && genHT <= 600)  return   luminosity * XSection("WJetsToLNu_HT-400to600") / W_HTbin[4];
        else if (genHT > 600 && genHT <= 800)  return   luminosity * XSection("WJetsToLNu_HT-600to800") / W_HTbin[5];
        else if (genHT > 800 && genHT <= 1200)  return   luminosity * XSection("WJetsToLNu_HT-800to1200") / W_HTbin[6];
        else if (genHT > 1200 && genHT <= 2500)  return   luminosity * XSection("WJetsToLNu_HT-1200to2500") / W_HTbin[7];
        else if (genHT > 2500 )  return   luminosity * XSection("WJetsToLNu_HT-2500toInf") / W_HTbin[8];
        else   {cout<<"**********   wooow  ********* There is a problem here\n";return 0;}
    }
    
    //    if (isWjet != string::npos && WMass <= 100){  FIXME
    //        if (genHT <= 70)  return  luminosity * XSection("WJetsToLNu_Inc") / W_HTbin[0];
    //        else if (genHT > 70 && genHT <= 100)  return   luminosity * XSection("WJetsToLNu_HT-70to100") / W_HTbin[1];
    //        else if (genHT > 100 && genHT <= 200)  return   luminosity * XSection("WJetsToLNu_HT-100to200") / W_HTbin[2];
    //        else if (genHT > 200 && genHT <= 400)  return   luminosity * XSection("WJetsToLNu_HT-200to400") / W_HTbin[3];
    //        else if (genHT > 400 && genHT <= 600)  return   luminosity * XSection("WJetsToLNu_HT-400to600") / W_HTbin[4];
    //        else if (genHT > 600 && genHT <= 800)  return   luminosity * XSection("WJetsToLNu_HT-600to800") / W_HTbin[5];
    //        else if (genHT > 800 && genHT <= 1200)  return   luminosity * XSection("WJetsToLNu_HT-800to1200") / W_HTbin[6];
    //        else if (genHT > 1200 && genHT <= 2500)  return   luminosity * XSection("WJetsToLNu_HT-1200to2500") / W_HTbin[7];
    //        else if (genHT > 2500 )  return   luminosity * XSection("WJetsToLNu_HT-2500toInf") / W_HTbin[8];
    //        else   {cout<<"**********   wooow  ********* There is a problem here\n";return 0;}
    //    }
    //
    
    //    if (isWjet != string::npos && WMass <= 100){
    //
    //        if (genNumJet_ == 0) return  luminosity * XSection("WJetsToLNu_Inc") / W_HTbin[0];
    //        else if (genNumJet_ == 1) return  luminosity * XSection("W1JetsToLNu") / W_HTbin[1];
    //        else if (genNumJet_ == 2) return  luminosity * XSection("W2JetsToLNu") / W_HTbin[2];
    //        else if (genNumJet_ == 3) return  luminosity * XSection("W3JetsToLNu") / W_HTbin[3];
    //        else if (genNumJet_ == 4) return  luminosity * XSection("W4JetsToLNu") / W_HTbin[4];
    //                else   {cout<<"**********   wooow  ********* There is a problem here\n";return 0;}
    //}
    
    
    
    else if (isWToMuNu != string::npos){
        if  (WMass > 100 && WMass <= 200)  return   luminosity /  (WMuNu_MassBin[0] /XSection("WToMuNu_M-100_"));
        else if  (WMass > 200 && WMass <= 500)  return   luminosity /  (WMuNu_MassBin[0] /XSection("WToMuNu_M-100_") +  WMuNu_MassBin[1]/ XSection("WToMuNu_M-200_")) ;
        else if  (WMass > 500 && WMass <= 1000)  return   luminosity /  (WMuNu_MassBin[0] /XSection("WToMuNu_M-100_") +  WMuNu_MassBin[1]/ XSection("WToMuNu_M-200_") +  WMuNu_MassBin[2]/ XSection("WToMuNu_M-500_")) ;
        else if  (WMass > 1000 && WMass <= 2000)  return   luminosity /  (WMuNu_MassBin[0] /XSection("WToMuNu_M-100_") +  WMuNu_MassBin[1]/ XSection("WToMuNu_M-200_") +  WMuNu_MassBin[2]/ XSection("WToMuNu_M-500_") + WMuNu_MassBin[3]/ XSection("WToMuNu_M-1000_")) ;
        else if  (WMass > 2000 )  return   luminosity / (WMuNu_MassBin[0] /XSection("WToMuNu_M-100_") +  WMuNu_MassBin[1]/ XSection("WToMuNu_M-200_") +  WMuNu_MassBin[2]/ XSection("WToMuNu_M-500_") + WMuNu_MassBin[3]/ XSection("WToMuNu_M-1000_") + WMuNu_MassBin[4]/ XSection("WToMuNu_M-2000_")) ;
        else   {cout<<"**********   wooow1  ********* There is a problem here\n";return 0;}
    }
    
    
    
    
    
    
    else if (isWToTauNu != string::npos){
        if  (WMass > 100 && WMass <= 200)  return   luminosity /  (WTauNu_Massbin[0] /XSection("WToMuNu_M-100_"));
        else if  (WMass > 200 && WMass <= 1000)  return   luminosity /  (WTauNu_Massbin[0] /XSection("WToMuNu_M-100_") +  WTauNu_Massbin[1]/ XSection("WToMuNu_M-200_")) ;
        else if  (WMass > 1000 && WMass <= 2000)  return   luminosity /  (WTauNu_Massbin[0] /XSection("WToMuNu_M-100_") +  WTauNu_Massbin[1]/ XSection("WToMuNu_M-200_") +  WTauNu_Massbin[2]/ XSection("WToMuNu_M-1000_")) ;
        else if  (WMass > 2000 )  return   luminosity / (WTauNu_Massbin[0] /XSection("WToMuNu_M-100_") +  WTauNu_Massbin[1]/ XSection("WToMuNu_M-200_") +   WTauNu_Massbin[2]/ XSection("WToMuNu_M-1000_") + WTauNu_Massbin[3]/ XSection("WToMuNu_M-2000_")) ;
        else   {cout<<"**********   wooow  ********* There is a problem here\n";return 0;}
    }
    
    
    
    else
        return luminosity * XSection(newOut)*1.0 / Histo->GetBinContent(2);
}


//####################################################################################################################################


//float weightCalc_NoWStitch(TH1F *Histo,std::string outputName, float genHT) {
//    
//    
//    stringstream ss(outputName);
//    
//    string token;
//    string M;
//    while (getline(ss,token, '/'))  M=token;
//    
//    std::string FirstPart = "";
//    std::string LastPart = ".root";
//    std::string newOut = M.substr(FirstPart.size());
//    newOut = newOut.substr(0, newOut.size() - LastPart.size());
//    
//    
//    //    float LOtoNLO_DY = 1.230888662;
//    float LOtoNLO_DY = 1; // Now we boson have pt dependent SF
//    //    float LOtoNLO_W = 1.213783784;
//    float LOtoNLO_W = 1;  // Now we boson have pt dependent SF
//    //    float luminosity=    12900;
//    float luminosity=    35867;
//    
//    
//    size_t isSingleMu = outputName.find("SingleMu");
//    size_t isSingleEle = outputName.find("SingleEle");
//    
//    
//    if (isSingleMu != string::npos || isSingleEle!= string::npos)   return 1;
//    
//    
//    else if (genHT < 70 &&  newOut.find("WJetsToLNu_Inc") != string::npos) return luminosity * 50690*1.0 / Histo->GetBinContent(2) ;   // As we have large cut at Skim, this one is not needed
//    else if (genHT >70 &&  newOut.find("WJetsToLNu_Inc") != string::npos) return 0 ;   // As we have large cut at Skim, this one is not needed
//    
//    
//    else
//        return luminosity * XSection(newOut)*1.0 / Histo->GetBinContent(2);
//    
//    
//}



//####################################################################################################################################
//####################################################################################################################################
//     ONLY for FXFX sample for K-factor Study
//####################################################################################################################################
//####################################################################################################################################
//####################################################################################################################################


//float weightCalc_Stitching(TH1F *Histo,std::string outputName , float WPt, float ZPt, vector<float> W_eventsNLO,vector<float> Z_eventsNLO) {
//    
//    float luminosity=    41400;
//    
//    size_t isWjet = outputName.find("WJets");
//    size_t isFXFX = outputName.find("FXFX");
//    size_t isDYJet = outputName.find("DYJets");
//    
//    //##################################################################
//    //   Stitching for  FXFX W sample
//    //##################################################################
//    if (isWjet != string::npos && isFXFX != string::npos) {
//        
//        if (WPt <= 100)                  return   luminosity / (W_eventsNLO[0] / XSection("WJetsToLNu"));
//        
//        else if (WPt > 100 && WPt <= 250)return   luminosity / (W_eventsNLO[1] / XSection("WJetsToLNu_Pt-100to250") + W_eventsNLO[0] / XSection("WJetsToLNu"));
//        else if (WPt > 250 && WPt <=400) return   luminosity / (W_eventsNLO[2] / XSection("WJetsToLNu_Pt-250to400") + W_eventsNLO[0] / XSection("WJetsToLNu"));
//        else if (WPt > 400 && WPt <=600) return   luminosity / (W_eventsNLO[3] / XSection("WJetsToLNu_Pt-400to600") + W_eventsNLO[0] / XSection("WJetsToLNu"));
//        else if (WPt > 600 )               return   luminosity / (W_eventsNLO[4] / XSection("WJetsToLNu_Pt-600toInf") + W_eventsNLO[0] / XSection("WJetsToLNu"));
//        else   {cout<<"**********   wooow2  ********* There is a problem here\n";return 0;}
//    }
//    //##################################################################
//    //   Stitching for  FXFX DY sample
//    //##################################################################
//    else if (isDYJet != string::npos && isFXFX != string::npos) {
//        
//        if (ZPt <= 100)                  return   luminosity / (Z_eventsNLO[0] / XSection("DYJetsToLL_M-50"));
//        else if (ZPt > 100 && ZPt <= 250)return   luminosity / (Z_eventsNLO[1] / XSection("DYJetsToLL_Pt-100to250") + Z_eventsNLO[0] / XSection("DYJetsToLL_M-50"));
//        else if (ZPt > 250 && ZPt <=400) return   luminosity / (Z_eventsNLO[2] / XSection("DYJetsToLL_Pt-250to400") + Z_eventsNLO[0] / XSection("DYJetsToLL_M-50"));
//        else if (ZPt > 400 && ZPt <=600) return   luminosity / (Z_eventsNLO[3] / XSection("DYJetsToLL_Pt-400to650") + Z_eventsNLO[0] / XSection("DYJetsToLL_M-50"));
//        else if (ZPt > 600 )               return   luminosity / (Z_eventsNLO[4] / XSection("DYJetsToLL_Pt-650toInf") + Z_eventsNLO[0] / XSection("DYJetsToLL_M-50"));
//        else   {cout<<"**********   wooow3  ********* There is a problem here\n";return 0;}
//    }
//    
//    else{
//        cout<<"\n\n*********\nNot a FXFX sample  !!!! Watch cout    "<<outputName<< "\n\n*********\n";
//        return 1;}
//}





//    if (OutName.find("WJetsToLNu_Inc") != string::npos) return 50690;   // As we have large cut at Skim, this one is not needed
//    //    else if (OutName.find("WJetsToLNu_HT-70To100") != string::npos) return 1372 * WScaleFactor;
//    else if (OutName.find("WJetsToLNu_HT-100To200") != string::npos) return 1345* WScaleFactor;
//    else if (OutName.find("WJetsToLNu_HT-200To400") != string::npos) return 359.7* WScaleFactor;
//    else if (OutName.find("WJetsToLNu_HT-400To600") != string::npos) return 48.91* WScaleFactor;
//    else if (OutName.find("WJetsToLNu_HT-600To800") != string::npos) return 12.05* WScaleFactor;
//    else if (OutName.find("WJetsToLNu_HT-800To1200") != string::npos) return 5.501* WScaleFactor;
//    else if (OutName.find("WJetsToLNu_HT-1200To2500") != string::npos) return 1.329* WScaleFactor;
//    else if (OutName.find("WJetsToLNu_HT-2500ToInf") != string::npos) return 0.03216* WScaleFactor;

//    else if (OutName.find("W1JetsToLNu") != string::npos) return 9644.5;
//    else if (OutName.find("W2JetsToLNu") != string::npos) return 3144.5;
//    else if (OutName.find("W3JetsToLNu") != string::npos) return 954.8;
//    else if (OutName.find("W4JetsToLNu") != string::npos) return 485.6;
//
//
//
//    //http://cms.cern.ch/iCMS/jsp/db_notes/noteInfo.jsp?cmsnoteid=CMS%20AN-2016/204
//    else if (OutName.find("WToMuNu_M-100_") != string::npos) return 163.15;
//    else if (OutName.find("WToMuNu_M-200_") != string::npos) return 6.236;
//    else if (OutName.find("WToMuNu_M-500_") != string::npos) return 0.2138;
//    else if (OutName.find("WToMuNu_M-1000_") != string::npos) return 0.01281;
//    else if (OutName.find("WToMuNu_M-2000_") != string::npos) return 5.56e-04;
//    else if (OutName.find("WToMuNu_M-3000_") != string::npos) return 2.904e-05;
//
//
//
//    else if (OutName.find("WToTauNu_M-100_") != string::npos) return 163.15;
//    else if (OutName.find("WToTauNu_M-200_") != string::npos) return 6.236;
//    else if (OutName.find("WToTauNu_M-500_") != string::npos) return 0.2138;
//    else if (OutName.find("WToTauNu_M-1000_") != string::npos) return 0.01281;
//    else if (OutName.find("WToTauNu_M-2000_") != string::npos) return 5.56e-04;



//    else if (OutName.find("DYJetsToLL_Inc") != string::npos) return 4895 * 1.012; // As we have large cut at Skim, this one is not needed
//    //    else if (OutName.find("DYJetsToLL_M-50_HT-70to100") != string::npos) return 169.9 * DYScaleFactor;
//    else if (OutName.find("DYJetsToLL_M-50_HT-100to200") != string::npos) return 147.40* DYScaleFactor;
//    else if (OutName.find("DYJetsToLL_M-50_HT-200to400") != string::npos) return 40.99* DYScaleFactor;
//    else if (OutName.find("DYJetsToLL_M-50_HT-400to600") != string::npos) return 5.678* DYScaleFactor;
//    else if (OutName.find("DYJetsToLL_M-50_HT-600to800") != string::npos) return 1.367* DYScaleFactor;
//    else if (OutName.find("DYJetsToLL_M-50_HT-800to1200") != string::npos) return 0.6304* DYScaleFactor;
//    else if (OutName.find("DYJetsToLL_M-50_HT-1200to2500") != string::npos) return 0.1514* DYScaleFactor;
//    else if (OutName.find("DYJetsToLL_M-50_HT-2500toInf") != string::npos) return 0.003565* DYScaleFactor;
//    else if (OutName.find("ZJetsToNuNu_HT-100to200") != string::npos) return    280.35  * 1.23       ;
//    else if (OutName.find("ZJetsToNuNu_HT-200to400") != string::npos) return     77.67  * 1.23     ;
//    else if (OutName.find("ZJetsToNuNu_HT-400to600") != string::npos) return      10.73 * 1.23     ;
//    else if (OutName.find("ZJetsToNuNu_HT-600to800") != string::npos) return      2.559  * 1.23     ;
//    else if (OutName.find("ZJetsToNuNu_HT-800to1200") != string::npos) return     1.1796   * 1.23    ;
//    else if (OutName.find("ZJetsToNuNu_HT-1200to2500") != string::npos) return     0.28833   * 1.23    ;
//    else if (OutName.find("ZJetsToNuNu_HT-2500toInf") != string::npos) return      0.006945    * 1.23     ;
//



//    {"Tbar-tW", 35.6},
//    {"T-tW", 35.6},
//    {"T-tW_v2", 35.6},
//    {"Tbar-tchan", 26.23},
//    {"Tbar-tchan_v2", 26.23},
//    {"T-tchan", 44.07},
//    {"TT", 831.76},
//    {"TTHad", 377.96},
//    {"TTToHadronic", 377.96},
//    {"TTHad_v2", 377.96},
//    {"TTLep", 88.29},
//    {"TTTo2L2Nu", 88.29},
//    {"TTSemi", 365.35},
//    {"TTToSemiLeptonic", 365.35},
//    {"TTSemi_v2", 365.35},
//    {"VV2l2nu", 11.95},
//    {"WJets", 61526.7},
//    {"WJets_ext1", 61526.7},
//    {"WJets1", 61526.7},
//    {"WJets2", 61526.7},
//    {"WJets3", 61526.7},
//    {"WJets4", 61526.7},
//    {"WW1l1nu2q", 49.997},
//    {"WZ1l1nu2q", 10.71},
//    {"WZ1l1nu2q_v2", 10.71},
//    {"WZ1l3nu", 3.05},
//    {"WZ2l2Q", 5.595},
//    {"WZ3l1nu", 4.708},
//    {"WW", 75.88},
//    {"WZ", 27.57},
//    {"ZZ", 12.14},
//    {"ZZ2l2q", 3.22},
//    {"ZZ4l", 1.212},
//    {"ZZ4l_ext1", 1.212},
//    {"ZZ4l_v2", 1.212},
//    {"data", 1.0},





//https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns
//    https://docs.google.com/spreadsheets/d/1rWM3AlFKO8IJVaeoQkWZYWwSvicQ1QCXYSzH74QyZqE/edit?alt=json#gid=398123591










