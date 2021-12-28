##Running analysis

#complie the code
./Make.sh BoostedHTT2017_mt.cc
# Run the executable
python automate_analysis.py -e HTTTagProbe2017_mt.exe -p /eos/uscms/store/user/abdollah/NewSkimBoost/TgnPr/mt/2017/muTau_tnp_v3_Hadd/ -P New_mt_2017_v1 -o New_mt_2017_v1 -y 2017
python automate_analysis.py -e HTTTagProbe2017_mt.exe -p /eos/uscms/store/user/abdollah/NewSkimBoost/TgnPr/mt/2017/muTau_tnp_v3_Hadd/ -P New_mm_2017_v1 -o New_mt_2017_v1 -y 2017

#Tu run locally
./HTTTagProbe2017_mt.exe -p /eos/uscms/store/user/abdollah/NewSkimBoost/TgnPr/mt/2017/muTau_tnp_v3_Hadd/  -s ZZ2l2q  -d ./ -y 2017

#To make control plots
# first compile the .cc file
./build process_trees_lt.cc process_trees_lt
# Then run the executable
#./process_trees_lt -d TestOut2 -t mutau_tree --suf ZMass -y 2017 -o vis_mass
./process_trees_tnp.exe -d NN_nominal_TnpV10_XS -t mutau_tree --suf ZMass -y 2017 -v ZMass -o ZMassV10 -c mt -b 20 0 200
# Make plots
python autoplot.py -i Output/templates/mt2017_ZMass.root -p mass -y 2017 -c mt



#python xrun.py -i NewAnalysis_v2 -y 2017
#python autoplot.py -i Output/templates/mt2017_m_sv.root -y 2017 -p test -c mt



#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# steps for running the post-skim
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# hadding the files:
open hadd_skim.py # Edit the locations 








#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Tag & Probe
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#The Tag n proble is using BoostedHTT_mt.cc file

# Two changes are introduced remove cut on m_sv from 50 to 0
# reduced the cut og Higgs pT from 280 to 100

python automate_analysis.py -e BoostedHTT_mt.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH2/2016/mt/v1_fast_Hadd/ -o newboost_mt_2016_sys --sys
python automate_analysis.py -e BoostedHTT_mt.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH2/2017/mt/v1_fast_Hadd/ -o newboost_mt_2017_sys --sys
python automate_analysis.py -e BoostedHTT_mt.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH2/2018/mt/v1_fast_Hadd/ -o newboost_mt_2018_sys --sys

# put all root files in One single folder i.e. newboost_mt_2016_SF_sys

#Make datacards
python SF_datacardMaker.py -i newboost_mt_2016_SF_sys
python SF_datacardMaker.py -i newboost_mt_2017_SF_sys
python SF_datacardMaker.py -i newboost_mt_2018_SF_sys







#The next step is making mt mm data cards

python Step6_PreSelectionPlotter.py NN_nominal_TnpV12_ht
python Step6_PreSelectionPlotter_DiMu.py  Tnp_mm_V4_XS

# Then hadd the pass and fail file in NN_nominal_TnpV12_ht
#scopy the files in the axuliary area
# scp NN_nominal_TnpV12_ht/template_boostedH_mt_2017.root Tnp_mm_V4_XS/template_boostedH_mm_2017.root cmslpc-sl7.fnal.gov:/uscms_data/d3/abdollah/Analysis/Limit/CMSSW_8_1_0/src/auxiliaries/shapes/.
# Now Moved to new CMSSW

/uscms_data/d3/abdollah/Analysis/Limit/CMSSW_10_2_13/src/CombineHarvester/CombineTools/bin
scp

# lim:  cd /uscms_data/d3/abdollah/Analysis/Limit/CMSSW_8_1_0/src/CombineHarvester/CombineTools/bin
 
# The two config files for making DC are:
BoostedTau_limit_single_plus_CR_new.cpp
BoostedTau_limit_single_plus_CR.cpp
scram b -j 8
BoostedTau_limit_single_plus_CR_new --postfix="test" --year=2017
#add appropriate line for BBB and rateParam
sh  add_auto_MC_Stat_TnP.sh test

#combineCards.py DYJets_* > combined.cmb
#text2workspace.py combined.cmb -m 125 -o ws.root -P HiggsAnalysis.CombinedLimit.TagAndProbeModel:tagAndProbe
#combine -M FitDiagnostics ws.root --robustFit=1 --rMin -2 --rMax 2

combineCards.py pass=DYJets_mt_1_13TeV.txt CR=DYJets_mm_1_13TeV.txt > NewComb.txt
text2workspace.py NewComb.txt -m 125 -o ws_new.root -P HiggsAnalysis.CombinedLimit.TagAndProbeModel:tagAndProbe
combine -M FitDiagnostics ws_new.root --robustFit=1 --rMin -2 --rMax 2

