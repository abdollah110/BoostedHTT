input=$1
Name=$2
Tree=$3

python preprocess.py -i  ${input}  -o testData_${Name}
python train.py --signal JJH125 --background NonDY --background2 ZTT --input datasets/testData_${Name}.h5 --model outputModel_${Name}
python classify.py --treename ${Tree} --input-vbf datasets/testData_${Name}.h5  --model-vbf models/outputModel_${Name}.hdf5   --dir ${input}  --output-dir ${Name}_NN



#sh run_all.sh ../Analysis/Output/trees/boost_mt_2016_v1/NN_nominal boost_mt_2016_v1 mutau_tree
#sh run_all.sh ../Analysis/Output/trees/boost_et_2016_v1/NN_nominal boost_et_2016_v1 etau_tree
#sh run_all.sh ../Analysis/Output/trees/boost_mt_2017_v1/NN_nominal boost_mt_2017_v1 mutau_tree
#sh run_all.sh ../Analysis/Output/trees/boost_et_2017_v1/NN_nominal boost_et_2017_v1 etau_tree
#sh run_all.sh ../Analysis/Output/trees/boost_mt_2018_v1/NN_nominal boost_mt_2018_v1 mutau_tree
#sh run_all.sh ../Analysis/Output/trees/boost_et_2018_v1/NN_nominal boost_et_2018_v1 etau_tree


#[abdollah@cmslpc169 test]$ dasgoclient -query="dataset dataset=/JJH0PMToTauTauPlusTwoJets*/*/MINIAODSIM"
#
#
#/JJH0PMToTauTauPlusTwoJets_Filtered_M125_TuneCUETP8M1_13TeV-mcatnloFXFX-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM
#/JJH0PMToTauTauPlusTwoJets_M125_TuneCUETP8M1_13TeV-mcatnloFXFX-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM
#
#/JJH0PMToTauTauPlusTwoJets_Filtered_M125_TuneCP5_13TeV-mcatnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM
#/JJH0PMToTauTauPlusTwoJets_M125_TuneCP5_13TeV-mcatnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM
#
#/JJH0PMToTauTauPlusTwoJets_Filtered_M125_TuneCP5_13TeV-mcatnloFXFX-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM
#/JJH0PMToTauTauPlusTwoJets_M125_TuneCP5_13TeV-mcatnloFXFX-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM
#
#
#




