#include"efcma.h"

Efcma::Efcma(int dimension,
	   int data_number,
	   int centers_number,
	   double fuzzifierLambda) 
  : Hcm(dimension, data_number, centers_number),
    Efcm(dimension, data_number, centers_number, fuzzifierLambda){
}


double Efcma::fuzzifierLambda(void)const{
  return FuzzifierLambda;
}

double &Efcma::fuzzifierLambda(void){
  return FuzzifierLambda;
}

void Efcma::revise_membership(void){
  Tmp_Membership=Membership;
  for(int k=0;k<data_number();k++){
    for(int i=0;i<centers_number();i++){
      double denominator=0.0;
      for(int j=0;j<centers_number();j++){
        denominator+=exp(-1.0*FuzzifierLambda*Dissimilarities[j][k])/exp(-1.0*FuzzifierLambda*Dissimilarities[i][k]);;
      }
      Membership[i][k]=1.0/denominator;
    }//else
  }//k
  return;
}

void Efcma::revise_alpha(void){
  Tmp_Alpha=Alpha;
  for(int i=0;i<centers_number();i++){
    Vector numerator(dimension(), 0.0, "all");
    for(int k=0;k<data_number();k++){
      numerator+=Membership[i][k];
    }
    Centers[i]=numerator/data_number();
  }
  return;
}
