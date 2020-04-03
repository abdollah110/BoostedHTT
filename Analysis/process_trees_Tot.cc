// Copyright 2018 Tyler Mitchell
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
    string year = parser.Option("-y");
    string suffix = parser.Option("--suf");
    string tree_name = parser.Option("-t");

    std::string var_name = parser.Option("-v");
    std::vector<std::string> sbins = parser.MultiOption("-b", 3);
    
    // get the provided histogram binning
    std::vector<int> bins;
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
    auto hists = new HistTool("mt", year, suffix, bins);
    
    // This part is tro derive the OS/SS ratio (one can actually get the 2D pt/eta binned Values as well)
    hists->histoQCD(files, dir, tree_name,  "None");    // fill histograms QCD
    
    std::vector<float>  OSSS= hists->Get_OS_SS_ratio();
    std::cout<<"\n\n\n\n OSSS  "<<OSSS[0]<<"\n";
    
    hists->histoLoop(year, files, dir, tree_name,var_name,OSSS, "None","");    // fill histograms
    
    std::vector<std::string> ListSys{ "",
        //        "_JetRelBal_Up","_JetRelSam_Up",
        //        "_JetRelBal_Down","_JetRelSam_Down",
        //        "_EEScale_Up","_EEScale_Down","_EESigma_Up","_EESigma_Down","_MES_Up","_MES_Down",
        //        "_JER_Down","_JER_Up","_JetAbsolute_Down","_JetAbsolute_Up","_JetAbsoluteyear_Down","_JetAbsoluteyear_Up",
        //        "_JetEC2_Down","_JetEC2_Up","_JetEC2year_Down","_JetEC2year_Up", "_JetFlavorQCD_Down","_JetFlavorQCD_Up",
        //        "_JetHFyear_Down","_JetHFyear_Up",
        //        "_RecoilReso_Up","_RecoilReso_Down","_RecoilResp_Up","_RecoilResp_Down"
    };
    
    
    hists->writeTemplates();  // write histograms to file
    hists->fout->Close();
    
    std::cout << "Template created.\n Timing Info: \n\t CPU Time: " << watch.CpuTime() << "\n\tReal Time: " << watch.RealTime() << std::endl;
    
    //  delete hists->ff_weight;
}

void HistTool::histoLoop(std::string year , vector<string> files, string dir, string tree_name , string var_name, vector<float> OSSS, string acWeight = "None", string Sys = "") {
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
        
        float mupt_=-10;
        float taupt_=-10;
        float vis_mass=-10;
        float LeadJetPt = -10;
        float dR_Z_jet=-10;
        bool Fail,Pass,PassM,FailM,PassT,FailT,OS,SS,Isolation,AntiIsolation;
        float tmass,ht,st,Met,weight, dR_mu_tau, Metphi;
        float NN_disc;
        float IsoMuValue,BoostedTauRawIso, higgs_pT, higgs_m, m_sv;
        
        
        tree->SetBranchAddress("muPt",&mupt_);
        tree->SetBranchAddress("taupt",&taupt_);
        tree->SetBranchAddress("Pass",&Pass);
        tree->SetBranchAddress("Fail",&Fail);
        tree->SetBranchAddress("OS",&OS);
        tree->SetBranchAddress("SS",&SS);
        tree->SetBranchAddress("lepIso",&Isolation);
//        tree->SetBranchAddress("lepAntiIso",&AntiIsolation);
        tree->SetBranchAddress("vis_mass",&vis_mass);
        tree->SetBranchAddress("tmass",&tmass);
        tree->SetBranchAddress("ht",&ht);
        tree->SetBranchAddress("st",&st);
        tree->SetBranchAddress("Met",&Met);
        tree->SetBranchAddress("LeadJetPt",&LeadJetPt);
        tree->SetBranchAddress("dR_mu_tau",&dR_mu_tau);
        tree->SetBranchAddress("evtwt",&weight);
        tree->SetBranchAddress("NN_disc",&NN_disc);
        tree->SetBranchAddress("IsoMuValue",&IsoMuValue);
        tree->SetBranchAddress("BoostedTauRawIso",&BoostedTauRawIso);
        tree->SetBranchAddress("higgs_pT",&higgs_pT);
        tree->SetBranchAddress("higgs_m",&higgs_m);
        tree->SetBranchAddress("m_sv",&m_sv);

        
        
        
        
        
        
        
        // Here we have to call OS/SS method extracter
        std::cout<<" tree->GetEntries() is "<<tree->GetEntries()<<"\n";
        for (auto i = 0; i < tree->GetEntries(); i++) {
            tree->GetEntry(i);
            
            std::map<std::string, float>  ObsName {
                {"muPt",mupt_},
                {"taupt",taupt_},
                {"Pass",Pass},
                {"lepIso",Isolation},
//                {"lepAntiIso",AntiIsolation},
                {"vis_mass",vis_mass},
                {"tmass",tmass},
                {"ht",ht},
                {"st",st},
                {"Met",Met},
                {"LeadJetPt",LeadJetPt},
                {"dR_mu_tau",dR_mu_tau},
                {"IsoMuValue",IsoMuValue},
                {"BoostedTauRawIso",BoostedTauRawIso},
                {"higgs_pT",higgs_pT},
                {"higgs_m",higgs_m},
                {"m_sv",m_sv},
                {"NN_disc",NN_disc}
            };
            
            
            vbf_var1 =ObsName[var_name];

            if (OS != 0  && Pass) {
                hists_1d.at(categories.at(zeroJet)).back()->Fill(vbf_var1,  weight);
            }

            if (SS != 0 && Pass ){
                fillQCD_Norm(zeroJet, name, vbf_var1,  weight,OSSS[0]);
            }

            if (SS != 0  && Pass ){
                fillQCD_Shape(zeroJet, name, vbf_var1,  weight,OSSS[0]);
            }
        }
        delete fin;
    }
}




