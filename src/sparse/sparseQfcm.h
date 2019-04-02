#include<cmath>
#include<cfloat>
#include"sparseMatrix.h"
#include"sparseHcm.h"
#include"sparseSfcm.h"
#include"sparseEfcm.h"

#ifndef __QFCM__
#define __QFCM__

class SparseQfcm: public SparseSfcm, public SparseEfcm{
public:
  SparseQfcm(int dimension,
       int data_number,
       int centers_number,
       double fuzzifierEm,
       double fuzzifierLambda);
  void revise_membership(void);
  void revise_centers(void);
};

#endif

