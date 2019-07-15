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
      recom.revise_missing_values_new();
      //GloupLens Methodで予測
      recom.reset2();
      recom.pearsonsim();
      recom.pearsonpred2();
      recom.mae(dir[0], 0, {});
      recom.fmeasure(dir[0], 0, {});
      recom.roc(dir[0], {});
      recom.choice_mae_f(dir, {}, 0);
      recom.Mcurrent()++;
    }//欠損数
    
    //最小MAEを計算
    recom.save_min_mae2(dir,{});
    //欠損数ごとの最小MAEを出力する
    recom.out_min_mae2(dirs);
    //AUC，MAE，F-measureの平均を計算，出力
    recom.precision_summary2(dirs,0,0);
   
  }//欠損パターン
  return 0;
}
