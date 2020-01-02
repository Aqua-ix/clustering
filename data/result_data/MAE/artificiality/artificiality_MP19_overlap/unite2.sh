#!/bin/bash/

DATA="artificiality"
MISS="1500 2000 2500 3000 3500 4000 4500 5000 5500 6000 6500 7000 7500"

mkdir -p unite
for M in $MISS ; do
    cd $M
    NAME=${DATA}_${M}
    pdfunite \
        ${NAME}_ALL_MAE.pdf \
        ${NAME}_FCS_MAE.pdf \
        ${NAME}_PCS_MAE.pdf \
        ${NAME}_B_MAE.pdf \
        ${NAME}_E_MAE.pdf \
        ${NAME}_Q_MAE.pdf \
        ../unite/$M.pdf
    cd ..
done

cd unite
rm -f unite_threshold.pdf
pdfunite *.pdf unite_threshold.pdf
cd ..
