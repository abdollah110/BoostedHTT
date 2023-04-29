import ROOT
from ROOT import *

import re
from array import array
from optparse import OptionParser
import sys

#parser = OptionParser()
import argparse
parser = argparse.ArgumentParser("Compare total template to stage 1.1 templates")
parser.add_argument(
        "-i",
        "--inputfile",
        action="store",
        dest="inputfile",
        default="X.root",
        help="Which file1name to run over?")
parser.add_argument(
        "-o",
        "--outputfile",
        action="store",
        dest="outputfile",
        default="Y.root",
        help="Which file1name to run over?")
parser.add_argument(
        "-d",
        "--diff",
        action="store",
        dest="diff",
        default="PTH",
        help="Is that PYH or PTJ")
args = parser.parse_args()

inputfile =args.inputfile
outputfile=args.outputfile
Diff=args.diff


inputfile =args.inputfile
outputfile=args.outputfile

file=ROOT.TFile(inputfile,"r")
file.cd()
dirList = gDirectory.GetListOfKeys()



year=0
if '2016' in inputfile:
    year = 2016
elif '2017' in inputfile:
    year = 2017
elif '2018' in inputfile:
    year = 2018
else:
    print 'which year ???'


def numBin(hist):
    return hist.GetNbinsX()



ofile=ROOT.TFile(outputfile,"recreate")
categories_list= file.GetListOfKeys()
categories=[]
for k2 in categories_list:
	categories.append(k2.GetName())
#    print 'k2.GetName() ', k2.GetName()
ncat=len(categories)
for k1 in dirList: # loop over categories
    print 'hi ', k1

    names_histos_used=[]

    h1 = k1.ReadObj()
    nom=k1.GetName()

    channel=''
    treeName=''
    executable=''
    categ=''

    if 'em_' in nom:
        channel = 'em'
        treeName = 'emu_tree'
        executable = 'process_trees_em'
    elif 'me_' in nom:
        channel = 'me'
        treeName = 'mue_tree'
        executable = 'process_trees_em'
    elif 'mt_' in nom:
        channel = 'mt'
        treeName = 'mutau_tree'
    #    executable = 'process_trees_lt'
        executable = 'process_trees_lt_fr'
    #    executable = 'process_trees_sf_fr'
    elif 'et_' in nom:
        channel = 'et'
        treeName = 'etau_tree'
    #    executable = 'process_trees_lt'
        executable = 'process_trees_lt_fr'
    elif 'tt_' in nom:
        channel = 'tt'
        treeName = 'tautau_tree'
        executable = 'process_trees_tt'
    else:
        print 'which channel ???'


    if 'qcd' in nom:
        type = '_qcd'
    elif 'ztt' in nom:
        type = '_ztt'
    elif 'signal' in nom:
        type = '_signal'


#    categ=nom.replace(channel+'_','').replace('nal','')
#    print 'categ is', categ
    
#
    if '_qcd_' in nom:
        categ='qcd'
    elif '_ztt_' in nom:
        categ='ztt'
    elif '_signal_' in nom:
        categ='signal'
    else:
        print 'which category  ???'
        
    print 'year is {} and channel is {} and categ is {}'.format(year,channel,categ)

#    ofile.mkdir(nom.replace('_0jet',''))
    Updatednom=nom.replace('_0jet','')
    binName=''
    
    if '_bin1' in Updatednom: Updatednom='Htt_{}_0_350_cat{}{}{}'.format(Diff,year,channel,type); binName='bin1'
    if '_bin2' in Updatednom: Updatednom='Htt_{}_350_450_cat{}{}{}'.format(Diff,year,channel,type); binName='bin2'
    if '_bin3' in Updatednom: Updatednom='Htt_{}_450_600_cat{}{}{}'.format(Diff,year,channel,type); binName='bin3'
    if '_bin4' in Updatednom: Updatednom='Htt_{}_GT600_cat{}{}{}'.format(Diff,year,channel,type); binName='bin4'
    
    
    ofile.mkdir(Updatednom)
    h1.cd()
    histoList = gDirectory.GetListOfKeys()
    name_last=""
    N_histo=0



    for histo in histoList:
    
        
        h1.cd()
        h2 = histo.ReadObj()
