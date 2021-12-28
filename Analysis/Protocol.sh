## Steps for Running analysis

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# ggNtuple Production
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Skim
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
for i in et mt tt em me ;do for j in 2016 2017 2018 ; do  python makeSubmissionPackage.py -x SkimerBoost_$i -n qcd$i\_$j\_v3_qcd -i InputSample_$j\_qcd.txt -o /store/user/abdollah/SkimBoostedH2/$j/$i/v3/ ; done; done



python makeSubmissionPackage.py -x SkimerBoost_et -n et_16_v4_mc -i InputSample_2016_mc.txt -o /store/user/abdollah/SkimBoostedH2/2016/et/v4/
python makeSubmissionPackage.py -x SkimerBoost_et -n et_17_v4_mc -i InputSample_2017_mc.txt -o /store/user/abdollah/SkimBoostedH2/2017/et/v4/
python makeSubmissionPackage.py -x SkimerBoost_et -n et_18_v4_mc -i InputSample_2018_mc.txt -o /store/user/abdollah/SkimBoostedH2/2018/et/v4/

python makeSubmissionPackage.py -x SkimerBoost_mt -n mt_16_v4_mc -i InputSample_2016_mc.txt -o /store/user/abdollah/SkimBoostedH2/2016/mt/v4/
python makeSubmissionPackage.py -x SkimerBoost_mt -n mt_17_v4_mc -i InputSample_2017_mc.txt -o /store/user/abdollah/SkimBoostedH2/2017/mt/v4/
python makeSubmissionPackage.py -x SkimerBoost_mt -n mt_18_v4_mc -i InputSample_2018_mc.txt -o /store/user/abdollah/SkimBoostedH2/2018/mt/v4/

python makeSubmissionPackage.py -x SkimerBoost_tt -n tt_16_v4_mc -i InputSample_2016_mc.txt -o /store/user/abdollah/SkimBoostedH2/2016/tt/v4/
python makeSubmissionPackage.py -x SkimerBoost_tt -n tt_17_v4_mc -i InputSample_2017_mc.txt -o /store/user/abdollah/SkimBoostedH2/2017/tt/v4/
python makeSubmissionPackage.py -x SkimerBoost_tt -n tt_18_v4_mc -i InputSample_2018_mc.txt -o /store/user/abdollah/SkimBoostedH2/2018/tt/v4/


python makeSubmissionPackage.py -x SkimerBoost_et -n et_16_v4_data -i InputSample_16_Ele.txt -o /store/user/abdollah/SkimBoostedH2/2016/et/v4/
python makeSubmissionPackage.py -x SkimerBoost_et -n et_17_v4_data -i InputSample_17_Ele.txt -o /store/user/abdollah/SkimBoostedH2/2017/et/v4/
python makeSubmissionPackage.py -x SkimerBoost_et -n et_18_v4_data -i InputSample_18_Ele.txt -o /store/user/abdollah/SkimBoostedH2/2018/et/v4/


python makeSubmissionPackage.py -x SkimerBoost_mt -n mt_16_v4_data -i InputSample_16_Mu.txt -o /store/user/abdollah/SkimBoostedH2/2016/mt/v4/
python makeSubmissionPackage.py -x SkimerBoost_mt -n mt_17_v4_data -i InputSample_17_Mu.txt -o /store/user/abdollah/SkimBoostedH2/2017/mt/v4/
python makeSubmissionPackage.py -x SkimerBoost_mt -n mt_18_v4_data -i InputSample_18_Mu.txt -o /store/user/abdollah/SkimBoostedH2/2018/mt/v4/

python makeSubmissionPackage.py -x SkimerBoost_tt_ht     -n tt_16_v4_data_ht -i InputSample_16_JetHT.txt -o /store/user/abdollah/SkimBoostedH2/2016/tt/v4/
python makeSubmissionPackage.py -x SkimerBoost_tt_htmht  -n tt_16_v4_data_htmht -i InputSample_16_HTMHT.txt -o /store/user/abdollah/SkimBoostedH2/2016/tt/v4/
python makeSubmissionPackage.py -x SkimerBoost_tt_ht     -n tt_17_v4_data_ht -i InputSample_17_JetHT.txt -o /store/user/abdollah/SkimBoostedH2/2017/tt/v4/
python makeSubmissionPackage.py -x SkimerBoost_tt_htmht  -n tt_17_v4_data_htmht -i InputSample_17_HTMHT.txt -o /store/user/abdollah/SkimBoostedH2/2017/tt/v4/
python makeSubmissionPackage.py -x SkimerBoost_tt        -n tt_18_v4_data -i InputSample_18_JetHT.txt -o /store/user/abdollah/SkimBoostedH2/2018/tt/v4/


