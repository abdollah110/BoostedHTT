#!/bin/bash
#
echo "input parameters: cluster, process, run path, out path, sample name" $1 $2 $3 $4
CLUSTER=$1
PROCESS=$2
RUNPATH=$3
OUTPATH=$4

echo "PROCESS: $PROCESS"

############  set the enviroment and copy the neccessary files
source /cvmfs/cms.cern.ch/cmsset_default.sh
setenv SCRAM_ARCH slc6_amd64_gcc630
scramv1 project CMSSW_10_2_10
cd CMSSW_10_2_10/src
xrdcp root://cmseos.fnal.gov//store/user/abdollah/TarFile.tar.gz   .
tar -xf TarFile.tar.gz
rm TarFile.tar.gz
cd TarFile
eval `scramv1 runtime -sh`
mkdir models datasets
ls

############  run FastMTT
FullSampleName=`sed -n "$((PROCESS+1))p"  < InputSamples_NN.txt`
ShortName=${FullSampleName##*/}

ArrayName=(${FullSampleName//// })
order=${#ArrayName[@]}-2
NewName=${ArrayName[${order}]}
xrdcp root://cmseos.fnal.gov//store/user/abdollah/NN_input/${NewName}.tar.gz .
tar -xf ${NewName}.tar.gz

Name="NN_"$NewName
inputdir=$NewName"/NN_nominal"

echo "  inputdir is " $inputdir
    
python preprocess.py -i  ${inputdir}  -o testData_${Name}
if [[ ${inputdir} == *"_em_"* ]]; then
  python train.py --signal JJH125 --ZTT ZTT --QCD NonDY --input datasets/testData_${Name}.h5 --model outputModel_${Name}
else
  python train.py --signal JJH125 --ZTT ZTT --QCD NonDY --input datasets/testData_${Name}.h5 --model outputModel_${Name}
fi
#python train.py --signal JJH125 --background ZTT --input datasets/testData_${Name}.h5 --model outputModel_${Name}
python classify.py  --input-boost datasets/testData_${Name}.h5  --model-boost models/outputModel_${Name}.hdf5   --dir ${inputdir}  --output-dir ${Name}_NN


xrdfs root://cmseos.fnal.gov/ mkdir /store/user/abdollah/NN_output/${Name}_NN
xrdcp -rf ${Name}_NN  root://cmseos.fnal.gov//store/user/abdollah/NN_output/${Name}_NN


END_TIME=`/bin/date`
echo "finished at ${END_TIME}"

exit $exitcode
echo "DONE!"