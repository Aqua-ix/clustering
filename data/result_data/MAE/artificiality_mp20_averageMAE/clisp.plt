set terminal svg
set output "clisp.svg"
set key left font "Arial,15"
set xlabel "欠損数" font "Arial,15"
set ylabel "MAE" font "Arial,15"
set xrange [1500:7500]
set xtics 500
plot \
"GROUPLENS_averageMAE.txt" with linespoints ps 2 title "GroupLens",\
"BFCS_CLISP_averageMAE.txt" with linespoints title "BFCS",\
"EFCS_CLISP_averageMAE.txt" with linespoints title "EFCS",\
"QFCS_CLISP_averageMAE.txt" with linespoints title "QFCS",\
"BPCS_CLISP_averageMAE.txt" with linespoints title "BPCS",\
"EPCS_CLISP_averageMAE.txt" with linespoints title "EPCS",\
"QPCS_CLISP_averageMAE.txt" with linespoints title "QPCS"\