sh
for i in Files*v4* ; do cd $i ; condor_submit Submit_batch_*.jdl; cd -; done



#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# fast MTT
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
python makeSubmissionPackage_sv.py -x FastMTT -i Input_em_2017.txt -n em_2017_v1 -o /store/user/abdollah/SkimBoostedH/2017/em/v1_fast

# multiple submission
for i in mt et em me ; do for j in 2016 2017 2018 ; do python makeSubmissionPackage_sv.py -x FastMTT -n $i\_$j\_v3 -i /eos/uscms/store/user/abdollah/SkimBoostedH2/$j/$i/v3; done; done
# submit
for i in Files_*v2; do cd $i/; condor_submit Submit_batch_*.jdl; cd -; done
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# hadd
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#python hadd_skim.py -g '/eos/uscms/store/user/abdollah/BoostedH/2018/Data/*/*' -s /eos/uscms/store/user/abdollah/SkimBoostedH/2018/em/v1_fast -n v1_em_2018_data
python hadd_skim.py -i Files_mm_18_mc_v2/InputSample_18_mc.txt -s /eos/uscms/store/user/abdollah/SkimBoostedH2/2018/mm/v3 -n v3_mm_2018

# This is for all channel for MC
for i in 16 17 18 ; do for j in mt et tt em me ; do  python hadd_skim.py -i Files\_$j\_$i\_mc\_v2/InputSample\_$i\_mc.txt -s /eos/uscms/store/user/abdollah/SkimBoostedH2/20$i/$j/v2_fast -n v2-$j-$i; done; done

#This is for Data
for i in 16 17 18 ; do for j in et  em ; do  python hadd_skim.py -i Files\_$j\_$i\_v3\_data/InputSample\_$i\_Ele.txt -s /eos/uscms/store/user/abdollah/SkimBoostedH2/20$i/$j/v3_fast -n v3-$j-$i; done; done
for i in 16 17 18 ; do for j in mt  me ; do  python hadd_skim.py -i Files\_$j\_$i\_v3\_data/InputSample\_$i\_Mu.txt  -s /eos/uscms/store/user/abdollah/SkimBoostedH2/20$i/$j/v3_fast -n v3-$j-$i; done; done



