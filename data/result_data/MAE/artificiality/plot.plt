set terminal pdf
set output "output/artificiality_".ms."_".ts.".pdf"
set key left font "Arial,15"
set xlabel "欠損数" font "Arial,15"
set ylabel "MAE" font "Arial,15"
set xrange [1500:7500]
set yrange [0:0.7]
set xtics 500
file(p, n, m) = sprintf("artificiality_MP%d_overlap_threshold%s00000/%s_OVERLAP_averageMAE.txt", p, n, m)
plot \
for [m in ms] \
for[t in ts] \
file(p, t, m) \
using 1:3 with linespoints title m."(".t.")"\
