from sklearn.model_selection import train_test_split
from os import environ
environ['KERAS_BACKEND'] = 'tensorflow'
from keras.callbacks import ModelCheckpoint, EarlyStopping
from keras.layers import Dense, Dropout
from keras.models import Sequential
from keras import optimizers
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from visualize import *

def main(args):
    data = pd.HDFStore(args.input)['df']
    ## define training variables
    training_variables = [
                    'lep1Pt','lep2Pt','Met','m_sv', 'LeadJetPt','higgs_m','higgs_pT','st','tmass'
#                    'lep1Pt','lep2Pt','Met', 'LeadJetPt','higgs_m','higgs_pT','st','tmass'
    ]

    nvars = len(training_variables)

    model = Sequential()
    model.add(Dense(nvars*2, input_shape=(nvars,), name='input', activation='relu'))
    model.add(Dense(nvars, name='hidden', activation='relu'))
    model.add(Dense(3, activation='softmax', kernel_initializer='glorot_normal')) # change sigmoid to softmax for multiNN
    model.summary()
    model.compile(optimizer='adam', loss='categorical_crossentropy',
                metrics=['accuracy'])

    ## build callbacks
    callbacks = [
        EarlyStopping(monitor='val_loss', patience=50),
        ModelCheckpoint('models/{}.hdf5'.format(args.model), monitor='val_loss',
                        verbose=0, save_best_only=True,
                        save_weights_only=False, mode='auto',
                        period=1
                        )
    ]

    ## get the data for the two-classes to discriminate
    training_processes = data[
        (data['sample_names'] == args.signal) | (data['sample_names'] == args.background) | (data['sample_names'] == args.background2)
    ]

    ## apply VBF category selection
    boost_processes = training_processes[
        (training_processes['is_signal'] > 0) &
        (training_processes['OS'] > 0)
        ]

    print 'No. Signal Events:     {}'.format(len(boost_processes[boost_processes['sample_names'] == args.signal]))
    print 'No. Background Events: {}'.format(len(boost_processes[boost_processes['sample_names'] == args.background]))
    print 'No. Background2 Events:{}'.format(len(boost_processes[boost_processes['sample_names'] == args.background2]))


    etau   = boost_processes[(boost_processes['lepton'] == 'et')]
    mutau  = boost_processes[(boost_processes['lepton'] == 'mt')]
    emu  = boost_processes[(boost_processes['lepton'] == 'em')]
    mue  = boost_processes[(boost_processes['lepton'] == 'me')]
    tautau  = boost_processes[(boost_processes['lepton'] == 'tt')]
    

    ## do event selection
    selected_mt = pd.DataFrame()
    selected_et = pd.DataFrame()
    selected_em = pd.DataFrame()
    selected_me = pd.DataFrame()
    selected_tt = pd.DataFrame()
    combine= pd.DataFrame()

    ## electron-tau channel selection (all in boost_process for now)
    if len(etau) > 0:
        selected_et = etau
        print '\n\nchannel is etau'
        combine = pd.concat([selected_et])
        
    ## muon-tau channel selection (all in boost_process for now)
    if len(mutau) > 0:
        selected_mt = mutau
        print '\n\nchannel is mutau'
        combine = pd.concat([selected_mt])


    if len(emu) > 0:
        selected_em = emu
        print '\n\nchannel is emu'
        combine = pd.concat([selected_em])

    if len(mue) > 0:
        selected_me = mue
        print '\n\nchannel is mue'
        combine = pd.concat([selected_me])


    if len(tautau) > 0:
        selected_tt = tautau
        print '\n\nchannel is tautau'
        combine = pd.concat([selected_tt])
        
        
#
#    ## do event selection
##    selected_et, selected_mt = pd.DataFrame(), pd.DataFrame()
#    selected_em = pd.DataFrame(), pd.DataFrame()
#
#    ## electron-tau channel selection (all in vbf_process for now)
##    if len(etau) > 0:
##        selected_et = etau
#
#    ## muon-tau channel selection (all in vbf_process for now)
##    if len(mutau) > 0:
##        selected_mt = mutau
#
#    ## muon-tau channel selection (all in vbf_process for now)
#    if len(emu) > 0:
#        selected_em = emu
#

    ## combine channels into total dataset
