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
rm -f unite_threshold.pdf
pdfunite *.pdf unite_threshold.pdf
cd ..
