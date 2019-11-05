#!/bin/bash/

ms1="B E Q"
ms2="FCS PCS"
ts="0.0 0.2 0.4 0.6 0.8 1.0"

for m1 in $ms1; do
    for t in $ts; do
        gnuplot -e "ms='${m1}FCS ${m1}PCS'; ts='$t'" -persist plot.plt
    done
    for m2 in $ms2; do
        m_str=$m1$m2
        gnuplot -e "ms='$m_str'; ts='$ts'" -persist plot.plt
    done
done
