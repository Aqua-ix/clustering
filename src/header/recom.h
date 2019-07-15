#include"sparseMatrix.h"
#include"matrix.h"
#include<stdarg.h>
#include<list>

#ifndef __RECOM__
#define __RECOM__

//欠損パターン
#define MISSINGTRIALS 10000
//クラスタリングの初期値
#define CLUSTERINGTRIALS 10
//pearson, eicf, co-clustering
#define METHOD_NUMBER 2

//欠損数
#ifdef ARTIFICIALITY
#define MISSING_MIN 1500
#define MISSING_MAX 7500
#define MISSING_DIFF 500
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
#else
#define MISSING_MIN 0
#define MISSING_MAX 0
#define MISSING_DIFF 1
#endif

//ファジィクラスタリング用クラスタ数設定値
#ifdef ARTIFICIALITY
#define C_START 5
#define C_END 5
#elif defined TEST
#define C_START 2
#define C_END 2
#else
#define C_START 1
#define C_END 10
#endif

//可能性クラスタリング用クラスタ中心しきい値
#ifdef ARTIFICIALITY
#define CENTERS_THRESHOLD 1.0
#elif defined TEST
#define CENTERS_THRESHOLD 1.0E-05
#else
#define CENTERS_THRESHOLD 1.0
#endif

//パラメータ
#define ALPHA 0.03
#ifdef ARTIFICIALITY
#define M_START 1.1
#define M_END 3.1
#define M_DIFF 0.2
#define LAMBDA_START 2
#define LAMBDA_END 1024
#define LAMBDA_DIFF 2
#elif defined TEST
#define M_START 1.1
#define M_END 10.0
#define M_DIFF 0.1
#define LAMBDA_START 2
#define LAMBDA_END 1024
#define LAMBDA_DIFF 2
#else
#define M_START 1.1
#define M_END 1.5
#define M_DIFF 0.1
#define LAMBDA_START 10
#define LAMBDA_END 100000
#define LAMBDA_DIFF 10
#endif

//収束条件
#define MAX_ITE 1000
#define DIFF_FOR_STOP 1.0E-10

//データディレクトリ
#define DATA_DIR "data/dataset/"
#define RESULT_DIR "data/result_data/"

class Recom{
protected:
  std::string METHOD_NAME;
  //欠損のさせ方を決めるシード値
  int Seed;
  //欠損のさせ方ループ数,クラスタリング初期値ループ数,欠損値ループ数,現在の欠損数
  int Current, CCurrent, MCurrent, Missing;
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
  Matrix resultMAE, resultFmeasure;
  Matrix choiceMAE, choiceFmeasure;
  Matrix choiceMAE_M, choiceFmeasure_M;
  //欠損数ごとの最小MAE
  Vector MinMAE;
  //MAE最小時ファジィ化パラメータ
  Matrix MinMAEParam;
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
  //データ入力
  void input(std::string);
  //欠損パターン初期化
  void seed(void);
  //初期化
  void reset(void);
  void reset2(void);
  //データを欠損
  void revise_missing_values_new(void);
  void revise_missing_values(void);
  //MAEの計算，textに保存
  void mae(std::string, int);
  void mae(std::string, int, std::vector<double>);
  //F-measureの計算，textに保存，indexはROC用ループ添字
  void fmeasure(std::string, int);
  void fmeasure(std::string, int, std::vector<double>);
  //ROCで必要な値をtextに保存
  void roc(std::string);
  void roc(std::string, std::vector<double>);
  //ROCの横軸の値で小さい順にソート
  void Sort(Vector &fal, Vector &tru, int index);
  //Seedとか保存
  void ofs_objective(std::string);
  //選ばれたクラスタリング初期値によるMAE,Fmeasureの欠損させ方数平均
  int min_objective_index(void);
  void choice_mae_f(std::vector<std::string>, int p=1);
  void choice_mae_f(std::vector<std::string>,
                    std::vector<double>, int p=1);
  //maeとfmeasure出力:人工データ用
  void save_mae_f(std::vector<std::string>);
  //MAEを出力
  void out_mae_f(std::vector<std::string>);
  //帰属度を出力
  void out_mem(std::vector<std::string>);
  //最小MAEを保存
  void save_min_mae(std::vector<std::string>,
                    std::vector<double>);
  //最小MAEを保存(パラメータ毎)
  void save_min_mae2(std::vector<std::string>,
                    std::vector<double>);
  //最小MAEを出力
  void out_min_mae(std::vector<std::string>);
  void out_min_mae(std::vector<std::string>,
                   std::vector<double>);
  //最小MAEを出力(パラメータ毎)
  void out_min_mae2(std::vector<std::string>);
  //AUCの計算，text1に読み込むROCファイル，text2に平均AUCを保存
  void precision_summary(std::vector<std::string>);
  void precision_summary2(std::vector<std::string>,
                          int param_num, double params, ...);
  //クラスタリングのみで予測値計算
  void revise_prediction(void);
  //Efficient Incremental Collaborative Filtering system
  void computation_w(void);
  void revise_prediction2(const Matrix &V);
  //ピアソン相関係数計算
  void pearsonsim(void);
  //行クラスタでフィルタにかけた状態で相関係数計算
  void pearsonsim_clustering(void);
  //PCM用類似度計算
  void pearsonsim_for_pcm(const int clusters_number);
  void pearsonsim_for_pcm(const Matrix &Membership,
                          const Vector &Threshold);
  //予測値計算:FireFly
  void pearsonpred1(void);
  //予測値計算:GroupLens
  void pearsonpred2(void);
  //indexのユーザの既評価値平均を計算
  double user_average(int index);
  SparseMatrix sparsecorrectdata(void) const;
  SparseVector &sparsecorrectdata(int index);
  SparseMatrix sparseincompletedata(void) const;
  SparseVector &sparseincompletedata(const int &index);
  //収束した帰属度をクリスプ化
  void crisp(const Matrix &Membership, const Matrix &ItemMembership);
  void crisp(const Matrix &Membership);
  void crisp(const Matrix &Membership, const int clusters_number);
  //収束した帰属度をオーバーラップ
  void overlap(const Matrix &Membership);
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
std::vector<std::string> MkdirFCS(std::string);
std::vector<std::string>
Mkdir(std::vector<double> param, int c, std::vector<std::string> dirs);
std::vector<std::string> Mkdir(int missing, std::vector<std::string> dirs);
std::vector<std::string> Mkdir(std::vector<std::string> methods);
#endif
