#include<cmath>
#include<cfloat>
#include"matrix.h"

#ifndef __HCM__
#define __HCM__

class Hcm{
 protected:
  Matrix Data, Centers, Tmp_Centers;
  Matrix Membership, Tmp_Membership, Dissimilarities;
  Matrix CrispMembership, CorrectCrispMembership, ContingencyTable;
  int Iterates;
  double Objective;
 public:
  Hcm(int dimension,
      int data_number,
      int centers_number);
  virtual void revise_membership(void);
  virtual void revise_dissimilarities(void);
  virtual void revise_centers(void);
  int dimension(void) const;
  int data_number(void) const;
  int centers_number(void) const;
  Matrix centers(void) const;
  Matrix tmp_centers(void) const;
  Matrix data(void) const;
  Matrix membership(void) const;
  Matrix tmp_membership(void) const;
  Vector alpha(void) const;
  Vector tmp_alpha(void) const;
  int &iterates(void);
  Matrix dissimilarities(void) const;
  double &data(int index1, int index2); 
  Vector &data(int index1); 
  double &centers(int index1, int index2); 
  Vector &centers(int index1); 
  double &membership(int index1, int index2); 
  double &dissimilarities(int index1, int index2);
  void set_objective(void);
  double objective(void) const;
  void set_crispMembership(void);
  Matrix crispMembership(void) const;
  double &crispMembership(int index1, int index2);
  Matrix correctCrispMembership(void) const;
  double &correctCrispMembership(int index1, int index2);
  void set_contingencyTable(void);
  Matrix contingencyTable(void) const;
  double ARI(void) const;
};

#endif
