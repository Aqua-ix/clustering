#!/bin/sh

gnuplot -e "
plot "2d-Gaussian-2clusters.dat" every ::1, "qFCMA-Em3.000000-Lambda1.000000-2d-Gaussian-2clusters.result_centers";
set size ratio -1;
set terminal pdf;
set output "qFCMA-Em3.000000-Lambda1.000000-2d-Gaussian-2clusters.result_centers.pdf";
replot;
set output;
quit
"
