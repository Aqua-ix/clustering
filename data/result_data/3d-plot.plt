set terminal qt enhanced
splot "qFCMA-user-knowledge.result.ari" using 1:2:3 with lines,
set hidden3d
unset key
set ticslevel 0
set xlabel '{/symbol l}'
set ylabel 'm'
set zlabel 'ARI' rotate by 90
set xlabel font "Arial,15"
set ylabel font "Arial,15"
set zlabel font "Arial,15"
set xrange [10:100]
set yrange [1:3]
replot
 
