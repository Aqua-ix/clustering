#include"recom.h"

//ユーザ数
const int user_number=return_user_number();
//アイテム数
const int item_number=return_item_number();
//データの名前
const std::string data_name=return_data_name();
//入力するデータ
const std::string InputDataName="sparse_"+data_name
  +"_"+std::to_string(user_number)
  +"_"+std::to_string(item_number)+".txt";
//手法名
const std::string METHOD_NAME="GROUPLENS";

int main(void){
  std::vector<std::string> dirs = Mkdir({METHOD_NAME});
  //Recomクラスの生成
  Recom recom(user_number, item_number, 0, 0, MISSING_MAX);
  recom.method_name()=METHOD_NAME;
  //データ入力
  recom.input(DATA_DIR+InputDataName);
  //欠損数
  recom.Mcurrent()=0;
  for(recom.missing()=MISSING_MIN;
      recom.missing()<=MISSING_MAX;recom.missing()+=MISSING_DIFF){
    //シード値の初期化
    recom.seed();
    //欠損のさせ方ループ
    for(recom.current()=0;recom.current()
          <MISSINGTRIALS;recom.current()++){
      //初期化
      recom.reset();
      //データを欠損
      recom.revise_missing_values_new();
      //GloupLens Methodで予測
      recom.reset2();
      recom.pearsonsim();
      recom.pearsonpred2();
      recom.mae(dirs[0], 0);
      recom.fmeasure(dirs[0], 0);
      recom.roc(dirs[0]);
      recom.choice_mae_f(dirs, 0);
    }
    //AUC，MAE，F-measureの平均を計算，出力
    recom.precision_summury(dirs);
    recom.Mcurrent()++;
  }
  //欠損数ごとの最小MAEを出力する
  recom.out_min_mae(dirs);
  return 0;
}
