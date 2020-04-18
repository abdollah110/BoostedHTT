#!/bin/bash
#
echo "input parameters: cluster, process, run path, out path, sample name" $1 $2 $3 $4
CLUSTER=$1
PROCESS=$2
RUNPATH=$3
OUTPATH=$4


START_TIME=`/bin/date`
echo "started at $START_TIME"


source /cvmfs/cms.cern.ch/cmsset_default.sh

echo "check whether eos is working here"
echo ${_CONDOR_SCRATCH_DIR}
cd ${_CONDOR_SCRATCH_DIR}
echo $PWD , "for job running"

setenv SCRAM_ARCH slc6_amd64_gcc530

scramv1 project CMSSW_9_4_13
cd CMSSW_9_4_13/src
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

############  Here is where the Skimmer is running     ############
# The format of the input file is similar to this
#/store/user/abdollah/BoostedH/An2017/Data/SingleMuon/crab_SingleMuon_Run2017C-31Mar2018-v1/200319_204604/0001/ggtree_data_1664.root
# To pick a proper outname for this directory we join the 4 strings after "crab_", separated by "/", together. So the outname for
# the above sample is skimed_SingleMuon_Run2017C-31Mar2018-v1_200319_204604_0001_ggtree_data_1664.root

##################### Run the skimmer
do
 ShortName=${FullDataSetName##*crab_}
 IFS="/"
 set $ShortName
 outName="skimed_"$1_$2_$3_$4
 IFS=""
 echo "input is " $FullDataSetName
 echo "output is " $outName
 ./SkimerBoost_mt  "root://cmsxrootd.fnal.gov//"$FullDataSetName $outName
done

##################### Hadd all output root files
ShortName2=${DataSetName##*crab_}
IFS="/"
set $ShortName2
FinalOutName=$1_$2_$3_$rootNumber".root"
IFS=""
echo "FinalOutName is " $FinalOutName
hadd -f $FinalOutName "skimed_"*.root

##################### Cope the output file the output directory
xrdcp -f $FinalOutName  root://cmseos.fnal.gov//OUTPUTFILE_LOCATION/$FinalOutName


END_TIME=`/bin/date`
echo "finished at ${END_TIME}"

exit $exitcode
echo "DONE!"

