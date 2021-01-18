import sys
import pandas as pd
import numpy as np
from glob import glob
from sklearn.preprocessing import StandardScaler, MinMaxScaler

# Variables used for selection. These shouldn't be normalized
selection_vars = [
                  'lep2IsoPass',
]

# Variables that could be used as NN input. These should be normalized
scaled_vars = [
               'evtwt','lep1Pt','lep2Pt','Met','m_sv', 'LeadJetPt','higgs_m','higgs_pT','st','tmass'
               ]


def loadFile(ifile, category):
    from root_pandas import read_root

    if 'mutau' in ifile or 'mt' in ifile:
        channel = 'mt'
    elif 'etau' in ifile or 'et' in ifile:
        channel = 'et'
    elif 'emu' in ifile or 'em' in ifile:
        channel = 'em'
    elif 'tautau' in ifile or 'tt' in ifile:
        channel = 'tt'
    else:
        raise Exception(
            'Input files must have MUTAU or ETAU or EMU in the provided path. You gave {}, ya goober.'.format(ifile))

    filename = ifile.split('/')[-1]
    print 'Loading input file...', filename

    columns = scaled_vars + selection_vars
    

    # read from TTrees into DataFrame
    input_df = read_root(ifile, columns=columns)
    input_df['idx'] = np.array([i for i in xrange(0, len(input_df))])

    # preselection
    slim_df = input_df[
#                (input_df['Pass'] > 0)  & (input_df['OS'] > 0)
                (input_df['lep2IsoPass'] > 0)
    #            (input_df['njets'] > 1) & (input_df['mjj'] > 300)
        ]
    

    slim_df = slim_df.dropna(axis=0, how='any')  # drop events with a NaN

    # get variables needed for selection (so they aren't normalized)
    selection_df = slim_df[selection_vars]
    # get just the weights (they are scaled differently)
    weights = slim_df['evtwt']
    index = slim_df['idx']
    todrop = ['evtwt','idx']
    slim_df = slim_df.drop(selection_vars+todrop, axis=1)



    isSignal = np.zeros(len(slim_df))
    isZTT = np.zeros(len(slim_df))

    if 'h125' in ifile.lower() or 'qqh' in ifile.lower() or 'wh' in ifile.lower() or 'zh' in ifile.lower() or 'ggh' in ifile.lower() or 'vbf' in ifile.lower():
        isSignal = np.ones(len(slim_df))
#    else 'ZTT' in ifile:
    else:
        isZTT = np.ones(len(slim_df))


    # save the name of the process
    somenames = np.full(len(slim_df), filename.split('.root')[0])

    # scale event weights between 1 - 2
    weights = MinMaxScaler(
        feature_range=(1., 2.)
    ).fit_transform(
        weights.values.reshape(-1, 1)
    )

    # get lepton channel
    lepton = np.full(len(slim_df), channel)

    return slim_df, selection_df, somenames, lepton, isSignal,isZTT,weights, index


def main(args):

    input_files = [ifile for ifile in glob('{}/*.root'.format(args.input_dir))]
#    input_files = [ifile for ifile in glob('{}/*.root'.format(args.mu_input_dir)) if args.mu_input_dir != None ]
#    input_files += [ifile for ifile in glob('{}/*.root'.format(args.el_input_dir)) if args.el_input_dir != None ]
#    input_files = [ifile for ifile in glob('{}/*.root'.format(args.lep_input_dir)) if args.lep_input_dir != None ]
    for ifile in input_files:
        print 'file is ', ifile
        
    # define collections that will all be merged in the end
    unscaled_data, selection_df = pd.DataFrame(), pd.DataFrame()
    names, leptons, isSignal,isZTT,weight_df, index = np.array(
        []), np.array([]), np.array([]), np.array([]), np.array([]), np.array([])

    for ifile in input_files:
        print 'file is ', ifile
        input_data, selection_data, new_name, lepton, sig,ztt, weight, idx = loadFile(
            ifile, args.category
        )
        # add data to the full set
        unscaled_data = pd.concat([unscaled_data, input_data])
        # add selection variables to full set
        selection_df = pd.concat([selection_df, selection_data])
        # insert the name of the current sample
        names = np.append(names, new_name)
        leptons = np.append(leptons, lepton)  # lepton channel
        isSignal = np.append(isSignal, sig)  # labels for signal/background
        isZTT = np.append(isZTT, ztt)  # labels for signal/background
        weight_df = np.append(weight_df, weight)  # weights scaled from 0 - 1
        index = np.append(index, idx)

    print "unscaled_data.values", unscaled_data.values
    # normalize the potential training variables
    scaled_data = pd.DataFrame(
        StandardScaler().fit_transform(unscaled_data.values),
        columns=unscaled_data.columns.values
    )

    # add selection variables
    for column in selection_df.columns:
        scaled_data[column] = selection_df[column].values

    # add other useful data
    scaled_data['sample_names'] = pd.Series(names)
    scaled_data['lepton'] = pd.Series(leptons)
    scaled_data['isSignal'] = pd.Series(isSignal)
    scaled_data['isZTT'] = pd.Series(isZTT)
    scaled_data['evtwt'] = pd.Series(weight_df)
    scaled_data['idx'] = pd.Series(index)

    # save the dataframe for later
    store = pd.HDFStore('datasets/{}.h5'.format(args.output))
    store['df'] = scaled_data


if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser()
    parser.add_argument('--el-input', '-e',  action='store',
                        dest='el_input_dir', default=None, help='path to etau input files')
    parser.add_argument('--mu-input', '-m',  action='store',
                        dest='mu_input_dir', default=None, help='path to mutau input files')
    parser.add_argument('-input', '-i',  action='store',
                        dest='input_dir', default=None, help='path to mutau input files')
    parser.add_argument('--l-input', '-l',  action='store',
                        dest='lep_input_dir', default=None, help='path to ltau input files')
    parser.add_argument('--output', '-o', action='store', dest='output',
                        default='store.h5', help='name of output file')
    parser.add_argument('--category', '-c', action='store', dest='category',
                        default='vbf', help='name of category for selection')

    main(parser.parse_args())
