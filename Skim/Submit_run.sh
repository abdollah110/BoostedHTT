#!/bin/bash
#
echo "input parameters: cluster, process, run path, out path, sample name" $1 $2 $3 $4
CLUSTER=$1
PROCESS=$2
RUNPATH=$3
OUTPATH=$4


#########For running locally uncommnet this line
#CLUSTER=""
#PROCESS=5
#RUNPATH=""
#OUTPATH=""


echo ""
echo "CMSSW on Condor"
echo ""

START_TIME=`/bin/date`
echo "started at $START_TIME"

echo ""
echo "parameter set:"
echo "CLUSTER: $CLUSTER"
echo "PROCESS: $PROCESS"
echo "RUNPATH: $RUNPATH"
echo "OUTPATH: $OUTPATH"

source /cvmfs/cms.cern.ch/cmsset_default.sh

echo "check whether eos is working here"
echo ${_CONDOR_SCRATCH_DIR}
cd ${_CONDOR_SCRATCH_DIR}
echo $PWD , "for job running"

setenv SCRAM_ARCH slc6_amd64_gcc530

xrdcp root://cmseos.fnal.gov//store/user/abdollah/CMSSW_9_4_13.tar.gz   .
tar -xf CMSSW_9_4_13.tar.gz
rm CMSSW_9_4_13.tar.gz
cd CMSSW_9_4_13/src/BoostedHTT/Skim/
scramv1 b ProjectRename
eval `scramv1 runtime -sh` 
ls
########### complie the Skimmer
make

#########  Smaple/Job splitting
SplitingNumber=10
DataSetArray=($(cat InputSamples.txt)) # array of the input datadets
echo ${DataSetArray[$PROCESS / $SplitingNumber]}
DataSetName=${DataSetArray[$PROCESS / $SplitingNumber]}
rootNumber=$(($PROCESS % $SplitingNumber))
#DataSetName=DataSetName_.replace("/store/user/abdollah/Moriond18/","")

########### loop over all root file in a dataset directory
xrdfs root://cmseos.fnal.gov ls $DataSetName | grep $rootNumber.root | while read FullDataSetName

############  Here is where the Skimmer is running     ############
do
 ShortName=${FullDataSetName##*crab_}
 IFS="/"
 set $ShortName
 outName="skimed_"$1_$2_$3_$4
 IFS=""

 echo "input is " $FullDataSetName
 echo "output is " $outName

 ./SkimerBoost  $FullDataSetName $outName
done
############  Here is where the Skimmer ends          ############

ShortName2=${DataSetName##*crab_}
IFS="/"
set $ShortName2
FinalOutName=$1_$2_$3_$rootNumber".root"
IFS=""

echo "FinalOutName is " $FinalOutName
hadd -f $FinalOutName "skimed_"*.root


##########  remove the unneccesat files
#rm skim*root  Skimmer.cc  Skimmer.h  Makefile  InputSamples.txt
echo "Done execution ..."
xrdcp -f $FinalOutName  root://cmseos.fnal.gov//store/user/abdollah/boostggNtuple/testtest2/$FinalOutName
xrdcp *.stdout *.stderr *.condor  root://cmseos.fnal.gov//store/user/abdollah/CONDOR/


END_TIME=`/bin/date`
echo "finished at ${END_TIME}"

exit $exitcode
echo "DONE!"

