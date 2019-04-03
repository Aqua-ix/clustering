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

### sFCMA
```
g++ -DCLASSIFICATION_FUNCTION -DCHECK_ANSWER -std=c++11 hcm.cxx efcm.cxx qfcm.cxx sfcm.cxx efcma.cxx qfcma.cxx sfcma.cxx matrix.cxx vector.cxx sfcma_main_2d-Gaussian-2clusters.cxx
```
To show graph, use [gnuplot](http://www.gnuplot.info/).
```
splot "sFCMA-Emx.000000-2d-Gaussian-2clusters.result_classificationFunction" using 1:2:3 with lines, "sFCMA-Emx.000000-2d-Gaussian-2clusters.result_classificationFunction" using 1:2:4 with lines, "< awk '{if($3>$4){print $1, $2, $3;}}' sFCMA-Emx.000000-2d-Gaussian-2clusters.result_membership", "< awk '{if($4>$3){print $1, $2, $4;}}' sFCMA-Emx.000000-2d-Gaussian-2clusters.result_membership"
```

### eFCMA
```
g++ -DCLASSIFICATION_FUNCTION -DCHECK_ANSWER -std=c++11 hcm.cxx efcm.cxx qfcm.cxx sfcm.cxx efcma.cxx qfcma.cxx sfcma.cxx matrix.cxx vector.cxx efcma_main_2d-Gaussian-2clusters.cxx
```
To show graph, use [gnuplot](http://www.gnuplot.info/).
```
splot "eFCMA-Lambdax.000000-2d-Gaussian-2clusters.result_classificationFunction" using 1:2:3 with lines, "eFCMA-Lambdax.000000-2d-Gaussian-2clusters.result_classificationFunction" using 1:2:4 with lines, "< awk '{if($3>$4){print $1, $2, $3;}}' eFCMA-Lambdax.000000-2d-Gaussian-2clusters.result_membership", "< awk '{if($4>$3){print $1, $2, $4;}}' eFCMA-Lambdax.000000-2d-Gaussian-2clusters.result_membership"
```

### qFCMA
```
g++ -DCLASSIFICATION_FUNCTION -DCHECK_ANSWER -std=c++11 hcm.cxx efcm.cxx qfcm.cxx sfcm.cxx efcma.cxx qfcma.cxx sfcma.cxx matrix.cxx vector.cxx qfcma_main_2d-Gaussian-2clusters.cxx
```
To show graph, use [gnuplot](http://www.gnuplot.info/).
```
splot "qFCMA-Emx.000000-Lambdax.000000-2d-Gaussian-2clusters.result_classificationFunction" using 1:2:3 with lines, "qFCMA-Emx.000000-Lambdax.000000-2d-Gaussian-2clusters.result_classificationFunction" using 1:2:4 with lines, "< awk '{if($3>$4){print $1, $2, $3;}}' qFCMA-Emx.000000-Lambdax.000000-2d-Gaussian-2clusters.result_membership", "< awk '{if($4>$3){print $1, $2, $4;}}' qFCMA-Emx.000000-Lambdax.000000-2d-Gaussian-2clusters.result_membership"
```

## For sparse data

### HCM
```
g++ -DCHECK_ANSWER -std=c++11 vector.cxx matrix.cxx sparseVector.cxx sparseMatrix.cxx sparseHcm.cxx sparseHcm_main_2d-Gaussian-2clusters-sparse1002.cxx
```

### sFCMA
```
g++ -DCHECK_ANSWER -std=c++11 vector.cxx matrix.cxx sparseVector.cxx sparseMatrix.cxx sparseHcm.cxx sparseSfcm.cxx sparseSfcma.cxx sparseSfcma_main_2d-Gaussian-2clusters.cxx
```

### eFCMA
```
g++ -DCHECK_ANSWER -std=c++11 vector.cxx matrix.cxx sparseVector.cxx sparseMatrix.cxx sparseHcm.cxx sparseEfcm.cxx sparseEfcma.cxx sparseEfcma_main_2d-Gaussian-2clusters.cxx
```

### qFCMA
```
g++ -DCHECK_ANSWER -std=c++11 vector.cxx matrix.cxx sparseVector.cxx sparseMatrix.cxx sparseHcm.cxx sparseSfcm.cxx sparseSfcma.cxx sparseEfcm.cxx sparseEfcma.cxx sparseQfcm.cxx sparseQfcma.cxx sparseQfcma_main_2d-Gaussian-2clusters.cxx
```

#Documents
##thesis
Command of Insert Font to PDF
```
dvipdfmx -f texfonts.map thesisAbst2018.dvi
```