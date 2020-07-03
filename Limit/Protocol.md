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
  
compile:
  
    scram b
  


    
