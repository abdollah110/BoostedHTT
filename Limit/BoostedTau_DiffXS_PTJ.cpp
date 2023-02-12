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
    
//    VString chns = { "mt"};
    VString chns = { "mt","et","em","tt"};
//VString  PT_BIN = { "_bin1","_bin2","_bin3","_bin4"};
    
    map<string, string> input_folders = {
        {"mt", "."},
        {"et", "."},
        {"em", "."},
//        {"me", "."},
        {"tt", "."}
    };
    
    map<string, VString> bkg_procs;
    bkg_procs["mt"] = {"QCD", "TT","VV","ZTT","OutsideAcceptance"};
    bkg_procs["et"] = {"QCD", "TT","VV","ZTT","OutsideAcceptance"};
    bkg_procs["em"] = {"QCD","W", "TT","VV","ZTT","OutsideAcceptance"};
//    bkg_procs["me"] = {"W", "TT","VV","ZTT"};
    bkg_procs["tt"] = {"QCD", "TT","VV","ZTT","OutsideAcceptance"};
    
//    VString sig_procs = {"ggH_PTJ_0_350","ggH_PTJ_350_450","ggH_PTJ_450_600","ggH_PTJ_600_800","ggH_PTJ_GT800","XH_PTJ_0_350","XH_PTJ_350_450","XH_PTJ_450_600","XH_PTJ_600_800","XH_PTJ_GT800"};
//    VString ggH_procs = {"ggH_PTJ_0_350","ggH_PTJ_350_450","ggH_PTJ_450_600","ggH_PTJ_600_800","ggH_PTJ_GT800"};
    VString sig_procs = {"ggH_PTJ_0_350","ggH_PTJ_350_450","ggH_PTJ_450_600","ggH_PTJ_GT600","XH_PTJ_0_350","XH_PTJ_350_450","XH_PTJ_450_600","XH_PTJ_GT600"};
    VString ggH_procs = {"ggH_PTJ_0_350","ggH_PTJ_350_450","ggH_PTJ_450_600","ggH_PTJ_GT600"};

//    VString sig_procs = {"H125"};
    map<string, Categories> cats;
    //cats["et_13TeV"] = {
    //      {1, "EleTau_DiJet"}};
            
            

    cats["mt"] = {
        {1, "Htt_PTJ_0_350_cat"+year+"mt"},
        {2, "Htt_PTJ_350_450_cat"+year+"mt"},
        {3, "Htt_PTJ_450_600_cat"+year+"mt"},
        {4, "Htt_PTJ_GT600_cat"+year+"mt"},
    };
    cats["et"] = {
        {1, "Htt_PTJ_0_350_cat"+year+"et"},
        {2, "Htt_PTJ_350_450_cat"+year+"et"},
        {3, "Htt_PTJ_450_600_cat"+year+"et"},
        {4, "Htt_PTJ_GT600_cat"+year+"et"},
    };
    cats["tt"] = {
        {1, "Htt_PTJ_0_350_cat"+year+"tt"},
        {2, "Htt_PTJ_350_450_cat"+year+"tt"},
        {3, "Htt_PTJ_450_600_cat"+year+"tt"},
        {4, "Htt_PTJ_GT600_cat"+year+"tt"},
    };
    cats["em"] = {
        {1, "Htt_PTJ_0_350_cat"+year+"em"},
        {2, "Htt_PTJ_350_450_cat"+year+"em"},
        {3, "Htt_PTJ_450_600_cat"+year+"em"},
        {4, "Htt_PTJ_GT600_cat"+year+"em"},
    };



//    cats["mt"] = {
//        {1, "mt_bin1"},
//        {2, "mt_bin2"},
//        {3, "mt_bin3"},
//        {4, "mt_bin4"},
//        {5, "mt_bin5"},
//    };
//    cats["et"] = {
//        {1, "et_bin1"},
//        {2, "et_bin2"},
//        {3, "et_bin3"},
//        {4, "et_bin4"},
//        {5, "et_bin5"},
//    };
//    cats["tt"] = {
//        {1, "tt_bin1"},
//        {2, "tt_bin2"},
//        {3, "tt_bin3"},
//        {4, "tt_bin4"},
//        {5, "tt_bin5"},
//    };
//    cats["em"] = {
//        {1, "em_bin1"},
//        {2, "em_bin2"},
//        {3, "em_bin3"},
//        {4, "em_bin4"},
//        {5, "em_bin5"},
//    };


//    cats["et_13TeV"] = {
//        {1, "et_0jet"},
//    };
//    cats["em_13TeV"] = {
//        {1, "em_0jet"},
//    };
//    cats["tt_13TeV"] = {
//        {1, "tt_0jet"},

