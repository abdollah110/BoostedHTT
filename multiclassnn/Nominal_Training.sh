input=$1
channel=$2

echo 'processing ' ${channel}
python preprocess.py -i $input -o NominalPreprocess_${channel} -s 1
python train.py --signal JJH125 --background NonDY --background2 ZTT --input datasets/NominalPreprocess_${channel}.h5  --model outputModel_NominalTraining_${channel}
    