#    combine = pd.concat([selected_et, selected_mt])
#    combine = pd.concat([selected_em])


    sig_df = combine[(combine['sample_names'] == args.signal)]
    bkg_df = combine[(combine['sample_names'] == args.background)]
    bkg_df2 = combine[(combine['sample_names'] == args.background2)]


    print "len(sig_df), len(bkg_df), len(bkg_df2))", len(sig_df), len(bkg_df), len(bkg_df2)
    highest = max(len(sig_df), len(bkg_df), len(bkg_df2))
    sig_df.loc[:, 'evtwt'] = sig_df['evtwt'].apply(lambda x: x*highest/len(sig_df)).values
    bkg_df.loc[:, 'evtwt'] = bkg_df['evtwt'].apply(lambda x: x*highest/len(bkg_df)).values
    bkg_df2.loc[:, 'evtwt'] = bkg_df2['evtwt'].apply(lambda x: x*highest/len(bkg_df2)).values
    
#    if '2016' in args.year:
#        bkg_df2.loc[:, 'evtwt'] = bkg_df2['evtwt'].apply(lambda x: 0.025*highest/len(bkg_df2)).values # scale to get correct TT/ZTT
#    elif '2017' in args.year:
#        bkg_df2.loc[:, 'evtwt'] = bkg_df2['evtwt'].apply(lambda x: 0.056*highest/len(bkg_df2)).values # scale to get correct TT/ZTT
#    elif '2018' in args.year:
#        bkg_df2.loc[:, 'evtwt'] = bkg_df2['evtwt'].apply(lambda x: 0.365*highest/len(bkg_df2)).values # scale to get correct TT/ZTT
#    else:
#        print 'not valid year'


    selected_events = pd.concat([sig_df, bkg_df, bkg_df2])


    ## remove all columns except those needed for training
    training_dataframe = selected_events[training_variables + ['isSignal','isQCD','isZTT', 'evtwt']]
    
    training_data, testing_data, training_meta, testing_meta, training_weights, testing_weights  = train_test_split(
        training_dataframe[training_variables].values, training_dataframe[['isSignal','isQCD','isZTT']].values, training_dataframe['evtwt'].values,
        test_size=0.1, random_state=7
        )

    ## train that there model, my dude
    history = model.fit(training_data, training_meta, shuffle=True,
                        epochs=10000, batch_size=1024, verbose=True,
                        callbacks=callbacks, validation_split=0.25, sample_weight=training_weights
                        )

    if not args.dont_plot:
#        ROC_curve(training_data, training_labels, training_weights, model, 'ROC_training_{}'.format(args.model), 'red')
#        ROC_curve(testing_data, testing_labels[:], testing_weights[:], model, 'ROC_testing_{}'.format(args.model), 'cyan')




        test_sig, test_tt, test_ztt = [], [], []
        for i in range(len(testing_meta)):
            if testing_meta[i, 0] == 1:
                test_sig.append(testing_data[i, :])
            elif testing_meta[i, 1] == 1:
                test_tt.append(testing_data[i, :])
            elif testing_meta[i, 2] == 1:
                test_ztt.append(testing_data[i, :])

        train_sig, train_tt, train_ztt = [], [], []
        for i in range(len(training_meta)):
            if training_meta[i, 0] == 1:
                train_sig.append(training_data[i, :])
            elif training_meta[i, 1] == 1:
                train_tt.append(training_data[i, :])
            elif training_meta[i, 2] == 1:
                train_ztt.append(training_data[i, :])



        trainingPlots(history, 'trainingPlot_{}'.format(args.model))

