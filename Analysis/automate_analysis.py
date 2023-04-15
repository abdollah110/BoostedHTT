#!/usr/bin/env python
# Analysis]$ python automate_analysis.py -e BoostedHTT2017_mt.exe -p /eos/uscms/store/user/abdollah/SkimBoostedH/2018/mt/v1_fast_Hadd/ -o boost_mt_2018_v2 
############################################################
## Script to automate running an analyzer on all files in ##
## a directory.                                           ##
############################################################

from os import popen, makedirs
from subprocess import call
from optparse import OptionParser
import time
from glob import glob

parser = OptionParser()
parser.add_option('--data', '-d', action='store_true',
                  default=False, dest='isData',
                  help='run on data or MC'
                  )
parser.add_option('--exe', '-e', action='store',
                  default='Analyze', dest='exe',
                  help='name of executable'
                  )
parser.add_option('--syst', action='store_true',
                  default=False, dest='syst',
                  help='run systematics as well'
                  )
parser.add_option('--path', '-p', action='store',
                  default='root_files/', dest='path',
                  help='path to input file directory'
                  )
#parser.add_option('--prefix', '-P', action='store',
#                  default=None, dest='prefix',
#                  help='prefix to strip'
#                  )
#parser.add_option('--year', '-y', action='store',
#                default=None, dest='year',
#                help='prefix to strip'
#)

parser.add_option('--output-dir', '-o', action='store',
                  default='', dest='output_dir', 
                  help='name of output directory after Output/trees'
                  )
(options, args) = parser.parse_args()
#prefix = options.prefix
#year = options.year
suffix = '.root'

try:
    makedirs('Output/trees/{}'.format(options.output_dir))
except:
    pass

start = time.time()
if options.isData:
    fileList = [ifile for ifile in glob(options.path+'/*') if '.root' in ifile and 'data' in ifile.lower()]
else:
    fileList = [ifile for ifile in glob(options.path+'/*') if '.root' in ifile]


def getSystematics(name,year,channel):
  systs = ['']
  
   
  if name != 'data_obs' or name != 'QCD':
     systs += [
              'MissingEn_UESUp', 'MissingEn_UESDown','JEnTotUp','JEnTotDown'
              ]
  if year==2016 or year ==2017:
     systs += [
               'prefireUp', 'prefireDown'
              ]
  if channel=='mt' or channel=='et' or channel=='tt':
     systs += [
              'TESUp_1prong', 'TESDown_1prong', 'TESUp_1prong1pizero','TESDown_1prong1pizero','TESUp_3prong','TESDown_3prong'
              ]
  if channel=='tt':
     systs += [
               'trig_ttUp','trig_ttDown'
              ]
  if name == 'TT':
    systs += ['ttbarShape_Up', 'ttbarShape_Down']

  if name == 'ZLL' or name == 'ZTT' or name == 'ZJ':
    systs += ['Z_masspt_Up', 'Z_masspt_Down', 'isr_Up','fsr_Up','isr_Down','fsr_Down']

  if name == 'ggH125':
    systs +=["THU_ggH_Mu_Up","THU_ggH_Res_Up","THU_ggH_Mig01_Up","THU_ggH_Mig12_Up","THU_ggH_VBF2j_Up","THU_ggH_VBF3j_Up","THU_ggH_PT60_Up","THU_ggH_PT120_Up","THU_ggH_qmtop_Up","THU_ggH_Mu_Down","THU_ggH_Res_Down","THU_ggH_Mig01_Down","THU_ggH_Mig12_Down","THU_ggH_VBF2j_Down","THU_ggH_VBF3j_Down","THU_ggH_PT60_Down","THU_ggH_PT120_Down","THU_ggH_qmtop_Down"]
#
#


#  if name == 'W':
#    systs += ['WBosonKFactorUp', 'WBosonKFactorDown']

  return systs

for ifile in fileList:
    print ifile
    sample = ifile.split('/')[-1].split(suffix)[0]
#    if prefix:
#      sample = sample.replace(prefix, '')
    tosample = ifile.replace(sample+suffix,'')

    if 'DYJets' not in sample: continue # FIXME this is just to run on DY samples
    if 'DYJets' in sample:
#        names = ['ZLL', 'ZTT']
#        names = ['ZLL', 'ZTT','ZJ']
        names = ['ZTT']
#        continue
    elif 'TT' in sample:
        names = ['TT']
#        continue
    elif 'WJets' in sample or 'EWK' in sample:
        names = ['W']
    elif 'data' in sample.lower() or 'run' in sample.lower():
        names = ['data_obs']
    elif 'ggH125' in sample:
        names = ['ggH125']
    elif 'qqH125' in sample:
        names = ['qqH125']
    elif 'WPlusH125' in sample:
        names = ['WPlusH125']
    elif 'WMinusH125' in sample:
        names = ['WMinusH125']
    elif 'ZH125' in sample or 'ZH' in sample or 'toptopH' in sample:
        names = ['ZH125']
    elif 'JJH' in sample or 'jjh' in sample:
        names = ['JJH']
    elif 'QCD' in sample or 'qcd' in sample:
        names = ['mcQCD']
    elif 'Embed' in sample:
        names = ['emb']
    else:
        names = ['VV']

#    callstring = './%s -p %s -s %s -d %s -y %s' % (options.exe, tosample, sample, options.output_dir, year)
    callstring = './{} -p {} -s {} -d {} '.format(options.exe, tosample, sample, options.output_dir)


    try:
        makedirs('Output/trees/{}'.format(options.output_dir))
    except:
        pass

    channelName=''
    year=0
    
    if '2016' in tosample:
        year = 2016
    elif '2017' in tosample:
        year = 2017
    elif '2018' in tosample:
        year = 2018
    elif '2020' in tosample:
        year = 2020
    else:
        print 'which year ???'


    if 'em' in options.exe or '_em' in options.exe:
        channel = 'em'
        channelName='em'
    elif 'me2' in options.exe or    '_me' in options.exe:
        channel = 'me'
        channelName='me'
        treeName = 'mue_tree'
    elif 'mt2' in options.exe or '_mt' in options.exe:
        channel = 'mt'
        channelName='mt'
        treeName = 'mutau_tree'
    elif 'et2' in options.exe  or  '_et' in options.exe:
        channel = 'et'
        channelName='et'
    elif 'tt2' in options.exe  or  '_tt' in options.exe:
        channel = 'tt'
        channelName='tt'
    else:
        print 'which channel ???'



    if options.syst and not 'data' in sample.lower() and not 'run' in sample.lower() and not 'qcd' in sample.lower():
        for name in names:
            for isyst in getSystematics(name,year,channel):
                #AM
                try:
                    makedirs('Output/trees/{}'.format(options.output_dir+'/_'+isyst))
                except:
                    pass

                tocall = callstring + ' -n %s -u %s' % (name, isyst)
                call(tocall, shell=True)
    else:
        for name in names:
            tocall = callstring + ' -n %s ' % name 
            call(tocall, shell=True)


    print tocall

end = time.time()
print 'Processing completed in', end-start, 'seconds.'
