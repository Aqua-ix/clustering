set terminal pdf
set output "output/".ms."_".ts.".pdf"
set title ms." ".ts
set key left font "Arial,15"
set xlabel "欠損数" font "Arial,15"
set ylabel "MAE" font "Arial,15"
set xrange [1500:7500]
set yrange [0:0.7]
set xtics 500
file(n, m) = sprintf("artificiality_MP19_overlap_threshold%s00000/%s_OVERLAP_averageMAE.txt", n, m)
plot \
for [m in ms] \
for[t in ts] \
file(t, m) \
using 1:3 with linespoints \
title m."(".t.")"