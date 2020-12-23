input=$1
Name=$2
Tree=$3

python preprocess.py -i  ${input}  -o testData_${Name}
python train.py --signal JJH125 --background ZTT --input datasets/testData_${Name}.h5 --model outputModel_${Name}
python classify.py --treename ${Tree} --input-vbf datasets/testData_${Name}.h5  --model-vbf models/outputModel_${Name}.hdf5   --dir ${input}  --output-dir ${Name}_NN



#sh run_all.sh ../Analysis/Output/trees/boost_mt_2016_v1/NN_nominal boost_mt_2016_v1 mutau_tree
#sh run_all.sh ../Analysis/Output/trees/boost_et_2016_v1/NN_nominal boost_et_2016_v1 etau_tree
#sh run_all.sh ../Analysis/Output/trees/boost_mt_2017_v1/NN_nominal boost_mt_2017_v1 mutau_tree
#sh run_all.sh ../Analysis/Output/trees/boost_et_2017_v1/NN_nominal boost_et_2017_v1 etau_tree
#sh run_all.sh ../Analysis/Output/trees/boost_mt_2018_v1/NN_nominal boost_mt_2018_v1 mutau_tree
#sh run_all.sh ../Analysis/Output/trees/boost_et_2018_v1/NN_nominal boost_et_2018_v1 etau_tree
