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
ggHName=''
XHName=''
for ifile in glob('{}/*root'.format(InputFile)):

#    if 'ggH125' in ifile:
#        ggHName=ifile.replace(InputFile,'')
#        print ifile
#
#        newName=ifile.replace('ggH125','ggH_PTH_0_350').replace(".root","125.root")
#        os.system("cp {} {}".format(ifile, newName))
#        newName=ifile.replace('ggH125','ggH_PTH_350_450').replace(".root","125.root")
#        os.system("cp {} {}".format(ifile, newName))
#        newName=ifile.replace('ggH125','ggH_PTH_450_600').replace(".root","125.root")
#        os.system("cp {} {}".format(ifile, newName))
#        newName=ifile.replace('ggH125','ggH_PTH_600_800').replace(".root","125.root")
#        os.system("cp {} {}".format(ifile, newName))
#        newName=ifile.replace('ggH125','ggH_PTH_GT800').replace(".root","125.root")
#        os.system("cp {} {}".format(ifile, newName))

#    if 'XH125' in ifile:
#        XHName=ifile.replace(InputFile,'')
#        print ifile
#
#        newName=ifile.replace('XH125','XH_PTH_0_350').replace(".root","125.root")
#        os.system("cp {} {}".format(ifile, newName))
#        newName=ifile.replace('XH125','XH_PTH_350_450').replace(".root","125.root")
#        os.system("cp {} {}".format(ifile, newName))
#        newName=ifile.replace('XH125','XH_PTH_450_600').replace(".root","125.root")
#        os.system("cp {} {}".format(ifile, newName))
#        newName=ifile.replace('XH125','XH_PTH_600_800').replace(".root","125.root")
#        os.system("cp {} {}".format(ifile, newName))
#        newName=ifile.replace('XH125','XH_PTH_GT800').replace(".root","125.root")
#        os.system("cp {} {}".format(ifile, newName))
        
    if 'JJH125' in ifile:
        JJHName=ifile.replace(InputFile,'')
        print ifile
        newName=ifile.replace('JJH125','JJH_PTH_0_350').replace(".root","125.root")
        os.system("cp {} {}".format(ifile, newName))
        newName=ifile.replace('JJH125','JJH_PTH_350_450').replace(".root","125.root")
        os.system("cp {} {}".format(ifile, newName))
        newName=ifile.replace('JJH125','JJH_PTH_450_600').replace(".root","125.root")
        os.system("cp {} {}".format(ifile, newName))
        newName=ifile.replace('JJH125','JJH_PTH_600_800').replace(".root","125.root")
        os.system("cp {} {}".format(ifile, newName))
        newName=ifile.replace('JJH125','JJH_PTH_GT800').replace(".root","125.root")
        os.system("cp {} {}".format(ifile, newName))


#OutSide=ggHName.replace('ggH125','OutsideAcceptance').replace("125.root",".root")
#os.system('hadd -f {}/{} {}/{} {}/{}'.format(InputFile, OutSide,InputFile, ggHName, InputFile,XHName))
        
