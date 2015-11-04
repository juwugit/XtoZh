# $1 = El/Mu
# $2 = XMass
# $sh run_2d_Shape.sh El 900

rm -rf *Testing_0819*.txt
rm -rf *_$2*.root
rm -rf *output_0819*.root
rm -rf Shape1d_0819.root

root -b -l -q ProjectHistograms.C+\(\"../result_cuts/ZPrime_ZH_lljj_M$2_$1_Cen.root\"\,\"../result_cuts/ZPrime_ZH_lljj_M$2_$1_Up.root\"\,\"../result_cuts/ZPrime_ZH_lljj_M$2_$1_Down.root\"\,\"../Bkg_estimation/Total_data_$1_Cen.root\"\,\"../Bkg_estimation/Total_data_$1_Up.root\"\,\"../Bkg_estimation/Total_data_$1_Down.root\"\)

root -b -l -q Change_data_obs_name.C+
python MakeDataCardsYJ.py
combineCards.py Name1=Datacard_Testing_0819_3.txt Name2=Datacard_Testing_0819_4.txt Name3=Datacard_Testing_0819_5.txt > Mycard_YJ.txt

combine -M Asymptotic Mycard_YJ.txt -n shape_1d_$2
#combine -M Asymptotic Datacard_Testing_0819_5.txt -n shape_1d_$2
#combine -M Asymptotic Datacard_counting_Testing_0819.txt -n counting_$2
#combine -M ProfileLikelihood Mycard_YJ.txt -n shape_2d_$2 --signif --pvalue -t -1 --expectSignal=1 
#combine -M ProfileLikelihood Datacard_1dshape_Testing_0819.txt -n shape_1d_$2 --signif --pvalue -t -1 --expectSignal=1 
#combine -M ProfileLikelihood Datacard_counting_Testing_0819.txt -n counting_$2 --signif --pvalue -t -1 --expectSignal=1 

rm roostats*