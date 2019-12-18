#include"recom.h"

Recom::Recom(int user,
             int item,
             int user_cen,
             int item_cen,
             int miss):
  Current(0),CCurrent(0),MCurrent(0),
  Missing(0),ClustersNum(0),
  OverlapThreshold(0),
  SparseIncompleteData(user, item),
  SparseCorrectData(user, item),
  NormalizedData(user, item),
  KessonIndex(miss, 2),
  Similarity(user, user),
  Mem(user_cen, user),
  ItemMem(item_cen, item),
  ResultMAE(METHOD_NUMBER, CLUSTERINGTRIALS),
  ResultFmeasure(METHOD_NUMBER, CLUSTERINGTRIALS),
  ChoicedMAE(MISSING_MAX/MISSING_DIFF
             -MISSING_MIN/MISSING_DIFF+1),
  ChoicedAUC(MISSING_MAX/MISSING_DIFF
      -MISSING_MIN/MISSING_DIFF+1),
  Prediction(miss),
  SparseIndex(miss),
  TP_FN((int)return_max_value()*10),
  FP_TN((int)return_max_value()*10),
  Obje(CLUSTERINGTRIALS),
  W(user){
  for(int i=0;i<(int)return_max_value()*10;i++){
    TP_FN[i]=0.0;
    FP_TN[i]=0.0;
  }
  for(int i=0;i<CLUSTERINGTRIALS;i++){
    Obje[i]=DBL_MAX;
  }
  }

std::string &Recom::method_name(void){
  return METHOD_NAME;
}

Vector Recom::obje(void) const{
  return Obje;
}

Matrix Recom::kessonindex(void) const{
  return KessonIndex;
}

double Recom::similarity(int index1, int index2){
  return Similarity[index1][index2];
}

double &Recom::obje(int index){
  return Obje[index];
}

int &Recom::current(void){
  return Current;
}

int &Recom::Ccurrent(void){
  return CCurrent;
}

int &Recom::Mcurrent(void){
  return MCurrent;
}

int &Recom::missing(void){
  return Missing;
}

int &Recom::clusters_num(void){
  return ClustersNum;
}

double &Recom::overlap_threshold(void){
  return OverlapThreshold;
}

SparseMatrix Recom::sparsecorrectdata(void) const{
  return SparseCorrectData;
}

SparseVector &Recom::sparsecorrectdata(int index){
  return SparseCorrectData[index];
}

SparseMatrix Recom::sparseincompletedata(void) const{
  return SparseIncompleteData;
}

SparseVector &Recom::sparseincompletedata(const int &index){
  return SparseIncompleteData[index];
}


void Recom::input(std::string InputDataName){
  std::ifstream ifs(InputDataName);
  if(!ifs){
    std::cerr << "DirectoryName : " <<InputDataName
              <<": could not open." << std::endl;
    exit(1);
  }
  for(int cnt=0;cnt<return_user_number();cnt++){
    int essencialSize;
    ifs >> essencialSize;
    SparseVector dummy(return_item_number(), essencialSize);
    for(int ell=0;ell<essencialSize;ell++){
      ifs >> dummy.indexIndex(ell) >> dummy.elementIndex(ell);
    }
    SparseCorrectData[cnt]=dummy;
  }
  ifs.close();
}

void Recom::reset_data(void){
  SparseIncompleteData=SparseCorrectData;
  for(int k=0;k<return_user_number();k++){
    for(int l=0;l<return_user_number();l++){
      Similarity[k][l]=0.0;
    }
  }
  return;
}

void Recom::reset_pred(){
  for(int miss=0;miss<Missing;miss++)
    Prediction[miss]=0.0;
  for(int i=0;i<(int)return_max_value()*10;i++){
    TP_FN[i]=0.0;
    FP_TN[i]=0.0;
  }
  return;
}

void Recom::reset_choice(){
  for(int miss=0;miss<ChoicedMAE.size();miss++){
    ChoicedMAE[miss]=0;
    ChoicedAUC[miss]=0;
  }
  return;
}

void Recom::revise_missing_values(void){
  int tmpRow,tmpCol;
  int seed = Current*MISSING_MAX;
  for(int m=0; m<Missing;){
    /****乱数生成****/
    std::mt19937_64 mt;
    mt.seed(seed);
    std::uniform_int_distribution<>
      randRow(0,return_user_number()-1);
    //ランダムに行番号生成
    tmpRow=randRow(mt);
    std::uniform_int_distribution<>
      randCol(0,SparseCorrectData[tmpRow].essencialSize()-1);
    //ランダムに列番号生成
    tmpCol=randCol(mt);
    //データ行すべて欠損させないように,一行に2要素は必ず残す
    int c=0;
    for(int i=0;i<SparseIncompleteData[tmpRow].essencialSize();i++)
      if(SparseIncompleteData[tmpRow].elementIndex(i)==0)
        c++;
    //既に欠損していない場合
    if(SparseIncompleteData[tmpRow].elementIndex(tmpCol)>0
       && SparseIncompleteData[tmpRow].essencialSize()-c>1){
      //要素を0にする
      SparseIncompleteData[tmpRow].elementIndex(tmpCol)=0;
      //欠損した行番号を保存
      KessonIndex[m][0]=tmpRow;
      //欠損した列番号を保存
      KessonIndex[m][1]=SparseIncompleteData[tmpRow]
        .indexIndex(tmpCol);
      //スパースデータの列番号を保存
      SparseIndex[m]=tmpCol;
      m++;
    }
    seed++;
  }
  return;
}