void HistTool::histoQCD( vector<string> files, string dir, string tree_name, string acWeight = "None") {
    
    
    
    std::cout<< "starting OS/SS calculation .... "<<dir<<"\n";
    float vbf_var1(0.);
    for (auto ifile : files) {
        
        string name = ifile.substr(0, ifile.find(".")).c_str();
        if (!(name == "W" || name == "ZTT" || name == "VV" || name == "TT" || name == "ZLL" || name == "ZJ" || name == "Data" )) continue;
        auto fin = new TFile((dir + "/" + ifile).c_str(), "read");
        auto tree = reinterpret_cast<TTree *>(fin->Get(tree_name.c_str()));
        
//        float mupt_=-10;
//        float weight=0;
//        bool Pass, Fail;
//        bool OS, SS, AntiIsolation;
        float mupt_=-10;
         bool Fail,Pass,PassM,FailM,PassT,FailT,OS,SS,Isolation,AntiIsolation;
         float weight;
         
        
        tree->SetBranchAddress("muPt",&mupt_);
        tree->SetBranchAddress("Pass",&Pass);
        tree->SetBranchAddress("Fail",&Fail);
        tree->SetBranchAddress("OS",&OS);
        tree->SetBranchAddress("SS",&SS);
        tree->SetBranchAddress("lepIso",&Isolation);
        tree->SetBranchAddress("evtwt",&weight);
        
        for (auto i = 0; i < tree->GetEntries(); i++) {
            tree->GetEntry(i);
            
//            std::cout<<OS <<Pass << !Isolation<<"\n";
            if (OS != 0 && !Pass && !Isolation){
//            if (OS != 0 &&  !Isolation){
//            if (OS != 0 ){
//            std::cout<<name<< " "<<mupt_<<"  " << weight<<"\n";
                fillQCD_OS_CR(zeroJet, name, mupt_,  weight);
            }
            else if (SS != 0 && !Pass && !Isolation){
//            else if (SS != 0  && !Isolation){
//            else if (SS != 0 ){
//            std::cout<<"\t "<<name<< " "<<mupt_<<"  " << weight<<"\n";
                fillQCD_SS_CR(zeroJet, name, mupt_,  weight);
            }
        }
        fin->Close();
        delete fin;
    }
}
