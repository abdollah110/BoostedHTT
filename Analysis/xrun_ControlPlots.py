# This script is to be used for making control plots:
# It takes 3 inputs:
#-i the location of the root file
#-p the prefix
#-o which is used either for a single plot making or for 'all' plot making

import os
from subprocess import call
from optparse import OptionParser


parser = OptionParser(description='script to make the template and run plot')
parser.add_option('--input', '-i', action='store',
                    default=False, dest='inputFile',
                    help='Location of input file'
                )

parser.add_option('--prefix', '-p', action='store',
                    default=False, dest='prefix',
                    help='prefix'
                )

parser.add_option('--Observable', '-o', action='store',
                    default=False, dest='Obs',
                    help='The observable variable'
                )



(options, args) = parser.parse_args()
InputFile=options.inputFile
prefix=options.prefix
Observable=options.Obs

year=0
if '2016' in InputFile:
    year = 2016
elif '2017' in InputFile:
    year = 2017
elif '2018' in InputFile:
    year = 2018
else:
    print 'which year ???'

channel=''
treeName=''
executable=''

if '_em' in InputFile:
    channel = 'em'
    treeName = 'emu_tree'
    executable = 'process_trees_NN_em'
elif '_me' in InputFile:
    channel = 'me'
    treeName = 'mue_tree'
    executable = 'process_trees_NN_em'
elif '_mt' in InputFile:
    channel = 'mt'
    treeName = 'mutau_tree'
    executable = 'process_trees_NN_lt'
elif '_et' in InputFile:
    channel = 'et'
    treeName = 'etau_tree'
    executable = 'process_trees_NN_lt'
elif '_tt' in InputFile:
    channel = 'tt'
    treeName = 'tautau_tree'
    executable = 'process_trees_NN_tt'
else:
    print 'which channel ???'

print channel, treeName, executable

Variable=[

            ['lep1Pt',20,0,400],
            ['lep2Pt',20,0,400],
#            ['tmass',20, 0, 100],
####            ['ZMass',20, 0, 200],
#            ['higgs_pT',25, 0, 1000],
            ['higgs_pT',20, 0, 1000],
#            ['higgs_m',20, 0, 400],
            ['Met', 25, 0, 500],
#            ['vis_mass',15, 0, 150],
            ['dR_lep_lep', 10,0,1],
#            ['LeadJetPt', 30,0,1500],
            ['LeadJetPt', 30,0,1500],
#            ['ht', 25,0,2000],
#            ['st', 25,0,2000],
            ['m_sv', 25,0,250],
            ['NN_disc',10,0,1],
#            ['NN_disc_ZTT',10,0,1],
#            ['NN_disc_QCD',10,0,1],
#            ['MuMatchedIsolation',10,-1,1],
#            ['EleMatchedIsolation',10,-1,1],
]

PTrange= [
        [0,100000,'_bin0'],
        [0,350,'_bin1'],
        [350,450,'_bin2'],
        [450,600,'_bin3'],
        [600,100000,'_bin4']
]

Diff=1

if Diff:
#    for pt in PTrange:
    for var in Variable:
#        if Observable==var[0]:
        print '\n\n\n\n =====> start making datacard for ', var
        print 'command is ' , './{} -d {}   --suf {} -v {} -b {} {} {} '.format(executable, InputFile, var[0],var[0],var[1],var[2],var[3])
        os.system('command is ' , './{} -d {}   --suf {} -v {} -b {} {} {} '.format(executable, InputFile, var[0],var[0],var[1],var[2],var[3]))
        break

#else:
#
#    for var in Variable:
#        if Observable==var[0]:
#            print '\n\n\n\n =====> start making datacard for ', var
#            print 'command is ' , './%s -d %s   --suf %s -v %s -b %f %f %f '%(executable, InputFile, var[0],var[0],var[1],var[2],var[3])
#            os.system('./%s -d %s   --suf %s -v %s -b %f %f %f '%(executable, InputFile, prefix,var[0],var[1],var[2],var[3]))
#            break
#
#    for var in Variable:
#        if Observable=='all':
#            print '\n\n\n\n =====> start making datacard for ', var
#            print 'command is ' , './%s -d %s   --suf %s -v %s -b %f %f %f '%(executable, InputFile, var[0],var[0],var[1],var[2],var[3])
#            os.system('./%s -d %s   --suf %s -v %s -b %f %f %f '%(executable, InputFile, prefix,var[0],var[1],var[2],var[3]))
