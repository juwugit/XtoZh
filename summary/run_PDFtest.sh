# $1 = El/Mu ; lepton channel
# $2 = Cen/Up/Down ; JetEnScale
# $3 = 0/1/-1 ; JetEnScale
# example: $sh run_HVT.sh El Cen 0



# signal MC
#root -b -l -q Main_analyzer/runPDF.C++\($3\,\"/data4/juwu/v5_sigNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M800.root\"\,\"PDFtest/ZPrime_ZH_lljj_M800_$1_$2.root\"\)
#root -b -l -q Main_analyzer/runPDF.C++\($3\,\"/data4/juwu/v5_sigNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M900.root\"\,\"PDFtest/ZPrime_ZH_lljj_M900_$1_$2.root\"\)
root -b -l -q Main_analyzer/runPDF.C++\($3\,\"/data4/juwu/v5_sigNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1000.root\"\,\"PDFtest/ZPrime_ZH_lljj_M1000_$1_$2.root\"\)
#root -b -l -q Main_analyzer/runPDF.C++\($3\,\"/data4/juwu/v5_sigNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1100.root\"\,\"PDFtest/ZPrime_ZH_lljj_M1100_$1_$2.root\"\)
#root -b -l -q Main_analyzer/runPDF.C++\($3\,\"/data4/juwu/v5_sigNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1200.root\"\,\"PDFtest/ZPrime_ZH_lljj_M1200_$1_$2.root\"\)
#root -b -l -q Main_analyzer/runPDF.C++\($3\,\"/data4/juwu/v5_sigNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1300.root\"\,\"PDFtest/ZPrime_ZH_lljj_M1300_$1_$2.root\"\)
#root -b -l -q Main_analyzer/runPDF.C++\($3\,\"/data4/juwu/v5_sigNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1400.root\"\,\"PDFtest/ZPrime_ZH_lljj_M1400_$1_$2.root\"\)
root -b -l -q Main_analyzer/runPDF.C++\($3\,\"/data4/juwu/v5_sigNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1500.root\"\,\"PDFtest/ZPrime_ZH_lljj_M1500_$1_$2.root\"\)
#root -b -l -q Main_analyzer/runPDF.C++\($3\,\"/data4/juwu/v5_sigNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1600.root\"\,\"PDFtest/ZPrime_ZH_lljj_M1600_$1_$2.root\"\)
#root -b -l -q Main_analyzer/runPDF.C++\($3\,\"/data4/juwu/v5_sigNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1700.root\"\,\"PDFtest/ZPrime_ZH_lljj_M1700_$1_$2.root\"\)
#root -b -l -q Main_analyzer/runPDF.C++\($3\,\"/data4/juwu/v5_sigNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1800.root\"\,\"PDFtest/ZPrime_ZH_lljj_M1800_$1_$2.root\"\)
#root -b -l -q Main_analyzer/runPDF.C++\($3\,\"/data4/juwu/v5_sigNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M1900.root\"\,\"PDFtest/ZPrime_ZH_lljj_M1900_$1_$2.root\"\)
root -b -l -q Main_analyzer/runPDF.C++\($3\,\"/data4/juwu/v5_sigNtuples/delpanj_v5_AbelianZPrime_ZH_lljj_M2000.root\"\,\"PDFtest/ZPrime_ZH_lljj_M2000_$1_$2.root\"\)