#        print 'number of bins   ', numBin(h2)
        h3=h2.Clone()
        if numBin(h2)==14:
            newhis=TH1F(h2.GetName(),h2.GetName(),13,0.35,1.0)
            for i in range(numBin(h2)):
                newhis.SetBinContent(i,h2.GetBinContent(i+1))
                newhis.SetBinError(i,h2.GetBinError(i+1))
            h3=newhis.Clone()
        histo_name=h2.GetName()
        
#        NonZeroIntegralHist=h2.Clone()
####################################################################################
############        Here we fix the issue with shape uncertainty up and down once one is zero and the other is non-zero, as this causes an issue in the fit
####################################################################################
        if h3.Integral()==0:
        
            downName=''
            if 'Up' in h3.GetName(): downName=h3.GetName().replace('Up','Down')
            if 'Down' in h3.GetName(): downName=h3.GetName().replace('Down','Up')
            
            for down in histoList:
    #            if 'Up' not in h3.GetName() or 'Down' not in h3.GetName() : continue
                if down.GetName() !=downName : continue
                if h3.Integral()==0 and down.ReadObj().Integral() ==0: continue
                if h3.Integral()!=0 and down.ReadObj().Integral() !=0: continue
                print '=========>>>>   zero integral     <<<<<========== ', h3.GetName(),down.GetName(), h3.Integral(), down.ReadObj().Integral()
                replacement=down.ReadObj()
                h3=replacement
                print 'new integral is ', h3.Integral()



        elif h3.Integral() < 0.000001 :
            print '========88888888=>>>>   small integral     <<<<<=====88888888===== ', h3.Integral()
            downName=''
            if 'Up' in h3.GetName(): downName=h3.GetName().replace('Up','Down')
            if 'Down' in h3.GetName(): downName=h3.GetName().replace('Down','Up')
            
            for down in histoList:
    #            if 'Up' not in h3.GetName() or 'Down' not in h3.GetName() : continue
                if down.GetName() !=downName : continue
                if h3.Integral()< 0.000001 and down.ReadObj().Integral() < 0.000001: continue
                if h3.Integral()> 0.000001 and down.ReadObj().Integral() > 0.000001: continue
                print '========88888888=>>>>   small integral     <<<<<=====88888888===== ', h3.GetName(),down.GetName(), h3.Integral(), down.ReadObj().Integral()
                replacement=down.ReadObj()
                h3=replacement
                print 'new integral is ', h3.Integral()




####################################################################################


        if (h2.GetName()==name_last):
            continue
        name_last=histo_name

#        %%%%%%%%%%%%%%%%%%
#           Tau energy scale
#        %%%%%%%%%%%%%%%%%%

#        histo_name=histo_name.replace('TES','CMS_scale_t_')
        histo_name=histo_name.replace('TESDown_1prong1pizero','CMS_scale_t_1prong1pizeroDown')
        histo_name=histo_name.replace('TESDown_1prong','CMS_scale_t_1prongDown')
        histo_name=histo_name.replace('TESDown_3prong','CMS_scale_t_3prongDown')
        histo_name=histo_name.replace('TESUp_1prong1pizero','CMS_scale_t_1prong1pizeroUp')
        histo_name=histo_name.replace('TESUp_1prong','CMS_scale_t_1prongUp')
        histo_name=histo_name.replace('TESUp_3prong','CMS_scale_t_3prongUp')

#        histo_name=histo_name.replace('JEnTot','CMS_scale_j_cat{}'.format(categ))
        histo_name=histo_name.replace('JEnTot','CMS_scale_j')
#        histo_name=histo_name.replace('MissingEn_UES','CMS_scale_met_unclustered_cat{}'.format(categ))
        histo_name=histo_name.replace('MissingEn_UES','CMS_scale_met_unclustered')
        histo_name=histo_name.replace('ttbarShape_','CMS_ttbarShape')
        histo_name=histo_name.replace('trig_tt','CMS_trig_tt')
        histo_name=histo_name.replace('CMS_JER','CMS_res_j')
