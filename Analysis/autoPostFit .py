import plotter

plots = [
    ('NN_disc', 'D_{NN}', 3),
    ('m_sv', 'm_{SVFit}', 3.0),
    ('higgs_pT', 'Higgs p_{T}', 3.0),
    ('higgs_m', 'Higgs mass', 3.0),
    ('tmass', 'm_{T}', 3.0),
    ('Met', 'Missing E_{T}', 3.0),
    ('vis_mass', 'm_{Visible}', 3.0),
    ('taupt', 'tau p_{T}', 3.0),
    ('muPt', 'Muon p_{T}', 3.0),
    ('IsoMu', '#mu rel isolation', 3.0),
    ('dR_mu_tau', 'dR_mu_tau', 3.0),
    ('LeadJetPt', 'LeadJetPt', 3.0),
    ('BoostedTauRawIso', 'BoostedTauRawIso', 3.0),
    ('ht', 'ht', 3.0),
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
    main(parser.parse_args())
