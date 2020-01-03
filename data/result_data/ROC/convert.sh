#!/bin/sh

D=$1
OT='0.200000 0.400000 0.600000 0.800000 1.000000'
METHOD='BFCS EFCS QFCS BPCS EPCS QPCS'
PAT='0 1 2 3 4'

for O in $OT; do
    cd ${D}/${D}_overlap_threshold${O}
    for P in $PAT; do
        mkdir -p missing_pattern$P
        for M in $METHOD; do
            cd $M
            mv ${M}_OVERLAP_ROC_${P}.txt ../missing_pattern${P}
            cd ..
            rmdir --ignore-fail-on-non-empty  $M
        done
    done
    cd ../..
done
