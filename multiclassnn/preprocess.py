import sys
import math
import pandas as pd
import numpy as np
from glob import glob
from sklearn.preprocessing import StandardScaler, MinMaxScaler

# Variables used for selection. These shouldn't be normalized
selection_vars = [
#                  'lep2IsoPass',
]

# Variables that could be used as NN input. These should be normalized
scaled_vars = [
               'evtwt','lep1Pt','lep2Pt','Met','m_sv', 'LeadJetPt','higgs_m','higgs_pT','st','tmass'
#               'evtwt','lep1Pt','lep2Pt','Met', 'LeadJetPt','higgs_m','higgs_pT','st','tmass'
               ]


def apply_selection(df):
    """Apply basic preselection and clean some variables."""
    # preselection
    slim_df = df

#    # make sure our DataFrame is actually reasonable
#    slim_df = slim_df.dropna(axis=0, how='any')  # drop events with a NaN
#    slim_df = slim_df.drop_duplicates()
#    slim_df = slim_df[(slim_df['Q2V1'] > -1e10) & (slim_df['Q2V1'] < 1e10)]
#    slim_df = slim_df[(slim_df['Q2V2'] > -1e10) & (slim_df['Q2V2'] < 1e10)]
#    slim_df = slim_df[(slim_df['Phi0'] > -2.1 * math.pi) & (slim_df['Phi0']
#                                                           < 2.1 * math.pi)]  # gave this a little wiggle room
#    slim_df = slim_df[(slim_df['Phi1'] > -2.1 * math.pi) & (slim_df['Phi1'] < 2.1 * math.pi)]
#    slim_df = slim_df[(slim_df['costheta1'] > -1) & (slim_df['costheta1'] < 1)]
#    slim_df = slim_df[(slim_df['costheta2'] > -1) & (slim_df['costheta2'] < 1)]
#    slim_df = slim_df[(slim_df['costhetastar'] > -1) & (slim_df['costhetastar'] < 1)]

    return slim_df


def get_Traininglabels(nevents, name):
    """Label events as sig vs ZTT v.s QCD"""
    
    print 'name is {}'.format(name)
    
    isSignal = np.zeros(nevents)
    isZTT = np.zeros(nevents)
    isQCD = np.zeros(nevents)
    if 'qqh' in name or 'wh' in name or 'zh' in name or 'ggh' in name or 'vbf' in name or 'xh' in name or 'jjh' in name:
        isSignal = np.ones(nevents)
    elif 'ztt' in name:
        isZTT = np.ones(nevents)
    else :
        isQCD = np.ones(nevents)
    
    return isSignal, isZTT, isQCD


def get_labels(nevents, name):
    """Label events as SM vs non-SM."""

    # get scaling label
    isSM = np.ones(nevents)
    if 'qqh' in name or 'wh' in name or 'zh' in name or 'ggh' in name or 'vbf' in name or 'xh' in name or 'jjh' in name:
        isSM = np.zeros(nevents)
    if 'data' in name:
        isSM = np.zeros(nevents)
    if 'ggh' in name and ('up' in name or 'down'  in name):
        isSM = np.ones(nevents)
    if 'jjh' in name and ('up' in name or 'down'  in name):
        isSM = np.ones(nevents)
    if 'vbf' in name and ('up' in name or 'down'  in name):
        isSM = np.ones(nevents)
    return isSM


def build_scaler(sm_only):
    """Fit to SM only then build DataFrame with all info to store in output file."""
    scaler = StandardScaler()
    # only fit the nominal backgrounds
    scaler.fit(sm_only.values)
    scaler_info = pd.DataFrame.from_dict({
        'mean': scaler.mean_,
        'scale': scaler.scale_,
        'variance': scaler.var_,
        'nsamples': scaler.n_samples_seen_
    })
    scaler_info.set_index(sm_only.columns.values, inplace=True)
    return scaler, scaler_info


def format_for_store(all_data, scaler):
    """Take the DataFrame and format it for storage."""
    formatted_data = pd.DataFrame(
        scaler.transform(all_data.values),
        columns=all_data.columns.values, dtype='float64')
    return formatted_data


