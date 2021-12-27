############################################################
## Script to automate running an analyzer on all files in ##
## a directory.                                           ##
############################################################

from os import popen, makedirs, path
from pprint import pprint
from subprocess import call
import time
import multiprocessing
from glob import glob
from collections import defaultdict
from raw_condor_submit_analysis import submit_command

def getNames(sample):
    """Return the sample names and signal type."""
   if 'DYJets' in sample:
#        names = ['ZLL', 'ZTT','ZJ']
        names = ['ZTT']
    elif 'TT' in sample:
        names = ['TT']
    elif 'WJets' in sample or 'EWK' in sample:
        names = ['W']
    elif 'data' in sample.lower() or 'run' in sample.lower():
        names = ['data_obs']
    elif 'ggH125' in sample:
        names = ['ggH125']
    elif 'qqH125' in sample:
        names = ['qqH125']
    elif 'WPlusH125' in sample:
        names = ['WPlusH125']
    elif 'WMinusH125' in sample:
        names = ['WMinusH125']
    elif 'ZH125' in sample:
        names = ['ZH125']
    elif 'JJH' in sample or 'jjh' in sample:
        names = ['JJH']
    else:
        names = ['VV']

    signal_type = 'None'
    if 'JJH' in sample:
        signal_type = 'madgraph'
    elif '125' in sample:
        signal_type = 'powheg'

    return names, signal_type


def valid_sample(ifile):
    """Remove samples that aren't used any longer"""
#    invalid_samples = ['EWKZ', 'EWKW', 'WW.root', 'WZ.root', 'ZZ.root', 'ggh125_madgraph_inc', 'minlo']
    invalid_samples = ['minlo']
    for sample in invalid_samples:
        if sample in ifile:
            return False
    return True


def getSyst(name, signal_type, exe, doSyst, year):
    """Return the list of systematics to be processed for this sample.

    The list of systematics is built based on the process, signal type, and channel.
    All applicable systematics will be added to the list for processing.
    Arguments:
    name        -- name of the process
    signal_type -- signal type or None
    exe         -- name of the executable to determine the channel
    doSyst      -- if False, returns a list with just the nominal case
    Returns:
    systs       -- list of systematics to processes
    """
    systs = ['']

    # handle cases with no systematics
    if not doSyst or signal_type == 'minlo' or name == 'data_obs' or (
            name == 'TTJ' or name == 'VVJ' or name == 'STJ'):
        return systs


    systs += [
             'MissingEn_JESUp', 'MissingEn_JESDown', 'MissingEn_UESUp', 'MissingEn_UESDown', 'prefireUp', 'prefireDown',
#             'met_reso_Up', 'met_resp_Up','met_reso_Down', 'met_resp_Down'
              ]
              
    if name == 'TT':
        systs += ['ttbarShape_Up', 'ttbarShape_Down']

    if name == 'ZLL' or name == 'ZTT' or name == 'ZJ':
        systs += ['Z_masspt_Up', 'Z_masspt_Down']

    if name == 'W':
        systs += ['WBosonKFactorUp', 'WBosonKFactorDown']
        

    return systs


def run_command(cmd, q, parallel=False):
    """Run the provided command and write the output

    Arguments:
    cmd      -- the command to be run in the shell
    q        -- the writable object (must be a Queue if parallel is True)
    save_fcn -- are you running with multiprocessing? 
    """
    code = call(cmd, shell=True)
    message = ''
    if code != 0:
        message = '\033[91m[ERROR] returned non-zero exit code while running {}\033[0m'.format(cmd)
    else:
        message = '\033[92m[SUCCESS] {} completed successfully \033[0m'.format(cmd)

    # print message
    print message

    file_message = message[5:-5]  # strip colors off message for file
    q.put(message) if parallel else q.write(message + "\n")
    return None


def listener(q, fname):
    """Listen for messages on q then writes to file."""
    with open(fname, 'w') as f:
        while 1:
            m = q.get()
            if m == 'kill':
                f.write('killed')
                break
            f.write(str(m) + '\n')
            f.flush()


def build_processes(processes, callstring, names, signal_type, exe, output_dir, doSyst,year):
    """Create output directories and callstrings then add them to the list of processes."""
    for name in names:
        for isyst in getSyst(name, signal_type, exe, doSyst, year):
#            if isyst == "" and not path.exists('Output/trees/{}/NOMINAL'.format(output_dir)):
#                makedirs('Output/trees/{}/NOMINAL'.format(output_dir))
#            if isyst != "" and not path.exists('Output/trees/{}/SYST_{}'.format(output_dir, isyst)):
#                makedirs('Output/trees/{}/SYST_{}'.format(output_dir, isyst))
            if not path.exists('Output/trees/{}/SYST_{}'.format(output_dir, isyst)):
                makedirs('Output/trees/{}/SYST_{}'.format(output_dir, isyst))


            tocall = callstring + ' -n {}'.format(name) + year
            if isyst != "":
                tocall += ' -u {}'.format(isyst)

            processes.append(tocall)
    return processes


