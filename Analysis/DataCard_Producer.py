#process_trees_tt -d /eos/uscms/store/user/abdollah/NN_output_Sys/NN_CADI_tt_2016_v1NN_Z_masspt_Down_NN --suf V1 -v NN_disc -b 20 0 1

import os
from optparse import OptionParser
#from colorama import Fore, Back, Style
from glob import glob


parser = OptionParser(description='script to make the template and run plot')

parser.add_option('--input', '-i', action='store',
                    default=False, dest='inputFile',
                    help='Location of input file'
                )

parser.add_option('--suffice', '-s', action='store',
                    default=False, dest='suffice',
                    help='Location of input file'
                )




(options, args) = parser.parse_args()
InputFile=options.inputFile
suffice=options.suffice


for ifile in glob('{}/*'.format(InputFile)):

    print 'ifile is   -- >>>  {}'.format(ifile)
    
    year=0
    if '2016' in ifile:
        year = 2016
    elif '2017' in ifile:
        year = 2017
    elif '2018' in ifile:
        year = 2018
    else:
        print 'which year ???'

    if '_em_' in ifile:
        channel = 'em'
        treeName = 'emu_tree'
        executable = 'process_trees_em'
    elif '_me_' in ifile:
        channel = 'me'
        treeName = 'emu_tree'
        executable = 'process_trees_em'
    elif '_mt_' in ifile:
        channel = 'mt'
        treeName = 'mutau_tree'
        executable = 'process_trees_lt_fr'
    elif '_et_' in ifile:
        channel = 'et'
        treeName = 'etau_tree'
        executable = 'process_trees_lt_fr'
    elif '_tt_' in ifile:
        channel = 'tt'
        treeName = 'tautau_tree'
        executable = 'process_trees_tt'
    elif '_mm_' in ifile:
        channel = 'mm'
        treeName = 'mumu_tree'
        executable = 'process_trees_mm'
    else:
        print 'which channel ???'



    Variable=[
    #            ['m_sv', 20,0,200],
                ['NN_disc',20,0,1]
    ]


    print 'ifile is   -- >>>  {}  year is {}   channel is {} '.format(ifile,year,channel)

    for var in Variable:
        print '{} -d {}  --suf {} -v {} -b {} {} {}'.format( executable, ifile, suffice, var[0],var[1],var[2],var[3])
        os.system('{} -d {}  --suf {} -v {} -b {} {} {}'.format( executable, ifile,suffice, var[0],var[1],var[2],var[3]))
        print '\n\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%'