void Recom::mae(std::string text, int method_number){
  double result=0.0;
  for(int m=0;m<Missing;m++){
    result+=fabs(SparseCorrectData[KessonIndex[m][0]]
                 .elementIndex(SparseIndex[m])-Prediction[m]);
  }
  ResultMAE[method_number][CCurrent]=result/(double)Missing;
  std::string mae_dir = text+"/"+METHOD_NAME+"_MAE.txt";
  std::ofstream ofs(mae_dir, std::ios::app);
  if(!ofs){
    std::cerr << mae_dir <<" could not open "<<std::endl;
    exit(1);
  }
  ofs<<Missing<<"\t"<<CCurrent<<"\t"
     <<std::fixed<<std::setprecision(10)
     <<ResultMAE[method_number][CCurrent]<<std::endl;
  ofs.close();
  return;
}

void Recom::fmeasure(std::string text, int method_number){
  std::ofstream ofs(text+"/"+METHOD_NAME+"_Fmeasure.txt",
                    std::ios::app);
  for(int index=1;index<(int)return_max_value()*10;index++){
    double TP=0.0,FP=0.0,FN=0.0,TN=0.0;
    //閾値の設定
    double siki=(double)index/10.0;
    for(int m=0;m<Missing;m++){
      //正解値が閾値以上かつ，予測値が閾値以上の場合
      if((siki<=SparseCorrectData[KessonIndex[m][0]]
          .elementIndex(SparseIndex[m]))
         &&(siki<=Prediction[m]))
        TP+=1.0;
      //正解値が閾値を下回ったかつ，予測値が閾値上回った場合
      else if((siki>SparseCorrectData[KessonIndex[m][0]]
               .elementIndex(SparseIndex[m]))
              &&(siki<=Prediction[m]))
        FP+=1.0;
      //正解値が閾値上回ったかつ，予測値が閾値を下回った場合
      else if((siki<=SparseCorrectData[KessonIndex[m][0]]
               .elementIndex(SparseIndex[m]))
              &&(siki>Prediction[m]))
        FN+=1.0;
      //それ以外
      else if((siki>SparseCorrectData[KessonIndex[m][0]]
               .elementIndex(SparseIndex[m]))
              &&(siki>Prediction[m]))
        TN+=1.0;
      else
        continue;
    }
    //閾値がF-measureで設定した閾値だった場合
    if(siki==return_threshold()){
      double Precision=TP/(TP+FP);
      double Recall=TP/(TP+FN);
      ResultFmeasure[method_number][CCurrent]
        =(2.0*Recall*Precision)/(Recall+Precision);
      if(std::isnan(ResultFmeasure[method_number][CCurrent]))
        ResultFmeasure[method_number][CCurrent]=0.0;
      ofs<<Missing<<"\t"
         <<TP<<" "
         <<FP<<" "
         <<FN<<" "
         <<TN<<" "
         <<std::fixed<<std::setprecision(10)
         <<ResultFmeasure[method_number][CCurrent]
         <<std::endl;
    }
    if(TP+TN==Missing){
      TP_FN[index]=1.0;
      FP_TN[index]=1.0;
    }
    //Recall，Falloutの計算
    else{
      TP_FN[index]=TP/(TP+FN);
      FP_TN[index]=FP/(FP+TN);
      if((TP+FN)==0||(FP+TN)==0){
        TP_FN[index]=1.0;
        FP_TN[index]=1.0;
      }
    }
  }
  ofs.close();
  return;
}

void Recom::roc(std::string dir){
  std::string param_str="";
  std::string roc_str
    =dir+"/ROC/"+METHOD_NAME+"_ROC_"+param_str
    +std::to_string(Missing)+"_"
    +std::to_string(CCurrent)+"_sort.txt";
  //ROCでプロットする点の数
  int max_index=(int)return_max_value()*10;
  Vector False=FP_TN;
  Vector True=TP_FN;
  std::ofstream ofs(roc_str,std::ios::app);
  if(!ofs){
    std::cerr << roc_str <<" could not open "<<std::endl;
    exit(1);
  }
  //横軸でソート
  Sort(False,True,max_index);
  for(int i=0;i<max_index;i++)
    ofs<<std::fixed<<std::setprecision(10)
       <<False[i]<<"\t"<<True[i]<<std::endl;
  
  ofs.close();
  return;
}

