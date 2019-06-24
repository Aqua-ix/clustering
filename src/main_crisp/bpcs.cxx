#include"recom.h"
#include"bpcs.h"

const int user_number=return_user_number();//ユーザ数
const int item_number=return_item_number();//アイテム数
const std::string data_name=return_data_name();//データの名前
const std::string InputDataName="sparse_"+data_name//入力するデータの場所
  +"_"+std::to_string(user_number)+"_"+std::to_string(item_number)+".txt";
const std::string METHOD_NAME="BPCS";//クラスタリング手法名
constexpr int clusters_number=1;

// const int user_number=2;
// const int item_number=1002;
// const std::string InputDataName="sparse_2d-Gaussian-2clusters.dat";

int main(void){
  std::vector<std::string> dirs = MkdirFCS(METHOD_NAME);
  Recom recom(user_number, item_number, user_number, item_number, KESSON);
  recom.method_name()=METHOD_NAME;
  
  double alpha=ALPHA;
  for(double m=M_START;m<=M_END;m+=M_DIFF){
    auto start=std::chrono::system_clock::now();
    BPCS test(item_number, user_number, clusters_number, m, alpha);

    std::vector<double> parameter= {m};
    std::vector<std::string> dir = Mkdir(parameter, clusters_number, dirs);

    recom.input(DATA_DIR+InputDataName);//データ入力
    recom.missing()=KESSON;//欠損数
    recom.Seed();//シード値の初期化
    //欠損パターンでループ
    for(recom.current()=0;recom.current()<MISSINGTRIALS;recom.current()++){
      recom.reset();//初期化
      recom.revise_missing_values_new();//データを欠損
      test.copydata(recom.sparseincompletedata());//データをtestに渡す
      test.ForSphericalData();//データをスパース化
      test.clusters_count()=0;
      for(int k=0;k<user_number;k++){//ユーザ数回ループ
        test.reset();
        test.initialize_centers_one_cluster(k);//初期クラスタ中心//pcm
        test.iterates()=0;
        while(1){//クラスタリング
          test.revise_dissimilarities();//hcs
          test.revise_membership();//bpcs
          test.revise_centers();//bfcs
	  
     	  double diff_v=max_norm(test.tmp_centers()-test.centers());
          double diff_u=max_norm(test.tmp_membership()-test.membership());
          double diff=diff_u+diff_v;
          if(std::isnan(diff)){
            std::cout<<"diff is nan \n"
                     <<"m:"<<m<<"\n"
                     <<"alpha:"<<alpha<<std::endl;
            test.reset();
            exit(1);
          }
	  
          if(diff<DIFF_FOR_STOP)break;
          if(test.iterates()>=MAX_ITE)break;
          test.iterates()++;
        }//クラスタリング
        test.marge_centers();
      }//ユーザー数回ループ
      std::cout<<"Clusters Count: "<<test.clusters_count()<<std::endl;

      //TODO: recomで保持している中心と帰属度配列の要素数をクラスタ数に合わせる
      recom.crisp(test.membership_pcm(),test.centers_pcm(), test.clusters_count());
      recom.pearsonsim_for_pcm(test.clusters_count());
      
      recom.pearsonpred2();//GroupLens
      recom.mae(dir[0], 0);
      recom.fmeasure(dir[0], 0);
      recom.roc(dir[0]);
      recom.obje(recom.Ccurrent())=-1;
      recom.ofs_objective(dir[0]);
      test.ofs_selected_data(dir[0]);
      recom.choice_mae_f(dir);
    }//欠損パターンでループ
    
    recom.precision_summury(dir);//出力

    auto end=std::chrono::system_clock::now();
    auto endstart=end-start;
    std::string time="_"
      +std::to_string
      (std::chrono::duration_cast<std::chrono::hours>(endstart).count())
      +"h"+std::to_string
      (std::chrono::duration_cast<std::chrono::minutes>(endstart).count()%60)
      +"m"+std::to_string
      (std::chrono::duration_cast<std::chrono::seconds>(endstart).count()%60)
      +"s";
    //計測時間でリネーム
    for(int i=0;i<(int)dir.size();i++)
      rename(dir[i].c_str(), (dir[i]+time).c_str()); 
  }
  return 0;
}
