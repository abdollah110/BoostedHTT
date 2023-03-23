// ./process_trees_tt -d newBoost_tt_2018_trgData_newcuts  --suf tt_2018_trgData_newcut  -v m_sv -b 30 0 300
// user includes
#include "TStopwatch.h"
#include "TMath.h"
#include "../interface/CLParser.h"
//#include "../interface/DiffMeasure.h"
#include "../interface/DiffMeasure_CR.h"
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
    bool runPDF = parser.Flag("-p");
    
    
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
    
    myMap1 = new std::unordered_map<std::string, TH1F*>();
    
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
    auto hists = new HistTool(newChannelName, channel, var_name, year, suffix, binName,bins);

    
    hists->histoLoop(year, files, dir, FR.FRhist, FR.FitPar, FR.FitParErr,tree_name,var_name,cut_name, lowVal, highVal,runPDF,"");    // fill histograms
    hists->writeTemplates(dir,channel,year);  // write histograms to file
    // histograms for pdf and scale
    unordered_map<string, TH1F*>::const_iterator iMap1 = myMap1->begin();
    unordered_map<string, TH1F*>::const_iterator jMap1 = myMap1->end();
    for (; iMap1 != jMap1; ++iMap1)
        nplot1(iMap1->first)->Write();
    //
    hists->fout->Close();
    
    std::cout << "Template created.\n Timing Info: \n\t CPU Time: " << watch.CpuTime() << "\n\tReal Time: " << watch.RealTime() << std::endl;
}

