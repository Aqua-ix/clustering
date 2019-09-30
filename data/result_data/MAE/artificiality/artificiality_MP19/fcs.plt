set terminal svg
set output "fcs.svg"
set key left font "Arial,15"
set xlabel "欠損数" font "Arial,15"
set ylabel "MAE" font "Arial,15"
set xrange [1500:7500]
set yrange [0:0.7]
set xtics 500
plot \
"BFCS_CRISP_averageMAE.txt" with linespoints title "BFCS(CRISP)",\
"EFCS_CRISP_averageMAE.txt" with linespoints title "EFCS(CRISP)",\
"QFCS_CRISP_averageMAE.txt" with linespoints title "QFCS(CRISP)",\
"BFCS_OVERLAP_averageMAE.txt" with linespoints title "BFCS(OVERLAP)",\
"EFCS_OVERLAP_averageMAE.txt" with linespoints title "EFCS(OVERLAP)",\
"QFCS_OVERLAP_averageMAE.txt" with linespoints title "QFCS(OVERLAP)"
