version=$1
year=$2

	echo 'processing ' ${year}  ' version is' ${version}
        python preprocess.py --em-input  /nfs_scratch/abdollah/_Code_/CMSSW_9_4_0/src/ltau_analyzers/Output/trees/AllCondor_2017_v13_harvest_NN_NOMINAL -o Training_${version}_${year} -s 1   

	python train.py --signal _qqH_inc --background TT --background2 ZTT --input datasets/Training_${version}_${year}.h5 --category vbf --year ${year} --model outputModel_${version}_${year}


