#!/bin/bash
#
echo "input parameters: cluster, process, run path, out path, sample name" $1 $2 $3 $4
CLUSTER=$1
PROCESS=$2
RUNPATH=$3
OUTPATH=$4

echo "PROCESS: $PROCESS"

START_TIME=`/bin/date`
echo "started at $START_TIME"

############  set the enviroment and copy the neccessary files
source /cvmfs/cms.cern.ch/cmsset_default.sh
echo "check whether eos is working here"
echo ${_CONDOR_SCRATCH_DIR}
cd ${_CONDOR_SCRATCH_DIR}
echo $PWD , "for job running"
setenv SCRAM_ARCH slc6_amd64_gcc530
scramv1 project CMSSW_10_2_22
cd CMSSW_10_2_22/src
xrdcp root://cmseos.fnal.gov//store/user/abdollah/TarFile.tar.gz   .
tar -xf TarFile.tar.gz
rm TarFile.tar.gz
cd TarFile
eval `scramv1 runtime -sh`
chmod a+x SkimerBoost_mt
ls

#########  Smaple/Job splitting
SplitingNumber=10
DataSetArray=($(cat InputSamples.txt)) # array of the input datadets
echo ${DataSetArray[$PROCESS / $SplitingNumber]}
DataSetName=${DataSetArray[$PROCESS / $SplitingNumber]}
rootNumber=$(($PROCESS % $SplitingNumber))

########### loop over all root file in a dataset directory
xrdfs root://cmseos.fnal.gov ls $DataSetName | grep $rootNumber.root | while read FullDataSetName

##################### Run the skimmer
do
 ShortName=${FullDataSetName##*crab_}
 outName="skimed_"`tr '/' '_' <<<"$ShortName"`
 
 echo "input is " $FullDataSetName
 echo "output is " $outName
 
 ./SkimerBoost_mt  "root://cmsxrootd.fnal.gov//"$FullDataSetName $outName
done

##################### Hadd all output root files
ShortName2=${DataSetName##*crab_}
FinalOutName=`tr '/' '_' <<<"$ShortName2"`_$rootNumber".root"

echo "FinalOutName is " $FinalOutName
hadd -f $FinalOutName "skimed_"*.root

##################### Cope the output file the output directory
xrdcp -f $FinalOutName  root://cmseos.fnal.gov//OUTPUTFILE_LOCATION/$FinalOutName


END_TIME=`/bin/date`
echo "finished at ${END_TIME}"

exit $exitcode
echo "DONE!"

