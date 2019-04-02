#include"sparseEfcma.h"
#include"sparseSfcma.h"

#ifndef __SPARSE_QFCMA__
#define __SPARSE_QFCMA__

class SparseQfcma: public SparseEfcma, public SparseSfcma{

public:
  SparseQfcma(int dimension,
        int data_number,
        int centers_number,
        double fuzzifierEm,
        double fuzzifierLambda);
  virtual void revise_membership(void);
  virtual void revise_centers(void);
  virtual void revise_clusters_size(void);
};

#endif