PostFitShapesFromWorkspace -w ws.root -f fitDiagnostics.root:fit_s --postfit --print -d combined.cmb -o postfit_shapes.root -m 125


python automate_analysis.py -e HTTTagProbe2017_mt.exe -p /eos/uscms/store/user/abdollah/NewSkimBoost/TgnPr/mt/2018/v1_Hadd/ -P New_mt_2018_v1 -o New_mt_2018_v1 -y 2018 --sys
python automate_analysis.py -e HTTTagProbe2017_mt.exe -p /eos/uscms/store/user/abdollah/NewSkimBoost/TgnPr/mt/2017/muTau_tnp_v3_Hadd/ -P New_mt_2017_v1 -o New_mt_2017_v1 -y 2017 --sys

python automate_analysis.py -e BoostedHTT2017_mm.exe -p /eos/uscms/store/user/abdollah/NewSkimBoost/TgnPr/mm/2018/v1_Hadd/  -P New_mm_2018_v1 -o New_mm_2018_v1 -y 2018

python automate_analysis.py -e BoostedHTT2017_mm.exe  -p /eos/uscms/store/user/abdollah/NewSkimBoost/TgnPr/mm/2017/mumu_tnp_v1_Hadd/ -P New_mm_2017_v1 -o New_mm_2017_v1 -y 2017


BoostedTau_limit_single_plus_CR_new --postfix="L2017" --year=2017 --inputFile="template_boostedH_mt_2017_L.root" --WP="L"
BoostedTau_limit_single_plus_CR_new --postfix="M2017" --year=2017 --inputFile="template_boostedH_mt_2017_M.root" --WP="M"
BoostedTau_limit_single_plus_CR_new --postfix="T2017" --year=2017 --inputFile="template_boostedH_mt_2017_T.root" --WP="T"
BoostedTau_limit_single_plus_CR_new --postfix="L2017" --year=2017 --inputFile="template_boostedH_mt_2017_L.root" --WP="L"
BoostedTau_limit_single_plus_CR_new --postfix="M2017" --year=2017 --inputFile="template_boostedH_mt_2017_M.root" --WP="M"
BoostedTau_limit_single_plus_CR_new --postfix="T2017" --year=2017 --inputFile="template_boostedH_mt_2017_T.root" --WP="T"
BoostedTau_limit_single_plus_CR_new --postfix="L2018" --year=2018 --inputFile="template_boostedH_mt_2018_L.root" --WP="L"
BoostedTau_limit_single_plus_CR_new --postfix="M2018" --year=2018 --inputFile="template_boostedH_mt_2018_M.root" --WP="M"
BoostedTau_limit_single_plus_CR_new --postfix="T2018" --year=2018 --inputFile="template_boostedH_mt_2018_T.root" --WP="T"



scp cmslpc-sl7.fnal.gov:/uscms_data/d3/abdollah/Analysis/Limit/CMSSW_8_1_0/src/CombineHarvester/CombineTools/bin/TagNProbe/T2018/125/postfit_shapes.root postfit_shapes_T2018.root
scp cmslpc-sl7.fnal.gov:/uscms_data/d3/abdollah/Analysis/Limit/CMSSW_8_1_0/src/CombineHarvester/CombineTools/bin/TagNProbe/M2018/125/postfit_shapes.root postfit_shapes_M2018.root
scp cmslpc-sl7.fnal.gov:/uscms_data/d3/abdollah/Analysis/Limit/CMSSW_8_1_0/src/CombineHarvester/CombineTools/bin/TagNProbe/L2018/125/postfit_shapes.root postfit_shapes_L2018.root

scp cmslpc-sl7.fnal.gov:/uscms_data/d3/abdollah/Analysis/Limit/CMSSW_8_1_0/src/CombineHarvester/CombineTools/bin/TagNProbe/T2017/125/postfit_shapes.root postfit_shapes_T2017.root
scp cmslpc-sl7.fnal.gov:/uscms_data/d3/abdollah/Analysis/Limit/CMSSW_8_1_0/src/CombineHarvester/CombineTools/bin/TagNProbe/M2017/125/postfit_shapes.root postfit_shapes_M2017.root
scp cmslpc-sl7.fnal.gov:/uscms_data/d3/abdollah/Analysis/Limit/CMSSW_8_1_0/src/CombineHarvester/CombineTools/bin/TagNProbe/L2017/125/postfit_shapes.root postfit_shapes_L2017.root


python Draw_POSTPREFIT_TnP.py postfit_shapes_L2018.root L2018
python Draw_POSTPREFIT_TnP.py postfit_shapes_M2018.root M2018
python Draw_POSTPREFIT_TnP.py postfit_shapes_T2018.root T2018
python Draw_POSTPREFIT_TnP.py postfit_shapes_L2017.root L2017
python Draw_POSTPREFIT_TnP.py postfit_shapes_M2017.root M2017
python Draw_POSTPREFIT_TnP.py postfit_shapes_T2017.root T2017


