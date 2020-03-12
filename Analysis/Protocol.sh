python automate_analysis.py -e BoostedHTT2017_mt.exe -p /eos/uscms/store/user/abdollah/SkimBoost/mt/v6_Hadd/ -P XXX -o newtest_data_includeHiggs
./build process_trees_Tot.cc out
./out -d TestOut2 -t mutau_tree --suf ZMass -y 2017 -o vis_mass
python autoplot.py -i Output/templates/mt2017_ZMass.root -p mass -y 2017 -c mt

python xrun.py -i NewAnalysis_v2 -y 2017
python autoplot.py -i Output/templates/mt2017_vis_mass.root -y 2017 -p test -c mt
