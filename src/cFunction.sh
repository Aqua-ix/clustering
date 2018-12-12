#!/bin/sh

cd ~/clustering/src

gnuplot <<EOF
splot "qFCMA-Em2.000000-Lambda10000.000000-2d-Gaussian-2clusters.result_classificationFunction" using 1:2:3 with lines, "qFCMA-Em2.000000-Lambda10000.000000-2d-Gaussian-2clusters.result_classificationFunction" using 1:2:4 with lines, "< awk '{if($3>$4){print $1, $2, $3;}}' qFCMA-Em2.000000-Lambda10000.000000-2d-Gaussian-2clusters.result_membership", "< awk '{if($4>$3){print $1, $2, $4;}}' qFCMA-Em2.000000-Lambda10000.000000-2d-Gaussian-2clusters.result_membership"
replot
set ticslevel 0
set key outside center bottom
set terminal pdf
set output "sFCMA-Em2.000000-2d-Gaussian-2clusters.result_classificationFunction.pdf" 
replot
set output
quit
EOF
