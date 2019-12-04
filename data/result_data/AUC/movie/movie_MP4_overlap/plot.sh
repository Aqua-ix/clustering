#!/bin/bash/

MISS="100000"
DATA="movie"

for M in $MISS ; do
    cp plot.plt $M
    cd $M
    gnuplot -e "miss='$M';data='$DATA'" plot.plt
    cd ..
done 
