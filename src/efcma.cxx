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
	  denominator+=exp(-1.0*FuzzifierLambda*Dissimilarities[j][k])/exp(-1.0*FuzzifierLambda*Dissimilarities[i][k]);;
	}
	Membership[i][k]=1.0/denominator;
      }
    }//else
  }//k
    return;
}

void Efcma::revise_centers(void){
  Tmp_Centers=Centers;
  for(int i=0;i<centers_number();i++){
    double denominator=0.0;
    Vector numerator(dimension(), 0.0, "all");
    for(int k=0;k<data_number();k++){
      denominator+=Membership[i][k];
      numerator+=Membership[i][k]*Data[k];
    }
    Centers[i]=numerator/denominator;
  }
  return;
}


void Efcma::revise_alpha(void){
  Tmp_Alpha=Alpha;
  for(int i=0;i<centers_number();i++){
    double denominator=0.0;
    Vector numerator(dimension(), 0.0, "all");
    for(int k=0;k<data_number();k++){
      denominator+=Membership[i][k];
      numerator+=Membership[i][k]*Data[k];
    }
    Centers[i]=numerator/denominator;
  }
  return;
}