def loadFile(ifile):
    from root_pandas import read_root

    if 'mutau' in ifile or '_mt_' in ifile:
        channel = 'mt'
    elif 'etau' in ifile or '_et_' in ifile:
        channel = 'et'
    elif 'emu' in ifile or '_em_' in ifile:
        channel = 'em'
    elif 'mue' in ifile or '_me_' in ifile:
        channel = 'me'
    elif 'tautau' in ifile or '_tt_' in ifile:
        channel = 'tt'
    else:
        raise Exception(
            'Input files must have MUTAU or ETAU, EMU, MUE or TauTau in the provided path. You gave {}, ya goober.'.format(ifile))
    
    print 'identified channel is {}'.format(channel)
    
    filename = ifile.split('/')[-1]
    print 'Loading input file...', filename

    columns = scaled_vars + selection_vars
    todrop = ['evtwt', 'idx']

    # read from TTrees into DataFrame
    input_df = read_root(ifile, columns=columns)
    input_df['idx'] = np.array([i for i in xrange(0, len(input_df))])
    
    slim_df = apply_selection(input_df)
    
    slim_df = slim_df.dropna(axis=0, how='any')  # drop events with a NaN
    # get variables needed for selection (so they aren't normalized)
    selection_df = slim_df[selection_vars]
    # get just the weights (they are scaled differently)
    weights = slim_df['evtwt']
    index = slim_df['idx']
#    if '_qqH_inc' in ifile:
#        weights = weights * slim_df['wt_a1']
    slim_df = slim_df.drop(selection_vars+todrop, axis=1)
    
    # add the training label
    isSignal, isZTT, isQCD = get_Traininglabels(len(slim_df), ifile.lower())
    
    # add the event label
    isSM = get_labels(len(slim_df), ifile.lower())
    slim_df['isSM'] = isSM
    
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

    return slim_df, selection_df, somenames, lepton, isSignal,isQCD, isZTT,weights, index

        
def main(args):

    input_files = [ifile for ifile in glob('{}/*.root'.format(args.input_dir))]
    for ifile in input_files:
        print 'file is ', ifile

    
#    input_files = [ifile for ifile in glob('{}/*.root'.format(args.input_dir)) if args.input_dir != None ]

    # create the store
    store = pd.HDFStore('datasets/{}.h5'.format(args.output),
                        complevel=9, complib='bzip2')
                        
    # define collections that will all be merged in the end
    unscaled_data, selection_df = pd.DataFrame(), pd.DataFrame()
    names, leptons, isSignal, isQCD,isZTT,weight_df, index = np.array(
        []), np.array([]), np.array([]), np.array([]), np.array([]), np.array([]), np.array([])


    for ifile in input_files:
        input_data, selection_data, new_name, lepton, sig,qcd,ztt, weight, idx = loadFile(ifile)
        print 'now checking {} out '.format(ifile)
        # add data to the full set
        unscaled_data = pd.concat([unscaled_data, input_data])
        # add selection variables to full set
        selection_df = pd.concat([selection_df, selection_data])
        # insert the name of the current sample
        names = np.append(names, new_name)
        isSignal = np.append(isSignal, sig)  # labels for signal/background
        isQCD = np.append(isQCD, qcd)  # labels for signal/background
        isZTT = np.append(isZTT, ztt)  # labels for signal/background
        weight_df = np.append(weight_df, weight)  # weights scaled from 0 - 1
        leptons = np.append(leptons, lepton)  # lepton channel
        index = np.append(index, idx)


    # build the scaler fit only to nominal SM backgrounds
    sm_only = unscaled_data[unscaled_data['isSM'] == 1]
    scaler, store['scaler'] = build_scaler(sm_only)


    scaled_data = pd.DataFrame()
    
    if args.Transform:
        # normalize the potential training variables
        print '\n The features will be scaled and transformed. Note: This should be used for Training NN'
        scaled_data= format_for_store(unscaled_data, scaler)

    else:
        # Just add the unscaled features to scaled data frame
        print '\n The features will NOT be transformed'
        for column in unscaled_data.columns:
            scaled_data[column] = unscaled_data[column].values

    # add selection variables
    for column in selection_df.columns:
        scaled_data[column] = selection_df[column].values


    # add other useful data
    scaled_data['sample_names'] = pd.Series(names)
    scaled_data['lepton'] = pd.Series(leptons)
    scaled_data['isSignal'] = pd.Series(isSignal)
    scaled_data['isQCD'] = pd.Series(isQCD)
    scaled_data['isZTT'] = pd.Series(isZTT)
    scaled_data['evtwt'] = pd.Series(weight_df)
    scaled_data['idx'] = pd.Series(index)

    store['df'] = scaled_data



if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser()
    parser.add_argument('-input', '-i',  action='store',
                        dest='input_dir', default=None, help='path to mutau input files')
    parser.add_argument('--output', '-o', action='store', dest='output',
                        default='store.h5', help='name of output file')
#    parser.add_argument('--em-input', '-em', action='store',
#                        dest='input_dir', default=None, help='path to emu input files')
#    parser.add_argument('--output', '-o', action='store', dest='output',
#                        default='store.h5', help='name of output file')
#    parser.add_argument('--category', '-c', action='store', dest='category',
#                        default='vbf', help='name of category for selection')
    parser.add_argument('--Transform', '-s', action='store', dest='Transform',
                        default=False, help='Trasnform the features or not')

    main(parser.parse_args())