#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#Renaming
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
for i in /eos/uscms/store/user/abdollah/SkimBoostedH2/2016/*/v2_fast_Hadd/ ; do sh _rename_2016.sh $i ; done
for i in /eos/uscms/store/user/abdollah/SkimBoostedH2/2017/*/v2_fast_Hadd/ ; do sh _rename_2017.sh $i ; done
for i in /eos/uscms/store/user/abdollah/SkimBoostedH2/2018/*/v2_fast_Hadd/ ; do sh _rename_2018.sh $i ; done

for i in et mt em me tt ; do for j in 2016 2017 2018; do sh _rename_$j.sh /eos/uscms/store/user/abdollah/SkimBoostedH2/$j/$i/v2_fast_Hadd ; done; done;

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Analysis
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

python automate_analysis.py -e BoostedHTT_mt.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH2/2018/mt/v3_fast_Hadd/ -o boost_mt_RecoilCheck_2018
python automate_analysis.py -e BoostedHTT_mt.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH2/2018/mt/v3_fast_Hadd/ -o boost_mt_RecoilCheck_2018 --sys

for i in em me et  mt tt; do python automate_analysis.py -e BoostedHTT_${i}.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH2/2018/${i}/v3_fast_Hadd/ -o boost_${i}_2018_V7 --sys; done
for i in em me et  mt tt; do python automate_analysis.py -e BoostedHTT_${i}.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH2/2017/${i}/v3_fast_Hadd/ -o boost_${i}_2017_V7 --sys; done
for i in em me et  mt tt; do python automate_analysis.py -e BoostedHTT_${i}.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH2/2016/${i}/v3_fast_Hadd/ -o boost_${i}_2016_V7 --sys; done


#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Hadd
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
sh hadd.sh Output/trees/boost_mt_RecoilCheck_2018

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Test plotting
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
./process_trees_lt_fr -d boost_mt_2017_v1/NN_nominal  --suf test1 -v m_sv -b 30 0 300
python autoplot.py -i Output/templates/mt2018_test1.root   -p et_plots_v1

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Full plotting
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#making single plot
./process_trees_lt_fr -d boost_mt_2017_v1/NN_nominal  --suf test1 -v m_sv -b 20 0 200
python autoplot.py -i Output/templates/et2018_test1.root   -p et_plots_v1

#making all plots
# To make control plots for all variables [this is usually been done ]
sh   for i in et mt tt ; do for j in 2016 2017 2018;  do cp -r /eos/uscms/store/user/abdollah/NN_output_Sys/NN_boost_${i}_${j}_NoCutNN_nominal_NN Output/trees/V6\_${i}\_${j}; done
mkdir Output/trees/V8_em_2016
mkdir Output/trees/V8_em_2017
mkdir Output/trees/V8_em_2018

cd Output/trees/V6_mt_2016
sh
for i in *root ; do hadd ../V8_em_2016/$i  /eos/uscms/store/user/abdollah/NN_output_Sys/NN_boost_em_2016_V8NN_nominal_NN/$i   /eos/uscms/store/user/abdollah/NN_output_Sys/NN_boost_me_2016_V8NN_nominal_NN/$i   ; done
for i in *root ; do hadd ../V8_em_2017/$i  /eos/uscms/store/user/abdollah/NN_output_Sys/NN_boost_em_2017_V8NN_nominal_NN/$i   /eos/uscms/store/user/abdollah/NN_output_Sys/NN_boost_me_2017_V8NN_nominal_NN/$i   ; done
for i in *root ; do hadd ../V8_em_2018/$i  /eos/uscms/store/user/abdollah/NN_output_Sys/NN_boost_em_2018_V8NN_nominal_NN/$i   /eos/uscms/store/user/abdollah/NN_output_Sys/NN_boost_me_2018_V8NN_nominal_NN/$i   ; done

# Full plotting
python xrun.py -i /eos/uscms/store/user/abdollah/NN_output_Sys/NN_boost_mt_2018_NoCutNN_nominal_NN -p finalPlotV6 -o all

python xrun.py -i Output/trees/V8_em_2016 -p CP -o all


# To make control plots for just one variaable
python xrun.py -i Output/trees/ALL_BoostNew_v4/boost_em_2016_v2/NN_nominal -p testPlot -o m_sv
for i in yOptimization/V1_First/NN_BoostNew_* ; do python xrun.py -i $i ;done


# Check m_sv for all 5 channels and 3 years
python plotChecker.pyf

# copy the files in the output/template/FullV1
for i in Output/templates/FullV1/*_m_sv_FullV1.root ; do python autoplot.py -i $i  -p testfullv1 ; done


./DiffMeasure_lt -d yOptimization/V1_First/NN_BoostNew_mt_2018_v2_NN/ --suf test1 -v m_sv -b 20 0 200 -c higgs_pT -l 0 -h 500

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# NN
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

# create some ditecyries for combination
# Then hadd all 3 years in the same direcory
#Copy all folders in to ALL_BoostNew_v5
#creat combine directories:
mkdir  Sum_tt Sum_mt Sum_et Sum_em

cd boost_tt_2018_NoCut/NN_nominal ;  for i in *.root ; do hadd ../../Sum_tt/$i $i ../../boost_tt_2017_NoCut/NN_nominal/$i ../../boost_tt_2016_NoCut/NN_nominal/$i ; done
cd boost_mt_2018_NoCut/NN_nominal ;  for i in *.root ; do hadd ../../Sum_mt/$i $i ../../boost_mt_2017_NoCut/NN_nominal/$i ../../boost_mt_2016_NoCut/NN_nominal/$i ; done
cd boost_et_2018_NoCut/NN_nominal ;  for i in *.root ; do hadd ../../Sum_et/$i $i ../../boost_et_2017_NoCut/NN_nominal/$i ../../boost_et_2016_NoCut/NN_nominal/$i ; done
cd boost_me_2018_NoCut/NN_nominal ;  for i in *.root ; do hadd -f ../../Sum_em/$i $i ../../boost_me_2017_NoCut/NN_nominal/$i ../../boost_me_2016_NoCut/NN_nominal/$i  ../../boost_em_2018_NoCut/NN_nominal/$i ../../boost_em_2017_NoCut/NN_nominal/$i ../../boost_em_2016_NoCut/NN_nominal/$i   ; done


#Make the combined training files
python preprocess_noSys.py -i ../Analysis/Output/trees/ALL_BoostNew_v5/Sum_mt_/ -o threeYear_mt
python preprocess_noSys.py -i ../Analysis/Output/trees/ALL_BoostNew_v5/Sum_et_/ -o threeYear_et
python preprocess_noSys.py -i ../Analysis/Output/trees/ALL_BoostNew_v5/Sum_tt_/ -o threeYear_tt
python preprocess_noSys.py -i ../Analysis/Output/trees/ALL_BoostNew_v5/Sum_em_/ -o threeYear_em


#Run the training
python train_noSys.py --signal JJH125 --ZTT ZTT --QCD NonDY --input datasets/threeYear_mt.h5 --model threeYear_mt
python train_noSys.py --signal JJH125 --ZTT ZTT --QCD NonDY --input datasets/threeYear_et.h5 --model threeYear_et
python train_noSys.py --signal JJH125 --ZTT ZTT --QCD NonDY --input datasets/threeYear_tt.h5 --model threeYear_tt
python train_noSys.py --signal JJH125 --ZTT ZTT --QCD NonDY --input datasets/threeYear_em.h5 --model threeYear_em



python preprocess.py -i ../Analysis/Output/trees/ALL_BoostNew_v2/BoostNew_em_2016_v2/NN_nominal/ -o testData_em_2016_f2
python train.py --signal JJH125 --ZTT ZTT --QCD NonDY --input datasets/testData_em_2016_f2.h5 --model outputModel_em_2016_f2
python classify.py -i datasets/testData_em_2016_f2.h5 -m models/outputModel_em_2016_f2.hdf5 --dir ../Analysis/Output/trees/ALL_BoostNew_v2/BoostNew_em_2016_v2/NN_nominal/ --output-dir me_16_v2_NN_f2


#NN using Condor
# First list all directories in an Input file
ls -d -1 ../Analysis/Output/trees/ALL_BoostNew_v2/BoostNew_*_201*/NN_n* > InputSamples_NN_Total_v1.txt

