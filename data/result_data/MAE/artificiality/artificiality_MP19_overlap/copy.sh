#!/bin/bash/

MISS="1500 2000 2500 3000 3500 4000 4500 5000 5500 6000 6500 7000 7500"

for M in $MISS ; do
    cd $M
    cp overlap_missing_$M.pdf ~/clustering/documents/presentation/
    cd ..
done 
