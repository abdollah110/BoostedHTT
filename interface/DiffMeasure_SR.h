
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
    void initVectors2d(string);
    void initSystematics(string);

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
    
    //  void convertDataToFake(Categories, string, double, double, double, double, double, double);  // 2d
    void histoLoop(string ,std::vector<string>, string, TH1F *, string, string,std::vector<float>,string, float, float, bool, string); // for lt and tt
    void histoLoop(string  ,std::vector<string>, string, TH1F *,float, float, string, string,std::vector<float>,string, float, float, bool, string); // for lt and tt
    void histoLoop(string ,std::vector<string>, string,string, string,std::vector<float>,string, float, float, bool, string); //for emu

    
    void histoQCD(std::vector<string>, string, string, string);
    //  void getJetFakes(std::vector<string>, string, string, bool);
    //    Categories getCategory(std::vector<Float_t>, double, double );
    
    bool doNN, old_selection;
    TFile *fout;
    //  FakeFactor *ff_weight;
    string channel_prefix, treeName, channel_bin, suffix;
    std::vector<string> categories, systematics;
    //    std::vector<float> mvis_bins, njets_bins;
    std::map<string, std::vector<TH1F *>> hists_1d, FF_systs, qcd_AM;
    std::vector<TH1F *> fakes_1d_norm,  fakes_1d_norm_Up,  fakes_1d_norm_Down , data;
    std::vector<TH1F *> fakes_1d_SS_CR, fakes_1d_SS_CR_Up, fakes_1d_SS_CR_Down;
    std::vector<TH1F *> fakes_1d_OS_CR, fakes_1d_OS_CR_Up, fakes_1d_OS_CR_Down;
    std::vector<TH1F *> fakes_1d_shape, fakes_1d_shape_Up, fakes_1d_shape_Down;
    
    std::vector<TH1F *> fakeRateShape_down, fakeRateShape_up, fakeRateNorm_down, fakeRateNorm_up;
    
    // binning
    std::vector<int> bins_NN, bins_FAKE;
    //    std::vector<Float_t> D0_binning_ggH, D0_binning_hvv;
};

// HistTool contructor to create the output file, the qcd histograms with the correct binning
// and the map from categories to vectors of TH1F*'s. Each TH1F* in the vector corresponds to
// one file that is being put into that categories directory in the output tempalte
//HistTool::HistTool(string treeName,  string var, string year, string suffix,std::vector<float> bins)
HistTool::HistTool(string treeName_, string channel_prefix, string var, string year, string suffix, string channel_bin,std::vector<int> bins)
: fout(new TFile(("Output/templates/" + channel_prefix + year + "_" + var+"_" +suffix+"_"+ channel_bin + ".root").c_str(), "recreate")),

