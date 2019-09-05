set terminal svg
set output "qfcs_overlap.svg"
set key left font "Arial,15"
set xlabel "欠損数" font "Arial,15"
set ylabel "MAE" font "Arial,15"
set xrange [1500:7500]
set yrange [0:0.7]
set xtics 500
plot \
"../artificiality_MP19_overlap_threshold0.200000/QFCS_OVERLAP_averageMAE.txt" with linespoints title "QFCS(80%)",\
"../artificiality_MP19_overlap_threshold0.400000/QFCS_OVERLAP_averageMAE.txt" with linespoints title "QFCS(60%)",\
"../artificiality_MP19_overlap_threshold0.600000/QFCS_OVERLAP_averageMAE.txt" with linespoints title "QFCS(40%)",\
