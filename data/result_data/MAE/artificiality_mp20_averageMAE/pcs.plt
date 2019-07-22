set terminal svg
set output "pcs.svg"
set key left font "Arial,15"
set xlabel "欠損数" font "Arial,15"
set ylabel "MAE" font "Arial,15"
set xrange [1500:7500]
set xtics 500
plot \
"BPCS_CLISP_averageMAE.txt" with linespoints title "BPCS(Clisp)",\
"EPCS_CLISP_averageMAE.txt" with linespoints title "EPCS(Clisp)",\
"QPCS_CLISP_averageMAE.txt" with linespoints title "QPCS(Clisp)",\
"BPCS_OVERLAP_averageMAE.txt" with linespoints title "BPCS(Overlap)",\
"EPCS_OVERLAP_averageMAE.txt" with linespoints title "EPCS(Overlap)",\
"QPCS_OVERLAP_averageMAE.txt" with linespoints title "QPCS(Overlap)"
