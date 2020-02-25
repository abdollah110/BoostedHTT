./build process_trees_Tot.cc out
./out -d TestOut2 -t mutau_tree --suf ZMass -y 2017
python autoplot.py -i Output/templates/mt2017_ZMass.root -p mass -y 2017 -c mt
