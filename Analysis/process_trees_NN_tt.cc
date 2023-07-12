// ./process_trees_tt -d newBoost_tt_2018_trgData_newcuts  --suf tt_2018_trgData_newcut  -v m_sv -b 30 0 300
// user includes
#include "TStopwatch.h"
#include "TMath.h"
#include "../interface/CLParser.h"
#include "../interface/process_trees_NN.h"
#include <iomanip>      // std::setprecision
#include <iostream>
#include <fstream>
//#include <json/json.h>
// #include <jsoncpp/json/json.h>



using std::string;
using std::vector;
int main(int argc, char *argv[]) {
    auto watch = TStopwatch();
    // get CLI arguments
    CLParser parser(argc, argv);
    bool doSyst = parser.Flag("-s");
    string dir = parser.Option("-d");
    string suffix = parser.Option("--suf");
    std::string var_name = parser.Option("-v");
    std::vector<std::string> sbins = parser.MultiOption("-b", 3);
    bool runPDF = parser.Flag("-p");
    std::string runTauId = parser.Option("-t");
    
    
    string year;
    if (dir.find("2016") != string::npos) year ="2016";
    else if (dir.find("2017") != string::npos ) year ="2017";
    else if (dir.find("2018") != string::npos) year ="2018";
    else (std::cout << "Year is not specificed in the outFile name !\n");
    
    struct {
        TH1F * FRhist;
        float FitPar;
        float FitParErr;
    } FR;
    
    //    TFile * FRFile= new TFile(("data/File_fr_numVLoose_"+year+".root").c_str(),"r");
    TFile * FRFile= new TFile(("data/File_fr_numVLoose_"+year+"_v7_pt.root").c_str(),"r");
    //    FR.FRhist=(TH1F *) FRFile->Get("numVLoose");
    FR.FRhist=(TH1F *) FRFile->Get("numHistRB"); // FIXME for reproducing the preapproval results
    TF1 *func = new TF1("fit","pol0",200,500);
    FR.FRhist->Fit("fit","R");
    FR.FitPar= func->GetParameter(0);
    FR.FitParErr= func->GetParError(0);
    cout<<"FitPar = " << FR.FitPar  <<"  FitParErr= " << FR.FitParErr<< "\n";
    
    //    TFile * FRFile= new TFile(("data/File_fr_numLoose_"+year+".root").c_str(),"r");
    //    TH1F * FRhist=(TH1F *) FRFile->Get("numLoose");
    
    string channel, tree_name;
    if (dir.find("tt") != string::npos) {channel ="tt";tree_name="tautau_tree";}
    else (std::cout << "channel is not specificed in the outFile name !\n");
    string newChannelName= channel;
    
    myMap1 = new std::unordered_map<std::string, TH1F*>();
    
    // get the provided histogram binning
    std::vector<float> bins;
    for (auto sbin : sbins) {
        bins.push_back(std::stoi(sbin));
    }
    
    
    
    
    // get input file directory
    if (dir.empty()) {
        std::cerr << "You must give an input directory" << std::endl;
        return -1;
    }
    
    
    // read all files from input directory
    vector<string> files;
    read_directory(dir, &files);
    
    // initialize histogram holder
    auto hists = new HistTool(newChannelName, channel,var_name,  year, suffix+runTauId, bins);
    
    
    // This part is tro derive the OS/SS ratio (one can actually get the 2D pt/eta binned Values as well)
    //    hists->histoQCD(files, dir, tree_name,  "None");    // fill histograms QCD
    
    //    std::vector<float>  OSSS= hists->Get_OS_SS_ratio();
    //    std::cout<<"\n\n\n\n OSSS  "<<OSSS[0]<<"\n";
    std::vector<float>  OSSS= hists->Get_OS_SS_ratio();
    
    
    
    hists->histoLoop(year, files, dir, FR.FRhist, FR.FitPar, FR.FitParErr,tree_name,var_name,OSSS,runPDF,runTauId);    // fill histograms
    hists->writeTemplates(dir,channel,year);  // write histograms to file
    // save histograms for pdf and scale uncertainties
    unordered_map<string, TH1F*>::const_iterator iMap1 = myMap1->begin();
    unordered_map<string, TH1F*>::const_iterator jMap1 = myMap1->end();
    for (; iMap1 != jMap1; ++iMap1)
        nplot1(iMap1->first)->Write();
    //
    hists->fout->Close();
    
    std::cout << "Template created.\n Timing Info: \n\t CPU Time: " << watch.CpuTime() << "\n\tReal Time: " << watch.RealTime() << std::endl;
    
    //  delete hists->ff_weight;
}

