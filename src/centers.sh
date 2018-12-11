#!/bin/sh

cd ~/clustering/src

gnuplot <<EOF
plot "2d-Gaussian-2clusters.dat" every ::1, "sFCMA-Em2.000000-2d-Gaussian-2clusters.result_centers"
set size ratio -1
set terminal pdf
set output "sFCMA-Em2.000000-2d-Gaussian-2clusters.result_centers.pdf"
replot
set output
quit
EOF
