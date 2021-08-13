Loc=$1
for year in 2016 
do
	echo 'processing ' ${year}
	python preprocess.py --em-input  ${Loc} -o  Nominal_preprocess_${year}


done

