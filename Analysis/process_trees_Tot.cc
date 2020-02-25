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
    
    // get input file directory
    if (dir.empty()) {
        std::cerr << "You must give an input directory" << std::endl;
        return -1;
    }
    
    
    // read all files from input directory
    vector<string> files;
    read_directory(dir, &files);
    
    // initialize histogram holder
    auto hists = new HistTool("mt", year, suffix);
    
    // This part is tro derive the OS/SS ratio (one can actually get the 2D pt/eta binned Values as well)
    hists->histoQCD(files, dir, tree_name, "None");    // fill histograms QCD
    
    std::vector<float>  OSSS= hists->Get_OS_SS_ratio();
    std::cout<<"\n\n\n\n"<<OSSS[0]<<"\n";
    
    hists->histoLoop(year, files, dir, tree_name,OSSS, "None","");    // fill histograms
    
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

void HistTool::histoLoop(std::string year , vector<string> files, string dir, string tree_name , vector<float> OSSS, string acWeight = "None", string Sys = "") {
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
        float ZMass=-10;
        float LeadJetPt = -10;
        float dR_Z_jet=-10;
        bool Fail,Pass,PassM,FailM,PassT,FailT,q_OS,q_SS,Isolation,AntiIsolation;
        float tmass,ht,Met,weight, dR_mu_tau, Metphi;
float NN_disc;
        
        
        
        tree->SetBranchAddress("muPt",&mupt_);
        tree->SetBranchAddress("taupt",&taupt_);
        tree->SetBranchAddress("Pass",&Pass);
        tree->SetBranchAddress("Fail",&Fail);
        tree->SetBranchAddress("q_OS",&q_OS);
        tree->SetBranchAddress("q_SS",&q_SS);
        tree->SetBranchAddress("lepIso",&Isolation);
        tree->SetBranchAddress("lepAntiIso",&AntiIsolation);
        tree->SetBranchAddress("ZMass",&ZMass);
        tree->SetBranchAddress("tmass",&tmass);
        tree->SetBranchAddress("ht",&ht);
        tree->SetBranchAddress("Met",&Met);
        tree->SetBranchAddress("LeadJetPt",&LeadJetPt);
        tree->SetBranchAddress("dR_mu_tau",&dR_mu_tau);
        tree->SetBranchAddress("evtwt",&weight);
        tree->SetBranchAddress("NN_disc",&NN_disc);
        
        
        
        
        
        // Here we have to call OS/SS method extracter
        std::cout<<" tree->GetEntries() is "<<tree->GetEntries()<<"\n";
        for (auto i = 0; i < tree->GetEntries(); i++) {
            tree->GetEntry(i);
            
            vbf_var1 = ZMass;
//            vbf_var1 = NN_disc;
            // fill histograms
            if (q_OS != 0 && Isolation && Pass) {
                    hists_1d.at(categories.at(zeroJet)).back()->Fill(vbf_var1,  weight);
            }
            else if (q_SS != 0 && Isolation  && Pass ){
                    fillQCD_Norm(zeroJet, name, vbf_var1,  weight,OSSS[0]);
            }
            
            else if (q_SS != 0 && !Pass && AntiIsolation){
                    fillQCD_Shape(zeroJet, name, vbf_var1,  weight);
            }
        }
        //        }// this for iteration over weights
        //        fin->Close();
        delete fin;
    }
}




void HistTool::histoQCD( vector<string> files, string dir, string tree_name, string acWeight = "None") {
    
    
    
    std::cout<< "starting qcd .... "<<dir<<"\n";
    float vbf_var1(0.);
    for (auto ifile : files) {

        string name = ifile.substr(0, ifile.find(".")).c_str();
        if (!(name == "W" || name == "ZTT" || name == "VV" || name == "TT" || name == "ZLL" || name == "ZJ" || name == "EWKZ" || name == "Data" )) continue;
        auto fin = new TFile((dir + "/" + ifile).c_str(), "read");
        auto tree = reinterpret_cast<TTree *>(fin->Get(tree_name.c_str()));
        
        
        // do some initialization
        //        initVectors2d(name);
        //        fout->cd();
        
        float mupt_=-10;
        float taupt_=-10;
        float ZMass=-10;
        float LeadJetPt = -10;
        float dR_Z_jet=-10;
        bool Fail,Pass,PassM,FailM,PassT,FailT,q_OS,q_SS,Isolation,AntiIsolation;
        float tmass,ht,Met,weight, dR_mu_tau, Metphi;
        float NN_disc;
        
        
        
        tree->SetBranchAddress("muPt",&mupt_);
        tree->SetBranchAddress("taupt",&taupt_);
        tree->SetBranchAddress("Pass",&Pass);
        tree->SetBranchAddress("Fail",&Fail);
        tree->SetBranchAddress("q_OS",&q_OS);
        tree->SetBranchAddress("q_SS",&q_SS);
        tree->SetBranchAddress("lepIso",&Isolation);
        tree->SetBranchAddress("lepAntiIso",&AntiIsolation);
        tree->SetBranchAddress("ZMass",&ZMass);
        tree->SetBranchAddress("tmass",&tmass);
        tree->SetBranchAddress("ht",&ht);
        tree->SetBranchAddress("Met",&Met);
        tree->SetBranchAddress("LeadJetPt",&LeadJetPt);
        tree->SetBranchAddress("dR_mu_tau",&dR_mu_tau);
        tree->SetBranchAddress("evtwt",&weight);
        tree->SetBranchAddress("NN_disc",&NN_disc);
        
        
        
    
        
        std::cout<<"\t FOR QCD tree->GetEntries() is "<<name << "    -->  "<<tree->GetEntries()<<"\n";
        for (auto i = 0; i < tree->GetEntries(); i++) {
            tree->GetEntry(i);
            vbf_var1 = ZMass;
//            vbf_var1 = NN_disc;
            if (q_OS != 0 && Pass && AntiIsolation){
                    fillQCD_OS_CR(zeroJet, name, vbf_var1,  weight);
            }
            
            else if (q_SS != 0 && Pass && AntiIsolation){

                    fillQCD_SS_CR(zeroJet, name, vbf_var1,  weight);

            }
        }
        fin->Close();
        delete fin;
        
    }
}
