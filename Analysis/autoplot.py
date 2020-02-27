import plotter

plots = [
    #    ('dEtajj', 'd#eta_{jj}', 2.2),
#    ('D0_VBF', 'D_{0-}^{VBF}', 2.2),
#    ('D0_ggH', 'D_{CP}^{ggH}', 2.2),
#    ('VBF_MELA', 'D_{2jet}^{VBF}', 2.2),
    ('NN_disc', 'D_{NN}^{VBF}', 3),
#    ('m_sv', 'm_{SVFit}', 2.2),
#    ('higgs_pT', 'Higgs p_{T}', 1.4),
#    ('mjj', 'm_{JJ}', 1.4),
#    ('met', 'Missing E_{T}', 1.4),
#    ('mt', 'TMass (lep,MET)', 1.4),
#    ('njets', 'N(jets)', 1.4),
    ('vis_mass', 'm_{Visible}', 2.2),
#    ('el_pt', 'Electron p_{T}', 1.4),
#    #    ('el_eta', 'Electron #eta', 2.2),
#    ('mu_pt', 'Muon p_{T}', 1.4),
#    #    ('mu_eta', 'Muon #eta', 2.2),
#    #    ('mu_iso', '#mu rel isolation', 2.2),
#    ('Q2V1', 'Q^{2} V1 [GeV]',1.4),
#    ('Q2V2', 'Q^{2} V2 [GeV]',1.4),
#    ('Phi', '#phi',1.4),
#    ('Phi1', '#phi_{1}',1.4),
#    ('costheta1', 'Cos(#theta_{1})',1.4),
#    ('costheta2', 'Cos(#theta_{2})',1.4),
#    ('costhetastar', 'Cos(#theta*)',1.4),
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
        for category in categories:
#            if ('D0' in plot[0] or 'VBF_MELA' in plot[0] or 'NN' in plot[0] or 'MELA' in plot[0] or 'mjj' in plot[0] or 'dEtajj' in plot[0] or 'Q2V' in plot[0] or 'Phi' in plot[0] or 'costheta' in plot[0]) and not 'vbf' in category:
#                continue

            inputs = PlotArgs(
                args.input,
                args.year,
                args.channel + category,
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
    parser.add_argument('--year', '-y', required=True, help='year to process')
    parser.add_argument('--channel', '-c', required=True, help='channel to plot')
    main(parser.parse_args())
