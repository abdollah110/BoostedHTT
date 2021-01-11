dir=$1

hadd  $dir/Data.root $dir/*Run*.root
hadd  $dir/DYJetsToLL_Pt-100To250.root $dir/DYJetsToLL_Pt-100To250_v*.root
hadd  $dir/DYJetsToLL_Pt-250To400.root  $dir/DYJetsToLL_Pt-250To400_v*.root
hadd  $dir/DYJetsToLL_Pt-400To650.root $dir/DYJetsToLL_Pt-400To650_v*.root
hadd  $dir/DYJetsToLL_Pt-50To100.root  $dir/DYJetsToLL_Pt-50To100_v*.root
hadd  $dir/DYJetsToLL_Pt-650ToInf.root  $dir/DYJetsToLL_Pt-650ToInf_v*.root
hadd $dir/VV2l2nu.root  $dir/VV2l2nu_v*.root
hadd $dir/WJetsToLNu_Pt-100To250.root   $dir/WJetsToLNu_Pt-100To250_v*.root
hadd $dir/WJetsToLNu_Pt-250To400.root  $dir/WJetsToLNu_Pt-250To400_v*.root
hadd $dir/WJetsToLNu_Pt-400To600.root $dir/WJetsToLNu_Pt-400To600_v*.root
hadd $dir/WJetsToLNu_Pt-600ToInf.root  $dir/WJetsToLNu_Pt-600ToInf_v*.root
mv $dir/jjh_0j_a1_madgraph.root $dir/JJH0PMToTauTauPlusZeroJets.root
mv $dir/jjh_1j_a1_madgraph.root $dir/JJH0PMToTauTauPlusOneJets.root
mv $dir/jjh_2j_a1_madgraph.root $dir/JJH0PMToTauTauPlusTwoJets.root
hadd $dir/ggH125.root  $dir/GluGluHToTauTau*.root
mv $dir/VBFHToTauTau_M125.root   $dir/qqH125.root
mv $dir/WminusHToTauTau_M125.root   $dir/WMinusH125.root
mv $dir/WplusHToTauTau_M125.root   $dir/WPlusH125.root
mv $dir/ZHToTauTau_M125.root   $dir/ZH125.root
echo 'Removing the following files' $dir/*_v*
rm $dir/*_v* $dir/*Run*.root 

