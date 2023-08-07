
// system includes
#include <dirent.h>
#include <sys/types.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "makeHisto.h"
#include "TF1.h"

// ROOT includes
#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"
using namespace std;

using std::cout;
using std::string;
using std::vector;
enum Categories { zeroJet,
};

// read all *.root files in the given directory and put them in the provided vector
void read_directory(const string &name, std::vector<string> *v) {
    DIR *dirp = opendir(name.c_str());
    struct dirent *dp;
    while ((dp = readdir(dirp)) != 0) {
        if (static_cast<string>(dp->d_name).find("root") != string::npos) {
            v->push_back(dp->d_name);
        }
    }
    closedir(dirp);
}

// class to hold the histograms until I'm ready to write them
class HistTool {
public:
    HistTool(string,string, string, string, string,string,std::vector<int>);
    //  ~HistTool() { delete ff_weight; }
    ~HistTool() {  }
    void writeHistos();
    void writeTemplates(string,string,string);
    void initVectors1d(string);
    void initVectors1dFake(string);

    void fillQCD_Norm(int, string, double, double,float);
    void fillQCD_Norm_fr_up(int, string, double, double,float);
    void fillQCD_Norm_fr_down(int, string, double, double,float);
    void fillQCD_Shape(int, string, double, double,float);
    void fillQCD_Norm_emu(int, string, double, double,float);
    void fillQCD_Shape_emu(int, string, double, double,float);
    void fillQCD_Shape_fr_up(int, string, double, double,float);
    void fillQCD_Shape_fr_down(int, string, double, double,float);
    void fillQCD_OS_CR(int, string, double, double);
    void fillQCD_SS_CR(int, string, double, double);
    std::vector<float>  Get_OS_SS_ratio();
    
    void histoLoop(string ,std::vector<string>, string, TH1F *, string, string,string, float, float, bool, string); // for lt and tt
    void histoLoop(string  ,std::vector<string>, string, TH1F *,float, float, string, string,string, float, float, bool, string); // for lt and tt
    void histoLoop(string ,std::vector<string>, string,string, string,string, float, float, bool, string); //for emu

    
    void histoQCD(std::vector<string>, string, string, string);
    
    //  void getJetFakes(std::vector<string>, string, string, bool);
    //    Categories getCategory(std::vector<Float_t>, double, double );
    
    bool doNN, old_selection;
    TFile *fout;
    string channel_prefix, tree_name, channel_bin, suffix;
    std::vector<string> categories, systematics;
    //    std::vector<float> mvis_bins, njets_bins;
    std::map<string, std::vector<TH1F *>> hists_1d, FF_systs, qcd_AM;
    
    std::vector<TH1F *> fakes_1d_norm,  fakes_1d_norm_Up,  fakes_1d_norm_Down , data;
    std::vector<TH1F *> fakes_1d_shape, fakes_1d_shape_Up, fakes_1d_shape_Down;
    
    std::map<std::string, std::vector<TH1F *>> hists_FakeNorm_1d, hists_FakeShape_1d;


    std::vector<TH1F *> fakeRateShape_down, fakeRateShape_up, fakeRateNorm_down, fakeRateNorm_up;
    
    // binning
    std::vector<Float_t> bins_NN, bins_FAKE,bins_NN_bkg;
    //    std::vector<Float_t> D0_binning_ggH, D0_binning_hvv;
};

// HistTool contructor to create the output file, the qcd histograms with the correct binning
// and the map from categories to vectors of TH1F*'s. Each TH1F* in the vector corresponds to
// one file that is being put into that categories directory in the output tempalte
//HistTool::HistTool(string treeName,  string var, string year, string suffix,std::vector<float> bins)
HistTool::HistTool(string treeName, string channel_prefix, string var, string year, string suffix, string channel_bin,std::vector<int> bins)
: fout(new TFile(("Output/templates/" + channel_prefix + year + "_" + var+"_" +suffix+"_"+ channel_bin + ".root").c_str(), "recreate")),