void Recom::Sort(Vector &fal, Vector &tru, int index){
  double tmp1,tmp2;
  for(int j=0;j<index-1;j++){
    for(int k=j+1;k<index;k++){
      if(fal[j]>fal[k]){
        tmp1=fal[j];
        tmp2=tru[j];
        fal[j]=fal[k];
        tru[j]=tru[k];
        fal[k]=tmp1;
        tru[k]=tmp2;
      }
    }
  } 
  return;
}

void Recom::ofs_objective(std::string dir){
  std::ofstream ofs(dir+"/object.txt",std::ios::app);
  if(!ofs){
    std::cerr << "ofs_objective : file could not open" << std::endl;
    exit(1);
  }
  ofs<<Missing<<"\t"<<Current<<"\t";
  return;
}

int Recom::min_objective_index(void){
  double tmp=DBL_MAX; int obje_index=0;
  for(int i=0;i<CLUSTERINGTRIALS;i++)
    if(tmp>Obje[i]){
      tmp=Obje[i];
      obje_index=i;
    }
  return obje_index;
}
  
void Recom::choice(std::vector<std::string> dir, int p){
  int obje_index=0;
  if(p==1)
    obje_index=min_objective_index();
  for(int method=0;method<(int)dir.size();method++){
    /*** MAE ***/
    ChoicedMAE[MCurrent]+=ResultMAE[method][obje_index];
    std::ofstream ofs_mae(dir[method]+"/"+METHOD_NAME+"_choicedMAE.txt",
                          std::ios::app);
    if(!ofs_mae){
      std::cerr << "choice: MAE file could not open" << std::endl;
      exit(1);
    }
    ofs_mae << Missing << "\t"
            <<std::fixed<<std::setprecision(6)
            << ResultMAE[method][obje_index] << std::endl;

    /*** ROC ***/
    std::string oldname
      =dir[method]+"/ROC"+"/"+METHOD_NAME+"_ROC_"
      +std::to_string(Missing)+"_"
      +std::to_string(obje_index)+"_sort.txt";
    std::string newname
      =dir[method]+"/ROC/choice"+"/"+METHOD_NAME+"_ROC_"
      +std::to_string(Missing)+"_sort.txt";
    Rename(oldname,newname);
    
    /*** AUC ***/
    int max=(int)return_max_value()*10;
    Matrix rocarea((int)dir.size(), MCurrent, 0.0);
    Vector array1(max,0.0,"all"), array2(max,0.0,"all");
    std::ifstream ifs(newname);
    if(!ifs){
      std::cerr << "choice: ROC file input failed" << std::endl;
      exit(1);
    }
      
    for(int i=0;i<max;i++)
      ifs>>array1[i]>>array2[i];
    ifs.close();
    double resultAUC = 0;
    for(int i=0;i<max-1;i++){
      if((array1[i]<array1[i+1])){
        double low=array1[i+1]-array1[i];
        double height=fabs(array2[i+1]-array2[i]);
        double squarearea=low*array2[i];
        double triangle=(low*height)/2.0;
        resultAUC+=squarearea+triangle;
      }
      if(array2[i]==1.0)
        break;
    }
    ChoicedAUC[MCurrent]+=resultAUC;
    std::ofstream ofs_auc(dir[method]+"/"+METHOD_NAME+"_choicedAUC.txt",
                          std::ios::app);
    if(!ofs_auc){
      std::cerr << "choice: AUC file could not open" << std::endl;
      exit(1);
    }
    ofs_auc << Missing << "\t"
            <<std::fixed<<std::setprecision(6)
            << resultAUC << std::endl;
  }
  return;
}

void Recom::precision_summary(std::vector<std::string> dir){
  for(int method=0;method<(int)dir.size();method++){
    
    /*** MAE結果出力 ***/
    std::ofstream ofs_mae(dir[method]+"/"+METHOD_NAME+"_averageMAE.txt",
                          std::ios::out);
    if(!ofs_mae){
      std::cerr
        <<"precision_summary: averageMAE file could not open"
        <<std::endl;
      exit(1);
    }
    std::vector<double> ave_mae(MCurrent, 0.0);
    int missing=MISSING_MIN;
    for(int miss=0;miss<(int)ChoicedMAE.size();miss++){
      ave_mae[miss]=ChoicedMAE[miss]/(Current+1);
      ofs_mae<<missing<<"\t"
             <<std::fixed<<std::setprecision(6)
             <<ave_mae[miss]<<std::endl;
      missing+=MISSING_DIFF;
    }

    /*** AUC結果出力 ***/
    std::ofstream ofs_auc(dir[method]+"/"+METHOD_NAME+"_averageAUC.txt",
                          std::ios::out);
    if(!ofs_auc){
      std::cerr
        <<"precision_summary: averageAUC file could not open"
        <<std::endl;
      exit(1);
    }
    std::vector<double> ave_auc(MCurrent, 0.0);
    missing=MISSING_MIN;
    for(int miss=0;miss<(int)ChoicedAUC.size();miss++){
      ave_auc[miss]=ChoicedAUC[miss]/(Current+1);
      ofs_auc<<missing<<"\t"
             <<std::fixed<<std::setprecision(6)
             <<ave_auc[miss]<<std::endl;
      missing+=MISSING_DIFF;
    }
    
  }
  return;
}

