set terminal qt
set output "fcs_overlap.svg"
set key left font "Arial,15"
set xlabel "欠損数" font "Arial,15"
set ylabel "MAE" font "Arial,15"
set xrange [1500:7500]
set yrange [0:0.7]
set xtics 500
plot \
"artificiality_MP19_overlap_threshold0.000000/BFCS_OVERLAP_averageMAE.txt" with linespoints title "BFCS(100%)",\
"artificiality_MP19_overlap_threshold0.000000/EFCS_OVERLAP_averageMAE.txt" with linespoints title "EFCS(100%)",\
"artificiality_MP19_overlap_threshold0.000000/QFCS_OVERLAP_averageMAE.txt" with linespoints title "QFCS(100%)",\
"artificiality_MP19_overlap_threshold0.100000/BFCS_OVERLAP_averageMAE.txt" with linespoints title "BFCS(90%)",\
"artificiality_MP19_overlap_threshold0.100000/EFCS_OVERLAP_averageMAE.txt" with linespoints title "EFCS(90%)",\
"artificiality_MP19_overlap_threshold0.100000/QFCS_OVERLAP_averageMAE.txt" with linespoints title "QFCS(90%)",\
"artificiality_MP19_overlap_threshold0.200000/BFCS_OVERLAP_averageMAE.txt" with linespoints title "BFCS(80%)",\
"artificiality_MP19_overlap_threshold0.200000/EFCS_OVERLAP_averageMAE.txt" with linespoints title "EFCS(80%)",\
"artificiality_MP19_overlap_threshold0.200000/QFCS_OVERLAP_averageMAE.txt" with linespoints title "QFCS(80%)",\
"artificiality_MP19_overlap_threshold0.300000/BFCS_OVERLAP_averageMAE.txt" with linespoints title "BFCS(70%)",\
"artificiality_MP19_overlap_threshold0.300000/EFCS_OVERLAP_averageMAE.txt" with linespoints title "EFCS(70%)",\
"artificiality_MP19_overlap_threshold0.300000/QFCS_OVERLAP_averageMAE.txt" with linespoints title "QFCS(70%)",\
"artificiality_MP19_overlap_threshold0.400000/BFCS_OVERLAP_averageMAE.txt" with linespoints title "BFCS(60%)",\
"artificiality_MP19_overlap_threshold0.400000/EFCS_OVERLAP_averageMAE.txt" with linespoints title "EFCS(60%)",\
"artificiality_MP19_overlap_threshold0.400000/QFCS_OVERLAP_averageMAE.txt" with linespoints title "QFCS(60%)",\
"artificiality_MP19_overlap_threshold0.500000/BFCS_OVERLAP_averageMAE.txt" with linespoints title "BFCS(50%)",\
"artificiality_MP19_overlap_threshold0.500000/EFCS_OVERLAP_averageMAE.txt" with linespoints title "EFCS(50%)",\
"artificiality_MP19_overlap_threshold0.500000/QFCS_OVERLAP_averageMAE.txt" with linespoints title "QFCS(50%)",\
"artificiality_MP19_overlap_threshold0.600000/BFCS_OVERLAP_averageMAE.txt" with linespoints title "BFCS(40%)",\
"artificiality_MP19_overlap_threshold0.600000/EFCS_OVERLAP_averageMAE.txt" with linespoints title "EFCS(40%)",\
"artificiality_MP19_overlap_threshold0.600000/QFCS_OVERLAP_averageMAE.txt" with linespoints title "QFCS(40%)",\
"artificiality_MP19_overlap_threshold0.700000/BFCS_OVERLAP_averageMAE.txt" with linespoints title "BFCS(30%)",\
"artificiality_MP19_overlap_threshold0.700000/EFCS_OVERLAP_averageMAE.txt" with linespoints title "EFCS(30%)",\
"artificiality_MP19_overlap_threshold0.700000/QFCS_OVERLAP_averageMAE.txt" with linespoints title "QFCS(30%)",\
"artificiality_MP19_overlap_threshold0.800000/BFCS_OVERLAP_averageMAE.txt" with linespoints title "BFCS(20%)",\
"artificiality_MP19_overlap_threshold0.800000/EFCS_OVERLAP_averageMAE.txt" with linespoints title "EFCS(20%)",\
"artificiality_MP19_overlap_threshold0.800000/QFCS_OVERLAP_averageMAE.txt" with linespoints title "QFCS(20%)",\
"artificiality_MP19_overlap_threshold0.900000/BFCS_OVERLAP_averageMAE.txt" with linespoints title "BFCS(10%)",\
"artificiality_MP19_overlap_threshold0.900000/EFCS_OVERLAP_averageMAE.txt" with linespoints title "EFCS(10%)",\
"artificiality_MP19_overlap_threshold0.900000/QFCS_OVERLAP_averageMAE.txt" with linespoints title "QFCS(10%)"
