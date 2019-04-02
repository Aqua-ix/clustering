#include<cmath>
#include<cfloat>
#include"matrix.h"
#include"hcm.h"

#ifndef __SFCM__
#define __SFCM__

class Sfcm: virtual public Hcm{
protected:
  double FuzzifierEm;
public:
  Sfcm(int dimension,
       int data_number,
       int centers_number,
       double fuzzifierEm);
  double fuzzifierEm(void)const;
  double &fuzzifierEm(void);
  virtual void revise_membership(void);
  virtual void revise_centers(void);
};

#endif

