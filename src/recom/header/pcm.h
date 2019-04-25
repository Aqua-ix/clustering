#include"hcm.h"

#ifndef __PCM__
#define __PCM__

class PCM: virtual public HCM{
protected:
  double Alpha;
  Vector Membership_Threshold;
  Matrix Membership_PCM;
public:
  PCM(int dimension,
      int data_number,
      int centers_number,
      double alpha);
  double &alpha(void);
  void initialize_centers_one_cluster(int);
  void ofs_membership(void);
  Matrix membership_pcm(void);//可能性の帰属度
  Vector membership_threshold(void);//帰属度のしきい値(中央値)
  void save_membebrship(int index);//帰属度保存
};

#endif
