#include"pcm.h"

PCM::PCM(int dimension,
         int data_number,
         int centers_number,
         double alpha): 
  HCM(dimension, data_number, centers_number),
  Alpha(alpha),
  Membership_Threshold(data_number),
  Centers_Threshold(0),
  Membership_PCM(data_number, data_number),
  Centers_PCM(data_number,dimension),
  Clusters_Count(1)
  {
}

double &PCM::alpha(void){
  return Alpha;
}

int &PCM::clusters_count(void){
  return Clusters_Count;
}

void PCM::initialize_centers_one_cluster(int index){
  for(int ell=0;ell<dimension();ell++)
    Centers[0][ell]=0.0;
  for(int ell=0;ell<Data[index].essencialSize();ell++)
    Centers[0][Data[index].indexIndex(ell)]
      = Data[index].elementIndex(ell);
  return;
}

Matrix PCM::membership_pcm(void){
  return Membership_PCM;
}

Matrix PCM::centers_pcm(void){
  return Centers_PCM;
}

Vector PCM::membership_threshold(void){
  return Membership_Threshold;
}

double &PCM::centers_threshold(void){
  return Centers_Threshold;
}

//ソートして中央値算出
double mid(Vector x){
  for (int i = 0; i < x.size() - 1; i++){
    int j = i;    
    for (int k = i; k < x.size(); k++){
      if (x[k] < x[j]) j = k;
    }
    if (i < j){
      double v = x[i];
      x[i] = x[j]; x[j] = v;
    }
  }
  return (x.size() % 2 == 0) ?
    (x[x.size()/2-1]+x[x.size()/2])/2.0 :
    x[x.size()/2];
}

//帰属度保存
void PCM::save_membership(int index){
  for(int k=0;k<data_number();k++){
    Membership_PCM[index][k]=Membership[0][k];
  }
  //帰属度中央値を保存
  Membership_Threshold[index]=mid(Membership_PCM[index]);
  return;
}

void PCM::marge_centers(){
  bool same=false;
  for(int i=0;i<Centers_PCM.rows();i++){
    if(squared_norm(Centers[0]-Centers_PCM[i])
       <= Centers_Threshold){
      same=true;
      break;
    }
  }
  if(same==false){
    Centers_PCM[Clusters_Count-1]=Centers[0];
    Membership_PCM[Clusters_Count-1]=Membership[0];
    if(Clusters_Count!=Centers_PCM.rows()){
      Clusters_Count++;
    }
  }
  return;
}

void PCM::centers_pcm_reset(void){
  for(int i=0;i<data_number();i++){
    for(int j=0;j<dimension();j++){
      Centers_PCM[i][j]=0.0;
    }
  }
  return;
}
