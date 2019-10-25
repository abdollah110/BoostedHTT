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
config.Data.outLFNDirBase = '/store/user/abdollah/BoostedH/An2017/SIG/'
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
    config.General.workArea = 'MC_SIG_Boost'

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



config.General.requestName = "ZHToTauTau_M125"
config.Data.inputDataset = "/ZHToTauTau_M125_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"
submit(config)

config.General.requestName = "WplusHToTauTau_M125"
config.Data.inputDataset = "/WplusHToTauTau_M125_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"
submit(config)

config.General.requestName = "WminusHToTauTau_M125"
config.Data.inputDataset = "/WminusHToTauTau_M125_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"
submit(config)

config.General.requestName = "VBFHToTauTau_M125"
config.Data.inputDataset = "/VBFHToTauTau_M125_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"
submit(config)

config.General.requestName = "GluGluHToTauTau_M125_ext"
config.Data.inputDataset = "/GluGluHToTauTau_M125_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"
submit(config)

config.General.requestName = "GluGluHToTauTau_M125"
config.Data.inputDataset = "/GluGluHToTauTau_M125_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"
submit(config)


config.General.requestName = "GluGluHToTauTau_M125_pmx_v2"
config.Data.inputDataset = "/GluGluHToTauTau_M125_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM"
submit(config)

#/VBFHToTauTau_M125_13TeV_amcatnloFXFX_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"
#
#/GluGluToHToTauTau_M125_13TeV_amcatnloFXFX_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"
