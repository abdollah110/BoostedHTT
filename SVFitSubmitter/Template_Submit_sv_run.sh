#!/bin/bash
#
echo "input parameters: cluster, process, run path, out path, sample name" $1 $2 $3 $4
CLUSTER=$1
PROCESS=$2
RUNPATH=$3
OUTPATH=$4

source /cvmfs/cms.cern.ch/cmsset_default.sh


echo "PROCESS: $PROCESS"

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

#
#
#xrdcp root://cmseos.fnal.gov//store/user/abdollah/CMSSW_9_4_4.tar.gz   .
#tar -xf CMSSW_9_4_4.tar.gz
#rm CMSSW_9_4_4.tar.gz
#cd CMSSW_9_4_4/src/SubmitSVFit/skim
#scramv1 b ProjectRename
#eval `scramv1 runtime -sh`
#ls
#

echo "this is the process number " $PROCESS

############  Here is where the Skimmer is running     ############

sed -n "${PROCESS}p"  < InputSamples_sv.txt > out.out
FullDataSetName=$(head -n 1 out.out)

# more info here \https://unix.stackexchange.com/questions/147560/explain-this-bash-script-echo-1
ShortName=${FullDataSetName##*/}

outName="svfited_"$ShortName
input="root://cmseos.fnal.gov/"$FullDataSetName

echo "  input is " $input
echo "  output is " $outName

./FastMTT doES=-1 metType=-1 inputfile=$input newFile=$outName

xrdcp -f $outName  root://cmseos.fnal.gov//OUTPUTFILE_LOCATION/$outName
xrdcp *.stdout *.stderr *.condor  root://cmseos.fnal.gov//store/user/abdollah/CONDOR/


END_TIME=`/bin/date`
echo "finished at ${END_TIME}"

exit $exitcode
echo "DONE!"