text2workspace.py card_14.txt -o workspace_14.root -P HiggsAnalysis.CombinedLimit.TagAndProbeModel:tagAndProbe

combine -M MaxLikelihoodFit workspace_14.root --plots
--saveNormalizations --skipBOnlyFit --saveShapes --saveWithUncertainties

#Gooness of Fit
combine -M GoodnessOfFit NewComb.txt --algo KS -m 125 -t 500 -s 123456



python automate_analysis.py -e BoostedHTT2017_mt.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH/2017/mt/v1_fast_Hadd/ -P boost_mt_2018_v1 -o boost_mt_2017_v1 -y 2017
python automate_analysis.py -e BoostedHTT2017_et.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH/2017/et/v1_fast_Hadd/ -P boost_et_2018_v1 -o boost_et_2017_v1 -y 2017

# Draw figures step 1
python xrun.py -e process_trees_lt -t mutau_tree -c mt -i boost_mt_2017_v1 -y 2017
# Draw figures step 2
python autoplot.py -i Output/templates/mt2017_m_sv.root -p mt_plots_v1 -y 2017 -c mt



#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Skim
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# fast MTT
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
python makeSubmissionPackage_sv.py -x FastMTT -i Input_em_2017.txt -n em_2017_v1 -o /store/user/abdollah/SkimBoostedH/2017/em/v1_fast



#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# hadd
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#python hadd_skim.py -g '/eos/uscms/store/user/abdollah/BoostedH/2018/Data/*/*' -s /eos/uscms/store/user/abdollah/SkimBoostedH/2018/em/v1_fast -n v1_em_2018_data
python hadd_skim.py -i Files_mm_18_mc_v2/InputSample_18_mc.txt -s /eos/uscms/store/user/abdollah/SkimBoostedH2/2018/mm/v3 -n v3_mm_2018

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Analysis
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

python automate_analysis.py -e BoostedHTT2017_et.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH/2016/et/v1_fast_Hadd/ -P boost_et_2016_v1_sys -o boost_et_2016_v1 -y 2016 --sys
python automate_analysis.py -e BoostedHTT2017_mt.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH/2016/mt/v1_fast_Hadd/ -P boost_mt_2016_v1_sys -o boost_mt_2016_v1 -y 2016 --sys
python automate_analysis.py -e BoostedHTT2017_et.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH/2017/et/v1_fast_Hadd/ -P boost_et_2017_v1_sys -o boost_et_2017_v1 -y 2017 --sys
python automate_analysis.py -e BoostedHTT2017_mt.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH/2017/mt/v1_fast_Hadd/ -P boost_mt_2017_v1_sys -o boost_mt_2017_v1 -y 2017 --sys
python automate_analysis.py -e BoostedHTT2017_et.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH/2018/et/v1_fast_Hadd/ -P boost_et_2018_v1_sys -o boost_et_2018_v1 -y 2018 --sys
python automate_analysis.py -e BoostedHTT2017_mt.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH/2018/mt/v1_fast_Hadd/ -P boost_mt_2018_v1_sys -o boost_mt_2018_v1 -y 2018 --sys



python automate_analysis.py -e BoostedHTT2017_et.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH/2016/et/v1_fast_Hadd/ -P boost_et_2016_v2 -o boost_et_2016_v2 -y 2016
python automate_analysis.py -e BoostedHTT2017_mt.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH/2016/mt/v1_fast_Hadd/ -P boost_mt_2016_v2 -o boost_mt_2016_v2 -y 2016
python automate_analysis.py -e BoostedHTT2017_et.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH/2017/et/v1_fast_Hadd/ -P boost_et_2017_v2 -o boost_et_2017_v2 -y 2017
python automate_analysis.py -e BoostedHTT2017_mt.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH/2017/mt/v1_fast_Hadd/ -P boost_mt_2017_v2 -o boost_mt_2017_v2 -y 2017
python automate_analysis.py -e BoostedHTT2017_et.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH/2018/et/v1_fast_Hadd/ -P boost_et_2018_v2 -o boost_et_2018_v2 -y 2018
python automate_analysis.py -e BoostedHTT2017_mt.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH/2018/mt/v1_fast_Hadd/ -P boost_mt_2018_v2 -o boost_mt_2018_v2 -y 2018

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Test plotting
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

./process_trees_lt -d boost_mt_2017_v1/NN_nominal  --suf test1 -v m_sv -b 20 0 200
python autoplot.py -i Output/templates/et2018_test1.root   -p et_plots_v1 -y 2018 -c et


#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# NN
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

input=$1
Name=$2
Tree=$3

