# $1 = El/Mu ; lepton channel
# $2 = Cen/Up/Down ; JetEnScale
# $3 = 0/1/-1 ; JetEnScale
# example: $sh run_HVT.sh El Cen 0


# Data
rm -rf result_cuts/*$1_$2.root
root -b -l -q Main_analyzer/recoXMassCSV.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v4_data_Double$1_A.root\"\,\"result_cuts/dataA_$1_$2.root\"\)
root -b -l -q Main_analyzer/recoXMassCSV.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v4_data_Double$1_B.root\"\,\"result_cuts/dataB_$1_$2.root\"\)
root -b -l -q Main_analyzer/recoXMassCSV.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v4_data_Double$1_C.root\"\,\"result_cuts/dataC_$1_$2.root\"\)
root -b -l -q Main_analyzer/recoXMassCSV.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v4_data_Double$1_D.root\"\,\"result_cuts/dataD_$1_$2.root\"\)

# Bkg MC
root -b -l -q Main_analyzer/recoXMassCSV.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v4_TTTo2L2Nu2B.root\"\,\"result_cuts/TH2_TTTo2L2Nu2B_$1_$2.root\"\)
root -b -l -q Main_analyzer/recoXMassCSV.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v4_WW_pythia_filtered.root\"\,\"result_cuts/TH2_DiBWW_$1_$2.root\"\)
root -b -l -q Main_analyzer/recoXMassCSV.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v4_WZ_pythia_filtered.root\"\,\"result_cuts/TH2_DiBWZ_$1_$2.root\"\)
root -b -l -q Main_analyzer/recoXMassCSV.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v4_ZZ_pythia_filtered.root\"\,\"result_cuts/TH2_DiBZZ_$1_$2.root\"\)
root -b -l -q Main_analyzer/recoXMassCSV.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v4_DYJetsToLL_PtZ-100.root\"\,\"result_cuts/TH2_DYJetsPtZ100_$1_$2.root\"\)
root -b -l -q Main_analyzer/recoXMassCSV.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v4_DYJetsToLL_PtZ-70To100.root\"\,\"result_cuts/TH2_DYJetsPtZ70To100_$1_$2.root\"\)

# signal MC
root -b -l -q Main_analyzer/runPDF.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M800.root\"\,\"result_cuts/ZPrime_ZH_lljj_M800_$1_$2.root\"\)
root -b -l -q Main_analyzer/runPDF.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M900.root\"\,\"result_cuts/ZPrime_ZH_lljj_M900_$1_$2.root\"\)
root -b -l -q Main_analyzer/runPDF.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1000.root\"\,\"result_cuts/ZPrime_ZH_lljj_M1000_$1_$2.root\"\)
root -b -l -q Main_analyzer/runPDF.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1100.root\"\,\"result_cuts/ZPrime_ZH_lljj_M1100_$1_$2.root\"\)
root -b -l -q Main_analyzer/runPDF.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1200.root\"\,\"result_cuts/ZPrime_ZH_lljj_M1200_$1_$2.root\"\)
root -b -l -q Main_analyzer/runPDF.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1300.root\"\,\"result_cuts/ZPrime_ZH_lljj_M1300_$1_$2.root\"\)
root -b -l -q Main_analyzer/runPDF.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1400.root\"\,\"result_cuts/ZPrime_ZH_lljj_M1400_$1_$2.root\"\)
root -b -l -q Main_analyzer/runPDF.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1500.root\"\,\"result_cuts/ZPrime_ZH_lljj_M1500_$1_$2.root\"\)
root -b -l -q Main_analyzer/runPDF.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1600.root\"\,\"result_cuts/ZPrime_ZH_lljj_M1600_$1_$2.root\"\)
root -b -l -q Main_analyzer/runPDF.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1700.root\"\,\"result_cuts/ZPrime_ZH_lljj_M1700_$1_$2.root\"\)
root -b -l -q Main_analyzer/runPDF.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1800.root\"\,\"result_cuts/ZPrime_ZH_lljj_M1800_$1_$2.root\"\)
root -b -l -q Main_analyzer/runPDF.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1900.root\"\,\"result_cuts/ZPrime_ZH_lljj_M1900_$1_$2.root\"\)
root -b -l -q Main_analyzer/runPDF.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M2000.root\"\,\"result_cuts/ZPrime_ZH_lljj_M2000_$1_$2.root\"\)


# signal MC with CT10 PDFset
root -b -l -q Main_analyzer/runPDF_CT10.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M800.root\"\,\"result_cuts/ZPrime_ZH_lljj_M800_$1_$2.root\"\)
root -b -l -q Main_analyzer/runPDF_CT10.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M900.root\"\,\"result_cuts/ZPrime_ZH_lljj_M900_$1_$2.root\"\)
root -b -l -q Main_analyzer/runPDF_CT10.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1000.root\"\,\"result_cuts/ZPrime_ZH_lljj_M1000_$1_$2.root\"\)
root -b -l -q Main_analyzer/runPDF_CT10.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1100.root\"\,\"result_cuts/ZPrime_ZH_lljj_M1100_$1_$2.root\"\)
root -b -l -q Main_analyzer/runPDF_CT10.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1200.root\"\,\"result_cuts/ZPrime_ZH_lljj_M1200_$1_$2.root\"\)
root -b -l -q Main_analyzer/runPDF_CT10.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1300.root\"\,\"result_cuts/ZPrime_ZH_lljj_M1300_$1_$2.root\"\)
root -b -l -q Main_analyzer/runPDF_CT10.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1400.root\"\,\"result_cuts/ZPrime_ZH_lljj_M1400_$1_$2.root\"\)
root -b -l -q Main_analyzer/runPDF_CT10.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1500.root\"\,\"result_cuts/ZPrime_ZH_lljj_M1500_$1_$2.root\"\)
root -b -l -q Main_analyzer/runPDF_CT10.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1600.root\"\,\"result_cuts/ZPrime_ZH_lljj_M1600_$1_$2.root\"\)
root -b -l -q Main_analyzer/runPDF_CT10.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1700.root\"\,\"result_cuts/ZPrime_ZH_lljj_M1700_$1_$2.root\"\)
root -b -l -q Main_analyzer/runPDF_CT10.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1800.root\"\,\"result_cuts/ZPrime_ZH_lljj_M1800_$1_$2.root\"\)
root -b -l -q Main_analyzer/runPDF_CT10.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1900.root\"\,\"result_cuts/ZPrime_ZH_lljj_M1900_$1_$2.root\"\)
root -b -l -q Main_analyzer/runPDF_CT10.C++\($3\,\"/afs/cern.ch/work/j/juwu/workspace/delpanjNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M2000.root\"\,\"result_cuts/ZPrime_ZH_lljj_M2000_$1_$2.root\"\)


# get signal MC maximum pdf shape uncertainty
root -b -l -q Main_analyzer/PDF_MaxValue.C++\(\"result_cuts/ZPrime_ZH_lljj_M800_$1_$2.root\"\)
root -b -l -q Main_analyzer/PDF_MaxValue.C++\(\"result_cuts/ZPrime_ZH_lljj_M900_$1_$2.root\"\)
root -b -l -q Main_analyzer/PDF_MaxValue.C++\(\"result_cuts/ZPrime_ZH_lljj_M1000_$1_$2.root\"\)
root -b -l -q Main_analyzer/PDF_MaxValue.C++\(\"result_cuts/ZPrime_ZH_lljj_M1100_$1_$2.root\"\)
root -b -l -q Main_analyzer/PDF_MaxValue.C++\(\"result_cuts/ZPrime_ZH_lljj_M1200_$1_$2.root\"\)
root -b -l -q Main_analyzer/PDF_MaxValue.C++\(\"result_cuts/ZPrime_ZH_lljj_M1300_$1_$2.root\"\)
root -b -l -q Main_analyzer/PDF_MaxValue.C++\(\"result_cuts/ZPrime_ZH_lljj_M1400_$1_$2.root\"\)
root -b -l -q Main_analyzer/PDF_MaxValue.C++\(\"result_cuts/ZPrime_ZH_lljj_M1500_$1_$2.root\"\)
root -b -l -q Main_analyzer/PDF_MaxValue.C++\(\"result_cuts/ZPrime_ZH_lljj_M1600_$1_$2.root\"\)
root -b -l -q Main_analyzer/PDF_MaxValue.C++\(\"result_cuts/ZPrime_ZH_lljj_M1700_$1_$2.root\"\)
root -b -l -q Main_analyzer/PDF_MaxValue.C++\(\"result_cuts/ZPrime_ZH_lljj_M1800_$1_$2.root\"\)
root -b -l -q Main_analyzer/PDF_MaxValue.C++\(\"result_cuts/ZPrime_ZH_lljj_M1900_$1_$2.root\"\)
root -b -l -q Main_analyzer/PDF_MaxValue.C++\(\"result_cuts/ZPrime_ZH_lljj_M2000_$1_$2.root\"\)

