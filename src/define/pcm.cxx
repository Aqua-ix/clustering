#include"pcm.h"

PCM::PCM(int dimension,
         int data_number,
         int centers_number,
         double alpha): 
  HCM(dimension, data_number, centers_number),
  Alpha(alpha),
  Membership_Threshold(data_number),
  Membership_PCM(data_number, data_number),
  Centers_PCM(data_number,dimension),
  Clusters_Count(0){
}

double &PCM::alpha(void){//可能性パラメータ
  return Alpha;
}

int &PCM::clusters_count(void){
  return Clusters_Count;
}

void PCM::initialize_centers_one_cluster(int index){//初期クラスタ中心
  for(int ell=0;ell<dimension();ell++)
    Centers[0][ell]=0.0;
  for(int ell=0;ell<Data[index].essencialSize();ell++)
    Centers[0][Data[index].indexIndex(ell)]=Data[index].elementIndex(ell);
  return;
}

void PCM::ofs_membership(void){//帰属度出力
  std::ofstream ofs("membership.txt");
  for(int k=0;k<data_number();k++)
    ofs<<Membership[0][k]<<" ";
  return;
}

Matrix PCM::membership_pcm(void){//可能性の帰属度
  return Membership_PCM;
}

Matrix PCM::centers_pcm(void){//可能性のクラスタ中心
  return Centers_PCM;
}

Vector PCM::membership_threshold(void){//帰属度しきい値(中央値入れる)
  return Membership_Threshold;
}

double mid(Vector x){//ソートして中央値算出
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

void PCM::save_membership(int index){//帰属度保存
  for(int k=0;k<data_number();k++){
    Membership_PCM[index][k]=Membership[0][k];
  }
  //帰属度中央値を保存
  Membership_Threshold[index]=mid(Membership_PCM[index]);
  return;
}

void PCM::marge_centers(){
  bool same=false;
  double threshold = 1.0;
  for(int i=0;i<Centers_PCM.rows();i++){
    if(norm_square(Centers[0]-Centers_PCM[i])<threshold){
      same=true;
    }
  }
  if(same==false){
    Centers_PCM[Clusters_Count]=Centers[0];
    Membership_PCM[Clusters_Count]=Membership[0];
    Clusters_Count++;
  }
  return;
}
