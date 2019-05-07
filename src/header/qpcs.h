#include"pcm.h"
#include"qfcs.h"

#ifndef __QPCS__
#define __QPCS__

class QPCS: public PCM, public QFCS{
 public:
  QPCS(int dimension,
       int data_number,
       int centers_number,
       double fuzzifierEm,
       double fuzzifierLambda,
       double alpha);
  virtual void revise_membership(void);
  virtual void set_objective(void);
};

#endif
