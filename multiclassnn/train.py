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
                    'muPt','taupt','lepIso','tmass', 'ht','Met','LeadJetPt', 'dR_mu_tau', 'ZMass','Pass'
    ]

    nvars = len(training_variables)

    model = Sequential()
    model.add(Dense(nvars*2, input_shape=(nvars,), name='input', activation='relu'))
    # model.add(Dropout(0.1))
    model.add(Dense(nvars, name='hidden', activation='relu', kernel_initializer='normal'))
    model.add(Dense(1, name='output', activation='sigmoid', kernel_initializer='normal'))
    model.summary()
    model.compile(optimizer='adam', loss='binary_crossentropy',
                metrics=['accuracy'])

    ## build callbacks
    callbacks = [
        EarlyStopping(monitor='val_loss', patience=50),
        ModelCheckpoint('models/{}.hdf5'.format(args.model), monitor='val_loss',
                        verbose=0, save_best_only=True,
                        save_weights_only=False, mode='auto',
                        period=1
                        )
#        TensorBoard(log_dir="logs/{}".format(time()), histogram_freq=200, write_grads=False, write_images=True)
    ]

    ## get the data for the two-classes to discriminate
    training_processes = data[
        (data['sample_names'] == args.signal) | (data['sample_names'] == args.background)
    ]

    ## apply VBF category selection
    vbf_processes = training_processes

    print 'No. Signal Events:     {}'.format(len(vbf_processes[vbf_processes['sample_names'] == args.signal]))
    print 'No. Background Events: {}'.format(len(vbf_processes[vbf_processes['sample_names'] == args.background]))

#    etau   = vbf_processes[(vbf_processes['lepton'] == 'et')]
    mutau  = vbf_processes[(vbf_processes['lepton'] == 'mt')]


    ## do event selection
    selected_mt = pd.DataFrame()

    ## electron-tau channel selection (all in vbf_process for now)
#    if len(etau) > 0:
#        selected_et = etau

    ## muon-tau channel selection (all in vbf_process for now)
    if len(mutau) > 0:
        selected_mt = mutau
    

    ## combine channels into total dataset
#    combine = pd.concat([selected_et, selected_mt])
    combine = pd.concat([selected_mt])
#    print 'combine is ', combine
    sig_df = combine[(combine['sample_names'] == args.signal)]
    bkg_df = combine[(combine['sample_names'] == args.background)]

    ## reweight to have equal events per class
    scaleto = max(len(sig_df), len(bkg_df))
    sig_df.loc[:, 'evtwt'] = sig_df['evtwt'].apply(lambda x: x*scaleto/len(sig_df))
    bkg_df.loc[:, 'evtwt'] = bkg_df['evtwt'].apply(lambda x: x*scaleto/len(bkg_df))
    selected_events = pd.concat([sig_df, bkg_df])



    ## remove all columns except those needed for training
    training_dataframe = selected_events[training_variables + ['isSignal', 'evtwt']]
    
    training_data, testing_data, training_labels, testing_labels, training_weights, testing_weights  = train_test_split(
        training_dataframe[training_variables].values, training_dataframe['isSignal'].values, training_dataframe['evtwt'].values,
        test_size=0.05, random_state=7
    )


    print "training_data \n\n\n\n",len(training_data), "  and , ", training_data
    print "training_labels \n\n\n\n",len(training_labels), "  and , ", training_labels
    print "training_weights \n\n\n\n",len(training_weights), "  and , ", training_weights
    
    ## train that there model, my dude
    history = model.fit(training_data, training_labels, shuffle=True,
                        epochs=10000, batch_size=1024, verbose=True,
                        callbacks=callbacks, validation_split=0.25, sample_weight=training_weights
                        )

    if not args.dont_plot:
#        ROC_curve(training_data, training_labels, training_weights, model, 'ROC_training_{}'.format(args.model), 'red')
#        ROC_curve(testing_data, testing_labels[:], testing_weights[:], model, 'ROC_testing_{}'.format(args.model), 'cyan')




        test_sig,  test_bkg = [], []
        for i in range(len(testing_labels)):
            if testing_labels[i] == 1:
                test_sig.append(testing_data[i, :])
            elif testing_labels[i] == 0:
                test_bkg.append(testing_data[i, :])

        train_sig,  train_bkg = [], []
        for i in range(len(training_labels)):
            if training_labels[i] == 1:
                train_sig.append(training_data[i, :])
            elif training_labels[i] == 0:
                train_bkg.append(training_data[i, :])

        discPlot('NN_disc_{}'.format(args.model), model, np.array(train_sig),
                  np.array(train_bkg), np.array(test_sig), np.array(test_bkg))
                  

        trainingPlots(history, 'trainingPlot_{}'.format(args.model))


if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser()
    parser.add_argument('--model', '-m', action='store', dest='model', default='testModel', help='name of the model to train')
    parser.add_argument('--input', '-i', action='store', dest='input', default='test', help='full name of input file')
    parser.add_argument('--signal', '-s', action='store', dest='signal', default='VBF125.root', help='name of signal file')
    parser.add_argument('--background', '-b', action='store', dest='background', default='TT.root', help='name of background file')
#    parser.add_argument('--background2', '-b2', action='store', dest='background2', default='ZTT.root', help='name of background file')
    parser.add_argument('--dont-plot', action='store_true', dest='dont_plot', help='don\'t make training plots')
    parser.add_argument('--category', '-c', action='store', dest='category', default='vbf', help='category to train')
    parser.add_argument('--year', '-y', action='store', dest='year', default='2018', help='which year')
    main(parser.parse_args())
