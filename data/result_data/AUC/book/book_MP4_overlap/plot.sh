#!/bin/bash/

MISS="30000"
DATA="book"

for M in $MISS ; do
    cp plot.plt $M
    cd $M
    gnuplot -e "miss='$M';data='$DATA'" plot.plt
    cd ..
done 
