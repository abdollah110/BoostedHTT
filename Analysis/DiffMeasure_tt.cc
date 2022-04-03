// ./process_trees_tt -d newBoost_tt_2018_trgData_newcuts  --suf tt_2018_trgData_newcut  -v m_sv -b 30 0 300
// user includes
#include "TStopwatch.h"
#include "TMath.h"
#include "../interface/CLParser.h"
#include "../interface/DiffMeasure.h"
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

    TFile * FRFile= new TFile(("data/File_fr_numVLoose_"+year+".root").c_str(),"r");
    TH1F * FRhist=(TH1F *) FRFile->Get("numVLoose");

    string channel, tree_name;
    if (dir.find("_tt") != string::npos) {channel ="tt";tree_name="tautau_tree";}
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
//    hists->histoQCD(files, dir, tree_name,  "None");    // fill histograms QCD
    
//    std::vector<float>  OSSS= hists->Get_OS_SS_ratio();
//    std::cout<<"\n\n\n\n OSSS  "<<OSSS[0]<<"\n";
    std::vector<float>  OSSS= hists->Get_OS_SS_ratio();

    

    hists->histoLoop(year, files, dir, FRhist,tree_name,var_name,OSSS,cut_name, lowVal, highVal,"");    // fill histograms
    hists->writeTemplates(dir,channel,year);  // write histograms to file
    hists->fout->Close();
    
    std::cout << "Template created.\n Timing Info: \n\t CPU Time: " << watch.CpuTime() << "\n\tReal Time: " << watch.RealTime() << std::endl;
    
    //  delete hists->ff_weight;
}

void HistTool::histoLoop(std::string year , vector<string> files, string dir, TH1F * FRhist, string tree_name , string var_name, vector<float> OSSS, string cut_name, float lowVal, float highVal  , string Sys = "") {

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
//                {"gen_higgs_pT",gen_higgs_pT},
                {"gen_higgs_pT",gen_higgs_pT},
                {"Rivet_j1pt",Rivet_j1pt},
                
            };
            
            std::string reco_name="LeadJetPt";
            if (cut_name.find("Rivet_higgsPt") !=string::npos) reco_name="higgs_pT";
            float Var_reco = ObsName[reco_name];
            if (Var_reco < lowVal || Var_reco > highVal ) continue;

            //OutOfAcceptance
            if (name.find("OutsideAcceptance")!=string::npos){
            if (Chan_tautau_fid) continue;
            }

            float Var_cut = ObsName[cut_name];
            
            // Higgs pT parameterization
            if (name.find("0_350")!=string::npos){
                if ( Var_cut > 350 ) continue ;
                if (!Chan_tautau || !Chan_tautau_fid) continue;
            }
            if (name.find("350_450")!=string::npos){
                if ( Var_cut <= 350 || Var_cut > 450 ) continue ;
                if (!Chan_tautau || !Chan_tautau_fid) continue;
            }
            if (name.find("450_600")!=string::npos){
                if ( Var_cut <= 450 || Var_cut > 600 ) continue ;
                if (!Chan_tautau || !Chan_tautau_fid) continue;
            }
            if (name.find("600_800")!=string::npos){
                if ( Var_cut <= 600 || Var_cut > 800 ) continue ;
                if (!Chan_tautau || !Chan_tautau_fid) continue;
            }
            if (name.find("GT800")!=string::npos){
                if ( Var_cut <= 800) continue ;
                if (!Chan_tautau || !Chan_tautau_fid) continue;
            }



