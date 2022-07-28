#./process_trees_sf_fr -d newboost_mt_2018_SF_sys --suf sys_v1 -v vis_mass -b 30 0 150 -c lep2IsoPassL -l 0 -h 1000 -n test -w Loose
import os
from optparse import OptionParser
import colorama
from colorama import Fore, Back, Style


parser = OptionParser(description='script to make the template and run plot')

#parser.add_option('--exe', '-e', action='store',
#                default=False, dest='exe',
#                help='executable'
#                )

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

year=0
if '2016' in InputFile:
    year = 2016
elif '2017' in InputFile:
    year = 2017
elif '2018' in InputFile:
    year = 2018
else:
    print 'which year ???'

#channel=''
#treeName=''
#executable=''
#
#
#if '_em_' in InputFile:
#    channel = 'em'
#    treeName = 'emu_tree'
#    executable = 'process_trees_em'
#elif '_mt_' in InputFile:
#    channel = 'mt'
#    treeName = 'mutau_tree'
#    executable = 'process_trees_lt'
##    executable = 'process_trees_lt_fr'
#elif '_et_' in InputFile:
#    channel = 'et'
#    treeName = 'etau_tree'
#    executable = 'process_trees_lt'
#elif '_tt_' in InputFile:
#    channel = 'tt'
#    treeName = 'tautau_tree'
#    executable = 'process_trees_tt'
#elif '_mm_' in InputFile:
#    channel = 'mm'
#    treeName = 'mumu_tree'
#    executable = 'process_trees_mm'
#else:
#    print 'which channel ???'



Variable=[

#            ['lep1Pt',30,0,300],
#            ['lep2Pt',30,0,300],
#            ['tmass',20, 0, 100],
###            ['ZMass',20, 0, 200],
#            ['higgs_pT',40, 0, 1000],
#            ['higgs_m',20, 0, 400],
#            ['Met', 25, 0, 500],
            ['vis_mass',24, 0, 120],
#            ['dR_lep_lep', 20,0,1],
#            ['LeadJetPt', 30,0,1500],
#            ['ht', 20,0,2000],
#            ['st', 20,0,2000],
#            ['m_sv', 20,0,200],
#            ['BoostedTauRawIso', 20,0,1],
#            ['NN_disc',20,0,1]
]
PTrange= [
#        [0,10000,'_bin0'],
#        [0,50,'_bin1'],
#        [50,100,'_bin2'],
#        [100,10000,'_bin3'],
#
        [0,1,'_bin0'],
        [0,0.5,'_bin1'],
        [0.5,0.65,'_bin2'],
        [0.65,0.8,'_bin3'],


]

WPs=[
    ['lep2IsoPassV', 'VLoose'],
    ['lep2IsoPassL','Loose'],
    ['lep2IsoPassM', 'Medium'],
    ['lep2IsoPassT' ,'Tight']
]
for var in Variable:
    for pt in PTrange:
        for wp in WPs:
            print '\n\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%'
            print(Back.GREEN + 'start making datacard for {} in pt range {} and WP is {} \n'.format(var, pt, wp[0]))
            os.system('./process_trees_sf_fr -d {}  --suf {} -v {} -b {} {} {} -c {} -w {} -l {} -h {} -n {}'.format( InputFile,suffice, var[0],var[1],var[2],var[3], wp[0], wp[1],pt[0],pt[1],pt[2]))