// x-axis
bins_NN(bins),
bins_FAKE({20,0,2000}),
channel_prefix(channel_prefix),
treeName(treeName_),
channel_bin(channel_bin),
categories{
    treeName + channel_bin,
//    channel_prefix + channel_bin,
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
        cout <<"category is "<<cat.c_str() <<"\n";

        fakes_1d_norm.push_back(new TH1F("fake", "fake_SS_0", bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
        fakes_1d_norm_Up.push_back(new TH1F("fake_Up", "fake_SS_0_Up_0", bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
        fakes_1d_norm_Down.push_back(new TH1F("fake_Down", "fake_SS_0_Down_0", bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
        fakeRateNorm_up.push_back(new TH1F("fakeRateNorm_up", "fakeRateNorm_up", bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
        fakeRateNorm_down.push_back(new TH1F("fakeRateNorm_down", "fakeRateNorm_down", bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));


        fakes_1d_shape.push_back(new TH1F("fake_shape", "fake_SS_shape_0", bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
        fakes_1d_shape_Up.push_back(new TH1F("fake_shape_Up", "fake_SS_shape_0_Up_0", bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
        fakes_1d_shape_Down.push_back(new TH1F("fake_shape_Down", "fake_SS_shape_0_Down_0", bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
        fakeRateShape_up.push_back(new TH1F("fakeRateShape_up", "fakeRateShape_up", bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
        fakeRateShape_down.push_back(new TH1F("fakeRateShape_down", "fakeRateShape_down", bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
        
        
        fakes_1d_OS_CR.push_back(new TH1F("OS_CR", "OS_CR", bins_FAKE.at(0), bins_FAKE.at(1), bins_FAKE.at(2)));
        fakes_1d_OS_CR_Up.push_back(new TH1F("OS_CR_Up", "OS_CR_Up", bins_FAKE.at(0), bins_FAKE.at(1), bins_FAKE.at(2)));
        fakes_1d_OS_CR_Down.push_back(new TH1F("OS_CR_Down", "OS_CR_Down", bins_FAKE.at(0), bins_FAKE.at(1), bins_FAKE.at(2)));
        
        fakes_1d_SS_CR.push_back(new TH1F("SS_CR", "SS_CR", bins_FAKE.at(0), bins_FAKE.at(1), bins_FAKE.at(2)));
        fakes_1d_SS_CR_Up.push_back(new TH1F("SS_CR_Up", "SS_CR_Up", bins_FAKE.at(0), bins_FAKE.at(1), bins_FAKE.at(2)));
        fakes_1d_SS_CR_Down.push_back(new TH1F("SS_CR_Down", "SS_CR_Down", bins_FAKE.at(0), bins_FAKE.at(1), bins_FAKE.at(2)));
                
        std::cout<<" cat.c_str()= "<<cat.c_str()<<"\n";
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
        if (key.first == treeName + channel_bin) {
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
void HistTool::fillQCD_Norm_fr_up(int cat, string name, double var1,  double weight, float OSSS_val) {
    TH1F *hist;
    if (name == "Data") {
        fakeRateNorm_up.at(cat)->Fill(var1, 1*OSSS_val);
    } else if ( name == "ZTT" || name == "VV" || name == "TT"  || name == "EWKZ" ) {
        fakeRateNorm_up.at(cat)->Fill(var1, -1*OSSS_val*weight);
    }
}
void HistTool::fillQCD_Norm_fr_down(int cat, string name, double var1,  double weight, float OSSS_val) {
    TH1F *hist;
    if (name == "Data") {
        fakeRateNorm_down.at(cat)->Fill(var1, 1*OSSS_val);
    } else if ( name == "ZTT" || name == "VV" || name == "TT"  || name == "EWKZ" ) {
        fakeRateNorm_down.at(cat)->Fill(var1, -1*OSSS_val*weight);
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

void HistTool::fillQCD_Shape_fr_up(int cat, string name, double var1,  double weight, float OSSS_val) {
    TH1F *hist;
    if (name == "Data") {
        fakeRateShape_up.at(cat)->Fill(var1, 1*OSSS_val);
    } else if ( name == "ZTT" || name == "VV" || name == "TT" || name == "EWKZ" ) {
        fakeRateShape_up.at(cat)->Fill(var1, -1*OSSS_val*weight);// this is fixed on Aug 25 (*weight was missing)
    }
}
void HistTool::fillQCD_Shape_fr_down(int cat, string name, double var1,  double weight, float OSSS_val) {
    TH1F *hist;
    if (name == "Data") {
        fakeRateShape_down.at(cat)->Fill(var1, 1*OSSS_val);
    } else if ( name == "ZTT" || name == "VV" || name == "TT" || name == "EWKZ" ) {
        fakeRateShape_down.at(cat)->Fill(var1, -1*OSSS_val*weight);// this is fixed on Aug 25 (*weight was missing)
    }
}

// for the emu
void HistTool::fillQCD_Norm_emu(int cat, string name, double var1,  double weight, float OSSS_val) {
    TH1F *hist;
    if (name == "Data") {
        fakes_1d_norm.at(cat)->Fill(var1, 1*OSSS_val);
        fakes_1d_norm_Up.at(cat)->Fill(var1, 1*OSSS_val);
        fakes_1d_norm_Down.at(cat)->Fill(var1, 1*OSSS_val);
//        hists_FakeNorm_1d.at(categories.at(cat))[3]->Fill(var1, 1*OSSS_val);
//        hists_FakeNorm_1d.at(categories.at(cat))[4]->Fill(var1, 1*OSSS_val);
    } else if (name == "W" || name == "ZTT" || name == "VV" || name == "TT"  || name == "EWKZ" ) {
        //            } else if ( name == "ZTT" || name == "VV" || name == "TT"  || name == "EWKZ" ) { // bug found in January 2023 W should be excluded
        fakes_1d_norm.at(cat)->Fill(var1, -1*OSSS_val*weight);
        fakes_1d_norm_Up.at(cat)->Fill(var1, -1*OSSS_val*weight*0.8);
        fakes_1d_norm_Down.at(cat)->Fill(var1, -1*OSSS_val*weight*1.2);
//        hists_FakeNorm_1d.at(categories.at(cat))[3]->Fill(var1, -1*OSSS_val*weight*0.9);
//        hists_FakeNorm_1d.at(categories.at(cat))[4]->Fill(var1, -1*OSSS_val*weight*1.1);
    }
}

// This is Loose SS region [To get the shape of QCD from SS and loose region]
void HistTool::fillQCD_Shape_emu(int cat, string name, double var1,  double weight, float OSSS_val) {
    TH1F *hist;
    if (name == "Data" || name == "W") {
        fakes_1d_shape.at(cat)->Fill(var1, 1*OSSS_val*weight);
        fakes_1d_shape_Up.at(cat)->Fill(var1, 1*OSSS_val*weight);
        fakes_1d_shape_Down.at(cat)->Fill(var1, 1*OSSS_val*weight);
//        hists_FakeShape_1d.at(categories.at(cat))[3]->Fill(var1, 1*OSSS_val*weight);
//        hists_FakeShape_1d.at(categories.at(cat))[4]->Fill(var1, 1*OSSS_val*weight);
        //    } else if ( name == "VV" || name == "TT" || name == "EWKZ" ) {
    } else if (name == "ZTT" || name == "VV" || name == "TT" || name == "EWKZ" ) {
        
        //        fakes_1d_shape.at(cat)->Fill(var1, -1*OSSS_val);
        //        fakes_1d_shape_Up.at(cat)->Fill(var1, -1*OSSS_val*0.9);
        //        fakes_1d_shape_Down.at(cat)->Fill(var1, -1*OSSS_val*1.1); // these are buggy
        fakes_1d_shape.at(cat)->Fill(var1, -1*OSSS_val*weight);
        fakes_1d_shape_Up.at(cat)->Fill(var1, -1*OSSS_val*weight*0.8);
        fakes_1d_shape_Down.at(cat)->Fill(var1, -1*OSSS_val*weight*1.2);
//        hists_FakeShape_1d.at(categories.at(cat))[3]->Fill(var1, -1*OSSS_val*weight*0.9);
//        hists_FakeShape_1d.at(categories.at(cat))[4]->Fill(var1, -1*OSSS_val*weight*1.2);
    }
}


// Derive OS/SS ratio
std::vector<float>  HistTool::Get_OS_SS_ratio(){
    
    std::vector<float>  os_ss_values;
    os_ss_values.clear();
    
    float OS_SS = fakes_1d_OS_CR.at(0)->Integral() /  fakes_1d_SS_CR.at(0)->Integral();
    
    cout<<"OS/SS num = "<<fakes_1d_OS_CR.at(0)->Integral() << "  OS/SS denum = "<<fakes_1d_SS_CR.at(0)->Integral() << "\n";
    
    os_ss_values.push_back(OS_SS);
    
    cout<< "numerator is "<<fakes_1d_OS_CR.at(0)->Integral()  << "   and denumerator is" <<fakes_1d_SS_CR.at(0)->Integral()<<"\n";
    return os_ss_values;
}

// write output histograms including the QCD histograms after scaling by OS/SS ratio
void HistTool::writeTemplates(string dir, string channel, string year) {
    auto order(0);
    for (auto cat : hists_1d) {
        fout->cd(cat.first.c_str());
        for (auto hist : cat.second) {
            hist->Write();
        }
        
        auto fake_hist_norm = fakes_1d_norm.at(order);
        auto fake_hist_norm_Up = fakes_1d_norm_Up.at(order);
        auto fake_hist_norm_Down = fakes_1d_norm_Down.at(order);
        auto hist_fakeRateNorm_up = fakeRateNorm_up.at(order);
        auto hist_fakeRateNorm_down = fakeRateNorm_down.at(order);
        
        auto fake_hist_shape = fakes_1d_shape.at(order);
        auto fake_hist_shape_Up = fakes_1d_shape_Up.at(order);
        auto fake_hist_shape_Down = fakes_1d_shape_Down.at(order);
        auto hist_fakeRateShape_up = fakeRateShape_up.at(order);
        auto hist_fakeRateShape_down = fakeRateShape_down.at(order);
        
        
        std::cout<<"\n\n Norm QCD is = "<<fake_hist_norm->Integral() <<   "  shape integral is "<< fake_hist_shape->Integral()  <<"\n";
        fake_hist_shape->Scale(fake_hist_norm->Integral()/fake_hist_shape->Integral());
        fake_hist_shape_Up->Scale(fake_hist_norm_Up->Integral()/fake_hist_shape_Up->Integral());
        fake_hist_shape_Down->Scale(fake_hist_norm_Down->Integral()/fake_hist_shape_Down->Integral());
        hist_fakeRateShape_up->Scale(hist_fakeRateNorm_up->Integral()/hist_fakeRateShape_up->Integral());
        hist_fakeRateShape_down->Scale(hist_fakeRateNorm_down->Integral()/hist_fakeRateShape_down->Integral());
        //========================================================================================================
        //                // ADD protection
        for (int i = 0 ; i < fake_hist_shape->GetNbinsX(); i++){
            if (fake_hist_shape->GetBinContent(i+1) <0 ){
                float negBin=fake_hist_shape->GetBinContent(i+1);
                float totIntegral =fake_hist_shape->Integral();
                fake_hist_shape->SetBinContent(i+1, 0.0001);
                fake_hist_shape->SetBinError(i+1, 0.1);
                std::cout<< cat.first.c_str() << "   QCD bin of "<<i <<"  ratio bin/TotIntegral"<< negBin/totIntegral <<"\n";
            }
            if (fake_hist_shape_Up->GetBinContent(i+1) <0 ){
                fake_hist_shape_Up->SetBinContent(i+1, 0.0001);
                fake_hist_shape_Up->SetBinError(i+1, 0.1);
            }
            if (fake_hist_shape_Down->GetBinContent(i+1) <0 ){
                fake_hist_shape_Down->SetBinContent(i+1, 0.0001);
                fake_hist_shape_Down->SetBinError(i+1, 0.1);
            }
            if (hist_fakeRateShape_up->GetBinContent(i+1) <0 ){
                hist_fakeRateShape_up->SetBinContent(i+1, 0.0001);
                hist_fakeRateShape_up->SetBinError(i+1, 0.1);
            }
            if (hist_fakeRateShape_down->GetBinContent(i+1) <0 ){
                hist_fakeRateShape_down->SetBinContent(i+1, 0.0001);
                hist_fakeRateShape_down->SetBinError(i+1, 0.1);
            }
        }
        //========================================================================================================
        
        if (dir.find("Up")==string::npos && dir.find("Down")==string::npos){
            fake_hist_shape->SetName("QCD");
            fake_hist_shape_Up->SetName("QCD_shape_Up");
            fake_hist_shape_Down->SetName("QCD_shape_Down");
            hist_fakeRateShape_up->SetName("QCD_fakerateYEAR_Up");
            hist_fakeRateShape_down->SetName("QCD_fakerateYEAR_Down");
            fake_hist_shape->Write();
            fake_hist_shape_Up->Write();
            fake_hist_shape_Down->Write();
            hist_fakeRateShape_up->Write();
            hist_fakeRateShape_down->Write();
            
            }
        
        order++;
    }
    
    
}
