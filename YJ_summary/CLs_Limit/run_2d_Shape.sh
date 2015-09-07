
xmass=900 
rm -rf *Testing_0819*.txt
rm -rf *_${xmass}*.root
rm -rf *output_0819*.root
rm -rf Shape1d_0819.root
root -b -l -q ProjectHistograms_YJ.C+\(\"../result_cuts/ZPrime_ZH_lljj_M${xmass}_Cen.root\"\)
root -b -l -q Change_data_obs_name.C+
python MakeDataCardsYJ.py
combineCards.py Name1=Datacard_Testing_0819_1.txt Name2=Datacard_Testing_0819_2.txt Name3=Datacard_Testing_0819_3.txt  Name4=Datacard_Testing_0819_4.txt   Name5=Datacard_Testing_0819_5.txt > Mycard_YJ.txt
combine -M Asymptotic Mycard_YJ.txt -n shape_2d_${xmass}
combine -M Asymptotic Datacard_1dshape_Testing_0819.txt -n shape_1d_${xmass}
combine -M Asymptotic Datacard_counting_Testing_0819.txt -n counting_${xmass}
combine -M ProfileLikelihood Mycard_YJ.txt -n shape_2d_${xmass} --signif --pvalue -t -1 --expectSignal=1 
combine -M ProfileLikelihood Datacard_1dshape_Testing_0819.txt -n shape_1d_${xmass} --signif --pvalue -t -1 --expectSignal=1 
combine -M ProfileLikelihood Datacard_counting_Testing_0819.txt -n counting_${xmass} --signif --pvalue -t -1 --expectSignal=1 

