#include"sparseQfcma.h"

SparseQfcma::SparseQfcma(int dimension,
             int data_number,
             int centers_number,
             double fuzzifierEm,
             double fuzzifierLambda) :
  SparseHcm(dimension, data_number, centers_number),
  SparseSfcma(dimension, data_number, centers_number,fuzzifierEm),
  SparseEfcma(dimension, data_number, centers_number,fuzzifierLambda){
}

void SparseQfcma::revise_membership(void){
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
          denominator+=Clusters_Size[j]/Clusters_Size[i]
            *pow((1.0-FuzzifierLambda*(1.0-FuzzifierEm)
                  *Dissimilarities[j][k])
                /(1.0-FuzzifierLambda*(1.0-FuzzifierEm)
                  *Dissimilarities[i][k])
                 ,1.0/(1.0-FuzzifierEm));
        }
        Membership[i][k]=1.0/denominator;
      }
    }//else
  }//k
  return;
}

void SparseQfcma::revise_centers(void){
  SparseSfcma::revise_centers();
  return;
}

void SparseQfcma::revise_clusters_size(void){
  Tmp_Clusters_Size=Clusters_Size;
  double denominator=0.0;
  for(int j=0;j<centers_number();j++){
    double tmp1=0.0;
    for(int k=0;k<data_number();k++){
      tmp1+=pow(Membership[j][k],FuzzifierEm)
        *(1.0-FuzzifierLambda*(1.0-FuzzifierEm)*Dissimilarities[j][k]);
    }
    denominator+=pow(tmp1,1.0/FuzzifierEm);
  }
  for(int i=0;i<centers_number();i++){
    double tmp2=0.0;
    for(int k=0;k<data_number();k++){
      tmp2+=pow(Membership[i][k],FuzzifierEm)
        *(1.0-FuzzifierLambda*(1.0-FuzzifierEm))*Dissimilarities[i][k];
    }
    Clusters_Size[i]=pow(tmp2,1/FuzzifierEm)/denominator;
  }
  return;
}
