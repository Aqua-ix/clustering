#include<cmath>
#include<cfloat>
#include"matrix.h"
#include"hcm.h"
#include"efcm.h"

#ifndef __EFCMA__
#define __EFCMA__

class Efcma:public Efcm{
protected:
  double FuzzifierLambda;
public:
  Efcma(int dimension,
       int data_number,
       int centers_number,
       double fuzzifierLambda);
  double fuzzifierLambda(void)const;
  double &fuzzifierLambda(void);
  void revise_membership(void);
  void revise_centers(void);
  void revise_alpha(void);
};

#endif
