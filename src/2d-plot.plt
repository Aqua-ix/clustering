splot "HCM-2d-Gaussian-2clusters.result_classificationFunction" using 1:2:3 title "funcsion1"  with lines lc rgb "green", "HCM-2d-Gaussian-2clusters.result_classificationFunction" using 1:2:4 title "funcsion2"  with lines lc rgb "blue", "< awk '{if($3>$4){print $1, $2, $3;}}' HCM-2d-Gaussian-2clusters.result_membership" title "cluster1" lc rgb "purple", "< awk '{if($4>$3){print $1, $2, $4;}}' HCM-2d-Gaussian-2clusters.result_membership"  title "cluster2" lc rgb "yellow"
set hidden3d
replot
set ticslevel 0
set key below 
set ztics 0.1
set xlabel 'dimension 1'
set ylabel 'dimension 2'
set zlabel 'membership' rotate by 90
set xlabel font "Arial,15"
set ylabel font "Arial,15"
set zlabel font "Arial,15"
set key font "Arial,15"
set key spacing 4.0
set zrange [0:1]
replot