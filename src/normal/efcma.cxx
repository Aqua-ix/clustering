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
        denominator+=(Clusters_Size[j]/Clusters_Size[i])*exp(FuzzifierLambda*(Dissimilarities[i][k]-Dissimilarities[j][k]));
      }
      Membership[i][k]=1.0/denominator;
    }
  }
  return;
}

void Efcma::revise_clusters_size(void){
  Tmp_Clusters_Size=Clusters_Size;
  for(int i=0;i<centers_number();i++){
    double numerator=0;
    for(int k=0;k<data_number();k++){
      numerator+=Membership[i][k];
    }
    Clusters_Size[i]=numerator/data_number();
  }
  return;
}
