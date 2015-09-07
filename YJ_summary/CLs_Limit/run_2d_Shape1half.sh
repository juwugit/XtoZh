
xmass=900 
rm -rf *Testing_0819*.txt
rm -rf *_${xmass}*.root
rm -rf *output_0819*.root
rm -rf Shape1d_0819.root
root -b -l -q ProjectHistograms_YJ.C+\(\"../result_cuts/ZPrime_ZH_lljj_M${xmass}_El_Cen.root\"\)
root -b -l -q Change_data_obs_name.C+
python MakeDataCardsYJ.py