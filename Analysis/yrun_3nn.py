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

if 'em_' in InputFile:
    channel = 'em'
    treeName = 'emu_tree'
    executable = 'process_trees_NN_em'
elif 'me_' in InputFile:
    channel = 'me'
    treeName = 'mue_tree'
    executable = 'process_trees_NN_em'
elif 'mt_' in InputFile:
    channel = 'mt'
    treeName = 'mutau_tree'
    executable = 'process_trees_NN_lt'
elif 'et_' in InputFile:
    channel = 'et'
    treeName = 'etau_tree'
    executable = 'process_trees_NN_lt'
elif 'tt_' in InputFile:
    channel = 'tt'
    treeName = 'tautau_tree'
    executable = 'process_trees_NN_tt'
else:
    print 'which channel ???'

print channel, treeName, executable

Variable=[
#
#            ['lep1Pt',30,0,300],
#            ['lep2Pt',30,0,300],
#            ['tmass',20, 0, 100],
###            ['ZMass',20, 0, 200],
#            ['higgs_pT',25, 0, 1000],
#            ['higgs_m',20, 0, 400],
#            ['Met', 25, 0, 500],
#            ['vis_mass',15, 0, 150],
#            ['dR_lep_lep', 10,0,1],
            ['LeadJetPt', 30,0,1500],
            ['ht', 25,0,2000],
            ['st', 25,0,2000],
            ['m_sv', 25,0,250],
##            ['BoostedTauRawIso', 20,0,1],
            ['NN_disc',20,0,1],
#            ['NN_disc',8,0,1],
#            ['NN_disc_ZTT',20,0,1],
#            ['NN_disc_QCD',20,0,1],
##            ['nbjet',5,0,5]
#            ['MuMatchedIsolation',20,0,-1,1],
#            ['EleMatchedIsolation',20,0,-1,1],
]

PTrange= [
        [0,100000,'_bin0'],
        [0,350,'_bin1'],
        [350,500,'_bin2'],
        [500,100000,'_bin3']
]

Diff=0

if Diff:
    for pt in PTrange:
        for var in Variable:
            if Observable==var[0]:
                print '\n\n\n\n =====> start making datacard for ', var
                print 'command is ' , './{} -d {}   --suf {} -v {} -b {} {} {} -c higgs_pT -l {} -h {}  '.format(executable, InputFile, var[0],var[0],var[1],var[2],var[3],pt[0],pt[1])
                os.system('./{} -d {}   --suf {} -v {} -b {} {} {} -c higgs_pT -l {} -h {}  '.format(executable, InputFile, pt[2],var[0],var[1],var[2],var[3],pt[0],pt[1]))
                break

else:

    for var in Variable:
        if Observable==var[0]:
            print '\n\n\n\n =====> start making datacard for ', var
            print 'command is ' , './%s -d %s   --suf %s -v %s -b %f %f %f '%(executable, InputFile, var[0],var[0],var[1],var[2],var[3])
            os.system('./%s -d %s   --suf %s -v %s -b %f %f %f '%(executable, InputFile, prefix,var[0],var[1],var[2],var[3]))
            break

    for var in Variable:
        if Observable=='all':
            print '\n\n\n\n =====> start making datacard for ', var
            print 'command is ' , './%s -d %s   --suf %s -v %s -b %f %f %f '%(executable, InputFile, var[0],var[0],var[1],var[2],var[3])
            os.system('./%s -d %s   --suf %s -v %s -b %f %f %f '%(executable, InputFile, prefix,var[0],var[1],var[2],var[3]))
