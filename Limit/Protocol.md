# Step to compute the limit/significance for boosted HTT analysis:

Checkout a version of CMSSW

    export SCRAM_ARCH=slc6_amd64_gcc530scram project 
  
    CMSSW CMSSW_9_4_5
    
    cd CMSSW_9_4_5/src
  
    cmsenv


Checkout combine limit package:

    git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
  
Checkout combine Harvester package
 
    git clone ssh://git@gitlab.cern.ch:7999/KState-HEP-HTT/CombineHarvester.git CombineHarvester
  
compile (takes some time):
  
    scram b
  
Enter to the bin directory and create a folder to store the root file:

    cd CombineHarvester/CombineTools/bin
    
    mkdir shapes
    
copy your datacard (a file with histograms for all processes) in the 'shapes' directory. Note that signal should be called as ``H125``

Cope the limit configuration file in the bin directory. Here you can find the limit configuration file.

    

    

    
