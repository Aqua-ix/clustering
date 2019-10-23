#include"recom.h"
#include"bpcs.h"

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
const std::string METHOD_NAME="BPCS_CRISP";
//クラスタ数
constexpr int clusters_number=1;

int main(void){
  //Recomクラスの生成
  Recom recom(user_number, item_number, user_number, item_number, MISSING_MAX);
  //手法のフォルダ作成
  std::vector<std::string> dirs = MkdirFCS(METHOD_NAME);
  recom.method_name()=METHOD_NAME;
  recom.clusters_num()=clusters_number;
  double alpha=ALPHA;
  //パラメータm
  for(double m=M_START;m<=M_END;m+=M_DIFF){
    std::cout<<"m: "<<m<<std::endl;
    std::vector<double> parameter= {m};
    BPCS test(item_number, user_number, clusters_number, m, alpha);
    //マージのしきい値設定
    test.centers_threshold()=CENTERS_THRESHOLD;
    //データ入力
    recom.input(DATA_DIR+InputDataName);
    //初期化
    recom.reset_choice();
    //欠損パターン
    for(recom.current()=0;recom.current()<MISSINGTRIALS;recom.current()++){
      std::cout<<"missing pattern: "<<recom.current()<<std::endl;
      //ディレクトリ作成
      std::vector<std::string> dir = Mkdir(recom.clusters_num(),
                                           parameter,
                                           recom.current(), dirs);
      //欠損数
      recom.Mcurrent()=0;
      for(recom.missing()=MISSING_MIN;
          recom.missing()<=MISSING_MAX;recom.missing()+=MISSING_DIFF){
        //初期化
        recom.reset();
        //データを欠損
        recom.revise_missing_values();
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
        //recomに帰属度を渡してクリスプ化
        recom.crisp(test.membership_pcm(), test.clusters_count());
        //クラスタリング＋ピアソン相関係数の計算
        recom.pearsonsim_pcs(test.clusters_count());
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
  }//パラメータm
  return 0;
}
