set terminal pdf
set output "overlap_missing.pdf"
set key left font "Arial,15"
set xlabel "オーバーラップ閾値" font "Arial,15"
set ylabel "MAE" font "Arial,15"
set xrange [0.0:1.0]
set xtics 0.1
plot \
"BFCS.txt" with linespoints title "BFCS",\
"EFCS.txt" with linespoints title "EFCS",\
"QFCS.txt" with linespoints title "QFCS",\
"BPCS.txt" with linespoints title "BPCS",\
"EPCS.txt" with linespoints title "EPCS",\
"QPCS.txt" with linespoints title "QPCS",\
