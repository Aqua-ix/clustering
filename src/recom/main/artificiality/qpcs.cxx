#include"../../src/recom.h"
#include"../../src/qpcs.h"

#define MAX_ITE 1000
#define DIFF_FOR_STOP 1.0E-10
const int user_number=return_user_number();
const int item_number=return_item_number();
const std::string data_name=return_data_name();
const std::string InputDataName="data/2018/sparse_"+data_name
  +"_"+std::to_string(user_number)
  +"_"+std::to_string(item_number)+".txt";
const std::string METHOD_NAME="QPCS";
constexpr int clusters_number=1;//クラスタ数1

int main(void){
  std::vector<std::string> dirs = MkdirFCS(METHOD_NAME);
  Recom recom(user_number, item_number
	      ,clusters_number, clusters_number, KESSON);
  recom.method_name()=METHOD_NAME;

  double alpha=0.03;
  for(double lambda=32;lambda<=32;lambda*=2){
    for(double m=2.0;m<=5.0;m+=0.5){
	
	auto start=std::chrono::system_clock::now();
	QPCS test(item_number, user_number
		  , clusters_number, m, lambda ,alpha);
	std::vector<double> parameter= {lambda, m};
	std::vector<std::string> dir
	  = Mkdir(parameter, clusters_number, dirs);
	
	recom.input(InputDataName);
	for(recom.missing()=KIZAMI;recom.missing()
	      <=KESSON;recom.missing()+=KIZAMI){
	  recom.Seed();
	  for(recom.current()=0;recom.current()
		<MISSINGTRIALS;recom.current()++){
	    recom.reset();
	    recom.revise_missing_values();
	    test.copydata(recom.sparseincompletedata());
	    test.ForSphericalData();	
	    
	    for(int k=0;k<user_number;k++){//ユーザ数回クラスタリング
	      test.reset();
	      test.initialize_centers_one_cluster(k);//初期クラスタ中心
	     
	      test.iterates()=0;
	      while(1){
		test.revise_dissimilarities();
		test.revise_membership();
		test.revise_centers();
		//std::cout<<test.centers()<<std::endl;
		//std::cout<<test.dissimilarities()<<std::endl;
		//std::cout<<test.membership()<<std::endl;
		double diff_v
		  =max_norm(test.tmp_centers()-test.centers());
		double diff_u
		  =max_norm(test.tmp_membership()-test.membership());
		double diff=diff_u+diff_v;
			if(std::isnan(diff)){
		  std::cout<<"diff is nan \t"<<m<<"\t"
			   <<lambda<<"\tC:"<<clusters_number<<std::endl;
		  test.reset();
		  exit(1);
		  }
		
		if(diff<DIFF_FOR_STOP)break;
		if(test.iterates()>=MAX_ITE)break;
		test.iterates()++;
	      }
	      test.save_membebrship(k);//帰属度保存
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
	  }
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
    }//m
  return 0;
}
