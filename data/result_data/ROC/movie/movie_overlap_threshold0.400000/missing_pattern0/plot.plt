set terminal pdf
set xlabel "FP/(FP+TN)"
set ylabel "TP/(TP+FN)"
set output "../../graph/".data."_roc_".ot."_p".pt.".pdf"
set key font "Arial, 20"
set key outside
plot \
"BFCS_OVERLAP_ROC_".pt.".txt" with linespoints title "BFCS" pointsize 0.5, \
"EFCS_OVERLAP_ROC_".pt.".txt" with linespoints title "BFCS" pointsize 0.5, \
"QFCS_OVERLAP_ROC_".pt.".txt" with linespoints title "BFCS" pointsize 0.5, \
"BPCS_OVERLAP_ROC_".pt.".txt" with linespoints title "BPCS" pointsize 0.5, \
"EPCS_OVERLAP_ROC_".pt.".txt" with linespoints title "EPCS" pointsize 0.5, \
"QPCS_OVERLAP_ROC_".pt.".txt" with linespoints title "QPCS" pointsize 0.5, \

