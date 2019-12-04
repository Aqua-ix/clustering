set terminal pdf
set output data."_".miss."_ALL_AUC.pdf"
set key outside font "Arial,15"
set xlabel "オーバーラップ閾値" font "Arial,15"
set xrange [0.2:1.0]
set yrange [0.67:0.685]
set xtics 0.1
set ylabel "AUC" font "Arial,15"
set ytics 0.005
plot \
"BFCS.txt" using 1:3 with linespoints title "BFCS",\
"EFCS.txt" using 1:3 with linespoints title "EFCS",\
"QFCS.txt" using 1:3 with linespoints title "QFCS",\
"BPCS.txt" using 1:3 with linespoints title "BPCS",\
"EPCS.txt" using 1:3 with linespoints title "EPCS",\
"QPCS.txt" using 1:3 with linespoints title "QPCS",\

set output  data."_".miss."_FCS_AUC.pdf"
plot \
"BFCS.txt" using 1:3 with linespoints title "BFCS",\
"EFCS.txt" using 1:3 with linespoints title "EFCS",\
"QFCS.txt" using 1:3 with linespoints title "QFCS",\

set output  data."_".miss."_PCS_AUC.pdf"
plot \
"BPCS.txt" using 1:3 with linespoints title "BPCS",\
"EPCS.txt" using 1:3 with linespoints title "EPCS",\
"QPCS.txt" using 1:3 with linespoints title "QPCS",\

set output  data."_".miss."_B_AUC.pdf"
plot \
"BFCS.txt" using 1:3 with linespoints title "BFCS",\
"BPCS.txt" using 1:3 with linespoints title "BPCS",\

set output  data."_".miss."_E_AUC.pdf"
plot \
"EFCS.txt" using 1:3 with linespoints title "EFCS",\
"EPCS.txt" using 1:3 with linespoints title "EPCS",\

set output  data."_".miss."_Q_AUC.pdf"
plot \
"QFCS.txt" using 1:3 with linespoints title "QFCS",\
"QPCS.txt" using 1:3 with linespoints title "QPCS",\
