set terminal svg
set output "fcs_overlap.svg"
set key left font "Arial,15"
set xlabel "欠損数" font "Arial,15"
set ylabel "MAE" font "Arial,15"
set xrange [1500:7500]
set yrange [0:0.7]
set xtics 500
plot \
"artificiality_MP19_overlap_threshold0.200000/BFCS_OVERLAP_averageMAE.txt" with linespoints title "BFCS(80%)",\
"artificiality_MP19_overlap_threshold0.200000/EFCS_OVERLAP_averageMAE.txt" with linespoints title "EFCS(80%)",\
"artificiality_MP19_overlap_threshold0.200000/QFCS_OVERLAP_averageMAE.txt" with linespoints title "QFCS(80%)",\
"artificiality_MP19_overlap_threshold0.400000/BFCS_OVERLAP_averageMAE.txt" with linespoints title "BFCS(60%)",\
"artificiality_MP19_overlap_threshold0.400000/EFCS_OVERLAP_averageMAE.txt" with linespoints title "EFCS(60%)",\
"artificiality_MP19_overlap_threshold0.400000/QFCS_OVERLAP_averageMAE.txt" with linespoints title "QFCS(60%)",\
"artificiality_MP19_overlap_threshold0.600000/BFCS_OVERLAP_averageMAE.txt" with linespoints title "BFCS(40%)",\
"artificiality_MP19_overlap_threshold0.600000/EFCS_OVERLAP_averageMAE.txt" with linespoints title "EFCS(40%)",\
"artificiality_MP19_overlap_threshold0.600000/QFCS_OVERLAP_averageMAE.txt" with linespoints title "QFCS(40%)"
