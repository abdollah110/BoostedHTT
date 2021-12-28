// command line
//BoostedTau_limit_single_plus_CR_new --year=2018 --bin=bin0 --WP=T --DIR=tgp_v1

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
    string year = "2016";
    string inputFile="";
    string WP="WP";
    string bin="bin";
    string DIR="DIR";

    po::variables_map vm;
    po::options_description config("configuration");
    config.add_options()
      ("postfix", po::value<string>(&postfix)->default_value(""))
      ("year", po::value<string>(&year)->default_value("2016"))
      ("WP", po::value<string>(&WP)->default_value(""))
      ("bin", po::value<string>(&bin)->default_value(""))
      ("inputFile", po::value<string>(&inputFile)->default_value(""))
      ("DIR", po::value<string>(&DIR)->default_value(""));
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
    
    VString chns = { "mt","mm"};
    
    map<string, string> input_folders = {
       {"mt", "."},
        {"mm", "."}
    };
    
    map<string, VString> bkg_procs;
//    bkg_procs["mt"] = {"W", "QCD", "TT","VV"};
    bkg_procs["mt"] = {"QCD", "TT","VV"};
    bkg_procs["mm"] = {"W",  "TT","VV"};


    VString sig_procs = {"DYJets"};
    
    map<string, Categories> cats;
    
    cats["mt_13TeV"] = {
        {1, "mt_0jet"},
//        {2, "fail"}
    };
    cats["mm_13TeV"] = {
        {1, "pass"},
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
                           {"*"}, {"DYJets"}, {"13TeV"}, {chn}, cats[chn+"_13TeV"]);
        cb.AddProcesses(
                        {"*"}, {"DYJets"}, {"13TeV"}, {chn}, bkg_procs[chn], cats[chn+"_13TeV"], false);
        cb.AddProcesses(
                        masses, sig_procs, {"13TeV"}, {chn}, sig_procs, cats[chn+"_13TeV"], true);
    }
    
    
    
    
    cout << ">> Extracting histograms from input root files...\n";
    for (string era : {"13TeV"}) {
        for (string chn : chns) {
            string file = aux_shapes + input_folders[chn] + "/"+chn+year+"_vis_masslep2IsoPass"+WP+"_"+bin+".root";
            if (chn.find("mm") != string::npos ) file = aux_shapes + input_folders[chn] + "/newtemplate_boostedH_"+chn+"_"+year+".root";
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
    

    
//    cb.cp().channel({"mt"}).bin_id({1}).process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZLL","ZJ"}}))
//    .AddSyst(cb, "CMS_eff_t$ERA", "lnN", SystMap<era>::init({"13TeV"}, 1.1/0.9));
//
//    cb.cp().channel({"mt"}).bin_id({2}).process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZLL","ZJ"}}))
//    .AddSyst(cb, "CMS_eff_t$ERA", "lnN", SystMap<era>::init({"13TeV"}, 0.9/1.1));
    

    cb.cp().channel({"mt","mm"}).process(ch::JoinStr({sig_procs, {"W", "TT","VV"}}))
    .AddSyst(cb, "CMS_lumi_$ERA", "lnN", SystMap<era>::init({"13TeV"}, 1.024));
    
    cb.cp().channel({"mt","mm"}).process(ch::JoinStr({sig_procs, {"W", "TT","VV"}}))
    .AddSyst(cb, "CMS_eff_m$ERA", "lnN", SystMap<era>::init({"13TeV"}, 1.02));
    
    cb.cp().channel({"mt","mm"}).process(ch::JoinStr({sig_procs, {"W", "TT","VV"}}))
    .AddSyst(cb, "CMS_trg_m$ERA", "lnN", SystMap<era>::init({"13TeV"}, 1.02));


//    cb.cp().channel({"mm"}).process(ch::JoinStr({sig_procs, {"W", "TT","VV"}}))
//    .AddSyst(cb, "CMS_lumi_$ERA", "lnN", SystMap<era>::init({"13TeV"}, 1.024));
//
//
//    cb.cp().channel({"mm"}).process(ch::JoinStr({sig_procs, {"W", "TT","VV"}}))
//    .AddSyst(cb, "CMS_eff_m$ERA", "lnN", SystMap<era>::init({"13TeV"}, 1.02));
//
//    cb.cp().channel({"mm"}).process(ch::JoinStr({sig_procs, {"W", "TT","VV"}}))
//    .AddSyst(cb, "CMS_trg_m$ERA", "lnN", SystMap<era>::init({"13TeV"}, 1.02));



//    cb.cp().process({"DYJets"})
//    .AddSyst(cb, "CMS_htt_ZTTNorm", "lnN", SystMap<>::init(1.10));
    
    cb.cp().process({"TT"})
    .AddSyst(cb, "CMS_htt_TTNorm", "lnN", SystMap<>::init(1.05));
    
    cb.cp().process({"VV"})
    .AddSyst(cb, "CMS_htt_VVNorm", "lnN", SystMap<>::init(1.10));
    
//    cb.cp().process({"ZLL"})
//    .AddSyst(cb, "CMS_htt_ZLLNorm", "lnN", SystMap<>::init(1.10));
//
//    cb.cp().process({"ZJ"})
//    .AddSyst(cb, "CMS_htt_ZJNorm", "lnN", SystMap<>::init(1.10));
    
    cb.cp().process({"W"})
    .AddSyst(cb, "CMS_htt_WNorm", "lnN", SystMap<>::init(1.10));
    
    cb.cp().process({"QCD"})
    .AddSyst(cb, "CMS_htt_QCDNorm", "lnN", SystMap<>::init(1.20));
    
    
    // Shape systematics
    
//    cb.cp().channel({"mt"}).process(ch::JoinStr({sig_procs, {"W", "TT","VV"}}))
//    .AddSyst(cb, "met_JES", "shape", SystMap<>::init(1.00));
//
//    cb.cp().channel({"mt"}).process(ch::JoinStr({sig_procs, {"W", "TT","VV"}}))
//    .AddSyst(cb, "met_UES", "shape", SystMap<>::init(1.00));
//
//    cb.cp().channel({"mt"}).process(ch::JoinStr({sig_procs, {"W", "TT","VV"}}))
//    .AddSyst(cb, "met_resp_", "shape", SystMap<>::init(1.00));
//
//    cb.cp().channel({"mt"}).process(ch::JoinStr({sig_procs, {"W", "TT","VV"}}))
//    .AddSyst(cb, "met_reso_", "shape", SystMap<>::init(1.00));
//
//    cb.cp().channel({"mt"}).process(ch::JoinStr({sig_procs, {"W", "TT","VV"}}))
//    .AddSyst(cb, "prefire", "shape", SystMap<>::init(1.00));
//
//    cb.cp().channel({"mt"}).process({sig_procs})
//    .AddSyst(cb, "Z_masspt_", "shape", SystMap<>::init(1.00));
//
//    cb.cp().channel({"mt"}).process({"W"})
//    .AddSyst(cb, "WBosonKFactor", "shape", SystMap<>::init(1.00));


    cb.cp().channel({"mt"}).process(ch::JoinStr({sig_procs, {"TT","VV"}}))
    .AddSyst(cb, "met_JES", "shape", SystMap<>::init(1.00));

    cb.cp().channel({"mt"}).process(ch::JoinStr({sig_procs, {"TT","VV"}}))
    .AddSyst(cb, "met_UES", "shape", SystMap<>::init(1.00));
//
//    cb.cp().channel({"mt"}).process(ch::JoinStr({sig_procs, {"TT","VV"}}))
//    .AddSyst(cb, "met_resp_", "shape", SystMap<>::init(1.00));
//
//    cb.cp().channel({"mt"}).process(ch::JoinStr({sig_procs, {"TT","VV"}}))
//    .AddSyst(cb, "met_reso_", "shape", SystMap<>::init(1.00));
//
    cb.cp().channel({"mt"}).process(ch::JoinStr({sig_procs, {"TT","VV"}}))
    .AddSyst(cb, "prefire", "shape", SystMap<>::init(1.00));

    cb.cp().channel({"mt"}).process({sig_procs})
    .AddSyst(cb, "Z_masspt_", "shape", SystMap<>::init(1.00));


    cb.cp().channel({"mt"}).process({"QCD"})
    .AddSyst(cb, "shape_", "shape", SystMap<>::init(1.00));

    cb.cp().channel({"mt"}).process({"TT"})
    .AddSyst(cb, "ttbarShape_", "shape", SystMap<>::init(1.00));

    
    cout << ">> Adding systematic uncertainties...\n";


    cb.cp().backgrounds().ExtractShapes(
                                        aux_shapes + "/mt"+year+"_vis_masslep2IsoPass"+WP+"_"+bin+".root",
                                        "$BIN/$PROCESS",
                                        "$BIN/$PROCESS_$SYSTEMATIC");
    cb.cp().signals().ExtractShapes(
                                        aux_shapes + "/mt"+year+"_vis_masslep2IsoPass"+WP+"_"+bin+".root",
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
    
    
    string folder = DIR+"/"+year+"_"+WP+"_"+bin;
    boost::filesystem::create_directories(folder);
    boost::filesystem::create_directories(folder + "/common");
    for (auto m : masses) {
        boost::filesystem::create_directories(folder + "/" + m);
    }
    
    for (string chn : chns) {
        TFile output((folder + "/common/boostedHTT_" + chn +"_"+year+".input.root").c_str(),
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