void Recom::pearsonsim(void){
  for(int user1=0;user1<return_user_number();user1++){
    /*ユーザ1の非ゼロサイズ*/
    int user1_size=
      SparseIncompleteData[user1]
      .essencialSize();
    for(int user2=0;user2<return_user_number();user2++){
      double psum=0.0,sum1=0.0,sum2=0.0,sum1sq=0.0,sum2sq=0.0;
      double hyokasu=0.0;
      /*ユーザ1がユーザ2である場合*/
      if(user1==user2)
        Similarity[user1][user2]=0.0;
      else{
        /*ユーザ2の非ゼロサイズ*/
        int user2_size=
          SparseIncompleteData[user2].essencialSize();
        /*ユーザ2のインデックスを0から*/
        int user2_ell=0;
        for(int ell=0;ell<user1_size;ell++){
          /*ユーザ2のインデックスが
            ユーザ2の非ゼロサイズを上回ったらbreak ~20180606*/
          if(user2_size<user2_ell)break;
          /*ユーザ1の既評価値*/
          double user1_element
            =SparseIncompleteData[user1]
            .elementIndex(ell);
          /*ユーザ1の既評価値が欠損でなければ計算*/
          if(user1_element>0){
            //ユーザ1のインデックス*/
            int user1_index
              =SparseIncompleteData[user1]
              .indexIndex(ell);
            while(1){
              if(user2_size==user2_ell)break;
              /*ユーザ2のインデックス*/
              int user2_index
                =SparseIncompleteData[user2].indexIndex(user2_ell);
              /*ユーザ2の方が上回ったらbreak*/
              if(user1_index<user2_index)break;	      
              /*ユーザ1の既評価値*/
              double user2_element
                =SparseIncompleteData[user2].elementIndex(user2_ell);
              /*インデックスが揃った場合とユーザ既評価値が
                欠損されてなければ計算*/
              if((user1_index==user2_index)&&(user2_element>0)){
                hyokasu+=1.0;
                psum+=user1_element*user2_element;
                sum1+=user1_element;
                sum2+=user2_element;
                sum1sq+=pow(user1_element,2.0);
                sum2sq+=pow(user2_element,2.0);
                user2_ell++;
                break;
              }
              user2_ell++;
            }
          }
        }
        double numerator=psum-(sum1*sum2/hyokasu);
        double denominator=sqrt((sum1sq-pow(sum1,2.0)/hyokasu)
                                *(sum2sq-pow(sum2,2.0)/hyokasu));
        if(denominator==0 || std::isnan(denominator))
          Similarity[user1][user2]=0.0;
        else
          Similarity[user1][user2]=numerator/denominator;
      }
    }
  }
  return;
}

void Recom::pearsonsim_fcs(void){
  for(int user1=0;user1<return_user_number();user1++){
    int user1_size/*ユーザ1の既評価数*/
      =SparseIncompleteData[user1].essencialSize();
    // CLUSTERING_PEAR
    int tmpcenternum=0;
    for(int i=0;i<Mem.rows();i++)//帰属度行列の行
      if(Mem[i][user1]==1.0)
        tmpcenternum=i;
    for(int user2=0;user2<return_user_number();user2++){
      double psum=0.0,sum1=0.0,sum2=0.0,sum1sq=0.0,sum2sq=0.0;
      double hyokasu=0.0;
      /*ユーザ2がユーザ1である，または
        ユーザ1が属すユーザクラスタに属さないユーザであった場合
        ユーザ2とユーザ1の類似度を0にすることで計算させない*/
      if(user1==user2 || Mem[tmpcenternum][user2]==0)
        Similarity[user1][user2]=0.0;
      else{	
        int user2_size/*ユーザ2の既評価数*/
          =SparseIncompleteData[user2].essencialSize();
        /*現在のユーザ2の既評価値インデックス*/
        int user2_ell=0;
        for(int ell=0;ell<user1_size;ell++){
          /*ユーザ2の既評価値インデックスがユーザ2の
            既評価数を上回ったらbreak*/
          if(user2_size<user2_ell)
            break;
          /*ユーザ1の現在の既評価値*/
          double user1_element
            =SparseIncompleteData[user1]
            .elementIndex(ell);
          /*ユーザ1の現在の既評価値が欠損されてなければ計算*/
          if(user1_element>0){
            /*ユーザ1の現在の評価値インデックスのインデックス*/
            int user1_index
              =SparseIncompleteData[user1].indexIndex(ell);
            while(1){
              if(user2_size==user2_ell)break;
              /*ユーザ2の現在の評価値インデックスのインデックス*/
              int user2_index
                =SparseIncompleteData[user2].indexIndex(user2_ell);
              /*ユーザ2の方が上回ったらbreak*/
              if(user1_index<user2_index)
                break;
              /*現在のユーザの既評価値*/
              double user2_element
                =SparseIncompleteData[user2].elementIndex(user2_ell);
              /*インデックスが揃った場合とユーザ既評価値が
                欠損されてなければ計算*/
              if((user1_index==user2_index)&&(user2_element>0)){
                hyokasu+=1.0;
                psum+=user1_element*user2_element;
                sum1+=user1_element;
                sum2+=user2_element;
                sum1sq+=pow(user1_element,2.0);
                sum2sq+=pow(user2_element,2.0);
                user2_ell++;
                break;
              }
              /*現在のユーザの既評価値インデックスインクリメント*/
              user2_ell++;
            }
          }
        }
        double numerator=psum-(sum1*sum2/hyokasu);
        double denominator=
          sqrt((sum1sq-pow(sum1,2.0)/hyokasu)*(sum2sq-pow(sum2,2.0)/hyokasu));
        if(denominator==0 || std::isnan(denominator))
          Similarity[user1][user2]=0.0;
        else
          Similarity[user1][user2]=numerator/denominator;
      }
    }
  }
  return;
}

