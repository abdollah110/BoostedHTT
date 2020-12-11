dir=$1

#hadd $dir/Data.root $dir/SingleMuon*root
hadd $dir/TTToHadronic.root          $dir/TTToHadronic_*.root
hadd $dir/TTToSemiLeptonic.root          $dir/TTToSemiLeptonic_*.root
hadd $dir/WZ1l1nu2q.root          $dir/WZ1l1nu2q_*root
hadd $dir/WZ3l1nu.root          $dir/WZ3l1nu_*root
hadd $dir/ZZ2l2q.root          $dir/ZZ2l2q_*root
mv $dir/GluGluHToTauTau_M125.root $dir/ggH125.root
mv $dir/VBFHToTauTau_M125.root   $dir/qqH125.root
mv $dir/WminusHToTauTau_M125.root   $dir/WMinusH125.root
mv $dir/WplusHToTauTau_M125.root   $dir/WPlusH125.root
mv $dir/ZHToTauTau_M125.root   $dir/ZH125.root
echo 'Removing the following files' $dir/*_v* $dir/*-v*
rm $dir/*_v*  $dir/*-v*
