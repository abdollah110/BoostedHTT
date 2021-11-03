import os
from subprocess import call
from optparse import OptionParser
from glob import glob

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
        [0,300,'_bin1'],
        [300,400,'_bin2'],
        [400,550,'_bin3'],
        [550,800,'_bin4'],
        [800,100000,'_bin5']
]


for ifile in glob('{}/NN*'.format(InputFile)):
    sample=ifile.replace(InputFile,'').replace('/','')
    
    print 'starting from {} and the file name is  {}'.format(ifile,sample)
    
        
        
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
    treeName=''
    executable=''


    if '_em_' in ifile:
        channel = 'em'
        treeName = 'emu_tree'
        executable = 'DiffMeasure_em'
    elif '_me_' in ifile:
        channel = 'me'
        treeName = 'emu_tree'
        executable = 'DiffMeasure_em'
    elif '_mt_' in ifile:
        channel = 'mt'
        treeName = 'mutau_tree'
        executable = 'DiffMeasure_lt'
    elif '_et_' in ifile:
        channel = 'et'
        treeName = 'etau_tree'
        executable = 'DiffMeasure_lt'
    elif '_tt_' in ifile:
        channel = 'tt'
        treeName = 'tautau_tree'
        executable = 'DiffMeasure_tt'
    else:
        print 'which channel ???'
                    
    for pt in PTrange:
            for var in Variable:
                if Observable==var[0]:
                    print '\n\n\n\n =====> start making datacard for ', var
                    print 'command is ' , './{} -d {}   --suf {} -v {} -b {} {} {} -c higgs_pT -l {} -h {}  '.format(executable, ifile, var[0],var[0],var[1],var[2],var[3],pt[0],pt[1])
                    os.system('./{} -d {}   --suf {}  --bin {} -v {} -b {} {} {} -c higgs_pT -l {} -h {}  '.format(executable, ifile, sample+prefix, pt[2],var[0],var[1],var[2],var[3],pt[0],pt[1]))
                    break
