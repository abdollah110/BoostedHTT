import os
import ROOT
from ROOT import *
import math


from glob import glob
from optparse import OptionParser


def FindBinUpDown(file):

    bin=''
    type=''

    if 'Bin_1' in inFile:
        bin='Bin_1'
    elif 'Bin_2' in inFile:
        bin='Bin_2'
    elif 'Bin_3' in inFile:
        bin='Bin_3'
    elif 'Bin_4' in inFile:
        bin='Bin_4'
    else:
        print 'which bin'

    if 'Up' in name:
        type='Up'
    elif 'Down' in name:
        type='Down'
    else:
        print 'which type'
        
    return bin+type
    

parser = OptionParser()
parser.add_option('--DC', '-d', action='store',
                  default='V20_pdfscale/', dest='current_DC',
                  help='path to current DC directory'
                  )
parser.add_option('--sys', '-s', action='store',
                  default='Output/templates/PDFScaleFiles/SysedFiles/', dest='current_sys',
                  help='path to current pdf and scale sys directory'
                  )
(options, args) = parser.parse_args()



DataCardRootFiles = [ifile for ifile in glob(options.current_DC+'/*pdfscale.root') if '.root' in ifile]
SysRootFiles = [ifile for ifile in glob(options.current_sys+'/*TauIdTauIdBin*.root') if '.root' in ifile]

for inFile in DataCardRootFiles:

    print 'starting ---->>   ', inFile
    
    File=TFile(inFile,'R')
    File.Cp(File.GetName().replace('.root','_')+"TauId.root")
    
    channel=''
    channelName=''
    year=0
    bin=''
    
    if '2016' in inFile:
        year = 2016
    elif '2017' in inFile:
        year = 2017
    elif '2018' in inFile:
        year = 2018
    elif '2020' in inFile:
        year = 2020
    else:
        print 'which year ???'
    print "the found year is {}".format(year)


    if '_em' in inFile or 'em2' in inFile:
        channelName = 'em'
        channel = 'em'
    elif '_me' in inFile or    'me2' in inFile:
        channelName = 'me'
        channel = 'em'
    elif '_mt' in inFile or 'mt2' in inFile:
        channelName = 'mt'
        channel = 'mt'
    elif '_et' in inFile  or  'et2' in inFile:
        channelName = 'et'
        channel = 'et'
    elif '_tt' in inFile  or  'tt2' in inFile:
        channelName = 'tt'
        channel = 'tt'
    else:
        print 'which channel ???'
    print "the found channel is {}".format(channel)




    lastSys=0
##########################################################################################
#Add PDF and QCd Scale uncertainty Uncertainty
##########################################################################################
    process=['ZTT','TT','VV']
#    SysType=['pdf','scale']
    categories=['_ztt','_qcd','_signal']
    
#    File=TFile(inFile,'R')


#mt2018_NN_disc_2018_mttestingTauIdTauIdBin_3_Up.root
    
    print 'channel is {} and years is {}'.format(channel, year)
    
    for sysFile in SysRootFiles:
    
        type=FindBinUpDown(sysFile)
    
        sysTFile=TFile(sysFile,'R')
        SysName=sysFile.rpartition('/')[-1]
        print 'Sys file name is ',SysName
    
        print '\t\t sys file is ', sysFile
    
        if channelName not in SysName or str(year) not in SysName: continue
        
        for cat in categories:
            for pro in process:
            
#                for sys in SysType:
                    
#                print '{}{}/{}_{}Up'.format(channel,cat,pro,sys)
                UpSysHist=sysTFile.Get('{}{}/{}'.format(channel,cat,pro))
                UpSysHist.SetName('{}_{}'.format(pro,type))
#                DownSysHist=sysTFile.Get('{}{}/{}_{}Down'.format(channel,cat,pro,sys))
#                DownSysHist.SetName('{}_{}Down'.format(pro,sys))
                
#                print UpSysHist.Integral(),DownSysHist.Integral()
    
    
                newFile=TFile(File.GetName().replace('.root','_')+"tauIdOut.root",'UPDATE')
                tDirectory= newFile.Get(channel+cat)
                tDirectory.cd()
                tDirectory.WriteObject(UpSysHist,'{}_{}'.format(pro,type))
#                tDirectory.WriteObject(DownSysHist,'{}_{}Down'.format(pro,sys))
                UpSysHist.Write()
#                    DownSysHist.Write()
                
                newFile.Close()
        
#        newFile.Close()
        File.Close()