void Recom::pearsonsim_pcs(const int clusters_number){
  for(int user1=0;user1<return_user_number();user1++){
    int user1_size/*ユーザ1の既評価数*/
      =SparseIncompleteData[user1].essencialSize();
    // CLUSTERING_PEAR
    int tmpcenternum=0;
    for(int i=0;i<clusters_number;i++)//帰属度行列の行
      if(Mem[i][user1]==1.0)
        tmpcenternum=i;
    for(int user2=0;user2<return_user_number();user2++){
      double psum=0.0,sum1=0.0,sum2=0.0,sum1sq=0.0,sum2sq=0.0;
      double hyokasu=0.0;
      /*ユーザ2がユーザ1である，または
        ユーザ1が属すユーザクラスタに属さないユーザであった場合
        ユーザ2とユーザ1の類似度を0にすることで計算させない*/
      if(user1==user2 || Mem[tmpcenternum][user2]==0)
        Similarity[user1][user2]=0.0;
      else{	
        int user2_size/*ユーザ2の既評価数*/
          =SparseIncompleteData[user2].essencialSize();
        /*現在のユーザ2の既評価値インデックス*/
        int user2_ell=0;
        for(int ell=0;ell<user1_size;ell++){
          /*ユーザ2の既評価値インデックスがユーザ2の
            既評価数を上回ったらbreak*/
          if(user2_size<user2_ell)
            break;
          /*ユーザ1の現在の既評価値*/
          double user1_element
            =SparseIncompleteData[user1]
            .elementIndex(ell);
          /*ユーザ1の現在の既評価値が欠損されてなければ計算*/
          if(user1_element>0){
            /*ユーザ1の現在の評価値インデックスのインデックス*/
            int user1_index
              =SparseIncompleteData[user1].indexIndex(ell);
            while(1){
              if(user2_size==user2_ell)break;
              /*ユーザ2の現在の評価値インデックスのインデックス*/
              int user2_index
                =SparseIncompleteData[user2].indexIndex(user2_ell);
              /*ユーザ2の方が上回ったらbreak*/
              if(user1_index<user2_index)
                break;
              /*現在のユーザの既評価値*/
              double user2_element
                =SparseIncompleteData[user2].elementIndex(user2_ell);
              /*インデックスが揃った場合とユーザ既評価値が
                欠損されてなければ計算*/
              if((user1_index==user2_index)&&(user2_element>0)){
                hyokasu+=1.0;
                psum+=user1_element*user2_element;
                sum1+=user1_element;
                sum2+=user2_element;
                sum1sq+=pow(user1_element,2.0);
                sum2sq+=pow(user2_element,2.0);
                user2_ell++;
                break;
              }
              /*現在のユーザの既評価値インデックスインクリメント*/
              user2_ell++;
            }
          }
        }
        double numerator=psum-(sum1*sum2/hyokasu);
        double denominator=sqrt((sum1sq-pow(sum1,2.0)/hyokasu)
                                *(sum2sq-pow(sum2,2.0)/hyokasu));
        if(denominator==0 || std::isnan(denominator))
          Similarity[user1][user2]=0.0;
        else
          Similarity[user1][user2]=numerator/denominator;
      }
    }
  }
  return;
}