void HistTool::histoLoop(std::string year , vector<string> files, string dir, TH1F * FRhist, float FitPar, float FitParErr, string tree_name , string var_name, string cut_name, float lowVal, float highVal, bool runPDF, string Sys = "") {
    
    std::cout<< "starting .... "<<dir<<"\n";
    initVectors1dFake("nominal");
    initVectors1dFake("up");
    initVectors1dFake("down");
    initVectors1dFake("frup");
    initVectors1dFake("frdown");

    for (auto ifile : files) {
        
        
        string name = ifile.substr(0, ifile.find(".")).c_str();
        if (runPDF && (name.find("TT") ==string::npos || name.find("Up") !=string::npos || name.find("Down") !=string::npos )) continue;
        
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
        float NN_disc,NN_disc_ZTT,NN_disc_QCD;
        float higgs_pT, higgs_m, m_sv, gen_higgs_pT, gen_leadjet_pT;
        bool Chan_emu, Chan_etau, Chan_mutau, Chan_tautau, Chan_emu_fid, Chan_etau_fid, Chan_mutau_fid, Chan_tautau_fid;
        Float_t         pdfWeight=0;
        vector<double>   *pdfSystWeight=0;
        bool isGenTauSub_, isGenTauLead_;
        
        tree->SetBranchAddress("Chan_emu",&Chan_emu);
        tree->SetBranchAddress("Chan_etau",&Chan_etau);
        tree->SetBranchAddress("Chan_mutau",&Chan_mutau);
        tree->SetBranchAddress("Chan_tautau",&Chan_tautau);
        tree->SetBranchAddress("Chan_emu_fid",&Chan_emu_fid);
        tree->SetBranchAddress("Chan_etau_fid",&Chan_etau_fid);
        tree->SetBranchAddress("Chan_mutau_fid",&Chan_mutau_fid);
        tree->SetBranchAddress("Chan_tautau_fid",&Chan_tautau_fid);
        
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
        tree->SetBranchAddress("gen_higgs_pT",&gen_higgs_pT);
        tree->SetBranchAddress("gen_leadjet_pT",&gen_leadjet_pT);
        if (runPDF){
            tree->SetBranchAddress("pdfWeight", &pdfWeight);
            tree->SetBranchAddress("pdfSystWeight",&pdfSystWeight);
        }
        
        int nbin[3]={13,1,1};
        float lowBin=0.35;
        float highBin=1;
        
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
                {"gen_higgs_pT",gen_higgs_pT},
                {"gen_leadjet_pT",gen_leadjet_pT},
                
            };
            
            //            FIXME  this cut is for running the analysis in dr< 0.5
//            if (dR_lep_lep > 0.5) continue;

            std::string reco_name="LeadJetPt";
            if (cut_name.find("gen_higgs_pT") !=string::npos) reco_name="higgs_pT";
            if (cut_name.find("gen_leadjet_pT") !=string::npos) reco_name="LeadJetPt";
            float Var_reco = ObsName[reco_name];
//            if (Var_reco < lowVal || Var_reco > highVal ) continue;
            
            //OutOfAcceptance
            if (name.find("OutsideAcceptance")!=string::npos){
                if (Chan_tautau_fid) continue;
            }
            
            float Var_cut = ObsName[cut_name];
            
            // Higgs pT parameterization
            if (name.find("0_350")!=string::npos){
                if ( Var_cut > 350 ) continue ;
                if (!Chan_tautau || !Chan_tautau_fid) continue;
//                if (!Chan_tautau) continue;
            }
            if (name.find("350_450")!=string::npos){
                if ( Var_cut <= 350 || Var_cut > 450 ) continue ;
                if (!Chan_tautau || !Chan_tautau_fid) continue;
//                if (!Chan_tautau ) continue;
            }
            if (name.find("450_600")!=string::npos){
                if ( Var_cut <= 450 || Var_cut > 600 ) continue ;
                if (!Chan_tautau || !Chan_tautau_fid) continue;
//                if (!Chan_tautau ) continue;
            }
            if (name.find("GT600")!=string::npos){
                if ( Var_cut <= 600) continue ;
                if (!Chan_tautau || !Chan_tautau_fid) continue;
//                if (!Chan_tautau) continue;
            }
            
            // apply tau Id SF
            if (isGenTauLead_ && (  name.find("ZTT")!= string::npos || name.find("TT")!= string::npos || name.find("VV")!= string::npos || name.find("125")!= string::npos || name.find("JJH125")!= string::npos )) weight *= 0.9;
            if (isGenTauSub_ && ( name.find("ZTT")!= string::npos || name.find("TT")!= string::npos || name.find("VV")!= string::npos || name.find("125")!= string::npos || name.find("JJH125")!= string::npos )) weight *= 0.9;
            
//             correction based on the lead lep pt
            float lep1CorWeight=1;
//            if (name.find("Data")== string::npos && year =="2016"){
//                if (lep1Pt_ < 200) lep1CorWeight=2.1+ (-0.00824)*lep1Pt_;
//                else (lep1CorWeight=0.566);
//                //                if (lep2Pt_ < 200) lep1CorWeight *= 1.11691+ (-0.00223)*lep2Pt_;
//                //                else (lep1CorWeight=1.11691+ (-0.00223)*200);
//            }
            weight *=lep1CorWeight;  // FIXME Removed to see the effects
            
            float lep2Ptval=lep2Pt_;
            
            float frValu2 = FRhist->GetBinContent(FRhist->GetXaxis()->FindBin(lep2Ptval));
            float frValuErr = FRhist->GetBinError(FRhist->GetXaxis()->FindBin(lep2Ptval));
            float frValuUncUp=frValu2+frValuErr;
            float frValuUncDown=frValu2-frValuErr;
            if (lep2Ptval > 200) {
                frValu2 = FitPar;
                frValuUncUp=frValu2+ 2*FitParErr + (lep2Ptval-200)*(5*FitParErr)/300;
                frValuUncDown=frValu2- 2*FitParErr - (lep2Ptval-200)*(5*FitParErr)/300;
            }

            
            float NN_sig, NN_ztt, NN_qcd;
            vector<float > NN_out_vec;
            NN_out_vec.clear();
            
            NN_out_vec.push_back((NN_disc > NN_disc_ZTT && NN_disc > NN_disc_QCD )? NN_disc : -1);
            NN_out_vec.push_back((NN_disc_ZTT > NN_disc && NN_disc_ZTT > NN_disc_QCD )? NN_disc_ZTT : -1);
            NN_out_vec.push_back((NN_disc_QCD > NN_disc_ZTT && NN_disc_QCD > NN_disc )? NN_disc_QCD : -1);
            
            
            for (int i =0; i < 3 ;i++) {
                if (NN_out_vec[i] < 0 )continue;
                if (NN_out_vec[0]> 0 && ( Var_reco < lowVal || Var_reco > highVal )) continue; // Only one bin for ztt and QCd CR
                
            // non-qcd norm and shape
            if (OS != 0  && lep1IsoPassV && lep2IsoPassV) {
                hists_1d.at(categories.at(i)).back()->Fill(NN_out_vec[i],  weight);
                if (runPDF){
                    // pdf scale and uncertainties
                    if (name.find("TT") != string::npos && name.find("_") == string::npos ){
                        for (int j =0; j < pdfSystWeight->size(); j++){
                            float newWeight= pdfSystWeight->at(j)/pdfWeight;
                            if (i==0) plotFill(name+"___"+categories.at(i)+std::to_string(j),NN_out_vec[i] , bins_NN.at(0), bins_NN.at(1), bins_NN.at(2) ,weight*newWeight);
                            else
                            plotFill(name+"___"+categories.at(i)+std::to_string(j),NN_out_vec[i] , bins_NN_bkg.at(0), bins_NN_bkg.at(1), bins_NN_bkg.at(2) ,weight*newWeight);

                        }
                    }
                }
            }
            // qcd norm
            if (OS != 0 && lep1IsoPassV && !lep2IsoPassV ){
                fillQCD_Norm(i, name, NN_out_vec[i],  weight, frValu2 / (1-frValu2));
                fillQCD_Norm_fr_up(i, name, NN_out_vec[i],  weight, frValuUncUp / (1-frValuUncUp));
                fillQCD_Norm_fr_down(i, name, NN_out_vec[i],  weight, frValuUncDown / (1-frValuUncDown));
            }
            // qcd shape
            if (SS != 0 && (!lep1IsoPassV || !lep2IsoPassV )){
                fillQCD_Shape(i, name, NN_out_vec[i],  weight, frValu2 / (1-frValu2));
                fillQCD_Shape_fr_up(i, name, NN_out_vec[i],  weight, frValuUncUp / (1-frValuUncUp));
                fillQCD_Shape_fr_down(i, name, NN_out_vec[i],  weight, frValuUncDown / (1-frValuUncDown));
                
            }
        }
        NN_out_vec.clear();
        }
        delete fin;
    }
}
