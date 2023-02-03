## Steps for Running analysis

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# ggNtuple Production
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Skim
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#Location of the latest Data and MC samples:

#Data
/eos/uscms/store/user/abdollah/BoostedH4/2016/Data/
/eos/uscms/store/user/abdollah/BoostedH4/2017/Data/
/eos/uscms/store/user/abdollah/BoostedH4/2018/Data/

# Only TT samples
/eos/uscms/store/user/abdollah/BoostedH4/2016/MC/
/eos/uscms/store/user/abdollah/BoostedH4/2017/MC/
/eos/uscms/store/user/abdollah/BoostedH4/2018/MC/

# Only DY samples:
/eos/uscms/store/group/lpcggntuples/ggNtuples/13TeV/BoostH3/2016/MC/
/eos/uscms/store/group/lpcggntuples/ggNtuples/13TeV/BoostH3/2017/MC/
/eos/uscms/store/group/lpcggntuples/ggNtuples/13TeV/BoostH3/2018/MC/

# all other MC samples:
/eos/uscms/store/group/lpcggntuples/ggNtuples/13TeV/BoostH2/2016/MC/
/eos/uscms/store/group/lpcggntuples/ggNtuples/13TeV/BoostH2/2017/MC/
/eos/uscms/store/group/lpcggntuples/ggNtuples/13TeV/BoostH2/2018/MC/





for i in et mt tt em me ;do for j in 2016 2017 2018 ; do  python makeSubmissionPackage.py -x SkimerBoost_$i -n InputSample${i}_${j}_v7_mc -i InputSample_${j}_mc_v7.txt -o /store/user/abdollah/SkimBoostedH2/${j}/${i}/v7/ ; done; done

for i in Files_InputSample*_v7_mc; do echo $i ; cd $i ; condor_submit Submit_batch_*.jdl; cd -   ; done


python makeSubmissionPackage.py -x SkimerBoost_et -n et_2016_v7_data -i InputSample_2016_Ele.txt -o /store/user/abdollah/SkimBoostedH2/2016/et/v7/
python makeSubmissionPackage.py -x SkimerBoost_et -n et_2017_v7_data -i InputSample_2017_Ele.txt -o /store/user/abdollah/SkimBoostedH2/2017/et/v7/
python makeSubmissionPackage.py -x SkimerBoost_et -n et_2018_v7_data -i InputSample_2018_Ele.txt -o /store/user/abdollah/SkimBoostedH2/2018/et/v7/

python makeSubmissionPackage.py -x SkimerBoost_em -n em_2016_v7_data -i InputSample_2016_Ele.txt -o /store/user/abdollah/SkimBoostedH2/2016/em/v7/
python makeSubmissionPackage.py -x SkimerBoost_em -n em_2017_v7_data -i InputSample_2017_Ele.txt -o /store/user/abdollah/SkimBoostedH2/2017/em/v7/
python makeSubmissionPackage.py -x SkimerBoost_em -n em_2018_v7_data -i InputSample_2018_Ele.txt -o /store/user/abdollah/SkimBoostedH2/2018/em/v7/


python makeSubmissionPackage.py -x SkimerBoost_mt -n mt_2016_v7_data -i InputSample_2016_Mu.txt -o /store/user/abdollah/SkimBoostedH2/2016/mt/v7/
python makeSubmissionPackage.py -x SkimerBoost_mt -n mt_2017_v7_data -i InputSample_2017_Mu.txt -o /store/user/abdollah/SkimBoostedH2/2017/mt/v7/
python makeSubmissionPackage.py -x SkimerBoost_mt -n mt_2018_v7_data -i InputSample_2018_Mu.txt -o /store/user/abdollah/SkimBoostedH2/2018/mt/v7/

python makeSubmissionPackage.py -x SkimerBoost_me -n me_2016_v7_data -i InputSample_2016_Mu.txt -o /store/user/abdollah/SkimBoostedH2/2016/me/v7/
python makeSubmissionPackage.py -x SkimerBoost_me -n me_2017_v7_data -i InputSample_2017_Mu.txt -o /store/user/abdollah/SkimBoostedH2/2017/me/v7/
python makeSubmissionPackage.py -x SkimerBoost_me -n me_2018_v7_data -i InputSample_2018_Mu.txt -o /store/user/abdollah/SkimBoostedH2/2018/me/v7/


python makeSubmissionPackage.py -x SkimerBoost_tt_ht     -n tt_2016_v7_data_ht -i InputSample_2016_JetHT.txt -o /store/user/abdollah/SkimBoostedH2/2016/tt/v7/
python makeSubmissionPackage.py -x SkimerBoost_tt_htmht  -n tt_2016_v7_data_htmht -i InputSample_2016_HTMHT.txt -o /store/user/abdollah/SkimBoostedH2/2016/tt/v7/
python makeSubmissionPackage.py -x SkimerBoost_tt_ht     -n tt_2017_v7_data_ht -i InputSample_2017_JetHT.txt -o /store/user/abdollah/SkimBoostedH2/2017/tt/v7/
python makeSubmissionPackage.py -x SkimerBoost_tt_htmht  -n tt_2017_v7_data_htmht -i InputSample_2017_HTMHT.txt -o /store/user/abdollah/SkimBoostedH2/2017/tt/v7/
python makeSubmissionPackage.py -x SkimerBoost_tt_ht        -n tt_2018_v7_data -i InputSample_2018_JetHT.txt -o /store/user/abdollah/SkimBoostedH2/2018/tt/v7/



for i in Files_*_v7_data*; do echo $i ; cd $i ; condor_submit Submit_batch_*.jdl; cd -   ; done


##embedded  Not needed anymore
#python makeSubmissionPackage.py -x SkimerBoost_et -n et_2018_v0_embed -i InputSample_Embed_ElTau_2018.txt  -o /store/user/abdollah/SkimBoostedH3/2018/et/v0/
#python makeSubmissionPackage.py -x SkimerBoost_mt -n mt_2018_v0_embed -i InputSample_Embed_MuTau_2018.txt  -o /store/user/abdollah/SkimBoostedH3/2018/mt/v0/
#python makeSubmissionPackage.py -x SkimerBoost_tt -n tt_2018_v0_embed -i InputSample_Embed_TauTau_2018.txt  -o /store/user/abdollah/SkimBoostedH3/2018/tt/v0/
#python makeSubmissionPackage.py -x SkimerBoost_em -n em_2018_v0_embed -i InputSample_Embed_ElMu_2018.txt  -o /store/user/abdollah/SkimBoostedH3/2018/em/v0/
#python makeSubmissionPackage.py -x SkimerBoost_me -n me_2018_v0_embed -i InputSample_Embed_ElMu_2018.txt  -o /store/user/abdollah/SkimBoostedH3/2018/me/v0/



sh
for i in Files*v2* ; do cd $i ; condor_submit Submit_batch_*.jdl; cd -; done



#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# fast MTT
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
cd /uscms_data/d3/abdollah/Analysis/ggNtuple/FastMTT/CMSSW_9_4_4/src/SubmitSVFit/skim
python makeSubmissionPackage_sv.py -x FastMTT -i Input_em_2017.txt -n em_2017_v1 -o /store/user/abdollah/SkimBoostedH/2017/em/v1_fast

# multiple submission
for i in mt et em me tt; do for j in 2016 2017 2018 ; do python makeSubmissionPackage_sv.py -x FastMTT -n $i\_$j\_v7 -i /eos/uscms/store/user/abdollah/SkimBoostedH2/$j/$i/v7; done; done
# submit
for i in Files_*v7; do cd $i/; condor_submit Submit_batch_*.jdl; cd -; done
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# hadd
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#python hadd_skim.py -g '/eos/uscms/store/user/abdollah/BoostedH/2018/Data/*/*' -s /eos/uscms/store/user/abdollah/SkimBoostedH/2018/em/v1_fast -n v1_em_2018_data
#python hadd_skim.py -i Files_mm_2018_mc_v2/InputSample_2018_mc.txt -s /eos/uscms/store/user/abdollah/SkimBoostedH3/2018/mm/v3 -n v3_mm_2018

# This is for all channel for MC
for i in 2016 2017 2018 ; do for j in mt et tt em me ; do  python hadd_skim.py -i Files_InputSample${j}_${i}_v7_mc/InputSample_${i}_mc_v7.txt -s /eos/uscms/store/user/abdollah/SkimBoostedH2/$i/$j/v7_fast -n v7-$j-$i-mc; done; done


#for i in 2016 2017 2018 ; do for j in mt et tt em me ; do  python hadd_skim.py -i Files_InputSample${j}_${i}_dy_mc/InputSample_${i}_mc_DY.txt -s /eos/uscms/store/user/abdollah/SkimBoostedH3/$i/$j/v6dy_fast -n v6dy-$j-$i-mc; done; done

#This is for Data
for i in 2016 2017 2018 ; do for j in et  em ; do  python hadd_skim.py -i Files\_$j\_$i\_v7\_data/InputSample\_$i\_Ele.txt -s /eos/uscms/store/user/abdollah/SkimBoostedH2/$i/$j/v7_fast -n v7-$j-$i; done; done
for i in 2016 2017 2018 ; do for j in mt  me ; do  python hadd_skim.py -i Files\_$j\_$i\_v7\_data/InputSample\_$i\_Mu.txt  -s /eos/uscms/store/user/abdollah/SkimBoostedH2/$i/$j/v7_fast -n v7-$j-$i; done; done

