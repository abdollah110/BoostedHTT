// user includes
#include "TStopwatch.h"
#include "TMath.h"
#include "../interface/CLParser.h"
#include "../interface/process_trees_Tot.h"
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
    //    string year = parser.Option("-y");
    string suffix = parser.Option("--suf");
    //    string tree_name = parser.Option("-t");
    //    string channel = parser.Option("-c");
    
    std::string var_name = parser.Option("-v");
    std::vector<std::string> sbins = parser.MultiOption("-b", 3);
    
    
    string year;
    if (dir.find("2016") != string::npos) year ="2016";
    else if (dir.find("2017") != string::npos ) year ="2017";
    else if (dir.find("2018") != string::npos) year ="2018";
    else (std::cout << "Year is not specificed in the outFile name !\n");
    
//    TFile * FRFile= new TFile(("data/File_fr_numVLoose_"+year+".root").c_str(),"r");
//    TH1F * FRhist=(TH1F *) FRFile->Get("numVLoose");
//    TFile * FRFile= new TFile(("data/File_fr_numTight_"+year+".root").c_str(),"r");
//    TH1F * FRhist=(TH1F *) FRFile->Get("numTight");

    TFile * FRFile= new TFile(("data/File_fr_numLoose_"+year+".root").c_str(),"r");
    TH1F * FRhist=(TH1F *) FRFile->Get("numLoose");


    string channel, tree_name;
    if (dir.find("_em_") != string::npos) { channel ="em"; tree_name="emu_tree";}
    else if (dir.find("_et_") != string::npos ) { channel ="et";tree_name="etau_tree";}
    else if (dir.find("_mt_") != string::npos) { channel ="mt";tree_name="mutau_tree";}
    else if (dir.find("_tt_") != string::npos) { channel ="tt";tree_name="tautau_tree";}
    else if (dir.find("_mm_") != string::npos) { channel ="mm";tree_name="mumu_tree";}
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
    auto hists = new HistTool(channel, year, suffix, bins);
    // This part is tro derive the OS/SS ratio (one can actually get the 2D pt/eta binned Values as well)
    hists->histoQCD(files, dir, tree_name,  "None");    // fill histograms QCD
    std::vector<float>  OSSS= hists->Get_OS_SS_ratio();
    std::cout<<"\n\n\n\n OSSS  "<<OSSS[0]<<"\n";
    
    hists->histoLoop(year, files, dir, FRhist,tree_name,var_name,OSSS, "None","");    // fill histograms
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

