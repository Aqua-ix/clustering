#include"sparseMatrix.h"
#include"matrix.h"
#include<stdarg.h>
#include<list>
#include <iomanip>

#ifndef __RECOM__
#define __RECOM__

//データディレクトリ
#define DATA_DIR "data/dataset/"
#define RESULT_DIR "data/result_data/"

//収束条件
#define MAX_ITE 1000
#define DIFF_FOR_STOP 1.0E-10

//手法数の最大値
#define METHOD_NUMBER 2

//ファジィクラスタリング用クラスタ数設定値
#ifdef ARTIFICIALITY
#define C_START 5
#define C_END 5
#elif defined TEST
#define C_START 1
#define C_END 2
#elif defined BOOK
#define C_START 15
#define C_END 35
#elif defined MOVIE
#define C_START 5
#define C_END 7
#elif defined LIBIMSETI
#define C_START 6
#define C_END 15
#elif defined EPINIONS
#define C_START 2
#define C_END 8
#elif defined JESTER
#define C_START 2
#define C_END 8
#elif defined SUSHI
#define C_START 2
#define C_END 8
#else
#define C_START 0
#define C_END 0
#endif

//オーバーラップ閾値
#ifdef ARTIFICIALITY
#define OT_START 0.60
#define OT_END 1.00
#define OT_DIFF 0.10
#elif defined TEST
#define OT_START 0.00
#define OT_END 1.10
#define OT_DIFF 0.20
#else
#define OT_START 0.20
#define OT_END 1.00
#define OT_DIFF 0.20
#endif

//パラメータ
#define ALPHA 0.03
//M_DIFF 設定した値で減算
//LAMBDA_DIFF 設定した値で乗算
#ifdef ARTIFICIALITY
#define M_START 2.9
#define M_END 1.1
#define M_DIFF 0.2
#define LAMBDA_START 2
#define LAMBDA_END 1024
#define LAMBDA_DIFF 2
#elif defined TEST
#define M_START 1.20
#define M_END 1.10
#define M_DIFF 0.10
#define LAMBDA_START 2
#define LAMBDA_END 10
#define LAMBDA_DIFF 2
#else
#define M_START 1.001
#define M_END 1.0001
#define M_DIFF 0.0003
#define LAMBDA_START 10
#define LAMBDA_END 1.0E04
#define LAMBDA_DIFF 10
#endif

//可能性クラスタリング用クラスタ中心閾値
#ifdef ARTIFICIALITY
#define CENTERS_THRESHOLD 1.0
#elif defined TEST
#define CENTERS_THRESHOLD 1.0E-05
#else
#define CENTERS_THRESHOLD 1.0E-03
#endif

//欠損数
#ifdef ARTIFICIALITY
#define MISSING_MIN 1500
#define MISSING_MAX 7500
#define MISSING_DIFF 500
#elif defined TEST
#define MISSING_MIN 0
#define MISSING_MAX 10
#define MISSING_DIFF 1
#elif defined BOOK
#define MISSING_MIN 30000
#define MISSING_MAX 30000
#define MISSING_DIFF 30000
#elif defined MOVIE
#define MISSING_MIN 100000
#define MISSING_MAX 100000
#define MISSING_DIFF 100000
#elif defined LIBIMSETI
#define MISSING_MIN 300000
#define MISSING_MAX 300000
#define MISSING_DIFF 300000
#elif defined EPINIONS
#define MISSING_MIN 20000
#define MISSING_MAX 20000
#define MISSING_DIFF 200000
#elif defined JESTER
#define MISSING_MIN 200000
#define MISSING_MAX 200000
#define MISSING_DIFF 200000
#elif defined SUSHI
#define MISSING_MIN 20000
#define MISSING_MAX 20000
#define MISSING_DIFF 20000
#else
#define MISSING_MIN 0
#define MISSING_MAX 0
#define MISSING_DIFF 0
#endif

//欠損パターン数
#ifdef ARTIFICIALITY
#define MISSINGTRIALS 20
#elif defined TEST
#define MISSINGTRIALS 2
#else
#define MISSINGTRIALS 5
#endif

//初期値パターン数
#define CLUSTERINGTRIALS 10

