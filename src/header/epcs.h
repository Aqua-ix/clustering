#include"pcm.h"
#include"efcs.h"

#ifndef __EPCS__
#define __EPCS__

class EPCS: public EFCS, public PCM{
public:
  EPCS(int dimension,
       int data_number,
       int centers_number,
       double fuzzifierLambda,
       double alpha);
  virtual void revise_membership(void);
  virtual void revise_centers(void);
  virtual void set_objective(void);
};

#endif
