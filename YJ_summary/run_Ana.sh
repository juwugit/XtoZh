rm -rf Bkg_estimation/*_Cen.root
hadd Bkg_estimation/Total_data_El_Cen.root result_cuts/data_El*_Cen.root
hadd Bkg_estimation/Total_DY_Cen.root result_cuts/TH2_DYJets*_Cen.root
hadd Bkg_estimation/Total_MCBKG_Cen.root result_cuts/TH2*_Cen.root
hadd Bkg_estimation/Total_Diboson_Cen.root result_cuts/TH2_Di*_Cen.root
cp result_cuts/TH2_TTTo2L2Nu2B_Cen.root Bkg_estimation/
cp result_cuts/TH2_Di*_Cen.root Bkg_estimation/

printf "create DY template"
root -b -q TH2Fitting/recoXmass_bkd_El_YJ.C++\(0\,\"Bkg_estimation/DY_El_Cen.root\"\)
printf "data sb to signal corrrection"
root -b -q Bkg_estimation/bkd_estimate_TH2_YJ.C++\(\"Bkg_estimation/Total_data_El_Cen.root\"\,\"Bkg_estimation/DY_El_Cen.root\"\,\"h_alphaXMsCSV\"\,\"h_sbXMsCSV\"\)
root -b -q Bkg_estimation/bkd_estimate_TH2_YJ.C++\(\"Bkg_estimation/Total_data_El_Cen.root\"\,\"Bkg_estimation/DY_El_Cen.root\"\,\"h_alphaXMCSV\"\,\"h_sbXMCSV\"\)
printf "DY Total Bkg ratio"
root -b -q Bkg_estimation/getRatio.C++\(\"Bkg_estimation/Total_DY_Cen.root\"\,\"Bkg_estimation/Total_MCBKG_Cen.root\"\,\"Bkg_estimation/Ratio_El_Cen.root\"\)
printf "Bkg ratio correction"
root -b -q Bkg_estimation/bkd_estimate_TH2_YJ.C++\(\"Bkg_estimation/Total_data_El_Cen.root\"\,\"Bkg_estimation/Ratio_El_Cen.root\"\,\"h_ratio_sbXMsCSV\"\,\"h_NbkgXMsCSV_DY\"\)
root -b -q Bkg_estimation/bkd_estimate_TH2_YJ.C++\(\"Bkg_estimation/Total_data_El_Cen.root\"\,\"Bkg_estimation/Ratio_El_Cen.root\"\,\"h_ratio_sbXMCSV\"\,\"h_NbkgXMCSV_DY\"\)