void Recom::pearsonsim_pcs_threshold(const Matrix &Membership_PCM,
                                     const Vector &Threshold){
  for(int user1=0;user1<return_user_number();user1++){
    int user1_size/*ユーザ1の既評価数*/
      = SparseIncompleteData[user1].essencialSize();
    for(int user2=0;user2<return_user_number();user2++){
      double psum=0.0,sum1=0.0,sum2=0.0,sum1sq=0.0,sum2sq=0.0;
      double hyokasu=0.0;
      /*ユーザ2がユーザ1である，または
        ユーザ1が属すユーザクラスタに属さないユーザであった場合(中央値未満)
        ユーザ2とユーザ1の類似度を0にすることで計算させない*/
      if(user1==user2 || Membership_PCM[user1][user2]<Threshold[user1])
        Similarity[user1][user2]=0.0;
      else{
        int user2_size/*ユーザ2の既評価数*/
          = SparseIncompleteData[user2].essencialSize();
        int user2_ell=0;/*現在のユーザ2の既評価値インデックス*/
	
        for(int ell=0;ell<user1_size;ell++){
          /*ユーザ2の既評価値インデックスが
            ユーザ2の既評価数を上回ったらbreak*/
          if(user2_size<user2_ell)break;
          /*ユーザ1の現在の既評価値*/
          double user1_element
            =SparseIncompleteData[user1].elementIndex(ell);
	  
          /*ユーザ1の現在の既評価値が欠損されてなければ計算*/
          if(user1_element>0){
            /*ユーザ1の現在の評価値インデックスのインデックス*/
            int user1_index
              =SparseIncompleteData[user1].indexIndex(ell);
	    
            while(1){
              if(user2_size==user2_ell)break;
              /*ユーザ2の現在の評価値インデックスのインデックス*/
              int user2_index
                =SparseIncompleteData[user2].indexIndex(user2_ell);
              /*ユーザ2の方が上回ったらbreak*/
              if(user1_index<user2_index)break;
              /*現在のユーザの既評価値*/
              double user2_element
                =SparseIncompleteData[user2].elementIndex(user2_ell);
	      
              /*インデックスが揃った場合とユーザ既評価値が
                欠損されてなければ計算*/
              if((user1_index==user2_index)&&(user2_element>0)){
                hyokasu+=1.0;
                psum+=user1_element*user2_element;
                sum1+=user1_element;
                sum2+=user2_element;
                sum1sq+=pow(user1_element,2.0);
                sum2sq+=pow(user2_element,2.0);
                user2_ell++;
                break;
              }
              /*現在のユーザの既評価値インデックスインクリメント*/
              user2_ell++;
            }//while(1)
          }//user1_element>0
        }//ell<user1_size
        double numerator=psum-(sum1*sum2/hyokasu);
        double denominator=sqrt((sum1sq-pow(sum1,2.0)/hyokasu)
                                *(sum2sq-pow(sum2,2.0)/hyokasu));
        //分母が0かnanなら
        if(denominator==0 || std::isnan(denominator))
          //計算させない
          Similarity[user1][user2]=0.0;
        else
          //類似度計算
          Similarity[user1][user2]=numerator/denominator;
      }
    }
  }
  return;
}

void Recom::revise_prediction(void){
  //Missingは現在の欠損数
  for(int index=0;index<Missing;index++){
    double numerator=0.0,denominator=0.0;
    //KessonIndexは欠損させた場所
    int miss_user_index=KessonIndex[index][1];
    //ユーザ数
    for(int i=0;i<return_user_number();i++){
      if(Similarity[KessonIndex[index][0]][i]>0.0){
        //ユーザの既評価値スパース化後サイズ
        int user_size
          =SparseIncompleteData[i].essencialSize();
        //ユーザのサイズ分
        for(int ell=0;ell<user_size;ell++){
          //ユーザの既評価値インデックス
          int user_index
            =SparseIncompleteData[i].indexIndex(ell);
          //ユーザの欠損インデックスが
          //ユーザの既評価インデックスを上回ったらbreak
          if(user_index>miss_user_index)break;
          //ユーザの既評価値
          double user_element
            =SparseIncompleteData[i].elementIndex(ell);
          //ユーザの既評価値が欠損してない、またはインデックスが一致したら計算
          if((user_element>0.0)&&(user_index==miss_user_index)){
            numerator+=Similarity[KessonIndex[index][0]][i]
              *(user_element-user_average(i));
            denominator+=Similarity[KessonIndex[index][0]][i];
            break;
          }
        }//ユーザ数
      }
    }
    if(denominator==0)
      //分母０なら予測欠損値は既評価値の平均
      Prediction[index]=user_average(KessonIndex[index][0]);
    else {
      //そうでなければ式の通り
      Prediction[index]=user_average(KessonIndex[index][0])
        +numerator/denominator;
    }
    //nanの処理
    if(std::isnan(Prediction[index])) Prediction[index]=0.0;
  }
  return;
}

double Recom::user_average(int index){
  double result=0.0;
  int hyokazu=0;
  for(int i=0;i<SparseIncompleteData[index].essencialSize();i++){
    if(SparseIncompleteData[index].elementIndex(i)>0.0){
      result+=SparseIncompleteData[index].elementIndex(i);
      hyokazu++;
    }
  }
  return result/hyokazu;
}

void Recom::crisp(const Matrix &Membership){
  for(int k=0;k<return_user_number();k++){
    for(int i=0;i<Membership.rows();i++){
      Mem[i][k]=0.0;
    }
    double max=-DBL_MAX;
    int max_index=-1;
    for(int i=0;i<Membership.rows();i++){
      if(Membership[i][k]>max){
        max=Membership[i][k];
        max_index=i;
      }
    }
    Mem[max_index][k]=1.0;
  }
  return;
}

