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
### example : eFCMA
```
g++ -DCLASSIFICATION_FUNCTION -DCHECK_ANSWER -std=c++11 hcm.cxx efcm.cxx qfcm.cxx sfcm.cxx efcma.cxx qfcma.cxx sfcma.cxx matrix.cxx vector.cxx efcma_main_2d-Gaussian-2clusters.cxx
```
To show graph, use [gnuplot](http://www.gnuplot.info/).
```
gnuplot
gnuplot > splot "qFCM-Em2.000000-2d-Gaussian-2clusters.result_classificationFunction" using 1:2:3 with lines, "qFCM-Em2.000000-2d-Gaussian-2clusters.result_classificationFunction" using 1:2:4 with lines, "< awk '{if($3>$4){print $1, $2, $3;}}' qFCM-Em2.000000-2d-Gaussian-2clusters.result_membership", "< awk '{if($4>$3){print $1, $2, $4;}}' qFCM-Em2.000000-2d-Gaussian-2clusters.result_membership"
```
