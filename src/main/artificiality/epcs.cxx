#include"recom.h"
#include"epcs.h"
#include"config.h"

//人工データ
//収束条件
#define MAX_ITE 1000
#define DIFF_FOR_STOP 1.0E-10

const int user_number=return_user_number();//ユーザ数
const int item_number=return_item_number();//アイテム数
const std::string data_name=return_data_name();//データの名前
const std::string InputDataName="sparse_"+data_name//入力するデータ
  +"_"+std::to_string(user_number)
  +"_"+std::to_string(item_number)+".txt";
const std::string METHOD_NAME="EPCS";//クラスタリング手法名
constexpr int clusters_number=1;//クラスタ数1

int main(void){
  std::vector<std::string> dirs
    = MkdirFCS(METHOD_NAME);//データ読み込み
  //Recomクラスの生成
  Recom recom(user_number, item_number
	      ,clusters_number, clusters_number, KESSON);
  recom.method_name()=METHOD_NAME;
  
  double alpha=0.03;
  for(double lambda=32;lambda<=256;lambda*=2){
        
  auto start=std::chrono::system_clock::now();//時間計測
  EPCS test(item_number, user_number
	    ,clusters_number, lambda, alpha);
  std::vector<double> parameter= {lambda};
  std::vector<std::string> dir=
    Mkdir(parameter, clusters_number, dirs);
      
  recom.input(DATA_DIR+InputDataName);//データ入力

  //動作チェック用
  //recom.missing()=KESSON;//
  //recom.Seed();//

  //欠損数ループ
  for(recom.missing()=KIZAMI;recom.missing()
	<=KESSON;recom.missing()+=KIZAMI){
    recom.Seed();//シード値の初期化
    //欠損のさせ方ループ
    for(recom.current()=0;recom.current()
	  <MISSINGTRIALS;recom.current()++){//5通り
      recom.reset();//初期化
      recom.revise_missing_values();//データを欠損
      test.copydata(recom.sparseincompletedata());//データをtestに渡す
      test.ForSphericalData();//球面データ化
	
	
      for(int k=0;k<user_number;k++){//ユーザ数分(100回)クラスタリング
	test.reset();//変数初期化
	//初期クラスタ中心(可能性クラスタリング)//pcm
	test.initialize_centers_one_cluster(k);
	test.iterates()=0;//クラスタリングループ数
	//クラスタリングスタート
	while(1){
	  test.revise_dissimilarities();//非類似度更新
	  test.revise_membership();//帰属度更新
	  test.revise_centers();//クラスタ中心更新
	  double diff_v
	    =max_norm(test.tmp_centers()-test.centers());
	  double diff_u
	    =max_norm(test.tmp_membership()-test.membership());
	  double diff=diff_u+diff_v;
	  if(std::isnan(diff)){//diffがnanのエラー処理
	    std::cout<<"diff is nan \t"
		     <<lambda<<" "<<alpha<<std::endl;
	    test.reset();
	    exit(1);
	  }
	  if(diff<DIFF_FOR_STOP)break;//収束条件
	  if(test.iterates()>=MAX_ITE)break;//収束条件
	  test.iterates()++;;//クラスタリングループ数
	}
	//クラスタリング終わり
	test.save_membebrship(k);//帰属度保存(100*100)
      }
	
      recom.pearsonsim_for_pcm(test.membership_pcm()
			       ,test.membership_threshold());
      recom.pearsonpred2();//GroupLens
      recom.mae(dir[0], 0);
      recom.fmeasure(dir[0], 0);
      recom.roc(dir[0]);
      recom.obje(recom.Ccurrent())=-1;
      recom.ofs_objective(dir[0]);
      test.ofs_selected_data(dir[0]);
      recom.choice_mae_f(dir);
	
    }//欠損パターン回(5回)終わるまで
    //AUC，MAE，F-measureの平均を計算，出力
    recom.precision_summury(dir);
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

  }//lambda
    
  return 0;
}
