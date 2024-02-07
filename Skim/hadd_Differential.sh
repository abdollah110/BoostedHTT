dir=$1
year=$2

echo "directory is " $1 "  and year is " $2

hadd ggH_htt125_$2.root $dir/GluGluHToTauTau*root
hadd qqH_htt125_$2.root $dir/VBFHToTauTau_M125*root
hadd WH_htt125_$2.root $dir/WplusHToTauTau_M125*root $dir/WminusHToTauTau_M125*root
hadd ZH_htt125_$2.root $dir/ZHToTauTau_M125*root
hadd ggZH_lep_htt125_$2.root $dir/ggZHTT_ZLL_M125*root $dir/ggZHTT_ZNuNu_M125*root
hadd ggZH_had_htt125_$2.root $dir/ggZHTT_ZQQ_M125*root
hadd ttH_htt125_$2.root $dir/ttHToTauTau_M125*root




hadd -f ggH_htt125.root ggH_htt125_*.root
hadd -f qqH_htt125.root qqH_htt125_*.root
hadd -f WH_htt125.root WH_htt125_*.root
hadd -f ZH_htt125.root ZH_htt125_*.root
hadd -f ggZH_lep_htt125.root ggZH_lep_htt125_*.root
hadd -f ggZH_had_htt125.root ggZH_had_htt125_*.root
hadd -f ttH_htt125.root ttH_htt125_*.root

