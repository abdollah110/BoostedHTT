
// system includes
#include <dirent.h>
#include <sys/types.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

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
    HistTool(string, string,string, string, string,std::vector<int>);
    //  ~HistTool() { delete ff_weight; }
    ~HistTool() {  }
    void writeHistos();
    void writeTemplates(string);
    void initVectors2d(string);
    void initSystematics(string);
    
    void fillQCD_Norm(int, string, double, double,float);
    void fillQCD_Shape(int, string, double, double,float);
    void fillQCD_Norm_emu(int, string, double, double,float);
    void fillQCD_Shape_emu(int, string, double, double,float);
    void fillQCD_OS_CR(int, string, double, double);
    void fillQCD_SS_CR(int, string, double, double);
    std::vector<float>  Get_OS_SS_ratio();
    
    //  void convertDataToFake(Categories, string, double, double, double, double, double, double);  // 2d    
    void histoLoop(string year  ,std::vector<string>, string, TH1F *, string, string,std::vector<float>,  string);
    void histoLoop(string year  ,std::vector<string>, string, TH1F *, string, string,std::vector<float>,string, float, float,  string);
//    void histoLoop(string year  ,std::vector<string>, string, TH1F *, string, string, string);
    void histoLoop(string channel, string year  ,std::vector<string>, string, string, string,std::vector<float>, string); //for emu
    void histoLoop(string, string   ,std::vector<string>, string, string, string,std::vector<float>,string, float, float, string); //for emu

    
    void histoQCD(std::vector<string>, string, string, string);
    //  void getJetFakes(std::vector<string>, string, string, bool);
    //    Categories getCategory(std::vector<Float_t>, double, double );
    
    bool doNN, old_selection;
    TFile *fout;
    //  FakeFactor *ff_weight;
    string channel_prefix, tree_name;
    std::vector<string> categories, systematics;
    //    std::vector<float> mvis_bins, njets_bins;
    std::map<string, std::vector<TH1F *>> hists_1d, FF_systs, qcd_AM;
    std::vector<TH1F *> fakes_1d_norm,  fakes_1d_norm_Up,  fakes_1d_norm_Down , data;
    std::vector<TH1F *> fakes_1d_SS_CR, fakes_1d_SS_CR_Up, fakes_1d_SS_CR_Down;
    std::vector<TH1F *> fakes_1d_OS_CR, fakes_1d_OS_CR_Up, fakes_1d_OS_CR_Down;
    std::vector<TH1F *> fakes_1d_shape, fakes_1d_shape_Up, fakes_1d_shape_Down;
    
    // binning
    std::vector<int> bins_NN, bins_FAKE;
    //    std::vector<Float_t> D0_binning_ggH, D0_binning_hvv;
};

// HistTool contructor to create the output file, the qcd histograms with the correct binning
// and the map from categories to vectors of TH1F*'s. Each TH1F* in the vector corresponds to
// one file that is being put into that categories directory in the output tempalte
HistTool::HistTool(string treeName, string channel_prefix, string var, string year, string suffix,std::vector<int> bins)
: fout(new TFile(("Output/templates/" + channel_prefix + year + "_" + var+"_" + suffix + ".root").c_str(), "recreate")),

