#include"recom.h"
#include"qpcs.h"

//ユーザ数
const int user_number=return_user_number();
//アイテム数
const int item_number=return_item_number();
//データの名前
const std::string data_name=return_data_name();
//入力するデータ
const std::string InputDataName
="sparse_"+data_name
  +"_"+std::to_string(user_number)
  +"_"+std::to_string(item_number)+".txt";
//クラスタリング手法名
const std::string METHOD_NAME="QPCS_CRISP";
//クラスタ数
constexpr int clusters_number=1;

int main(void){
  //Recomクラスの生成
  Recom recom(user_number, item_number,
              user_number, item_number, MISSING_MAX);
  //手法のフォルダ作成
  std::vector<std::string> dirs = MkdirFCS(METHOD_NAME);
  recom.method_name()=METHOD_NAME;
  recom.clusters_num()=clusters_number;
  //パラメータ
  double alpha=ALPHA;
  for(double m=M_START;m>=M_END;m-=M_DIFF){
    for(double lambda=LAMBDA_START;
        lambda<=LAMBDA_END;
        lambda*=LAMBDA_DIFF){
      std::cout<<"m: "<<m<<"\tlambda: "<<lambda<<std::endl;
      
      QPCS test(item_number, user_number,
                clusters_number, m, lambda, alpha);
      //マージのしきい値設定
      test.centers_threshold()=CENTERS_THRESHOLD;
      std::vector<double> parameter= {m, lambda};
      //データ入力
      recom.input(DATA_DIR+InputDataName);
      //初期化
      recom.reset_choice();
      //欠損パターン
      for(recom.current()=0;
          recom.current()<MISSINGTRIALS;
          recom.current()++){
        std::cout<<"missing pattern: "<<recom.current()<<std::endl;
        //ディレクトリ作成
        std::vector<std::string> dir
          = Mkdir(recom.clusters_num(),
                  parameter,
                  recom.current(),dirs);
        //欠損数
        recom.Mcurrent()=0;
        for(recom.missing()=MISSING_MIN;
            recom.missing()<=MISSING_MAX;
            recom.missing()+=MISSING_DIFF){
          //初期化
          recom.reset_data();
          //データを欠損
          recom.revise_missing_values();
          //データをtestに渡す
          test.copydata(recom.sparseincompletedata());
          //データをスパース化
          test.ForSphericalData();
          //PCM用クラスタ中心の初期化
          test.centers_pcm_reset();
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
	  
              double diff_v
                =max_norm(test.tmp_centers()-test.centers());
              double diff_u
                =max_norm(test.tmp_membership()
                          -test.membership());
              double diff=diff_u+diff_v;
              if(std::isnan(diff)){
                std::cout<<"diff is nan"<<std::endl;
                std::cout<<"m: "<<m<<std::endl;
                std::cout<<"lambda: "<<lambda<<std::endl;
                exit(1);
              }
              if(diff<DIFF_FOR_STOP)break;
              if(test.iterates()>=MAX_ITE)break;
              test.iterates()++;
            }//クラスタリング
            test.save_membership(k);
          }//ユーザー数回ループ
          //閾値でフィルタリング
          recom.pearsonsim_pcs_threshold
            (test.membership_pcm(),
             test.membership_threshold());
          //予測値を計算
          recom.revise_prediction();
          //MAEを計算
          recom.mae(dir[0], 0);
          //F-measureを計算
          recom.fmeasure(dir[0], 0);
          //ROCを計算
          recom.roc(dir[0]);
          //recomに目的関数値を渡す
          recom.obje(recom.Ccurrent())=-1;
          //目的関数をファイル出力
          recom.ofs_objective(dir[0]);
          test.ofs_selected_data(dir[0]);
          recom.choice(dir);
          recom.Mcurrent()++;
        }//欠損数
        //AUC，MAEの平均を計算，出力
        recom.precision_summary(dir);
      }//欠損パターン
    }//パラメータlambda
  }//パラメータm
  return 0;
}

