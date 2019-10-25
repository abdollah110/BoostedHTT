from WMCore.Configuration import Configuration
config = Configuration()
config.section_('General')
config.General.transferOutputs = True
config.General.workArea = 'Data'
config.section_('JobType')
config.JobType.psetName = 'run_data2017_94X.py'
config.JobType.pluginName = 'Analysis'
config.JobType.outputFiles = ['ggtree_data.root']
config.JobType.inputFiles = ['Fall17_17Nov2017BCDEF_V6_DATA.db','Fall17_17Nov2017_V4_MC.db']
config.JobType.maxMemoryMB = 4000
config.JobType.sendExternalFolder = True
config.section_('Data')
config.Data.unitsPerJob = 20
config.Data.splitting = 'LumiBased'
config.Data.lumiMask = 'Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt' 
config.Data.runRange = '294927-306462'
#config.Data.outLFNDirBase = '/store/user/abdollah/Moriond18/Data/'
#config.Data.outLFNDirBase = '/store/user/abdollah/Moriond18/PreFire'
config.Data.outLFNDirBase = '/store/user/abdollah/BoostedH/An2017/Data/'
#config.Data.useParent = True
config.section_('User')
config.section_('Site')
config.Site.storageSite = 'T3_US_FNALLPC'


if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    config.General.workArea = 'Data_Boosted'

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

    config.General.requestName = "JetHT_Run2017B-31Mar2018-v1"
    config.Data.inputDataset = "/JetHT/Run2017B-31Mar2018-v1/MINIAOD"
    submit(config)

    config.General.requestName = "JetHT_Run2017C-31Mar2018-v1"
    config.Data.inputDataset = "/JetHT/Run2017C-31Mar2018-v1/MINIAOD"
    submit(config)

#    config.General.requestName ="JetHT_Run2017D-31Mar2018-v1"
#    config.Data.inputDataset = "/JetHT/Run2017D-31Mar2018-v1/MINIAOD"
#    submit(config)
 
    config.General.requestName = "JetHT_Run2017E-31Mar2018-v1"
    config.Data.inputDataset = "/JetHT/Run2017E-31Mar2018-v1/MINIAOD"
    submit(config)

    config.General.requestName = "JetHT_Run2017F-31Mar2018-v1"
    config.Data.inputDataset = "/JetHT/Run2017F-31Mar2018-v1/MINIAOD"
    submit(config)
