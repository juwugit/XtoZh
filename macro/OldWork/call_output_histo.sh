#!/bin/bash


DATA_DIR=/home/juwu/XtoZh/results/eff

ROOT=`ls $DATA_DIR`

for FILE in $ROOT
do

    NEWDIR=`echo ${FILE:0:-5}`
    echo -e "Processing root file *** $FILE ***\n"
    root -q -b -l output_histo.C++\(\"$DATA_DIR/$FILE\"\,\"$NEWDIR\"\)
    mv $NEWDIR /home/juwu/XtoZh/histo/eff
    echo -e "Done!\n"

done

echo -e "Remove unnecessary files..."
rm -f *.d *.so
echo -e "All jobs done!\n"

exit
