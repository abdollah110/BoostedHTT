input=$1
channel=$2

echo 'processing ' ${channel}
python preprocess.py -i $input -o NominalTraining_${channel} -s 1
python train.py --signal JJH125 --background NonDY --background2 ZTT --input datasets/NominalTraining_${channel}.h5  --model outputModel_NominalTraining_${channel}
    