#        test_sig, test_tt = [], []
#        for i in range(len(testing_labels)):
#            if testing_labels[i] == 1:
#                test_sig.append(testing_data[i, :])
#            elif testing_labels[i] == 0:
#                test_tt.append(testing_data[i, :])
#
#        train_sig, train_tt = [], []
#        for i in range(len(training_labels)):
#            if training_labels[i] == 1:
#                train_sig.append(training_data[i, :])
#            elif training_labels[i] == 0:
#                train_tt.append(training_data[i, :])

#        discPlot('NN_disc_{}'.format(args.model), model, np.array(train_sig), np.array(train_tt), np.array(test_sig), np.array(test_tt))


        discPlot('NN_sig_{}_vbf_ztt'.format(args.model), model, np.array(train_sig), np.array(train_ztt), np.array(test_sig), np.array(test_ztt))
        discPlot('NN_sig_{}_vbf_tt'.format(args.model), model, np.array(train_sig), np.array(train_tt), np.array(test_sig), np.array(test_tt))
        discPlot('NN_sig_{}_ztt_tt'.format(args.model), model, np.array(train_ztt), np.array(train_tt), np.array(test_ztt), np.array(test_tt))
        discPlot('NN_bkg_{}_vbf_ztt'.format(args.model), model, np.array(train_sig), np.array(train_ztt), np.array(test_sig), np.array(test_ztt))
        discPlot('NN_bkg_{}_vbf_tt'.format(args.model), model, np.array(train_sig), np.array(train_tt), np.array(test_sig), np.array(test_tt))
        discPlot('NN_bkg_{}_ztt_tt'.format(args.model), model, np.array(train_ztt), np.array(train_tt), np.array(test_ztt), np.array(test_tt))
        discPlot('NN_tt_{}_vbf_ztt'.format(args.model), model, np.array(train_sig), np.array(train_ztt), np.array(test_sig), np.array(test_ztt))
        discPlot('NN_tt_{}_vbf_tt'.format(args.model), model, np.array(train_sig), np.array(train_tt), np.array(test_sig), np.array(test_tt))
        discPlot('NN_tt_{}_ztt_tt'.format(args.model), model, np.array(train_ztt), np.array(train_tt), np.array(test_ztt), np.array(test_tt))



if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser()
    parser.add_argument('--model', '-m', action='store', dest='model', default='testModel', help='name of the model to train')
    parser.add_argument('--input', '-i', action='store', dest='input', default='test', help='full name of input file')
    parser.add_argument('--signal', '-s', action='store', dest='signal', default='VBF125.root', help='name of signal file')
    parser.add_argument('--background', '-b', action='store', dest='background', default='TT.root', help='name of background file')
    parser.add_argument('--background2', '-b2', action='store', dest='background2', default='ZTT.root', help='name of background file')
    parser.add_argument('--dont-plot', action='store_true', dest='dont_plot', help='don\'t make training plots')
    parser.add_argument('--category', '-c', action='store', dest='category', default='vbf', help='category to train')
    parser.add_argument('--year', '-y', action='store', dest='year', default='2018', help='which year')
    main(parser.parse_args())

#    parser.add_argument('--model', '-m', action='store', dest='model', default='testModel', help='name of the model to train')
#    parser.add_argument('--input', '-i', action='store', dest='input', default='test', help='full name of input file')
#    parser.add_argument('--signal', '-s', action='store', dest='signal', default='boost125.root', help='name of signal file')
#    parser.add_argument('--ZTT', '-b', action='store', dest='ZTT', default='ZTT.root', help='name of ZTT file')
#    parser.add_argument('--QCD', '-q', action='store', dest='QCD', default='QCD.root', help='name of QCD file')
##    parser.add_argument('--ZTT2', '-b2', action='store', dest='ZTT2', default='ZTT.root', help='name of ZTT file')
#    parser.add_argument('--dont-plot', action='store_true', dest='dont_plot', help='don\'t make training plots')
#    parser.add_argument('--category', '-c', action='store', dest='category', default='boost', help='category to train')
#    parser.add_argument('--year', '-y', action='store', dest='year', default='2018', help='which year')
