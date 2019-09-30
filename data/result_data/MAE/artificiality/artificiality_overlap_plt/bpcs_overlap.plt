set terminal svg
set output "bpcs_overlap.svg"
set key left font "Arial,15"
set xlabel "欠損数" font "Arial,15"
set ylabel "MAE" font "Arial,15"
set xrange [1500:7500]
set yrange [0:0.7]
set xtics 500
plot \
"../artificiality_MP19_overlap_threshold0.000000/BPCS_OVERLAP_averageMAE.txt" with linespoints title "BPCS(100%)",\
"../artificiality_MP19_overlap_threshold0.100000/BPCS_OVERLAP_averageMAE.txt" with linespoints title "BPCS(90%)",\
"../artificiality_MP19_overlap_threshold0.200000/BPCS_OVERLAP_averageMAE.txt" with linespoints title "BPCS(80%)",\
"../artificiality_MP19_overlap_threshold0.300000/BPCS_OVERLAP_averageMAE.txt" with linespoints title "BPCS(70%)",\
"../artificiality_MP19_overlap_threshold0.400000/BPCS_OVERLAP_averageMAE.txt" with linespoints title "BPCS(60%)",\
"../artificiality_MP19_overlap_threshold0.500000/BPCS_OVERLAP_averageMAE.txt" with linespoints title "BPCS(50%)",\
"../artificiality_MP19_overlap_threshold0.600000/BPCS_OVERLAP_averageMAE.txt" with linespoints title "BPCS(40%)",\
"../artificiality_MP19_overlap_threshold0.700000/BPCS_OVERLAP_averageMAE.txt" with linespoints title "BPCS(30%)",\
"../artificiality_MP19_overlap_threshold0.800000/BPCS_OVERLAP_averageMAE.txt" with linespoints title "BPCS(20%)",\
"../artificiality_MP19_overlap_threshold0.900000/BPCS_OVERLAP_averageMAE.txt" with linespoints title "BPCS(10%)",\