python makeSubmissionPackage_NN_Sys.py -n Total_v1 -i InputSamples_NN_Total_v1.txt
cd Files_Total_v1
condor_submit Submit_batch_Total_v1.jdl

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# NN Systematics
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

# prepare the nominal trainings
1)
for i in em et mt tt; do echo $i----- ; sh Nominal_Training.sh ../Analysis/Output/trees/ALL_BoostNew_v6_NoCut/Sum\_${i} $i ; done

2)
sh Nominal_Training.sh ../Analysis/Output/trees/ALL_BoostNew_v4/Sum_tt_ tt
sh Nominal_Training.sh ../Analysis/Output/trees/ALL_BoostNew_v4/Sum_mt_ mt
sh Nominal_Training.sh ../Analysis/Output/trees/ALL_BoostNew_v4/Sum_et_ et
sh Nominal_Training.sh ../Analysis/Output/trees/ALL_BoostNew_v4/Sum_em_ em

3)
cp datasets/NominalTraining_em.h5 datasets/NominalTraining_me.h5
cp models/outputModel_NominalTraining_em.hdf5  models/outputModel_NominalTraining_me.hdf5

4)
cp datasets/NominalPreprocess_* /eos/uscms/store/user/abdollah/NominalPreprocess/.
cp models/outputModel_NominalTraining_* /eos/uscms/store/user/abdollah/NominalTrainings/.



5)
# list all NN_XXX (nominal and Sys) in a .txt file
ls -d -1 ../Analysis/Output/trees/ALL_BoostNew_v5/boost_*/NN* > InputSamples_NN_Total_v4.txt

#for i in NominalTraining_* ; do mv $i ${i/"NominalTraining"/"NominalPreprocess"}; done
python makeSubmissionPackage_NN_Sys.py -n Total_v3_Sys -i InputSamples_NN_Total_v3_Sys.txt

