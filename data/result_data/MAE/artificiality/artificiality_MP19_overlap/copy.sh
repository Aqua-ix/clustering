#!/bin/bash/

MISS="1500 2000 2500 3000 3500 4000 4500 5000 5500 6000 6500 7000 7500"

mkdir -p overlap_missing.pdf ~/clustering/documents/presentation/results

for M in $MISS ; do
    cd $M
    cp overlap_missing.pdf ~/clustering/documents/presentation/results/overlap_missing_$M.pdf
    cd ..
done 
