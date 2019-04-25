#include"hcs.h"
#include"efcm.h"

#ifndef __EFCS__
#define __EFCS__

class EFCS: public HCS, public EFCM{
public:
  EFCS(int dimension,
	int data_number,
	int centers_number,
	double fuzzifierLambda);
  virtual void revise_centers(void);

};

#endif
