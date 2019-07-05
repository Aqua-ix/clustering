#include"hcm.h"

#ifndef __PCM__
#define __PCM__

class PCM: virtual public HCM{
protected:
  double Alpha;
  Vector Membership_Threshold;
  double Centers_Threshold;
  Matrix Membership_PCM;
  Matrix Centers_PCM;
  int Clusters_Count;
public:
  PCM(int dimension,
      int data_number,
      int centers_number,
      double alpha);
  double &alpha(void);
  int &clusters_count(void);//クラスタ数カウント
  void initialize_centers_one_cluster(int);//初期クラスタ中心の設定
  Matrix membership_pcm(void);//可能性の帰属度
  Matrix centers_pcm(void);//可能性のクラスタ中心
  Vector membership_threshold(void);//帰属度のしきい値(中央値)
  double &centers_threshold(void);//クラスタ中心マージのしきい値
  void save_membership(int index);//帰属度保存
  void marge_centers(void);//クラスタ中心のマージ
  void centers_pcm_reset(void);//可能性のクラスタ中心初期化
};

#endif
