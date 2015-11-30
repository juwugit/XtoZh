# $1 = El/Mu ; lepton channel
# $2 = Cen/Up/Down ; JetEnScale
# $3 = 0/1/-1 ; JetEnScale
# example: $sh run_HVT.sh El Cen 0


sh run_HVT.sh El Cen 0
sh run_HVT.sh El Up 1
sh run_HVT.sh El Down -1

sh run_HVT.sh Mu Cen 0
sh run_HVT.sh Mu Up 1
sh run_HVT.sh Mu Down -1
