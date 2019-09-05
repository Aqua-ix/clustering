set terminal svg
set output "pcs_overlap.svg"
set key left font "Arial,15"
set xlabel "欠損数" font "Arial,15"
set ylabel "MAE" font "Arial,15"
set xrange [1500:7500]
set xtics 500
plot \
"artificiality_MP19_overlap_threshold0.200000/BPCS_OVERLAP_averageMAE.txt" with linespoints title "BPCS(80%)",\
"artificiality_MP19_overlap_threshold0.200000/EPCS_OVERLAP_averageMAE.txt" with linespoints title "EPCS(80%)",\
"artificiality_MP19_overlap_threshold0.200000/QPCS_OVERLAP_averageMAE.txt" with linespoints title "QPCS(80%)",\
"artificiality_MP19_overlap_threshold0.400000/BPCS_OVERLAP_averageMAE.txt" with linespoints title "BPCS(60%)",\
"artificiality_MP19_overlap_threshold0.400000/EPCS_OVERLAP_averageMAE.txt" with linespoints title "EPCS(60%)",\
"artificiality_MP19_overlap_threshold0.400000/QPCS_OVERLAP_averageMAE.txt" with linespoints title "QPCS(60%)",\
"artificiality_MP19_overlap_threshold0.600000/BPCS_OVERLAP_averageMAE.txt" with linespoints title "BPCS(40%)",\
"artificiality_MP19_overlap_threshold0.600000/EPCS_OVERLAP_averageMAE.txt" with linespoints title "EPCS(40%)",\
"artificiality_MP19_overlap_threshold0.600000/QPCS_OVERLAP_averageMAE.txt" with linespoints title "QPCS(40%)"