void Recom::crisp(const Matrix &Membership, int clusters_number){
  for(int k=0;k<return_user_number();k++){
    for(int i=0;i<clusters_number;i++){
      Mem[i][k]=0.0;
    }
    double max=-DBL_MAX;
    int max_index=-1;
    for(int i=0;i<clusters_number;i++){
      if(Membership[i][k]>max){
        max=Membership[i][k];
        max_index=i;
      }
    }
    Mem[max_index][k]=1.0;
  }
}

void Recom::overlap(const Matrix &Membership){
  for(int k=0;k<return_user_number();k++){
    for(int i=0;i<Membership.rows();i++){
      Mem[i][k]=0.0;
    }
    double max=-DBL_MAX;
    int max_index=-1;
    for(int i=0;i<Membership.rows();i++){
      if(Membership[i][k]>max){
        max=Membership[i][k];
        max_index=i;
      }
    }
    Mem[max_index][k]=1.0;
    if(OverlapThreshold < 1.0){
      for(int i=0;i<Membership.rows();i++){
        if(Membership[i][k]>=Membership[max_index][k]*OverlapThreshold){
          Mem[i][k]=1.0;
        }
      }
    }
  }
  return;
}

void Recom::overlap(const Matrix &Membership, int clusters_number){
  for(int k=0;k<return_user_number();k++){
    for(int i=0;i<clusters_number;i++){
      Mem[i][k]=0.0;
    }
    double max=-DBL_MAX;
    int max_index=-1;
    for(int i=0;i<clusters_number;i++){
      if(Membership[i][k]>max){
        max=Membership[i][k];
        max_index=i;
      }
    }
    Mem[max_index][k]=1.0;
    if(OverlapThreshold < 1.0){
      for(int i=0;i<clusters_number;i++){
        if(Membership[i][k]>=Membership[max_index][k]*OverlapThreshold){
          Mem[i][k]=1.0;
        }
      }
    }
  }
  return;
}

int return_user_number(){//ユーザ数
#ifdef MOVIE
  return 905;
#elif defined BOOK
  return 1091;//1090;
#elif defined JESTER
  return 2916;
#elif defined MOVIE
  return 500;
#elif defined LIBIMSETI
  return 866;//500;
#elif defined EPINIONS
  return 1022;//2000;
#elif defined SUSHI
  return 5000;
#elif defined ARTIFICIALITY
  return 100;
#elif defined TEST
  return 100;
#else
  std::cout<<"Error: Please specify USER NUMBER.\n";
  exit(1);
#endif
}

int return_item_number(){//アイテム数
#ifdef MOVIE
  return 684;
#elif defined BOOK
  return 2248;//2247;
#elif defined JESTER
  return 140;
#elif defined MOVIE
  return 2523;
#elif defined LIBIMSETI
  return 1156;//2041;
#elif defined EPINIONS
  return 835;//517;
#elif defined SUSHI
  return 100;
#elif defined ARTIFICIALITY
  return 100;
#elif defined TEST
  return 1002;
#else
  std::cout<<"Error: Please specify ITEM NUMBER.\n";
  exit(1);
#endif
}

double return_threshold(){//閾値
#ifdef MOVIE
  return 3.5;
#elif defined BOOK
  return 7.0;
#elif defined JESTER
  return 14.7;
#elif defined MOVIE
  return 3.5;
#elif defined LIBIMSETI
  return 7.0;
#elif defined EPINIONS
  return 3.5;
#elif defined SUSHI
  return 3.5;
#elif defined ARTIFICIALITY
  return 3.5;
#elif defined TEST
  return 3.5;
#else
  std::cout<<"Error: Please specify THRESHOLD.\n";
  exit(1); 
#endif
}

double return_max_value(){
#ifdef MOVIE
  return 5.0;
#elif defined BOOK
  return 10.0;
#elif defined JESTER
  return 21.0;
#elif defined MOVIE
  return 5.0;
#elif defined LIBIMSETI
  return 10.0;
#elif defined EPINIONS
  return 5.0;
#elif defined SUSHI
  return 5.0;
#elif defined ARTIFICIALITY
  return 5.0;
#elif defined TEST
  return 5.0;
#else
  std::cout<<"Error: Please specify MAX VALUE.\n";
  exit(1);
#endif
}

std::string return_data_name(){//データ名
#ifdef MOVIE
  return "movie";
#elif defined BOOK
  return "book";
#elif defined JESTER
  return "jester";
#elif defined MOVIE
  return "movie10M";
#elif defined LIBIMSETI
  return "libimseti";
#elif defined EPINIONS
  return "epinions";
#elif defined SUSHI
  return "sushi";
#elif defined ARTIFICIALITY
  return "artificiality";
#elif defined TEST
  return "artificiality_overlap";
#else
  std::cout<<"Error: Please specify DATA NAME.\n";
  exit(1);
#endif
}

void FILE_ENDL(std::string text){
  std::ofstream ofs(text,std::ios::app);
  ofs<<std::endl;
  ofs.close();
  return;
}

