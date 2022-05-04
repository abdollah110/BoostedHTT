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



year=0
if '2016' in inputfile:
    year = 2016
elif '2017' in inputfile:
    year = 2017
elif '2018' in inputfile:
    year = 2018
else:
    print 'which year ???'





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
#    ofile.mkdir(nom.replace('_0jet',''))
    Updatednom=nom.replace('_0jet','')
    ofile.mkdir(Updatednom)
    h1.cd()
    histoList = gDirectory.GetListOfKeys()
    name_last=""
    N_histo=0

    channel=''
    treeName=''
    executable=''


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

    print 'year is {} and channel is {}'.format(year,channel)

    for histo in histoList:
        h1.cd()
        h2 = histo.ReadObj()
        h3=h2.Clone()
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
####################################################################################


        if (h2.GetName()==name_last):
            continue
        name_last=histo_name
#        if 'reweighted_ggH' in histo_name:
        histo_name=histo_name.replace('TES','CMS_scale_t_')
        histo_name=histo_name.replace('JEnTot','CMS_scale_j_')
        histo_name=histo_name.replace('MissingEn_UES','CMS_scale_met_unclustered')
        histo_name=histo_name.replace('ttbarShape','CMS_ttbarShape')
        histo_name=histo_name.replace('trig_tt','CMS_trig_tt')


        if 'THU' not in histo_name: histo_name=histo_name.replace('Up',str(year)+'Up')
        if 'THU' not in histo_name: histo_name=histo_name.replace('Down',str(year)+'Down')

        histo_name=histo_name.replace('prefire2016','CMS_prefiring')
        histo_name=histo_name.replace('prefire2017','CMS_prefiring')
        histo_name=histo_name.replace('prefire2018','CMS_prefiring')
        
        histo_name=histo_name.replace('CMS_ttbarShape_2016','CMS_ttbarShape_')
        histo_name=histo_name.replace('CMS_ttbarShape_2017','CMS_ttbarShape_')
        histo_name=histo_name.replace('CMS_ttbarShape_2018','CMS_ttbarShape_')
        
        histo_name=histo_name.replace('Up125','Up')
        histo_name=histo_name.replace('Down125','Down')
        
        histo_name=histo_name.replace('_0_350_','_0_350125_')
        histo_name=histo_name.replace('_350_450_','_350_450125_')
        histo_name=histo_name.replace('_450_600_','_450_600125_')
        histo_name=histo_name.replace('_600_800_','_600_800125_')
        histo_name=histo_name.replace('_GT800_','_GT800125_')
        
        
#        histo_name=histo_name.replace('2016','2020')
#        histo_name=histo_name.replace('2017','2020')
#        histo_name=histo_name.replace('2018','2020')

        h3.rebin(2)
        
        ofile.cd(Updatednom)
        h3.Write(histo_name)
