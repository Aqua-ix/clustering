# Clustering
C++ Programming for Clustering

# Algorythm
 - HCM
 - eFCM
 - qFCM
 - sFCM
 - eFCMA
 - qFCMA
 - sFCMA

# Run
## Require
[Boost C++ Libraries](https://www.boost.org/)

## Command
### eFCMA
```
g++ -DCLASSIFICATION_FUNCTION -DCHECK_ANSWER -std=c++11 hcm.cxx efcm.cxx qfcm.cxx sfcm.cxx efcma.cxx qfcma.cxx sfcma.cxx matrix.cxx vector.cxx efcma_main_2d-Gaussian-2clusters.cxx
```
To show graph, use [gnuplot](http://www.gnuplot.info/).
```
splot "eFCMA-2d-Gaussian-2clusters.result_classificationFunction" using 1:2:3 with lines, "eFCMA-2d-Gaussian-2clusters.result_classificationFunction" using 1:2:4 with lines, "< awk '{if($3>$4){print $1, $2, $3;}}' eFCMA-2d-Gaussian-2clusters.result_membership", "< awk '{if($4>$3){print $1, $2, $4;}}' eFCMA-2d-Gaussian-2clusters.result_membership"
```

### qFCMA
```
g++ -DCLASSIFICATION_FUNCTION -DCHECK_ANSWER -std=c++11 hcm.cxx efcm.cxx qfcm.cxx sfcm.cxx efcma.cxx qfcma.cxx sfcma.cxx matrix.cxx vector.cxx qfcma_main_2d-Gaussian-2clusters.cxx
```
To show graph, use [gnuplot](http://www.gnuplot.info/).
```
splot "qFCMA-2d-Gaussian-2clusters.result_classificationFunction" using 1:2:3 with lines, "qFCMA-2d-Gaussian-2clusters.result_classificationFunction" using 1:2:4 with lines, "< awk '{if($3>$4){print $1, $2, $3;}}' qFCMA-2d-Gaussian-2clusters.result_membership", "< awk '{if($4>$3){print $1, $2, $4;}}' qFCMA-2d-Gaussian-2clusters.result_membership"
```


### sFCMA
```
g++ -DCLASSIFICATION_FUNCTION -DCHECK_ANSWER -std=c++11 hcm.cxx efcm.cxx qfcm.cxx sfcm.cxx efcma.cxx qfcma.cxx sfcma.cxx matrix.cxx vector.cxx sfcma_main_2d-Gaussian-2clusters.cxx
```
To show graph, use [gnuplot](http://www.gnuplot.info/).
```
splot "sFCMA-2d-Gaussian-2clusters.result_classificationFunction" using 1:2:3 with lines, "sFCMA-2d-Gaussian-2clusters.result_classificationFunction" using 1:2:4 with lines, "< awk '{if($3>$4){print $1, $2, $3;}}' sFCMA-2d-Gaussian-2clusters.result_membership", "< awk '{if($4>$3){print $1, $2, $4;}}' sFCMA-2d-Gaussian-2clusters.result_membership"
```