// x-axis
//bins_NN(bins),
//bins_NN({7,0.3,1}),
//bins_NN({13,0.35,1}),
bins_NN({5,0.35,1}),
//bins_NN({40,0,1}), // FIXME just for the test
//bins_NN({20,0,1}),
//bins_NN_bkg({3,0.3,1}),
bins_NN_bkg({1,0.35,1}),
//bins_NN_bkg({1,0,1}), // FIXME just for the test
channel_prefix(channel_prefix),
tree_name(treeName),
channel_bin(channel_bin),
categories{
    tree_name + "_signal"+ channel_bin,
    tree_name + "_ztt"+ channel_bin,
    tree_name + "_qcd"+ channel_bin,

//    treeName + channel_bin,
//    channel_prefix + channel_bin,
    //    channel_prefix + "_boosted",
    //    channel_prefix + "_vbf",
},
systematics{
    ""
} {
    // Create empty histograms for each category to fill later.
    for (auto cat : categories) {
        hists_1d[cat.c_str()] = std::vector<TH1F *>();
        hists_FakeNorm_1d[cat.c_str()] = std::vector<TH1F *>();
        hists_FakeShape_1d[cat.c_str()] = std::vector<TH1F *>();
    }
    
    // make all of the directories for templates
    for (auto it = hists_1d.begin(); it != hists_1d.end(); it++) {
        fout->cd();
        fout->mkdir((it->first).c_str());
        fout->cd();
    }
}

