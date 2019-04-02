#include<cmath>
#include<cfloat>
#include"matrix.h"
#include"hcm.h"

#ifndef __EFCM__
#define __EFCM__

class Efcm: virtual public Hcm{
protected:
  double FuzzifierLambda;
public:
  Efcm(int dimension,
       int data_number,
       int centers_number,
       double fuzzifierLambda);
  double fuzzifierLambda(void)const;
  double &fuzzifierLambda(void);
  virtual void revise_membership(void);
  virtual void revise_centers(void);
};

#endif