for i in 2016 2017 ; do for j in tt ; do  python hadd_skim.py -i Files\_$j\_$i\_v7\_data\_ht/InputSample\_$i\_JetHT.txt  -s /eos/uscms/store/user/abdollah/SkimBoostedH2/$i/$j/v7_fast -n v7-$j-$i-ht; done; done
for i in 2016 2017 ; do for j in tt ; do  python hadd_skim.py -i Files\_$j\_$i\_v7\_data\_htmht/InputSample\_$i\_HTMHT.txt  -s /eos/uscms/store/user/abdollah/SkimBoostedH2/$i/$j/v7_fast -n v7-$j-$i-htmht; done; done
for i in 2018 ; do for j in tt ; do  python hadd_skim.py -i Files\_$j\_$i\_v7\_data/InputSample\_$i\_JetHT.txt  -s /eos/uscms/store/user/abdollah/SkimBoostedH2/$i/$j/v7_fast -n v7-$j-$i-ht; done; done

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#Renaming
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
for i in /eos/uscms/store/user/abdollah/SkimBoostedH2/2016/*/v7_fast_Hadd/ ; do sh _rename_2016.sh $i ; done
for i in /eos/uscms/store/user/abdollah/SkimBoostedH2/2017/*/v7_fast_Hadd/ ; do sh _rename_2017.sh $i ; done
for i in /eos/uscms/store/user/abdollah/SkimBoostedH2/2018/*/v7_fast_Hadd/ ; do sh _rename_2018.sh $i ; done

for i in tt et mt em me ; do for j in 2016 2017 2018; do sh _rename_$j.sh /eos/uscms/store/user/abdollah/SkimBoostedH2/$j/$i/v7_fast_Hadd ; done; done;

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Analysis
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

python automate_analysis.py -e BoostedHTT_mt.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH3/2018/mt/v3_fast_Hadd/ -o boost_mt_RecoilCheck_2018
python automate_analysis.py -e BoostedHTT_mt.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH3/2018/mt/v2_fast_Hadd/ -o boost_mt_RecoilCheck_2018 --sys


for i in em et  ; do python automate_analysis.py -e BoostedHTT_${i}.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH2/2018/${i}/v7_fast_Hadd/ -o boost_${i}_2018_v7_firstTry --sys; done
for i in em et  ; do python automate_analysis.py -e BoostedHTT_${i}.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH2/2017/${i}/v7_fast_Hadd/ -o boost_${i}_2017_v7_firstTry --sys; done
for i in em et  ; do python automate_analysis.py -e BoostedHTT_${i}.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH2/2016/${i}/v7_fast_Hadd/ -o boost_${i}_2016_v7_firstTry --sys; done

for i in  me  mt ; do python automate_analysis.py -e BoostedHTT_${i}.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH2/2018/${i}/v7_fast_Hadd/ -o boost_${i}_2018_v7_firstTry --sys; done
for i in  me  mt; do python automate_analysis.py -e BoostedHTT_${i}.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH2/2017/${i}/v7_fast_Hadd/ -o boost_${i}_2017_v7_firstTry --sys; done
for i in  me  mt; do python automate_analysis.py -e BoostedHTT_${i}.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH2/2016/${i}/v7_fast_Hadd/ -o boost_${i}_2016_v7_firstTry --sys; done


for i in  tt; do python automate_analysis.py -e BoostedHTT_${i}.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH2/2018/${i}/v7_fast_Hadd/ -o boost_${i}_2018_v7_firstTry --sys; done
for i in  tt; do python automate_analysis.py -e BoostedHTT_${i}.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH2/2017/${i}/v7_fast_Hadd/ -o boost_${i}_2017_v7_firstTry --sys; done
for i in  tt; do python automate_analysis.py -e BoostedHTT_${i}.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH2/2016/${i}/v7_fast_Hadd/ -o boost_${i}_2016_v7_firstTry --sys; done



/eos/uscms/store/user/abdollah/SkimBoostedH2/2016/tt/v6dy_fast_Hadd

## Sys
#for i in em me et  ; do python automate_analysis.py -e BoostedHTT_${i}.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH3/2018/${i}/v2_fast_Hadd/ -o boost_${i}_2018_V12_newDM --sys; done
#for i in em me et  ; do python automate_analysis.py -e BoostedHTT_${i}.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH3/2017/${i}/v2_fast_Hadd/ -o boost_${i}_2017_V12_newDM --sys; done
#for i in em me et  ; do python automate_analysis.py -e BoostedHTT_${i}.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH3/2016/${i}/v2_fast_Hadd/ -o boost_${i}_2016_V12_newDM --sys; done
#
#for i in   et mt tt; do python automate_analysis.py -e BoostedHTT_${i}.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH3/2018/${i}/v2_fast_Hadd/ -o boost_${i}_2018_V15_TES --sys; done
#for i in   et mt tt; do python automate_analysis.py -e BoostedHTT_${i}.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH3/2017/${i}/v2_fast_Hadd/ -o boost_${i}_2017_V15_TES --sys; done
#for i in   et mt tt; do python automate_analysis.py -e BoostedHTT_${i}.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH3/2016/${i}/v2_fast_Hadd/ -o boost_${i}_2016_V15_TES --sys; done
#

#for Embed
for i in A B C D; do ./BoostedHTT_mt.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH3/2018/mt/v0_fast_Hadd/ -s EmbeddingRun2018${i}_MuTauFinalState-inputDoubleMu_102X_miniAOD-v1 -d ./;  ./BoostedHTT_et.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH3/2018/et/v0_fast_Hadd/ -s EmbeddingRun2018${i}_ElTauFinalState-inputDoubleMu_102X_miniAOD-v1 -d ./;   ./BoostedHTT_em.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH3/2018/em/v0_fast_Hadd/ -s EmbeddingRun2018${i}_ElMuFinalState-inputDoubleMu_102X_miniAOD-v1 -d ./; ./BoostedHTT_me.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH3/2018/me/v0_fast_Hadd/ -s EmbeddingRun2018${i}_ElMuFinalState-inputDoubleMu_102X_miniAOD-v1 -d ./;  ./BoostedHTT_tt.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH3/2018/tt/v0_fast_Hadd/ -s EmbeddingRun2018${i}_TauTauFinalState-inputDoubleMu_102X_miniAOD-v1 -d ./; done


for i in A B C D; do  ./BoostedHTT_em.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH3/2018/em/v0_fast_Hadd/ -s EmbeddingRun2018${i}_ElMuFinalState-inputDoubleMu_102X_miniAOD-v1 -d ./; done
for i in A B C D; do  ./BoostedHTT_me.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH3/2018/me/v0_fast_Hadd/ -s EmbeddingRun2018${i}_ElMuFinalState-inputDoubleMu_102X_miniAOD-v1 -d ./;  done


hadd -f Output/trees/Embed_mt_v1.root Output/trees/EmbeddingRun2018*_MuTauFinalState* ;
hadd -f Output/trees/Embed_et_v1.root Output/trees/EmbeddingRun2018*_ElTauFinalState* ;
hadd -f Output/trees/Embed_em_v1.root Output/trees/EmbeddingRun2018*_ElMuFinalState* ;
hadd -f Output/trees/Embed_me_v1.root Output/trees/EmbeddingRun2018*_ElMuFinalState* ;
hadd -f Output/trees/Embed_tt_v1.root Output/trees/EmbeddingRun2018*_TauTauFinalState* ;

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Hadd
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
sh hadd.sh Output/trees/boost_mt_RecoilCheck_2018

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#                                               Control plots
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Single plotting

#./process_trees_lt_fr -d ../V20_pdfscale_noSys/2016_mt/  --suf test1 -v m_sv -b 30 0 300
./build process_trees_lt_fr.cc process_trees_lt_fr
./process_trees_lt_fr -d Output/trees/boost_mt_2016_v7_firstTry/NN_nominal/ --suf test -v m_sv -b 30 0 300

#python autoplot.py -i Output/templates/mt2016_m_sv_test1.root   -p mt_plots_v1



#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# single plotting for single channel/year
python ControlPlotMaker.py -i ../V20_pdfscale_noSys/2016_mt/ -p test -o m_sv
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Full plotting for single channel/year
python ControlPlotMaker.py -i ../V20_pdfscale_noSys/2016_mt/ -p test -o all
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Full plotting for all channel/year
sh
for i in ../V20_pdfscale_noSys/201*; do python ControlPlotMaker.py -i $i -p NewAN -o all; done
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Drawing the plots
# We need first to combine em and me channels:
mkdir NewAN_forPreApproval
mv *t201*NewAN*root NewAN_forPreApproval
cd NewAN_forPreApproval
sh
for i in tt201* ; do hadd  ${i/tt2/em2} ../${i/tt2/em2} ../${i/tt2/me2} ; done

# from the Analysis run the following command
for i in Output/templates/NewAN_forPreApproval/*_m_sv_NewAN.root ; do python autoplot.py -i $i  -p NewAN ; done

# The plots are available in the Output/plots directory
mkdir NewAN_ControlPlots_PreApproval
mv NewAN_*pdf NewAN_ControlPlots_PreApproval
cp NewAN_ControlPlots_PreApproval/NewAN_*2016* /Users/abdollah/Documents/Publication/Note/AN-21-012/figure/control2016/.
cp NewAN_ControlPlots_PreApproval/NewAN_*2017* /Users/abdollah/Documents/Publication/Note/AN-21-012/figure/control2017/.
cp NewAN_ControlPlots_PreApproval/NewAN_*2018* /Users/abdollah/Documents/Publication/Note/AN-21-012/figure/control2018/.

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Check m_sv for all 5 channels and 3 years
python plotChecker.py



./DiffMeasure_lt -d yOptimization/V1_First/NN_BoostNew_mt_2018_v2_NN/ --suf test1 -v m_sv -b 20 0 200 -c higgs_pT -l 0 -h 500


#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# NN just on local on one directory (with no systematics)
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

python preprocess.py  -i ../Analysis/Output/trees/ALL_Boost_v7/Sum_mt -o Sum_mt_2016
python train.py       --signal JJH125 --background NonDY --background2 ZTT --input datasets/Sum_mt_2016.h5 --model Sum_mt_2016
python preprocess.py  -i ../Analysis/Output/trees/ALL_Boost_v7/boost_mt_2016_V6_nonDYTT/NN_nominal/ -o test_mt_2016
python classify.py --input-boost datasets/test_mt_2016.h5 --model-boost models/Sum_mt_2016.hdf5 --dir ../Analysis/Output/trees/ALL_Boost_v7/boost_mt_2016_V6_nonDYTT/NN_nominal/  --output-dir out_mt_2016_TEST -s 1 --nominal_input datasets/Sum_mt_2016.h5

#python classify.py -i datasets/test_mt_2016.h5 -m models/test_mt_2016.hdf5 --dir ../Analysis/Output/trees/ALL_Boost_v7/boost_mt_2016_V6_nonDYTT/NN_nominal --output-dir out_test_mt_2016

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# NN
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


# create some directories for combination
# Then hadd all 3 years in the same direcory
#Copy all folders in to ALL_BoostNew_v5
#creat combine directories:
mkdir  Sum_tt_v7 Sum_mt_v7 Sum_et_v7 Sum_em_v7

sh
for i in et mt tt; do  cd boost_${i}_2018_v7_firstTry/NN_nominal ; for j in *.root ; do  hadd ../../Sum_${i}/$j $j ../../boost_${i}_2017_v7_firstTry//NN_nominal/$j ../../boost_${i}_2016_v7_firstTry//NN_nominal/$j ; done ;cd ../..; done
cd boost_me_2018_v7_firstTry/NN_nominal ;  for i in *.root ; do hadd -f ../../Sum_em_v7/$i $i ../../boost_me_2017_v7_firstTry/NN_nominal/$i ../../boost_me_2016_v7_firstTry/NN_nominal/$i ../../boost_em_2018_v7_firstTry/NN_nominal/$i ../../boost_em_2017_v7_firstTry/NN_nominal/$i ../../boost_em_2016_v7_firstTry/NN_nominal/$i   ; done




#Make the combined training files
python preprocess_noSys.py -i ../Analysis/Output/trees/ALL_Boost_v7/Sum_mt_v7/ -o threeYear_mt
python preprocess_noSys.py -i ../Analysis/Output/trees/ALL_Boost_v7/Sum_et_v7/ -o threeYear_et
python preprocess_noSys.py -i ../Analysis/Output/trees/ALL_Boost_v7/Sum_tt_v7/ -o threeYear_tt
python preprocess_noSys.py -i ../Analysis/Output/trees/ALL_Boost_v7/Sum_em_v7/ -o threeYear_em
#
#
##Run the training
python train_noSys.py --signal JJH125 --background NonDY --background2 ZTT --input datasets/threeYear_mt.h5 --model threeYear_mt
python train_noSys.py --signal JJH125 --background NonDY --background2 ZTT --input datasets/threeYear_et.h5 --model threeYear_et
python train_noSys.py --signal JJH125 --background NonDY --background2 ZTT --input datasets/threeYear_tt.h5 --model threeYear_tt
python train_noSys.py --signal JJH125 --background NonDY --background2 ZTT --input datasets/threeYear_em.h5 --model threeYear_em



#for i in mt et tt;
#do
python preprocess_noSys.py -i ../Analysis/Output/trees/boost_mt_2016_V15_TES/NN_nominal/ -o debug_mt_2016
python train_noSys.py --signal JJH125 --background ZTT --background2 NonDY --input datasets/debug_mt_2016.h5 --model debug_mt_2016
python classify_noSys.py -i datasets/debug_mt_2016.h5 -m models/debug_mt_2016.hdf5 --dir ../Analysis/Output/trees/boost_mt_2016_V15_TES/NN_nominal/ --output-dir debug_mt_2016




python preprocess.py -i ../Analysis/Output/trees/ALL_BoostNew_v2/BoostNew_em_2016_v2/NN_nominal/ -o testData_em_2016_f2
python train.py --signal JJH125 --background NonDY --background2 ZTT --input datasets/testData_em_2016_f2.h5 --model outputModel_em_2016_f2
python classify.py -i datasets/testData_em_2016_f2.h5 -m models/outputModel_em_2016_f2.hdf5 --dir ../Analysis/Output/trees/ALL_BoostNew_v2/BoostNew_em_2016_v2/NN_nominal/ --output-dir me_16_v2_NN_f2


#NN using Condor
# First list all directories in an Input file
ls -d -1 ../Analysis/Output/trees/ALL_BoostNew_v2/BoostNew_*_201*/NN_n* > InputSamples_NN_Total_v1.txt

python makeSubmissionPackage_NN_Sys.py -n Total_v15_TES -i InputSamples_NN_Total_V15_TES.txt
cd Total_v15_TES
condor_submit Submit_batch_Total_v15_TES.jdl

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# NN Systematics
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

# prepare the nominal trainings
1)
for i in em et mt tt; do echo $i----- ; sh Nominal_Training.sh ../Analysis/Output/trees/ALL_Boost_v7/Sum_${i}_v7 $i ; done


3)
cp datasets/NominalPreprocess_em.h5 datasets/NominalPreprocess_me.h5
cp models/outputModel_NominalTraining_em.hdf5  models/outputModel_NominalTraining_me.hdf5

4)
cp datasets/NominalPreprocess_* /eos/uscms/store/user/abdollah/NominalPreprocess/.
cp models/outputModel_NominalTraining_* /eos/uscms/store/user/abdollah/NominalTrainings/.


5)
# list all NN_XXX (nominal and Sys) in a .txt file
ls -d -1 ../Analysis/Output/trees/ALL_Boost_v7/boost_*/NN* > InputSamples_NN_Total_v7.txt

6)
#for i in NominalTraining_* ; do mv $i ${i/"NominalTraining"/"NominalPreprocess"}; done
python makeSubmissionPackage_NN_Sys.py -n Total_v7_Sys -i InputSamples_NN_Total_v7.txt

7)
#The output will appear in /eos/uscms/store/user/abdollah/NN_output_Sys  so in the end:
cd /eos/uscms/store/user/abdollah/NN_output_Sys
mkdir V7_XMass2023
for i in em me et mt tt; do for j in 2016 2017 2018 ; do mkdir V7_XMass2023/${j}_${i}; mv NN_boost_${i}_${j}*v7_firstTryNN*/*root V7_XMass2023/${j}_${i}/.; done ; done
for i in em me et mt tt; do for j in 2016 2017 2018 ; do echo $i$j ; mv NN_boost_${i}_${j}*v7_firstTryNN*/*root V7_XMass2023/${j}_${i}/.; done ; done

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Run Analysis (no PDF or Scale Uncertainty)
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# The full sys files are now locarted in the \eos area
#/eos/uscms/store/user/abdollah/NN_output_Sys/V7_XMass2023

#We need to complie these thress executables and run the following command:
./build process_trees_NN_em.cc process_trees_NN_em
./build process_trees_NN_lt.cc process_trees_NN_lt
./build process_trees_NN_tt.cc process_trees_NN_tt


python DataCard_Producer.py -i /eos/uscms/store/user/abdollah/NN_output_Sys/V7_XMass2023 -s V7_XMass2023_Retry
cd Output/templates
mkdir V7_XMass2023_Retry
mv *V7_XMass2023_Retry*root V7_XMass2023_Retry


#or

for i in em  tt; do for j in 2016 2017 2018 ; do ./process_trees_NN_${i} -d /eos/uscms/store/user/abdollah/NN_output_Sys/V7_XMass2023/${j}_${i} --suf V7_XMass_remain -v NN_disc -b 20 0 1 ; done ; done
for i in et  mt; do for j in 2016 2017 2018 ; do ./process_trees_NN_lt   -d /eos/uscms/store/user/abdollah/NN_output_Sys/V7_XMass2023/${j}_${i} --suf V7_XMass_remain -v NN_disc -b 20 0 1 ; done ; done



#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Run Analysis (for PDF or Scale Uncertainty)
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# first make a version of the *nominal* root files : note of the -p at the end of the command
#Then

python DataCard_Producer.py -i /eos/uscms/store/user/abdollah/NN_output_Sys/V7_XMass2023_Nominal -s V7_XMass2023_nominal -p 1

#or

for i in em  tt; do for j in 2016 2017 2018 ; do ./process_trees_NN_${i} -d /eos/uscms/store/user/abdollah/NN_output_Sys/V7_XMass2023_Nominal/${j}_${i} --suf V7_XMass2023_pdfscale -v NN_disc -b 20 0 1  -p; done ; done
for i in et  mt; do for j in 2016 2017 2018 ; do ./process_trees_NN_lt   -d /eos/uscms/store/user/abdollah/NN_output_Sys/V7_XMass2023_Nominal/${j}_${i} --suf V7_XMass2023_pdfscale -v NN_disc -b 20 0 1  -p; done ; done



#This can be done interactively as well

python DataCard_Producer.py -i V7_XMass2023_Nominal -s V7_XMass2023_nominal -p 1
cd Output/templates
mkdir PDFScaleFiles_v7_new
mv *_XMass2023_nominal.root PDFScaleFiles_v7_new
scp -r cmslpc-sl7.fnal.gov:/uscms_data/d3/abdollah/Analysis/ggNtuple/CMSSW_10_2_10/src/BoostedHTT/Analysis/Output/templates/V7_XMass2023_Retry .
cd -
python Draw_Sys_ScaleUnc.py -p Output/templates/PDFScaleFiles_v7_new
(python Draw_Sys_ScaleUnc_Diff.py -p Output/templates/Diff_0p5_PDFSCale_3bin_v2) # for diff


#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Combine files with no PDF and PDf uncertainties  (to be done in the lpc machines)
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

# Nopw we have two directories one is the files with all nominal and sus uncertaintiy files and the other nominal and pdf + scale uncertainty files. We have to combine these two

#The last step is to add the sys file to the orginal datacards
#This needs to be done at the lpc machine as there is an inconsistency between the root version in lpc machine and my laptop


python Draw_Sys_AddScalePdf_To_DC.py -d Output/templates/V7_XMass2023_Retry -s Output/templates/PDFScaleFiles_v7_new  #V7_XMass2023_Retry are the directory with full-sys datacards and PDFScaleFiles_v7_new is directory with added pdf/scale datacards which is copied from my laptop
python Draw_Sys_AddScalePdf_To_DC.py -d Output/templates/V21_addgenJet_noPTH -s Output/templates/V20_pdfscale_TTZTT_XMass23
(python Draw_Sys_AddScalePdf_To_DC.py -d Output/templates/Inclusive_0p5_v1 -s Output/templates/Inclusive_0p5_PDFSCale_v1/)

# now the updated root files will be Output/templates/V7_XMass2023_Retry and ends with _pdfscaleOut.root