#The output will appear in /eos/uscms/store/user/abdollah/NN_output_Sys
# To Collect the NN outputs
#No need to Collect

# To Draw the NN output quickly



#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Run dataCard maker on all NN
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
python DataCard_Producer.py -i /eos/uscms/store/user/abdollah/NN_output_Sys/ -s Sysv2
cd Output/templates
for i in em et mt tt me; do for j in 2016 2017 2018; do hadd -f V6_${i}_${j}_NN.root $i$j*Sysv6.root; done ; done

hadd -f NewV6me_2016_NN.root V6_*_2016_NN.root
hadd -f NewV6me_2017_NN.root V6_*_2017_NN.root
hadd -f NewV6me_2018_NN.root V6_*_2018_NN.root



cp NewV6_201*_NN.root  /uscms_data/d3/abdollah/Analysis/Limit/CMSSW_10_2_13/src/CombineHarvester/CombineTools/bin/aux/.


#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Make DataCard both with m_sv and NN
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


python xrun.py -i All_v2/boost_et_2016_v2_NN -p test

# make datacard with obervable NN_disc
for i in yOptimization/V1_First/NN_BoostNew_*; do python xrun.py  -i $i -p 13 -o NN_disc ; done

# make templates for all variavles listed in xrun.py
for i in yOptimization/V1_First/NN_BoostNew_*; do python xrun.py  -i $i -p 15 -o all; done



# check plottings
for i in Output/templates/*_m_sv_False.root ; do python autoplot.py -i $i  -p test1; done



hadd V1_2016_NN.root et2016_NN_disc.root mt2016_NN_disc.root
hadd V1_2016_m_sv.root et2016_m_sv.root mt2016_m_sv.root
hadd V1_2017_NN.root et2017_NN_disc.root mt2017_NN_disc.root
hadd V1_2017_m_sv.root et2017_m_sv.root mt2017_m_sv.root
hadd V1_2018_NN.root et2018_NN_disc.root mt2018_NN_disc.root
hadd V1_2018_m_sv.root et2018_m_sv.root mt2018_m_sv.root



hadd aux/V8_2016_NN.root aux/*2016_NN_disc.root
hadd aux/V8_2017_NN.root aux/*2017_NN_disc.root
hadd aux/V8_2018_NN.root aux/*2018_NN_disc.root



#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Run the limit
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

# Run limit for all 4 final states & 3 years + fit + draw postfit
python QuickLimit.py NewV5 NN


# To print only the values
python QuickLimit_printVal.py NewV3


#Drawing the postfit plots:
for i in NewV3/postfit_shapes_NewV3_201* ; do python Draw_POSTPREFIT_Boost.py $i test1; done






BoostedTau_limit_V1 --prefix="V9" --postfix="V1/2016" --year=2016 --Var=NN
BoostedTau_limit_V1 --prefix="V9" --postfix="V1/2017" --year=2017 --Var=NN
BoostedTau_limit_V1 --prefix="V9" --postfix="V1/2018" --year=2018 --Var=NN

sh add_auto_MC_Stat.sh V1

combine -M Significance -d allCmb.txt -t -1 -m 125 --expectSignal=1
PostFitShapesFromWorkspace -w ws.root -f fitDiagnostics.root:fit_s --postfit --print -d allCmb.txt -o postfit_shapes.root -m 125

for i in em et mt tt me ; do for j in 2016 2017 2018; do echo  V2/$j/$j/125/*$i*txt; cd V2/$j/$j/125/ ; combine -M Significance -d *$i*.txt -t -1 -m 125 --expectSignal=1 ; mv higgsCombineTest.Significance.mH125.root higgsCombineTest.Significance.mH125$i$j.root ; cd - ; done; done
python getlim.py V2/2016/
python getlim.py V2/2017/
python getlim.py V2/2018/
cd V2/
combineCards.py 201*/*/125/*txt > cmb.txt
combine -M Significance -d cmb.txt -t -1 -m 125 --expectSignal=1
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





#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Preparing Datacard for Differential Measurements
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# first make several copy of the Higgs files 

#Step ---- 1
sh
#for i in mt_2018_addHpT_* ; do for j in 0_350 350_450 450_600 GT600  ; do echo $i ; cp $i/H125.root $i/ggH_PTH_$j.root; done ; done
for i in V7_FinalNNResults/NN*nominal* ; do for j in 0_350 350_450 450_600 GT600  ; do echo $i ; cp $i/ggH125.root $i/ggH_PTH_${j}125.root; done ; done
exit

#Step ---- 2
./build DiffMeasure_em.cc DiffMeasure_em
./build DiffMeasure_lt.cc DiffMeasure_lt
./build DiffMeasure_tt.cc DiffMeasure_tt


#Step ---- 3
#for i in yOptimization/V1_First/NN_BoostNew_*; do python DiffMeasure_DataCardProducer.py  -i $i -p 13 -o NN_disc ; done
#New command
for i in V7_FinalNNResults/NN_boost_*; do python DiffMeasure_DataCardProducer.py  -i $i -p Diff_V7 -o NN_disc ; done

#Step ---- 3 (including shape systematics)
mkdir NN_output_Sys_Diff
cd  NN_output_Sys
cp -r *_V8NN_* ../NN_output_Sys_Diff/

python DiffMeasure_DataCardProducer.py -i /eos/uscms/store/user/abdollah/NN_output_Sys/ -p DiffSysV1 -o NN_disc


#for i in 0 1 2 3 ; do for j in 2016 2017 2018 ; do hadd -f Output/datacard/V10\_bin$i\_$j\_NN.root Output/templates/*$j\_NN_disc\__bin$i.root ; done ; done
#new command
for j in 2016 2017 2018 ; do hadd -f Output/datacard/Diff_V7_${j}_NN.root Output/templates/*${j}*Diff_V7*.root ; done
#The coutcome will be located in Output/datacard

# scp to cmslpc
python _scp_lpc.py Output/datacard/Diff_V7_*

#The file to edit is
BoostedTau_DiffXS.cpp

BoostedTau_DiffXS --prefix="Diff_V7" --postfix="Vdiff7" --year=2016 --Var=NN
BoostedTau_DiffXS --prefix="Diff_V7" --postfix="Vdiff7" --year=2017 --Var=NN
BoostedTau_DiffXS --prefix="Diff_V7" --postfix="Vdiff7" --year=2018 --Var=NN

sh add_auto_MC_Stat.sh Vdiff7

combineCards.py */125/H_mt_* > all.txt


