// user includes
#include "TStopwatch.h"
#include "TMath.h"
#include "../interface/CLParser.h"
#include "../interface/DiffMeasure.h"
#include <iomanip>      // std::setprecision


using namespace std;


using std::string;
using std::vector;
int main(int argc, char *argv[]) {
    auto watch = TStopwatch();
    // get CLI arguments
    CLParser parser(argc, argv);
    bool doSyst = parser.Flag("-s");
    string dir = parser.Option("-d");
    string suffix = parser.Option("--suf");
    string binName = parser.Option("--bin");
    std::string var_name = parser.Option("-v");
    std::string cut_name = parser.Option("-c");
    float lowVal= std::stoi(parser.Option("-l"));
    float highVal= std::stoi(parser.Option("-h"));
    std::vector<std::string> sbins = parser.MultiOption("-b", 3);
    
    
    string year;
    if (dir.find("2016") != string::npos) year ="2016";
    else if (dir.find("2017") != string::npos ) year ="2017";
    else if (dir.find("2018") != string::npos) year ="2018";
    else (std::cout << "Year is not specificed in the outFile name !\n");

    string channel, tree_name;
    if (dir.find("_em") != string::npos) { channel ="em"; tree_name="emu_tree";}
    else if (dir.find("_me") != string::npos ) { channel ="me";tree_name="emu_tree";}
    else (std::cout << "channel is not specificed in the outFile name !\n");


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
    auto hists = new HistTool(channel, var_name, year, suffix,binName, bins);
    // This part is tro derive the OS/SS ratio (one can actually get the 2D pt/eta binned Values as well)
//    hists->histoQCD(files,var_name,  dir, tree_name,  "None");    // fill histograms QCD
    hists->histoQCD(files,var_name,  dir, tree_name);    // fill histograms QCD
    std::vector<float>  OSSS= hists->Get_OS_SS_ratio();
    std::cout<<"\n\n\n\n OSSS  "<<OSSS[0]<<"\n";
    
    hists->histoLoop(year, files, dir, tree_name,var_name,OSSS,cut_name, lowVal, highVal,"");    // fill histograms
    hists->writeTemplates(dir,channel,year);  // write histograms to file
    hists->fout->Close();
    
    std::cout << "Template created.\n Timing Info: \n\t CPU Time: " << watch.CpuTime() << "\n\tReal Time: " << watch.RealTime() << std::endl;
    
    //  delete hists->ff_weight;
}
//           void histoLoop(std::string year  ,std::vector<std::string>, std::string, std::string, std::string,std::vector<float>, std::string, std::string);
//void HistTool::histoLoop(std::string year , vector<string> files, string dir, string tree_name , string var_name, vector<float> OSSS, string acWeight = "None", string Sys = "") {
void HistTool::histoLoop(std::string year , vector<string> files, string dir, string tree_name , string var_name, vector<float> OSSS, string cut_name, float lowVal, float highVal ,string Sys = "") {

    
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
        float vis_mass=-10;
        float LeadJetPt = -10;
        float dR_Z_jet=-10;
        bool OS,SS,lep1IsoPass,eleIDMVA, lep2IsoPass;
        float tmass,ht,st,Met,weight, dR_lep_lep, Metphi, lep2Pt_;
        float NN_disc;
        float higgs_pT, higgs_m, m_sv, gen_higgs_pT, Rivet_higgsPt, Rivet_j1pt;
        bool Chan_emu, Chan_etau, Chan_mutau, Chan_tautau, Chan_emu_fid, Chan_etau_fid, Chan_mutau_fid, Chan_tautau_fid;
        tree->SetBranchAddress("Chan_emu",&Chan_emu);
        tree->SetBranchAddress("Chan_etau",&Chan_etau);
        tree->SetBranchAddress("Chan_mutau",&Chan_mutau);
        tree->SetBranchAddress("Chan_tautau",&Chan_tautau);
        tree->SetBranchAddress("Chan_emu_fid",&Chan_emu_fid);
        tree->SetBranchAddress("Chan_etau_fid",&Chan_etau_fid);
        tree->SetBranchAddress("Chan_mutau_fid",&Chan_mutau_fid);
        tree->SetBranchAddress("Chan_tautau_fid",&Chan_tautau_fid);

        tree->SetBranchAddress("lep1Pt",&lep1Pt_);
        tree->SetBranchAddress("lep2Pt",&lep2Pt_);
        tree->SetBranchAddress("OS",&OS);
        tree->SetBranchAddress("SS",&SS);
        tree->SetBranchAddress("lep1IsoPass",&lep1IsoPass);
        tree->SetBranchAddress("lep2IsoPass",&lep2IsoPass);
        tree->SetBranchAddress("vis_mass",&vis_mass);
        tree->SetBranchAddress("tmass",&tmass);
        tree->SetBranchAddress("ht",&ht);
        tree->SetBranchAddress("st",&st);
        tree->SetBranchAddress("Met",&Met);
        tree->SetBranchAddress("LeadJetPt",&LeadJetPt);
        tree->SetBranchAddress("dR_lep_lep",&dR_lep_lep);
        tree->SetBranchAddress("evtwt",&weight);
        tree->SetBranchAddress("NN_disc",&NN_disc);
        tree->SetBranchAddress("higgs_pT",&higgs_pT);
        tree->SetBranchAddress("higgs_m",&higgs_m);
        tree->SetBranchAddress("m_sv",&m_sv);
//        tree->SetBranchAddress("gen_higgs_pT",&gen_higgs_pT);
        
        tree->SetBranchAddress("gen_higgs_pT",&Rivet_higgsPt);
        tree->SetBranchAddress("gen_leadjet_pT",&Rivet_j1pt);
        
        
        
        // Here we have to call OS/SS method extracter
        std::cout<<" tree->GetEntries() is "<<tree->GetEntries()<<"\n";
        for (auto i = 0; i < tree->GetEntries(); i++) {
            tree->GetEntry(i);
            
            std::map<std::string, float>  ObsName {
                {"lep1Pt",lep1Pt_},
                {"lep2Pt",lep2Pt_},
                {"lep1IsoPass",lep1IsoPass},
                {"lep2IsoPass",lep2IsoPass},
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
                {"gen_higgs_pT",gen_higgs_pT},
                {"Rivet_higgsPt",Rivet_higgsPt},
                {"Rivet_j1pt",Rivet_j1pt},
                
            };
            
            float Var_cut = ObsName[cut_name];
            if (Var_cut < lowVal || Var_cut > highVal ) continue;

            //OutOfAcceptance
            if (name.find("OutsideAcceptance")!=string::npos){
            if (Chan_emu_fid) continue;
            }

            // Higgs pT parameterization
            if (name.find("0_350")!=string::npos){
                if ( Var_cut > 350 ) continue ;
                if (!Chan_emu || !Chan_emu_fid) continue;
            }
            if (name.find("350_450")!=string::npos){
                if ( Var_cut <= 350 || Var_cut > 450 ) continue ;
                if (!Chan_emu || !Chan_emu_fid) continue;
            }
            if (name.find("450_600")!=string::npos){
                if ( Var_cut <= 450 || Var_cut > 600 ) continue ;
                if (!Chan_emu || !Chan_emu_fid) continue;
            }
            if (name.find("600_800")!=string::npos){
                if ( Var_cut <= 600 || Var_cut > 800 ) continue ;
                if (!Chan_emu || !Chan_emu_fid) continue;
            }
            if (name.find("GT800")!=string::npos){
                if ( Var_cut <= 800) continue ;
                if (!Chan_emu || !Chan_emu_fid) continue;
            }
            
//            // Lead jet pT parameterization
//            if (name.find("0_350")!=string::npos){
//                if ( Rivet_j1pt > 350 ) continue ;
//                if (!Chan_emu || !Chan_emu_fid) continue;
//            }
//            if (name.find("350_450")!=string::npos){
//                if ( Rivet_j1pt <= 350 || Rivet_j1pt > 450 ) continue ;
//                if (!Chan_emu || !Chan_emu_fid) continue;
//            }
//            if (name.find("450_600")!=string::npos){
//                if ( Rivet_j1pt <= 450 || Rivet_j1pt > 600 ) continue ;
//                if (!Chan_emu || !Chan_emu_fid) continue;
//            }
//            if (name.find("600_800")!=string::npos){
//                if ( Rivet_j1pt <= 600 || Rivet_j1pt > 800 ) continue ;
//                if (!Chan_emu || !Chan_emu_fid) continue;
//            }
//            if (name.find("GT800")!=string::npos){
//                if ( Rivet_j1pt <= 800) continue ;
//                if (!Chan_emu || !Chan_emu_fid) continue;
//            }



//            if (higgs_pT < 400) continue;
            
//            if (NN_disc < 0.3) continue;
            // The OS/SS is measured in a QCD populated CR and it is 2.21 for 2016 and 2017 and 2.3 for 2018. We will simply us 2.2 for all 3 years

            float meausred_OSSS = 2.2;
            if (year.find("2016") != string::npos ) meausred_OSSS=1.81;
            else if (year.find("2017") != string::npos ) meausred_OSSS=2.06;
            else if (year.find("2018") != string::npos ) meausred_OSSS=1.39;
            
            
            
            
            vbf_var1 =ObsName[var_name];

            if (OS != 0  && lep1IsoPass && lep2IsoPass) {
//            if (OS != 0  && lep1IsoPass ) {
                hists_1d.at(categories.at(zeroJet)).back()->Fill(vbf_var1,  weight);
            }

            if (SS != 0 && lep1IsoPass && lep2IsoPass ){
//            if (SS != 0 && lep1IsoPass  ){
                fillQCD_Norm(zeroJet, name, vbf_var1,  weight,meausred_OSSS);
            }

            if (SS != 0 ){
//            if (SS != 0 && lep1IsoPass && lep2IsoPass){
                fillQCD_Shape(zeroJet, name, vbf_var1,  weight,meausred_OSSS);
            }
        }
        delete fin;
    }
}