#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Hadd files and Rename for combine Harvester
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#Hadd
for j in 2016 2017 2018; do hadd -f Output/templates/V7_XMass2023_Retry/V7_XMass2023_Retry_${j}_NN.root Output/templates/V7_XMass2023_Retry/*${j}*V7_XMass2023_Retry_pdfscaleOut.root; done
cd ../Limit/.


#Rename the root file
cd ../Limit/.
python ReNamingDC_Limit.py -i ../Analysis/Output/templates/V7_XMass2023_Retry/V7_XMass2023_Retry_2018_NN.root -o V7_XMass2023_Retry_rename_2018_NN.root
python ReNamingDC_Limit.py -i ../Analysis/Output/templates/V7_XMass2023_Retry/V7_XMass2023_Retry_2017_NN.root -o V7_XMass2023_Retry_rename_2017_NN.root
python ReNamingDC_Limit.py -i ../Analysis/Output/templates/V7_XMass2023_Retry/V7_XMass2023_Retry_2016_NN.root -o V7_XMass2023_Retry_rename_2016_NN.root

#(python ReNamingDC.py -i ../Analysis/Output/templates/Inclusive_0p5_v1/V1_dr0p5_2016_NN.root -o V1_dr0p5_rename_2016_NN.root)
(python ReNamingDC_diff.py -i ../Analysis/Output/templates/Diff_0p5_3bin_v2/V2_Diff_dr0p5_hpt_3bin_2016_NN.root -o V2_Diff_dr0p5_hpt_3bin_rename_2016_NN.root)

# Finally scp these to lxplus

scp V7_XMass2023_Retry_rename_*root lxplus.cern.ch:/afs/cern.ch/work/a/abdollah/scratch1/LimiBoosted/CMSSW_10_2_13/src/CombineHarvester/CombineTools/bin/aux/.






#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Measuring the jet to boosted tau fake rate
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#Skim
#------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# The first step is to run a dedicated skimmer called  SkimerBoost_mFake.cc

#for MC
for j in 2016 2017 2018 ; do  python makeSubmissionPackage.py -x SkimerBoost_mFake -n InputSample_${j}_v7_mc_mfake -i InputSample_${j}_mc_v7.txt -o /store/user/abdollah/SkimBoostedH2/${j}/mfake/v7/ ; done

#for data
for j in 2016 2017 2018 ; do  python makeSubmissionPackage.py -x SkimerBoost_mFake -n InputSample_${j}_v7_data_mfake -i InputSample_${j}_Mu.txt -o /store/user/abdollah/SkimBoostedH2/${j}/mfake/v7/ ; done

# submit both
for i in Files_InputSample_201*_v7_*_mfake; do echo $i ; cd $i ; condor_submit Submit_batch_*.jdl; cd -   ; done

#------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#hadd
#------------------------------------------------------------------------------------------------------------------------------------------------------------------------
python hadd_skim.py -i Files_InputSample_2016_v7_mc_mfake/InputSample_2016_mc_v7.txt -s /eos/uscms/store/user/abdollah/SkimBoostedH2/2016/mfake/v7 -n v7_mfake_2016

for j in 2016 2017 2018 ; do  python hadd_skim.py -i Files_InputSample_${j}_v7_mc_mfake/InputSample_${j}_mc_v7.txt -s /eos/uscms/store/user/abdollah/SkimBoostedH2/${j}/mfake/v7 -n v7_mfake_${j}_mc; done
for j in 2016 2017 2018 ; do  python hadd_skim.py -i Files_InputSample_${j}_v7_data_mfake/InputSample_${j}_Mu.txt -s /eos/uscms/store/user/abdollah/SkimBoostedH2/${j}/mfake/v7 -n v7_mfake_${j}_data; done


#------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#rename
#------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 for j in 2016 2017 2018; do sh _rename_$j.sh /eos/uscms/store/user/abdollah/SkimBoostedH2/$j/mfake/v7_Hadd ; done

#------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#run analysis
#------------------------------------------------------------------------------------------------------------------------------------------------------------------------
./Make.sh BoostedHTT_mFake.cc
for i in 2016 2017 2018; do python automate_analysis.py -e BoostedHTT_mFake.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH2/$i/mfake/v7_Hadd/ -o boost_mFake_${i}_v7 ; done

#or
python automate_analysis.py -e BoostedHTT_mFake.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH2/2016/mfake/v7_Hadd/ -o boost_mFake_2016_v7
python automate_analysis.py -e BoostedHTT_mFake.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH2/2017/mfake/v7_Hadd/ -o boost_mFake_2017_v7
python automate_analysis.py -e BoostedHTT_mFake.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH2/2018/mfake/v7_Hadd/ -o boost_mFake_2018_v7


#------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#hadd the output filrs which are located in Output/trees directory
#------------------------------------------------------------------------------------------------------------------------------------------------------------------------
sh hadd.sh Output/trees/boost_mFake_2016_v7
sh hadd.sh Output/trees/boost_mFake_2017_v7
sh hadd.sh Output/trees/boost_mFake_2018_v7


#------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#copy the file to the local area and measure the jet to tau fake rate
#------------------------------------------------------------------------------------------------------------------------------------------------------------------------

python FR_boostedTau.py Output/trees/boost_mFake_2016_v7/Data.root
python FR_boostedTau.py Output/trees/boost_mFake_2017_v7/Data.root
python FR_boostedTau.py Output/trees/boost_mFake_2018_v7/Data.root


#The outcomes are fake pdf file and root file that can be used to estimate QCD


#./Step6_PreSelectionPlotter_Fake.py FakeRate_v1/newboost_mfake_2016_v5/
#python Draw_PreSelection_Fake.py FakeRate_v1/newboost_mfake_2016_v5_Test/




#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Tag n Probe for boosted tau Id SF and uncertainty
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#The skimmed ntuples are the ones used for mutau channels: i.e.


/eos/uscms/store/user/abdollah/SkimBoostedH3/2016/mt/v3_fast_Hadd/
/eos/uscms/store/user/abdollah/SkimBoostedH3/2017/mt/v3_fast_Hadd/
/eos/uscms/store/user/abdollah/SkimBoostedH3/2018/mt/v3_fast_Hadd/

#The first step is to run the code on these skimmed ntuples:
python automate_analysis.py -e BoostedHTT_mt.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH3/2016/mt/v3_fast_Hadd/ -o newboost_tnp_mt_2016_sys --sys
python automate_analysis.py -e BoostedHTT_mt.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH3/2017/mt/v3_fast_Hadd/ -o newboost_tnp_mt_2017_sys --sys
python automate_analysis.py -e BoostedHTT_mt.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH3/2018/mt/v3_fast_Hadd/ -o newboost_tnp_mt_2018_sys --sys

#The second step is to hadd the files

#The copy all files to the laptop


#The thirs step is update the process_trees_sf_fr file and then run it
./build process_trees_sf_fr.cc process_trees_sf_fr


#// test the code locally
./process_trees_sf_fr -d newboost_mt_2018_SF_sys --suf sys_v1 -v vis_mass -b 30 0 150 -c lep2IsoPassL -l 0 -h 1000 -n test -w Loose

# Move all files for each year in one category
mkdir ALL
mv NN* ALL

#Make DC for computing limits
python SF_datacardMaker.py -i TagNProbe1/boost_mt_2016_tnp2/ALL/ -s NewSF
python SF_datacardMaker.py -i TagNProbe1/boost_mt_2017_tnp2/ALL/ -s NewSF
python SF_datacardMaker.py -i TagNProbe1/boost_mt_2018_tnp2/ALL/ -s NewSF

#Next is scp these files in cmslpc for runinng the limiy
python _scp_lpc.py Output/sf/mt201*_bin*root


#Note: The three following commands are all now encoded in runLimit_tnp.py
#The combine file name is BoostedTau_limit_single_plus_CR_new.cpp
BoostedTau_limit_single_plus_CR_new --year=2018 --WP="V" --bin=bin3 --DIR="tnpDIR"
#Run for all 48 channels/years/bins
for i in 2016 2017 2018 ; do for j in V L M T ; do for k in bin0 bin1 bin2 bin3 ; do BoostedTau_limit_single_plus_CR_new --year=${i} --WP=$j --bin=$k --DIR="newTnP_v1"; done ; done; done
#add appropriate line for BBB and rateParam
sh  add_auto_MC_Stat_TnP.sh newTnP_v1

#and finaly run the full limit calculation chain
python runLimit_tnp.py newTnP_v2

#cp the file to the laptop
scp -r cmslpc-sl7.fnal.gov:/uscms_data/d3/abdollah/Analysis/Limit/CMSSW_10_2_13/src/CombineHarvester/CombineTools/bin/newTnP_v2 .


# To get the prefit/postfit plots
sh
for i in TnP_dR_V1/*/125/postfit_shapes.root ; do python Draw_POSTPREFIT_TnP.py $i $i ; done

# To get the SF and it uncertainty # Note that some mofication is needed in case you are drawing the SF v.s. dR two leptons or pt of the boosted tau
python drawGraph.py TnP_dR_V1

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# DiMu Scale factor
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#The input root files are stored here:

MM_ScaleFactor_v3/newBoost_mm_2016_v3/
MM_ScaleFactor_v3/newBoost_mm_2017_v3/
MM_ScaleFactor_v3/newBoost_mm_2018_v3/


#To get the SF 2D-table:
python Measure_ZmumuRatio.py MM_ScaleFactor_v3/newBoost_mm_2016_v3/_2DZMassPt_OS-2016_N.root
python Measure_ZmumuRatio.py MM_ScaleFactor_v3/newBoost_mm_2017_v3/_2DZMassPt_OS-2017_N.root
python Measure_ZmumuRatio.py MM_ScaleFactor_v3/newBoost_mm_2018_v3/_2DZMassPt_OS-2018_N.root

#The outcome is already here (after the SF has been applied):
mm_2016_validation/
mm_2017_validation/
mm_2018_validation/




#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# QCD Validation
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#for emu the files are located here:
/Users/abdollah/cernbox/Analysis/BoostedH/NewBoostedH/BoostedHTT/Analysis/QCD_Valication_EMU



#for tautau the files are located here:
/Users/abdollah/cernbox/Analysis/BoostedH/NewBoostedH/BoostedHTT/Analysis/tt_2016_qcdValidation
/Users/abdollah/cernbox/Analysis/BoostedH/NewBoostedH/BoostedHTT/Analysis/tt_2017_qcdValidation
/Users/abdollah/cernbox/Analysis/BoostedH/NewBoostedH/BoostedHTT/Analysis/tt_2018_qcdValidation


#for l-tau the files are located here:
#The first step is to update the BoostedHTT_mt.cc and BoostedHTT_et.cc files and remove 3 cuts (m_tautau, Higgs pt and MT) Then we need to run them on V3_fast_hadd

python automate_analysis.py -e BoostedHTT_mt.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH3/2018/mt/v3_fast_Hadd/ -o qcdValidation_mt_2018
python automate_analysis.py -e BoostedHTT_mt.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH3/2017/mt/v3_fast_Hadd/ -o qcdValidation_mt_2017
python automate_analysis.py -e BoostedHTT_mt.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH3/2016/mt/v3_fast_Hadd/ -o qcdValidation_mt_2016

python automate_analysis.py -e BoostedHTT_et.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH3/2018/et/v3_fast_Hadd/ -o qcdValidation_et_2018
python automate_analysis.py -e BoostedHTT_et.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH3/2017/et/v3_fast_Hadd/ -o qcdValidation_et_2017
python automate_analysis.py -e BoostedHTT_et.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH3/2016/et/v3_fast_Hadd/ -o qcdValidation_et_2016

#after hadd and move them to the local directory the files are located here:
/Users/abdollah/cernbox/Analysis/BoostedH/NewBoostedH/BoostedHTT/Analysis/Output/trees/qcdValidation_et_2016



# Now we update the process_trees_lt_fr.cc and change the code to run for vaidation
./build process_trees_lt_fr.cc process_trees_lt_fr_qcdValidation
./process_trees_lt_fr_qcdValidation -d Output/trees/qcdValidation_mt_2018 --suf test_fr_MB -v dR_lep_lep -b 20 0 1


# plotting qcd  validation
python autoplot_single.py -i Output/templates/mt2018_dR_lep_lep_test_fr_MB.root -p testval -v dR_lep_lep







#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#  Preparing Datacard for Differential Measurements   Step 1  Finidng the theory cross section
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

python makeSubmissionPackage.py -x SkimerBoost_Differntial -n diff_2016_v2 -i InputSample_Diff_2016.txt -o /eos/uscms/store/user/abdollah/SkimBoostedH3/2016/Diff/v2_sys
python makeSubmissionPackage.py -x SkimerBoost_Differntial -n diff_2017_v2 -i InputSample_Diff_2017.txt -o /eos/uscms/store/user/abdollah/SkimBoostedH3/2017/Diff/v2_sys
python makeSubmissionPackage.py -x SkimerBoost_Differntial -n diff_2018_v2 -i InputSample_Diff_2018.txt -o /eos/uscms/store/user/abdollah/SkimBoostedH3/2018/Diff/v2_sys


#The first step is to run the SkimerBoost_Differntial.cc code on signal samples. This code is splitting the Higgs signal into different channels the outcome will be here:
# This preselect some signal sampels in all caregories
/eos/uscms/store/user/abdollah/SkimBoostedH3/2016/Diff/v2_sys/
/eos/uscms/store/user/abdollah/SkimBoostedH3/2017/Diff/v2_sys/
/eos/uscms/store/user/abdollah/SkimBoostedH3/2018/Diff/v2_sys/

# NExt step is hadding these samples
sh hadd_Differential.sh /eos/uscms/store/user/abdollah/SkimBoostedH3/2016/Diff/v2_sys/ 2016
sh hadd_Differential.sh /eos/uscms/store/user/abdollah/SkimBoostedH3/2017/Diff/v2_sys/ 2017
sh hadd_Differential.sh /eos/uscms/store/user/abdollah/SkimBoostedH3/2018/Diff/v2_sys/ 2018

mv *125* AllHiggs_v3_sys
#Now
scp -r cmslpc-sl7.fnal.gov:/uscms_data/d3/abdollah/Analysis/ggNtuple/CMSSW_10_2_10/src/BoostedHTT/Skim/AllHiggs_v5_sys to the /Users/abdollah/cernbox/Analysis/BoostedH/NewBoostedH/BoostedHTT/Limit


# to get the diff money plot
python Draw_differential_Boost_4bins.py -g AllROOT/higgsCombinetest_param0.MultiDimFit.mH125_hpt_V9_Fid.root -i differential_theory_5_fourBins.root -o newout -j hpt







#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#  Preparing Datacard for Differential Measurements   Step 2  Finding the Limit
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


# first make several copy of the Higgs files
#sh
#for i in mt_2018_addHpT_* ; do for j in 0_350 350_450 450_600 GT600  ; do echo $i ; cp $i/H125.root $i/ggH_PTH_$j125.root; done ; done
#exit

# For this step we need to have the root files all of the added with NN and in the category

