#!/bin/bash/

ms1="B E Q"
ms2="FCS PCS"
ts="1.0"
mp=4

for m1 in $ms1; do
    for t in $ts; do
        gnuplot -e "p=${mp}; ms='${m1}FCS ${m1}PCS'; ts='$t'" -persist plot.plt
    done
    for m2 in $ms2; do
        m_str=$m1$m2
        gnuplot -e "p=${mp}; ms='$m_str'; ts='$ts'" -persist plot.plt
    done
done


for m2 in $ms2; do
     for t in $ts; do
         gnuplot -e "p=${mp}; ms='B${m2} E${m2} Q${m2}'; ts='$t'" -persist plot.plt
     done
done

for t in $ts; do
    gnuplot -e "p=${mp}; ms='BFCS EFCS QFCS BPCS EPCS QPCS'; ts='$t'" -persist plot.plt
done
