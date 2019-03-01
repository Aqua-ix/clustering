#include"sfcma.h"

Sfcma::Sfcma(const int &dimension,
             const int &data_number,
             const int &centers_number,
             const double &fuzzifierEm) : 
  Hcm(dimension, data_number, centers_number),
  Sfcm(dimension, data_number, centers_number,fuzzifierEm){
}

void Sfcma::revise_membership(void){
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
          denominator+=Alpha[j]/Alpha[i]
            *pow(Dissimilarities[i][k]/Dissimilarities[j][k],
            1.0/(FuzzifierEm-1.0));
        }
        Membership[i][k]=1.0/denominator;
      }
    }
  }
  return;
}

void Sfcma::revise_centers(void){
  Sfcm::revise_centers();
  return;
}

void Sfcma::revise_alpha(void){
  Tmp_Alpha=Alpha;
  double denominator=0.0;
  for(int j=0;j<centers_number();j++){
    double tmp1=0.0;
    for(int k=0;k<data_number();k++){
      tmp1+=pow(Membership[j][k],FuzzifierEm)*Dissimilarities[j][k];
    }
    denominator+=pow(tmp1,1.0/FuzzifierEm);
  }
  for(int i=0;i<centers_number();i++){
    double tmp2=0.0;
    for(int k=0;k<data_number();k++){
      tmp2+=pow(Membership[i][k],FuzzifierEm)*Dissimilarities[i][k];
    }
    Alpha[i]=pow(tmp2,1.0/FuzzifierEm)/denominator;
  }
  return;
}
