set terminal pdf
set output "artificiality_".miss."_ALL.pdf"
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

set output "artificiality_".miss."_FCS.pdf"
plot \
"BFCS.txt" using 1:3 with linespoints title "BFCS",\
"EFCS.txt" using 1:3 with linespoints title "EFCS",\
"QFCS.txt" using 1:3 with linespoints title "QFCS",\

set output "artificiality_".miss."_PCS.pdf"
plot \
"BPCS.txt" using 1:3 with linespoints title "BPCS",\
"EPCS.txt" using 1:3 with linespoints title "EPCS",\
"QPCS.txt" using 1:3 with linespoints title "QPCS",\

set output "artificiality_".miss."_B.pdf"
plot \
"BFCS.txt" using 1:3 with linespoints title "BFCS",\
"BPCS.txt" using 1:3 with linespoints title "BPCS",\

set output "artificiality_".miss."_E.pdf"
plot \
"EFCS.txt" using 1:3 with linespoints title "EFCS",\
"EPCS.txt" using 1:3 with linespoints title "EPCS",\

set output "artificiality_".miss."_Q.pdf"
plot \
"QFCS.txt" using 1:3 with linespoints title "QFCS",\
"QPCS.txt" using 1:3 with linespoints title "QPCS",\
