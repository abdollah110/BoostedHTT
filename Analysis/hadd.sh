#This step is done running analyze
# first
mv _ ~/.
mkdir _nominal
mv *root _nominal

for SYS in *_;
do
    mkdir NN${SYS}

    hadd   NN${SYS}/Data${SYS}.root    ${SYS}/data*
    hadd   NN${SYS}/W${SYS}.root    ${SYS}/*_W_*.root
    hadd   NN${SYS}/VV${SYS}.root    ${SYS}/*_VV_*.root
    hadd   NN${SYS}/TT${SYS}.root    ${SYS}/TT*.root
    hadd   NN${SYS}/ZLL${SYS}.root    ${SYS}/*_ZLL_*.root
    hadd   NN${SYS}/ZTT${SYS}.root    ${SYS}/*_ZTT_*
    hadd   NN${SYS}/ZJ${SYS}.root    ${SYS}/*_ZJ_*

done


for file in NN_nominal/*
do
    mv $file ${file/"_nominal.root"/".root"}
done


###### move junk files to DEL directory

mkdir DEL
find . -name "*.root" -size -2k | xargs -n 1 -I {} mv {} DEL/

