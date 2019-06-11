#include"recom.h"
#include"epcs.h"
#include"config.h"

//実データ
//収束条件
#define MAX_ITE 1000
#define DIFF_FOR_STOP 1.0E-10

const int user_number=return_user_number();//ユーザ数
const int item_number=return_item_number();//アイテム数
const std::string data_name=return_data_name();//データの名前
const std::string InputDataName="sparse_"+data_name//入力するデータの場所
  +"_"+std::to_string(user_number)+"_"+std::to_string(item_number)+".txt";
const std::string METHOD_NAME="EPCS";//クラスタリング手法名
constexpr int clusters_number=1;

int main(void){
  std::vector<std::string> dirs = MkdirFCS(METHOD_NAME);
  //Recomクラスの生成
  Recom recom(user_number, item_number,clusters_number, clusters_number, KESSON);
  recom.method_name()=METHOD_NAME;

  double alpha=0.03;
  for(double lambda=100;lambda<=100;lambda*=10){   
    //時間計測
    auto start=std::chrono::system_clock::now();
    EPCS test(item_number, user_number,clusters_number, lambda, alpha);
    std::vector<double> parameter= {lambda};
    std::vector<std::string> dir= Mkdir(parameter, clusters_number, dirs);
    recom.input(DATA_DIR+InputDataName);//データ入力

    //欠損数
      recom.missing()=KESSON;
      //欠損数ループ
      //for(recom.missing()=KIZAMI;recom.missing()<=KESSON;recom.missing()+=KIZAMI){
	//シード値の初期化
	recom.Seed();
	//欠損のさせ方ループ
	for(recom.current()=0;recom.current()<MISSINGTRIALS;recom.current()++){
	  //初期化
	  recom.reset();
	  //データを欠損
	  recom.revise_missing_values_new();
	  //データをtestに渡す
	  test.copydata(recom.sparseincompletedata());
	  test.ForSphericalData();
	  //ユーザ数分クラスタリングし，N*Nの帰属度を得る
	  for(int k=0;k<user_number;k++){
	    //変数初期化
	    test.reset();
	    //可能性クラスクラスタリング初期クラスタ中心
	    test.initialize_centers_one_cluster(k);
	    //クラスタリングループ数
	    test.iterates()=0;
	    while(1){
	      test.revise_dissimilarities();
	      test.revise_membership();
	      test.revise_centers();
	      double diff_v=max_norm(test.tmp_centers()-test.centers());
	      double diff_u=max_norm(test.tmp_membership()-test.membership());
	      double diff=diff_u+diff_v;
	      if(std::isnan(diff)){
		std::cout<<"diff is nan \t"
			 <<lambda<<" "<<alpha<<std::endl;
		test.reset();
		exit(1);
	      }
	      if(diff<DIFF_FOR_STOP)break;
	      if(test.iterates()>=MAX_ITE)break;
	      test.iterates()++;
	    }
	    //帰属度保存
	    test.save_membership(k);
	  }
	  //PCM＋ピアソン相関係数の計算
	  recom.pearsonsim_for_pcm(test.membership_pcm(),
				   test.membership_threshold());
	  //grouplens計算
	  recom.pearsonpred2();
	  recom.mae(dir[0], 0);
	  recom.fmeasure(dir[0], 0);
	  recom.roc(dir[0]);
	  recom.obje(recom.Ccurrent())=-1;
	  recom.ofs_objective(dir[0]);
	  test.ofs_selected_data(dir[0]);
	  recom.choice_mae_f(dir);
	}//number of missing values
	
	recom.precision_summury(dir);//AUC，MAE，F-measureの平均を計算，出力
     
      //計測終了
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
  }//lambda
  return 0;
}
