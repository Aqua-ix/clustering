set terminal pdf
set output "all.pdf"
set title miss."all"
set key left font "Arial,15"
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
set title miss."FCS"
plot \
"BFCS.txt" using 1:3 with linespoints title "BFCS",\
"EFCS.txt" using 1:3 with linespoints title "EFCS",\
"QFCS.txt" using 1:3 with linespoints title "QFCS",\

set output "pcs.pdf"
set title miss."PCS"
plot \
"BPCS.txt" using 1:3 with linespoints title "BPCS",\
"EPCS.txt" using 1:3 with linespoints title "EPCS",\
"QPCS.txt" using 1:3 with linespoints title "QPCS",\

set output "method_b.pdf"
set title miss."B"
plot \
"BFCS.txt" using 1:3 with linespoints title "BFCS",\
"BPCS.txt" using 1:3 with linespoints title "BPCS",\

set output "method_e.pdf"
set title miss."E"
plot \
"EFCS.txt" using 1:3 with linespoints title "EFCS",\
"EPCS.txt" using 1:3 with linespoints title "EPCS",\

set output "method_q.pdf"
set title miss."Q"
plot \
"QFCS.txt" using 1:3 with linespoints title "QFCS",\
"QPCS.txt" using 1:3 with linespoints title "QPCS",\