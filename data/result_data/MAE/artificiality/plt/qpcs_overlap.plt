set terminal svg
set output "qpcs_overlap.svg"
set key left font "Arial,15"
set xlabel "欠損数" font "Arial,15"
set ylabel "MAE" font "Arial,15"
set xrange [1500:7500]
set yrange [0:0.7]
set xtics 500
plot \
"../artificiality_MP19_overlap_threshold0.000000/QPCS_OVERLAP_averageMAE.txt" using 1:3 with linespoints title "QPCS(0.0)",\
"../artificiality_MP19_overlap_threshold0.100000/QPCS_OVERLAP_averageMAE.txt" using 1:3 with linespoints title "QPCS(0.1)",\
"../artificiality_MP19_overlap_threshold0.200000/QPCS_OVERLAP_averageMAE.txt" using 1:3 with linespoints title "QPCS(0.2)",\
"../artificiality_MP19_overlap_threshold0.300000/QPCS_OVERLAP_averageMAE.txt" using 1:3 with linespoints title "QPCS(0.3)",\
"../artificiality_MP19_overlap_threshold0.400000/QPCS_OVERLAP_averageMAE.txt" using 1:3 with linespoints title "QPCS(0.4)",\
"../artificiality_MP19_overlap_threshold0.500000/QPCS_OVERLAP_averageMAE.txt" using 1:3 with linespoints title "QPCS(0.5)",\
"../artificiality_MP19_overlap_threshold0.600000/QPCS_OVERLAP_averageMAE.txt" using 1:3 with linespoints title "QPCS(0.6)",\
"../artificiality_MP19_overlap_threshold0.700000/QPCS_OVERLAP_averageMAE.txt" using 1:3 with linespoints title "QPCS(0.7)",\
"../artificiality_MP19_overlap_threshold0.800000/QPCS_OVERLAP_averageMAE.txt" using 1:3 with linespoints title "QPCS(0.8)",\
"../artificiality_MP19_overlap_threshold0.900000/QPCS_OVERLAP_averageMAE.txt" using 1:3 with linespoints title "QPCS(0.9)",\
"../artificiality_MP19_overlap_threshold1.000000/QPCS_OVERLAP_averageMAE.txt" using 1:3 with linespoints title "QPCS(1.0)",\
