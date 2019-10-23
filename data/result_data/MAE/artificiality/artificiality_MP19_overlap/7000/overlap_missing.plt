set terminal pdf
set output "overlap_missing.pdf"
set key left font "Arial,15"
set xlabel "オーバーラップ閾値" font "Arial,15"
set ylabel "MAE" font "Arial,15"
set xrange [0.0:1.0]
set xtics 0.1
plot \
"BFCS.txt" using 1:3 with linespoints title "BFCS",\
"EFCS.txt" using 1:3 with linespoints title "EFCS",\
"QFCS.txt" using 1:3 with linespoints title "QFCS",\
"BPCS.txt" using 1:3 with linespoints title "BPCS",\
"EPCS.txt" using 1:3 with linespoints title "EPCS",\
"QPCS.txt" using 1:3 with linespoints title "QPCS",\