//    };
    
    
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
                           {"*"}, {"H"}, {"13TeV"}, {chn}, cats[chn]);
        cb.AddProcesses(
                        {"*"}, {"H"}, {"13TeV"}, {chn}, bkg_procs[chn], cats[chn], false);
        cb.AddProcesses(
                         masses,{"H"}, {"13TeV"}, {chn}, sig_procs, cats[chn], true);
    }
    
    
    
    
    cout << ">> Extracting histograms from input root files...\n";
    for (string era : {"13TeV"}) {
        for (string chn : chns) {
            string file = aux_shapes + input_folders[chn] + "/"+prefix+"_"+year+"_"+Var+".root";
            cb.cp().channel({chn}).era({era}).backgrounds().ExtractShapes(  file, "$BIN/$PROCESS", "$BIN/$PROCESS_$SYSTEMATIC");
            cb.cp().channel({chn}).era({era}).signals().ExtractShapes(      file, "$BIN/$PROCESS$MASS", "$BIN/$PROCESS$MASS_$SYSTEMATIC");
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
    
        // Lumi https://twiki.cern.ch/twiki/bin/view/CMS/TWikiLUM#LumiComb
     if (year.find("2016") != string::npos){
        cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT","OutsideAcceptance"}})).AddSyst(cb, "lumi_13TeV_"+year, "lnN", SystMap<era>::init({"13TeV"}, 1.01));
        cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT","OutsideAcceptance"}})).AddSyst(cb, "lumi_13TeV_correlated", "lnN", SystMap<era>::init({"13TeV"}, 1.006));
     }

     if (year.find("2017") != string::npos){
        cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT","OutsideAcceptance"}})).AddSyst(cb, "lumi_13TeV_"+year, "lnN", SystMap<era>::init({"13TeV"}, 1.02));
        cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT","OutsideAcceptance"}})).AddSyst(cb, "lumi_13TeV_correlated", "lnN", SystMap<era>::init({"13TeV"}, 1.009));
        cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT","OutsideAcceptance"}})).AddSyst(cb, "lumi_13TeV_1718", "lnN", SystMap<era>::init({"13TeV"}, 1.006));
     }

     if (year.find("2018") != string::npos){
        cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT","OutsideAcceptance"}})).AddSyst(cb, "lumi_13TeV_"+year, "lnN", SystMap<era>::init({"13TeV"}, 1.015));
        cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT","OutsideAcceptance"}})).AddSyst(cb, "lumi_13TeV_correlated", "lnN", SystMap<era>::init({"13TeV"}, 1.02));
        cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT","OutsideAcceptance"}})).AddSyst(cb, "lumi_13TeV_1718", "lnN", SystMap<era>::init({"13TeV"}, 1.002));
     }


    //        tau    
    cb.cp().process(ch::JoinStr({sig_procs, {"TT","VV","ZTT","OutsideAcceptance"}})).channel({"et","mt","tt"})
    .AddSyst(cb, "CMS_eff_tboost"+year, "lnN", SystMap<era>::init({"13TeV"}, 1.10));

    //         electron
    cb.cp().process(ch::JoinStr({sig_procs, {"W","TT","VV","ZTT","OutsideAcceptance"}})).channel({"em"})
    .AddSyst(cb, "CMS_eff_e_em"+year, "lnN", SystMap<era>::init({"13TeV"}, 1.02));
    cb.cp().process(ch::JoinStr({sig_procs, {"W","TT","VV","ZTT","OutsideAcceptance"}})).channel({"et"})
    .AddSyst(cb, "CMS_eff_e_et"+year, "lnN", SystMap<era>::init({"13TeV"}, 1.02));
    
    cb.cp().process(ch::JoinStr({sig_procs, {"W","TT","VV","ZTT","OutsideAcceptance"}})).channel({"et","em"})
    .AddSyst(cb, "CMS_scale_e", "lnN", SystMap<era>::init({"13TeV"}, 1.02));
    
    cb.cp().process(ch::JoinStr({sig_procs, {"W","TT","VV","ZTT","OutsideAcceptance"}})).channel({"em"})
    .AddSyst(cb, "CMS_trg_e_em"+year, "lnN", SystMap<era>::init({"13TeV"}, 1.02));
    cb.cp().process(ch::JoinStr({sig_procs, {"W","TT","VV","ZTT","OutsideAcceptance"}})).channel({"et"})
    .AddSyst(cb, "CMS_trg_e_et"+year, "lnN", SystMap<era>::init({"13TeV"}, 1.02));



    //      muon
    cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT","OutsideAcceptance"}})).channel({"em"})
    .AddSyst(cb, "CMS_eff_m_em"+year, "lnN", SystMap<era>::init({"13TeV"}, 1.02));
    cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT","OutsideAcceptance"}})).channel({"mt"})
    .AddSyst(cb, "CMS_eff_m_mt"+year, "lnN", SystMap<era>::init({"13TeV"}, 1.02));
    
    cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT","OutsideAcceptance"}})).channel({"mt","em"})
    .AddSyst(cb, "CMS_scale_m", "lnN", SystMap<era>::init({"13TeV"}, 1.02));
    
    cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT","OutsideAcceptance"}})).channel({"em"})
    .AddSyst(cb, "CMS_trg_m_em"+year, "lnN", SystMap<era>::init({"13TeV"}, 1.02));
    cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT","OutsideAcceptance"}})).channel({"mt"})
    .AddSyst(cb, "CMS_trg_m_mt"+year, "lnN", SystMap<era>::init({"13TeV"}, 1.02));
    
    //      JER
    
    cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT","OutsideAcceptance"}}))
    .AddSyst(cb, "CMS_res_j"+year, "lnN", SystMap<era>::init({"13TeV"}, 1.01));
    
    cb.cp().process({"ZTT"})
    .AddSyst(cb, "CMS_htt_ZTTNorm"+year, "lnN", SystMap<>::init(1.03));
    
    cb.cp().process({"TT"})
    .AddSyst(cb, "CMS_htt_TTNorm"+year, "lnN", SystMap<>::init(1.05));
    
    cb.cp().process({"VV"})
    .AddSyst(cb, "CMS_htt_VVNorm"+year, "lnN", SystMap<>::init(1.05));
        
    cb.cp().process({"W"})
    .AddSyst(cb, "CMS_htt_WNorm"+year, "lnN", SystMap<>::init(1.10));
    
    cb.cp().process({"QCD"}).channel({"et"})
    .AddSyst(cb, "CMS_htt_QCDNorm_et"+year, "lnN", SystMap<>::init(1.20));
    cb.cp().process({"QCD"}).channel({"mt"})
    .AddSyst(cb, "CMS_htt_QCDNorm_mt"+year, "lnN", SystMap<>::init(1.20));
    cb.cp().process({"QCD"}).channel({"tt"})
    .AddSyst(cb, "CMS_htt_QCDNorm_tt"+year, "lnN", SystMap<>::init(1.20));
    cb.cp().process({"QCD"}).channel({"em"})
    .AddSyst(cb, "CMS_htt_QCDNorm_em"+year, "lnN", SystMap<>::init(1.20));


    cb.cp().process({"QCD"}).channel({"et","mt","tt"})
        .AddSyst(cb, "CMS_QCD_bkg_fakerate"+year, "shape", SystMap<>::init(1.00));



    //####################################################################################
    // Shape systematics
    //####################################################################################


    cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT","OutsideAcceptance"}}))
    .AddSyst(cb, "CMS_scale_j"+year, "shape", SystMap<>::init(1.00));

    cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT","OutsideAcceptance"}}))
    .AddSyst(cb, "CMS_scale_met_unclustered"+year, "shape", SystMap<>::init(1.00));

//
//Tau Energy Scale
//


    cb.cp().process(ch::JoinStr({sig_procs, {"TT","VV","ZTT","OutsideAcceptance"}})).channel({"mt","et","tt"})
        .AddSyst(cb, "CMS_scale_t_1prong1pizero"+year, "shape", SystMap<>::init(1.00));

    cb.cp().process(ch::JoinStr({sig_procs, {"TT","VV","ZTT","OutsideAcceptance"}})).channel({"mt","et","tt"})
        .AddSyst(cb, "CMS_scale_t_1prong"+year, "shape", SystMap<>::init(1.00));

    cb.cp().process(ch::JoinStr({sig_procs, {"TT","VV","ZTT","OutsideAcceptance"}})).channel({"mt","et","tt"})
        .AddSyst(cb, "CMS_scale_t_3prong"+year, "shape", SystMap<>::init(1.00));


    cb.cp().process(ch::JoinStr({sig_procs, {"TT","VV","ZTT","OutsideAcceptance"}})).channel({"tt"})
    .AddSyst(cb, "CMS_trig_tt"+year, "shape", SystMap<>::init(1.00));

    cb.cp().process({"QCD"}).channel({"em"})
    .AddSyst(cb, "CMS_QCD_bkg_modeling_em"+year, "shape", SystMap<>::init(1.00));
    cb.cp().process({"QCD"}).channel({"et"})
    .AddSyst(cb, "CMS_QCD_bkg_modeling_et"+year, "shape", SystMap<>::init(1.00));
    cb.cp().process({"QCD"}).channel({"mt"})
    .AddSyst(cb, "CMS_QCD_bkg_modeling_mt"+year, "shape", SystMap<>::init(1.00));
    cb.cp().process({"QCD"}).channel({"tt"})
    .AddSyst(cb, "CMS_QCD_bkg_modeling_tt"+year, "shape", SystMap<>::init(1.00));

    if (year.find("2018") == string::npos){
    cb.cp().process(ch::JoinStr({sig_procs, {"W","TT","VV","ZTT","OutsideAcceptance"}}))
    .AddSyst(cb, "CMS_prefiring", "shape", SystMap<>::init(1.00));
    }

    cb.cp().process({"TT"})
    .AddSyst(cb, "CMS_ttbarShape"+year, "shape", SystMap<>::init(1.00));

    cb.cp().process({"ZTT"})
    .AddSyst(cb, "Z_masspt_"+year, "shape", SystMap<>::init(1.00));
    

    //####################################################################################
    // PDf and QCd Scale systematics
    //####################################################################################


    cb.cp().process({"ZTT"})
        .AddSyst(cb, "ZTTpdf"+year, "shape", SystMap<>::init(1.00));
    cb.cp().process({"TT"})
        .AddSyst(cb, "TTpdf"+year, "shape", SystMap<>::init(1.00));

    cb.cp().process({"ZTT"})
        .AddSyst(cb, "ZTTQCDScale"+year, "shape", SystMap<>::init(1.00));
    cb.cp().process({"TT"})
        .AddSyst(cb, "TTQCDScale"+year, "shape", SystMap<>::init(1.00));
    
    
    //####################################################################################
    // Theorethical systematics
    //####################################################################################

    cb.cp().process({ggH_procs})
    .AddSyst(cb, "THU_ggH_Mu_", "shape", SystMap<>::init(1.00));

    cb.cp().process({ggH_procs})
    .AddSyst(cb, "THU_ggH_Res_", "shape", SystMap<>::init(1.00));

    cb.cp().process({ggH_procs})
    .AddSyst(cb, "THU_ggH_Mig01_", "shape", SystMap<>::init(1.00));

    cb.cp().process({ggH_procs})
    .AddSyst(cb, "THU_ggH_Mig12_", "shape", SystMap<>::init(1.00));

    cb.cp().process({ggH_procs})
    .AddSyst(cb, "THU_ggH_VBF2j_", "shape", SystMap<>::init(1.00));

    cb.cp().process({ggH_procs})
    .AddSyst(cb, "THU_ggH_VBF3j_", "shape", SystMap<>::init(1.00));

    cb.cp().process({ggH_procs})
    .AddSyst(cb, "THU_ggH_PT60_", "shape", SystMap<>::init(1.00));

    cb.cp().process({ggH_procs})
    .AddSyst(cb, "THU_ggH_PT120_", "shape", SystMap<>::init(1.00));

    cb.cp().process({ggH_procs})
    .AddSyst(cb, "THU_ggH_qmtop_", "shape", SystMap<>::init(1.00));
//
    
//    cout << ">> Adding systematic uncertainties...\n";
    // ch::AddSystematics_et_mt(cb);
    
    //! [part6]
    
    //! [part7]
    
    cb.cp().backgrounds().ExtractShapes(
                                        aux_shapes + "/"+prefix+"_"+year+"_"+Var+".root",
                                        "$BIN/$PROCESS",
                                        "$BIN/$PROCESS_$SYSTEMATIC");
    cb.cp().signals().ExtractShapes(
                                    aux_shapes + "/"+prefix+"_"+year+"_"+Var+".root",
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
    
    
    string folder = postfix+"/"+year;
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
                cb.cp().channel({chn}).bin({b}).mass({m, "*"}).WriteDatacard(folder + "/" + m + "/" + b + ".txt", output);
            }
        }
        output.Close();
    }
    
    
    //! [part9]
    
}


//text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO 'map=.*/.*H.*PTJ_0_350.*:r_H_PTJ_0_350[1,-25,25]' --PO 'map=.*/.*H.*PTJ_350_450.*:r_H_PTJ_350_450[1,-25,25]' --PO 'map=.*/.*H.*PTJ_450_600.*:r_H_PTJ_450_600[1,-25,25]' --PO 'map=.*/.*H.*PTJ_G.600.*:r_H_PTJ_GT600[1,-25,25]' diff_1.txt -o Workspace_PTJ.root -m 125

//combine Workspace_PTJ.root --robustFit=1 --preFitValue=1. --X-rtd MINIMIZER_analytic --algo=singles --cl=0.68 --setParameters r_H_PTJ_0_350=1.0,r_H_PTJ_350_450=1.0,r_H_PTJ_450_600=1.0,r_H_PTJ_GT600=1.0 --setParameterRanges r_H_PTJ_0_350=-15,15:r_H_PTJ_350_450=-15,15:r_H_PTJ_450_600=-15,15:r_H_PTJ_GT450=-15,15 --floatOtherPOIs=1 -M MultiDimFit -n test_param0 -m 125 --cminDefaultMinimizerStrategy=0
