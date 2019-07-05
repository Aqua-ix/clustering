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
const std::string METHOD_NAME="BPCS_OVERLAP";
//クラスタ数
constexpr int clusters_number=1;

int main(void){
  std::vector<std::string> dirs = MkdirFCS(METHOD_NAME);
  Recom recom(user_number, item_number, clusters_number, clusters_number, MISSING_MAX);
  recom.method_name()=METHOD_NAME;

  double alpha=ALPHA;
  for(double m=M_START;m<=M_END;m+=M_DIFF){
    BPCS test(item_number, user_number, clusters_number, m, alpha);
    std::vector<double> parameter= {m};
    std::vector<std::string> dir = Mkdir(parameter, clusters_number, dirs);

    //データ入力
    recom.input(DATA_DIR+InputDataName);
    //欠損数
    recom.Mcurrent()=0;
    for(recom.missing()=MISSING_MIN;
        recom.missing()<=MISSING_MAX;recom.missing()+=MISSING_DIFF){
      //シード値の初期化
      recom.Seed();
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
        //ユーザ数回ループ
        for(int k=0;k<user_number;k++){
          test.reset();
          //初期クラスタ中心
          test.initialize_centers_one_cluster(k);
          test.iterates()=0;
          while(1){
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
          }
          //帰属度保存
          test.save_membership(k);
        }//ユーザー数回ループ
        recom.pearsonsim_for_pcm(test.membership_pcm(),test.membership_threshold());
        recom.pearsonpred2();
        recom.mae(dir[0], 0);
        recom.fmeasure(dir[0], 0);
        recom.roc(dir[0]);
        recom.obje(recom.Ccurrent())=-1;
        recom.ofs_objective(dir[0]);
        test.ofs_selected_data(dir[0]);
        recom.choice_mae_f(dir);
      }//欠損パターン
      recom.precision_summury(dir);
      recom.Mcurrent()++;
    }//欠損数
    //欠損数ごとの最小MAEを出力する
    recom.out_min_mae(dirs);
  }//パラメータm
  return 0;
}
