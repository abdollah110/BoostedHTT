// ./process_trees_tt -d newBoost_tt_2018_trgData_newcuts  --suf tt_2018_trgData_newcut  -v m_sv -b 30 0 300
// user includes
#include "TStopwatch.h"
#include "TMath.h"
#include "../interface/CLParser.h"
#include "../interface/process_trees_NN_scale.h"
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
    
    TFile * FRFile= new TFile(("data/File_fr_numVLoose_"+year+".root").c_str(),"r");
    TH1F * FRhist=(TH1F *) FRFile->Get("numVLoose");
    
    string channel, tree_name;
    if (dir.find("tt") != string::npos) {channel ="tt";tree_name="tautau_tree";}
    else (std::cout << "channel is not specificed in the outFile name !\n");
    string newChannelName= channel;
    
    myMap1 = new std::map<std::string, TH1F*>();
    
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
    std::vector<float>  OSSS= hists->Get_OS_SS_ratio();
    
    
    
    hists->histoLoop(year, files, dir, FRhist,tree_name,var_name,OSSS,"");    // fill histograms
    hists->writeTemplates(dir,channel,year);  // write histograms to file
    
    map<string, TH1F*>::const_iterator iMap1 = myMap1->begin();
    map<string, TH1F*>::const_iterator jMap1 = myMap1->end();
    for (; iMap1 != jMap1; ++iMap1)
        nplot1(iMap1->first)->Write();
//    outTr->Write();


    hists->fout->Close();
    
    std::cout << "Template created.\n Timing Info: \n\t CPU Time: " << watch.CpuTime() << "\n\tReal Time: " << watch.RealTime() << std::endl;
    
    //  delete hists->ff_weight;
}

void HistTool::histoLoop(std::string year , vector<string> files, string dir, TH1F * FRhist, string tree_name , string var_name, vector<float> OSSS, string Sys = "") {
    
    std::cout<< "starting .... "<<dir<<"\n";
    float vbf_var1(0.);
    
    initVectors1dFake("nominal");
//    initVectors1dFake("up");
//    initVectors1dFake("down");
//    initVectors1dFake("frup");
//    initVectors1dFake("frdown");


    for (auto ifile : files) {
        
        
        string name = ifile.substr(0, ifile.find(".")).c_str();
        
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
   Float_t         pdfWeight;
   vector<float>   *pdfSystWeight;
//   vector<float>   *pdf;
   TBranch        *b_pdfWeight;   //!
   TBranch        *b_pdfSystWeight;   //!
//   TBranch        *b_pdf;   //!




        tree->SetBranchAddress("pdfWeight", &pdfWeight, &b_pdfWeight);
   
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
        tree->SetBranchAddress("pdfSystWeight",&pdfSystWeight);
        
            vector<string> ccc;
            ccc.clear();
            ccc.push_back("_signal");
            ccc.push_back("_ztt");
            ccc.push_back("_qcd");

        // Here we have to call OS/SS method extracter
        std::cout<<" tree->GetEntries() is "<<tree->GetEntries()<<"\n";
        for (auto i = 0; i < tree->GetEntries(); i++) {
            tree->GetEntry(i);
//            cout<<"   i   "<<i<<"\n";
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
            if (name.find("ZTT")!= string::npos || name.find("TT")!= string::npos || name.find("VV")!= string::npos || name.find("H125")!= string::npos || name.find("JJH125")!= string::npos ) weight *= 0.81;
            
            float NN_sig, NN_ztt, NN_qcd;
            vector<float > NN_out_vec;
            NN_out_vec.clear();
            
            
            NN_out_vec.push_back((NN_disc > NN_disc_ZTT && NN_disc > NN_disc_QCD )? NN_disc : -1);
            NN_out_vec.push_back((NN_disc_ZTT > NN_disc && NN_disc_ZTT > NN_disc_QCD )? NN_disc_ZTT : -1);
            NN_out_vec.push_back((NN_disc_QCD > NN_disc_ZTT && NN_disc_QCD > NN_disc )? NN_disc_QCD : -1);

            int nbin[3]={14,3,3};
    
            for (int i =0; i < 3 ;i++) {
            if (NN_out_vec[i] < 0 )continue;
            if (OS != 0  && lep1IsoPassV && lep2IsoPassV) { // final analysis
                hists_1d.at(categories.at(i)).back()->Fill(NN_out_vec[i],  weight);
                
                
                for (int j =0; j < pdfSystWeight->size(); j++){
                float newWeight= pdfSystWeight->at(j)/pdfWeight;
                if (pdfWeight==0) cout << "pdfWeight   is zero "<<pdfWeight<<"\n";
                plotFill(name+"___"+ccc[i]+std::to_string(j),NN_out_vec[i] ,nbin[i],0.3,1,weight*newWeight);
//                plotFill("___SysScaleDenumerator_"+ccc[i]+std::to_string(j),1, nbin[i],0.3,1,newWeight);
        }
        }
        }
            NN_out_vec.clear();
        }
        delete fin;
    }
}
