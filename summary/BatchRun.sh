#!/bin/tcsh

cd $1

setenv slc6_amd64_gcc472; eval `scramv1 runtime -csh`

sh run_HVT.sh El Cen 0
