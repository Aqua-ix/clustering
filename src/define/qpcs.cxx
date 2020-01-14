#include"qpcs.h"

QPCS::QPCS(int dimension,
	   int data_number,
	   int centers_number,
	   double fuzzifierEm,
	   double fuzzifierLambda,
	   double alpha): 
  HCM(dimension, data_number, centers_number),
  HCMA(dimension, data_number, centers_number),
  PCM(dimension, data_number, centers_number, alpha),
  QFCS(dimension, data_number, centers_number,
       fuzzifierEm, fuzzifierLambda){
}

void QPCS::revise_membership(void){
#ifdef CHECK_CLASS
  std::cout<<"QPCS::revise_membership"<<std::endl;
#endif
  Tmp_Membership=Membership;
  for(int i=0;i<centers_number();i++){
    for(int k=0;k<data_number();k++){
      double formula=0.0;
      formula
        =(1.01
          -FuzzifierLambda
          *(1.01-FuzzifierEm)
          *Dissimilarities[i][k]);
      if(formula<0){
	formula=0;
      }
      Membership[i][k]=pow(formula, 1.01/(1.01-FuzzifierEm));
    }
  }
  return;
}
