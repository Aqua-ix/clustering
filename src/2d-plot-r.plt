splot "qFCMA-Em2.000000-Lambda10.000000-2d-Gaussian-2clusters.result_classificationFunction" using 1:2:3 title "funcsion1"  with lines lc rgb "blue", "qFCMA-Em2.000000-Lambda10.000000-2d-Gaussian-2clusters.result_classificationFunction" using 1:2:4 title "funcsion2"  with lines lc rgb "green", "< awk '{if($3>$4){print $1, $2, $3;}}' qFCMA-Em2.000000-Lambda10.000000-2d-Gaussian-2clusters.result_membership" title "cluster1" lc rgb "yellow", "< awk '{if($4>$3){print $1, $2, $4;}}' qFCMA-Em2.000000-Lambda10.000000-2d-Gaussian-2clusters.result_membership"  title "cluster2" lc rgb "purple"
set hidden3d
replot
set ticslevel 0
set key outside center bottom
set ztics 0.1
set xlabel 'dimension 1'
set ylabel 'dimension 2'
set zlabel 'membership' rotate by 90
set xlabel font "Arial,15"
 set ylabel font "Arial,15"
 set zlabel font "Arial,15"
 set key font "Arial,15"
replot