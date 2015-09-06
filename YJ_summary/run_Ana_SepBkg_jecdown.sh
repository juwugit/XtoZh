rm -rf Bkg_estimation/*_Jecdown.root
hadd Bkg_estimation/Total_data_El_Jecdown.root result_cuts/data_El*_Jecdown.root
hadd Bkg_estimation/Total_DY_Jecdown.root result_cuts/TH2_DYJets*_Jecdown.root
hadd Bkg_estimation/Total_MCBKG_Jecdown.root result_cuts/TH2*_Jecdown.root
hadd Bkg_estimation/Total_Diboson_Jecdown.root result_cuts/TH2_Di*_Jecdown.root
cp result_cuts/TH2_TTTo2L2Nu2B_Jecdown.root Bkg_estimation/
cp result_cuts/TH2_Di*_Jecdown.root Bkg_estimation/

printf "create DY template"
root -b -q TH2Fitting/recoXmass_bkd_El_YJ.C++\(0\,\"Bkg_estimation/DY_El_Jecdown.root\"\)
printf "data sb to signal corrrection"
root -b -q Bkg_estimation/bkd_estimate_TH2_YJ.C++\(\"Bkg_estimation/Total_data_El_Jecdown.root\"\,\"Bkg_estimation/DY_El_Jecdown.root\"\,\"h_alphaXMsCSV\"\,\"h_sbXMsCSV\"\)
root -b -q Bkg_estimation/bkd_estimate_TH2_YJ.C++\(\"Bkg_estimation/Total_data_El_Jecdown.root\"\,\"Bkg_estimation/DY_El_Jecdown.root\"\,\"h_alphaXMCSV\"\,\"h_sbXMCSV\"\)
printf "get DY Total Bkg ratio"
root -b -q Bkg_estimation/getRatio.C++\(\"Bkg_estimation/Total_DY_Jecdown.root\"\,\"Bkg_estimation/Total_MCBKG_Jecdown.root\"\,\"Bkg_estimation/Ratio_El_Jecdown.root\"\)
printf "get DY ttbar Bkg ratio"
root -b -q Bkg_estimation/getRatio.C++\(\"Bkg_estimation/Total_DY_Jecdown.root\"\,\"Bkg_estimation/TH2_TTTo2L2Nu2B_Jecdown.root\"\,\"Bkg_estimation/Ratio_ttbar_El_Jecdown.root\"\)
printf "get DY WZ Bkg ratio"
root -b -q Bkg_estimation/getRatio.C++\(\"Bkg_estimation/Total_DY_Jecdown.root\"\,\"Bkg_estimation/TH2_DiBWZ_Jecdown.root\"\,\"Bkg_estimation/Ratio_WZ_El_Jecdown.root\"\)
printf "get DY ZZ Bkg ratio"
root -b -q Bkg_estimation/getRatio.C++\(\"Bkg_estimation/Total_DY_Jecdown.root\"\,\"Bkg_estimation/TH2_DiBZZ_Jecdown.root\"\,\"Bkg_estimation/Ratio_ZZ_El_Jecdown.root\"\)
printf "get DY WW Bkg ratio"
root -b -q Bkg_estimation/getRatio.C++\(\"Bkg_estimation/Total_DY_Jecdown.root\"\,\"Bkg_estimation/TH2_DiBWW_Jecdown.root\"\,\"Bkg_estimation/Ratio_WW_El_Jecdown.root\"\)


printf "Bkg ratio correction"
root -b -q Bkg_estimation/bkd_estimate_TH2_YJ.C++\(\"Bkg_estimation/Total_data_El_Jecdown.root\"\,\"Bkg_estimation/Ratio_El_Jecdown.root\"\,\"h_ratio_sbXMsCSV\"\,\"h_n_XMsCSV_DYSbCorred\"\)
root -b -q Bkg_estimation/bkd_estimate_TH2_YJ.C++\(\"Bkg_estimation/Total_data_El_Jecdown.root\"\,\"Bkg_estimation/Ratio_El_Jecdown.root\"\,\"h_ratio_sbXMCSV\"\,\"h_n_XMCSV_DYSbCorred\"\)
root -b -q Bkg_estimation/bkd_estimate_TH2_YJ.C++\(\"Bkg_estimation/Total_data_El_Jecdown.root\"\,\"Bkg_estimation/Ratio_ttbar_El_Jecdown.root\"\,\"h_ratio_sbXMsCSV\"\,\"h_n_XMsCSV_DYSbCorred\"\)
root -b -q Bkg_estimation/bkd_estimate_TH2_YJ.C++\(\"Bkg_estimation/Total_data_El_Jecdown.root\"\,\"Bkg_estimation/Ratio_ttbar_El_Jecdown.root\"\,\"h_ratio_sbXMCSV\"\,\"h_n_XMCSV_DYSbCorred\"\)
root -b -q Bkg_estimation/bkd_estimate_TH2_YJ.C++\(\"Bkg_estimation/Total_data_El_Jecdown.root\"\,\"Bkg_estimation/Ratio_WZ_El_Jecdown.root\"\,\"h_ratio_sbXMsCSV\"\,\"h_n_XMsCSV_DYSbCorred\"\)
root -b -q Bkg_estimation/bkd_estimate_TH2_YJ.C++\(\"Bkg_estimation/Total_data_El_Jecdown.root\"\,\"Bkg_estimation/Ratio_WZ_El_Jecdown.root\"\,\"h_ratio_sbXMCSV\"\,\"h_n_XMCSV_DYSbCorred\"\)
root -b -q Bkg_estimation/bkd_estimate_TH2_YJ.C++\(\"Bkg_estimation/Total_data_El_Jecdown.root\"\,\"Bkg_estimation/Ratio_ZZ_El_Jecdown.root\"\,\"h_ratio_sbXMsCSV\"\,\"h_n_XMsCSV_DYSbCorred\"\)
root -b -q Bkg_estimation/bkd_estimate_TH2_YJ.C++\(\"Bkg_estimation/Total_data_El_Jecdown.root\"\,\"Bkg_estimation/Ratio_ZZ_El_Jecdown.root\"\,\"h_ratio_sbXMCSV\"\,\"h_n_XMCSV_DYSbCorred\"\)
root -b -q Bkg_estimation/bkd_estimate_TH2_YJ.C++\(\"Bkg_estimation/Total_data_El_Jecdown.root\"\,\"Bkg_estimation/Ratio_WW_El_Jecdown.root\"\,\"h_ratio_sbXMsCSV\"\,\"h_n_XMsCSV_DYSbCorred\"\)
root -b -q Bkg_estimation/bkd_estimate_TH2_YJ.C++\(\"Bkg_estimation/Total_data_El_Jecdown.root\"\,\"Bkg_estimation/Ratio_WW_El_Jecdown.root\"\,\"h_ratio_sbXMCSV\"\,\"h_n_XMCSV_DYSbCorred\"\)









