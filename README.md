# Clustering
C++ Programming for Clustering

# Algorythm
 - HCM
 - sFCM
 - eFCM
 - qFCM
 - sFCMA
 - eFCMA
 - qFCMA

# Run
```
g++ -DCLASSIFICATION_FUNCTION -DCHECK_ANSWER -std=c++11 hcm.cxx qfcm.cxx sfcm.cxx efcm.cxx  matrix.cxx vector.cxx qfcm_main_2d-Gaussian-2clusters.cxx
```

```
gnuplot
splot "qFCM-Em2.000000-2d-Gaussian-2clusters.result_classificationFunction" using 1:2:3 with lines, "qFCM-Em2.000000-2d-Gaussian-2clusters.result_classificationFunction" using 1:2:4 with lines, "< awk '{if($3>$4){print $1, $2, $3;}}' qFCM-Em2.000000-2d-Gaussian-2clusters.result_membership", "< awk '{if($4>$3){print $1, $2, $4;}}' qFCM-Em2.000000-2d-Gaussian-2clusters.result_membership"
```
