# This short script add the autoMCStat BBB at the end of each txt file
# provide the folder at the end of the command 
ls $1/*/*.txt | while read sample
do
   echo  '* autoMCStats 0' >> $sample 
done
