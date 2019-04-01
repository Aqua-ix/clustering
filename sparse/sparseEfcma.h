#include"sparseEfcm.h"

#ifndef __SPARSE_EFCMA__
#define __SPARSE_EFCMA__

class SparseEfcma: public SparseEfcm {
public:
  SparseEfcma(
       int dimension,
       int data_number,
       int centers_number,
       double fuzzifierLambda);
  void revise_membership(void);
  void revise_clusters_size(void);
};

#endif

