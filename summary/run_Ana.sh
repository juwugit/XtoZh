# $1 = El/Mu ; lepton channel
# $2 = Cen/Up/Down ; JetEnScale
# example: $sh run_Ana.sh El Cen

rm -rf Bkg_estimation/*$1_$2.root
hadd Bkg_estimation/Total_data_$1_$2.root result_cuts/data*_$1_$2.root
hadd Bkg_estimation/Total_MCBKG_$1_$2.root result_cuts/TH2*_$1_$2.root


# create DY template
root -b -l -q Bkg_estimation/mergeDYJets.C++\(\"result_cuts/TH2_DYJetsPtZ70To100_$1_$2.root\"\,\"result_cuts/TH2_DYJetsPtZ100_$1_$2.root\"\,\"Bkg_estimation/Total_DYJets_$1_$2.root\"\)


# data sb to signal corrrection
root -b -l -q Bkg_estimation/bkg_estimate_TH2.C++\(\"Bkg_estimation/Total_data_$1_$2.root\"\,\"Bkg_estimation/Total_DYJets_$1_$2.root\"\,\"h_alphaMxCA8jetCSV\"\,\"h_sbMxCA8jetCSV\"\)
root -b -l -q Bkg_estimation/bkg_estimate_TH2.C++\(\"Bkg_estimation/Total_data_$1_$2.root\"\,\"Bkg_estimation/Total_DYJets_$1_$2.root\"\,\"h_alphaMxSubjetCSV\"\,\"h_sbMxSubjetCSV\"\)


# get DYJets/Total Bkg ratio
root -b -l -q Bkg_estimation/getRatio.C++\(\"Bkg_estimation/Total_DYJets_$1_$2.root\"\,\"Bkg_estimation/Total_MCBKG_$1_$2.root\"\)


# DYJets/Bkg ratio correction
root -b -l -q Bkg_estimation/bkg_estimate_TH2.C++\(\"Bkg_estimation/Total_data_$1_$2.root\"\,\"Bkg_estimation/Total_DYJets_$1_$2.root\"\,\"h_ratio_sbMxCA8jetCSV\"\,\"h_n_MxCA8jetCSV_SbCorred\"\)
root -b -l -q Bkg_estimation/bkg_estimate_TH2.C++\(\"Bkg_estimation/Total_data_$1_$2.root\"\,\"Bkg_estimation/Total_DYJets_$1_$2.root\"\,\"h_ratio_sbMxSubjetCSV\"\,\"h_n_MxSubjetCSV_SbCorred\"\)


# get TTTo2L2Nu2B background
root -b -l -q Bkg_estimation/pushBKD.C++\(\"Bkg_estimation/Total_data_$1_$2.root\"\,\"result_cuts/TH2_TTTo2L2Nu2B_$1_$2.root\"\,\"h_sigMxCA8jetCSV\"\)
root -b -l -q Bkg_estimation/pushBKD.C++\(\"Bkg_estimation/Total_data_$1_$2.root\"\,\"result_cuts/TH2_TTTo2L2Nu2B_$1_$2.root\"\,\"h_sigMxSubjetCSV\"\)

# get DiBWW background
root -b -l -q Bkg_estimation/pushBKD.C++\(\"Bkg_estimation/Total_data_$1_$2.root\"\,\"result_cuts/TH2_DiBWW_$1_$2.root\"\,\"h_sigMxCA8jetCSV\"\)
root -b -l -q Bkg_estimation/pushBKD.C++\(\"Bkg_estimation/Total_data_$1_$2.root\"\,\"result_cuts/TH2_DiBWW_$1_$2.root\"\,\"h_sigMxSubjetCSV\"\)

# get DiBWZ background
root -b -l -q Bkg_estimation/pushBKD.C++\(\"Bkg_estimation/Total_data_$1_$2.root\"\,\"result_cuts/TH2_DiBWZ_$1_$2.root\"\,\"h_sigMxCA8jetCSV\"\)
root -b -l -q Bkg_estimation/pushBKD.C++\(\"Bkg_estimation/Total_data_$1_$2.root\"\,\"result_cuts/TH2_DiBWZ_$1_$2.root\"\,\"h_sigMxSubjetCSV\"\)

# get DiBZZ background
root -b -l -q Bkg_estimation/pushBKD.C++\(\"Bkg_estimation/Total_data_$1_$2.root\"\,\"result_cuts/TH2_DiBZZ_$1_$2.root\"\,\"h_sigMxCA8jetCSV\"\)
root -b -l -q Bkg_estimation/pushBKD.C++\(\"Bkg_estimation/Total_data_$1_$2.root\"\,\"result_cuts/TH2_DiBZZ_$1_$2.root\"\,\"h_sigMxSubjetCSV\"\)
