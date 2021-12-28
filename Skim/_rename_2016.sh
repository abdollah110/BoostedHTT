dir=$1

#hadd  $dir/Data.root $dir/*Run*.root
hadd  $dir/DYJetsToLL_Pt-100To250.root $dir/DYJetsToLL_Pt-100To250_v*.root
hadd  $dir/DYJetsToLL_Pt-250To400.root  $dir/DYJetsToLL_Pt-250To400_v*.root
hadd  $dir/DYJetsToLL_Pt-400To650.root $dir/DYJetsToLL_Pt-400To650_v*.root
hadd  $dir/DYJetsToLL_Pt-50To100.root  $dir/DYJetsToLL_Pt-50To100_v*.root
hadd  $dir/DYJetsToLL_Pt-650ToInf.root  $dir/DYJetsToLL_Pt-650ToInf_v*.root
hadd $dir/VV2l2nu.root  $dir/VV2l2nu_v*.root
hadd $dir/WJetsToLNu_HT-100To200.root  $dir/WJetsToLNu_HT-100To200*.root
hadd $dir/WJetsToLNu_HT-1200To2500.root  $dir/WJetsToLNu_HT-1200To2500*.root
hadd $dir/WJetsToLNu_HT-200To400.root  $dir/WJetsToLNu_HT-200To400*.root
hadd $dir/WJetsToLNu_HT-2500ToInf.root  $dir/WJetsToLNu_HT-2500ToInf*.root
hadd $dir/WJetsToLNu_HT-400To600.root  $dir/WJetsToLNu_HT-400To600*.root
hadd $dir/WJetsToLNu_HT-600To800.root  $dir/WJetsToLNu_HT-600To800*.root
hadd $dir/WJetsToLNu_HT-800To1200.root  $dir/WJetsToLNu_HT-800To1200*.root
hadd $dir/QCD_HT300to500.root $dir/QCD_HT300to500_v*.root
hadd $dir/QCD_HT500to700.root $dir/QCD_HT500to700_v*.root
hadd $dir/QCD_HT1000to1500.root $dir/QCD_HT1000to1500_v*.root
hadd $dir/QCD_HT1500to2000.root $dir/QCD_HT1500to2000_v*.root
hadd $dir/QCD_HT2000toInf.root $dir/QCD_HT2000toInf_v*.root
hadd $dir/ggH125.root  $dir/GluGluHToTauTau*.root
mv $dir/VBFHToTauTau_M125.root   $dir/qqH125.root
mv $dir/WminusHToTauTau_M125.root   $dir/WMinusH125.root
mv $dir/WplusHToTauTau_M125.root   $dir/WPlusH125.root
mv $dir/ZHToTauTau_M125.root   $dir/ZH125.root
mv $dir/ggZHTT_ZLL_M125.root   $dir/ggZHLL125.root
mv $dir/ggZHTT_ZNuNu_M125.root   $dir/ggZHNuNu125.root
mv $dir/ggZHTT_ZQQ_M125.root   $dir/ggZHQQ125.root
mv $dir/ttHToTauTau_M125.root   $dir/toptopH125.root
echo 'Removing the following files' $dir/*_v1* $dir/*_v2* $dir/*_v3* $dir/*_v4*
rm $dir/*_v1* $dir/*_v2* $dir/*_v3* $dir/*_v4*