#for i in V7_FinalNNResults/NN_boost_* ; do for j in 0_350 350_450 400_600 600_800 GT800 ; do  cp $i/ggH125.root $i/ggH_PTH_$j.root ;done ;done
cd /eos/uscms/store/user/abdollah/NN_output_Sys
for i in V21_addgenJet/*/*ggH125* ; do echo "hadding  OutsideAcceptance" $i;  OutSide=${i/"ggH125"/"OutsideAcceptance"}; XH=${i/"ggH125"/"XH125"};  hadd ${OutSide} ${i} ${XH} ;done
for i in V21_addgenJet/*/*125* ; do echo "coping " $i; for j in 0_350 350_450 450_600  GT600 ; do  X=${i/"125"/"125"_PTH_${j}}; cp $i $X ;done ;done
# no theoretical uncertainties on Outside
rm V21_addgenJet/*/OutsideAcceptance_THU_ggH_*

# This is also another code that might work (need to revisit)
python addDifferentialSamply.py -i /eos/XXX





./build DiffMeasure_em.cc DiffMeasure_em
./build DiffMeasure_lt.cc DiffMeasure_lt
./build DiffMeasure_tt.cc DiffMeasure_tt

# A local test
./DiffMeasure_tt -d /eos/uscms/store/user/abdollah/NN_output_Sys/V12_newDMNN/2016_tt/ --suf testtttt -v NN_disc -b 20 0 1  -c Rivet_higgsPt -l 350 -h 450

# Run all This could be run on lpc/lxplu
for i in /eos/uscms/store/user/abdollah/NN_output_Sys/V20_pdfscale/* ; do echo $i; python DiffMeasure_DataCardProducer.py  -i $i -s XMass23_V1 -o NN_disc -v gen_higgs_pT ; done
for i in ../V20_pdfscale/* ; do python DiffMeasure_DataCardProducer.py  -i $i -s Diff_dr0p5_higgs_pT_3bins_v2 -o NN_disc -v gen_higgs_pT ; done # to run interactively
# To get the root file included the pdf and qcd scale, we need to run on my laptop

# on my lapton
for i in V20_pdfscale_TTZTT/* ; do python DiffMeasure_DataCardProducer.py  -i $i -s Diff_dr0p5_higgs_pT_pdfscale_3bins_v2 -o NN_disc -v gen_higgs_pT -p 1; done
# Note: special treatment should be done for lt channel (I do not know the reason yet)



# Gen lead jet pt

for i in ../V20_pdfscale/* ; do python DiffMeasure_DataCardProducer.py  -i $i -s Diff_jet_pT_v1 -o NN_disc -v gen_leadjet_pT; done
for i in V20_pdfscale_TTZTT/* ; do python DiffMeasure_DataCardProducer.py  -i $i -s Diff_jet_pT_sys_v1 -o NN_disc -v gen_leadjet_pT -p 1; done



python Draw_Sys_ScaleUnc_Diff.py -p Output/templates/Diff_Unblind_v2_higgs_pT  # to be run in my laptop


#The last step is to add the sys file to the orginal datacards
#This needs to be done at the lpc machine as there is an inconsistency between the root version in lpc machine and my laptop
python Draw_Sys_AddScalePdf_To_DC_Diff.py -d Output/templates/Unblind_v2_higgs_pT_ -s Diff_Unblind_v2_higgs_pT  #V20_pdfscale are the directory with full-sys datacards and SysedFiles is directory with added pdf/scale datacards which is copied from my laptop
python Draw_Sys_AddScalePdf_To_DC_Diff.py  -d Output/templates/Diff_XMass23_V2_LeadJet -s Output/templates/Diff_dr0p5_leadjet_pT_pdfscale_XMass23_V1


# The output will be


#for i in 0 1 2 3 4 5; do for j in 2016 2017 2018 ; do hadd -f Output/datacard/V9\_bin$i\_$j\_NN.root Output/templates/*$j\_NN_disc*NN9*bin$i.root ; done ; done
# for j in 2016 2017 2018 ; do hadd -f Output/datacard/V10\_bin_$j\_NN.root Output/templates/*$j\_NN_disc*NNV10*bin*.root ; done
 for i in 2016 2017 2018 ; do hadd -f Unblinding_V3_hpt_${i}_NN.root  *${i}*_NN_disc_Unblind_v3_higgs_pT__*_pdfscaleOut.root ; done
 for i in 2016 2017 2018 ; do hadd -f V1_diff_jpt_${i}_NN.root  *${i}*NN_disc_Diff_jet_pT_v1_*_pdfscaleOut.root ; done
# scp to cmslpc
#python ReNamingDC.py -i V12_new_2016_NN.root -o V12_new_rename_2016_NN.root
#python ReNamingDC.py -i V12_new_2017_NN.root -o V12_new_rename_2017_NN.root
#python ReNamingDC.py -i V12_new_2018_NN.root -o V12_new_rename_2018_NN.root

python ReNamingDC_Diff.py -i ../Analysis/Unblind_v2_higgs_pT_/Unblinding_V2_hpt_2016_NN.root -o V2_unblind_hpt_rename_2016_NN.root
python ReNamingDC_Diff.py -i ../Analysis/Unblind_v2_higgs_pT_/Unblinding_V2_hpt_2017_NN.root -o V2_unblind_hpt_rename_2017_NN.root
python ReNamingDC_Diff.py -i ../Analysis/Unblind_v2_higgs_pT_/Unblinding_V2_hpt_2018_NN.root -o V2_unblind_hpt_rename_2018_NN.root

python ReNamingDC_diff.py -i ../Analysis/Output/templates/Diff_jpt_v1/V1_diff_jpt_2017_NN.root -o V1_diff_jpt_rename_2017_NN.root

#python _scp_lpc.py Output/datacard/V10_bin*
python _scp_lxp.py V2_unblind_hpt_rename_*


#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#%%%%%%%%%%%%%%%%%%%#                                  LIMIT                                #%%%%%%%%%%%%%%%%%%%#

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Inclusive limit
#------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


#Make DC for only one year
BoostedTau_3NN --prefix="V23_singleBin_rename" --postfix="V23_singleBin" --year=2016 --Var=NN
sh add_auto_MC_Stat.sh V1  # Adding BBB

#Make Only Datacarad in 3 years
python QuickLimit_justDC.py  V20_pdfscale_noPTH_XMass2023_QCDFix_CorrTau_rename   WHATEVERNAMEYOULIKE   NN

#Run the limit for all three years (combine 3 categories)
python QuickLimit_Unblinding.py V20_pdfscale_noPTH_XMass2023_QCDFix_CorrTau_rename   WHATEVERNAMEYOULIKE   NN

#Run the limit for all three years (separate each category)  # Run limit for all 4 final states & 3 years + fit + draw postfit
python  QuickLimit.py V20_pdfscale_noPTH_XMass2023_QCDFix_CorrTau_rename NN

#Print the Obs/Exp Significance for each year/channel (note that 3 categories are combined now)
python QuickLimit_printVal.py NAMEOFTHE_FOLDER_WHERE_DC_ARE_THERE

#Drawing the postfit plots:
for i in NewV3/postfit_shapes_NewV3_201* ; do python Draw_POSTPREFIT_Boost.py $i test1; done

# combining DC all
combineCards.py 201*/*/125/*txt > all.txt
# combining DC for channel/year
for i in et mt em tt; do cd ch${i}; combineCards.py ../201*/125/*$i* > ${i}.txt ; text2workspace.py ${i}.txt -m 125; cd - ; done
for i in 2016 2017 2018; do cd yr${i}; combineCards.py ../${i}/125/*.txt > ${i}.txt ; text2workspace.py ${i}.txt -m 125; cd - ; done


#TextToWS
text2workspace.py all.txt -m 125

#Significance  exp/obs
combine -M Significance -d all.txt -m 125 -t -1  --expectSignal=1
combine -M Significance -d all.txt -m 125

# Get PostFit plots
PostFitShapesFromWorkspace -w ws.root -f fitDiagnosticsTest.root:fit_s --postfit --print -d all.txt -o postfit_shapes.root -m 125

#Get Limit  (i.e. for optimization)
for i in em et mt tt me ; do for j in 2016 2017 2018; do echo  V2/$j/$j/125/*$i*txt; cd V2/$j/$j/125/ ; combine -M Significance -d *$i*.txt -t -1 -m 125 --expectSignal=1 ; mv higgsCombineTest.Significance.mH125.root higgsCombineTest.Significance.mH125$i$j.root ; cd - ; done; done
python getlim.py V2/2016/
python getlim.py V2/2017/
python getlim.py V2/2018/


#--------------------
# Impact
#--------------------

combineTool.py -M Impacts -d all.root -m 125 --doInitialFit --robustFit 1 --setParameterRanges r=-5,5 --cminDefaultMinimizerType Minuit2 --cminDefaultMinimizerStrategy 0 --cminDefaultMinimizerTolerance 0.1  (-t -1 --expectSignal 1)
combineTool.py -M Impacts -d all.root -m 125 --doFits       --robustFit 1 --setParameterRanges r=-5,5 --cminDefaultMinimizerType Minuit2 --cminDefaultMinimizerStrategy 0 --cminDefaultMinimizerTolerance 0.1 (-t -1 --expectSignal 1)
combineTool.py -M Impacts -d all.root -m 125 -o impacts.json
plotImpacts.py -i impacts.json -o impacts_all
# blind
plotImpacts.py -i impacts.json -o impacts_tt --blind


# Impact plots on condor dryrun
combineTool.py -M Impacts -d all.root -m 125 --doInitialFit --robustFit 1 -t -1 --expectSignal 1 --cminDefaultMinimizerType Minuit2 --cminDefaultMinimizerStrategy 0 --cminDefaultMinimizerTolerance 0.1 --job-mode condor --task-name doInitialFit_all --dry-run
combineTool.py -M Impacts -d all.root -m 125 --doFits       --robustFit 1 -t -1 --expectSignal 1 --cminDefaultMinimizerType Minuit2 --cminDefaultMinimizerStrategy 0 --cminDefaultMinimizerTolerance 0.1 --job-mode condor --task-name doFits_all --dry-run

# Impact plots run on condor
combineTool.py -M Impacts -d all.root -m 125 --doFits       --robustFit 1 -t -1 --expectSignal 1 --cminDefaultMinimizerType Minuit2 --cminDefaultMinimizerStrategy 0 --cminDefaultMinimizerTolerance 0.1 --job-mode condor --task-name doFits_all --sub-opt '+JobFlavour = "espresso"' --X-rtd MINIMIZER_analytic
# other options
+JobFlavour = "microcentury"
+JobFlavour = "longlunch"



# run impact for each single channel
 for i in et em mt tt; do for j in 2016 2017 2018 ; do mkdir $i$j ; cd $i$j ; combineCards.py ../$j/125/*_${i}_*.txt > $i$j.txt ;  text2workspace.py $i$j.txt -m 125 ;  combineTool.py -M Impacts -d $i$j.root -m 125 --doInitialFit --robustFit 1 --setParameterRanges r=-10,10 ;  combineTool.py -M Impacts -d $i$j.root -m 125 --robustFit 1 --doFits  --setParameterRanges r=-10,10 ;  combineTool.py -M Impacts -d $i$j.root -m 125 -o impacts$i$j.json ;  plotImpacts.py -i impacts$i$j.json -o impacts$i$j --blind ; cd - ; done ; done
 
 
 # run impact for each channel (for all 3 years)
 for i in et em mt tt; do mkdir $i ; cd $i ; combineCards.py ../*/125/*_${i}_*.txt > $i.txt ;  text2workspace.py $i.txt -m 125 ;   combineTool.py -M Impacts -d $i.root -m 125 --doInitialFit --robustFit 1 --setParameterRanges r=-10,10;  combineTool.py -M Impacts -d $i.root -m 125 --robustFit 1 --doFits  --setParameterRanges r=-10,10 ;  combineTool.py -M Impacts -d $i.root -m 125 -o impacts$i.json ;  plotImpacts.py -i impacts$i.json -o impacts$i --blind ; cd - ; done
# for i in et em mt tt; do mkdir $i ; cd $i ; text2workspace.py $i.txt -m 125 ;   combineTool.py -M Impacts -d $i.root -m 125 --doInitialFit --robustFit 1 --setParameterRanges r=-10,10;  combineTool.py -M Impacts -d $i.root -m 125 --robustFit 1 --doFits  --setParameterRanges r=-10,10 ;  combineTool.py -M Impacts -d $i.root -m 125 -o impacts$i.json ;  plotImpacts.py -i impacts$i.json -o impacts$i --blind ; cd - ; done
 

 # run impact for each channel (for all 3 years)
 for i in 2016 2017 2018 ; do mkdir yr$i ; cd yr$i ; combineCards.py ../${i}/125/*.txt > $i.txt ;  text2workspace.py $i.txt -m 125 ;  combineTool.py -M Impacts -d $i.root -m 125 --doInitialFit --robustFit 1 --setParameterRanges r=-10,10;  combineTool.py -M Impacts -d $i.root -m 125 --robustFit 1 --doFits  --setParameterRanges r=-10,10 ;  combineTool.py -M Impacts -d $i.root -m 125 -o impacts$i.json ;  plotImpacts.py -i impacts$i.json -o impacts$i --blind ; cd - ; done
# for i in 2016 2017 2018 ; do mkdir yr$i ; cd yr$i ;  text2workspace.py $i.txt -m 125 ;  combineTool.py -M Impacts -d $i.root -m 125 --doInitialFit --robustFit 1 --setParameterRanges r=-10,10;  combineTool.py -M Impacts -d $i.root -m 125 --robustFit 1 --doFits  --setParameterRanges r=-10,10 ;  combineTool.py -M Impacts -d $i.root -m 125 -o impacts$i.json ;  plotImpacts.py -i impacts$i.json -o impacts$i --blind ; cd - ; done


 # run impact for each category (for all 3 years and 4 channels)
 for i in ztt qcd sig; do mkdir $i ; cd $i ; combineCards.py ../*/125/*$i*.txt > $i.txt ;  text2workspace.py $i.txt -m 125 ;   combineTool.py -M Impacts -d $i.root -m 125 --doInitialFit --robustFit 1 --setParameterRanges r=-10,10;  combineTool.py -M Impacts -d $i.root -m 125 --robustFit 1 --doFits  --setParameterRanges r=-10,10 ;  combineTool.py -M Impacts -d $i.root -m 125 -o impacts$i.json ;  plotImpacts.py -i impacts$i.json -o impacts$i --blind ; cd - ; done
# for i in ztt qcd sig; do mkdir $i ; cd $i ;  text2workspace.py $i.txt -m 125 ;   combineTool.py -M Impacts -d $i.root -m 125 --doInitialFit --robustFit 1 --setParameterRanges r=-10,10;  combineTool.py -M Impacts -m 125 --doFits --rMin -20 --rMax 20 -d $i.root --job-mode condor --robustFit 1 --task-name combined_dl_impacts --setParameterRanges r=-10,10 ;  combineTool.py -M Impacts -d $i.root -m 125 -o impacts$i.json ;  plotImpacts.py -i impacts$i.json -o impacts$i --blind ; cd - ; done


#all
 mkdir all ; cd all ; combineCards.py ../*/125/*.txt > all.txt ;  text2workspace.py all.txt -m 125 ;  combineTool.py -M Impacts -d all.root -m 125 --doInitialFit --robustFit 1 --setParameterRanges r=-10,10;  combineTool.py -M Impacts -d all.root -m 125 --robustFit 1 --doFits --setParameterRanges r=-10,10 ;  combineTool.py -M Impacts -d all.root -m 125 -o impactsall.json ;  plotImpacts.py -i impactsall.json -o impactsall --blind ; cd -



#--------------------
# Goodness of Fit GoF
#--------------------

#simple steps
combine -M GoodnessOfFit all.txt --algo=saturated -m 125
combine -M GoodnessOfFit all.txt --algo=saturated -t 500 -s 123456 -m 125
combineTool.py -M CollectGoodnessOfFit --input higgsCombineTest.GoodnessOfFit.mH125.root higgsCombineTest.GoodnessOfFit.mH125.123456.root  -m 125.0 -o gof.json
plotGof.py gof.json --statistic saturated --mass 125.0 -o gof_plot_all --title-right="all"


# run GoF for each single channel-year
 for i in et em mt tt; do for j in 2016 2017 2018 ; do mkdir $i$j ; cd $i$j ; combineCards.py ../$j/125/*_${i}_*.txt > $i$j.txt ; combine -M GoodnessOfFit $i$j.txt --algo=saturated -m 125 ; combine -M GoodnessOfFit $i$j.txt --algo=saturated -t 500 -s 123456 -m 125 ; combineTool.py -M CollectGoodnessOfFit --input higgsCombineTest.GoodnessOfFit.mH125.root higgsCombineTest.GoodnessOfFit.mH125.123456.root  -m 125.0 -o gof${i}${j}.json ; plotGof.py gof${i}${j}.json --statistic saturated --mass 125.0 -o gof_plot_${i}${j} --title-right="$i$j" ; cd - ; done ; done
 
 
# run GoF for combined channels (combined all 3 years)
 for i in et em mt tt; do mkdir $i  ; cd $i ; combineCards.py ../*/125/*_${i}_*.txt > $i.txt ; combine -M GoodnessOfFit $i.txt --algo=saturated -m 125 ; combine -M GoodnessOfFit $i.txt --algo=saturated -t 500 -s 123456 -m 125 ; combineTool.py -M CollectGoodnessOfFit --input higgsCombineTest.GoodnessOfFit.mH125.root higgsCombineTest.GoodnessOfFit.mH125.123456.root  -m 125.0 -o gof${i}.json ; plotGof.py gof${i}.json --statistic saturated --mass 125.0 -o gof_plot_${i} --title-right="$i" ; cd - ; done
 
# run GoF for each years (combined 4 channels)
for i in 2016 2017 2018; do mkdir yr$i  ;  cd yr${i}; combineCards.py ../${i}/125/*.txt > ${i}.txt ;  combine -M GoodnessOfFit $i.txt --algo=saturated -m 125 ; combine -M GoodnessOfFit $i.txt --algo=saturated -t 500 -s 123456 -m 125 ; combineTool.py -M CollectGoodnessOfFit --input higgsCombineTest.GoodnessOfFit.mH125.root higgsCombineTest.GoodnessOfFit.mH125.123456.root  -m 125.0 -o gof${i}.json ; plotGof.py gof${i}.json --statistic saturated --mass 125.0 -o gof_plot_${i} --title-right="$i" ; cd - ; done
 
# run GoF for each categories (combined year-channel) exclusively for Inclusive analysis
for i in ztt qcd sig; do mkdir $i  ;  cd ${i}; combineCards.py ../*/125/*$i*.txt > ${i}.txt ;  combine -M GoodnessOfFit $i.txt --algo=saturated -m 125 ; combine -M GoodnessOfFit $i.txt --algo=saturated -t 250 -s 123456 -m 125 ; combineTool.py -M CollectGoodnessOfFit --input higgsCombineTest.GoodnessOfFit.mH125.root higgsCombineTest.GoodnessOfFit.mH125.123456.root  -m 125.0 -o gof${i}.json ; plotGof.py gof${i}.json --statistic saturated --mass 125.0 -o gof_plot_${i} --title-right="$i" ; cd - ; done

# run GoF for each categories (combined year-channel) exclusively for differenrtial analysis
for i in _1_ _2_ _3_ _4_ ; do mkdir $i  ;  cd ${i}; combineCards.py ../*/125/*$i*.txt > ${i}.txt ;  combine -M GoodnessOfFit $i.txt --algo=saturated -m 125 ; combine -M GoodnessOfFit $i.txt --algo=saturated -t 250 -s 123456 -m 125 ; combineTool.py -M CollectGoodnessOfFit --input higgsCombineTest.GoodnessOfFit.mH125.root higgsCombineTest.GoodnessOfFit.mH125.123456.root  -m 125.0 -o gof${i}.json ; plotGof.py gof${i}.json --statistic saturated --mass 125.0 -o gof_plot_${i} --title-right="$i" ; cd - ; done

# all
#  run GoF for all combined [This needs to be done in lxplus and using condor]
 mkdir all; cd all; combineCards.py ../201*/125/*.txt > all.txt ;text2workspace.py all.txt -m 125 ;combine -M GoodnessOfFit all.txt --algo=saturated -m 125 ;for idx in {0..199}; do combineTool.py -d all.root -M GoodnessOfFit -m 125  -t 20 -n name_batch${idx} --job-mode condor --task-name GoF_MC_batch${idx} --sub-opts="+JobFlavour = \"longlunch\"\n+JobBatchName=\"GoF MC\"" --algo=saturated -s -1; done

# Draw GoF for all
 hadd X.root higgsCombinename_batch*
 combineTool.py -M CollectGoodnessOfFit --input higgsCombineTest.GoodnessOfFit.mH125.root X.root  -m 125.0 -o gof.json
 plotGof.py gof.json --statistic saturated --mass 125.0 -o gof_plot_all --title-right="all"



#--------------------
# FastScan
#--------------------

combineTool.py -M FastScan -w workspace.root:w
combineTool.py -M FastScan -w all.root:w --job-mode condor  --sub-opts="+JobFlavour = \"longlunch\""

# plots 1D scan (for differntial)
plot1DScan.py higgsCombineTest.MultiDimFit.mH125.root --POI r_H_PTH_450_600

#--------------------
# FitDiagnostics
#--------------------

combine -M FitDiagnostics all.root  -m 125 --setParameterRanges r_H_PTH_0_350=-15,15:r_H_PTH_350_450=-15,15:r_H_PTH_450_600=-15,15:r_H_PTH_GT600=-15,15
PostFitShapesFromWorkspace -w all.root -f fitDiagnosticsTest.root:fit_s --postfit  --print -d  all.txt -o postfit_shapes_all_diff_V3.root -m 125

















#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Differential limit
#------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#Make DC for only one year
BoostedTau_DiffXS --prefix="Diff_HiggsPt_XMass23_V1_rename" --postfix="Diff_HiggsPt_XMass23_V1" --year=2016 --Var=NN
BoostedTau_DiffXS_PTJ --prefix="Diff_LeadJetPt_XMass23_V1_rename" --postfix="Diff_LeadJetPt_XMass23_V1" --year=2016 --Var=NN
sh add_auto_MC_Stat.sh V1  # Adding BBB



#Make Only Datacarad in 3 years  PTH
python QuickLimit_justDC_Diff.py  Diff_HiggsPt_XMass23_V1_rename   WHATEVERNAMEYOULIKE   NN

#Make Only Datacarad in 3 years PTJ
python QuickLimit_justDC_DiffLeadJet.py Diff_LeadJetPt_XMass23_V1_rename   WHATEVERNAMEYOULIKE   NN





#--------------------
# Impact Diff
#--------------------

 
 for i in et em mt tt; do for j in 2016 2017 2018 ; do mkdir $i$j ; cd $i$j ; combineCards.py ../$j/125/*_${i}_*.txt > $i$j.txt ;  text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO 'map=.*/.*H.*PTH_0_350.*:r_H_PTH_0_350[1,-25,25]' --PO 'map=.*/.*H.*PTH_350_450.*:r_H_PTH_350_450[1,-25,25]' --PO 'map=.*/.*H.*PTH_450_600.*:r_H_PTH_450_600[1,-25,25]' --PO 'map=.*/.*H.*PTH_G.600.*:r_H_PTH_GT600[1,-25,25]' $i$j.txt -m 125 ;  combineTool.py -M Impacts -d $i$j.root -m 125 --doInitialFit --robustFit 1 --setParameterRanges r_H_PTH_0_350=-15,15:r_H_PTH_350_450=-15,15:r_H_PTH_450_600=-15,15:r_H_PTH_GT600=-15,15  --redefineSignalPOIs r_H_PTH_0_350  ;  combineTool.py -M Impacts -d $i$j.root -m 125 --robustFit 1 --doFits  --setParameterRanges r_H_PTH_0_350=-15,15:r_H_PTH_350_450=-15,15:r_H_PTH_450_600=-15,15:r_H_PTH_GT600=-15,15  --redefineSignalPOIs r_H_PTH_0_350 ;  combineTool.py -M Impacts -d $i$j.root -m 125 -o impacts$i$j.json ;  plotImpacts.py -i impacts$i$j.json -o impacts$i$j --blind ; cd - ; done ; done
 
 
 # run impact for each channel (for all 3 years)
 for i in et em mt tt; do mkdir $i ; cd $i ; combineCards.py ../*/125/*_${i}_*.txt > $i.txt ;  text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO 'map=.*/.*H.*PTH_0_350.*:r_H_PTH_0_350[1,-25,25]' --PO 'map=.*/.*H.*PTH_350_450.*:r_H_PTH_350_450[1,-25,25]' --PO 'map=.*/.*H.*PTH_450_600.*:r_H_PTH_450_600[1,-25,25]' --PO 'map=.*/.*H.*PTH_G.600.*:r_H_PTH_GT600[1,-25,25]' $i.txt -m 125 ;   combineTool.py -M Impacts -d $i.root -m 125 --doInitialFit --robustFit 1 --setParameterRanges r_H_PTH_0_350=-15,15:r_H_PTH_350_450=-15,15:r_H_PTH_450_600=-15,15:r_H_PTH_GT600=-15,15 ;  combineTool.py -M Impacts -d $i.root -m 125 --robustFit 1 --doFits  --setParameterRanges r_H_PTH_0_350=-15,15:r_H_PTH_350_450=-15,15:r_H_PTH_450_600=-15,15:r_H_PTH_GT600=-15,15  ;  combineTool.py -M Impacts -d $i.root -m 125 -o impacts$i.json ;  plotImpacts.py -i impacts$i.json -o impacts$i --blind ; cd - ; done
