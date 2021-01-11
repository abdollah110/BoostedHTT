#This step is done running analyze
# first
dir=$1
cd ${dir}
mv _ ~/.
mkdir _nominal
mv *root _nominal

for SYS in _*;
do
    mkdir NN${SYS}

    hadd   -f NN${SYS}/Data${SYS}.root    ${SYS}/*data*
    hadd   -f NN${SYS}/W${SYS}.root    ${SYS}/*_W_*.root
    hadd   -f NN${SYS}/VV${SYS}.root    ${SYS}/*_VV_*.root
    hadd   -f NN${SYS}/TT${SYS}.root    ${SYS}/TT*.root
    hadd   -f NN${SYS}/ZLL${SYS}.root    ${SYS}/*_ZLL_*.root
    hadd   -f NN${SYS}/ZTT${SYS}.root    ${SYS}/*_ZTT_*
    hadd   -f NN${SYS}/ZJ${SYS}.root    ${SYS}/*_ZJ_*
    hadd   -f NN${SYS}/JJH125${SYS}.root    ${SYS}/*JJH*
#    hadd   -f NN${SYS}/WH125${SYS}.root    ${SYS}/*WMinusH125_* ${SYS}/*WPlusH125_*
#    hadd   -f NN${SYS}/ZH125${SYS}.root    ${SYS}/*ZH125_*
#    hadd   -f NN${SYS}/ggH125${SYS}.root    ${SYS}/*ggH125*
#    hadd   -f NN${SYS}/qqH125${SYS}.root    ${SYS}/*qqH125*
    hadd  -f NN${SYS}/H125${SYS}.root   ${SYS}/*WMinusH125_* ${SYS}/*WPlusH125_*  ${SYS}/*ZH125_*  ${SYS}/*ggH125*  ${SYS}/*qqH125*
    hadd   -f NN${SYS}/H125${SYS}.root    ${SYS}/*WMinusH125_* ${SYS}/*WPlusH125_* ${SYS}/*ZH125_*  ${SYS}/*ggH125*  ${SYS}/*qqH125*


done


for file in NN_nominal/*
do
    mv $file ${file/"_nominal.root"/".root"}
done


###### move junk files to DEL directory

mkdir DEL
find . -name "*.root" -size -2k | xargs -n 1 -I {} mv {} DEL/
cd -
