#include<fstream>
#include<iostream>

int main(void){
  std::ifstream ifs("2d-Gaussian-2clusters.dat");
  int dataNumber;
  int dimension;
  ifs >> dataNumber >> dimension;
  std::ofstream ofs("2d-Gaussian-2clusters-sparse1002.dat");
  ofs << dataNumber << "\t" << dimension+1000 << std::endl;
  for(int k=0;k<dataNumber;k++){
    ofs << dimension << "\t";
    double value;
    for(int ell=0;ell<dimension;ell++){
      ifs >> value;
      ofs << 500+ell << "\t" << value << "\t";
    }
    ofs << std::endl;
  }
  return 0;
}
