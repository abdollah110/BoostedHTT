import plotter


categories = ['_0jet']

class PlotArgs():
    def __init__(self, input, year, category, variable, label, prefix, scale):
        self.input = input
        self.year = year
        self.category = category
        self.variable = variable
        self.label = label
        self.prefix = prefix
        self.scale = scale

def main(args):
#    for plot in plots:
    for category in categories:

        InputFile=args.input
        channel=''
        year=0
        
        if '2016' in InputFile:
            year = 2016
        elif '2017' in InputFile:
            year = 2017
        elif '2018' in InputFile:
            year = 2018
        else:
            print 'which year ???'


        if 'em2' in InputFile or '_em_' in InputFile:
            channel = 'em'
        elif 'me2' in InputFile or '_me_' in InputFile:
            channel = 'me'
        elif 'mt2' in InputFile or '_mt_' in InputFile:
            channel = 'mt'
        elif 'et2' in InputFile or '_et_' in InputFile:
            channel = 'et'
        elif 'tt2' in InputFile or '_tt_' in InputFile:
            channel = 'tt'
        elif 'mm2' in InputFile or '_mm_' in InputFile:
            channel = 'mm'
        else:
            print 'which channel ???'



        inputs = PlotArgs(
            args.input,
            year,
            channel + category,
            args.variable,
            args.prefix,
            args.variable,
            3
        )
        plotter.BuildPlot(inputs)

if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser()
    parser.add_argument('--input', '-i', required=True, help='path to input files')
    parser.add_argument('--prefix', '-p', required=True, help='prefix for files')
    parser.add_argument('--variable', '-v', required=True, help='Which variable')
    main(parser.parse_args())
