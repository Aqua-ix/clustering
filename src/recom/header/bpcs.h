#include"pcm.h"
#include"bfcs.h"

#ifndef __BPCS__
#define __BPCS__

class BPCS: public BFCS, public PCM{
public:
  BPCS(int dimension,
       int data_number,
       int centers_number,
       double fuzzifierEm,
       double alpha);
  virtual void revise_membership(void);
  virtual void set_objective(void);
};

#endif
