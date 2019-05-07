#include<iostream>
#include<iomanip>
#include<string>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<chrono>
#include<random>
#include<array>
#include<vector>
#include<unistd.h>
#include<fstream>
#include<sstream>
#include<sys/types.h>
#include<sys/stat.h>
#include<experimental/filesystem>
#include<boost/math/special_functions/binomial.hpp>
using namespace std::experimental::filesystem::v1;

#ifndef __VECTOR__
#define __VECTOR__

class Matrix;
class SparseVector;

class Vector{
  //非公開
 private:
  //要素数
  int Size;
  //要素
  double *Element;
  //公開
 public:
  //コンストラクタ
  Vector(int size=0);
  //デストラクタ
  ~Vector(void);
  //明示的呼び出しのみ可能とするコンストラクタ
  //第三引数を"all"とすることで第二引数の値で全ての要素を初期化
  explicit Vector(int dim, double arg, const char *s);
  //初期化子並びコンストラクタ
  Vector(std::initializer_list<double> arg);
  //コピーコンストラクタ
  Vector(const Vector &args);
  //ムーブコンストラクタ
  Vector(Vector &&arg);
  //コピー代入
  Vector &operator=(const Vector &arg);
  //スパース用コピー代入
  Vector &operator=(const SparseVector &arg);
  //ムーブ代入
  Vector &operator=(Vector &&arg);
  //privateで定義されたSizeを返す関数
  int size(void) const;
  //添字演算子
  double operator[](int index) const;
  double &operator[](int index);
  Vector operator+(void) const;
  Vector operator-(void) const;
  Vector &operator+=(const Vector &rhs);
  Vector &operator-=(const Vector &rhs);
  Vector &operator*=(double rhs);
  Vector &operator/=(double rhs);
  Vector operator+(const Vector &rhs) const;
  Vector operator-(const Vector &rhs) const;
  //内積
  double operator*(const Vector &rhs) const;
  bool operator==(const Vector &rhs) const;
  bool operator!=(const Vector &rhs) const;
  //beginからendまでの要素のみを取り出し新たなベクトル作成
  Vector sub(int begin, int end) const;
  //argのbeginからendまでの要素をコピー
  void set_sub(int begin, int end, const Vector &arg);
};

Vector operator*(double lhs, const Vector &rhs);
Vector operator*(const Vector &lhs, double rhs);
//Vector operator/(double lhs, const Vector &rhs);
Vector operator/(const Vector &lhs, double rhs);
//逆数
Vector fraction(const Vector &arg);
//各要素を最大の要素で割る
Vector max_fraction(const Vector &arg);
//各要素を要素の合計で割る
Vector sum_fraction(const Vector &arg);
std::ostream &operator<<(std::ostream &os, const Vector &rhs);
//絶対値をとった要素の最大
double max_norm(const Vector &arg);
//2ノルム
double squared_norm(const Vector &arg);
//2ノルムの二乗
double norm_square(const Vector &arg);
//1ノルム
double L1norm_square(const Vector &arg);

#endif
