#!/bin/bash


a=800
counter=0

while [ $a -le 2000 ]
do

root -l -b -q readXSec.C+\($a\)
a=$(($a+5))
counter=$(($counter+1))

done

echo $counter