void HistTool::histoLoop(std::string year , vector<string> files, string dir, TH1F * FRhist, float FitPar, float FitParErr,  string tree_name , string var_name, vector<float> OSSS, bool runPDF,string runTauId ) {
    
    //void HistTool::histoLoop(std::string year , vector<string> files, string dir, TH1F * FR.FRhist, float FR.FitPar, float FR.FitParErr,, string tree_name , string var_name, vector<float> OSSS, bool runPDF, string Sys = "") {
    
    std::cout<< "starting .... "<<dir<<"\n";
    float vbf_var1(0.);
    
    initVectors1dFake("nominal");
    initVectors1dFake("up");
    initVectors1dFake("down");
    initVectors1dFake("frup");
    initVectors1dFake("frdown");
    
    
    for (auto ifile : files) {
        
        
        string name = ifile.substr(0, ifile.find(".")).c_str();
        if (runPDF && (name.find("TT") ==string::npos || name.find("Up") !=string::npos || name.find("Down") !=string::npos )) continue;
        if (runTauId.find("TauIdBin")!=string::npos && (name.find("Up") !=string::npos || name.find("Down") !=string::npos )) continue;
        if (name.find("PTH") !=string::npos || name.find("OutsideAcceptance") !=string::npos) continue;
        
        
        //         for Control Plots
        //        if (name.find("Up") !=string::npos || name.find("Down") !=string::npos ) continue;
        
        auto fin = new TFile((dir + "/" + ifile).c_str(), "read");
        std::cout<<"ifile is openning: " <<ifile<<"\n";
        auto tree = reinterpret_cast<TTree *>(fin->Get(tree_name.c_str()));
        
        
        // do some initialization
        initVectors1d(name);
        fout->cd();
        
        float lep1Pt_=-10;
        float lep2Pt_=-10;
        float vis_mass=-10;
        float LeadJetPt = -10;
        bool lep1IsoPassV, lep2IsoPassV ,OS,SS, lep1IsoPassL, lep2IsoPassL;
        float tmass,ht,st,Met,weight, dR_lep_lep, Metphi;
        float NN_disc,MuMatchedIsolation,EleMatchedIsolation,NN_disc_ZTT,NN_disc_QCD;
        float higgs_pT, higgs_m, m_sv, gen_higgs_pT;
        Float_t         pdfWeight=0;
        vector<double>   *pdfSystWeight=0;
        bool isGenTauSub_, isGenTauLead_;
        
        
        tree->SetBranchAddress("isGenTauLead_",&isGenTauLead_);
        tree->SetBranchAddress("isGenTauSub_",&isGenTauSub_);
        tree->SetBranchAddress("lep1Pt",&lep1Pt_);
        tree->SetBranchAddress("lep2Pt",&lep2Pt_);
        tree->SetBranchAddress("lep1IsoPassV",&lep1IsoPassV);
        tree->SetBranchAddress("lep2IsoPassV",&lep2IsoPassV);
        tree->SetBranchAddress("lep1IsoPassL",&lep1IsoPassL);
        tree->SetBranchAddress("lep2IsoPassL",&lep2IsoPassL);
        tree->SetBranchAddress("OS",&OS);
        tree->SetBranchAddress("SS",&SS);
        tree->SetBranchAddress("vis_mass",&vis_mass);
        tree->SetBranchAddress("tmass",&tmass);
        tree->SetBranchAddress("ht",&ht);
        tree->SetBranchAddress("st",&st);
        tree->SetBranchAddress("Met",&Met);
        tree->SetBranchAddress("LeadJetPt",&LeadJetPt);
        tree->SetBranchAddress("dR_lep_lep",&dR_lep_lep);
        tree->SetBranchAddress("evtwt",&weight);
        tree->SetBranchAddress("NN_disc",&NN_disc);
        tree->SetBranchAddress("NN_disc_ZTT",&NN_disc_ZTT);
        tree->SetBranchAddress("NN_disc_QCD",&NN_disc_QCD);
        tree->SetBranchAddress("higgs_pT",&higgs_pT);
        tree->SetBranchAddress("higgs_m",&higgs_m);
        tree->SetBranchAddress("m_sv",&m_sv);
        tree->SetBranchAddress("MuMatchedIsolation",&MuMatchedIsolation);
        tree->SetBranchAddress("EleMatchedIsolation",&EleMatchedIsolation);
        tree->SetBranchAddress("gen_higgs_pT",&gen_higgs_pT);
        if (runPDF){
            tree->SetBranchAddress("pdfWeight", &pdfWeight);
            tree->SetBranchAddress("pdfSystWeight",&pdfSystWeight);
        }
        
        int nbin[3]={13,1,1};
        float lowBin=0.35;
        float highBin=1;
        //        int nbin[3]={40,1,1}; // FIXME changining the binning to 40
        //        float lowBin=0;
        //        float highBin=1;
        
        
        // Here we have to call OS/SS method extracter
        std::cout<<" tree->GetEntries() is "<<tree->GetEntries()<<"\n";
        for (auto i = 0; i < tree->GetEntries(); i++) {
            tree->GetEntry(i);
            if (runPDF) {if (i % 10 == 0) fprintf(stdout, "\r  Processed events: %8d of %8lld ", i, tree->GetEntries());}
            
            std::map<std::string, float>  ObsName {
                {"lep1Pt",lep1Pt_},
                {"lep2Pt",lep2Pt_},
                {"lep1IsoPassV",lep1IsoPassV},
                {"lep2IsoPassV",lep2IsoPassV},
                {"vis_mass",vis_mass},
                {"tmass",tmass},
                {"ht",ht},
                {"st",st},
                {"Met",Met},
                {"LeadJetPt",LeadJetPt},
                {"dR_lep_lep",dR_lep_lep},
                {"higgs_pT",higgs_pT},
                {"higgs_m",higgs_m},
                {"m_sv",m_sv},
                {"NN_disc",NN_disc},
                {"NN_disc_ZTT",NN_disc_ZTT},
                {"NN_disc_QCD",NN_disc_QCD},
                {"MuMatchedIsolation",MuMatchedIsolation},
                {"EleMatchedIsolation",EleMatchedIsolation}
            };
            
            // apply tau Id SF
            if (isGenTauLead_ && (  name.find("ZTT")!= string::npos || name.find("TT")!= string::npos || name.find("VV")!= string::npos || name.find("125")!= string::npos )) weight *= 0.9;
            if (isGenTauSub_ && ( name.find("ZTT")!= string::npos || name.find("TT")!= string::npos || name.find("VV")!= string::npos || name.find("125")!= string::npos ))
                weight *= 0.9;
            
            //            Json::Value people;
            //            std::ifstream people_file("TauUncValues.json", std::ifstream::binary);
            //            people_file >> people;
            //            std::cout << people["value"] << "\n";
            
            float UncVal=0;
            
            if (runTauId.find("TauIdBin_1") != string::npos && year.find("2016") != string::npos) UncVal=
                0.155270725489;
            if (runTauId.find("TauIdBin_1") != string::npos && year.find("2017") != string::npos) UncVal=
                0.145713633392;
            if (runTauId.find("TauIdBin_1") != string::npos && year.find("2018") != string::npos) UncVal=
                0.107479907572;
            if (runTauId.find("TauIdBin_2") != string::npos && year.find("2016") != string::npos) UncVal=
                0.0943855410442;
            if (runTauId.find("TauIdBin_2") != string::npos && year.find("2017") != string::npos) UncVal=
                0.111481435597;
            if (runTauId.find("TauIdBin_2") != string::npos && year.find("2018") != string::npos) UncVal=
                0.0855802134611;
            if (runTauId.find("TauIdBin_3") != string::npos && year.find("2016") != string::npos) UncVal=
                0.271097958088;
            if (runTauId.find("TauIdBin_3") != string::npos && year.find("2017") != string::npos) UncVal=
                0.30220964551;
            if (runTauId.find("TauIdBin_3") != string::npos && year.find("2018") != string::npos) UncVal=
                0.271097958088;
            if (runTauId.find("TauIdBin_4") != string::npos && year.find("2016") != string::npos) UncVal=
                0.586049079895;
            if (runTauId.find("TauIdBin_4") != string::npos && year.find("2017") != string::npos) UncVal=
                0.716439247131;
            if (runTauId.find("TauIdBin_4") != string::npos && year.find("2018") != string::npos) UncVal=
                0.345309078693;
            
            
            if (runTauId.find("TauIdBin_1_Up") != string::npos && (higgs_pT> 200 && higgs_pT < 400 ) && (isGenTauLead_ && isGenTauSub_) && (name.find("ZTT")!= string::npos || name.find("TT")!= string::npos || name.find("VV")!= string::npos || name.find("125")!= string::npos )) weight *=  (1+UncVal) ;
            if (runTauId.find("TauIdBin_1_Down") != string::npos && (higgs_pT> 200 && higgs_pT < 400 ) && (isGenTauLead_ && isGenTauSub_) && (name.find("ZTT")!= string::npos || name.find("TT")!= string::npos || name.find("VV")!= string::npos || name.find("125")!= string::npos )) weight *=  (1-UncVal) ;
            if (runTauId.find("TauIdBin_2_Up") != string::npos && (higgs_pT> 400 && higgs_pT < 600 ) && (isGenTauLead_ && isGenTauSub_) && (name.find("ZTT")!= string::npos || name.find("TT")!= string::npos || name.find("VV")!= string::npos || name.find("125")!= string::npos )) weight *=  (1+UncVal) ;
            if (runTauId.find("TauIdBin_2_Down") != string::npos && (higgs_pT> 400 && higgs_pT < 600 ) && (isGenTauLead_ && isGenTauSub_) && (name.find("ZTT")!= string::npos || name.find("TT")!= string::npos || name.find("VV")!= string::npos || name.find("125")!= string::npos )) weight *=  (1-UncVal) ;
            if (runTauId.find("TauIdBin_3_Up") != string::npos && (higgs_pT> 600 && higgs_pT < 800 ) && (isGenTauLead_ && isGenTauSub_) && (name.find("ZTT")!= string::npos || name.find("TT")!= string::npos || name.find("VV")!= string::npos || name.find("125")!= string::npos )) weight *=  (1+UncVal) ;
            if (runTauId.find("TauIdBin_3_Down") != string::npos && (higgs_pT> 600 && higgs_pT < 800 ) && (isGenTauLead_ && isGenTauSub_) && (name.find("ZTT")!= string::npos || name.find("TT")!= string::npos || name.find("VV")!= string::npos || name.find("125")!= string::npos )) weight *=  (1-UncVal) ;
            if (runTauId.find("TauIdBin_4_Up") != string::npos && (higgs_pT> 800 && higgs_pT < 1000 ) && (isGenTauLead_ && isGenTauSub_) && (name.find("ZTT")!= string::npos || name.find("TT")!= string::npos || name.find("VV")!= string::npos || name.find("125")!= string::npos )) weight *=  (1+UncVal) ;
            if (runTauId.find("TauIdBin_4_Down") != string::npos && (higgs_pT> 800 && higgs_pT < 1000 ) && (isGenTauLead_ && isGenTauSub_) && (name.find("ZTT")!= string::npos || name.find("TT")!= string::npos || name.find("VV")!= string::npos || name.find("125")!= string::npos )) weight *=  (1-UncVal) ;
            
            
            
            // Validation cuts relaxed!
            //            if (m_sv < 50) continue;
            //            if (higgs_pT < 100) continue;
            //            if (tmass > 200) continue;
            
            
            float lep1Ptval=lep1Pt_;
            if (lep1Ptval > 200) lep1Ptval=200;
            float frValu1 = FRhist->GetBinContent(FRhist->GetXaxis()->FindBin(lep1Ptval));
            
            
            float lep2Ptval=lep2Pt_;
            //            if (lep2Ptval > 200) lep2Ptval=200;// FIXME for reproducing the preapproval results
            float frValu2 = FRhist->GetBinContent(FRhist->GetXaxis()->FindBin(lep2Ptval));
            float frValuErr = FRhist->GetBinError(FRhist->GetXaxis()->FindBin(lep2Ptval));
            float frValuUncUp=frValu2+frValuErr;
            float frValuUncDown=frValu2-frValuErr;
            if (lep2Ptval > 200) {
                frValu2 = FitPar;
                frValuUncUp=frValu2+ 2*FitParErr + (lep2Ptval-200)*(5*FitParErr)/300;
                frValuUncDown=frValu2- 2*FitParErr - (lep2Ptval-200)*(5*FitParErr)/300;
            }// FIXME for reproducing the preapproval results
            
            
            
            vbf_var1 =ObsName[var_name];
            
            
            //            //            ################################################################################
            //            //            ################    Fill  data, signal & non QCD Bkg
            //            //            ################################################################################
            //            if (OS != 0  && lep1IsoPassV && lep2IsoPassV) { // final analysis
            //                hists_1d.at(categories.at(zeroJet)).back()->Fill(vbf_var1,  weight); // final analysis
            //                hists_2d.at(categories.at(zeroJet)).back()->Fill(NN_disc,NN_disc_ZTT,  weight);
            //                Histo_2DMatrix.at(categories.at(zeroJet)).back()->Fill(gen_higgs_pT,higgs_pT,  weight);
            //            }
            //
            //
            ////             ======= Validation
            ////
            ////            if (SS != 0  && lep1IsoPassV && lep2IsoPassV) { // Validation
            ////                hists_1d.at(categories.at(zeroJet)).back()->Fill(vbf_var1,  weight);
            ////            }
            //
            //
            //            //            ################################################################################
            //            //            ################    Estimate QCD Norm
            //            //            ################################################################################
            //            if (OS != 0 && lep1IsoPassV && !lep2IsoPassV ){ // final analysis
            //                fillQCD_Norm(zeroJet, name, vbf_var1,  weight, frValu2 / (1-frValu2));// final analysis
            //                fillQCD_Norm(zeroJet, name, NN_disc,NN_disc_ZTT,  weight, frValu2 / (1-frValu2));// final analysis
            //            }
            //
            ////             ======= Validation
            //
            ////            if (SS != 0 && !lep1IsoPassV && lep2IsoPassV ){ // Validation with lep1
            ////                fillQCD_Norm(zeroJet, name, vbf_var1,  weight, frValu1 / (1-frValu1));
            ////            }
            ////            if (SS != 0  && lep1IsoPassV && !lep2IsoPassV) { // Validation with lep2
            ////                fillQCD_Norm(zeroJet, name, vbf_var1,  weight, frValu2 / (1-frValu2));
            ////            }
            ////            if (SS != 0 && !lep1IsoPassV && !lep2IsoPassV ){ // Validation with both lep1 and lep2
            ////                fillQCD_Norm(zeroJet, name, vbf_var1,  weight, frValu1*frValu2 / (1-frValu1*frValu2));
            ////            }
            //
            //            //            ################################################################################
            //            //            ################    Estimate QCD Shape
            //            //            ################################################################################
            ////            if (SS != 0 && (!lep1IsoPassV || !lep2IsoPassV )){ // final analysis
            //            if (SS != 0 && lep1IsoPassV && !lep2IsoPassV ){ // final analysis
            //                fillQCD_Shape(zeroJet, name, vbf_var1,  weight, frValu2 / (1-frValu2)); // final analysis
            //                fillQCD_Shape(zeroJet, name, NN_disc,NN_disc_ZTT,  weight, frValu2 / (1-frValu2)); // final analysis
            //            }
            //
            
            // ======= Validation
            //            if (SS != 0 && !lep1IsoPassV && lep2IsoPassV ){ // Validation with lep1
            //                fillQCD_Shape(zeroJet, name, vbf_var1,  weight, frValu1 / (1-frValu1));
            //            }
            //            if (SS != 0 && lep1IsoPassV && !lep2IsoPassV ){ // Validation with lep2
            //                fillQCD_Shape(zeroJet, name, vbf_var1,  weight, frValu2 / (1-frValu2));
            //            }
            //            if (SS != 0 && !lep1IsoPassV && !lep2IsoPassV ){ // Validation with both lep1 and lep2
            //                fillQCD_Shape(zeroJet, name, vbf_var1,  weight, frValu1*frValu2 / (1-frValu1*frValu2));
            //            }
            
            
            
            
            //            if (SS != 0 && (!lep1IsoPassV || !lep2IsoPassV )){ // Validation with lep2
            //            if (SS != 0 && !lep1IsoPassV && lep2IsoPassV ){ // Validation with lep1
            //            if (SS != 0 && !lep1IsoPassV && !lep2IsoPassV ){ // Validation with both lep1 and lep2
            
            //                fillQCD_Shape(zeroJet, name, vbf_var1,  weight, frValu1 / (1-frValu1));
            //                fillQCD_Shape(zeroJet, name, vbf_var1,  weight, frValu1*frValu2 / (1-frValu1*frValu2));
            
            //            if (OS != 0  && lep1IsoPass && lep2IsoPass) {
            //                hists_1d.at(categories.at(zeroJet)).back()->Fill(vbf_var1,  weight);
            //            }
            //
            //            if (SS != 0 && lep1IsoPass && lep2IsoPass ){
            //                fillQCD_Norm(zeroJet, name, vbf_var1,  weight,OSSS[0]);
            //            }
            //
            ////            if (SS != 0  && Pass ){
            //            if (SS != 0){
            //                fillQCD_Shape(zeroJet, name, vbf_var1,  weight,OSSS[0]);
            //            }
            
            
            float NN_sig, NN_ztt, NN_qcd;
            vector<float > NN_out_vec;
            NN_out_vec.clear();
            
            NN_out_vec.push_back((NN_disc > NN_disc_ZTT && NN_disc > NN_disc_QCD )? NN_disc : -1);
            NN_out_vec.push_back((NN_disc_ZTT > NN_disc && NN_disc_ZTT > NN_disc_QCD )? NN_disc_ZTT : -1);
            NN_out_vec.push_back((NN_disc_QCD > NN_disc_ZTT && NN_disc_QCD > NN_disc )? NN_disc_QCD : -1);
            
            
            for (int i =0; i < 3 ;i++) {
                
                if (NN_out_vec[i] < 0 )continue;
                
                if (OS != 0  && lep1IsoPassV && lep2IsoPassV) { // final analysis
                    hists_1d.at(categories.at(i)).back()->Fill(NN_out_vec[i],  weight);
                    //                    hists_1d.at(categories.at(i)).back()->Fill(vbf_var1,  weight);
                    
                    //                    plotFill(name+"_HiggsPt_"+categories.at(i),higgs_pT,20,200,1000,weight);
                    //                    plotFill(name+"_m_sv_"+categories.at(i),m_sv,20,0,400,weight);
                    //                    plotFill(name+"_Met_"+categories.at(i),Met,20,0,400,weight);
                    //                    plotFill(name+"_NN_disc_"+categories.at(i),NN_disc,20,0,1,weight);
                    //                    plotFill(name+"_LeadTauPt_"+categories.at(i),lep1Pt_,20,0,400,weight);
                    //                    plotFill(name+"_SubLeadTauPt_"+categories.at(i),lep2Pt_,20,0,400,weight);
                    //                    plotFill(name+"_LeadJetPt_"+categories.at(i),LeadJetPt,20,0,1000,weight);
                    //                    plotFill(name+"_dR_lep_lep_"+categories.at(i),dR_lep_lep,20,0,4,weight);
                    
                    
                    plotFill(name+"_ZPt_NN_all"+categories.at(i),higgs_pT,20,200,1000,weight);
                    if (NN_out_vec[i] > 0.4 && NN_out_vec[i] < 0.5) plotFill(name+"_ZPt_NN_p4_p5"+categories.at(i),higgs_pT,20,200,1000,weight);
                    if (NN_out_vec[i] > 0.5 && NN_out_vec[i] < 0.6) plotFill(name+"_ZPt_NN_p5_p6"+categories.at(i),higgs_pT,20,200,1000,weight);
                    if (NN_out_vec[i] > 0.6 && NN_out_vec[i] < 0.7) plotFill(name+"_ZPt_NN_p6_p7"+categories.at(i),higgs_pT,20,200,1000,weight);
                    if (NN_out_vec[i] > 0.7 && NN_out_vec[i] < 0.8) plotFill(name+"_ZPt_NN_p7_p8"+categories.at(i),higgs_pT,20,200,1000,weight);
                    if (NN_out_vec[i] > 0.8 && NN_out_vec[i] < 0.9) plotFill(name+"_ZPt_NN_p8_p9"+categories.at(i),higgs_pT,20,200,1000,weight);
                    if (NN_out_vec[i] > 0.9 && NN_out_vec[i] < 1.0) plotFill(name+"_ZPt_NN_p9_p10"+categories.at(i),higgs_pT,20,200,1000,weight);
                    
                    
                    if (runPDF){
                        // pdf scale and uncertainties
                        if (name.find("TT") != string::npos && name.find("_") == string::npos ){
                            for (int j =0; j < pdfSystWeight->size(); j++){
                                float newWeight= pdfSystWeight->at(j)/pdfWeight;
                                if (pdfWeight==0) cout << "pdfWeight   is zero "<<pdfWeight<<"\n";
                                plotFill(name+"___"+categories.at(i)+std::to_string(j),NN_out_vec[i] ,nbin[i],lowBin,highBin,weight*newWeight);
                                
                            }
                        }
                    }
                    
                }
                //            qcd norm
                if (OS != 0 && lep1IsoPassV && !lep2IsoPassV ){ // final analysis qcd
                    fillQCD_Norm(i, name, NN_out_vec[i],  weight, frValu2 / (1-frValu2));
                    //                    fillQCD_Norm(i, name, vbf_var1,  weight, frValu2 / (1-frValu2));
                    fillQCD_Norm_fr_up(i, name, NN_out_vec[i],  weight, frValuUncUp / (1-frValuUncUp));
                    fillQCD_Norm_fr_down(i, name, NN_out_vec[i],  weight, frValuUncDown / (1-frValuUncDown));
                }
                //            qcd shape
                //                if (SS != 0 && lep1IsoPassV && !lep2IsoPassV ){ // final analysis
                if (SS != 0 && !lep2IsoPassV ){ // final analysis
                    fillQCD_Shape(i, name, NN_out_vec[i],  weight, frValu2 / (1-frValu2));
                    //                    fillQCD_Shape(i, name, vbf_var1,  weight, frValu2 / (1-frValu2));
                    fillQCD_Shape_fr_up(i, name, NN_out_vec[i],  weight, frValuUncUp / (1-frValuUncUp));
                    fillQCD_Shape_fr_down(i, name, NN_out_vec[i],  weight, frValuUncDown / (1-frValuUncDown));
                }
            }
            NN_out_vec.clear();
        }
        delete fin;
    }
}
