# $1 = El/Mu ; lepton channel
# $2 = Cen/Up/Down ; JetEnScale
# $3 = 0/1/-1 ; JetEnScale
# example: $sh run_HVT.sh El Cen 0


# Data
rm -rf result_cuts/*$1_$2.root
root -b -l -q recoXMassCSV.C++\($3\,\"../../delpanj_v4_data_Double$1_A.root\"\,\"result_cuts/dataA_$1_$2.root\"\)
root -b -l -q recoXMassCSV.C++\($3\,\"../../delpanj_v4_data_Double$1_B.root\"\,\"result_cuts/dataB_$1_$2.root\"\)
root -b -l -q recoXMassCSV.C++\($3\,\"../../delpanj_v4_data_Double$1_C.root\"\,\"result_cuts/dataC_$1_$2.root\"\)
root -b -l -q recoXMassCSV.C++\($3\,\"../../delpanj_v4_data_Double$1_D.root\"\,\"result_cuts/dataD_$1_$2.root\"\)

# Bkg MC
root -b -l -q recoXMassCSV.C++\($3\,\"../../delpanj_v4_TTTo2L2Nu2B.root\"\,\"result_cuts/TH2_TTTo2L2Nu2B_$1_$2.root\"\)
root -b -l -q recoXMassCSV.C++\($3\,\"../../delpanj_v4_WW_pythia_filtered.root\"\,\"result_cuts/TH2_DiBWW_$1_$2.root\"\)
root -b -l -q recoXMassCSV.C++\($3\,\"../../delpanj_v4_WZ_pythia_filtered.root\"\,\"result_cuts/TH2_DiBWZ_$1_$2.root\"\)
root -b -l -q recoXMassCSV.C++\($3\,\"../../delpanj_v4_ZZ_pythia_filtered.root\"\,\"result_cuts/TH2_DiBZZ_$1_$2.root\"\)
root -b -l -q recoXMassCSV.C++\($3\,\"../../delpanj_v4_DYJetsToLL_PtZ-100.root\"\,\"result_cuts/TH2_DYJetsPtZ100_$1_$2.root\"\)
root -b -l -q recoXMassCSV.C++\($3\,\"../../delpanj_v4_DYJetsToLL_PtZ-70To100.root\"\,\"result_cuts/TH2_DYJetsPtZ70To100_$1_$2.root\"\)

