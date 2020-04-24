#!/bin/bash
#
echo "input parameters: cluster, process, run path, out path, sample name" $1 $2 $3 $4
CLUSTER=$1
PROCESS=$2
RUNPATH=$3
OUTPATH=$4

echo "PROCESS: $PROCESS"

source /cvmfs/cms.cern.ch/cmsset_default.sh
setenv SCRAM_ARCH slc6_amd64_gcc630
scramv1 project CMSSW_9_4_13
cd CMSSW_9_4_13/src
xrdcp root://cmseos.fnal.gov//store/user/abdollah/TarFile.tar.gz   .
tar -xf TarFile.tar.gz
rm TarFile.tar.gz
cd TarFile
cp *.so ../../lib/*/.
eval `scramv1 runtime -sh`
chmod a+x FastMTT
ls

############  Here is where the Skimmer is running     ############
#find the nth line of the InputSamples_sv.txt where n is the PROCESS number
# more info here \https://unix.stackexchange.com/questions/147560/explain-this-bash-script-echo-1
FullSampleName=`sed -n "$((PROCESS+1))p"  < InputSamples_sv.txt`
ShortName=${FullSampleName##*/}

outName="svfited_"$ShortName
input="root://cmseos.fnal.gov/"$FullSampleName

echo "  input is " $input
echo "  output is " $outName

./FastMTT doES=-1 metType=-1 inputfile=$input newFile=$outName

xrdcp -f $outName  root://cmseos.fnal.gov//OUTPUTFILE_LOCATION/$outName
xrdcp *.stdout *.stderr *.condor  root://cmseos.fnal.gov//store/user/abdollah/CONDOR/


END_TIME=`/bin/date`
echo "finished at ${END_TIME}"

exit $exitcode
echo "DONE!"
