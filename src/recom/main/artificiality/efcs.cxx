#include"../../src/recom.h"
#include"../../src/klfcs.h"

//収束条件
#define MAX_ITE 1000
#define DIFF_FOR_STOP 1.0E-10

const int user_number=return_user_number();//ユーザ数
const int item_number=return_item_number();//アイテム数
const std::string data_name=return_data_name();//データの名前
const std::string InputDataName=
  "data/2018/sparse_"+data_name//入力するデータの場所
  +"_"+std::to_string(user_number)+"_"
  +std::to_string(item_number)+".txt";
const std::string METHOD_NAME="KLFCS";//クラスタリング手法名

int main(void){
  std::vector<std::string> dirs = MkdirFCS(METHOD_NAME);//データ読み込み
  //クラスタ数でループ
  //for(int clusters_number=4;clusters_number<=6;clusters_number++){
  int clusters_number=5;
    //Recomクラスの生成
    Recom recom(user_number, item_number
		, clusters_number, clusters_number, KESSON);
    recom.method_name()=METHOD_NAME;
    for(double lambda=1;lambda<=16;lambda*=2){//lambdaの範囲と刻み
      
      auto start=std::chrono::system_clock::now();//時間計測
      KLFCS test(item_number, user_number, clusters_number, lambda);
      std::vector<double> parameter= {lambda};
      std::vector<std::string> dir =
	Mkdir(parameter, clusters_number, dirs);//データ読み込み
      
      recom.input(InputDataName);//データ入力
      //欠損数ループ
      for(recom.missing()=KIZAMI;recom.missing()
	    <=KESSON;recom.missing()+=KIZAMI){
	recom.Seed();//シード値の初期化
	//欠損のさせ方ループ
	for(recom.current()=0;recom.current()
	      <MISSINGTRIALS;recom.current()++){
	  recom.reset();//初期化
	  recom.revise_missing_values();//データを欠損
	  test.copydata(recom.sparseincompletedata());//データをtestに渡す
	  test.ForSphericalData();//データをスパース化
	  test.reset();//初期化
	  test.initialize_clustersize();//初期クラスタサイズ調整変数//hcma
	  test.initialize_membership2();//初期帰属度//hcm
	  test.iterates()=0;//クラスタリングループ数
	  
	  //クラスタリングスタート
	  while(1){
	    test.revise_centers();
	    test.revise_dissimilarities();
	    test.revise_membership();
	    test.revise_clusters_size();
	    double diff_v
	      =max_norm(test.tmp_centers()-test.centers());
	    double diff_u
	      =max_norm(test.tmp_membership()-test.membership());
	    double diff_p
	      =max_norm(test.tmp_clusters_size()-test.clusters_size());
	    double diff=diff_u+diff_v+diff_p;
	    if(std::isnan(diff)){//diffがnanのエラー処理
	      std::cout<<"diff is nan \t"
		       <<lambda<<"\tC:"<<clusters_number<<std::endl;
	      test.reset();
	      exit(1);
	    }
	    if(diff<DIFF_FOR_STOP)break;
	    if(test.iterates()>=MAX_ITE)break;
	    test.iterates()++;
	  }
	  //クラスタリング終わり
	  
	  //目的関数値の計算
	  test.set_objective();
	  //recomに目的関数値を渡す
	  recom.obje(recom.Ccurrent())=test.objective();
	  //recomに帰属度を渡してクリスプ化
	  recom.crisp(test.membership(),test.centers());
	  
	  recom.reset2();
	  //クラスタリング＋ピアソン相関係数の計算
	  recom.pearsonsim_clustering();
	  recom.pearsonpred2();//グループレンズで欠損値を予測
	  recom.mae(dir[0], 0);//精度評価MAE
	  recom.fmeasure(dir[0], 0);//精度評価Fmeasure
	  recom.ofs_objective(dir[0]);
	  test.ofs_selected_data(dir[0]);
	  recom.save_mae_f(dir);
	}
	recom.out_mae_f(dir);//出力
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
    //   }//number of clusters
  return 0;
}
