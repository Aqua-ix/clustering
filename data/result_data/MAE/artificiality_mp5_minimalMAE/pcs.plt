set key left font "Arial,15"
set xlabel "Number of Missing Values" font "Arial,15"
set ylabel "MAE" font "Arial,15"
set xrange [1500:7500]
set xtics 500
plot \
"BPCS_CLISP_minimalMAE.txt" with linespoints title "BPCS(Clisp)",\
"EPCS_CLISP_minimalMAE.txt" with linespoints title "EPCS(Clisp)",\
"QPCS_CLISP_minimalMAE.txt" with linespoints title "QPCS(Clisp)",\
"BPCS_OVERLAP_minimalMAE.txt" with linespoints title "BPCS(Overlap)",\
"EPCS_OVERLAP_minimalMAE.txt" with linespoints title "EPCS(Overlap)",\
"QPCS_OVERLAP_minimalMAE.txt" with linespoints title "QPCS(Overlap)"
