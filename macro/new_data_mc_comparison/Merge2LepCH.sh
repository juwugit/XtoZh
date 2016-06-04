# $1 = Cen, Up or Down
rm result_cuts/*FN*.root

hadd result_cuts/dataA_FN_$1.root result_cuts/dataA_El_$1.root result_cuts/dataA_Mu_$1.root
hadd result_cuts/dataB_FN_$1.root result_cuts/dataB_El_$1.root result_cuts/dataB_Mu_$1.root
hadd result_cuts/dataC_FN_$1.root result_cuts/dataC_El_$1.root result_cuts/dataC_Mu_$1.root
hadd result_cuts/dataD_FN_$1.root result_cuts/dataD_El_$1.root result_cuts/dataD_Mu_$1.root
hadd result_cuts/data_FN_$1.root result_cuts/data*_FN_$1.root

hadd result_cuts/TH2_DYJetsPtZ70To100_FN_$1.root result_cuts/TH2_DYJetsPtZ70To100_El_$1.root result_cuts/TH2_DYJetsPtZ70To100_Mu_$1.root

hadd result_cuts/TH2_DYJetsPtZ100_FN_$1.root result_cuts/TH2_DYJetsPtZ100_El_$1.root result_cuts/TH2_DYJetsPtZ100_Mu_$1.root

hadd result_cuts/TH2_TTTo2L2Nu2B_FN_$1.root result_cuts/TH2_TTTo2L2Nu2B_El_$1.root result_cuts/TH2_TTTo2L2Nu2B_Mu_$1.root
hadd result_cuts/TH2_DiBWW_FN_$1.root result_cuts/TH2_DiBWW_El_$1.root result_cuts/TH2_DiBWW_Mu_$1.root
hadd result_cuts/TH2_DiBWZ_FN_$1.root result_cuts/TH2_DiBWZ_El_$1.root result_cuts/TH2_DiBWZ_Mu_$1.root
hadd result_cuts/TH2_DiBZZ_FN_$1.root result_cuts/TH2_DiBZZ_El_$1.root result_cuts/TH2_DiBZZ_Mu_$1.root

