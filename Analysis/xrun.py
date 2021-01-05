import os
from optparse import OptionParser


parser = OptionParser(description='script to make the template and run plot')

parser.add_option('--exe', '-e', action='store',
                default=False, dest='exe',
                help='executable'
                )

parser.add_option('--input', '-i', action='store',
                    default=False, dest='inputFile',
                    help='Location of input file'
                )


(options, args) = parser.parse_args()
InputFile=options.inputFile

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

if '_em_' in InputFile:
    channel = 'em'
    treeName = 'emu_tree'
elif '_mt_' in InputFile:
    channel = 'mt'
    treeName = 'mutau_tree'
elif '_et_' in InputFile:
    channel = 'et'
    treeName = 'etau_tree'
elif '_tt_' in InputFile:
    channel = 'tt'
    treeName = 'tautau_tree'
elif '_mm_' in InputFile:
    channel = 'mm'
    treeName = 'mumu_tree'
else:
    print 'which channel ???'



Variable=[
#            ['Met',20,0,400],
#            ['muPt',15,0,300],
            ['taupt',15,0,300],
##            ['leadPt',15,0,300],
##            ['subPt',15,0,300],
            ['tmass',20, 0, 100],
##            ['ZMass',20, 0, 200],
            ['higgs_pT',20, 0, 800],
            ['higgs_m',20, 0, 400],
            ['Met', 20, 0, 400],
            ['vis_mass',12, 0, 120],
            ['dR_lep_tau', 20,0,1],
##            ['dR_tau_tau', 20,0,1],
            ['LeadJetPt', 20,0,600],
##            ['BoostedTauRawIso', 20,-1,1],
##            ['IsoMuValue', 2,0,2],
##            ['eleIDMVANoIso', 20,0,2],
            ['ht', 24,0,1200],
#            ['st', 24,0,1200],
            ['m_sv', 20,0,200],
            ['NN_disc',20,0,1]
]
for var in Variable:
    print '=====> start making datacard for ', var
    os.system('./%s -y %s -t %s  -c %s -d %s   --suf %s -v %s -b %f %f %f '%(options.exe, year, treeName, channel, InputFile, var[0],var[0],var[1],var[2],var[3]))