# for i in et em mt tt; do mkdir $i ; cd $i ; text2workspace.py $i.txt -m 125 ;   combineTool.py -M Impacts -d $i.root -m 125 --doInitialFit --robustFit 1 --setParameterRanges r=-10,10;  combineTool.py -M Impacts -d $i.root -m 125 --robustFit 1 --doFits  --setParameterRanges r=-10,10 ;  combineTool.py -M Impacts -d $i.root -m 125 -o impacts$i.json ;  plotImpacts.py -i impacts$i.json -o impacts$i --blind ; cd - ; done
 

 # run impact for each channel (for all 3 years)
 for i in 2016 2017 2018 ; do mkdir yr$i ; cd yr$i ; combineCards.py ../${i}/125/*.txt > $i.txt ;  text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO 'map=.*/.*H.*PTH_0_350.*:r_H_PTH_0_350[1,-25,25]' --PO 'map=.*/.*H.*PTH_350_450.*:r_H_PTH_350_450[1,-25,25]' --PO 'map=.*/.*H.*PTH_450_600.*:r_H_PTH_450_600[1,-25,25]' --PO 'map=.*/.*H.*PTH_G.600.*:r_H_PTH_GT600[1,-25,25]' $i.txt -m 125 ;  combineTool.py -M Impacts -d $i.root -m 125 --doInitialFit --robustFit 1 --setParameterRanges r_H_PTH_0_350=-15,15:r_H_PTH_350_450=-15,15:r_H_PTH_450_600=-15,15:r_H_PTH_GT600=-15,15 ;  combineTool.py -M Impacts -d $i.root -m 125 --robustFit 1 --doFits  --setParameterRanges r_H_PTH_0_350=-15,15:r_H_PTH_350_450=-15,15:r_H_PTH_450_600=-15,15:r_H_PTH_GT600=-15,15  ;  combineTool.py -M Impacts -d $i.root -m 125 -o impacts$i.json ;  plotImpacts.py -i impacts$i.json -o impacts$i --blind ; cd - ; done
# for i in 2016 2017 2018 ; do mkdir yr$i ; cd yr$i ;  text2workspace.py $i.txt -m 125 ;  combineTool.py -M Impacts -d $i.root -m 125 --doInitialFit --robustFit 1 --setParameterRanges r=-10,10;  combineTool.py -M Impacts -d $i.root -m 125 --robustFit 1 --doFits  --setParameterRanges r=-10,10 ;  combineTool.py -M Impacts -d $i.root -m 125 -o impacts$i.json ;  plotImpacts.py -i impacts$i.json -o impacts$i --blind ; cd - ; done


 # run impact for each category (for all 3 years and 4 channels)
 for i in _1_ _2_ _3_ _4_; do mkdir $i ; cd $i ; combineCards.py ../*/125/*$i*.txt > $i.txt ;  text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO 'map=.*/.*H.*PTH_0_350.*:r_H_PTH_0_350[1,-25,25]' --PO 'map=.*/.*H.*PTH_350_450.*:r_H_PTH_350_450[1,-25,25]' --PO 'map=.*/.*H.*PTH_450_600.*:r_H_PTH_450_600[1,-25,25]' --PO 'map=.*/.*H.*PTH_G.600.*:r_H_PTH_GT600[1,-25,25]' $i.txt -m 125 ;   combineTool.py -M Impacts -d $i.root -m 125 --doInitialFit --robustFit 1 --setParameterRanges r_H_PTH_0_350=-15,15:r_H_PTH_350_450=-15,15:r_H_PTH_450_600=-15,15:r_H_PTH_GT600=-15,15 ;  combineTool.py -M Impacts -d $i.root -m 125 --robustFit 1 --doFits  --setParameterRanges r_H_PTH_0_350=-15,15:r_H_PTH_350_450=-15,15:r_H_PTH_450_600=-15,15:r_H_PTH_GT600=-15,15  ;  combineTool.py -M Impacts -d $i.root -m 125 -o impacts$i.json ;  plotImpacts.py -i impacts$i.json -o impacts$i --blind ; cd - ; done
# for i in ztt qcd sig; do mkdir $i ; cd $i ;  text2workspace.py $i.txt -m 125 ;   combineTool.py -M Impacts -d $i.root -m 125 --doInitialFit --robustFit 1 --setParameterRanges r=-10,10;  combineTool.py -M Impacts -m 125 --doFits --rMin -20 --rMax 20 -d $i.root --job-mode condor --robustFit 1 --task-name combined_dl_impacts --setParameterRanges r=-10,10 ;  combineTool.py -M Impacts -d $i.root -m 125 -o impacts$i.json ;  plotImpacts.py -i impacts$i.json -o impacts$i --blind ; cd - ; done


mkdir all_0_350 all_350_450 all_450_600 all_GT600
for i in all_* ; do cd $i;  combineCards.py ../201*/125/*.txt > all.txt ;  text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO 'map=.*/.*H.*PTH_0_350.*:r_H_PTH_0_350[1,-25,25]' --PO 'map=.*/.*H.*PTH_350_450.*:r_H_PTH_350_450[1,-25,25]' --PO 'map=.*/.*H.*PTH_450_600.*:r_H_PTH_450_600[1,-25,25]' --PO 'map=.*/.*H.*PTH_G.600.*:r_H_PTH_GT600[1,-25,25]' all.txt -m 125 ;     par=${i/"all_"/"r_H_PTH_"}; combineTool.py -M Impacts -d all.root -m 125 --robustFit 1 --doInitialFit  --setParameterRanges r_H_PTH_0_350=-25,25:r_H_PTH_350_450=-25,25:r_H_PTH_450_600=-25,25:r_H_PTH_GT600=-25,25  --redefineSignalPOIs ${par} --cminDefaultMinimizerType Minuit2 --cminDefaultMinimizerStrategy 0 --cminDefaultMinimizerTolerance 0.1; combineTool.py -M Impacts -d all.root -m 125 --robustFit 1 --doFits  --setParameterRanges r_H_PTH_0_350=-25,25:r_H_PTH_350_450=-25,25:r_H_PTH_450_600=-25,25:r_H_PTH_GT600=-25,25  --redefineSignalPOIs ${par} --cminDefaultMinimizerType Minuit2 --cminDefaultMinimizerStrategy 0 --cminDefaultMinimizerTolerance 0.1 --job-mode condor --sub-opts="+JobFlavour = \"longlunch\"\n+JobBatchName=\"Imp MC\"" ;  cd -; done

