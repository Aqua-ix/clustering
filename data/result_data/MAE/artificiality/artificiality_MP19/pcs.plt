set terminal svg
set output "pcs.svg"
set key left font "Arial,15"
set xlabel "欠損数" font "Arial,15"
set ylabel "MAE" font "Arial,15"
set xrange [1500:7500]
set xtics 500
plot \
"BPCS_CRISP_averageMAE.txt" with linespoints title "BPCS(CRISP)",\
"EPCS_CRISP_averageMAE.txt" with linespoints title "EPCS(CRISP)",\
"QPCS_CRISP_averageMAE.txt" with linespoints title "QPCS(CRISP)",\
"BPCS_OVERLAP_averageMAE.txt" with linespoints title "BPCS(OVERLAP)",\
"EPCS_OVERLAP_averageMAE.txt" with linespoints title "EPCS(OVERLAP)",\
"QPCS_OVERLAP_averageMAE.txt" with linespoints title "QPCS(OVERLAP)"
