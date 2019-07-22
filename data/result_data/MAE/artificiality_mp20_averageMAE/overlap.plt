set terminal svg
set output "overlap.svg"
set key left font "Arial,15"
set xlabel "欠損数" font "Arial,15"
set ylabel "MAE" font "Arial,15"
set xrange [1500:7500]
set xtics 500
plot \
"GROUPLENS_averageMAE.txt" with linespoints ps 2 title "GroupLens",\
"BFCS_OVERLAP_averageMAE.txt" with linespoints title "BFCS",\
"EFCS_OVERLAP_averageMAE.txt" with linespoints title "EFCS",\
"QFCS_OVERLAP_averageMAE.txt" with linespoints title "QFCS",\
"BPCS_OVERLAP_averageMAE.txt" with linespoints title "BPCS",\
"EPCS_OVERLAP_averageMAE.txt" with linespoints title "EPCS",\
"QPCS_OVERLAP_averageMAE.txt" with linespoints title "QPCS"\