#        histo_name=histo_name.replace('shapeYEAR_','CMS_QCD_bkg_modeling')
        histo_name=histo_name.replace('fakerateYEAR_','CMS_QCD_bkg_fakerate')
        histo_name=histo_name.replace('scaleUp','QCDScaleUp')
        histo_name=histo_name.replace('scaleDown','QCDScaleDown')




        if channel=='em' or channel=='me': histo_name=histo_name.replace('shapeYEAR_','CMS_QCD_bkg_modeling_em_cat{}'.format(categ))#// for correlating these uncertainties across categories FIXME
        if channel=='et' : histo_name=histo_name.replace('shapeYEAR_','CMS_QCD_bkg_modeling_et_cat{}'.format(categ))
        if channel=='mt':  histo_name=histo_name.replace('shapeYEAR_','CMS_QCD_bkg_modeling_mt_cat{}'.format(categ))
        if channel=='tt'                 : histo_name=histo_name.replace('shapeYEAR_','CMS_QCD_bkg_modeling_tt_cat{}'.format(categ))

#        if channel=='em' or channel=='me': histo_name=histo_name.replace('shapeYEAR_','CMS_QCD_bkg_modeling_em')
#        if channel=='et' : histo_name=histo_name.replace('shapeYEAR_','CMS_QCD_bkg_modeling_et')
#        if channel=='mt':  histo_name=histo_name.replace('shapeYEAR_','CMS_QCD_bkg_modeling_mt')
#        if channel=='tt'                 : histo_name=histo_name.replace('shapeYEAR_','CMS_QCD_bkg_modeling_tt')

        if 'THU' not in histo_name and 'pdf' not in histo_name and 'QCDScale' not in histo_name: histo_name=histo_name.replace('Up',str(year)+'Up')
        if 'THU' not in histo_name and 'pdf' not in histo_name and 'QCDScale' not in histo_name: histo_name=histo_name.replace('Down',str(year)+'Down')
        
        if 'ZTT' not in histo_name: histo_name=histo_name.replace('TT_pdf','TT_TTpdf'+str(year))
        histo_name=histo_name.replace('ZTT_pdf','ZTT_ZTTpdf'+str(year))

        if 'ZTT' not in histo_name: histo_name=histo_name.replace('TT_QCDScale','TT_TTQCDScale_cat{}'.format(categ)+str(year)) #// for correlating these uncertainties across categories FIXME
        histo_name=histo_name.replace('ZTT_QCDScale','ZTT_ZTTQCDScale_cat{}'.format(categ)+str(year))
#        if 'ZTT' not in histo_name: histo_name=histo_name.replace('TT_QCDScale','TT_TTQCDScale'+str(year))
#        histo_name=histo_name.replace('ZTT_QCDScale','ZTT_ZTTQCDScale'+str(year))

        histo_name=histo_name.replace('prefire2016','CMS_prefiring')
        histo_name=histo_name.replace('prefire2017','CMS_prefiring')
        histo_name=histo_name.replace('prefire2018','CMS_prefiring')
        
        histo_name=histo_name.replace('Up125','Up')
        histo_name=histo_name.replace('Down125','Down')
        
    
        
        histo_name=histo_name.replace('_0_350','_0_350125')
        histo_name=histo_name.replace('_350_450','_350_450125')
        histo_name=histo_name.replace('_450_600','_450_600125')
        histo_name=histo_name.replace('_GT600','_GT600125')
        histo_name=histo_name.replace('_0_450','_0_450125')

        histo_name=histo_name.replace('XH125','XH')
        histo_name=histo_name.replace('ggH125','ggH')
#        histo_name=histo_name.replace('OutsideAcceptance','OutsideAcceptance125')

        if 'PTJ' in Diff: histo_name=histo_name.replace('PTH','PTJ')

#        if 'THU' in histo_name: histo_name=histo_name.replace('Up',binName+'Up')
#        if 'THU' in histo_name: histo_name=histo_name.replace('Down',binName+'Down')
        
#        histo_name=histo_name.replace('2016','2020')
#        histo_name=histo_name.replace('2017','2020')
#        histo_name=histo_name.replace('2018','2020')

#        h3.Rebin(2)
        
        ofile.cd(Updatednom)
        h3.Write(histo_name)
