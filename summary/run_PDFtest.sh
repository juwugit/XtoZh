# $1 = El/Mu ; lepton channel
# $2 = Cen/Up/Down ; JetEnScale
# $3 = 0/1/-1 ; JetEnScale
# example: $sh run_HVT.sh El Cen 0



# signal MC

root -b -l -q Main_analyzer/runPDF.C++\($3\,\"/data4/juwu/v5_sigNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1500.root\"\,\"PDFtest/ZPrime_ZH_lljj_M1500_$1_$2.root\"\)

root -b -l -q Main_analyzer/runPDF_CT10.C++\($3\,\"/data4/juwu/v5_sigNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1500.root\"\,\"PDFtest/ZPrime_ZH_lljj_M1500_$1_$2.root\"\)