// change to the correct output directory then create a new TH1F that will be filled for the current input file
void HistTool::initVectors1d(string name) {
    for (auto key : hists_1d) {
        fout->cd(key.first.c_str());
        if (name.find("Data") != string::npos) {
            name = "data_obs";
        }
        if (key.first == tree_name + "_signal" + channel_bin) {
            hists_1d.at(key.first.c_str()).push_back(new TH1F(name.c_str(), name.c_str(), bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
        }
        if (key.first == tree_name + "_ztt" + channel_bin) {
            hists_1d.at(key.first.c_str()).push_back(new TH1F(name.c_str(), name.c_str(), bins_NN_bkg.at(0), bins_NN_bkg.at(1), bins_NN_bkg.at(2)));
        }
        if (key.first == tree_name + "_qcd" + channel_bin) {
            hists_1d.at(key.first.c_str()).push_back(new TH1F(name.c_str(), name.c_str(), bins_NN_bkg.at(0), bins_NN_bkg.at(1), bins_NN_bkg.at(2)));
        }
    }
}
void HistTool::initVectors1dFake(string type) {
    
    for (auto key : hists_FakeNorm_1d) {
    cout<< " ++++  key.first.c_str() " <<key.first.c_str()<<"\n";
    }
    
    for (auto key : hists_FakeNorm_1d) {
        fout->cd(key.first.c_str());
    std:string name="Newfake_"+type+key.first;
        
        if (key.first == tree_name +"_signal" + channel_bin) {
            hists_FakeNorm_1d.at(key.first.c_str()).push_back(new TH1F((name+"_signal"+ channel_bin).c_str(), (name+"_signal").c_str(), bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
            hists_FakeShape_1d.at(key.first.c_str()).push_back(new TH1F((name+"_shape_signal"+ channel_bin).c_str(), (name+"_shape_signal").c_str(), bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
            
        }
        else if (key.first == tree_name + "_ztt" + channel_bin) {
            hists_FakeNorm_1d.at(key.first.c_str()).push_back(new TH1F((name+"_ztt"+ channel_bin).c_str(), (name+"_ztt").c_str(), bins_NN_bkg.at(0), bins_NN_bkg.at(1), bins_NN_bkg.at(2)));
            hists_FakeShape_1d.at(key.first.c_str()).push_back(new TH1F((name+"_shape_ztt"+ channel_bin).c_str(), (name+"_shape_ztt").c_str(), bins_NN_bkg.at(0), bins_NN_bkg.at(1), bins_NN_bkg.at(2)));
            
        }
        else if (key.first == tree_name + "_qcd" + channel_bin) {
            hists_FakeNorm_1d.at(key.first.c_str()).push_back(new TH1F((name+"_qcd"+ channel_bin).c_str(), (name+"_qcd").c_str(), bins_NN_bkg.at(0), bins_NN_bkg.at(1), bins_NN_bkg.at(2)));
            hists_FakeShape_1d.at(key.first.c_str()).push_back(new TH1F((name+"_shape_qcd"+ channel_bin).c_str(), (name+"_shape_qcd").c_str(), bins_NN_bkg.at(0), bins_NN_bkg.at(1), bins_NN_bkg.at(2)));
            
        }
    }
}


// This is SS region [need to apply the OS/SS ratio here]
void HistTool::fillQCD_Norm(int cat, string name, double var1,  double weight, float OSSS_val) {
    TH1F *hist;
    if (name == "Data") {
        hists_FakeNorm_1d.at(categories.at(cat))[0]->Fill(var1, 1*OSSS_val);
        hists_FakeNorm_1d.at(categories.at(cat))[1]->Fill(var1, 1*OSSS_val);
        hists_FakeNorm_1d.at(categories.at(cat))[2]->Fill(var1, 1*OSSS_val);
    } else if ( name == "ZTT" || name == "VV" || name == "TT"  || name == "EWKZ" ) {
        hists_FakeNorm_1d.at(categories.at(cat))[0]->Fill(var1, -1*OSSS_val*weight);
        hists_FakeNorm_1d.at(categories.at(cat))[1]->Fill(var1, -1*OSSS_val*weight*0.8);
        hists_FakeNorm_1d.at(categories.at(cat))[2]->Fill(var1, -1*OSSS_val*weight*1.2);
    }
}
void HistTool::fillQCD_Norm_fr_up(int cat, string name, double var1,  double weight, float OSSS_val) {
    TH1F *hist;
    if (name == "Data") {
        hists_FakeNorm_1d.at(categories.at(cat))[3]->Fill(var1, 1*OSSS_val);
    } else if ( name == "ZTT" || name == "VV" || name == "TT"  || name == "EWKZ" ) {
        hists_FakeNorm_1d.at(categories.at(cat))[3]->Fill(var1, -1*OSSS_val*weight);
    }
}
void HistTool::fillQCD_Norm_fr_down(int cat, string name, double var1,  double weight, float OSSS_val) {
    TH1F *hist;
    if (name == "Data") {
        hists_FakeNorm_1d.at(categories.at(cat))[4]->Fill(var1, 1*OSSS_val);
    } else if ( name == "ZTT" || name == "VV" || name == "TT"  || name == "EWKZ" ) {
        hists_FakeNorm_1d.at(categories.at(cat))[4]->Fill(var1, -1*OSSS_val*weight);
    }
}
void HistTool::fillQCD_Norm_emu(int cat, string name, double var1,  double weight, float OSSS_val) {
    TH1F *hist;
    if (name == "Data") {
        hists_FakeNorm_1d.at(categories.at(cat))[0]->Fill(var1, 1*OSSS_val);
        hists_FakeNorm_1d.at(categories.at(cat))[1]->Fill(var1, 1*OSSS_val);
        hists_FakeNorm_1d.at(categories.at(cat))[2]->Fill(var1, 1*OSSS_val);
        hists_FakeNorm_1d.at(categories.at(cat))[3]->Fill(var1, 1*OSSS_val);
        hists_FakeNorm_1d.at(categories.at(cat))[4]->Fill(var1, 1*OSSS_val);
    } else if (name == "W" || name == "ZTT" || name == "VV" || name == "TT"  || name == "EWKZ" ) {
        hists_FakeNorm_1d.at(categories.at(cat))[0]->Fill(var1, -1*OSSS_val*weight);
        hists_FakeNorm_1d.at(categories.at(cat))[1]->Fill(var1, -1*OSSS_val*weight*0.8);
        hists_FakeNorm_1d.at(categories.at(cat))[2]->Fill(var1, -1*OSSS_val*weight*1.2);
        hists_FakeNorm_1d.at(categories.at(cat))[3]->Fill(var1, -1*OSSS_val*weight*0.9);
        hists_FakeNorm_1d.at(categories.at(cat))[4]->Fill(var1, -1*OSSS_val*weight*1.1);
    }
}

// This is Loose SS region [To get the shape of QCD from SS and loose region]
void HistTool::fillQCD_Shape(int cat, string name, double var1,  double weight, float OSSS_val) {
    TH1F *hist;
    if (name == "Data" || name == "W") {
        hists_FakeShape_1d.at(categories.at(cat))[0]->Fill(var1, 1*OSSS_val);
        hists_FakeShape_1d.at(categories.at(cat))[1]->Fill(var1, 1*OSSS_val);
        hists_FakeShape_1d.at(categories.at(cat))[2]->Fill(var1, 1*OSSS_val);
    } else if (name == "ZTT" || name == "VV" || name == "TT" || name == "EWKZ" ) {
        (hists_FakeShape_1d.at(categories.at(cat))[0])->Fill(var1, -1*OSSS_val*weight);
        hists_FakeShape_1d.at(categories.at(cat))[1]->Fill(var1, -1*OSSS_val*weight*0.8);
        hists_FakeShape_1d.at(categories.at(cat))[2]->Fill(var1, -1*OSSS_val*weight*1.2);
    }
}
void HistTool::fillQCD_Shape_fr_up(int cat, string name, double var1,  double weight, float OSSS_val) {
    TH1F *hist;
    if (name == "Data" || name == "W") {
        hists_FakeShape_1d.at(categories.at(cat))[3]->Fill(var1, 1*OSSS_val);
    } else if ( name == "ZTT" || name == "VV" || name == "TT" || name == "EWKZ" ) {
        hists_FakeShape_1d.at(categories.at(cat))[3]->Fill(var1, -1*OSSS_val*weight);
    }
}
void HistTool::fillQCD_Shape_fr_down(int cat, string name, double var1,  double weight, float OSSS_val) {
    TH1F *hist;
    if (name == "Data" || name == "W") {
        hists_FakeShape_1d.at(categories.at(cat))[4]->Fill(var1, 1*OSSS_val);
    } else if ( name == "ZTT" || name == "VV" || name == "TT" || name == "EWKZ" ) {
        hists_FakeShape_1d.at(categories.at(cat))[4]->Fill(var1, -1*OSSS_val*weight);
    }
}
// This is Loose SS region [To get the shape of QCD from SS and loose region]
void HistTool::fillQCD_Shape_emu(int cat, string name, double var1,  double weight, float OSSS_val) {
    TH1F *hist;
    if (name == "Data" || name == "W") {
        hists_FakeShape_1d.at(categories.at(cat))[0]->Fill(var1, 1*OSSS_val*weight);
        hists_FakeShape_1d.at(categories.at(cat))[1]->Fill(var1, 1*OSSS_val*weight);
        hists_FakeShape_1d.at(categories.at(cat))[2]->Fill(var1, 1*OSSS_val*weight);
        hists_FakeShape_1d.at(categories.at(cat))[3]->Fill(var1, 1*OSSS_val*weight);
        hists_FakeShape_1d.at(categories.at(cat))[4]->Fill(var1, 1*OSSS_val*weight);
    } else if (name == "ZTT" || name == "VV" || name == "TT" || name == "EWKZ" ) {
        hists_FakeShape_1d.at(categories.at(cat))[0]->Fill(var1, -1*OSSS_val*weight);
        hists_FakeShape_1d.at(categories.at(cat))[1]->Fill(var1, -1*OSSS_val*weight*0.8);
        hists_FakeShape_1d.at(categories.at(cat))[2]->Fill(var1, -1*OSSS_val*weight*1.2);
        hists_FakeShape_1d.at(categories.at(cat))[3]->Fill(var1, -1*OSSS_val*weight*0.9);
        hists_FakeShape_1d.at(categories.at(cat))[4]->Fill(var1, -1*OSSS_val*weight*1.2);
    }
}

// write output histograms including the QCD histograms after scaling by OS/SS ratio
void HistTool::writeTemplates(string dir, string channel, string year) {
    for (auto cat : hists_1d) {
        fout->cd(cat.first.c_str());
        for (auto hist : cat.second) {
            hist->Write();
        }
        
        auto fake_hist_norm = hists_FakeNorm_1d.at(cat.first.c_str())[0];
        auto fake_hist_norm_Up = hists_FakeNorm_1d.at(cat.first.c_str())[1];
        auto fake_hist_norm_Down = hists_FakeNorm_1d.at(cat.first.c_str())[2];
        auto fake_hist_norm_fr_Up = hists_FakeNorm_1d.at(cat.first.c_str())[3];
        auto fake_hist_norm_fr_Down = hists_FakeNorm_1d.at(cat.first.c_str())[4];
        
        auto fake_hist_shape = hists_FakeShape_1d.at(cat.first.c_str())[0];
        auto fake_hist_shape_Up = hists_FakeShape_1d.at(cat.first.c_str())[1];
        auto fake_hist_shape_Down = hists_FakeShape_1d.at(cat.first.c_str())[2];
        auto fake_hist_shape_fr_Up = hists_FakeShape_1d.at(cat.first.c_str())[3];
        auto fake_hist_shape_fr_Down = hists_FakeShape_1d.at(cat.first.c_str())[4];
        

        cout<<fake_hist_norm->Integral()<<"\n";
        cout<<fake_hist_norm_Up->Integral()<<"\n";
        cout<<fake_hist_norm_Down->Integral()<<"\n";
        cout<<fake_hist_norm_fr_Up->Integral()<<"\n";
        cout<<fake_hist_norm_fr_Down->Integral()<<"\n";
        
        cout<<fake_hist_shape->Integral()<<"\n";
        cout<<fake_hist_shape_Up->Integral()<<"\n";
        cout<<fake_hist_shape_Down->Integral()<<"\n";
        cout<<fake_hist_shape_fr_Up->Integral()<<"\n";
        cout<<fake_hist_shape_fr_Down->Integral()<<"\n";
        

        
        
        
        //========================================================================================================
        // Set back to normalization
        //========================================================================================================
        
        fake_hist_shape->Scale(fake_hist_norm->Integral()/fake_hist_shape->Integral());
        fake_hist_shape_Up->Scale(fake_hist_norm_Up->Integral()/fake_hist_shape_Up->Integral());
        fake_hist_shape_Down->Scale(fake_hist_norm_Down->Integral()/fake_hist_shape_Down->Integral());
        fake_hist_shape_fr_Up->Scale(fake_hist_norm_fr_Up->Integral()/fake_hist_shape_fr_Up->Integral());
        fake_hist_shape_fr_Down->Scale(fake_hist_norm_fr_Down->Integral()/fake_hist_shape_fr_Down->Integral());
        
        //========================================================================================================
        
        TH1F *fake_hist_shape_original= (TH1F*)fake_hist_shape->Clone("QCD_original");
        TH1F *fake_hist_shape_original_up= (TH1F*)fake_hist_shape_Up->Clone("QCD_original_up");
        TH1F *fake_hist_shape_original_down= (TH1F*)fake_hist_shape_Down->Clone("QCD_original_down");
        TH1F *fake_hist_shape_original_fr_up= (TH1F*)fake_hist_shape_fr_Up->Clone("QCD_original_fr_up");
        TH1F *fake_hist_shape_original_fr_down= (TH1F*)fake_hist_shape_fr_Down->Clone("QCD_original_fr_down");
        
        
        //========================================================================================================

        //========================================================================================================
        //                // ADD protection
        float totIntegral =fake_hist_shape->Integral();
//        if (totIntegral< 0){
//
//                for (int i = 0 ; i < fake_hist_shape->GetNbinsX(); i++){
//
//                fake_hist_shape->SetBinContent(i+1, 0.001);
//                fake_hist_shape->SetBinError(i+1, 0.01);
//
//                fake_hist_shape_Up->SetBinContent(i+1, 0.001);
//                fake_hist_shape_Up->SetBinError(i+1, 0.01);
//
//                fake_hist_shape_Down->SetBinContent(i+1, 0.001);
//                fake_hist_shape_Down->SetBinError(i+1, 0.01);
//
//                fake_hist_shape_fr_Up->SetBinContent(i+1, 0.001);
//                fake_hist_shape_fr_Up->SetBinError(i+1, 0.01);
//                fake_hist_shape_fr_Down->SetBinContent(i+1, 0.001);
//                fake_hist_shape_fr_Down->SetBinError(i+1, 0.01);
//        }
//        }
        
        for (int i = 0 ; i < fake_hist_shape->GetNbinsX(); i++){
            
            if (fake_hist_shape->GetBinContent(i+1) <0 ){
                float negBin=fake_hist_shape->GetBinContent(i+1);
                fake_hist_shape->SetBinContent(i+1, 0.001);
                fake_hist_shape->SetBinError(i+1, 0.01);
                std::cout<< cat.first.c_str() << "   QCD bin of "<<i <<"  ratio bin/TotIntegral"<< negBin/totIntegral <<"\n";
            }
            if (fake_hist_shape_Up->GetBinContent(i+1) <0 ){
                fake_hist_shape_Up->SetBinContent(i+1, 0.001);
                fake_hist_shape_Up->SetBinError(i+1, 0.01);
            }
            if (fake_hist_shape_Down->GetBinContent(i+1) <0 ){
                fake_hist_shape_Down->SetBinContent(i+1, 0.001);
                fake_hist_shape_Down->SetBinError(i+1, 0.01);
            }
            if (fake_hist_shape_fr_Up->GetBinContent(i+1) <0 ){
                fake_hist_shape_fr_Up->SetBinContent(i+1, 0.001);
                fake_hist_shape_fr_Up->SetBinError(i+1, 0.01);
            }
            if (fake_hist_shape_fr_Down->GetBinContent(i+1) <0 ){
                fake_hist_shape_fr_Down->SetBinContent(i+1, 0.001);
                fake_hist_shape_fr_Down->SetBinError(i+1, 0.01);
            }
            
        }
        
        cout<<"Before fake_hist_shape_Down fake_hist_norm_Down"<<fake_hist_shape_Down->Integral() <<"  "<<fake_hist_norm_Down->Integral()<<"\n\n";
        
        if (fake_hist_shape_original->Integral() > 0)
            fake_hist_shape->Scale(fake_hist_norm->Integral()/fake_hist_shape->Integral());
        if (fake_hist_shape_original_up->Integral() > 0)
            fake_hist_shape_Up->Scale(fake_hist_norm_Up->Integral()/fake_hist_shape_Up->Integral());
        if (fake_hist_shape_original_down->Integral() > 0)
            fake_hist_shape_Down->Scale(fake_hist_norm_Down->Integral()/fake_hist_shape_Down->Integral());
        if (fake_hist_shape_original_fr_up->Integral() > 0)
            fake_hist_shape_fr_Up->Scale(fake_hist_norm_fr_Up->Integral()/fake_hist_shape_fr_Up->Integral());
        if (fake_hist_shape_original_fr_down->Integral() > 0)
            fake_hist_shape_fr_Down->Scale(fake_hist_norm_fr_Down->Integral()/fake_hist_shape_fr_Down->Integral());

        cout<<"After fake_hist_shape_Down fake_hist_norm_Down"<<fake_hist_shape_Down->Integral() <<"  "<<fake_hist_norm_Down->Integral()<<"\n\n";

//
//        //                // ADD protection
//        for (int i = 0 ; i < fake_hist_shape->GetNbinsX(); i++){
//
//            if (fake_hist_shape->GetBinContent(i+1) <0 ){
//                float negBin=fake_hist_shape->GetBinContent(i+1);
//                float totIntegral =fake_hist_shape->Integral();
//                fake_hist_shape->SetBinContent(i+1, 0.001);
//                fake_hist_shape->SetBinError(i+1, 0.001);
//                std::cout<< cat.first.c_str() << "   QCD bin of "<<i <<"  ratio bin/TotIntegral"<< negBin/totIntegral <<"\n";
//            }
//            if (fake_hist_shape_Up->GetBinContent(i+1) <0 ){
//                fake_hist_shape_Up->SetBinContent(i+1, 0.001);
//                fake_hist_shape_Up->SetBinError(i+1, 0.001);
//            }
//            if (fake_hist_shape_Down->GetBinContent(i+1) <0 ){
//                fake_hist_shape_Down->SetBinContent(i+1, 0.001);
//                fake_hist_shape_Down->SetBinError(i+1, 0.001);
//            }
//            if (fake_hist_shape_fr_Up->GetBinContent(i+1) <0 ){
//                fake_hist_shape_fr_Up->SetBinContent(i+1, 0.001);
//                fake_hist_shape_fr_Up->SetBinError(i+1, 0.001);
//            }
//            if (fake_hist_shape_fr_Down->GetBinContent(i+1) <0 ){
//                fake_hist_shape_fr_Down->SetBinContent(i+1, 0.001);
//                fake_hist_shape_fr_Down->SetBinError(i+1, 0.001);
//            }
//
//        }
//
//        if (fake_hist_shape_original->Integral() > 0)
//            fake_hist_shape->Scale(fake_hist_norm->Integral()/fake_hist_shape->Integral());
//        if (fake_hist_shape_original_up->Integral() > 0)
//            fake_hist_shape_Up->Scale(fake_hist_norm_Up->Integral()/fake_hist_shape_Up->Integral());
//        if (fake_hist_shape_original_down->Integral() > 0)
//            fake_hist_shape_Down->Scale(fake_hist_norm_Down->Integral()/fake_hist_shape_Down->Integral());
//        if (fake_hist_shape_original_fr_up->Integral() > 0)
//            fake_hist_shape_fr_Up->Scale(fake_hist_norm_fr_Up->Integral()/fake_hist_shape_fr_Up->Integral());
//        if (fake_hist_shape_original_fr_down->Integral() > 0)
//            fake_hist_shape_fr_Down->Scale(fake_hist_norm_fr_Down->Integral()/fake_hist_shape_fr_Down->Integral());
        
        std::cout<<"\n\n Norm QCD is = "<<fake_hist_norm->Integral() <<   "  shape integral is "<< fake_hist_shape->Integral()  <<"\n";
        std::cout<<"\n\n fake_hist_shape_Up = "<<fake_hist_shape_Up->Integral() <<"\n";
        std::cout<<"\n\n fake_hist_shape_Down = "<<fake_hist_shape_Down->Integral() <<"\n";
        std::cout<<"\n\n fake_hist_shape_fr_Up = "<<fake_hist_shape_fr_Up->Integral() <<"\n";
        std::cout<<"\n\n fake_hist_shape_fr_Down = "<<fake_hist_shape_fr_Down->Integral() <<"\n";
        
        // Only make QCD for nominal process and not sys Up/Down
        if (dir.find("Up")==string::npos && dir.find("Down")==string::npos){
            fake_hist_shape->SetName("QCD");
            fake_hist_shape_Up->SetName("QCD_shapeYEAR_Up");
            fake_hist_shape_Down->SetName("QCD_shapeYEAR_Down");
            fake_hist_shape_fr_Up->SetName("QCD_fakerateYEAR_Up");
            fake_hist_shape_fr_Down->SetName("QCD_fakerateYEAR_Down");
            
            fake_hist_shape->Write();
            fake_hist_shape_Up->Write();
            fake_hist_shape_Down->Write();
            fake_hist_shape_fr_Up->Write();
            fake_hist_shape_fr_Down->Write();
            fake_hist_shape_original->Write();
            
            
        }
    }
}