text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO 'map=.*/.*H.*PTH_0_350.*:r_H_PTH_0_350[1,-25,25]' --PO 'map=.*/.*H.*PTH_350_450.*:r_H_PTH_350_450[1,-25,25]' --PO 'map=.*/.*H.*PTH_450_600.*:r_H_PTH_450_600[1,-25,25]' --PO 'map=.*/.*H.*PTH_G.600.*:r_H_PTH_GT600[1,-25,25]' all.txt  -o Workspace_pth_all.root -m 125


combine Workspace_pth_all.root --robustFit=1 --preFitValue=1. --X-rtd MINIMIZER_analytic --algo=singles --cl=0.68 --setParameters r_H_PTH_0_350=1.0,r_H_PTH_350_450=1.0,r_H_PTH_450_600=1.0,r_H_PTH_GT600=1.0 --setParameterRanges r_H_PTH_0_350=-15,15:r_H_PTH_350_450=-15,15:r_H_PTH_450_600=-15,15:r_H_PTH_GT450=-15,15 --floatOtherPOIs=1 -M MultiDimFit -n test_param0 -m 125 --cminDefaultMinimizerStrategy=0

#only mt
#   r_H_PTH_450_600 :    +4.012   -2.765/+2.907 (68%)
#   r_H_PTH_350_450 :    +0.592   -2.250/+2.281 (68%)
#     r_H_PTH_0_350 :    +0.079   -1.359/+1.483 (68%)
#     r_H_PTH_GT600 :    -1.431   -2.773/+2.692 (68%)

#all combined 3 years
#   r_H_PTH_450_600 :    +2.858   -1.206/+1.269 (68%)
#   r_H_PTH_350_450 :    -1.142   -1.305/+1.330 (68%)
#     r_H_PTH_0_350 :    +1.768   -0.987/+1.048 (68%)
#     r_H_PTH_GT600 :    -1.704   -0.709/+0.879 (68%)


