#include"recom.h"
#include"epcs.h"

//ユーザ数
const int user_number=return_user_number();
//アイテム数
const int item_number=return_item_number();
//データの名前
const std::string data_name=return_data_name();
//入力するデータ
const std::string InputDataName="sparse_"+data_name
+"_"+std::to_string(user_number)+"_"+std::to_string(item_number)+".txt";
//クラスタリング手法名
const std::string METHOD_NAME="EPCS_CLISP";
//クラスタ数
constexpr int clusters_number=1;

int main(void){
  std::vector<std::string> dirs = MkdirFCS(METHOD_NAME);
  //Recomクラスの生成
  Recom recom(user_number, item_number, user_number, item_number, MISSING_MAX);
  recom.method_name()=METHOD_NAME;

  double alpha=ALPHA;
  //パラメータlambda
  for(double lambda=LAMBDA_START;lambda<=LAMBDA_END;lambda*=LAMBDA_DIFF){
    std::cout<<"lambda: "<<lambda<<std::endl;
    EPCS test(item_number, user_number, clusters_number, lambda, alpha);
    //マージのしきい値設定
    test.centers_threshold()=CENTERS_THRESHOLD;

    std::vector<double> parameter= {lambda};
    std::vector<std::string> dir = Mkdir(parameter, clusters_number, dirs);

    //データ入力
    recom.input(DATA_DIR+InputDataName);
    //欠損数
    recom.Mcurrent()=0;
    for(recom.missing()=MISSING_MIN;
        recom.missing()<=MISSING_MAX;recom.missing()+=MISSING_DIFF){
      //シード値の初期化
      recom.seed();
      //欠損パターン
      for(recom.current()=0;recom.current()<MISSINGTRIALS;recom.current()++){
        std::cout<<"missing pattern: "<<recom.current()<<std::endl;
        //初期化
        recom.reset();
        //データを欠損
        recom.revise_missing_values_new();
        //データをtestに渡す
        test.copydata(recom.sparseincompletedata());
        //データをスパース化
        test.ForSphericalData();
        //PCM用クラスタ中心の初期化
        test.centers_pcm_reset();
        //クラスタ数カウント
        test.clusters_count()=1;
        //ユーザ数回ループ
        for(int k=0;k<user_number;k++){
          test.reset();
          //初期クラスタ中心
          test.initialize_centers_one_cluster(k);
          test.iterates()=0;
          while(1){//クラスタリング
            test.revise_dissimilarities();//hcs
            test.revise_membership();//bpcs
            test.revise_centers();//bfcs
	  
            double diff_v=max_norm(test.tmp_centers()-test.centers());
            double diff_u=max_norm(test.tmp_membership()-test.membership());
            double diff=diff_u+diff_v;
            if(std::isnan(diff)){
              std::cout<<"diff is nan"<<std::endl;
              test.reset();
              exit(1);
            }
            if(diff<DIFF_FOR_STOP)break;
            if(test.iterates()>=MAX_ITE)break;
            test.iterates()++;
          }//クラスタリング
          test.marge_centers();
        }//ユーザー数回ループ
        std::cout<<"clusters count: "<<test.clusters_count()<<std::endl;
        recom.crisp(test.membership_pcm(), test.clusters_count());
        recom.pearsonsim_for_pcm(test.clusters_count());
      
        recom.pearsonpred2();//GroupLens
        recom.mae(dir[0], 0);
        recom.fmeasure(dir[0], 0);
        recom.roc(dir[0]);
        recom.obje(recom.Ccurrent())=-1;
        recom.ofs_objective(dir[0]);
        test.ofs_selected_data(dir[0]);
        recom.choice_mae_f(dir);
      }//欠損パターン
      //最小MAEを計算
      recom.save_min_mae(dir, parameter);
      //AUC，MAE，F-measureの平均を計算，出力
      recom.precision_summury(dir);
      recom.Mcurrent()++;
    }//欠損数
    //欠損数ごとの最小MAEを出力する
    recom.out_min_mae(dirs, parameter);
  }//パラメータlambda
  return 0;
}
