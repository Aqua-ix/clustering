set key left font "Arial,15"
set xlabel "Number of Missing Values" font "Arial,15"
set ylabel "MAE" font "Arial,15"
set xrange [1500:7500]
set xtics 500
plot \
"BFCS_CLISP_minimalMAE.txt" with linespoints title "BFCS(Clisp)",\
"EFCS_CLISP_minimalMAE.txt" with linespoints title "EFCS(Clisp)",\
"QFCS_CLISP_minimalMAE.txt" with linespoints title "QFCS(Clisp)",\
"BFCS_OVERLAP_minimalMAE.txt" with linespoints title "BFCS(Overlap)",\
"EFCS_OVERLAP_minimalMAE.txt" with linespoints title "EFCS(Overlap)",\
"QFCS_OVERLAP_minimalMAE.txt" with linespoints title "QFCS(Overlap)"
