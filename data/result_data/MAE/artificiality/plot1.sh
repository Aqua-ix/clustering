#!/bin/bash/

DATA="artificiality"
MP=19
MS1="B E Q"
MS2="FCS PCS"
TS="0.0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0"

mkdir -p graph

for M1 in $MS1; do
    for t in $TS; do
        gnuplot -e "data='$DATA'; p=${MP}; ms='${M1}FCS ${M1}PCS'; ts='$t'" -persist plot1.plt
    done
    for M2 in $MS2; do
        m_str=$M1$M2
        gnuplot -e "data='$DATA'; p=${MP}; ms='$m_str'; ts='$TS'" -persist plot1.plt
    done
done


for M2 in $MS2; do
     for t in $TS; do
         gnuplot -e "data='$DATA'; p=${MP}; ms='B${M2} E${M2} Q${M2}'; ts='$t'" -persist plot1.plt
     done
done

for t in $TS; do
    gnuplot -e "data='$DATA'; p=${MP}; ms='BFCS EFCS QFCS BPCS EPCS QPCS'; ts='$t'" -persist plot1.plt
done
