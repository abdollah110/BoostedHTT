import plotter
import ROOT
from ROOT import *


plots = [
    ('NN_disc', 'D_{NN}', 5),
]

categories = ['_0jet']

class PlotArgs():
    def __init__(self, input, year, category,channelName, variable, label, prefix, scale):
        self.input = input
        self.year = year
        self.category = category
        self.channelName = channelName
        self.variable = variable
        self.label = label
        self.prefix = prefix
        self.scale = scale

def main(args):
    for plot in plots:
    
        print plot
        inputfile =args.input
#        outputfile=args.outputfile

        file=ROOT.TFile(inputfile,"r")
        file.cd()
        dirList = gDirectory.GetListOfKeys()

    #
    #
    #
    #    ofile=ROOT.TFile(outputfile,"recreate")
    #    categories_list= file.GetListOfKeys()
    #    categories=[]
    #    for k2 in categories_list:
    #        categories.append(k2.GetName())
    #    #    print 'k2.GetName() ', k2.GetName()
    #    ncat=len(categories)
        year=0
        channel=''
        for KKK in dirList: # loop over categories


            k1=KKK.GetName()
            
            if '2016' in k1:
                year = 2016
            elif '2017' in k1:
                year = 2017
            elif '2018' in k1:
                year = 2018
            else:
                print 'which year ???'


            if 'em' in k1:
                channel = 'em'
                channelName = 'emu_tree'
                executable = 'process_trees_em'
            elif 'me' in k1:
                channel = 'me'
                channelName = 'mue_tree'
                executable = 'process_trees_em'
            elif 'mt' in k1:
                channel = 'mt'
                channelName = 'mutau_tree'
            #    executable = 'process_trees_lt'
                executable = 'process_trees_lt_fr'
            #    executable = 'process_trees_sf_fr'
            elif 'et' in k1:
                channel = 'et'
                channelName = 'etau_tree'
            #    executable = 'process_trees_lt'
                executable = 'process_trees_lt_fr'
            elif 'tt' in k1:
                channel = 'tt'
                channelName = 'tautau_tree'
                executable = 'process_trees_tt'
            else:
                print 'which channel ???'


            print 'hi ', k1, year,channel
        

            inputs = PlotArgs(
                args.input,
                year,
                k1,
                channelName,
                plot[0],
                plot[1],
                args.prefix,
                plot[2]
            )
            plotter.BuildPlot(inputs)

if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser()
    parser.add_argument('--input', '-i', required=True, help='path to input files')
    parser.add_argument('--prefix', '-p', required=True, help='prefix for files')
    main(parser.parse_args())
