import os
import ROOT
from ROOT import *
import math


from glob import glob
from optparse import OptionParser


def FindBinUpDown(file):

    bin=''
    type=''

    if 'Bin_1' in file:
        bin='Bin_1'
    elif 'Bin_2' in file:
        bin='Bin_2'
    elif 'Bin_3' in file:
        bin='Bin_3'
    elif 'Bin_4' in file:
        bin='Bin_4'
    else:
        print 'which bin'

    if 'Up' in file:
        type='Up'
    elif 'Down' in file:
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
parser.add_option('--name', '-n', action='store',
                  default='testZ', dest='name',
                  help='the prefix of the root files'
                  )
                  
(options, args) = parser.parse_args()



DataCardRootFiles = [ifile for ifile in glob(options.current_DC+'/*{}.root'.format(options.name)) if '.root' in ifile]
SysRootFiles = [ifile for ifile in glob(options.current_sys+'/*TauIdBin*.root') if '.root' in ifile]

for inFile in DataCardRootFiles:

    print 'starting ---->>   ', inFile
    
    File=TFile(inFile,'R')
    File.Cp(File.GetName().replace('.root','_')+"tauIdOut.root")
    
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


    ptbin=''
    if 'bin0' in inFile: ptbin = '_bin0'
    elif 'bin1' in inFile: ptbin = '_bin1'
    elif 'bin2' in inFile: ptbin = '_bin2'
    elif 'bin3' in inFile: ptbin = '_bin3'
    elif 'bin4' in inFile: ptbin = '_bin4'
#    elif 'bin5' in inFile: ptbin = '_bin5'
    else:
        print 'which ptbinegory/bin ???'
    print "the found ptbinegory is {}".format(ptbin)

    carOrg=ptbin



    lastSys=0
##########################################################################################
#Add PDF and QCd Scale uncertainty Uncertainty
##########################################################################################
    Diff="PTH"
    process=['ZTT','TT','VV',"ggH125_"+Diff+"_0_350","ggH125_"+Diff+"_350_450","ggH125_"+Diff+"_450_600","ggH125_"+Diff+"_GT600","XH125_"+Diff+"_0_350","XH125_"+Diff+"_350_450","XH125_"+Diff+"_450_600","XH125_"+Diff+"_GT600"]
#    SysType=['pdf','scale']
    categories=['_ztt','_qcd','_signal']
    
#    File=TFile(inFile,'R')
    
    print 'channel is {} and years is {}'.format(channel, year)
    
    for sysFile in SysRootFiles:
    
        type=FindBinUpDown(sysFile)
    
        sysTFile=TFile(sysFile,'R')
        SysName=sysFile.rpartition('/')[-1]
        print 'Sys file name is ',SysName
    
        print '\t\t sys file is ', sysFile
    
        if channelName not in SysName or str(year) not in SysName or carOrg not in SysName: continue
        
        for categ in categories:
            for pro in process:
            
                cat=categ+carOrg
            
#                for sys in SysType:
                    
                print '{}{}/{}'.format(channel,cat,pro)
                UpSysHist=sysTFile.Get('{}{}/{}'.format(channel,cat,pro))
                UpSysHist.SetName('{}_{}'.format(pro,type))
#                DownSysHist=sysTFile.Get('{}{}/{}_{}Down'.format(channel,cat,pro,sys))
#                DownSysHist.SetName('{}_{}Down'.format(pro,sys))
                
                print "UpSysHist.Integral() in tegral " , UpSysHist.Integral()
    
    
                newFile=TFile(File.GetName().replace('.root','_')+"tauIdOut.root",'UPDATE')
                tDirectory= newFile.Get(channel+cat)
                tDirectory.cd()
                tDirectory.WriteObject(UpSysHist,'{}_{}'.format(pro,type))
#                tDirectory.WriteObject(DownSysHist,'{}_{}Down'.format(pro,sys))
#                UpSysHist.Write()
#                    DownSysHist.Write()
                
                newFile.Close()
        
#        newFile.Close()
        File.Close()