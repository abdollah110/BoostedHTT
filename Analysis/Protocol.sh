##Running analysis

#complie the code
./Make.sh BoostedHTT2017_mt.cc
# Run the executable
python automate_analysis.py -e BoostedHTT2017_mt.exe -p /eos/uscms/store/user/abdollah/SkimBoost/mt/v6_Hadd/ -P muTau2017 -o newtest_data_includeHiggs

#To make control plots
# first compile the .cc file
./build process_trees_lt.cc process_trees_lt
# Then run the executable
./process_trees_lt -d TestOut2 -t mutau_tree --suf ZMass -y 2017 -o vis_mass
# Make plots
python autoplot.py -i Output/templates/mt2017_ZMass.root -p mass -y 2017 -c mt

#python xrun.py -i NewAnalysis_v2 -y 2017
#python autoplot.py -i Output/templates/mt2017_m_sv.root -y 2017 -p test -c mt
