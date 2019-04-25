#include"../../src/recom.h"
#include"../../src/bfcs.h"

//収束条件
#define MAX_ITE 1000
#define DIFF_FOR_STOP 1.0E-10

const int user_number=return_user_number();
const int item_number=return_item_number();
const std::string data_name=return_data_name();
//入力するデータの場所
const std::string InputDataName="data/2018/sparse_"+data_name
  +"_"+std::to_string(user_number)
  +"_"+std::to_string(item_number)+".txt";
const std::string METHOD_NAME="BFCS";

int main(void){
  std::vector<std::string> dirs = MkdirFCS(METHOD_NAME);
  //クラスタ数でループ
  //for(int clusters_number=4;clusters_number<=6;clusters_number++){
  int clusters_number=5;
    //Recomクラスの生成
    Recom recom(user_number, item_number, clusters_number
		, clusters_number, KESSON);
    recom.method_name()=METHOD_NAME;
    for(double m=1.4;m>=1.001;m-=0.0003){
      //時間計測
      auto start=std::chrono::system_clock::now();
      BFCS test(item_number, user_number, clusters_number, m);
      std::vector<double> parameter= {m};
      std::vector<std::string> dir
	= Mkdir(parameter, clusters_number, dirs);
      
      //データ入力
      recom.input(InputDataName);
      //欠損数ループ
      for(recom.missing()=KIZAMI;recom.missing()
	    <=KESSON;recom.missing()+=KIZAMI){
	recom.Seed();
	//欠損のさせ方ループ
	for(recom.current()=0;recom.current()
	      <MISSINGTRIALS;recom.current()++){
	  //初期化
	  recom.reset();
	  //データを欠損
	  recom.revise_missing_values();
	  //データをtestに渡す
	  test.copydata(recom.sparseincompletedata());
	  test.ForSphericalData();	
	  test.reset();
	  //初期クラスタサイズ調整変数の設定
	  test.initialize_clustersize();
	  //初期帰属度の設定
	  test.initialize_membership2();
	  //クラスタリングループ数
	  test.iterates()=0;
	  while(1){
	    test.revise_centers();//bfcs
	    test.revise_dissimilarities();//hcs
	    test.revise_membership();//bfcm
	    //std::cout<<test.membership()<<std::endl;
	    test.revise_clusters_size();//bfcm
	    double diff_v
	      =max_norm(test.tmp_centers()-test.centers());
	    double diff_u
	      =max_norm(test.tmp_membership()-test.membership());
	    double diff_p
	      =max_norm(test.tmp_clusters_size()-test.clusters_size());
	    double diff=diff_u+diff_v+diff_p;
	    if(std::isnan(diff)){
	      std::cout<<"diff is nan"
		       <<"\tm="<<m
		       <<"\tclusters_number="
		       <<clusters_number<<std::endl;
	      test.reset();
	      exit(1);
	    }
	    if(diff<DIFF_FOR_STOP)break;
	    if(test.iterates()>=MAX_ITE)break;
	    test.iterates()++;
	  }
	  //目的関数値の計算
	  test.set_objective();
	  //recomに目的関数値を渡す
	  recom.obje(recom.Ccurrent())=test.objective();
	  //recomに帰属度を渡してクリスプ化
	  recom.crisp(test.membership(),test.centers());
	  //クラスタリング＋ピアソン相関係数の計算
	  //GroupLen Methodで予測
	  recom.reset2();
	  recom.pearsonsim_clustering();
	  recom.pearsonpred2();
	  recom.mae(dir[0], 0);
	  recom.fmeasure(dir[0], 0);
	  recom.ofs_objective(dir[0]);
	  test.ofs_selected_data(dir[0]);
	  recom.save_mae_f(dir);
	}
	recom.out_mae_f(dir);
      }
      //計測終了
      auto end=std::chrono::system_clock::now();
      auto endstart=end-start;
      std::string time="_"
	+std::to_string
	(std::chrono::duration_cast
	 <std::chrono::hours>(endstart).count())
	+"h"+std::to_string
	(std::chrono::duration_cast
	 <std::chrono::minutes>(endstart).count()%60)
	+"m"+std::to_string
	(std::chrono::duration_cast
	 <std::chrono::seconds>(endstart).count()%60)
	+"s";
      //計測時間でリネーム
      for(int i=0;i<(int)dir.size();i++)
	rename(dir[i].c_str(), (dir[i]+time).c_str());
    }//m
    //}//number of clusters
  return 0;
}