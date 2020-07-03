# Step to compute the limit/significance for boosted HTT analysis:

Checkout a version of CMSSW

  export SCRAM_ARCH=slc6_amd64_gcc530scram project 
  CMSSW CMSSW_9_4_5cd CMSSW_9_4_5/src
  cmsenv


Checkout combine limit package:

  git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
  
 Checkout combine Harvester package
 
   git clone ssh://git@gitlab.cern.ch:7999/KState-HEP-HTT/CombineHarvester.git CombineHarvester
  
  compile:
  
    scram b
  

    
Location of the ggNtuples, Skimmed Ntuples, SVFItted Ntuples:

    https://docs.google.com/spreadsheets/d/1ItBdYFDzD3MIzFWVVi26t-2UuBNxgKjGL73h9cWGA0s/edit#gid=0