#   r_H_PTH_450_600 :    +4.009   -1.467/+1.510 (68%)
#   r_H_PTH_350_450 :    -1.804   -1.510/+1.524 (68%)
#     r_H_PTH_0_350 :    +2.281   -1.130/+1.207 (68%)
#     r_H_PTH_GT600 :    -3.425   -1.175/+1.621 (68%)
     
     
#V2/2016/2016/125/higgsCombineTest.Significance.mH125em2016.root
#2016 -1.0 0.15
#V2/2016/2016/125/higgsCombineTest.Significance.mH125et2016.root
#2016 -1.0 0.78
#V2/2016/2016/125/higgsCombineTest.Significance.mH125mt2016.root
#2016 -1.0 0.99
#V2/2016/2016/125/higgsCombineTest.Significance.mH125tt2016.root
#2016 -1.0 0.73
#V2/2016/2016/125/higgsCombineTest.Significance.mH125me2016.root
#2016 -1.0 0.41
#[abdollah@cmslpc133 bin]$ python getlim.py V2/2017/
#V2/2017/2017/125/higgsCombineTest.Significance.mH125em2017.root
#2017 -1.0 0.1
#V2/2017/2017/125/higgsCombineTest.Significance.mH125et2017.root
#2017 -1.0 0.8
#V2/2017/2017/125/higgsCombineTest.Significance.mH125mt2017.root
#2017 -1.0 1.07
#V2/2017/2017/125/higgsCombineTest.Significance.mH125tt2017.root
#2017 -1.0 0.65
#V2/2017/2017/125/higgsCombineTest.Significance.mH125me2017.root
#2017 -1.0 0.34
#[abdollah@cmslpc133 bin]$ python getlim.py V2/2018/
#V2/2018/2018/125/higgsCombineTest.Significance.mH125em2018.root
#2018 -1.0 0.2
#V2/2018/2018/125/higgsCombineTest.Significance.mH125et2018.root
#2018 -1.0 0.95
#V2/2018/2018/125/higgsCombineTest.Significance.mH125mt2018.root
#2018 -1.0 1.03
#V2/2018/2018/125/higgsCombineTest.Significance.mH125tt2018.root
#2018 -1.0 0.89
#V2/2018/2018/125/higgsCombineTest.Significance.mH125me2018.root
#2018 -1.0 0.43

# -- Significance --
#Significance: 2.57664
#Done in 0.05 min (cpu), 0.05 min (real)



# New with macthed Tau
em 2018
0.474567566797
et 2018
1.49801228118
mt 2018
1.29504844403
tt 2018
1.6342696217

#past
em 2018
0.594751852479
et 2018
1.66997922325
mt 2018
1.43625456153
tt 2018
1.6342696217



#only em
Done in 0.00 min (cpu), 0.00 min (real)
em 2016
0.320824308285
em 2017
0.221253424583
em 2018
0.333552192876


#only me
em 2016
0.549105320083
em 2017
0.421811404775
em 2018
0.655144551337



#Noshape sys
mt 2016
1.44125692513
mt 2017
1.30972793045
mt 2018
1.5148383445



#Exclude QCD and DY sys
mt 2016
1.24239364606
mt 2017
1.07673174618
mt 2018
1.02681514644

#Exclude QCD and DY sys & TT
mt 2016
1.24245735147
mt 2017
1.0768550741
mt 2018
1.02683346981

#Exclude QCD and DY sys & TT & TES
mt 2016
1.32754820474
mt 2017
1.17401148802
mt 2018
1.06001050595

#Exclude QCD and DY sys & TT & TES & JES
mt 2016
1.33023843407
mt 2017
1.17909765048
mt 2018
1.07293909935

#Exclude QCD and DY sys & TT & TES & MES UES
mt 2016
1.35480306128
mt 2017
1.21805786314
mt 2018
1.08342143756
//
et 2016
1.11578412277
et 2017
1.01400357695
et 2018
1.26091447844


#Exclude QCD and DY sys & TT & TES & MES UES * MES JES
mt 2016
1.44119987657
mt 2017
1.3097348754
mt 2018
1.51483834411
#//
et 2016
1.17926297422
et 2017
1.08751081186
et 2018
1.62374161174