// x-axis
//bins_NN{0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0}, // This is for 0jet
bins_NN(bins), // This is for 0jet
//bins_NN({20,0,200}),
bins_FAKE({20,0,2000}),
channel_prefix(channel_prefix),
tree_name(treeName),
categories{
    tree_name + "_0jet",
    //    channel_prefix + "_boosted",
    //    channel_prefix + "_vbf",
},
systematics{
    ""
} {
    
    // Create empty histograms for each category to fill later.
    for (auto cat : categories) {
        // make a 2d template
        hists_1d[cat.c_str()] = std::vector<TH1F *>();
        
        if (cat.find("0jet") != string::npos) {
            
            fakes_1d_norm.push_back(new TH1F("fake_0jet", "fake_SS_0", bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
            fakes_1d_norm_Up.push_back(new TH1F("fake_0jet_Up", "fake_SS_0_Up_0", bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
            fakes_1d_norm_Down.push_back(new TH1F("fake_0jet_Down", "fake_SS_0_Down_0", bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
            
            fakes_1d_shape.push_back(new TH1F("fake_0jet_shape", "fake_SS_shape_0", bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
            fakes_1d_shape_Up.push_back(new TH1F("fake_0jet_shape_Up", "fake_SS_shape_0_Up_0", bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
            fakes_1d_shape_Down.push_back(new TH1F("fake_0jet_shape_Down", "fake_SS_shape_0_Down_0", bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
            
            fakes_1d_OS_CR.push_back(new TH1F("OS_CR_0jet", "OS_CR_0jet", bins_FAKE.at(0), bins_FAKE.at(1), bins_FAKE.at(2)));
            fakes_1d_OS_CR_Up.push_back(new TH1F("OS_CR_0jet_Up", "OS_CR_0jet_Up", bins_FAKE.at(0), bins_FAKE.at(1), bins_FAKE.at(2)));
            fakes_1d_OS_CR_Down.push_back(new TH1F("OS_CR_0jet_Down", "OS_CR_0jet_Down", bins_FAKE.at(0), bins_FAKE.at(1), bins_FAKE.at(2)));
            
            fakes_1d_SS_CR.push_back(new TH1F("SS_CR_0jet", "SS_CR_0jet", bins_FAKE.at(0), bins_FAKE.at(1), bins_FAKE.at(2)));
            fakes_1d_SS_CR_Up.push_back(new TH1F("SS_CR_0jet_Up", "SS_CR_0jet_Up", bins_FAKE.at(0), bins_FAKE.at(1), bins_FAKE.at(2)));
            fakes_1d_SS_CR_Down.push_back(new TH1F("SS_CR_0jet_Down", "SS_CR_0jet_Down", bins_FAKE.at(0), bins_FAKE.at(1), bins_FAKE.at(2)));
            
            
        }
        std::cout<<" cat.c_str()= "<<cat.c_str()<<"\n";
        
        //        data.push_back(new TH1F(("data_" + cat).c_str(), ("data_" + cat).c_str(), mvis_bins.size() - 1, &mvis_bins[0], njets_bins.size() - 1, &njets_bins[0]));
    }
    
    // make all of the directories for templates
    for (auto it = hists_1d.begin(); it != hists_1d.end(); it++) {
        fout->cd();
        fout->mkdir((it->first).c_str());
        std::cout <<"\t test 1   first directory is "<<it->first <<"\n";
        fout->cd();
    }
}

// change to the correct output directory then create a new TH1F that will be filled for the current input file
void HistTool::initVectors2d(string name) {
    for (auto key : hists_1d) {
        //                std::cout<<"Now Making  "<<key.first.c_str()<< " on "<<name<<"\n";
        fout->cd(key.first.c_str());
        if (name.find("Data") != string::npos) {
            name = "data_obs";
        }
        if (key.first == tree_name + "_0jet") {
            hists_1d.at(key.first.c_str()).push_back(new TH1F(name.c_str(), name.c_str(), bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
        }
    }
}

// This is CR to extract OS/SS ratio
void HistTool::fillQCD_OS_CR(int cat, string name, double var1,  double weight) {
    //            cout<<"fillQCD_OS_CR    cat ="<<cat <<"   pt= "<<var1 << "  weight= "<<weight<<"\n";
    if (name == "Data") {
        fakes_1d_OS_CR.at(cat)->Fill(var1, 1);
        fakes_1d_OS_CR_Up.at(cat)->Fill(var1, 1);
        fakes_1d_OS_CR_Down.at(cat)->Fill(var1, 1);
        //            } else if (name == "W" || name == "ZTT" || name == "VV" || name == "TT" || name == "ZJ"|| name == "ZLL" || name == "EWKZ" ) {
    } else if (name == "W" || name == "ZTT" || name == "VV" || name == "TT" || name == "EWKZ" ) {
        
        fakes_1d_OS_CR.at(cat)->Fill(var1, -1*weight);
        fakes_1d_OS_CR_Up.at(cat)->Fill(var1, -1*weight*0.9);
        fakes_1d_OS_CR_Down.at(cat)->Fill(var1, -1*weight*1.1);
    }
}
// This is CR to extract OS/SS ratio
void HistTool::fillQCD_SS_CR(int cat, string name, double var1,  double weight) {
    //            cout<<"fillQCD_SS_CR   cat ="<<cat <<"   pt= "<<var1 << "  weight= "<<weight<<"\n";
    if (name == "Data") {
        fakes_1d_SS_CR.at(cat)->Fill(var1, 1);
        fakes_1d_SS_CR_Up.at(cat)->Fill(var1, 1);
        fakes_1d_SS_CR_Down.at(cat)->Fill(var1, 1);
        //            } else if (name == "W" || name == "ZTT" || name == "VV" || name == "TT" || name == "ZJ"|| name == "ZLL" || name == "EWKZ" ) {
    } else if (name == "W" || name == "ZTT" || name == "VV" || name == "TT" ||  name == "EWKZ" ) {
        fakes_1d_SS_CR.at(cat)->Fill(var1, -1*weight);
        fakes_1d_SS_CR_Up.at(cat)->Fill(var1, -1*weight*0.9);
        fakes_1d_SS_CR_Down.at(cat)->Fill(var1, -1*weight*1.1);
    }
}

// This is SS region [need to apply the OS/SS ratio here]
void HistTool::fillQCD_Norm(int cat, string name, double var1,  double weight, float OSSS_val) {
    TH1F *hist;
    if (name == "Data") {
        fakes_1d_norm.at(cat)->Fill(var1, 1*OSSS_val);
        fakes_1d_norm_Up.at(cat)->Fill(var1, 1*OSSS_val);
        fakes_1d_norm_Down.at(cat)->Fill(var1, 1*OSSS_val);
        //            } else if (name == "W" || name == "ZTT" || name == "VV" || name == "TT" || name == "ZJ"|| name == "ZLL" || name == "EWKZ" ) {
//    } else if (name == "W" || name == "ZTT" || name == "VV" || name == "TT"  || name == "EWKZ" ) {
    } else if ( name == "ZTT" || name == "VV" || name == "TT"  || name == "EWKZ" ) {
        fakes_1d_norm.at(cat)->Fill(var1, -1*OSSS_val*weight);
        fakes_1d_norm_Up.at(cat)->Fill(var1, -1*OSSS_val*weight*0.9);
        fakes_1d_norm_Down.at(cat)->Fill(var1, -1*OSSS_val*weight*1.1);
    }
}

void HistTool::fillQCD_Norm_emu(int cat, string name, double var1,  double weight, float OSSS_val) {
    TH1F *hist;
    if (name == "Data") {
        fakes_1d_norm.at(cat)->Fill(var1, 1*OSSS_val);
        fakes_1d_norm_Up.at(cat)->Fill(var1, 1*OSSS_val);
        fakes_1d_norm_Down.at(cat)->Fill(var1, 1*OSSS_val);
        //            } else if (name == "W" || name == "ZTT" || name == "VV" || name == "TT" || name == "ZJ"|| name == "ZLL" || name == "EWKZ" ) {
    } else if (name == "W" || name == "ZTT" || name == "VV" || name == "TT"  || name == "EWKZ" ) {
//    } else if ( name == "ZTT" || name == "VV" || name == "TT"  || name == "EWKZ" ) {
        fakes_1d_norm.at(cat)->Fill(var1, -1*OSSS_val*weight);
        fakes_1d_norm_Up.at(cat)->Fill(var1, -1*OSSS_val*weight*0.9);
        fakes_1d_norm_Down.at(cat)->Fill(var1, -1*OSSS_val*weight*1.1);
    }
}


// This is Loose SS region [To get the shape of QCD from SS and loose region]
void HistTool::fillQCD_Shape(int cat, string name, double var1,  double weight, float OSSS_val) {
    TH1F *hist;
    if (name == "Data") {
        fakes_1d_shape.at(cat)->Fill(var1, 1*OSSS_val);
        fakes_1d_shape_Up.at(cat)->Fill(var1, 1*OSSS_val);
        fakes_1d_shape_Down.at(cat)->Fill(var1, 1*OSSS_val);
        //            } else if (name == "W" || name == "ZTT" || name == "VV" || name == "TT" || name == "ZJ"|| name == "ZLL" || name == "EWKZ" ) {
//    } else if (name == "W" || name == "ZTT" || name == "VV" || name == "TT" || name == "EWKZ" ) {
    } else if ( name == "ZTT" || name == "VV" || name == "TT" || name == "EWKZ" ) {
        
        fakes_1d_shape.at(cat)->Fill(var1, -1*OSSS_val*weight);
        fakes_1d_shape_Up.at(cat)->Fill(var1, -1*OSSS_val*weight*0.9);
        fakes_1d_shape_Down.at(cat)->Fill(var1, -1*OSSS_val*weight*1.1);
    }
}

// This is Loose SS region [To get the shape of QCD from SS and loose region]
void HistTool::fillQCD_Shape_emu(int cat, string name, double var1,  double weight, float OSSS_val) {
    TH1F *hist;
    if (name == "Data") {
        fakes_1d_shape.at(cat)->Fill(var1, 1*OSSS_val);
        fakes_1d_shape_Up.at(cat)->Fill(var1, 1*OSSS_val);
        fakes_1d_shape_Down.at(cat)->Fill(var1, 1*OSSS_val);
        //            } else if (name == "W" || name == "ZTT" || name == "VV" || name == "TT" || name == "ZJ"|| name == "ZLL" || name == "EWKZ" ) {
    } else if (name == "W" || name == "ZTT" || name == "VV" || name == "TT" || name == "EWKZ" ) {
//    } else if ( name == "ZTT" || name == "VV" || name == "TT" || name == "EWKZ" ) {
        
        fakes_1d_shape.at(cat)->Fill(var1, -1*OSSS_val*weight);
        fakes_1d_shape_Up.at(cat)->Fill(var1, -1*OSSS_val*weight*0.9);
        fakes_1d_shape_Down.at(cat)->Fill(var1, -1*OSSS_val*weight*1.1);
    }
}

// Derive OS/SS ratio
std::vector<float>  HistTool::Get_OS_SS_ratio(){
    
    std::vector<float>  os_ss_values;
    os_ss_values.clear();
    
    float OS_SS_0jet = fakes_1d_OS_CR.at(0)->Integral() /  fakes_1d_SS_CR.at(0)->Integral();
    
    cout<<"OS/SS num = "<<fakes_1d_OS_CR.at(0)->Integral() << "  OS/SS denum = "<<fakes_1d_SS_CR.at(0)->Integral() << "\n";
    
    os_ss_values.push_back(OS_SS_0jet);
    
    cout<< "numerator is "<<fakes_1d_OS_CR.at(0)->Integral()  << "   and denumerator is" <<fakes_1d_SS_CR.at(0)->Integral()<<"\n";
    return os_ss_values;
}

// write output histograms including the QCD histograms after scaling by OS/SS ratio
void HistTool::writeTemplates(string dir) {
    auto order(0);
    for (auto cat : hists_1d) {
        fout->cd(cat.first.c_str());
        for (auto hist : cat.second) {
            hist->Write();
        }
        
        auto fake_hist_norm = fakes_1d_norm.at(order);
        auto fake_hist_norm_Up = fakes_1d_norm_Up.at(order);
        auto fake_hist_norm_Down = fakes_1d_norm_Down.at(order);
        auto fake_hist_shape = fakes_1d_shape.at(order);
        auto fake_hist_shape_Up = fakes_1d_shape_Up.at(order);
        auto fake_hist_shape_Down = fakes_1d_shape_Down.at(order);
        
        std::cout<<"\n\n Norm QCD is = "<<fake_hist_norm->Integral() <<   "  shape integral is "<< fake_hist_shape->Integral()  <<"\n";
        fake_hist_shape->Scale(fake_hist_norm->Integral()/fake_hist_shape->Integral());
        fake_hist_shape_Up->Scale(fake_hist_norm_Up->Integral()/fake_hist_shape_Up->Integral());
        fake_hist_shape_Down->Scale(fake_hist_norm_Down->Integral()/fake_hist_shape_Down->Integral());
        
        //========================================================================================================
        //                // ADD protection
        //                for (int i = 0 ; i < fake_hist_shape->GetNbinsX(); i++){
        //                    for (int j = 0 ; j < fake_hist_shape->GetNbinsY(); j++){
        //                        if (fake_hist_shape->GetBinContent(i+1,j+1) <0 ){
        //                            float negBin=fake_hist_shape->GetBinContent(i+1,j+1);
        //                            float totIntegral =fake_hist_shape->Integral();
        //                            fake_hist_shape->SetBinContent(i+1,j+1, 0.0001);
        //                            fake_hist_shape->SetBinError(i+1,j+1, 0.0001);
        //                            std::cout<< cat.first.c_str() << "   QCD bin of "<<i <<"  " <<j<< "  ratio bin/TotIntegral"<< negBin/totIntegral <<"\n";
        //                        }
        //                        if (fake_hist_shape_Up->GetBinContent(i+1,j+1) <0 ){
        //                            fake_hist_shape_Up->SetBinContent(i+1,j+1, 0.0001);
        //                            fake_hist_shape_Up->SetBinError(i+1,j+1, 0.0001);
        //                        }
        //                        if (fake_hist_shape_Down->GetBinContent(i+1,j+1) <0 ){
        //                            fake_hist_shape_Down->SetBinContent(i+1,j+1, 0.0001);
        //                            fake_hist_shape_Down->SetBinError(i+1,j+1, 0.0001);
        //                        }
        //                    }
        //                }
        //========================================================================================================
    // Only make QCD for nominal process and not sys Up/Down
        if (dir.find("Up")==string::npos && dir.find("Down")==string::npos){
            fake_hist_shape->SetName("QCD");
            fake_hist_shape_Up->SetName("QCD_shape_Up");
            fake_hist_shape_Down->SetName("QCD_shape_Down");
//        }
        fake_hist_shape->Write();
        fake_hist_shape_Up->Write();
        fake_hist_shape_Down->Write();
        }
        
        order++;
    }
    
    
}
