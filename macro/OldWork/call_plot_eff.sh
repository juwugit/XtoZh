#!/bin/bash

SIGNAL_DIR=/home/juwu/XtoZh/results

declare -a NTUPLES=(
    "delpanj_diboson_signal_ZPrime_hZ_qqll_LHC8_M1000.root"
    "delpanj_diboson_signal_ZPrime_hZ_qqll_LHC8_M1500.root"
    "delpanj_diboson_signal_ZPrime_hZ_qqll_LHC8_M2000.root"
    "delpanj_diboson_signal_ZPrime_ZH_llWW_M1100.root"
    "delpanj_diboson_signal_ZPrime_ZH_llWW_M1200.root"
    "delpanj_diboson_signal_ZPrime_ZH_llWW_M1300.root"
    "delpanj_diboson_signal_ZPrime_ZH_llWW_M1400.root"
    "delpanj_diboson_signal_ZPrime_ZH_llWW_M1600.root"
    "delpanj_diboson_signal_ZPrime_ZH_llWW_M1700.root"
    "delpanj_diboson_signal_ZPrime_ZH_llWW_M1800.root"
    "delpanj_diboson_signal_ZPrime_ZH_llWW_M1900.root"
    "delpanj_diboson_signal_ZPrime_ZH_llWW_M800.root"
    "delpanj_diboson_signal_ZPrime_ZH_llWW_M900.root"
    "delpanj_diboson_signal_ZPrime_ZH_llZZ_M1000.root"
    "delpanj_diboson_signal_ZPrime_ZH_llZZ_M1100.root"
    "delpanj_diboson_signal_ZPrime_ZH_llZZ_M1200.root"
    "delpanj_diboson_signal_ZPrime_ZH_llZZ_M1300.root"
    "delpanj_diboson_signal_ZPrime_ZH_llZZ_M1400.root"
    "delpanj_diboson_signal_ZPrime_ZH_llZZ_M1500.root"
    "delpanj_diboson_signal_ZPrime_ZH_llZZ_M1600.root"
    "delpanj_diboson_signal_ZPrime_ZH_llZZ_M1700.root"
    "delpanj_diboson_signal_ZPrime_ZH_llZZ_M1800.root"
    "delpanj_diboson_signal_ZPrime_ZH_llZZ_M1900.root"
)

for FILE in "${NTUPLES[@]}"
do

    echo -e "Processing root file *** $FILE ***\n"
    root -q -b -l plot_eff.C++\(\"$SIGNAL_DIR/$FILE\"\,\"$FILE\"\)
    echo -e "Done!\n"

done

mkdir results/eff
mv *.root results/eff
rm -f *.d *.so

exit
