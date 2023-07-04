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

parser.add_option('--InputChannel', '-c', action='store',
                    default=False, dest='InputChannel',
                    help='InputChannel'
                )

# One could have 6 different runs, nominal_H, pdf_H, tauId_H, nominal_Z, pdf_Z, tauId_Z

parser.add_option('--nominal_H', '-nh', action='store',
                    default=False, dest='nominal_H',
                    help='nominal on Higgs'
                )
parser.add_option('--pdf_H', '-ph', action='store',
                    default=False, dest='pdf_H',
                    help='Run PDF & QCD scale or not on Higgs'
                )
parser.add_option('--tauId_H', '-th', action='store',
                    default=False, dest='tauId_H',
                    help='Add tau Id Unc on Higgs'
                )
parser.add_option('--nominal_Z', '-nz', action='store',
                    default=False, dest='nominal_Z',
                    help='nominal on Z'
                )
parser.add_option('--pdf_Z', '-pz', action='store',
                    default=False, dest='pdf_Z',
                    help='Run PDF & QCD scale or not on Z'
                )
parser.add_option('--tauId_Z', '-pz', action='store',
                    default=False, dest='tauId_Z',
                    help='Add tau Id Unc on Z'
                )




(options, args) = parser.parse_args()
InputFile=options.inputFile
suffice=options.suffice
InputChannel=options.InputChannel
nominal_H=options.nominal_H
pdf_H=options.pdf_H
tauId_H=options.tauId_H
nominal_Z=options.nominal_Z
pdf_Z=options.pdf_Z
tauId_Z=options.tauId_Z

#for ifile in glob('{}/NN_boost_*V12_newDM*'.format(InputFile)):
for ifile in glob('{}/*'.format(InputFile)):

    print 'ifile is   -- >>>  {}'.format(ifile)
    
    if InputChannel not in ifile: continue
    
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
    
    
        if nominal_H:
                print './{} -d {}  --suf {} -v {} -b {} {} {} '.format( executable, ifile, sample+suffice, var[0],var[1],var[2],var[3])
                os.system('./{} -d {}  --suf {} -v {} -b {} {} {} '.format( executable, ifile,sample+suffice, var[0],var[1],var[2],var[3]))
                print '\n\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%'
        elif nominal_Z:
                print './{} -d {}  --suf {} -v {} -b {} {} {} '.format( executable_Z, ifile, sample+suffice, var[0],var[1],var[2],var[3])
                os.system('./{} -d {}  --suf {} -v {} -b {} {} {} '.format( executable_Z, ifile,sample+suffice, var[0],var[1],var[2],var[3]))
                print '\n\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%'
        elif pdf_H :
            print './{} -d {}  --suf {} -v {} -b {} {} {} -p'.format( executable, ifile, sample+suffice, var[0],var[1],var[2],var[3])
            os.system('./{} -d {}  --suf {} -v {} -b {} {} {} -p'.format( executable, ifile,sample+suffice, var[0],var[1],var[2],var[3]))
            print '\n\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%'
        elif pdf_Z:
                print './{} -d {}  --suf {} -v {} -b {} {} {} -p'.format( executable_Z, ifile, sample+suffice, var[0],var[1],var[2],var[3])
                os.system('./{} -d {}  --suf {} -v {} -b {} {} {} -p'.format( executable_Z, ifile,sample+suffice, var[0],var[1],var[2],var[3]))
                print '\n\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%'
        elif tauId_H :
            for tausys in tadIsVars:
                print './{} -d {}  --suf {} -v {} -b {} {} {} -t {}'.format( executable, ifile, sample+suffice, var[0],var[1],var[2],var[3],tausys)
                os.system('./{} -d {}  --suf {} -v {} -b {} {} {} -t {}'.format( executable, ifile,sample+suffice, var[0],var[1],var[2],var[3],tausys))
                print '\n\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%'
        elif tauId_Z :
            for tausys in tadIsVars:
                print './{} -d {}  --suf {} -v {} -b {} {} {} -t {}'.format( executable_Z, ifile, sample+suffice, var[0],var[1],var[2],var[3],tausys)
                os.system('./{} -d {}  --suf {} -v {} -b {} {} {} -t {}'.format( executable_Z, ifile,sample+suffice, var[0],var[1],var[2],var[3],tausys))
                print '\n\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%'
        else:
            print 'input not known'
