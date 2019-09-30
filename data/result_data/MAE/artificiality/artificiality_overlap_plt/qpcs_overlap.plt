set terminal svg
set output "qpcs_overlap.svg"
set key left font "Arial,15"
set xlabel "欠損数" font "Arial,15"
set ylabel "MAE" font "Arial,15"
set xrange [1500:7500]
set yrange [0:0.7]
set xtics 500
plot \
"../artificiality_MP19_overlap_threshold0.000000/QPCS_OVERLAP_averageMAE.txt" with linespoints title "QPCS(100%)",\
"../artificiality_MP19_overlap_threshold0.100000/QPCS_OVERLAP_averageMAE.txt" with linespoints title "QPCS(90%)",\
"../artificiality_MP19_overlap_threshold0.200000/QPCS_OVERLAP_averageMAE.txt" with linespoints title "QPCS(80%)",\
"../artificiality_MP19_overlap_threshold0.300000/QPCS_OVERLAP_averageMAE.txt" with linespoints title "QPCS(70%)",\
"../artificiality_MP19_overlap_threshold0.400000/QPCS_OVERLAP_averageMAE.txt" with linespoints title "QPCS(60%)",\
"../artificiality_MP19_overlap_threshold0.500000/QPCS_OVERLAP_averageMAE.txt" with linespoints title "QPCS(50%)",\
"../artificiality_MP19_overlap_threshold0.600000/QPCS_OVERLAP_averageMAE.txt" with linespoints title "QPCS(40%)",\
"../artificiality_MP19_overlap_threshold0.700000/QPCS_OVERLAP_averageMAE.txt" with linespoints title "QPCS(30%)",\
"../artificiality_MP19_overlap_threshold0.800000/QPCS_OVERLAP_averageMAE.txt" with linespoints title "QPCS(20%)",\
"../artificiality_MP19_overlap_threshold0.900000/QPCS_OVERLAP_averageMAE.txt" with linespoints title "QPCS(10%)",\
