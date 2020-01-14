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
  int &clusters_count(void);
  void initialize_centers_one_cluster(int);
  Matrix membership_pcm(void);
  Matrix centers_pcm(void);
  Vector membership_threshold(void);
  double &centers_threshold(void);
  void marge_centers(void);
  void save_membership(int index);
  void centers_pcm_reset(void);
};

#endif