mkdir all_0_350 all_350_450 all_450_600 all_GT600
for i in all_* ; do cd $i;  combineCards.py ../201*/125/*.txt > all.txt ;  text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO 'map=.*/.*H.*PTJ_0_350.*:r_H_PTJ_0_350[1,-25,25]' --PO 'map=.*/.*H.*PTJ_350_450.*:r_H_PTJ_350_450[1,-25,25]' --PO 'map=.*/.*H.*PTJ_450_600.*:r_H_PTJ_450_600[1,-25,25]' --PO 'map=.*/.*H.*PTJ_G.600.*:r_H_PTJ_GT600[1,-25,25]' all.txt -m 125 ;     par=${i/"all_"/"r_H_PTJ_"}; combineTool.py -M Impacts -d all.root -m 125 --robustFit 1 --doInitialFit  --setParameterRanges r_H_PTJ_0_350=-25,25:r_H_PTJ_350_450=-25,25:r_H_PTJ_450_600=-25,25:r_H_PTJ_GT600=-25,25  --redefineSignalPOIs ${par} ; combineTool.py -M Impacts -d all.root -m 125 --robustFit 1 --doFits  --setParameterRanges r_H_PTJ_0_350=-25,25:r_H_PTJ_350_450=-25,25:r_H_PTJ_450_600=-25,25:r_H_PTJ_GT600=-25,25  --redefineSignalPOIs ${par} --job-mode condor --sub-opts="+JobFlavour = \"longlunch\"\n+JobBatchName=\"Imp MC\"" ;  cd -; done




for i in all_* ; do cd $i;  combineCards.py ../201*/125/*.txt > all.txt ;  text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO 'map=.*/.*H.*PTH_450_600.*:r_H_PTH_450_600[1,-25,25]' --PO 'map=.*/.*H.*PTH_G.600.*:r_H_PTH_GT600[1,-25,25]' all.txt -m 125 ;     par=${i/"all_"/"r_H_PTH_"}; combineTool.py -M Impacts -d all.root -m 125 --robustFit 1 --doInitialFit  --setParameterRanges r_H_PTH_450_600=-25,25:r_H_PTH_GT600=-25,25  --redefineSignalPOIs ${par} ; combineTool.py -M Impacts -d all.root -m 125 --robustFit 1 --doFits  --setParameterRanges r_H_PTH_450_600=-25,25:r_H_PTH_GT600=-25,25  --redefineSignalPOIs ${par} --job-mode condor --sub-opts="+JobFlavour = \"longlunch\"\n+JobBatchName=\"Imp MC\"" ;  cd -; done



for i in all_* ; do cd $i;  combineCards.py ../201*/125/*.txt > all.txt ;  text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO 'map=.*/.*H.*PTH_0_350.*:r_H_PTH_0_350[1,-25,25]' --PO 'map=.*/.*H.*PTH_350_450.*:r_H_PTH_350_450[1,-25,25]' --PO 'map=.*/.*H.*PTH_450_600.*:r_H_PTH_450_600[1,-25,25]' --PO 'map=.*/.*H.*PTH_G.600.*:r_H_PTH_GT600[1,-25,25]' all.txt -m 125 ;  cd -; done


for i in all_* ; do cd $i;  combineCards.py ../201*/125/*.txt > all.txt ;  text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO 'map=.*/.*H.*PTH_0_350.*:r_H_PTH_0_350[1,-25,25]' --PO 'map=.*/.*H.*PTH_350_450.*:r_H_PTH_350_450[1,-25,25]' --PO 'map=.*/.*H.*PTH_450_600.*:r_H_PTH_450_600[1,-25,25]' --PO 'map=.*/.*H.*PTH_G.600.*:r_H_PTH_GT600[1,-25,25]' all.txt -m 125 ;     par=${i/"all_"/"r_H_PTH_"}; combineTool.py -M Impacts -d all.root -m 125 --robustFit 1 --doInitialFit  --setParameterRanges r_H_PTH_0_350=-25,25:r_H_PTH_350_450=-25,25:r_H_PTH_450_600=-25,25:r_H_PTH_GT600=-25,25  --redefineSignalPOIs ${par} ;  cd -; done


for i in all_* ; do cd $i; par=${i/"all_"/"r_H_PTH_"}; combineTool.py -M Impacts -d all.root -m 125 --robustFit 1 --doFits  --setParameterRanges r_H_PTH_0_350=-25,25:r_H_PTH_350_450=-25,25:r_H_PTH_450_600=-25,25:r_H_PTH_GT600=-25,25  --redefineSignalPOIs ${par} --job-mode condor --sub-opts="+JobFlavour = \"longlunch\"\n+JobBatchName=\"Imp MC\""; cd -; done

for i in all_* ; do cd $i; par=${i/"all_"/"r_H_PTH_"}; combineTool.py -M Impacts -d all.root -m 125 -o impacts$i.json  --redefineSignalPOIs ${par}  ;  plotImpacts.py -i impacts$i.json -o impacts$i --blind ; cd -; done
for i in all_* ; do cd $i; par=${i/"all_"/"r_H_PTH_"}; combineTool.py -M Impacts -d all.root -m 125 -o impacts$i.json  --redefineSignalPOIs ${par}  ;  plotImpacts.py -i impacts$i.json -o impacts$i  ; cd -; done
 

#^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
# impact troubleshootings
#^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
# fixxing the issue with failure
combineTool.py -M Impacts -d mt.root -m 125 --robustFit 1 --doInitialFit --X-rtd MINIMIZER_freezeDisassociatedParams --X-rtd MINIMIZER_multiMin_hideConstants --X-rtd MINIMIZER_multiMin_maskConstraints --X-rtd MINIMIZER_multiMin_maskChannels=2 --rMin -1.3 --rMax 1.3


 combineTool.py -M Impacts -m 125 -d 2018.root --doInitialFit --robustFit 1 --setParameterRanges r=-10,10 --freezeParameter CMS_scale_t_1prong1pizero_tt2018



#--------------------
# Goodness of Fit GoF
#--------------------

# run GoF for each single channel
 for i in et em mt tt; do for j in 2016 2017 2018 ; do mkdir $i$j ; cd $i$j ; combineCards.py ../$j/125/*_${i}_*.txt > $i$j.txt ; combine -M GoodnessOfFit $i$j.txt --algo=saturated -m 125 ; combine -M GoodnessOfFit $i$j.txt --algo=saturated -t 500 -s 123456 -m 125 ; combineTool.py -M CollectGoodnessOfFit --input higgsCombineTest.GoodnessOfFit.mH125.root higgsCombineTest.GoodnessOfFit.mH125.123456.root  -m 125.0 -o gof${i}${j}.json ; plotGof.py gof${i}${j}.json --statistic saturated --mass 125.0 -o gof_plot_${i}${j} --title-right="$i$j" ; cd - ; done ; done
 
 
# run GoF for combined channels (all 3 years)
 for i in et em mt tt; do mkdir $i  ; cd $i ; combineCards.py ../*/125/*_${i}_*.txt > $i.txt ; combine -M GoodnessOfFit $i.txt --algo=saturated -m 125 ; combine -M GoodnessOfFit $i.txt --algo=saturated -t 500 -s 123456 -m 125 ; combineTool.py -M CollectGoodnessOfFit --input higgsCombineTest.GoodnessOfFit.mH125.root higgsCombineTest.GoodnessOfFit.mH125.123456.root  -m 125.0 -o gof${i}.json ; plotGof.py gof${i}.json --statistic saturated --mass 125.0 -o gof_plot_${i} --title-right="$i" ; cd - ; done
 
# run GoF for combined years (all 4 channels)
for i in 2016 2017 2018; do mkdir yr$i  ;  cd yr${i}; combineCards.py ../${i}/125/*.txt > ${i}.txt ;  combine -M GoodnessOfFit $i.txt --algo=saturated -m 125 ; combine -M GoodnessOfFit $i.txt --algo=saturated -t 500 -s 123456 -m 125 ; combineTool.py -M CollectGoodnessOfFit --input higgsCombineTest.GoodnessOfFit.mH125.root higgsCombineTest.GoodnessOfFit.mH125.123456.root  -m 125.0 -o gof${i}.json ; plotGof.py gof${i}.json --statistic saturated --mass 125.0 -o gof_plot_${i} --title-right="$i" ; cd - ; done
 
# run GoF for combined categories (all 4 channels)
for i in _1_ _2_ _3_ _4_ ; do mkdir $i  ;  cd ${i}; combineCards.py ../*/125/*$i*.txt > ${i}.txt ;  combine -M GoodnessOfFit $i.txt --algo=saturated -m 125 ; combine -M GoodnessOfFit $i.txt --algo=saturated -t 250 -s 123456 -m 125 ; combineTool.py -M CollectGoodnessOfFit --input higgsCombineTest.GoodnessOfFit.mH125.root higgsCombineTest.GoodnessOfFit.mH125.123456.root  -m 125.0 -o gof${i}.json ; plotGof.py gof${i}.json --statistic saturated --mass 125.0 -o gof_plot_${i} --title-right="$i" ; cd - ; done


# To run coimbined channel/years on condor
 mkdir all; cd all; combineCards.py ../201*/125/*.txt > all.txt ; text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO 'map=.*/.*H.*PTH_0_350.*:r_H_PTH_0_350[1,-25,25]' --PO 'map=.*/.*H.*PTH_350_450.*:r_H_PTH_350_450[1,-25,25]' --PO 'map=.*/.*H.*PTH_450_600.*:r_H_PTH_450_600[1,-25,25]' --PO 'map=.*/.*H.*PTH_G.600.*:r_H_PTH_GT600[1,-25,25]' all.txt -m 125 ;combine -M GoodnessOfFit all.txt --algo=saturated -m 125 ;for idx in {0..199}; do combineTool.py -d all.root -M GoodnessOfFit -m 125  -t 20 -n name_batch${idx} --job-mode condor --task-name GoF_MC_batch${idx} --sub-opts="+JobFlavour = \"longlunch\"\n+JobBatchName=\"GoF MC\"" --algo=saturated -s -1; done


mkdir all; cd all; combineCards.py ../201*/125/*.txt > all.txt ; text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO 'map=.*/.*H.*PTJ_0_350.*:r_H_PTJ_0_350[1,-25,25]' --PO 'map=.*/.*H.*PTJ_350_450.*:r_H_PTJ_350_450[1,-25,25]' --PO 'map=.*/.*H.*PTJ_450_600.*:r_H_PTJ_450_600[1,-25,25]' --PO 'map=.*/.*H.*PTJ_G.600.*:r_H_PTJ_GT600[1,-25,25]' all.txt -m 125 ;combine -M GoodnessOfFit all.txt --algo=saturated -m 125 ;for idx in {0..199}; do combineTool.py -d all.root -M GoodnessOfFit -m 125  -t 20 -n name_batch${idx} --job-mode condor --task-name GoF_MC_batch${idx} --sub-opts="+JobFlavour = \"longlunch\"\n+JobBatchName=\"GoF MC\"" --algo=saturated -s -1; done

# Draw GoF for all
 hadd X.root higgsCombinename_batch*
 combineTool.py -M CollectGoodnessOfFit --input higgsCombineTest.GoodnessOfFit.mH125.root X.root  -m 125.0 -o gof.json
 plotGof.py gof.json --statistic saturated --mass 125.0 -o gof_plot_all --title-right="all"





#--------------------
# mu-value Diff
#--------------------

rm all_GT600/higgsCombine_paramFit_Test_prop_binch19_bin9_QCD.MultiDimFit.mH125.root
rm all_350_450/higgsCombine_paramFit_Test_prop_binch19_bin9_QCD.MultiDimFit.mH125.root
rm all_0_350/higgsCombine_paramFit_Test_prop_binch19_bin9_QCD.MultiDimFit.mH125.root


 
 # run mu-value for each channel (for all 3 years)
 for i in et em mt tt; do mkdir $i ; cd $i ; combineCards.py ../*/125/*_${i}_*.txt > $i.txt ;  text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO 'map=.*/.*H.*PTH_0_350.*:r_H_PTH_0_350[1,-25,25]' --PO 'map=.*/.*H.*PTH_350_450.*:r_H_PTH_350_450[1,-25,25]' --PO 'map=.*/.*H.*PTH_450_600.*:r_H_PTH_450_600[1,-25,25]' --PO 'map=.*/.*H.*PTH_G.600.*:r_H_PTH_GT600[1,-25,25]' $i.txt -m 125 ; for j in r_H_PTH_0_350  r_H_PTH_350_450 r_H_PTH_450_600 r_H_PTH_GT600; do combine $i.root -m 125 -M MultiDimFit --redefineSignalPOIs r_H_PTH_0_350,r_H_PTH_350_450,r_H_PTH_450_600,r_H_PTH_GT600 --algo=grid -P $j --floatOtherPOIs 1 ; mv higgsCombineTest.MultiDimFit.mH125.root  higgsCombineTest.MultiDimFit.mH125_${i}_${j}.root  ; done ; cd - ;  done
 

 # run mu-value for each channel (for all 3 years)
 for i in 2016 2017 2018; do mkdir yr$i ; cd yr$i ;  combineCards.py ../${i}/125/*.txt > $i.txt ;  text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO 'map=.*/.*H.*PTH_0_350.*:r_H_PTH_0_350[1,-25,25]' --PO 'map=.*/.*H.*PTH_350_450.*:r_H_PTH_350_450[1,-25,25]' --PO 'map=.*/.*H.*PTH_450_600.*:r_H_PTH_450_600[1,-25,25]' --PO 'map=.*/.*H.*PTH_G.600.*:r_H_PTH_GT600[1,-25,25]' $i.txt -m 125 ; for j in r_H_PTH_0_350  r_H_PTH_350_450 r_H_PTH_450_600 r_H_PTH_GT600; do combine $i.root -m 125 -M MultiDimFit --redefineSignalPOIs r_H_PTH_0_350,r_H_PTH_350_450,r_H_PTH_450_600,r_H_PTH_GT600 --algo=grid -P $j --floatOtherPOIs 1 ; mv higgsCombineTest.MultiDimFit.mH125.root  higgsCombineTest.MultiDimFit.mH125_${i}_${j}.root  ; done ; cd - ;  done


