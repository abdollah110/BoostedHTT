input=$1
Name=$2
python preprocess_X.py --mu-input ${input}  -o testData_${Name}
python train_X.py --signal JJH125 --background NonDY --background2 ZTT --input datasets/testData_${Name}.h5 --model outputModel_${Name}
python classify_X.py --treename emu_tree --input-vbf datasets/testData_${Name}.h5  --model-vbf outputModel_${Name}   --dir ${input}  --output-dir ${Name}_NN

