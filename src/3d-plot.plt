 splot "qFCMA_RD.txt" using 1:2:3 with lines,
 set hidden3d
 unset key
 set zlabel 'ARI' rotate by 90
 set xlabel 'm'
 set ylabel '{/symbol l}'
 set ticslevel 0
 set xlabel font "Arial,15"
 set ylabel font "Arial,15"
 set zlabel font "Arial,15"
 set logscale y 2
 set xrange [1:2.5]
 replot
 
