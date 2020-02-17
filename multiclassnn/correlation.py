import pandas as pd
import seaborn as sbr
import matplotlib.pyplot as plt


def main(args):
    data = pd.HDFStore(args.input)['df']
#    samples = data[(data['sample_names'] == 'TT') | (data['sample_names'] == 'VV') | (data['sample_names'] == 'ZTT') | (data['sample_names'] == 'ZLL') | (data['sample_names'] == 'W') ]
    samples = data[(data['sample_names'] == 'TT')]
#    samples = data[(data['sample_names'] == 'ggh_madgraph_twojet')]
    sample = samples[(samples['mjj'] < 80000)]
    correlations = sample[['njets','mt', 'D_zeta',
                           'mjj','hjj_pT', 'higgs_pT','m_sv',
                           'Q2V1', 'Q2V2', 'Phi', 'Phi1', 'costheta1', 'costheta2', 'costhetastar']].corr(method='pearson') * 100
#    correlations = sample[['njets','mt', 'el_iso', 'mu_iso', 'D_zeta','mt_elmet','mt_mumet',
#                       'mjj', 'dEtajj', 'el_pt', 'mu_pt', 'hjj_pT', 'higgs_pT','m_sv']].corr(method='pearson') * 100
#    correlations = sample[['Q2V1', 'Q2V2', 'Phi', 'Phi1', 'costheta1', 'costheta2', 'costhetastar']].corr(method='pearson') * 100
    ax = sbr.heatmap(correlations, linewidth=0.5, annot=True)
    plt.yticks(rotation=45)
    plt.xticks(rotation=45)
#    plt.savefig('corr-sig--vbf.png')
    plt.savefig('corr-bkg.png')


if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser()
    parser.add_argument('--input', '-i', action='store',
                        dest='input', default='test.h5', help='input dataframe')
    main(parser.parse_args())