void Rename(std::string filename, std::string newname){
  if(!access(filename.c_str(),0)){ //If the file exists
    //Successfully deleted
    if(!rename(filename.c_str(),newname.c_str())){
      // std::cout<<"roctxtFile successfully  renamed"
      //          <<std::endl ;
      // std::cout<<newname<<std::endl;
    }
    else//Cannot rename: file not open or insufficient permissions
      {
        std::cout
          <<"The file cannot be renamed"
          <<" (may be the following reasons):"
          <<std::endl;
        std::cout<<"\t"<<"1. "
                 <<newname<<" Already exists"
                 <<std::endl
                 << "\t" << "2. "<<newname
                 <<" Being used, not closed"
                 <<std::endl
                 <<"\t"<<"3. "
                 <<"You do not have permission to rename this file"
                 <<std::endl;
      }
  }else{//The file does not exist
  }
  return;
}

std::vector<std::string> MkdirFCS(std::string method){
  std::vector<std::string> v;
  std::string dir = RESULT_DIR;
  mkdir(dir.c_str(),0755);
  std::string d=
    dir+method+"_"+return_data_name();
  mkdir(d.c_str(),0755);
  v.push_back(d);
  return v;
}

std::vector<std::string>
Mkdir(int missing, std::vector<std::string> dirs){
  std::vector<std::string> v;  
  for(int i=0;i<(int)dirs.size();i++){
    const std::string dir=
      dirs[i]+"/missing_pattern"+std::to_string(missing);
    v.push_back(dir);
    mkdir(dir.c_str(),0755);
    //ROCフォルダ作成
    const std::string roc=dir+"/ROC";
    mkdir(roc.c_str(),0755);
    //選ばれるROCファイルをまとめるフォルダ作成
    const std::string choice=roc+"/choice";
    mkdir(choice.c_str(),0755);
  }
  return v;
}

std::vector<std::string>
Mkdir(int c, std::vector<double> params,
      int missing, std::vector<std::string> dirs){
  std::vector<std::string> v;  
  for(int i=0;i<(int)dirs.size();i++){
    //クラスタ数フォルダ作成
    const std::string c_dir = dirs[i]+"/clusters_number"+std::to_string(c);
    mkdir(c_dir.c_str(),0755);
    //パラメータフォルダ作成
    std::string p_str = "/params";
    for(int p=0;p<(int)params.size();p++){
      p_str += "_"+std::to_string(params[p]);
    }
    const std::string p_dir = c_dir + p_str;
    mkdir(p_dir.c_str(),0755);
    //欠損パターンフォルダ作成
    const std::string m_dir
      = p_dir + "/missing_pattern"+std::to_string(missing);
    mkdir(m_dir.c_str(),0755);
    v.push_back(m_dir);
    //ROCフォルダ作成
    const std::string roc=m_dir+"/ROC";
    mkdir(roc.c_str(),0755);
    //選ばれるROCファイルをまとめるフォルダ作成
    const std::string choice=roc+"/choice";
    mkdir(choice.c_str(),0755);
  }
  return v;
}

std::vector<std::string>
Mkdir(int c, double threshold, std::vector<double> params,
      int missing, std::vector<std::string> dirs){
  std::vector<std::string> v;  
  for(int i=0;i<(int)dirs.size();i++){
    //クラスタ数フォルダ作成
    const std::string c_dir = dirs[i]+"/clusters_number"+std::to_string(c);
    mkdir(c_dir.c_str(),0755);
    //オーバーラップ閾値フォルダ作成
    const std::string t_dir
      = c_dir+"/overlap_threshold"+std::to_string(threshold);
    mkdir(t_dir.c_str(),0755);
    //パラメータフォルダ作成
    std::string p_str = "/params";
    for(int p=0;p<(int)params.size();p++){
      p_str += "_"+std::to_string(params[p]);
    }
    const std::string p_dir = t_dir + p_str;
    mkdir(p_dir.c_str(),0755);
    //欠損パターンフォルダ作成
    const std::string m_dir
      = p_dir + "/missing_pattern"+std::to_string(missing);
    mkdir(m_dir.c_str(),0755);
    v.push_back(m_dir);
    //ROCフォルダ作成
    const std::string roc=m_dir+"/ROC";
    mkdir(roc.c_str(),0755);
    //選ばれるROCファイルをまとめるフォルダ作成
    const std::string choice=roc+"/choice";
    mkdir(choice.c_str(),0755);
  }
  return v;
}

std::vector<std::string>
Mkdir(std::vector<std::string> methods){
  std::vector<std::string> v;
  std::string dir = RESULT_DIR;
  mkdir(dir.c_str(),0755);
  for(int i=0;i<(int)methods.size();i++){
    std::string d=
      dir+methods[i]
      +"_"+return_data_name();
    mkdir(d.c_str(),0755);
    //ROCフォルダ作成
    const std::string roc=d+"/ROC";
    mkdir(roc.c_str(),0755);
    //選ばれるROCファイルをまとめるフォルダ作成
    const std::string choice=roc+"/choice";
    mkdir(choice.c_str(),0755);
    v.push_back(d);
  }
  return v;
}
