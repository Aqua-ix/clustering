#include"hcma.h"

#ifndef __EFCM__
#define __EFCM__

class EFCM: virtual public HCMA{
protected:
  //KLダイバージェンス正則化項に付与したパラメータ
  double FuzzifierLambda;
public:
  EFCM(int dimension,
	int data_number,
	int centers_number,
	double fuzzifierLambda);
  double &fuzzifierLambda(void);
  virtual void revise_membership(void);
  virtual void revise_clusters_size(void);
  virtual void set_objective(void);
};

#endif
