// ./process_trees_tt -d newBoost_tt_2018_trgData_newcuts  --suf tt_2018_trgData_newcut  -v m_sv -b 30 0 300
// user includes
#include "TStopwatch.h"
#include "TMath.h"
#include "../interface/CLParser.h"
#include "../interface/process_trees_Tot.h"
#include <iomanip>      // std::setprecision




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
//    TH1F * FRhist=(TH1F *) FRFile->Get("numVLoose");
    FR.FRhist=(TH1F *) FRFile->Get("numHistRB");
    TF1 *func = new TF1("fit","pol0",200,500);
    FR.FRhist->Fit("fit","R");
     FR.FitPar= func->GetParameter(0);
     FR.FitParErr= func->GetParError(0);
    cout<<"FitPar = " << FR.FitPar  <<"  FitParErr= " << FR.FitParErr<< "\n";
    
    string channel, tree_name;
    if (dir.find("_tt") != string::npos) {channel ="tt";tree_name="tautau_tree";}
    else (std::cout << "channel is not specificed in the outFile name !\n");
    string newChannelName= channel;
    
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
    auto hists = new HistTool(newChannelName, channel,var_name,  year, suffix, bins);
    
    
    // This part is tro derive the OS/SS ratio (one can actually get the 2D pt/eta binned Values as well)
    //    hists->histoQCD(files, dir, tree_name,  "None");    // fill histograms QCD
    
    //    std::vector<float>  OSSS= hists->Get_OS_SS_ratio();
    //    std::cout<<"\n\n\n\n OSSS  "<<OSSS[0]<<"\n";
    std::vector<float>  OSSS= hists->Get_OS_SS_ratio();
    
    
    
    hists->histoLoop(year, files, dir, FR.FRhist, FR.FitPar, FR.FitParErr,tree_name,var_name,OSSS,0,"");    // fill histograms
    hists->writeTemplates(dir,channel,year);  // write histograms to file
    hists->fout->Close();
    
    std::cout << "Template created.\n Timing Info: \n\t CPU Time: " << watch.CpuTime() << "\n\tReal Time: " << watch.RealTime() << std::endl;
    
    //  delete hists->ff_weight;
}

