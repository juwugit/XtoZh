rm -rf Bkg_estimation/*El_Cen.root
cp result_cuts/data_El_Cen.root Bkg_estimation/Total_data_El_Cen.root
hadd Bkg_estimation/Total_MCBKG_El_Cen.root result_cuts/TH2*_El_Cen.root
hadd Bkg_estimation/Total_Diboson_El_Cen.root result_cuts/TH2_Di*_El_Cen.root


printf "create DY template"
root -b -l -q Bkg_estimation/mergeDYJets.C++\(\"result_cuts/TH2_DYJetsPtZ70To100_El_Cen.root\"\,\"result_cuts/TH2_DYJetsPtZ100_El_Cen.root\"\,\"Bkg_estimation/Total_DYJets_El_Cen.root\"\)


printf "data sb to signal corrrection"
root -b -l -q Bkg_estimation/bkd_estimate_TH2_YJ.C++\(\"Bkg_estimation/Total_data_El_Cen.root\"\,\"Bkg_estimation/Total_DYJets_El_Cen.root\"\,\"h_alphaMxCA8jetCSV\"\,\"h_sbMxCA8jetCSV\"\)
root -b -l -q Bkg_estimation/bkd_estimate_TH2_YJ.C++\(\"Bkg_estimation/Total_data_El_Cen.root\"\,\"Bkg_estimation/Total_DYJets_El_Cen.root\"\,\"h_alphaMxSubjetCSV\"\,\"h_sbMxSubjetCSV\"\)


printf "get DY Total Bkg ratio"
root -b -l -q Bkg_estimation/getRatio.C++\(\"Bkg_estimation/Total_DYJets_El_Cen.root\"\,\"Bkg_estimation/Total_MCBKG_El_Cen.root\"\)


printf "DY/Bkg ratio correction"
root -b -l -q Bkg_estimation/bkd_estimate_TH2_YJ.C++\(\"Bkg_estimation/Total_data_El_Cen.root\"\,\"Bkg_estimation/Total_DYJets_El_Cen.root\"\,\"h_ratio_sbMxCA8jetCSV\"\,\"h_n_MxCA8jetCSV_SbCorred\"\)
root -b -l -q Bkg_estimation/bkd_estimate_TH2_YJ.C++\(\"Bkg_estimation/Total_data_El_Cen.root\"\,\"Bkg_estimation/Total_DYJets_El_Cen.root\"\,\"h_ratio_sbMxSubjetCSV\"\,\"h_n_MxSubjetCSV_SbCorred\"\)


printf "get TTTo2L2Nu2B background"
root -b -l -q Bkg_estimation/pushBKD.C++\(\"Bkg_estimation/Total_data_El_Cen.root\"\,\"result_cuts/TH2_TTTo2L2Nu2B_El_Cen.root\"\,\"h_sigMxCA8jetCSV\"\)
root -b -l -q Bkg_estimation/pushBKD.C++\(\"Bkg_estimation/Total_data_El_Cen.root\"\,\"result_cuts/TH2_TTTo2L2Nu2B_El_Cen.root\"\,\"h_sigMxSubjetCSV\"\)

printf "get DiBWW background"
root -b -l -q Bkg_estimation/pushBKD.C++\(\"Bkg_estimation/Total_data_El_Cen.root\"\,\"result_cuts/TH2_DiBWW_El_Cen.root\"\,\"h_sigMxCA8jetCSV\"\)
root -b -l -q Bkg_estimation/pushBKD.C++\(\"Bkg_estimation/Total_data_El_Cen.root\"\,\"result_cuts/TH2_DiBWW_El_Cen.root\"\,\"h_sigMxSubjetCSV\"\)

printf "get DiBWZ background"
root -b -l -q Bkg_estimation/pushBKD.C++\(\"Bkg_estimation/Total_data_El_Cen.root\"\,\"result_cuts/TH2_DiBWZ_El_Cen.root\"\,\"h_sigMxCA8jetCSV\"\)
root -b -l -q Bkg_estimation/pushBKD.C++\(\"Bkg_estimation/Total_data_El_Cen.root\"\,\"result_cuts/TH2_DiBWZ_El_Cen.root\"\,\"h_sigMxSubjetCSV\"\)

printf "get DiBZZ background"
root -b -l -q Bkg_estimation/pushBKD.C++\(\"Bkg_estimation/Total_data_El_Cen.root\"\,\"result_cuts/TH2_DiBZZ_El_Cen.root\"\,\"h_sigMxCA8jetCSV\"\)
root -b -l -q Bkg_estimation/pushBKD.C++\(\"Bkg_estimation/Total_data_El_Cen.root\"\,\"result_cuts/TH2_DiBZZ_El_Cen.root\"\,\"h_sigMxSubjetCSV\"\)
