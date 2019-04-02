
#include"efcm.h"

#ifndef __EFCMA__
#define __EFCMA__

class Efcma: public Efcm {
public:
  Efcma(
       int dimension,
       int data_number,
       int centers_number,
       double fuzzifierLambda);
  void revise_membership(void);
  void revise_alpha(void);
};

#endif

