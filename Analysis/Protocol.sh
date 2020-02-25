python automate_analysis.py -e BoostedHTT2017_mt.exe -p /eos/uscms/store/user/abdollah/SkimBoost/mt/v6_Hadd/ -P XXX -o newtest_data_includeHiggs
./build process_trees_Tot.cc out
./out -d TestOut2 -t mutau_tree --suf ZMass -y 2017
python autoplot.py -i Output/templates/mt2017_ZMass.root -p mass -y 2017 -c mt
