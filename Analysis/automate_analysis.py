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


def getSystematics(name):
  systs = ['']
  
   
  if name != 'data_obs' || name != 'QCD':
     systs += [
             'met_JESUp', 'met_JESDown', 'met_UESUp', 'met_UESDown', 'prefireUp', 'prefireDown',
#             'met_reso_Up', 'met_resp_Up','met_reso_Down', 'met_resp_Down'
              ]
              
  if name == 'TT':
    systs += ['ttbarShape_Up', 'ttbarShape_Down']

  if name == 'ZLL' or name == 'ZTT' or name == 'ZJ':
    systs += ['Z_masspt_Up', 'Z_masspt_Down']

#  if name == 'W':
#    systs += ['WBosonKFactorUp', 'WBosonKFactorDown']

  return systs

for ifile in fileList:
    print ifile
    sample = ifile.split('/')[-1].split(suffix)[0]
#    if prefix:
#      sample = sample.replace(prefix, '')
    tosample = ifile.replace(sample+suffix,'')

    if 'DYJets' in sample:
#        names = ['ZLL', 'ZTT','ZJ']
        names = ['ZTT']
    elif 'TT' in sample:
        names = ['TT']
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
    elif 'ZH125' in sample:
        names = ['ZH125']
    elif 'JJH' in sample or 'jjh' in sample:
        names = ['JJH']
    elif 'QCD' in sample or 'qcd' in sample:
        names = ['QCD']
    else:
        names = ['VV']

#    callstring = './%s -p %s -s %s -d %s -y %s' % (options.exe, tosample, sample, options.output_dir, year)
    callstring = './{} -p {} -s {} -d {} '.format(options.exe, tosample, sample, options.output_dir)


    try:
        makedirs('Output/trees/{}'.format(options.output_dir))
    except:
        pass


    if options.syst and not 'Data' in sample.lower():
        for name in names:
            for isyst in getSystematics(name):
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
