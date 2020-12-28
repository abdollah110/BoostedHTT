#include <string>
#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include "boost/algorithm/string/predicate.hpp"
#include "boost/program_options.hpp"
#include "boost/lexical_cast.hpp"
#include "boost/regex.hpp"
#include "boost/filesystem.hpp"
#include "CombineHarvester/CombineTools/interface/CombineHarvester.h"
#include "CombineHarvester/CombineTools/interface/Utilities.h"
#include "CombineHarvester/CombineTools/interface/HttSystematics.h"
#include "CombineHarvester/CombineTools/interface/CardWriter.h"
#include "CombineHarvester/CombineTools/interface/CopyTools.h"
#include "CombineHarvester/CombineTools/interface/BinByBin.h"
#include "CombineHarvester/CombineTools/interface/Systematics.h"

namespace po = boost::program_options;
using boost::starts_with;
using namespace std;

int main(int argc, char** argv) {

    string postfix="";
    string prefix="";
    string year = "2016";
    string inputFile="";
    string WP="WP";
    string Var="NN";
    po::variables_map vm;
    po::options_description config("configuration");
    config.add_options()
//    ("mass,m", po::value<string>(&mass)->default_value(mass))
//      ("input_folder_em", po::value<string>(&input_folder_em)->default_value("USCMS"))
//      ("input_folder_et", po::value<string>(&input_folder_et)->default_value("USCMS"))
//      ("input_folder_mt", po::value<string>(&input_folder_mt)->default_value("USCMS"))
//      ("input_folder_tt", po::value<string>(&input_folder_tt)->default_value("USCMS"))
//      ("input_folder_mm", po::value<string>(&input_folder_mm)->default_value("USCMS"))
//      ("input_folder_ttbar", po::value<string>(&input_folder_ttbar)->default_value("USCMS"))
      ("prefix", po::value<string>(&prefix)->default_value(""))
      ("postfix", po::value<string>(&postfix)->default_value(""))
      ("Var", po::value<string>(&Var)->default_value(""))
//      ("vbfcateStr_tt", po::value<string>(&vbfcateStr_tt)->default_value("tt_vbf_ggHMELA_bin"))
//      ("vbfcateStr_mt", po::value<string>(&vbfcateStr_mt)->default_value("mt_vbf_ggHMELA_bin"))
//      ("auto_rebin", po::value<bool>(&auto_rebin)->default_value(false))
//      ("real_data", po::value<bool>(&real_data)->default_value(false))
//      ("manual_rebin", po::value<bool>(&manual_rebin)->default_value(false))
//      ("output_folder", po::value<string>(&output_folder)->default_value("sm_run2"))
//      ("SM125,h", po::value<string>(&SM125)->default_value(SM125))
//      ("control_region", po::value<int>(&control_region)->default_value(0))
      ("year", po::value<string>(&year)->default_value("2016"))
      ("WP", po::value<string>(&WP)->default_value(""))
      ("inputFile", po::value<string>(&inputFile)->default_value(""));
//      ("mm_fit", po::value<bool>(&mm_fit)->default_value(true))
//      ("ttbar_fit", po::value<bool>(&ttbar_fit)->default_value(true))
//      ("jetfakes", po::value<bool>(&do_jetfakes)->default_value(false))
//      ("embedded", po::value<bool>(&do_embedded)->default_value(false))
//      ("shapeSyst", po::value<bool>(&do_shapeSyst)->default_value(false))
//      ("sync", po::value<bool>(&do_sync)->default_value(false))
//      ("useSingleVBFdir", po::value<bool>(&useSingleVBFdir)->default_value(false))
//      ("chn", po::value<string>(&do_chn)->default_value("tt"))
//      ("par", po::value<string>(&par)->default_value("fa3"))
//      ("is2017", po::value<bool>(&is_2017)->default_value(false))
//      ("use_ggHint", po::value<bool>(&use_ggHint)->default_value(false))
//      ("check_neg_bins", po::value<bool>(&check_neg_bins)->default_value(false))
//      ("poisson_bbb", po::value<bool>(&poisson_bbb)->default_value(false))
//      ("w_weighting", po::value<bool>(&do_w_weighting)->default_value(false));
    po::store(po::command_line_parser(argc, argv).options(config).run(), vm);
    po::notify(vm);








    //! [part1]
    // First define the location of the "auxiliaries" directory where we can
    // source the input files containing the datacard shapes
//    string aux_shapes = string(getenv("CMSSW_BASE")) + "/src/auxiliaries/shapes/";
    string aux_shapes = string(getenv("CMSSW_BASE")) + "/src/CombineHarvester/CombineTools/bin/aux/";
    
    // Create an empty CombineHarvester instance that will hold all of the
    // datacard configuration and histograms etc.
    ch::CombineHarvester cb;
    
    typedef vector<pair<int, string>> Categories;
    typedef vector<string> VString;
    // Uncomment this next line to see a *lot* of debug information
    // cb.SetVerbosity(3);
    
    // Here we will just define two categories for an 8TeV analysis. Each entry in
    // the vector below specifies a bin name and corresponding bin_id.
    
    VString chns = { "mt","et","em"};
    
    map<string, string> input_folders = {
        {"mt", "."},
        {"et", "."},
        {"em", "."}
    };
    
    map<string, VString> bkg_procs;
    bkg_procs["mt"] = {"W", "QCD", "TT","VV","ZTT"};
    bkg_procs["et"] = {"W", "QCD", "TT","VV","ZTT"};
    bkg_procs["em"] = {"W", "TT","VV","ZTT"};
    
    VString sig_procs = {"JJH"};
    
    map<string, Categories> cats;
    //cats["et_13TeV"] = {
    //      {1, "EleTau_DiJet"}};
    

    cats["mt_13TeV"] = {
        {1, "mt_0jet"},
//        {2, "fail"}
    };
    cats["et_13TeV"] = {
        {1, "et_0jet"},
//        {2, "fail"}
    };
    cats["em_13TeV"] = {
        {1, "em_0jet"},
//        {2, "fail"}
    };
    
    
    // ch::Categories is just a typedef of vector<pair<int, string>>
    //! [part1]
    
    
    //! [part2]
    //    vector<string> masses = ch::MassesFromRange("800-1500:100");
    //    vector<string> masses = ch::MassesFromRange("14-15:1");
    //vector<string> masses = ch::MassesFromRange("14-15:1");
    vector<string> masses = {"125"};
    // Or equivalently, specify the mass points explicitly:
    //! [part2]
    
    
    //! [part4]
    for (auto chn : chns) {
        cb.AddObservations(
                           {"*"}, {"JJH"}, {"13TeV"}, {chn}, cats[chn+"_13TeV"]);
        cb.AddProcesses(
                        {"*"}, {"JJH"}, {"13TeV"}, {chn}, bkg_procs[chn], cats[chn+"_13TeV"], false);
        cb.AddProcesses(
                        masses, sig_procs, {"13TeV"}, {chn}, sig_procs, cats[chn+"_13TeV"], true);
    }
    
    
    
    
    cout << ">> Extracting histograms from input root files...\n";
    for (string era : {"13TeV"}) {
        for (string chn : chns) {
            
            string file = aux_shapes + input_folders[chn] + "/"+prefix+"_"+year+"_"+Var+".root";
            cb.cp().channel({chn}).era({era}).backgrounds().ExtractShapes(
                                                                          file, "$BIN/$PROCESS", "$BIN/$PROCESS_$SYSTEMATIC");
            cb.cp().channel({chn}).era({era}).signals().ExtractShapes(
                                                                      file, "$BIN/$PROCESS$MASS", "$BIN/$PROCESS$MASS_$SYSTEMATIC");
        }
    }
    
    
    //Some of the code for this is in a nested namespace, so
    // we'll make some using declarations first to simplify things a bit.
    using ch::syst::SystMap;
    using ch::syst::era;
    using ch::syst::bin_id;
    using ch::syst::process;
    using ch::JoinStr;
    
    
        // Norm systematics
        
        cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT"}}))
        .AddSyst(cb, "CMS_lumi_$ERA", "lnN", SystMap<era>::init({"13TeV"}, 1.024));
        
    //    cb.cp().bin_id({1}).process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT"}}))
    //    .AddSyst(cb, "CMS_eff_t$ERA", "lnN", SystMap<era>::init({"13TeV"}, 1.1/0.9));
        
    //    cb.cp().bin_id({2}).process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT"}}))
    //    .AddSyst(cb, "CMS_eff_t$ERA", "lnN", SystMap<era>::init({"13TeV"}, 0.9/1.1));
        
        cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT"}}))
        .AddSyst(cb, "CMS_eff_t$ERA", "lnN", SystMap<era>::init({"13TeV"}, 1.05));


        cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT"}}))
        .AddSyst(cb, "CMS_eff_m$ERA", "lnN", SystMap<era>::init({"13TeV"}, 1.02));
        
        cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT"}}))
        .AddSyst(cb, "CMS_trg_m$ERA", "lnN", SystMap<era>::init({"13TeV"}, 1.02));

        cb.cp().process({"JJH125"})
        .AddSyst(cb, "CMS_htt_SignalNorm", "lnN", SystMap<>::init(1.10));

        cb.cp().process({"ZTT"})
        .AddSyst(cb, "CMS_htt_ZTTNorm", "lnN", SystMap<>::init(1.10));
        
        cb.cp().process({"TT"})
        .AddSyst(cb, "CMS_htt_TTNorm", "lnN", SystMap<>::init(1.10));
        
        cb.cp().process({"VV"})
        .AddSyst(cb, "CMS_htt_VVNorm", "lnN", SystMap<>::init(1.10));
        
//        cb.cp().process({"ZLL"})
//        .AddSyst(cb, "CMS_htt_ZLLNorm", "lnN", SystMap<>::init(1.10));
//        
//        cb.cp().process({"ZJ"})
//        .AddSyst(cb, "CMS_htt_ZJNorm", "lnN", SystMap<>::init(1.10));
        
        cb.cp().process({"W"})
        .AddSyst(cb, "CMS_htt_WNorm", "lnN", SystMap<>::init(1.10));
        
        cb.cp().process({"QCD"})
        .AddSyst(cb, "CMS_htt_QCDNorm", "lnN", SystMap<>::init(1.20));
        
    
    // Shape systematics
    
//    cb.cp().channel({"mt"}).process(ch::JoinStr({sig_procs, {"WJets", "ttbar","Diboson"}}))
//    .AddSyst(cb, "met_JES", "shape", SystMap<>::init(1.00));
//
//    cb.cp().channel({"mt"}).process(ch::JoinStr({sig_procs, {"WJets", "ttbar","Diboson"}}))
//    .AddSyst(cb, "met_UES", "shape", SystMap<>::init(1.00));

//    cb.cp().channel({"mt"}).process(ch::JoinStr({sig_procs, {"ZLL","ZJ"}}))
//    .AddSyst(cb, "dyShape_", "shape", SystMap<>::init(1.00));
//
//    cb.cp().channel({"mt"}).process(ch::JoinStr({sig_procs, {"ZLL","ZJ"}}))
//    .AddSyst(cb, "zmumuShape_", "shape", SystMap<>::init(1.00));
//


    
    cout << ">> Adding systematic uncertainties...\n";
    // ch::AddSystematics_et_mt(cb);
    
    //cb.cp().process(ch::JoinStr({sig_procs, {"ZTT"}}))
    //    .AddSyst(cb, "CMS_scale_t_mutau_$ERA", "shape", SystMap<>::init(1.00));
    //! [part6]
    
    //! [part7]
    
    cb.cp().backgrounds().ExtractShapes(
                                        aux_shapes + "/"+inputFile,
                                        "$BIN/$PROCESS",
                                        "$BIN/$PROCESS_$SYSTEMATIC");
    cb.cp().signals().ExtractShapes(
                                        aux_shapes + "/"+inputFile,
                                    "$BIN/$PROCESS$MASS",
                                    "$BIN/$PROCESS$MASS_$SYSTEMATIC");
    
    
    
    
    //! [part7]
    
    //! [part8]
    //    auto bbb = ch::BinByBinFactory()
    //    .SetAddThreshold(0.1)
    //    .SetFixNorm(true);
    
    //    bbb.AddBinByBin(cb.cp().backgrounds(), cb);
    
    // This function modifies every entry to have a standardised bin name of
    // the form: {analysis}_{channel}_{bin_id}_{era}
    // which is commonly used in the htt analyses
    ch::SetStandardBinNames(cb);
    
    
    
    //! [part8]
    
    //! [part9]
    // First we generate a set of bin names:
    set<string> bins = cb.bin_set();
    // This method will produce a set of unique bin names by considering all
    // Observation, Process and Systematic entries in the CombineHarvester
    // instance.
    
    // We create the output root file that will contain all the shapes.
    //TFile output("RHW_mt.inputs.root", "RECREATE");
    
    // Finally we iterate through each bin,mass combination and write a
    
    
    auto pre_drop = cb.syst_name_set();
    //cb.syst_name(droplist, false);
    auto post_drop = cb.syst_name_set();
    cout << ">> Systematics dropped: " << pre_drop.size() - post_drop.size()
    << "\n";
    
    
    string folder = "FinalBoost/"+postfix;
    boost::filesystem::create_directories(folder);
    boost::filesystem::create_directories(folder + "/common");
    for (auto m : masses) {
        boost::filesystem::create_directories(folder + "/" + m);
    }
    
    for (string chn : chns) {
        TFile output((folder + "/common/"+chn+"_"+year+"_"+Var+".root").c_str(),
                     "RECREATE");
        auto bins = cb.cp().channel({chn}).bin_set();
        for (auto b : bins) {
            for (auto m : masses) {
                cout << ">> Writing datacard for bin: " << b << " and mass: " << m
                << "\r" << flush;
                cb.cp().channel({chn}).bin({b}).mass({m, "*"}).WriteDatacard(
                                                                             folder + "/" + m + "/" + b + ".txt", output);
            }
        }
        output.Close();
    }
    
    
    //! [part9]
    
}
