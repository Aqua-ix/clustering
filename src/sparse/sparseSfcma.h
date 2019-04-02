#include"sparseHcm.h"
#include"sparseSfcm.h"

#ifndef __SPARSE_SFCMA__
#define __SPARSE_SFCMA__

class SparseSfcma: virtual public SparseHcm, public SparseSfcm{
 public:
  SparseSfcma(const int &dimension,
        const int &data_number,
        const int &centers_number,
        const double &fuzzifierEm);
  virtual void revise_membership(void);
  virtual void revise_clusters_size(void);
};
#endif
