#!/bin/bash/

MISS="300000"
DATA="libimseti"

for M in $MISS ; do
    cp plot.plt $M
    cd $M
    gnuplot -e "miss='$M';data='$DATA'" plot.plt
    cd ..
done 
