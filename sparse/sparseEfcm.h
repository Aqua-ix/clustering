#include<cmath>
#include<cfloat>
#include"sparseMatrix.h"
#include"sparseHcm.h"

#ifndef __SPARSE_EFCM__
#define __SPARSE_EFCM__

class SparseEfcm: virtual public SparseHcm{
protected:
  double FuzzifierLambda;
public:
  SparseEfcm(int dimension,
       int data_number,
       int centers_number,
       double fuzzifierLambda);
  double fuzzifierLambda(void)const;
  double &fuzzifierLambda(void);
  virtual void revise_membership(void);
  virtual void revise_centers(void);
};

#endif
