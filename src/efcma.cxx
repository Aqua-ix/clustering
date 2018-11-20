
#include"efcma.h"

Efcma::Efcma(int dimension,
	   int data_number,
	   int centers_number,   
	   double fuzzifierLambda) 
  : Hcm(dimension, data_number, centers_number),
    Efcm(dimension, data_number, centers_number, fuzzifierLambda){
}

void Efcma::revise_membership(void){
  Tmp_Membership=Membership;
  for(int k=0;k<data_number();k++){
    for(int i=0;i<centers_number();i++){
      double denominator=0.0;
      for(int j=0;j<centers_number();j++){
        denominator+=(Alpha[j]/Alpha[i])*exp(FuzzifierLambda*(Dissimilarities[i][k]-Dissimilarities[j][k]));
      }
      //std::cout<<denominator<<" "<<FuzzifierLambda<<std::endl;
      Membership[i][k]=1.0/denominator;
    }
  }//k
  return;
}

void Efcma::revise_alpha(void){
  Tmp_Alpha=Alpha;
  for(int i=0;i<centers_number();i++){
    double numerator=0;
    for(int k=0;k<data_number();k++){
      numerator+=Membership[i][k];
    }
    Alpha[i]=numerator/data_number();
  }
  return;
}
