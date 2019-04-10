#include<iostream>
#include<fstream>
#include<cstdlib>
#include<random>
#include"sparseQfcm.h"
#include"config.h"

#define MAX_ITERATES 100000
#define DIFF_FOR_STOP 1.0E-10

const int centers_number=2;

int main(void){

  double fuzzifierEm = EM;
  double fuzzifierLambda = LAMBDA;
  
  std::string filenameData("2d-Gaussian-2clusters-sparse1002.dat");
  std::string filenameCorrectCrispMembership("2d-Gaussian-2clusters.correctCrispMembership");

  std::string::size_type filenameDataDotPosition=filenameData.find_last_of(".");
  if(filenameDataDotPosition==std::string::npos){
    std::cerr << "File:" << filenameData
	      << " needs \".\" and filename-extention." << std::endl;
    exit(1);
  }

  std::ifstream ifs(DATA_DIR+filenameData);
  if(!ifs){
    std::cerr << "File:" << filenameData
	      << " could not open." << std::endl;
    exit(1);
  }
  int data_number, data_dimension;
  ifs >> data_number;
  ifs >> data_dimension;
	
  SparseQfcm test(data_dimension, data_number, centers_number, fuzzifierEm, fuzzifierLambda);
  
  for(int cnt=0;cnt<data_number;cnt++){
    int essencialSize;
    ifs >> essencialSize;
    SparseVector dummy(data_dimension, essencialSize);
    for(int ell=0;ell<essencialSize;ell++){
      ifs >> dummy.indexIndex(ell) >> dummy.elementIndex(ell);
    }
    test.data(cnt)=dummy;
  }

  /***Initial Centers Setting***/
  std::random_device rnd;
  std::mt19937 mt(rnd());
  std::uniform_int_distribution<> randDataNumber(0,test.data_number()-1);
 
  std::ifstream ifs_correctCrispMembership(DATA_DIR+filenameCorrectCrispMembership);
  if(!ifs_correctCrispMembership){
    std::cerr << "File:" << filenameCorrectCrispMembership
	      << " could not open." << std::endl;
    exit(1);
  }
  for(int i=0;i<test.centers_number();i++){
    for(int k=0;k<test.data_number();k++){
      ifs_correctCrispMembership >> test.correctCrispMembership(i, k);
    }
  }
  
  for(int i=0;i<test.centers_number();i++){
    for(int k=0;k<test.data_number();k++){
      test.membership(i,k)=test.correctCrispMembership(i, k);
    }
  }

  test.iterates()=0;
  while(1){
    test.revise_centers();
#ifdef VERBOSE
    std::cout << "v:\n" << test.centers() << std::endl;
#endif
    test.revise_dissimilarities();
#ifdef VERBOSE
    std::cout << "d:\n" << test.dissimilarities() << std::endl;
#endif  
    test.revise_membership();
#ifdef VERBOSE
    std::cout << "u:\n" << test.membership() << std::endl;
#endif
  
    double diff_u=max_norm(test.tmp_membership()-test.membership());
    double diff_v=max_norm(test.tmp_centers()-test.centers());
    double diff=diff_u+diff_v;
#ifdef DIFF
    std::cout << "#diff:" << diff << "\t";
    std::cout << "#diff_u:" << diff_u << "\t";
    std::cout << "#diff_v:" << diff_v << "\n";
#endif
    if(diff<DIFF_FOR_STOP)break;
    if(test.iterates()>=MAX_ITERATES)break;
    test.iterates()++;
  }
#ifdef VERBOSE
  std::cout << "v:\n" << test.centers() << std::endl;
#endif

#ifdef CHECK_ANSWER
  test.set_crispMembership();
  for(int i=0;i<test.centers_number();i++){
    for(int k=0;k<test.data_number();k++){
      ifs_correctCrispMembership >> test.correctCrispMembership(i, k);
    }
  }
  test.set_contingencyTable();
  std::cout << "Contingency Table:\n" << test.contingencyTable() << std::endl;
  std::cout << "ARI:" << test.ARI() << std::endl;
#endif

  std::string filenameResultBin
    =std::string("qFCM-Em")+std::to_string(test.fuzzifierEm())
    +std::string("-Lambda")+std::to_string(test.fuzzifierLambda())
    +std::string("-")
    +filenameData.substr(0, filenameDataDotPosition)
    +std::string(".bin");
   std::ofstream ofs_bin(RESULT_DIR+filenameResultBin, std::ios::binary | std::ios::out);
  if(!ofs_bin){
    std::cerr << "File:" << filenameResultBin
	      << "could not open." << std::endl;
    exit(1);
  }
  
  std::string filenameResultMembership
    =std::string("qFCM-Em")+std::to_string(test.fuzzifierEm())
    +std::string("-Lambda")+std::to_string(test.fuzzifierLambda())
    +std::string("-")
    +filenameData.substr(0, filenameDataDotPosition)
    +std::string(".result_membership");
  std::ofstream ofs_membership(RESULT_DIR+filenameResultMembership);
  if(!ofs_membership){
    std::cerr << "File:" << filenameResultMembership
	      << "could not open." << std::endl;
    exit(1);
  }
 
  for(int k=0;k<test.data_number();k++){
    for(int ell=0;ell<test.data()[k].essencialSize();ell++){
      ofs_membership << test.data()[k].indexIndex(ell) << "\t"
		     << test.data()[k].elementIndex(ell) << "\t";
    }
    for(int i=0;i<test.centers_number();i++){
      ofs_membership << test.membership()[i][k] << "\t";
      ofs_bin.write((char*)&test.membership()[i][k],sizeof(test.membership()[i][k]));
    }
    ofs_membership << std::endl;
  }
  ofs_membership.close();
  
  std::string filenameResultCenters
    =std::string("qFCM-Em")+std::to_string(test.fuzzifierEm())
    +std::string("-Lambda")+std::to_string(test.fuzzifierLambda())
    +std::string("-")
    +filenameData.substr(0, filenameDataDotPosition)
    +std::string(".result_centers");
  std::ofstream ofs_centers(RESULT_DIR+filenameResultCenters);
  if(!ofs_centers){
    std::cerr << "File:" << filenameResultCenters
	      << "could not open." << std::endl;
    exit(1);
  }
  for(int i=0;i<test.centers_number();i++){
    for(int ell=0;ell<test.dimension();ell++){
      ofs_centers << test.centers()[i][ell] << "\t";
      for(int ell=500;ell<=501;ell+=1){
        ofs_bin.write((char*)&test.centers()[i][ell],sizeof(test.centers()[i][ell]));
      }
    }
    ofs_centers << std::endl;
  }
  ofs_centers.close();

  ofs_bin.close();

  return 0;
}
