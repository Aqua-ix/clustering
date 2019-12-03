set terminal pdf
set output "all.pdf"
set key outside font "Arial,15"
set xlabel "オーバーラップ閾値" font "Arial,15"
set xrange [0.0:1.0]
set xtics 0.1
set ylabel "MAE" font "Arial,15"
set ytics 0.01
plot \
"BFCS.txt" using 1:3 with linespoints title "BFCS",\
"EFCS.txt" using 1:3 with linespoints title "EFCS",\
"QFCS.txt" using 1:3 with linespoints title "QFCS",\
"BPCS.txt" using 1:3 with linespoints title "BPCS",\
"EPCS.txt" using 1:3 with linespoints title "EPCS",\
"QPCS.txt" using 1:3 with linespoints title "QPCS",\

set output "fcs.pdf"
plot \
"BFCS.txt" using 1:3 with linespoints title "BFCS",\
"EFCS.txt" using 1:3 with linespoints title "EFCS",\
"QFCS.txt" using 1:3 with linespoints title "QFCS",\

set output "pcs.pdf"
plot \
"BPCS.txt" using 1:3 with linespoints title "BPCS",\
"EPCS.txt" using 1:3 with linespoints title "EPCS",\
"QPCS.txt" using 1:3 with linespoints title "QPCS",\

set output "method_b.pdf"
plot \
"BFCS.txt" using 1:3 with linespoints title "BFCS",\
"BPCS.txt" using 1:3 with linespoints title "BPCS",\

set output "method_e.pdf"
plot \
"EFCS.txt" using 1:3 with linespoints title "EFCS",\
"EPCS.txt" using 1:3 with linespoints title "EPCS",\

set output "method_q.pdf"
plot \
"QFCS.txt" using 1:3 with linespoints title "QFCS",\
"QPCS.txt" using 1:3 with linespoints title "QPCS",\
