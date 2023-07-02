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

parser.add_option('--RunPdf', '-p', action='store',
                    default=False, dest='PDF',
                    help='Run PDF & QCD scale or not'
                )

parser.add_option('--RunZTauId', '-t', action='store',
                    default=False, dest='RunZTauId',
                    help='Run TauId'
                )
parser.add_option('--RunRunZNominal', '-z', action='store',
                    default=False, dest='RunZNominal',
                    help='Run RunZNominal'
                )
parser.add_option('--RunZpdf', '-f', action='store',
                    default=False, dest='RunZpdf',
                    help='Run RunZpdf'
                )




(options, args) = parser.parse_args()
InputFile=options.inputFile
suffice=options.suffice
RunPdf=options.PDF
RunZTauId=options.RunZTauId
RunZNominal=options.RunZNominal
RunZpdf=options.RunZpdf

#for ifile in glob('{}/NN_boost_*V12_newDM*'.format(InputFile)):
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

    channel=''
    executable=''
    treeName=''
    
    if '_em' in ifile:
        channel = 'em'
        treeName = 'emu_tree'
#        executable = 'process_trees_em'
        executable = 'process_trees_NN_em'
        executable_Z = 'process_trees_NN_em_Z'
    elif '_me' in ifile:
        channel = 'me'
        treeName = 'emu_tree'
#        executable = 'process_trees_em'
        executable = 'process_trees_NN_em'
        executable_Z = 'process_trees_NN_em_Z'
    elif '_mt' in ifile:
        channel = 'mt'
        treeName = 'mutau_tree'
#        executable = 'process_trees_lt_fr'
        executable = 'process_trees_NN_lt'
        executable_Z = 'process_trees_NN_lt_Z'
    elif '_et' in ifile:
        channel = 'et'
        treeName = 'etau_tree'
#        executable = 'process_trees_lt_fr'
        executable = 'process_trees_NN_lt'
        executable_Z = 'process_trees_NN_lt_Z'
    elif '_tt' in ifile:
        channel = 'tt'
        treeName = 'tautau_tree'
#        executable = 'process_trees_tt'
        executable = 'process_trees_NN_tt'
        executable_Z = 'process_trees_NN_tt_Z'
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
    
    
    tadIsVars=[
    "TauIdBin_1_Up","TauIdBin_1_Down","TauIdBin_2_Up","TauIdBin_2_Down",
    "TauIdBin_3_Up","TauIdBin_3_Down","TauIdBin_4_Up","TauIdBin_4_Down"
    ]
    
    sample=ifile.replace(InputFile,'').replace('/','')
    
    print 'ifile is   -- >>>  {}  sample is {} year is {}   channel is {} '.format(ifile,sample, year,channel)

    for var in Variable:
    
    
        if RunZTauId :
            for tausys in tadIsVars:
                print './{} -d {}  --suf {} -v {} -b {} {} {} -t {}'.format( executable_Z, ifile, sample+suffice, var[0],var[1],var[2],var[3],tausys)
                os.system('./{} -d {}  --suf {} -v {} -b {} {} {} -t {}'.format( executable_Z, ifile,sample+suffice, var[0],var[1],var[2],var[3],tausys))
                print '\n\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%'
        elif RunZNominal:
                print './{} -d {}  --suf {} -v {} -b {} {} {} '.format( executable_Z, ifile, sample+suffice, var[0],var[1],var[2],var[3])
                os.system('./{} -d {}  --suf {} -v {} -b {} {} {} '.format( executable_Z, ifile,sample+suffice, var[0],var[1],var[2],var[3]))
        elif RunZpdf:
                print './{} -d {}  --suf {} -v {} -b {} {} {} -p'.format( executable_Z, ifile, sample+suffice, var[0],var[1],var[2],var[3])
                os.system('./{} -d {}  --suf {} -v {} -b {} {} {} -p'.format( executable_Z, ifile,sample+suffice, var[0],var[1],var[2],var[3]))
                print '\n\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%'
        elif RunPdf :
            print './{} -d {}  --suf {} -v {} -b {} {} {} -p'.format( executable, ifile, sample+suffice, var[0],var[1],var[2],var[3])
            os.system('./{} -d {}  --suf {} -v {} -b {} {} {} -p'.format( executable, ifile,sample+suffice, var[0],var[1],var[2],var[3]))
            print '\n\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%'
        else:
            print './{} -d {}  --suf {} -v {} -b {} {} {}'.format( executable, ifile, sample+suffice, var[0],var[1],var[2],var[3])
            os.system('./{} -d {}  --suf {} -v {} -b {} {} {}'.format( executable, ifile,sample+suffice, var[0],var[1],var[2],var[3]))
            print '\n\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%'
