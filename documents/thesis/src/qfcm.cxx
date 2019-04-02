#include"qfcm.h"

Qfcm::Qfcm(int dimension,
	   int data_number,
	   int centers_number,
	   double fuzzifierEm,
	   double fuzzifierLambda):
  Hcm(dimension, data_number, centers_number),
  Sfcm(dimension, data_number, centers_number,fuzzifierEm),
  Efcm(dimension, data_number, centers_number,fuzzifierLambda){
}

void Qfcm::revise_membership(void){
  Tmp_Membership=Membership;
  for(int k=0;k<data_number();k++){
    int numZeroDissimilarities=0;
    Vector indexZeroDissimilarities(centers_number(), 0.0, "all");
    for(int i=0;i<centers_number();i++){
      if(Dissimilarities[i][k]==0.0){
	numZeroDissimilarities++;
	indexZeroDissimilarities[i]=1.0;
      }
    }
    if(numZeroDissimilarities!=0){
      for(int i=0;i<centers_number();i++){
	Membership[i][k]=indexZeroDissimilarities[i]/numZeroDissimilarities;
      }
    }
    else{
      for(int i=0;i<centers_number();i++){
        double denominator=0.0;
        for(int j=0;j<centers_number();j++){
          //帰属度
          denominator+=(FuzzifierLambda*(FuzzifierEm-1.0)*Dissimilarities[i][k]+1)/(FuzzifierLambda*(FuzzifierEm-1.0)*Dissimilarities[j][k]+1.0);
      }
      Membership[i][k]=1.0/pow(denominator,1/(1.0-FuzzifierEm));
      }
    }//else
  }//k
    return;
}

void Qfcm::revise_centers(void){
  Sfcm::revise_centers();
  return;
}
