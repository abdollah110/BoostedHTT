#This step is done running analyze
# first
mv _ ~/.
mkdir _nominal
mv *root _nominal

for SYS in *;
do
    mkdir NN${SYS}

    hadd   -f NN${SYS}/Data${SYS}.root    ${SYS}/data*
    hadd   -f NN${SYS}/WJetsToLNu${SYS}.root    ${SYS}/*_W_*.root
    hadd   -f NN${SYS}/VV${SYS}.root    ${SYS}/*_VV_*.root
    hadd   -f NN${SYS}/TTJets${SYS}.root    ${SYS}/TT*.root
    hadd   -f NN${SYS}/ZLL${SYS}.root    ${SYS}/*_ZLL_*.root
    hadd   -f NN${SYS}/DYJetsToLL${SYS}.root    ${SYS}/*_ZTT_*
    hadd   -f NN${SYS}/ZJ${SYS}.root    ${SYS}/*_ZJ_*

done


for file in NN_nominal/*
do
    mv $file ${file/"_nominal.root"/".root"}
done


###### move junk files to DEL directory

mkdir DEL
find . -name "*.root" -size -2k | xargs -n 1 -I {} mv {} DEL/

