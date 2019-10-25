from WMCore.Configuration import Configuration
config = Configuration()
config.section_('General')
config.General.transferOutputs = True
config.General.workArea = 'MC_BG'
config.section_('JobType')
config.JobType.psetName = 'run_mc2017_94X.py'
config.JobType.pluginName = 'Analysis'
config.JobType.outputFiles = ['ggtree_mc.root']
config.JobType.inputFiles = ['Fall17_17Nov2017BCDEF_V6_DATA.db','Fall17_17Nov2017_V6_MC.db']
config.JobType.maxMemoryMB = 2500
config.JobType.sendExternalFolder = True
config.section_('Data')
config.Data.unitsPerJob = 2
#config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.outLFNDirBase = '/store/user/abdollah/BoostedH/An2017/MC/'
config.Data.allowNonValidInputDataset = True
config.section_('User')
config.section_('Site')
config.Site.storageSite = 'T3_US_FNALLPC'


if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    config.General.workArea = 'MC_BG_Boost'

    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException as hte:
            print "Failed submitting task: %s" % (hte.headers)
        except ClientException as cle:
            print "Failed submitting task: %s" % (cle)

    #############################################################################################
    ## From now on that's what users should modify: this is the a-la-CRAB2 configuration part. ##
    #############################################################################################








##### W samples

#config.General.requestName = "WJetsToLNu_Inc"
#config.Data.inputDataset = "/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"
#submit(config)
#
#config.General.requestName = "WJetsToLNu_Inc_ext"
#config.Data.inputDataset = "/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2/MINIAODSIM"
#submit(config)
#
#config.General.requestName = "WJetsToLNu_HT-100To200"
#config.Data.inputDataset = "/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"
#submit(config)
#
#config.General.requestName = "WJetsToLNu_HT-200To400"
#config.Data.inputDataset = "/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"
#submit(config)
#
#config.General.requestName = "WJetsToLNu_HT-400To600"
#config.Data.inputDataset = "/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"
#submit(config)

config.General.requestName = "WJetsToLNu_HT-600To800"
config.Data.inputDataset = "/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"
submit(config)

config.General.requestName = "WJetsToLNu_HT-800To1200"
config.Data.inputDataset = "/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"
submit(config)

#config.General.requestName = "WJetsToLNu_HT-1200To2500"
#config.Data.inputDataset = "/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"
#submit(config)
#
#config.General.requestName = "WJetsToLNu_HT-2500ToInf"
#config.Data.inputDataset = "/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3/MINIAODSIM"
#submit(config)


##### DY Samples


#
#config.General.requestName = "DYJetsToLL_M-50_v1"
#config.Data.inputDataset = "/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"
#submit(config)
#
#config.General.requestName = "DYJetsToLL_M-50_v1_ext1"
#config.Data.inputDataset = "/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"
#submit(config)
#
#
#config.General.requestName = "DYJetsToLL_M-50_HT-100to200"
#config.Data.inputDataset = "/DYJetsToLL_M-50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"
#submit(config)
#
#
#config.General.requestName = "DYJetsToLL_M-50_HT-100to200_ext"
#config.Data.inputDataset = "/DYJetsToLL_M-50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"
#submit(config)
#
#
#
#config.General.requestName = "DYJetsToLL_M-50_HT-200to400_v1"
#config.Data.inputDataset = "/DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"
#submit(config)
#
#config.General.requestName = "DYJetsToLL_M-50_HT-200to400_v2"
#config.Data.inputDataset = "/DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"
#submit(config)
#
#config.General.requestName = "DYJetsToLL_M-50_HT-200to400_ext"
#config.Data.inputDataset = "/DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"
#submit(config)
#
#
#config.General.requestName = "DYJetsToLL_M-50_HT-400to600"
#config.Data.inputDataset = "/DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"
#submit(config)
#
#config.General.requestName = "DYJetsToLL_M-50_HT-400to600_v2"
#config.Data.inputDataset = "/DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM"
#submit(config)
#
#config.General.requestName = "DYJetsToLL_M-50_HT-600to800_v1"
#config.Data.inputDataset = "/DYJetsToLL_M-50_HT-600to800_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"
#submit(config)
#
#config.General.requestName = "DYJetsToLL_M-50_HT-600to800_v2"
#config.Data.inputDataset = "/DYJetsToLL_M-50_HT-600to800_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM"
#submit(config)
#
#
#config.General.requestName = "DYJetsToLL_M-50_HT-800to1200"
#config.Data.inputDataset = "/DYJetsToLL_M-50_HT-800to1200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"
#submit(config)
#
#config.General.requestName = "DYJetsToLL_M-50_HT-1200to2500"
#config.Data.inputDataset = "/DYJetsToLL_M-50_HT-1200to2500_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"
#submit(config)
#
#config.General.requestName = "DYJetsToLL_M-50_HT-2500toInf"
#config.Data.inputDataset = "/DYJetsToLL_M-50_HT-2500toInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM"
#submit(config)
#


