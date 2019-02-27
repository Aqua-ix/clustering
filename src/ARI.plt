set terminal qt enhanced
set output "sFCMA_ARI.pdf"
plot "sfcma_user_knowledge_ARI.txt" with line
set xlabel "{/Italic m}"
set ylabel "ARI"
unset key
replot