#include<cmath>
#include<cfloat>
#include"matrix.h"
#include"sparseHcm.h"

#ifndef __SPARSE_SFCM__
#define __SPARSE_SFCM__

class SparseSfcm: virtual public SparseHcm{
protected:
  double FuzzifierEm;
public:
  SparseSfcm(int dimension,
       int data_number,
       int centers_number,
       double fuzzifierEm);
  double fuzzifierEm(void)const;
  double &fuzzifierEm(void);
  virtual void revise_membership(void);
  virtual void revise_centers(void);
};

#endif