//hists->histoQCD(files,var_name,  dir, tree_name);    // fill histograms QCD
void HistTool::histoQCD( vector<string> files, string var_name , string dir, string tree_name) {


    std::cout<< "starting OS/SS calculation .... "<<dir<<"\n";
    float vbf_var1(0.);
    for (auto ifile : files) {

        string name = ifile.substr(0, ifile.find(".")).c_str();
        if (!(name == "W" || name == "ZTT" || name == "VV" || name == "TT" || name == "ZLL" || name == "ZJ" || name == "Data" )) continue;
        auto fin = new TFile((dir + "/" + ifile).c_str(), "read");
        auto tree = reinterpret_cast<TTree *>(fin->Get(tree_name.c_str()));

        float lep1Pt_=-10;
        float lepPt2_=-10;
         bool OS,SS,lep1IsoPass,lep2IsoPass;
         float weight;


        tree->SetBranchAddress("lep1Pt",&lep1Pt_);
        tree->SetBranchAddress("lep2Pt",&lepPt2_);
        tree->SetBranchAddress("OS",&OS);
        tree->SetBranchAddress("SS",&SS);
        tree->SetBranchAddress("lep1IsoPass",&lep1IsoPass);
        tree->SetBranchAddress("lep2IsoPass",&lep2IsoPass);
        tree->SetBranchAddress("evtwt",&weight);

        for (auto i = 0; i < tree->GetEntries(); i++) {
            tree->GetEntry(i);

//            if (OS != 0 && !Pass && !lep1IsoPass){
                if (OS != 0 &&  !lep2IsoPass){
//            if (OS != 0 &&  !lep1IsoPass){
//            if (OS != 0 ){
                fillQCD_OS_CR(zeroJet, name, lep1Pt_,  weight);
            }
//            else if (SS != 0 && !Pass && !lep1IsoPass){
            else if (SS != 0 &&  !lep2IsoPass){
//            else if (SS != 0  && !lep1IsoPass){
//            else if (SS != 0 ){
//            std::cout<<"\t "<<name<< " "<<lep1Pt_<<"  " << weight<<"\n";
                fillQCD_SS_CR(zeroJet, name, lep1Pt_,  weight);
            }
        }
        fin->Close();
        delete fin;
    }
}
