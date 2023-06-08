import os
import ROOT
from ROOT import *
import math


from glob import glob
from optparse import OptionParser

parser = OptionParser()
parser.add_option('--DC', '-d', action='store',
                  default='V20_pdfscale/', dest='current_DC',
                  help='path to current DC directory'
                  )
parser.add_option('--sys', '-s', action='store',
                  default='templates/PDFScaleFiles/SysedFiles/', dest='current_sys',
                  help='path to current pdf and scale sys directory'
                  )
(options, args) = parser.parse_args()



DataCardRootFiles = [ifile for ifile in glob(options.current_DC+'/*.root') if '.root' in ifile and 'pdfscaleOut.root' not in ifile]
SysRootFiles = [ifile for ifile in glob(options.current_sys+'/*pdfscale.root') if '.root' in ifile]

for inFile in DataCardRootFiles:

    print 'starting ---->>   ', inFile
    
    File=TFile(inFile,'R')
    File.Cp(File.GetName().replace('.root','_')+"pdfscaleOut.root")
    
    channel=''
    channelName=''
    year=0
    
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
        channelName = 'em2'
        channel = 'em'
    elif '_me' in inFile or    'me2' in inFile:
        channelName = 'me2'
        channel = 'em'
    elif '_mt' in inFile or 'mt2' in inFile:
        channelName = 'mt2'
        channel = 'mt'
    elif '_et' in inFile  or  'et2' in inFile:
#    elif 'et2' in inFile:
        channelName = 'et2'
        channel = 'et'
    elif '_tt' in inFile  or  'tt2' in inFile:
        channelName = 'tt2'
        channel = 'tt'
    else:
        print 'which channel ???', inFile
    print "the found channel is {} in ".format(channel,inFile)

#Output/templates/Diff_DC_lead_jet_pt_Sys_v1/me2018_NN_disc_Unblind_v1_lead_jet_pT_sys__bin3_pdfscale.root
    cat=''
    if 'bin0' in inFile: cat = '_bin0'
    elif 'bin1' in inFile: cat = '_bin1'
    elif 'bin2' in inFile: cat = '_bin2'
    elif 'bin3' in inFile: cat = '_bin3'
    elif 'bin4' in inFile: cat = '_bin4'
#    elif 'bin5' in inFile: cat = '_bin5'
    else:
        print 'which category/bin ???'
    print "the found category is {}".format(cat)

    carOrg=cat
    lastSys=0
##########################################################################################
#Add PDF and QCd Scale uncertainty Uncertainty
##########################################################################################
    process=['ZTT','TT']
    SysType=['pdf','scale']
    categories=['_ztt','_qcd','_signal']
    
#    File=TFile(inFile,'R')
    
    print 'channel is {} and years is {}'.format(channel, year)
    
    for sysFile in SysRootFiles:
    
        sysTFile=TFile(sysFile,'R')
        SysName=sysFile.rpartition('/')[-1]
        
        print 'Sys file name is ',SysName
        
        if channelName not in SysName or str(year) not in SysName or cat not in sysFile: continue
        
        for type in categories:
            cat=type+carOrg
            for pro in process:
                for sys in SysType:
                    
                    print 'hiiiii  {} {}  {}{}/{}_{}Up'.format(sysTFile, year, channel,cat,pro,sys)
                    UpSysHist=sysTFile.Get('{}{}/{}_{}Up'.format(channel,cat,pro,sys))
                    UpSysHist.SetName('{}_{}Up'.format(pro,sys))
                    DownSysHist=sysTFile.Get('{}{}/{}_{}Down'.format(channel,cat,pro,sys))
                    DownSysHist.SetName('{}_{}Down'.format(pro,sys))
                    
                    print UpSysHist.Integral(),DownSysHist.Integral()
        
        
                    newFile=TFile(File.GetName().replace('.root','_')+"pdfscaleOut.root",'UPDATE')
                    print File.GetName().replace('.root','_')+"pdfscaleOut.root", "  --<   channel+cat  ", channel+cat
                    tDirectory= newFile.Get(channel+cat)
                    tDirectory.cd()
                    tDirectory.WriteObject(UpSysHist,'{}_{}Up'.format(pro,sys))
                    tDirectory.WriteObject(DownSysHist,'{}_{}Down'.format(pro,sys))
    #                    UpSysHist.Write()
    #                    DownSysHist.Write()
                    
                    newFile.Close()
                
    #        newFile.Close()
        File.Close()
        break