void HistTool::histoLoop(std::string year , vector<string> files, string dir, TH1F * FRhist, float FitPar, float FitParErr,  string tree_name , string var_name, vector<float> OSSS, bool runPDF,string Sys = "") {

    
    std::cout<< "starting .... "<<dir<<"\n";
    float vbf_var1(0.);
    for (auto ifile : files) {
        
        
        string name = ifile.substr(0, ifile.find(".")).c_str();
        
        auto fin = new TFile((dir + "/" + ifile).c_str(), "read");
        std::cout<<"ifile is openning: " <<ifile<<"\n";
        auto tree = reinterpret_cast<TTree *>(fin->Get(tree_name.c_str()));
        
        
        // do some initialization
        initVectors2d(name);
        fout->cd();
        
        float lep1Pt_=-10;
        float lep2Pt_=-10;
        float vis_mass=-10;
        float LeadJetPt = -10;
        bool lep1IsoPassV, lep2IsoPassV ,OS,SS, lep1IsoPassL, lep2IsoPassL;
        float tmass,ht,st,Met,weight, dR_lep_lep, Metphi;
        float NN_disc,MuMatchedIsolation,EleMatchedIsolation,NN_disc_ZTT,NN_disc_QCD;
        float higgs_pT, higgs_m, m_sv, gen_higgs_pT;
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
        
        // Here we have to call OS/SS method extracter
        std::cout<<" tree->GetEntries() is "<<tree->GetEntries()<<"\n";
        for (auto i = 0; i < tree->GetEntries(); i++) {
            tree->GetEntry(i);
            
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
            
//            if (LeadJetPt > 350) continue;
            
//            if (NN_disc > 0.5) continue; // FIXME to derive the SF for tau
            // apply tau Id SF
//            if (name.find("ZTT")!= string::npos || name.find("TT")!= string::npos || name.find("VV")!= string::npos || name.find("H125")!= string::npos || name.find("JJH125")!= string::npos ) weight *= 0.81;

            // apply tau Id SF
            if (isGenTauLead_ && (  name.find("ZTT")!= string::npos || name.find("TT")!= string::npos || name.find("VV")!= string::npos || name.find("125")!= string::npos || name.find("JJH125")!= string::npos )) weight *= 0.9;
            if (isGenTauSub_ && ( name.find("ZTT")!= string::npos || name.find("TT")!= string::npos || name.find("VV")!= string::npos || name.find("125")!= string::npos || name.find("JJH125")!= string::npos )) weight *= 0.9;

            
            // Validation cuts relaxed!
//            if (m_sv < 50) continue;
//            if (higgs_pT < 100) continue;
//            if (tmass > 200) continue;

            
            float lep1Ptval=lep1Pt_;
            if (lep1Ptval > 200) lep1Ptval=200;
            float frValu1 = FRhist->GetBinContent(FRhist->GetXaxis()->FindBin(lep1Ptval));
            
            
            float lep2Ptval=lep2Pt_;
            if (lep2Ptval > 200) lep2Ptval=200;
            float frValu2 = FRhist->GetBinContent(FRhist->GetXaxis()->FindBin(lep2Ptval));

//p0                        =     0.566429   +/-   0.0729392
//
//****************************************
//Minimizer is Linear / Migrad
//Chi2                      =      11.4832
//NDf                       =            7
//p0                        =      2.09128   +/-   0.223334
//p1                        =  -0.00823976   +/-   0.00166197

//p0                        =     0.585434   +/-   0.371824
//
//****************************************
//****************************************
//Minimizer is Linear / Migrad
//Chi2                      =     0.961271
//NDf                       =            3
//p0                        =     0.585434   +/-   0.371824
//
//****************************************
//Minimizer is Linear / Migrad
//Chi2                      =      5.11415
//NDf                       =            7
//p0                        =      1.11691   +/-   0.118326
//p1                        =  -0.00223231   +/-   0.00156051


            float lep1CorWeight=1;
             if (name.find("Data")== string::npos && year =="2016"){
                if (lep1Pt_ < 200) lep1CorWeight=2.1+ (-0.00824)*lep1Pt_;
                else (lep1CorWeight=0.566);
//                if (lep2Pt_ < 200) lep1CorWeight *= 1.11691+ (-0.00223)*lep2Pt_;
//                else (lep1CorWeight=1.11691+ (-0.00223)*200);
                }
                


//                        if (higgs_pT > 350) continue;
            
            vbf_var1 =ObsName[var_name];
            

            
            
            //            ################################################################################
            //            ################    Fill  data, signal & non QCD Bkg
            //            ################################################################################
            if (OS != 0  && lep1IsoPassV && lep2IsoPassV) { // final analysis
//            if (OS != 0  && lep1IsoPassV) { // final analysis
                hists_1d.at(categories.at(zeroJet)).back()->Fill(vbf_var1,  weight*lep1CorWeight); // final analysis
                hists_2d.at(categories.at(zeroJet)).back()->Fill(lep2IsoPassV,higgs_pT,  weight);
//                hists_2d.at(categories.at(zeroJet)).back()->Fill(NN_disc,NN_disc_ZTT,  weight);
//                Histo_2DMatrix.at(categories.at(zeroJet)).back()->Fill(gen_higgs_pT,higgs_pT,  weight);
            }
            
            
//             ======= Validation

//            if (SS != 0  && lep1IsoPassV && lep2IsoPassV) { // Validation
//                hists_1d.at(categories.at(zeroJet)).back()->Fill(vbf_var1,  weight);
//            }
            
            
            //            ################################################################################
            //            ################    Estimate QCD Norm
            //            ################################################################################
            if (OS != 0 && lep1IsoPassV && !lep2IsoPassV ){ // final analysis
                fillQCD_Norm(zeroJet, name, vbf_var1,  weight*lep1CorWeight, frValu2 / (1-frValu2));// final analysis
//                fillQCD_Norm(zeroJet, name, NN_disc,NN_disc_ZTT,  weight, frValu2 / (1-frValu2));// final analysis
            }
            
//             ======= Validation
            
//            if (SS != 0 && !lep1IsoPassV && lep2IsoPassV ){ // Validation with lep1
//                fillQCD_Norm(zeroJet, name, vbf_var1,  weight, frValu1 / (1-frValu1));
//            }
//            if (SS != 0  && lep1IsoPassV && !lep2IsoPassV) { // Validation with lep2
//                fillQCD_Norm(zeroJet, name, vbf_var1,  weight, frValu2 / (1-frValu2));
//            }
//            if (SS != 0 && !lep1IsoPassV && !lep2IsoPassV ){ // Validation with both lep1 and lep2
//                fillQCD_Norm(zeroJet, name, vbf_var1,  weight, frValu1*frValu2 / (1-frValu1*frValu2));
//            }
            
            //            ################################################################################
            //            ################    Estimate QCD Shape
            //            ################################################################################
            if (SS != 0 && (!lep1IsoPassV || !lep2IsoPassV )){ // final analysis
//            if (SS != 0 && lep1IsoPassV && !lep2IsoPassV ){ // final analysis
                fillQCD_Shape(zeroJet, name, vbf_var1,  weight*lep1CorWeight, frValu2 / (1-frValu2)); // final analysis
//                fillQCD_Shape(zeroJet, name, NN_disc,NN_disc_ZTT,  weight, frValu2 / (1-frValu2)); // final analysis
            }
            
            
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
        }
        delete fin;
    }
}
