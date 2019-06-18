#include"recom.h"
#include"bpcs.h"
#include"config.h"
#include<list>

//実データ
#define MAX_ITE 1000
#define DIFF_FOR_STOP 1.0E-10

const int user_number=return_user_number();
const int item_number=return_item_number();
const std::string data_name=return_data_name();
const std::string InputDataName="sparse_"+data_name
  +"_"+std::to_string(user_number)+"_"+std::to_string(item_number)+".txt";
const std::string METHOD_NAME="BPCS";
constexpr int clusters_number=1;

int main(void){
  std::vector<std::string> dirs = MkdirFCS(METHOD_NAME);
  Recom recom(user_number, item_number, clusters_number, clusters_number, KESSON);
  recom.method_name()=METHOD_NAME;

  double alpha=0.03;
  for(double m=1.1;m<=1.1;m+=0.1){
    auto start=std::chrono::system_clock::now();
    BPCS test(item_number, user_number, clusters_number, m, alpha);

    std::list<Matrix> result_cen;
    std::list<Matrix>::iterator iter;
    int clusters_count=0;

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
        
        // 今までに算出したクラスタ中心(ユーザ)から距離が近い(1.0E-3未満)かどうか
        bool same=false;      
        for(iter=result_cen.begin();iter!=result_cen.end();iter++){
          if(frobenius_norm(*iter-test.centers())<1.0E-3){
            same=true;
          }
        }
        // 新たなクラスタ中心(ユーザ)をlist最後尾に追加
        if(!same){
          result_cen.push_back(test.centers());
          clusters_count++;
        }

      }//ユーザー数回ループ
      
      std::cout<<"clusters : "<<clusters_count<<std::endl;

      BPCS test2(item_number, clusters_count, clusters_number, m, alpha);
      test2.copydata(recom.sparseincompletedata());//データをtestに渡す
      test2.ForSphericalData();//データをスパース化
        
      test2.reset();
      //TODO: クラスタ中心を再設定
      iter=result_cen.begin();
      for(int i=0; i<clusters_count; i++){
        test2.save_centers(i, *iter);
        iter++;
      }
        
      test2.revise_dissimilarities();//hcs
      test2.revise_membership();//bpcs
        
      recom.crisp(test2.membership(),test2.centers());
      recom.pearsonsim_clustering();
      
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