## Diboson



#config.General.requestName = "WZTo2L2Q_13TeV_amcatnloFXFX_madspin"
#config.Data.inputDataset = "/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1/MINIAODSIM"
#submit(config)



config.General.requestName = "WZTo1L3Nu_13TeV_amcatnloFXFX"
config.Data.inputDataset ="/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_v2/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"
submit(config)



#config.General.requestName = "WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin"
#config.Data.inputDataset = "/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"
#submit(config)

#config.General.requestName = "WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX"
#config.Data.inputDataset = "/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"
#submit(config)


## WW

config.General.requestName = "WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin"
config.Data.inputDataset = "/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"
submit(config)

#config.General.requestName = "WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg"
#config.Data.inputDataset = "/WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"
#submit(config)

config.General.requestName = "WWTo4Q_NNPDF31_TuneCP5_13TeV-powheg"
config.Data.inputDataset = "/WWTo4Q_NNPDF31_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"
submit(config)

#config.General.requestName = "WWToLNuQQ_NNPDF31_TuneCP5_13TeV-powheg"
#config.Data.inputDataset = "/WWToLNuQQ_NNPDF31_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"
#submit(config)
#
config.General.requestName = "WWToLNuQQ_NNPDF31_TuneCP5_13TeV-powheg_ext"
config.Data.inputDataset = "/WWToLNuQQ_NNPDF31_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10_ext1-v1/MINIAODSIM"
submit(config)



## ZZ

#config.General.requestName = "ZZTo4L_13TeV_powheg_v2"
#config.Data.inputDataset = "/ZZTo4L_13TeV_powheg_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"
#submit(config)

#config.General.requestName = "ZZTo2L2Q_13TeV_amcatnloFXFX_madspin"
#config.Data.inputDataset = "/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1/MINIAODSIM"
#submit(config)

#config.General.requestName = "ZZTo2L2Nu_13TeV_powheg"
#config.Data.inputDataset = "/ZZTo2L2Nu_13TeV_powheg_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"
#submit(config)

#config.General.requestName = "ZZTo4L_13TeV_powheg_v1"
#config.Data.inputDataset = "/ZZTo4L_13TeV_powheg_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"
#submit(config)

#config.General.requestName = "ZZTo4L_13TeV_powheg_ext"
#config.Data.inputDataset = "/ZZTo4L_13TeV_powheg_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10_ext1-v1/MINIAODSIM"
#submit(config)


## TT


config.General.requestName = "TTToHadronic"
config.Data.inputDataset = "/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"
submit(config)

config.General.requestName = "TTToSemiLeptonic"
config.Data.inputDataset = "/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"
submit(config)

config.General.requestName = "TTTo2L2Nu"
config.Data.inputDataset = "/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"
submit(config)



## SIingle Top

#
#config.General.requestName = "ST_s-channel_4f_leptonDecays"
#config.Data.inputDataset = "/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"
#submit(config)
#
#
#
#config.General.requestName = "ST_s-channel_4f_leptonDecays"
#config.Data.inputDataset = "/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"
#submit(config)
#
#config.General.requestName = "ST_t-channel_antitop_4f_inclusiveDecays"
#config.Data.inputDataset = "/ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"
#submit(config)
#
#
#config.General.requestName = "ST_t-channel_top_4f_inclusiveDecays"
#config.Data.inputDataset = "/ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"
#submit(config)
#
#config.General.requestName = "ST_tW_antitop_5f_inclusiveDecays"
#config.Data.inputDataset = "/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"
#submit(config)
#
#config.General.requestName = "ST_tW_top_5f_inclusiveDecays"
#config.Data.inputDataset = "/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"
#submit(config)
#