void HistTool::histoLoop(std::string year , vector<string> files, string dir, TH1F * FRhist, string tree_name , string var_name, vector<float> OSSS, string acWeight = "None", string Sys = "") {
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
        float dR_Z_jet=-10;
        bool lep2IsoPass,lep2IsoPassV, OS,SS,lep1IsoPass,eleIDMVA, lep2IsoPassT,lep2IsoPassL;
        float tmass,ht,st,Met,weight, dR_lep_lep, Metphi;
        float NN_disc;
        float BoostedTauRawIso, higgs_pT, higgs_m, m_sv;
        
        tree->SetBranchAddress("lep1Pt",&lep1Pt_);
        tree->SetBranchAddress("lep2Pt",&lep2Pt_);
        tree->SetBranchAddress("lep1IsoPass",&lep1IsoPass);
        tree->SetBranchAddress("lep2IsoPass",&lep2IsoPass);
        tree->SetBranchAddress("lep2IsoPassV",&lep2IsoPassV);
        tree->SetBranchAddress("lep2IsoPassT",&lep2IsoPassT);
        tree->SetBranchAddress("lep2IsoPass",&lep2IsoPassL);
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
        tree->SetBranchAddress("BoostedTauRawIso",&BoostedTauRawIso);
        tree->SetBranchAddress("higgs_pT",&higgs_pT);
        tree->SetBranchAddress("higgs_m",&higgs_m);
        tree->SetBranchAddress("m_sv",&m_sv);
        
        
        // Here we have to call OS/SS method extracter
        std::cout<<" tree->GetEntries() is "<<tree->GetEntries()<<"\n";
        for (auto i = 0; i < tree->GetEntries(); i++) {
            tree->GetEntry(i);
            
            std::map<std::string, float>  ObsName {
                {"lep1Pt",lep1Pt_},
                {"lep2Pt",lep2Pt_},
                {"lep1IsoPass",lep1IsoPass},
                {"lep2IsoPass",lep2IsoPass},
                {"lep2IsoPassV",lep2IsoPassV},
                {"lep2IsoPassT",lep2IsoPassT},
                {"lep2IsoPassL",lep2IsoPassL},
                {"vis_mass",vis_mass},
                {"tmass",tmass},
                {"ht",ht},
                {"st",st},
                {"Met",Met},
                {"LeadJetPt",LeadJetPt},
                {"dR_lep_lep",dR_lep_lep},
                {"BoostedTauRawIso",BoostedTauRawIso},
                {"higgs_pT",higgs_pT},
                {"higgs_m",higgs_m},
                {"m_sv",m_sv},
                {"NN_disc",NN_disc}
            };
            
            if (higgs_pT < 250) continue;
            if (vis_mass < 20) continue;

            
            float lep2Ptval=lep2Pt_;
            if (lep2Ptval > 200) lep2Ptval=200;
            
            float frValu = FRhist->GetBinContent(FRhist->GetXaxis()->FindBin(lep2Ptval));
//            cout<<"lep2Pt_ = "<<lep2Pt_ <<"  fr ="<<frValu<<"\n";
            vbf_var1 =ObsName[var_name];
            
            if (OS != 0  && lep1IsoPass && lep2IsoPassL) {
//            if (SS != 0  && lep1IsoPass && lep2IsoPassV) { // Validation
//            if (SS != 0  && lep1IsoPass && lep2IsoPassL) { // Validation
                hists_1d.at(categories.at(zeroJet)).back()->Fill(vbf_var1,  weight);
            }
            if (OS != 0 && lep1IsoPass && !lep2IsoPassL ){
//            if (SS != 0 && lep1IsoPass && !lep2IsoPassV ){ // Validation
//            if (SS != 0 && lep1IsoPass && !lep2IsoPassL ){ // Validation
                fillQCD_Norm(zeroJet, name, vbf_var1,  weight, frValu / (1-frValu));
            }
            if (SS != 0 && !lep2IsoPassL){
                fillQCD_Shape(zeroJet, name, vbf_var1,  weight, frValu / (1-frValu));
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
        
        float lep1Pt_=-10;
        float lep2Pt_=-10;
        bool lep2IsoPass,lep2IsoPassV, OS,SS,lep1IsoPass;
        float weight;
        
        
        tree->SetBranchAddress("lep1Pt",&lep1Pt_);
        tree->SetBranchAddress("lep2Pt",&lep2Pt_);
        tree->SetBranchAddress("lep1IsoPass",&lep1IsoPass);
        tree->SetBranchAddress("lep2IsoPass",&lep2IsoPass);
        tree->SetBranchAddress("lep2IsoPassV",&lep2IsoPassV);
        tree->SetBranchAddress("OS",&OS);
        tree->SetBranchAddress("SS",&SS);
        tree->SetBranchAddress("evtwt",&weight);
        
        for (auto i = 0; i < tree->GetEntries(); i++) {
            tree->GetEntry(i);
            
//            if (OS != 0 && !lep2IsoPass && !lep1IsoPass){
//            if (OS != 0 && !lep2IsoPass ){
            if (OS != 0 && !lep2IsoPassV ){
                fillQCD_OS_CR(zeroJet, name, lep1Pt_,  weight);
            }
//            else if (SS != 0 && !lep2IsoPass && !lep1IsoPass){
//            else if (SS != 0 && !lep2IsoPass ){
            else if (SS != 0 && !lep2IsoPassV ){
                fillQCD_SS_CR(zeroJet, name, lep1Pt_,  weight);
            }
        }
        fin->Close();
        delete fin;
    }
}