# combined
 for i in all; do mkdir all$i ; cd all$i ;  combineCards.py ../*/125/*.txt > $i.txt ;  text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO 'map=.*/.*H.*PTH_0_350.*:r_H_PTH_0_350[1,-25,25]' --PO 'map=.*/.*H.*PTH_350_450.*:r_H_PTH_350_450[1,-25,25]' --PO 'map=.*/.*H.*PTH_450_600.*:r_H_PTH_450_600[1,-25,25]' --PO 'map=.*/.*H.*PTH_G.600.*:r_H_PTH_GT600[1,-25,25]' $i.txt -m 125 ; for j in r_H_PTH_0_350  r_H_PTH_350_450 r_H_PTH_450_600 r_H_PTH_GT600; do combine $i.root -m 125 -M MultiDimFit --redefineSignalPOIs r_H_PTH_0_350,r_H_PTH_350_450,r_H_PTH_450_600,r_H_PTH_GT600 --algo=grid -P $j --floatOtherPOIs 1 --cminDefaultMinimizerType Minuit2 --cminDefaultMinimizerStrategy 0 --cminDefaultMinimizerTolerance 0.1 ; mv higgsCombineTest.MultiDimFit.mH125.root  higgsCombineTest.MultiDimFit.mH125_${i}_${j}.root  ; done ; cd - ;  done

cd allall
for j in r_H_PTH_0_350  r_H_PTH_350_450 r_H_PTH_450_600 r_H_PTH_GT600; do plot1DScan.py higgsCombineTest.MultiDimFit.mH125_all_${j}.root --POI $j ;  mv scan.pdf ${j}_scan.pdf; mv scan.txt ${j}_scan.txt; done;
mkdir PDFTXT
cp *pdf *txt PDFTXT/

for i in all; do mkdir all$i ; cd all$i ;  combineCards.py ../*/125/*.txt > $i.txt ;  text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO 'map=.*/.*H.*PTJ_0_350.*:r_H_PTJ_0_350[1,-25,25]' --PO 'map=.*/.*H.*PTJ_350_450.*:r_H_PTJ_350_450[1,-25,25]' --PO 'map=.*/.*H.*PTJ_450_600.*:r_H_PTJ_450_600[1,-25,25]' --PO 'map=.*/.*H.*PTJ_G.600.*:r_H_PTJ_GT600[1,-25,25]' $i.txt -m 125 ; for j in r_H_PTJ_0_350  r_H_PTJ_350_450 r_H_PTJ_450_600 r_H_PTJ_GT600; do combine $i.root -m 125 -M MultiDimFit --redefineSignalPOIs r_H_PTJ_0_350,r_H_PTJ_350_450,r_H_PTJ_450_600,r_H_PTJ_GT600 --algo=grid -P $j --floatOtherPOIs 1 --cminDefaultMinimizerType Minuit2 --cminDefaultMinimizerStrategy 0 --cminDefaultMinimizerTolerance 0.1 ; mv higgsCombineTest.MultiDimFit.mH125.root  higgsCombineTest.MultiDimFit.mH125_${i}_${j}.root  ; done ; cd - ;  done

cd allall
for j in r_H_PTJ_0_350  r_H_PTJ_350_450 r_H_PTJ_450_600 r_H_PTJ_GT600; do plot1DScan.py higgsCombineTest.MultiDimFit.mH125_all_${j}.root --POI $j ;  mv scan.pdf ${j}_scan.pdf; mv scan.txt ${j}_scan.txt; done;


























 

 
 ########## ########## ########## ########## ########## ########## ########## ########## ########## ########## ##########
#Diff with SYS ##########
#The files are located here
/eos/uscms/store/user/abdollah/NN_output_Sys_Diff_v8
for i in /eos/uscms/store/user/abdollah/NN_output_Sys_Diff_v8/; do python DiffMeasure_DataCardProducer.py  -i $i -p 8 -o NN_disc ; done
# Then hadd the files
for i in 0 1 2 3 4 5; do for j in 2016 2017 2018 ; do hadd -f Output/datacard/V8\_bin$i\_$j\_NN.root Output/templates/*$j\_NN_disc*NN8*bin$i.root ; done ; done

hadd Diff_SysV8_2020_NN.root Output/datacard/V8*.root
cp Diff_SysV8_2020_NN.root XXX/YYY/aux/.
BoostedTau_DiffXS --prefix="Diff_SysV8" --postfix="Diff_SysV8" --year=2020 --Var=NN
sh add_auto_MC_Stat.sh Diff_SysV8
cd Diff_SysV8
combineCards.py 2020/125/H_* > all.txt

text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO 'map=.*/.*H.*PTH_0_350.*:r_H_PTH_0_350[1,-25,25]' --PO 'map=.*/.*H.*PTH_350_450.*:r_H_PTH_350_450[1,-25,25]' --PO 'map=.*/.*H.*PTH_450_600.*:r_H_PTH_450_600[1,-25,25]' --PO 'map=.*/.*H.*PTH_G.600.*:r_H_PTH_GT60  0[1,-25,25]' all.txt -m 125

text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO 'map=.*/.*H.*PTH_0_450.*:r_H_PTH_0_450[1,-25,25]' --PO 'map=.*/.*H.*PTH_450_600.*:r_H_PTH_450_600[1,-25,25]' --PO 'map=.*/.*H.*PTH_G.600.*:r_H_PTH_GT600[1,-25,25]' all.txt -m 125


combine -M FitDiagnostics all.root -m 125 --setParameterRanges r_H_PTH_0_350=-5,5:r_H_PTH_350_450=-5,5:r_H_PTH_450_600=-5,5:r_H_PTH_GT600=-5,5



combine all.root --robustFit=1 --X-rtd MINIMIZER_analytic --algo=singles --cl=0.68 --setParameters r_H_PTH_0_350=1.0,r_H_PTH_350_450=1.0,r_H_PTH_450_600=1.0,r_H_PTH_GT600=1.0 --setParameterRanges r_H_PTH_0_350=-15,15:r_H_PTH_350_450=-15,15:r_H_PTH_450_600=-15,15:r_H_PTH_GT600=-15,15 --floatOtherPOIs=1 -M MultiDimFit -n test_param0 -m 125 --cminDefaultMinimizerStrategy=0 -t -1

combine all.root --robustFit=1 --X-rtd MINIMIZER_analytic --algo=grid --cl=0.68 --redefineSignalPOIs r_H_PTH_0_450 --setParameterRanges r_H_PTH_0_450=-15,15:r_H_PTH_450_600=-15,15:r_H_PTH_GT600=-15,15 --floatOtherPOIs=1 -M MultiDimFit -n test_param0 -m 125 --cminDefaultMinimizerStrategy=0

combine all.root --robustFit=1 --X-rtd MINIMIZER_analytic --algo=grid --cl=0.68 --redefineSignalPOIs r --setParameterRanges 1=-15,15 -M MultiDimFit -n test_param0 -m 125 --cminDefaultMinimizerStrategy=0

#Impact
#combineTool.py -M Impacts -d all.root -m 125 --doInitialFit --robustFit 1 --setParameterRanges r_H_PTH_0_350=-15,15:r_H_PTH_350_450=-15,15:r_H_PTH_450_600=-15,15:r_H_PTH_GT600=-15,15 --redefineSignalPOIs r_H_PTH_350_600
#combineTool.py -M Impacts -d all.root -m 125 --doFit --robustFit 1 --setParameterRanges r_H_PTH_0_350=-15,15:r_H_PTH_350_450=-15,15:r_H_PTH_450_600=-15,15:r_H_PTH_GT600=-15,15 --job-mode condor

combineTool.py -M Impacts -d all.root -m 125 --doInitialFit --robustFit 1 --setParameterRanges r_H_PTH_450_600=-15,15:r_H_PTH_GT600=-15,15 --redefineSignalPOIs r_H_PTH_450_600


combine all.root --robustFit=1 --X-rtd MINIMIZER_analytic --algo=grid -P CMS_scale_t_1prong1pizero_tt2016 --floatOtherPOIs=1 -M MultiDimFit -n test_param0 -m 125 --cminDefaultMinimizerStrategy=0



scp cmslpc127.fnal.gov:/uscms_data/d3/abdollah/Analysis/Limit/CMSSW_10_2_13/src/CombineHarvester/CombineTools/bin/Diff_SysV9_LeadJet/higgsCombinetest_param0.MultiDimFit.mH125.root /Users/abdollah/cernbox/Analysis/BoostedH/NewBoostedH/BoostedHTT/Limit/higgsCombinetest_param0.MultiDimFit.mH125_hpt.root



#This is for Higgs pT
 --- MultiDimFit ---
best fit parameter values and profile-likelihood uncertainties:
     r_H_PTH_0_300 :    -0.487   -4.813/+5.270 (68%)
     r_H_PTH_GT800 :    +3.562   -3.575/+4.446 (68%)
   r_H_PTH_300_400 :    +0.962   -2.488/+2.513 (68%)
   r_H_PTH_550_800 :    -0.163   -0.766/+1.525 (68%)
   r_H_PTH_400_550 :    +1.519   -1.241/+1.227 (68%)
Done in 0.34 min (cpu), 0.34 min (real)




# Now try for leading Jet pT
best fit parameter values and profile-likelihood uncertainties:
     r_H_PTH_0_300 :    -0.039   -0.660/+0.697 (68%)
     r_H_PTH_GT800 :    -1.075   -0.829/+1.301 (68%)
   r_H_PTH_300_400 :    +0.181   -0.609/+0.639 (68%)
   r_H_PTH_550_800 :    -1.116   -0.733/+0.994 (68%)
   r_H_PTH_400_550 :    -0.519   -0.594/+0.641 (68%)





#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#  Unblinded Impact Differential
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%






#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Impacts
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

 text2workspace.py htt_tt.txt -m 125
combineTool.py -M Impacts -d all.root -m 125 --doInitialFit --robustFit 1 --setParameterRanges r=-10,10 (-t -1 --expectSignal 1 )

combineTool.py -M Impacts -d all.root -m 125 --robustFit 1 --doFits --setParameterRanges r=-10,10 (-t -1 --expectSignal 1)
combineTool.py -M Impacts -m 125 --doFits --rMin -20 --rMax 20 -d all.root --job-mode condor --robustFit 1 --task-name combined_dl_impacts --setParameterRanges r=-10,10

combineTool.py -M Impacts -d all.root -m 125 -o impacts.json
plotImpacts.py -i impacts.json -o impacts_cmb_sig_qcd --blind

combineTool.py -M Impacts -d all.root -m 125 -o impacts.json --redefineSignalPOIs r_H_PTH_0_350

#combineTool.py -M Impacts -d em2016.root -m 125 --doInitialFit --robustFit 1 -t -1 --expectSignal 1 --job-mode condor --task-name doInitialFit_em2016 --dry-run
#combineTool.py -M Impacts -d 2018.root -m 125 --robustFit 1 --doFits -t -1 --expectSignal 1 --job-mode condor --task-name doFits_2018 --dry-run


 
 
 
 
# impact with condors
# mkdir all ; cd all ; combineCards.py ../*/125/*.txt > all.txt ;  text2workspace.py all.txt -m 125 ; combineTool.py -M Impacts -d all.root -m 125 --doInitialFit --robustFit 1 --setParameterRanges r=-10,10; combineTool.py -M Impacts -m 125 --doFits --rMin -20 --rMax 20 -d all.root --job-mode condor --robustFit 1 --task-name combined_dl_impacts --setParameterRanges r=-10,10 ;combineTool.py -M Impacts -d all.root -m 125 -o impacts.json; plotImpacts.py -i impacts.json -o impacts_all --blind
 mkdir all ; cd all ; text2workspace.py all.txt -m 125 ; combineTool.py -M Impacts -d all.root -m 125 --doInitialFit --robustFit 1 --setParameterRanges r=-10,10; combineTool.py -M Impacts -m 125 --doFits --rMin -20 --rMax 20 -d all.root --job-mode condor --robustFit 1 --task-name combined_dl_impacts --setParameterRanges r=-10,10 ;combineTool.py -M Impacts -d all.root -m 125 -o impacts.json; plotImpacts.py -i impacts.json -o impacts_all --blind
 
 
 
 condor_submit condor_combined_dl_impacts.sub
 
 
 
 
 #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# GOF Diff
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#BoostedTau_DiffXS --prefix="V1_Diff_hpt_rename" --postfix="V1_Diff_dr0p5_hpt_GOF" --year=2016 --Var=NN
#BoostedTau_DiffXS --prefix="V1_Diff_hpt_rename" --postfix="V1_Diff_dr0p5_hpt_GOF" --year=2017 --Var=NN
#BoostedTau_DiffXS --prefix="V1_Diff_hpt_rename" --postfix="V1_Diff_dr0p5_hpt_GOF" --year=2018 --Var=NN
#BoostedTau_DiffXS --prefix="V1_Diff_hpt_rename" --postfix="V1_Diff_dr0p5_hpt_Impact" --year=2016 --Var=NN
#BoostedTau_DiffXS --prefix="V1_Diff_hpt_rename" --postfix="V1_Diff_dr0p5_hpt_Impact" --year=2017 --Var=NN
#BoostedTau_DiffXS --prefix="V1_Diff_hpt_rename" --postfix="V1_Diff_dr0p5_hpt_Impact" --year=2018 --Var=NN
#
#sh add_auto_MC_Stat.sh V1_Diff_dr0p5_hpt_GOF
#sh add_auto_MC_Stat.sh V1_Diff_dr0p5_hpt_Impact
#
#
#





 
 



 
 
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#  Preparing Datacard for Differential Measurements   Step 3  Drawing the differential plots
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



cd    /Users/abdollah/cernbox/Analysis/BoostedH/NewBoostedH/BoostedHTT/Limit
#We need to have a script called:   File_Theory_Diff.py  This creates the    differential_theory_2.root file which has a certain structure
python File_Theory_Diff.py -i AllHiggs_v5_sys -o differential_theory_5.root
#To run the above file we need to already  have a directory with the different Higgs process root files called AllHiggs_v3_sys
# The out come of the above file is differential_theory_3.root whihc is the input to Draw_differential_Boost.py
# The last step is to run Draw_differential_Boost.py


python Draw_differential_Boost.py -g AllROOT/higgsCombinetest_param0.MultiDimFit.mH125_hpt_V9_Fid.root -i AllROOT/differential_theory_5.root -o out -j hpt
# This needs four arguments. one is the theory differential and one is the houtcome of teh Higgs combined
#This create two files pdf and png
#





for i in */higgsCombineTest.MultiDimFit.mH125*root; do for j in r_H_PTH_0_350  r_H_PTH_350_450 r_H_PTH_450_600 r_H_PTH_GT600; do plot1DScan.py $i --POI $j ;  mv scan.pdf ${i}_scan.pdf; mv scan.txt ${i}_scan.txt; done; done


#==========================
#How to make differential_theory.root file



#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#List of files that the final resulst were made from
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# final plotting for inclusive analysis
postfit_shapes_all_V32_fixTESNew_13bin.root



