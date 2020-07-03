# Steps to setup limit package 

Checkout a version of CMSSW

    export SCRAM_ARCH=slc6_amd64_gcc530scram project 
  
    CMSSW CMSSW_9_4_5
    
    cd CMSSW_9_4_5/src
  
    cmsenv


Checkout combine limit package:

    git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
  
Checkout combine Harvester package
 
    git clone ssh://git@gitlab.cern.ch:7999/KState-HEP-HTT/CombineHarvester.git CombineHarvester
  
There seems to be a buggy file in this version. first remove the file and then compile
    
    rm CombineHarvester/CombineTools/bin/LimitCompare.cpp
    
compile (takes some time):
  
    scram b -j 8
  
Enter to the bin directory and create a folder to store the root file:

    cd CombineHarvester/CombineTools/bin
    
    mkdir shapes
    
copy your datacard (a file with histograms for all processes) in the ``shapes`` directory. Note that signal should be called as ``H125``. Change the name of the root file to ``template_boostedH.root``


[Important: check that naming convention in your root file is compatible with the example committed to the github:]

Copy the limit configuration file to the bin directory. Here you can find the limit configuration file.

    https://github.com/abdollah110/BoostedHTT/blob/boost/Limit/BoostedTau_limit.cpp
    
Update the ``BuildFile.xml`` by adding the following line:

    <bin file="BoostedTau_limit.cpp" name="BoostedTau_limit"></bin>

Then complie (note whenever you change something in BoostedTau_limit.cpp you have to complie). This creates an executable for you:

    cd ..
    scram b -j 8
    cd -
    
# Step to compute the limit/significance for boosted HTT analysis:
    
The first step is to create a datacard from your root file:

    BoostedTau_limit
    
This creates a datacard structure in the following directory ``outputBoostedHTT_v2/V2_mt_sys``. Change the directory whenever you run a new limit. The best is that to pass this as an argument (todo list). 

Then you need to add a line to the datacrd to include bin-by-bin uncertainty (``add_auto_MC_Stat.sh`` can be found in the github):

    sh add_auto_MC_Stat.sh outputBoostedHTT_v2/V2_mt_sys/
     
Also try to enter the created directory and explore files inside there.
    
    cd outputBoostedHTT_v2/V2_mt_sys/125
    
creating a workspace from the datacard:

    text2workspace.py H_mt_1_13TeV.txt -o ws.root -m 125
    
compute the expected limit:

    combineTool.py -M AsymptoticLimits -d ws.root -m 125 -t -1
    
The limit values will be prointed for you as the following:

     -- AsymptoticLimits ( CLs ) --
    Observed Limit: r < 1.9226
    Expected  2.5%: r < 0.9985
    Expected 16.0%: r < 1.3520
    Expected 50.0%: r < 1.9219
    Expected 84.0%: r < 2.7722
    Expected 97.5%: r < 3.8642


    
    

        
    