class Recom{
protected:
  std::string METHOD_NAME;
  //欠損パターン数,クラスタリング初期値パターン数,欠損値ループ数,欠損数,クラスタ数
  int Current, CCurrent, MCurrent, Missing, ClustersNum;
  //オーバーラップ閾値
  double OverlapThreshold;
  //欠損後データ
  SparseMatrix SparseIncompleteData;
  //欠損前データ
  SparseMatrix SparseCorrectData;
  //球面正規データ
  SparseMatrix NormalizedData;
  //欠損させた箇所，類似度
  Matrix KessonIndex, Similarity;
  //行帰属度，列帰属度
  Matrix Mem, ItemMem;
  //MAE, F-measure, AUC
  Matrix ResultMAE, ResultFmeasure;
  Vector ChoicedMAE, ChoicedAUC;
  //予測評価値
  Vector Prediction;
  //欠損させた箇所のスパースデータの列番号
  Vector SparseIndex;
  //Recall，Fallout
  Vector TP_FN, FP_TN;
  //目的関数値
  Vector Obje;
  //w of EICF
  Vector W;
 public:
  //ユーザ数，アイテム数，行クラスタ数，列クラスタ数，最大欠損数
  Recom(int user,
        int item,
	int user_cen,
	int item_cen,
	int miss);
  std::string &method_name(void);
  Vector obje(void) const;
  Matrix kessonindex(void) const;
  double similarity(int, int);
  double &obje(int index);
  //欠損パターン番号
  int &current(void);
  //クラスタリングの初期値パターン番号
  int &Ccurrent(void);
  //欠損数インデックス
  int &Mcurrent(void);
  //現在の欠損数
  int &missing(void);
  //現在のクラスタ数
  int &clusters_num(void);
  //オーバーラップ閾値
  double &overlap_threshold(void);
  //欠損前スパースデータ
  SparseMatrix sparsecorrectdata(void) const;
  SparseVector &sparsecorrectdata(int index);
  //欠損済スパースデータ
  SparseMatrix sparseincompletedata(void) const;
  SparseVector &sparseincompletedata(const int &index);
  //データ入力
  void input(std::string);
  //初期化
  void reset_data(void);
  void reset_pred(void);
  void reset_choice(void);
  //データを欠損
  void revise_missing_values(void);
  //MAEの計算，textに保存
  void mae(std::string, int);
  //F-measureの計算，textに保存，indexはROC用ループ添字
  void fmeasure(std::string, int);
  //ROCで必要な値をtextに保存
  void roc(std::string);
  //ROCの横軸の値で小さい順にソート
  void Sort(Vector &fal, Vector &tru, int index);
  //目的関数の保存
  void ofs_objective(std::string);
  //選ばれたクラスタリング初期値によるMAE,Fmeasureの欠損させ方数平均
  int min_objective_index(void);
  //目的関数が最小になるMAEとROCを選択
  void choice(std::vector<std::string>, int p=1);
  //平均MAE, AUCの計算
  void precision_summary(std::vector<std::string>);
  //ピアソン相関係数計算
  void pearsonsim(void);
  //ファジィクラスタリングの結果を用いたピアソン相関係数計算
  void pearsonsim_fcs(void);
  //可能性クラスタリングの結果を用いたピアソン相関係数計算
  void pearsonsim_pcs(const int clusters_number);
  //可能性クラスタリングの結果を閾値でフィルタリングしたピアソン相関係数計算
  void pearsonsim_pcs_threshold(const Matrix &Membership,
                                const Vector &Threshold);
  //GroupLensの結果を用いた予測値計算
  void revise_prediction(void);
  //indexのユーザの既評価値平均を計算
  double user_average(int index);
 
  //収束した帰属度をクリスプ化
  void crisp(const Matrix &Membership);
  void crisp(const Matrix &Membership, const int clusters_number);
  //収束した帰属度をオーバーラップ
  void overlap(const Matrix &Membership);
  void overlap(const Matrix &Membership, const int clusters_number);
};
//ユーザ数を返す
int return_user_number(void);
//アイテム数を返す
int return_item_number(void);
//設定した閾値を返す
double return_threshold(void);
//最大評価値を返す
double return_max_value(void);
//データの名前を返す
std::string return_data_name(void);
//textを改行する
void FILE_ENDL(std::string text);
//何通りかの初期値を与えた場合，目的関数最大時のROCを選ぶ
void Rename(std::string filename, std::string newname);
//ディレクトリ作成関数
std::vector<std::string> MkdirFCS(std::string);
std::vector<std::string>
Mkdir(int missing, std::vector<std::string> dirs);
std::vector<std::string>
Mkdir(int c, std::vector<double> params,
      int missing, std::vector<std::string> dirs);
std::vector<std::string>
Mkdir(int c, double threshold, std::vector<double> params,
      int missing, std::vector<std::string> dirs);
std::vector<std::string> Mkdir(std::vector<std::string> methods);
#endif
