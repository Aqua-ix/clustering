set terminal svg
set output "bfcs_overlap.svg"
set key left font "Arial,15"
set xlabel "欠損数" font "Arial,15"
set ylabel "MAE" font "Arial,15"
set xrange [1500:7500]
set yrange [0:0.7]
set xtics 500
plot \
"../artificiality_MP19_overlap_threshold0.000000/BFCS_OVERLAP_averageMAE.txt" using 1:3 with linespoints title "BFCS(0.0)",\
"../artificiality_MP19_overlap_threshold0.100000/BFCS_OVERLAP_averageMAE.txt" using 1:3 with linespoints title "BFCS(0.1)",\
"../artificiality_MP19_overlap_threshold0.200000/BFCS_OVERLAP_averageMAE.txt" using 1:3 with linespoints title "BFCS(0.2)",\
"../artificiality_MP19_overlap_threshold0.300000/BFCS_OVERLAP_averageMAE.txt" using 1:3 with linespoints title "BFCS(0.3)",\
"../artificiality_MP19_overlap_threshold0.400000/BFCS_OVERLAP_averageMAE.txt" using 1:3 with linespoints title "BFCS(0.4)",\
"../artificiality_MP19_overlap_threshold0.500000/BFCS_OVERLAP_averageMAE.txt" using 1:3 with linespoints title "BFCS(0.5)",\
"../artificiality_MP19_overlap_threshold0.600000/BFCS_OVERLAP_averageMAE.txt" using 1:3 with linespoints title "BFCS(0.6)",\
"../artificiality_MP19_overlap_threshold0.700000/BFCS_OVERLAP_averageMAE.txt" using 1:3 with linespoints title "BFCS(0.7)",\
"../artificiality_MP19_overlap_threshold0.800000/BFCS_OVERLAP_averageMAE.txt" using 1:3 with linespoints title "BFCS(0.8)",\
"../artificiality_MP19_overlap_threshold0.900000/BFCS_OVERLAP_averageMAE.txt" using 1:3 with linespoints title "BFCS(0.9)",\
"../artificiality_MP19_overlap_threshold1.000000/BFCS_OVERLAP_averageMAE.txt" using 1:3 with linespoints title "BFCS(1.0)",\
