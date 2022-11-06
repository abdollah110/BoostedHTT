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
args = parser.parse_args()

inputfile =args.inputfile
outputfile=args.outputfile

file=ROOT.TFile(inputfile,"r")
file.cd()
dirList = gDirectory.GetListOfKeys()






ofile=ROOT.TFile(outputfile,"recreate")
categories_list= file.GetListOfKeys()
categories=[]
for k2 in categories_list:
	categories.append(k2.GetName())
#    print 'k2.GetName() ', k2.GetName()
ncat=len(categories)
year=0
channel=''
for KKK in dirList: # loop over categories


    k1=KKK.GetName()
    
    if '2016' in k1:
        year = 2016
    elif '2017' in k1:
        year = 2017
    elif '2018' in k1:
        year = 2018
    else:
        print 'which year ???'


    if 'em' in k1:
        channel = 'em'
        treeName = 'emu_tree'
        executable = 'process_trees_em'
    elif 'me' in k1:
        channel = 'me'
        treeName = 'mue_tree'
        executable = 'process_trees_em'
    elif 'mt' in k1:
        channel = 'mt'
        treeName = 'mutau_tree'
    #    executable = 'process_trees_lt'
        executable = 'process_trees_lt_fr'
    #    executable = 'process_trees_sf_fr'
    elif 'et' in k1:
        channel = 'et'
        treeName = 'etau_tree'
    #    executable = 'process_trees_lt'
        executable = 'process_trees_lt_fr'
    elif 'tt' in k1:
        channel = 'tt'
        treeName = 'tautau_tree'
        executable = 'process_trees_tt'
    else:
        print 'which channel ???'


    print 'hi ', k1, year,channel
    
    
    
#
#    names_histos_used=[]
#
#    h1 = k1.ReadObj()
#    nom=k1.GetName()
#
#    channel=''
#    treeName=''
#    executable=''
#
#

#
#    print 'year is {} and channel is {}'.format(year,channel)
#
#
#
##    ofile.mkdir(nom.replace('_0jet',''))
#    Updatednom=nom.replace('_0jet','')
#
#    if '_bin1' in Updatednom: Updatednom='Htt_PTH_0_350_cat{}{}'.format(year,channel)
#    if '_bin2' in Updatednom: Updatednom='Htt_PTH_350_450_cat{}{}'.format(year,channel)
#    if '_bin3' in Updatednom: Updatednom='Htt_PTH_450_600_cat{}{}'.format(year,channel)
#    if '_bin4' in Updatednom: Updatednom='Htt_PTH_600_800_cat{}{}'.format(year,channel)
#    if '_bin5' in Updatednom: Updatednom='Htt_PTH_GT800_cat{}{}'.format(year,channel)
#
#    ofile.mkdir(Updatednom)
#    h1.cd()
#    histoList = gDirectory.GetListOfKeys()
#    name_last=""
#    N_histo=0
#
#
#
#    for histo in histoList:
#        h1.cd()
#        h2 = histo.ReadObj()
#        h3=h2.Clone()
#        histo_name=h2.GetName()
#
##        NonZeroIntegralHist=h2.Clone()
#####################################################################################
#############        Here we fix the issue with shape uncertainty up and down once one is zero and the other is non-zero, as this causes an issue in the fit
#####################################################################################
#        if h3.Integral()==0:
#
#            downName=''
#            if 'Up' in h3.GetName(): downName=h3.GetName().replace('Up','Down')
#            if 'Down' in h3.GetName(): downName=h3.GetName().replace('Down','Up')
#
#            for down in histoList:
#    #            if 'Up' not in h3.GetName() or 'Down' not in h3.GetName() : continue
#                if down.GetName() !=downName : continue
#                if h3.Integral()==0 and down.ReadObj().Integral() ==0: continue
#                if h3.Integral()!=0 and down.ReadObj().Integral() !=0: continue
#                print '=========>>>>   zero integral     <<<<<========== ', h3.GetName(),down.GetName(), h3.Integral(), down.ReadObj().Integral()
#                replacement=down.ReadObj()
#                h3=replacement
#                print 'new integral is ', h3.Integral()
#
#
#
#        elif h3.Integral() < 0.000001 :
#            print '========88888888=>>>>   small integral     <<<<<=====88888888===== ', h3.Integral()
#            downName=''
#            if 'Up' in h3.GetName(): downName=h3.GetName().replace('Up','Down')
#            if 'Down' in h3.GetName(): downName=h3.GetName().replace('Down','Up')
#
#            for down in histoList:
#    #            if 'Up' not in h3.GetName() or 'Down' not in h3.GetName() : continue
#                if down.GetName() !=downName : continue
#                if h3.Integral()< 0.000001 and down.ReadObj().Integral() < 0.000001: continue
#                if h3.Integral()> 0.000001 and down.ReadObj().Integral() > 0.000001: continue
#                print '========88888888=>>>>   small integral     <<<<<=====88888888===== ', h3.GetName(),down.GetName(), h3.Integral(), down.ReadObj().Integral()
#                replacement=down.ReadObj()
#                h3=replacement
#                print 'new integral is ', h3.Integral()
#
#
#
#
#####################################################################################
#
#
#        if (h2.GetName()==name_last):
#            continue
#        name_last=histo_name
##        if 'reweighted_ggH' in histo_name:
#        histo_name=histo_name.replace('TES','CMS_scale_t_')
#        histo_name=histo_name.replace('JEnTot','CMS_scale_j_')
#        histo_name=histo_name.replace('MissingEn_UES','CMS_scale_met_unclustered')
#        histo_name=histo_name.replace('ttbarShape_','CMS_ttbarShape')
#        histo_name=histo_name.replace('trig_tt','CMS_trig_tt')
#        histo_name=histo_name.replace('CMS_JER','CMS_res_j')
#        histo_name=histo_name.replace('shape_','CMS_QCD_bkg_modeling')
#
#
#        if 'THU' not in histo_name: histo_name=histo_name.replace('Up',str(year)+'Up')
#        if 'THU' not in histo_name: histo_name=histo_name.replace('Down',str(year)+'Down')
#
#        histo_name=histo_name.replace('prefire2016','CMS_prefiring')
#        histo_name=histo_name.replace('prefire2017','CMS_prefiring')
#        histo_name=histo_name.replace('prefire2018','CMS_prefiring')
#
#        histo_name=histo_name.replace('CMS_ttbarShape2016','CMS_ttbarShape')
#        histo_name=histo_name.replace('CMS_ttbarShape2017','CMS_ttbarShape')
#        histo_name=histo_name.replace('CMS_ttbarShape2018','CMS_ttbarShape')
#
#        histo_name=histo_name.replace('Up125','Up')
#        histo_name=histo_name.replace('Down125','Down')
#
#        histo_name=histo_name.replace('_0_350_','_0_350125_')
#        histo_name=histo_name.replace('_350_450_','_350_450125_')
#        histo_name=histo_name.replace('_450_600_','_450_600125_')
#        histo_name=histo_name.replace('_600_800_','_600_800125_')
#        histo_name=histo_name.replace('_GT800_','_GT800125_')
#
#
#
#
#
##        histo_name=histo_name.replace('2016','2020')
##        histo_name=histo_name.replace('2017','2020')
##        histo_name=histo_name.replace('2018','2020')
#
##        h3.Rebin(2)
#
#        ofile.cd(Updatednom)
#        h3.Write(histo_name)