def run_parallel(output_dir, processes):
    """Run analyzer using multiprocessing."""
    manager = multiprocessing.Manager()
    q = manager.Queue()

    # Use 10 cores if the machine has more than 20 total cores.
    # Otherwise, use half the available cores.
    n_processes = min(10, multiprocessing.cpu_count() / 2)
    print 'Process with {} cores'.format(n_processes)
    pool = multiprocessing.Pool(processes=n_processes)
    watcher = pool.apply_async(listener, (q, 'Output/trees/{}/logs/runninglog.txt'.format(output_dir)))

    jobs = []
    for command in processes:
        job = pool.apply_async(run_command, (command, q, True))
        jobs.append(job)

    for job in jobs:
        job.get()

    q.put('kill')
    pool.close()
    pool.join()


def run_series(output_dir, processes):
    """Run analyzer on processes in series."""
    with open('Output/trees/{}/logs/runninglog.txt'.format(output_dir), 'w') as ifile:
        [run_command(command, ifile, False) for command in processes]


def main(args):
    """Build all processes and run them."""
    start = time.time()
    suffix = '.root'
    print '\n the path is {}\n'.format(args.path)
    fileList = [ifile for ifile in glob(args.path+'/*') if '.root' in ifile and valid_sample(ifile)]

    if args.condor:
        job_map = {}
        for ifile in fileList:
            print '\t\t\t\t ifile is {}'.format(ifile)
##            --------- FIXME -------------
#            inMyList = 'data' in ifile or 'embed' in ifile
#            if not inMyList: continue
##            --------- FIXME -------------
            print '\n the ifile is {}\n'.format(ifile)
            sample = ifile.split('/')[-1].split(suffix)[0]
#            tosample = ifile.replace(sample+suffix, '')
            tosample = ifile.replace(sample+suffix, '').replace('/hdfs', 'root://cmsxrootd.hep.wisc.edu:1094/')
            names, signal_type = getNames(sample)
            print names, signal_type ,sample
            file_map = defaultdict(list)
            for name in names:
                print '\n the name is {}\n'.format(name)
                systs = getSyst(name, signal_type, args.exe, args.syst, args.year)
                for syst in systs:
                    if syst == '':
                      syst = 'SYST_'+'NOMINAL'
                    else:
                      syst = 'SYST_' + syst
                    command = './{} -p {} -s {} -d ./ --stype {} -n {} -u {} -y {} --condor'.format(
                            args.exe, tosample, sample, signal_type,
                            name, syst.replace('SYST_', ''), args.year)

                    file_map[syst].append({
                        'path': tosample,
                        'sample': sample,
                        'name': name,
                        'command': command,
                        'signal_type': signal_type,
                        'syst': syst,
                    })

            job_map[sample] = file_map

        to_submit = []
        for sample, systs in job_map.iteritems():
            for syst, configs in systs.iteritems():
                for config in configs:
                    to_submit.append(config)
        submit_command(args.nfs_dir, args.output_dir, to_submit, False)
    else:
        try:
            makedirs('Output/trees/{}/logs'.format(args.output_dir))
        except:
            pass

        processes = []
        for ifile in fileList:
            sample = ifile.split('/')[-1].split(suffix)[0]
#            tosample = ifile.replace(sample+suffix, '')
            tosample = ifile.replace(sample+suffix, '').replace('/hdfs', 'root://cmsxrootd.hep.wisc.edu:1094/')

            names, signal_type = getNames(sample)
            # if signal_type != "None": continue
            callstring = './{} -p {} -s {} -d {} --stype {} -y {}'.format(args.exe,
                                                                     tosample, sample, args.output_dir, signal_type, args.year)

            doSyst = True if args.syst and not 'data' in sample.lower() else False
            processes = build_processes(processes, callstring, names, signal_type, args.exe, args.output_dir, doSyst, args.year)
        pprint(processes, width=150)

        if args.parallel:
            run_parallel(args.output_dir, processes)
        else:
            run_series(args.output_dir, processes)

        end = time.time()
        print 'Processing completed in', end-start, 'seconds.'


if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser()
    parser.add_argument('--exe', '-e', required=True, help='name of executable')
    parser.add_argument('--syst', action='store_true', help='run systematics as well')
    parser.add_argument('--path', '-p', required=True, help='path to input file directory')
    parser.add_argument('--parallel', action='store_true', help='run in parallel')
    parser.add_argument('--output-dir', required=True, dest='output_dir',
                        help='name of output directory after Output/trees')
    parser.add_argument('--condor', action='store_true', help='submit jobs to condor')
    parser.add_argument('--year','-y', action='store', dest='year', help='Which year')
    parser.add_argument('--nfs', action='store', dest='nfs_dir', help='Which year')
    


    main(parser.parse_args())
