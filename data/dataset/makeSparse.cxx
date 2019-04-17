#include <iostream>
#include <fstream>
#include <Eigen/Dense>
using Eigen::MatrixXd;
using Eigen::VectorXd;
#define REP(i,n) for(int i=(0);i<(n);i++)

int main(const int argc, const char *argv[]){
  std::string argv0=argv[1];
  //int row = atoi(argv[2]);
  //int col = atoi(argv[3]);
  std::ifstream ifs(argv0);
  if(ifs.fail()){
    std::cerr<<"argv0 error\n"
	     <<"./a.out datasetname/datasetfile(.txt) rows cols"
	     <<std::endl;
    exit(1);
  }
  int row,col;
  ifs>>row>>col;
  MatrixXd A = MatrixXd::Zero(row, col);
  VectorXd B = VectorXd::Zero(row);
  double value[row][col];
  REP(i,row){
    REP(j,col){
      ifs>>value[i][j];
      A(i,j)=value[i][j];
    }
  }
  ifs.close();
  std::string str="";
  str+="sparse_";
  for(int i=0;i<(int)argv0.size()-4;i++){
    str+=argv0[i];
  }
  
  std::ofstream ofs(str+".dat");
  ofs<<row<<" "<<col<<std::endl;
  REP(i,row){
    REP(j,col){
      if(A(i,j))
        B(i)++;
    }
    ofs<<B[i]<<" ";
    REP(j,col){
      if(A(i,j))
        ofs<<j<<" "<<A(i,j)<<" ";
    }
    ofs<<std::endl;
  }
  return 0;
}
