set terminal svg
set output "fcs.svg"
set key left font "Arial,15"
set xlabel "欠損数" font "Arial,15"
set ylabel "MAE" font "Arial,15"
set xrange [1500:7500]
set yrange [0:0.7]
set xtics 500
plot \
"BFCS_CLISP_averageMAE.txt" with linespoints title "BFCS(Clisp)",\
"EFCS_CLISP_averageMAE.txt" with linespoints title "EFCS(Clisp)",\
"QFCS_CLISP_averageMAE.txt" with linespoints title "QFCS(Clisp)",\
"BFCS_OVERLAP_averageMAE.txt" with linespoints title "BFCS(Overlap)",\
"EFCS_OVERLAP_averageMAE.txt" with linespoints title "EFCS(Overlap)",\
"QFCS_OVERLAP_averageMAE.txt" with linespoints title "QFCS(Overlap)"
