set key left font "Arial,15"
set xlabel "Number of Missing Values" font "Arial,15"
set ylabel "MAE" font "Arial,15"
set xrange [1500:7500]
set xtics 500
plot \
"GROUPLENS_minimalMAE.txt" with linespoints ps 2 title "GroupLens",\
"BFCS_OVERLAP_minimalMAE.txt" with linespoints title "BFCS",\
"EFCS_OVERLAP_minimalMAE.txt" with linespoints title "EFCS",\
"QFCS_OVERLAP_minimalMAE.txt" with linespoints title "QFCS",\
"BPCS_OVERLAP_minimalMAE.txt" with linespoints title "BPCS",\
"EPCS_OVERLAP_minimalMAE.txt" with linespoints title "EPCS",\
"QPCS_OVERLAP_minimalMAE.txt" with linespoints title "QPCS"\
