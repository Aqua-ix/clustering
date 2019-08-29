#include"recom.h"
#include"efcs.h"

//ユーザ数
const int user_number=return_user_number();
//アイテム数
const int item_number=return_item_number();
//データの名前
const std::string data_name=return_data_name();
//入力するデータの場所
const std::string InputDataName="sparse_"+data_name
  +"_"+std::to_string(user_number)
  +"_"+std::to_string(item_number)+".txt";
//クラスタリング手法名
const std::string METHOD_NAME="EFCS_CLISP";

int main(void){
  std::vector<std::string> dirs = MkdirFCS(METHOD_NAME);
  //クラスタ数
  for(int clusters_number=C_START;clusters_number<=C_END;clusters_number++){
    std::cout<<"clusters number: "<<clusters_number<<std::endl;
    //Recomクラスの生成
    Recom recom(user_number, item_number,
                clusters_number, clusters_number, MISSING_MAX);
    recom.method_name()=METHOD_NAME;
    recom.clusters_num()=clusters_number;
    //シード値の初期化
    recom.seed();    
    //欠損パターン
    for(recom.current()=0;recom.current()<MISSINGTRIALS;recom.current()++){
      std::cout<<"missing pattern: "<<recom.current()<<std::endl;
      //フォルダ作成
      std::vector<std::string> dir = Mkdir(recom.clusters_num(),
                                           recom.current(),dirs);
      //パラメータlambda
      for(double lambda=LAMBDA_START;lambda<=LAMBDA_END;lambda*=LAMBDA_DIFF){
        std::cout<<"lambda: "<<lambda<<std::endl;
        EFCS test(item_number, user_number, clusters_number, lambda);
        std::vector<double> parameter= {lambda};
        //データ入力
        recom.input(DATA_DIR+InputDataName);
        //欠損数
        recom.Mcurrent()=0;
        for(recom.missing()=MISSING_MIN;
            recom.missing()<=MISSING_MAX;recom.missing()+=MISSING_DIFF){
          //初期化
          recom.reset();
          //データを欠損
          recom.revise_missing_values();
          recom.pearsonsim();
          //データをtestに渡す
          test.copydata(recom.sparseincompletedata());
          test.ForSphericalData();	
          //選んだデータがNanになったときシード値変更変数
          int ForBadChoiceData=0, InitCentLoopis10=0;
          //初期値パターン
          for(recom.Ccurrent()=0;recom.Ccurrent()
                <CLUSTERINGTRIALS;recom.Ccurrent()++){
            test.reset();
            //初期クラスタサイズ調整変数の設定
            test.initialize_clustersize();
            //初期クラスタ中心の設定
            test.initialize_centers(recom.Ccurrent()
                                    +ForBadChoiceData);
            //クラスタリングループ数
            test.iterates()=0;
            //nanが出た時の回避で使う
            int p=1;
            while(1){
              if(InitCentLoopis10>9){
                test.reset();
                recom.obje(recom.Ccurrent())=DBL_MAX;
                recom.revise_prediction();
                recom.mae(dir[0], 0, parameter);
                recom.fmeasure(dir[0], 0, parameter);
                recom.roc(dir[0], parameter);
                recom.ofs_objective(dir[0]);
                test.ofs_selected_data(dir[0]);
                InitCentLoopis10=0;
                p=0;
                break;
              }
              test.revise_dissimilarities();
              test.revise_membership();
              test.revise_centers();
              test.revise_clusters_size();
              double diff_v
                =max_norm(test.tmp_centers()-test.centers());
              double diff_u
                =max_norm(test.tmp_membership()-test.membership());
              double diff_p
                =max_norm(test.tmp_clusters_size()-test.clusters_size());
              double diff=diff_u+diff_v+diff_p;
              if(std::isnan(diff)){
                test.reset();
                recom.Ccurrent()--;p=0;
                ForBadChoiceData++;
                InitCentLoopis10++;
                break;
              }
              if(diff<DIFF_FOR_STOP)break;
              if(test.iterates()>=MAX_ITE)break;
              test.iterates()++;
            }
    
            if(p){
              //目的関数値の計算
              test.set_objective();
              //recomに目的関数値を渡す
              recom.obje(recom.Ccurrent())=test.objective();
              //recomに帰属度を渡してクリスプ
              recom.crisp(test.membership());
              //GroupLens Methodで予測
              recom.reset_pred();
              //クラスタリング＋ピアソン相関係数の計算
              recom.pearsonsim_fcs();
              recom.revise_prediction();
              recom.mae(dir[0], 0, parameter);
              recom.fmeasure(dir[0], 0, parameter);
              recom.roc(dir[0], parameter);
              recom.ofs_objective(dir[0]);
              test.ofs_selected_data(dir[0]);
              InitCentLoopis10=0;
            }
          }//初期値パターン
          recom.choice_mae(dir, parameter);
          recom.Mcurrent()++;         
        }//欠損数
        //欠損数ごとのMAEが今までのMAEより小さければ保存する
        recom.save_min_mae(dir, parameter);
      }//パラメータm
      //最小MAE出力
      recom.out_min_mae_crisp(dirs);
      //AUC，MAEの平均を計算，出力
      recom.precision_summary_crisp(dirs, 1,
                               LAMBDA_START, LAMBDA_END, LAMBDA_DIFF);
    }//欠損パターン
  }//クラスタ数
  return 0;
}
