#include"bpcs.h"

BPCS::BPCS(int dimension,
	   int data_number,
	   int centers_number,
	   double fuzzifierEm,
	   double alpha): 
  HCM(dimension, data_number, centers_number),
  HCMA(dimension, data_number, centers_number),
  BFCS(dimension, data_number, centers_number, fuzzifierEm),
  PCM(dimension, data_number, centers_number, alpha){
}

void BPCS::revise_membership(void){
#ifdef CHECK_CLASS
  std::cout<<"BPCS::revise_membership"<<std::endl;
#endif
  Tmp_Membership=Membership;
  for(int k=0;k<data_number();k++){ 
    for(int i=0;i<centers_number();i++){
      double denominator=0.0;
      denominator=pow(Dissimilarities[i][k]/Alpha,
		      1.0/(FuzzifierEm-1.0));
      Membership[i][k]=1.0/(1.0+denominator);
    }
  }
  
  return;
}

void BPCS::set_objective(void){
  Objective=0.0;
  for(int i=0;i<centers_number();i++){
    for(int k=0;k<data_number();k++){
      Objective+=pow(Membership[i][k],FuzzifierEm)*Dissimilarities[i][k]
	-Alpha*pow((1.0-Membership[i][k]),FuzzifierEm);
    }
  }
  return;
}
