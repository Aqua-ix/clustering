#include<random>
#include<iostream>
#include<fstream>

int main(void){
  std::random_device rnd;
  std::mt19937 mt(rnd());
  std::normal_distribution<> normDist(0.0, 1.0);

  const int dimension=2, eachDataNum=250, clusterNum=2;
  const double means[clusterNum][dimension]={
    {-0.8,-0.8},{0.8,0.8}};
  const double stddevs[clusterNum][dimension]={
    {0.5,0.5},{0.5,0.5}};

  const int dataNum = eachDataNum*clusterNum;
  std::string fileName
    = "test_"
    + std::to_string(dataNum)+ "_"
    + std::to_string(dimension) + ".txt";
  std::ofstream nOfs(fileName,std::ios::out);

  std::string sparseFileName
    = "sparse_test_"
    + std::to_string(dataNum) + "_"
    + std::to_string(dimension) + ".txt";
  std::ofstream sOfs(sparseFileName ,std::ios::out);
  
  for(int i=0;i<clusterNum;i++){
    for(int k=0;k<eachDataNum;k++){
      sOfs << dimension << "\t";
      for(int ell=0;ell<dimension;ell++){
        double data = normDist(mt)*stddevs[i][ell]+means[i][ell];
        nOfs << data  << "\t";
        sOfs << ell << "\t";
        sOfs << data << "\t";
      }
      nOfs << std::endl;
      sOfs << std::endl;
    }
  }
  
  return 0;
}
