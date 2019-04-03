#include<cmath>
#include<cfloat>
#include"matrix.h"
#include"hcm.h"
#include"sfcm.h"
#include"efcm.h"

#ifndef __QFCM__
#define __QFCM__

class Qfcm: public Sfcm, public Efcm{
public:
  Qfcm(int dimension,
       int data_number,
       int centers_number,
       double fuzzifierEm,
       double fuzzifierLambda);
  virtual void revise_membership(void);
  virtual void revise_centers(void);
};

#endif

