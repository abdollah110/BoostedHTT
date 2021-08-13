input=$1
year=$2
version=$3

echo 'processing ' ${year}
python preprocess.py -i $input -o Training_${version}_${year} -s 1
python train.py --signal JJH125 --background QCD --background2 ZTT --input datasets/Training_${version}_${year}.h5  --year ${year} --model outputModel_${version}_${year}


