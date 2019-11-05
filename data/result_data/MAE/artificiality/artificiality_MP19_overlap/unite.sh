#!/bin/bash/

MISS="1500 2000 2500 3000 3500 4000 4500 5000 5500 6000 6500 7000 7500"

for M in $MISS ; do
    cd $M
    pdfunite \
        all.pdf \
        fcs.pdf \
        pcs.pdf \
        method_b.pdf \
        method_e.pdf \
        method_q.pdf \
        ../unite/$M.pdf
    cd ..
done

cd unite
pdfunite \
    1500.pdf \
    2000.pdf \
    2500.pdf \
    3000.pdf \
    3500.pdf \
    4000.pdf \
    4500.pdf \
    5000.pdf \
    5500.pdf \
    6000.pdf \
    6500.pdf \
    7000.pdf \
    7500.pdf \
    unite.pdf
cd ..
