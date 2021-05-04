import pandas as pd
import seaborn as sbr
import matplotlib.pyplot as plt


def main(args):
    data = pd.HDFStore(args.input)['df']
    sample = data[(data['sample_names'] == args.process)]
#    sample = samples[(samples['Pass'] > 0) ]
    correlations = sample[['lep1Pt','lep2Pt','Met','m_sv', 'LeadJetPt','higgs_m','higgs_pT','st','tmass']].corr(method='pearson') * 100
    ax = sbr.heatmap(correlations, linewidth=0.5, annot=True)
    plt.yticks(rotation=45)
    plt.xticks(rotation=25)
    plt.savefig('corr_{}.pdf'.format(args.process))

if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser()
    parser.add_argument('--input', '-i', action='store',
                        dest='input', default='test.h5', help='input dataframe')
    parser.add_argument('--process', '-p', action='store',
                        dest='process', default='ZTT', help='input dataframe')
    main(parser.parse_args())