//            // Higgs pT parameterization
//            if (name.find("0_350")!=string::npos){
//                if ( Rivet_higgsPt > 350 ) continue ;
//                if (!Chan_tautau || !Chan_tautau_fid) continue;
//            }
//            if (name.find("350_450")!=string::npos){
//                if ( Rivet_higgsPt <= 350 || Rivet_higgsPt > 450 ) continue ;
//                if (!Chan_tautau || !Chan_tautau_fid) continue;
//            }
//            if (name.find("450_600")!=string::npos){
//                if ( Rivet_higgsPt <= 450 || Rivet_higgsPt > 600 ) continue ;
//                if (!Chan_tautau || !Chan_tautau_fid) continue;
//            }
//            if (name.find("600_800")!=string::npos){
//                if ( Rivet_higgsPt <= 600 || Rivet_higgsPt > 800 ) continue ;
//                if (!Chan_tautau || !Chan_tautau_fid) continue;
//            }
//            if (name.find("GT800")!=string::npos){
//                if ( Rivet_higgsPt <= 800) continue ;
//                if (!Chan_tautau || !Chan_tautau_fid) continue;
//            }
            
//            // Lead jet pT parameterization
//            if (name.find("0_350")!=string::npos){
//                if ( Rivet_j1pt > 350 ) continue ;
//                if (!Chan_tautau || !Chan_tautau_fid) continue;
//            }
//            if (name.find("350_450")!=string::npos){
//                if ( Rivet_j1pt <= 350 || Rivet_j1pt > 450 ) continue ;
//                if (!Chan_tautau || !Chan_tautau_fid) continue;
//            }
//            if (name.find("450_600")!=string::npos){
//                if ( Rivet_j1pt <= 450 || Rivet_j1pt > 600 ) continue ;
//                if (!Chan_tautau || !Chan_tautau_fid) continue;
//            }
//            if (name.find("600_800")!=string::npos){
//                if ( Rivet_j1pt <= 600 || Rivet_j1pt > 800 ) continue ;
//                if (!Chan_tautau || !Chan_tautau_fid) continue;
//            }
//            if (name.find("GT800")!=string::npos){
//                if ( Rivet_j1pt <= 800) continue ;
//                if (!Chan_tautau || !Chan_tautau_fid) continue;
//            }




//            if (higgs_pT < 400) continue;
            
//            if (NN_disc < 0.3) continue;
            // apply tau Id SF
            if (name.find("ZTT")!= string::npos || name.find("TT")!= string::npos || name.find("VV")!= string::npos || name.find("125")!= string::npos || name.find("JJH125")!= string::npos ) weight *= 0.81;
            
            float lep2Ptval=lep2Pt_;
            if (lep2Ptval > 200) lep2Ptval=200;
            float frValu2 = FRhist->GetBinContent(FRhist->GetXaxis()->FindBin(lep2Ptval));

//            float lep1Ptval=lep1Pt_;
//            if (lep1Ptval > 200) lep1Ptval=200;
//            float frValu2 = FRhist->GetBinContent(FRhist->GetXaxis()->FindBin(lep1Ptval));


            vbf_var1 =ObsName[var_name];
            
            
            
            if (OS != 0  && lep1IsoPassV && lep2IsoPassV) {
//            if (OS != 0  && lep1IsoPassL && lep2IsoPassL) {
//            if (SS != 0  && lep1IsoPassV && lep2IsoPassV) { // Validation
//            if (SS != 0  && lep1IsoPass && lep2IsoPassV) { // Validation
                hists_1d.at(categories.at(zeroJet)).back()->Fill(vbf_var1,  weight);
            }
            if (OS != 0 && !lep1IsoPassV && lep2IsoPassV ){
//            if (OS != 0 && !lep1IsoPassL && lep2IsoPassL ){
//            if (SS != 0 && lep1IsoPassV && !lep2IsoPassV ){ // Validation
//            if (SS != 0 && !lep1IsoPassV && !lep2IsoPassV ){ // Validation
                fillQCD_Norm(zeroJet, name, vbf_var1,  weight, frValu2 / (1-frValu2));
//                fillQCD_Norm(zeroJet, name, vbf_var1,  weight, frValu*frValu2 / (1-frValu*frValu2));
            }
//            if (SS != 0 && !lep2IsoPassV){
//            if (SS != 0 && !lep2IsoPassV){
            if (SS != 0 && (!lep1IsoPassV || !lep2IsoPassV )){
                fillQCD_Shape(zeroJet, name, vbf_var1,  weight, frValu2 / (1-frValu2));
            }
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
