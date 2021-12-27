import plotter_sf
from glob import glob


plots = [
#    ('NN_disc', 'D_{NN}', 3),
    ('m_sv', 'm_{SVFit}', 3.0),
    ('higgs_pT', 'Higgs p_{T}', 3.0),
    ('higgs_m', 'Higgs mass', 3.0),
    ('tmass', 'm_{T}', 3.0),
    ('Met', 'Missing E_{T}', 3.0),
    ('vis_mass', 'm_{Visible}', 3.0),
    ('lep1Pt', '1st lepton pT', 3.0),
    ('lep2Pt', '2nd lepton pT', 3.0),
    ('dR_lep_lep', 'dR_{#tau #tau}', 3.0),
    ('LeadJetPt', 'LeadJetPt', 3.0),
    ('ht', 'ht', 3.0),
    ('st', 'st', 3.0),
###    ('ZMass', 'ZMass', 3.0),
    ('BoostedTauRawIso', 'BoostedTauRawIso', 5.0),

]

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
    for plot in plots:
        print plot
#        for category in categories:
        fileList = [ifile for ifile in glob(args.input+'/*') if '.root' in ifile]
        category='_0jet'
        for InputFile in fileList:
            print 'InputFile = {}'.format(InputFile)
        
#            if ('D0' in plot[0] or 'VBF_MELA' in plot[0] or 'NN' in plot[0] or 'MELA' in plot[0] or 'mjj' in plot[0] or 'dEtajj' in plot[0] or 'Q2V' in plot[0] or 'Phi' in plot[0] or 'costheta' in plot[0]) and not 'vbf' in category:
#                continue

#            InputFile=args.input
            channel=''
    #        treeName=''
            year=0
            
            if '2016' in InputFile:
                year = 2016
            elif '2017' in InputFile:
                year = 2017
            elif '2018' in InputFile:
                year = 2018
            else:
                print 'which year ???'


            if 'em2' in InputFile:
                channel = 'em'
    #            treeName = 'emu_tree'
            elif 'mt2' in InputFile:
                channel = 'mt'
                treeName = 'mutau_tree'
            elif 'et2' in InputFile:
                channel = 'et'
    #            treeName = 'etau_tree'
            elif 'tt2' in InputFile:
                channel = 'tt'
    #            treeName = 'tautau_tree'
            elif 'mm2' in InputFile:
                channel = 'mm'
    #            treeName = 'mumu_tree'
            else:
                print 'which channel ???'



            inputs = PlotArgs(
                InputFile,
                year,
                channel + category,
                plot[0],
                plot[1],
                args.prefix,
                plot[2]
            )
            plotter_sf.BuildPlot(inputs)

if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser()
    parser.add_argument('--input', '-i', required=True, help='path to input files')
    parser.add_argument('--prefix', '-p', required=True, help='prefix for files')
#    parser.add_argument('--year', '-y', required=True, help='year to process')
#    parser.add_argument('--channel', '-c', required=True, help='channel to plot')
    main(parser.parse_args())
