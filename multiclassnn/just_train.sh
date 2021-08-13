version=$1
year=$2

	echo 'processing ' ${year}
        python preprocess.py --em-input  /hdfs/store/user/abdollah/PreApproval_rootFiles_${version}/AllCondor_${year}_v11/NN_NOMINAL/ -o Training_${version}_${year} -s 1   

	python train.py --signal _qqH_inc --background TT --background2 ZTT --input datasets/Training_${version}_${year}.h5 --category vbf --year ${year} --model outputModel_${version}_${year}


