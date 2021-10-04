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


if '_em_' in InputFile:
    channel = 'em'
    treeName = 'emu_tree'
    executable = 'DiffMeasure_em'
elif '_me_' in InputFile:
    channel = 'me'
    treeName = 'mue_tree'
    executable = 'DiffMeasure_em'
elif '_mt_' in InputFile:
    channel = 'mt'
    treeName = 'mutau_tree'
    executable = 'DiffMeasure_lt'
elif '_et_' in InputFile:
    channel = 'et'
    treeName = 'etau_tree'
    executable = 'DiffMeasure_lt'
elif '_tt_' in InputFile:
    channel = 'tt'
    treeName = 'tautau_tree'
    executable = 'DiffMeasure_tt'
else:
    print 'which channel ???'



Variable=[
            ['lep1Pt',30,0,300],
            ['lep2Pt',30,0,300],
            ['tmass',20, 0, 100],
            ['higgs_pT',25, 0, 1000],
            ['higgs_m',20, 0, 400],
            ['Met', 25, 0, 500],
            ['vis_mass',15, 0, 150],
            ['dR_lep_lep', 20,0,1],
            ['LeadJetPt', 30,0,1500],
            ['ht', 25,0,2000],
            ['st', 25,0,2000],
            ['m_sv', 25,0,250],
            ['NN_disc',20,0,1],
]

PTrange= [
        [0,100000,'_bin0'],
        [0,350,'_bin1'],
        [350,450,'_bin2'],
        [450,600,'_bin3'],
        [600,100000,'_bin4']
]

for pt in PTrange:
        for var in Variable:
            if Observable==var[0]:
                print '\n\n\n\n =====> start making datacard for ', var
                print 'command is ' , './{} -d {}   --suf {} -v {} -b {} {} {} -c higgs_pT -l {} -h {}  '.format(executable, InputFile, var[0],var[0],var[1],var[2],var[3],pt[0],pt[1])
                os.system('./{} -d {}   --suf {}  --bin {} -v {} -b {} {} {} -c higgs_pT -l {} -h {}  '.format(executable, InputFile, prefix, pt[2],var[0],var[1],var[2],var[3],pt[0],pt[1]))
                break
