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
  std::vector<std::string> dirs = MkdirFCS({METHOD_NAME});
  //Recomクラスの生成
  Recom recom(user_number, item_number, 0, 0, MISSING_MAX);
  recom.method_name()=METHOD_NAME;
  //データ入力
  recom.input(DATA_DIR+InputDataName);
  //シード値の初期化
  recom.seed();
  //欠損パターン
  for(recom.current()=0;recom.current()
        <MISSINGTRIALS;recom.current()++){
    std::cout<<"missing pattern: "<<recom.current()<<std::endl;
    //missing_pattern_xのフォルダ作成
    std::vector<std::string> dir = Mkdir(recom.current(), dirs);
    //欠損数
    recom.Mcurrent()=0;
    for(recom.missing()=MISSING_MIN;
        recom.missing()<=MISSING_MAX;recom.missing()+=MISSING_DIFF){
      //初期化
      recom.reset();
      //データを欠損
      recom.revise_missing_values();
      //GloupLens Methodで予測
      recom.reset_pred();
      recom.pearsonsim();
      recom.revise_prediction();
      recom.mae(dir[0], 0, {});
      recom.fmeasure(dir[0], 0, {});
      recom.roc(dir[0], {});
      recom.choice(dir, {}, 0);
      recom.Mcurrent()++;
    }//欠損数
    
    //MAE, AUCを計算
    recom.save_min_mae(dir,{});
    recom.save_min_auc(dir,{});
    //欠損数ごとの最小MAE, AUCを出力する
    recom.out_mae(dirs);
    recom.out_auc(dirs);
    //MAE, AUCの平均を計算，出力
    recom.precision_summary_gl(dirs);
   
  }//欠損パターン
  return 0;
}