python preprocess.py -i  ${input}  -o testData_${Name}
python train.py --signal JJH125 --background ZTT --input datasets/testData_${Name}.h5 --model outputModel_${Name}
python classify.py --treename ${Tree} --input-vbf datasets/testData_${Name}.h5  --model-vbf models/outputModel_${Name}.hdf5   --dir ${input}  --output-dir ${Name}_NN


sh run_all.sh ../Analysis/Output/trees/boost_mt_2016_v2/NN_nominal boost_mt_2016_v2 mutau_tree
sh run_all.sh ../Analysis/Output/trees/boost_et_2016_v2/NN_nominal boost_et_2016_v2 etau_tree
sh run_all.sh ../Analysis/Output/trees/boost_mt_2017_v2/NN_nominal boost_mt_2017_v2 mutau_tree
sh run_all.sh ../Analysis/Output/trees/boost_et_2017_v2/NN_nominal boost_et_2017_v2 etau_tree
sh run_all.sh ../Analysis/Output/trees/boost_mt_2018_v2/NN_nominal boost_mt_2018_v2 mutau_tree
sh run_all.sh ../Analysis/Output/trees/boost_et_2018_v2/NN_nominal boost_et_2018_v2 etau_tree


#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Make DataCard both with m_sv and NN
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



python xrun.py -e process_trees_lt -t mutau_tree -c mt -i boost_mt_2017_v1 -y 2017

python xrun.py -i All_v2/boost_et_2016_v2_NN -c et -e process_trees_lt
python xrun.py -i All_v2/boost_mt_2016_v2_NN -c mt -e process_trees_lt
python xrun.py -i All_v2/boost_et_2017_v2_NN -c et -e process_trees_lt
python xrun.py -i All_v2/boost_mt_2017_v2_NN -c mt -e process_trees_lt
python xrun.py -i All_v2/boost_et_2018_v2_NN -c et -e process_trees_lt
python xrun.py -i All_v2/boost_mt_2018_v2_NN -c mt -e process_trees_lt



python autoplot.py -i Output/templates/et2018_m_sv.root -p _v2_ -y 2018 -c et
python autoplot.py -i Output/templates/mt2018_m_sv.root -p _v2_ -y 2018 -c mt
python autoplot.py -i Output/templates/et2017_m_sv.root -p _v2_ -y 2017 -c et
python autoplot.py -i Output/templates/mt2017_m_sv.root -p _v2_ -y 2017 -c mt
python autoplot.py -i Output/templates/et2016_m_sv.root -p _v2_ -y 2016 -c et
python autoplot.py -i Output/templates/mt2016_m_sv.root -p _v2_ -y 2016 -c mt



hadd V1_2016_NN.root et2016_NN_disc.root mt2016_NN_disc.root
hadd V1_2016_m_sv.root et2016_m_sv.root mt2016_m_sv.root
hadd V1_2017_NN.root et2017_NN_disc.root mt2017_NN_disc.root
hadd V1_2017_m_sv.root et2017_m_sv.root mt2017_m_sv.root
hadd V1_2018_NN.root et2018_NN_disc.root mt2018_NN_disc.root
hadd V1_2018_m_sv.root et2018_m_sv.root mt2018_m_sv.root


hadd aux/V8_2016_NN.root aux/*2016_NN_disc.root
hadd aux/V8_2017_NN.root aux/*2017_NN_disc.root
hadd aux/V8_2018_NN.root aux/*2018_NN_disc.root





BoostedTau_limit_V1 --prefix="V3" --postfix="2018" --year=2018 --Var=NN

combine -M Significance -d allCmb.txt -t -1 -m 125 --expectSignal=1

PostFitShapesFromWorkspace -w ws.root -f fitDiagnostics.root:fit_s --postfit --print -d allCmb.txt -o postfit_shapes.root -m 125




#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Measuring the jet to boosted tau fake rate
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# measuring the fake rate
./Make.sh BoostedHTT_mFake.cc
# running code for FR measurement
python automate_analysis.py -e BoostedHTT_mFake.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH2/2016/mfake/v1_Hadd/ -o newboost_mfake_2016_v5
./Step6_PreSelectionPlotter_Fake.py FakeRate_v1/newboost_mfake_2016_v5/
python FR_boostedTau.py FakeRate_v1/newboost_mfake_20176_v5/Data.root

# code to run
./build process_trees_sf_fr.cc process_trees_sf_fr

#// test the code locally
./process_trees_sf_fr -d newboost_mt_2018_SF_sys --suf sys_v1 -v vis_mass -b 30 0 150 -c lep2IsoPassL -l 0 -h 1000 -n test -w Loose

#Make DC for computing limits
python SF_datacardMaker.py -i newboost_mt_2016_sys_v2/
python SF_datacardMaker.py -i newboost_mt_2017_sys_v2/
python SF_datacardMaker.py -i newboost_mt_2018_sys_v2/




