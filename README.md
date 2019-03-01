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


### sFCMA
```
g++ -DCLASSIFICATION_FUNCTION -DCHECK_ANSWER -std=c++11 hcm.cxx efcm.cxx qfcm.cxx sfcm.cxx efcma.cxx qfcma.cxx sfcma.cxx matrix.cxx vector.cxx sfcma_main_2d-Gaussian-2clusters.cxx
```
To show graph, use [gnuplot](http://www.gnuplot.info/).
```
splot "sFCMA-Emx.000000-2d-Gaussian-2clusters.result_classificationFunction" using 1:2:3 with lines, "sFCMA-Emx.000000-2d-Gaussian-2clusters.result_classificationFunction" using 1:2:4 with lines, "< awk '{if($3>$4){print $1, $2, $3;}}' sFCMA-Emx.000000-2d-Gaussian-2clusters.result_membership", "< awk '{if($4>$3){print $1, $2, $4;}}' sFCMA-Emx.000000-2d-Gaussian-2clusters.result_membership"
```

# 進捗
- 2019/02/06 13:00-15:00 概要書「はじめに」作成
- 2019/02/13 13:00-16:40 概要書「実験内容」作成
- 2019/02/20 13:00-16:40 概要書「人工データ実験の結果」作成
- 2019/02/27 13:00-16:40 概要書「実データ実験の結果」作成
- 2019/02/28 13:00~00:00 概要書「まとめと今後の課題」作成 第一稿提出
- 2019/03/01 16:00~18:00 論文構成作成