#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# special treatment for diff dR0p5 (3 bins)
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
for i in 201*/*0_350* ; do echo $i ; name=${i/"0_350"/"0_450"} ; echo "-->"${name}; cp $i ${name}; done







#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



#                                              OverLapping Analysis                                              #



#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%




#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#Step 3 of unblinding of the inclusive analysis   (Overlapping)
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#============================
#Expected and observed significance as well muValue all in root file
#============================
python QuickLimit_ReadRootFile.py V32_fixTESNew_13bin_Unblinding WithOverlap
# The outcome will b ethe two following root files
# Then we open the following two files and save the histograms:
-rw-r--r--  1 abdollah  4894 Sep 13 14:14 OutReadFile_WithOverlap_V32_fixTESNew_13bin_Unblinding_ObsSig.root
-rw-r--r--  1 abdollah  4905 Sep 13 14:14 OutReadFile_WithOverlap_V32_fixTESNew_13bin_Unblinding_ExpSig.root

PostFitShapesFromWorkspace -w all.root -f fitDiagnosticsTest.root:fit_s --postfit  --print -d  all.txt -o postfit_shapes_all.root -m 125

#postfit plotspost
python Draw_POSTPREFIT_Boost_CMB.py V32_fixTESNew_13bin/postfit_shapes_all.root  HPT_0p8 inc


#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#Step 3 of unblinding of the differential analysis v.s. Higgs pT  (Overlapping)
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


# to get the diff money plot
python Draw_differential_Boost_4bins.py -g FITALL_multiDim -i differential_theory_5_fourBins.root -o moneyPlot_higgsPtdr0p8 -j hpt


#============================
#draw prefit/postfit plots
#============================
# The postfot plot can be found here V2_diff_jpt_qcdratefix/postfit_shapes_all_V2_diff_jpt_qcdratefix.root   with 48 channels 4(bin)*4(channel)*3(year)
python Draw_POSTPREFIT_Boost_CMB.py V4_unblind_hpt_otherimpacts/postfit_shapes_all_diff_V4.root Inclusive_0p8 diff



#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#Step 3 of unblinding of the differential analysis v.s. lead jet pT (Overlapping)
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# We need to have the following files in 4 bins
differential_theory_5_fourBins.root

#on lxplus:
cd /afs/cern.ch/work/a/abdollah/scratch1/LimiBoosted/CMSSW_10_2_13/src/CombineHarvester/CombineTools/bin/V2_diff_jpt_qcdratefix

 # run mu-value for each channel (for all 3 years)
 for i in et em mt tt; do mkdir $i ; cd $i ; combineCards.py ../*/125/*_${i}_*.txt > $i.txt ;  text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO 'map=.*/.*H.*PTH_0_350.*:r_H_PTH_0_350[1,-25,25]' --PO 'map=.*/.*H.*PTH_350_450.*:r_H_PTH_350_450[1,-25,25]' --PO 'map=.*/.*H.*PTH_450_600.*:r_H_PTH_450_600[1,-25,25]' --PO 'map=.*/.*H.*PTH_G.600.*:r_H_PTH_GT600[1,-25,25]' $i.txt -m 125 ; for j in r_H_PTH_0_350  r_H_PTH_350_450 r_H_PTH_450_600 r_H_PTH_GT600; do combine $i.root -m 125 -M MultiDimFit --redefineSignalPOIs r_H_PTH_0_350,r_H_PTH_350_450,r_H_PTH_450_600,r_H_PTH_GT600 --algo=grid -P $j --floatOtherPOIs 1 ; mv higgsCombineTest.MultiDimFit.mH125.root  higgsCombineTest.MultiDimFit.mH125_${i}_${j}.root  ; done ; cd - ;  done
 
 # run mu-value for each channel (for all 3 years)
 for i in 2016 2017 2018; do mkdir yr$i ; cd yr$i ;  combineCards.py ../${i}/125/*.txt > $i.txt ;  text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO 'map=.*/.*H.*PTH_0_350.*:r_H_PTH_0_350[1,-25,25]' --PO 'map=.*/.*H.*PTH_350_450.*:r_H_PTH_350_450[1,-25,25]' --PO 'map=.*/.*H.*PTH_450_600.*:r_H_PTH_450_600[1,-25,25]' --PO 'map=.*/.*H.*PTH_G.600.*:r_H_PTH_GT600[1,-25,25]' $i.txt -m 125 ; for j in r_H_PTH_0_350  r_H_PTH_350_450 r_H_PTH_450_600 r_H_PTH_GT600; do combine $i.root -m 125 -M MultiDimFit --redefineSignalPOIs r_H_PTH_0_350,r_H_PTH_350_450,r_H_PTH_450_600,r_H_PTH_GT600 --algo=grid -P $j --floatOtherPOIs 1 ; mv higgsCombineTest.MultiDimFit.mH125.root  higgsCombineTest.MultiDimFit.mH125_${i}_${j}.root  ; done ; cd - ;  done

# combined
 for i in all; do mkdir all$i ; cd all$i ;  combineCards.py ../*/125/*.txt > $i.txt ;  text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO 'map=.*/.*H.*PTH_0_350.*:r_H_PTH_0_350[1,-25,25]' --PO 'map=.*/.*H.*PTH_350_450.*:r_H_PTH_350_450[1,-25,25]' --PO 'map=.*/.*H.*PTH_450_600.*:r_H_PTH_450_600[1,-25,25]' --PO 'map=.*/.*H.*PTH_G.600.*:r_H_PTH_GT600[1,-25,25]' $i.txt -m 125 ; for j in r_H_PTH_0_350  r_H_PTH_350_450 r_H_PTH_450_600 r_H_PTH_GT600; do combine $i.root -m 125 -M MultiDimFit --redefineSignalPOIs r_H_PTH_0_350,r_H_PTH_350_450,r_H_PTH_450_600,r_H_PTH_GT600 --algo=grid -P $j --floatOtherPOIs 1 ; mv higgsCombineTest.MultiDimFit.mH125.root  higgsCombineTest.MultiDimFit.mH125_${i}_${j}.root  ; done ; cd - ;  done

# combined for LeadJet
 for i in all; do mkdir all$i ; cd all$i ;  combineCards.py ../*/125/*.txt > $i.txt ;  text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO 'map=.*/.*H.*PTJ_0_350.*:r_H_PTJ_0_350[1,-25,25]' --PO 'map=.*/.*H.*PTJ_350_450.*:r_H_PTJ_350_450[1,-25,25]' --PO 'map=.*/.*H.*PTJ_450_600.*:r_H_PTJ_450_600[1,-25,25]' --PO 'map=.*/.*H.*PTJ_G.600.*:r_H_PTJ_GT600[1,-25,25]' $i.txt -m 125 ; for j in r_H_PTJ_0_350  r_H_PTJ_350_450 r_H_PTJ_450_600 r_H_PTJ_GT600; do combine $i.root -m 125 -M MultiDimFit --redefineSignalPOIs r_H_PTJ_0_350,r_H_PTJ_350_450,r_H_PTJ_450_600,r_H_PTJ_GT600 --algo=grid -P $j --floatOtherPOIs 1 ; mv higgsCombineTest.MultiDimFit.mH125.root  higgsCombineTest.MultiDimFit.mH125_${i}_${j}.root  ; done ; cd - ;  done


cd /afs/cern.ch/work/a/abdollah/scratch1/LimiBoosted/CMSSW_10_2_13/src/CombineHarvester/CombineTools/bin/V2_diff_jpt_qcdratefix
for i in */higgsCombineTest.MultiDimFit.mH125*root; do for j in r_H_PTH_0_350  r_H_PTH_350_450 r_H_PTH_450_600 r_H_PTH_GT600; do plot1DScan.py $i --POI $j ;  mv scan.pdf ${i}_scan.pdf; mv scan.txt ${i}_scan.txt; done; done

#============================
# LL Scan
#============================
plot1DScan.py higgsCombineTest.MultiDimFit.mH125_all_r_H_PTH_0_350.root --POI r_H_PTH_0_350


#Once done copy the directory to laptop
/Users/abdollah/cernbox/Analysis/BoostedH/NewBoostedH/BoostedHTT/Limit/V2_diff_jpt_qcdratefix_Unblinding

#============================
#draw muValue
#============================
python drawGraph_muValue_DiffAnalysis_multiDim_fromtxt.py higssPt0p5 FITALL_multiDim_JetPt

#============================
#draw money plot:
#============================
cd /Users/abdollah/cernbox/Analysis/BoostedH/NewBoostedH/BoostedHTT/Limit/V2_diff_jpt_qcdratefix_Unblinding/allall
hadd higgsCombineTest.MultiDimFit.mH125_all_cmb.root higgsCombineTest.MultiDimFit.mH125_all_r_H_PTH_*.root

cd /Users/abdollah/cernbox/Analysis/BoostedH/NewBoostedH/BoostedHTT/Limit/
python Draw_differential_Boost_4bins.py -g V2_diff_jpt_qcdratefix_Unblinding/allall/    -i differential_theory_5_fourBins.root -o moneyPlot_jetPtdr0p8 -j jpt


#============================
#draw prefit/postfit plots
#============================
# The postfot plot can be found here V2_diff_jpt_qcdratefix/postfit_shapes_all_V2_diff_jpt_qcdratefix.root   with 48 channels 4(bin)*4(channel)*3(year)
python Draw_POSTPREFIT_Boost_CMB.py V2_diff_jpt_qcdratefix/postfit_shapes_all_V2_diff_jpt_qcdratefix.root JPT_0p8 diff

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



#                                              Non OverLapping Analysis                                              #



#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%







#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#Step 3 of unblinding of the non-overlapping inclusive analysis
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#location:
cd /afs/cern.ch/work/a/abdollah/scratch1/LimiBoosted/CMSSW_10_2_13/src/CombineHarvester/CombineTools/bin/V3_dr0p5_qcdfix
python QuickLimit_Unblinding.py var V3_dr0p5_qcdfix var
#to run on the combined channels:
combine -M Significance -d all.root -m 125 -t -1 --expectSignal=1
combine -M Significance -d all.root -m 125
combine -M FitDiagnostics all.root -m 125 --rMin -5 --rMax 5  --robustFit=1

#The copy the directory to the laptop:
scp -r lxplus.cern.ch:/afs/cern.ch/work/a/abdollah/scratch1/LimiBoosted/CMSSW_10_2_13/src/CombineHarvester/CombineTools/bin/V3_dr0p5_qcdfix .

#============================
#Expected and observed significance as well muValue all in root file
#============================
python QuickLimit_ReadRootFile.py V3_dr0p5_qcdfix noOverlap
# The outcome will b ethe two following root files
# Then we open the following two files and save the histograms:
-rw-r--r--    1 abdollah      4738 Sep  9 12:15 OutReadFile_noOverlap_V3_dr0p5_qcdfix_ObsSig.root
-rw-r--r--    1 abdollah      4747 Sep  9 12:15 OutReadFile_noOverlap_V3_dr0p5_qcdfix_ExpSig.root

#============================
# LL scan plot
#============================
combine all.root -m 125 -M MultiDimFit --redefineSignalPOIs r --algo=grid -P r --floatOtherPOIs 1
plot1DScan.py higgsCombineTest.MultiDimFit.mH125.root --POI r
# the outcome will be scan.pdf and scan.png






#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#Step 3 of unblinding of the differential analysis v.s. Higgs pT  non overalpping region
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# We need to have the following files in 4 bins
differential_theory_5_fourBins.root

#on lxplus:
cd /afs/cern.ch/work/a/abdollah/scratch1/LimiBoosted/CMSSW_10_2_13/src/CombineHarvester/CombineTools/bin/V2_diff_jpt_qcdratefix


 # run mu-value for each channel (for all 3 years)
 for i in et em mt tt; do mkdir $i ; cd $i ; combineCards.py ../*/125/*_${i}_*.txt > $i.txt ;  text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel  --PO 'map=.*/.*H.*PTH_450_600.*:r_H_PTH_450_600[1,-25,25]' --PO 'map=.*/.*H.*PTH_G.600.*:r_H_PTH_GT600[1,-25,25]' $i.txt -m 125 ; for j in r_H_PTH_450_600 r_H_PTH_GT600; do combine $i.root -m 125 -M MultiDimFit --redefineSignalPOIs r_H_PTH_450_600,r_H_PTH_GT600 --algo=grid -P $j --floatOtherPOIs 1 ; mv higgsCombineTest.MultiDimFit.mH125.root  higgsCombineTest.MultiDimFit.mH125_${i}_${j}.root  ; done ; cd - ;  done
 

 # run mu-value for each channel (for all 3 years)
 for i in 2016 2017 2018; do mkdir yr$i ; cd yr$i ;  combineCards.py ../${i}/125/*.txt > $i.txt ;  text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO 'map=.*/.*H.*PTH_450_600.*:r_H_PTH_450_600[1,-25,25]' --PO 'map=.*/.*H.*PTH_G.600.*:r_H_PTH_GT600[1,-25,25]' $i.txt -m 125 ; for j in r_H_PTH_450_600 r_H_PTH_GT600; do combine $i.root -m 125 -M MultiDimFit --redefineSignalPOIs r_H_PTH_450_600,r_H_PTH_GT600 --algo=grid -P $j --floatOtherPOIs 1 ; mv higgsCombineTest.MultiDimFit.mH125.root  higgsCombineTest.MultiDimFit.mH125_${i}_${j}.root  ; done ; cd - ;  done


# combined
 for i in all; do mkdir all$i ; cd all$i ;  combineCards.py ../*/125/*.txt > $i.txt ;  text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO 'map=.*/.*H.*PTH_450_600.*:r_H_PTH_450_600[1,-25,25]' --PO 'map=.*/.*H.*PTH_G.600.*:r_H_PTH_GT600[1,-25,25]' $i.txt -m 125 ; for j in r_H_PTH_450_600 r_H_PTH_GT600; do combine $i.root -m 125 -M MultiDimFit --redefineSignalPOIs r_H_PTH_450_600,r_H_PTH_GT600 --algo=grid -P $j --floatOtherPOIs 1 ; mv higgsCombineTest.MultiDimFit.mH125.root  higgsCombineTest.MultiDimFit.mH125_${i}_${j}.root  ; done ; cd - ;  done


cd /afs/cern.ch/work/a/abdollah/scratch1/LimiBoosted/CMSSW_10_2_13/src/CombineHarvester/CombineTools/bin/V2_Diff_dr0p5_hpt_2bin/V2_Diff_dr0p5_hpt_2bin_Unblinding_Step3
for i in */higgsCombineTest.MultiDimFit.mH125*root; do for j in r_H_PTH_450_600 r_H_PTH_GT600; do plot1DScan.py $i --POI $j ;  mv scan.pdf ${i}_scan.pdf; mv scan.txt ${i}_scan.txt; done; done

#============================
# LL scan
#============================

plot1DScan.py higgsCombineTest.MultiDimFit.mH125_all_r_H_PTH_GT600.root --POI r_H_PTH_GT600

#============================
# muvalue plots
#============================
python drawGraph_muValue_DiffAnalysis_multiDim_fromtxt.py higssPt0p5 FITALL_multiDim_HiggsPt0p5


#============================
#draw prefit/postfit plots
#============================
# The postfot plot can be found here V2_diff_jpt_qcdratefix/postfit_shapes_all_V2_diff_jpt_qcdratefix.root   with 48 channels 4(bin)*4(channel)*3(year)
python Draw_POSTPREFIT_Boost_CMB.py V1_Diff_hpt_dr0p5_noEmu_forPostFitPlots/postfit_shapes_all.root HPT_0p5 diff




#============================
#Comments from Andrea
#============================
 Andrea_Validation $ for i in mt et em tt ; do for j in 2016 2017 2018; do for k in ZTT ggH125 VV TT ; do python NN_comparrer.py AndreaNNValidationRootFiles/${i}_${j}_runOnTrainHalf1 AndreaNNValidationRootFiles/${i}_${j}_runOnTrainHalf2 $k $i $j ; done ; done ; done
