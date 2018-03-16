#include "mpi.h"
#include "omp.h"
#include "lr.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iomanip>
#include <ctime>
#include <hiredis/hiredis.h>

LR::LR(){}
LR::~LR(){}

float LR::sigmoid(float x){
 double sgm = 1/(1+exp(-(double)x));
 return (float)sgm;
}

vector<string> LR::splitline(string &line){
 vector<string> tmp_vec;
 size_t beg = 0, end = 0;
 string split_tag = "\t";
 while((end = line.find_first_of(split_tag,beg)) != string::npos){
  if(end > beg){
   string index_str = line.substr(beg, end - beg);
   tmp_vec.push_back(index_str);
  }
  beg = end + 1;
 }
 if(beg < line.size()){
  string index_end = line.substr(beg);
  tmp_vec.push_back(index_end);
 }
 return tmp_vec;
}
int LR::get_feature_num(string sample_filename, vector<int>& label, vec_vec& feature_matrix,int myid,int numprocs){
 /*cout<<"Calculate feature number......"<<endl;
   ifstream fin(sample_filename.c_str());
   if(!fin)cerr<<"open error get feature number..."<<sample_filename<<endl;

   string line, splittag = ":";
   int max_index = 0;
   vector<string> feature_index;
   sparse_feature sf;
   vec key_val;
   int i = 0;
   while(getline(fin,line)){
   i++;
   key_val.clear();
   feature_index.clear();
   feature_index = splitline(line);
   int y = atoi(feature_index[0].c_str());
   label.push_back(y);
   for(int i = 1; i < feature_index.size(); i++){  
   int index = 0;
   index = atoi(feature_index[i].c_str());
   if(index > max_index) max_index = index;
   }
   }
   fin.close();*/
 int max_index = 59336397;//train.feature
 //int max_index = 57452449;//smalltrain.feature
 cout<<"maxindex = "<<max_index<<endl;
 return max_index;
}

void LR::getfeature(string sample_fileline,vector<int>& label, vec_vec& feature_matrix, int myid, int numprocs){
 //ifstream fin(sample_fileline.c_str());
 vector<string> feature_index;
 sparse_feature sf;
 vec key_val;
 key_val.clear();
 feature_index.clear();
 //while(getline(fin, fileline)){
 //  feature_index = splitline(fileline);
 feature_index = splitline(sample_fileline);
 int y = atoi(feature_index[0].c_str());
 label.push_back(y);
 for(int i = 1; i < feature_index.size(); i++){  
  int index = 0, beg = 0, end = 0;
  while((end = feature_index[i].find_first_of(":",beg)) != string::npos){
   if(end > beg){
    string indexstr = feature_index[i].substr(beg,end-beg);
    index = atoi(indexstr.c_str());
    sf.id_index = index - 1;

   }
   //beg += 1; //this code must remain,it makes me crazy two days!!!
   beg = end + 1;
  }
  if(beg < feature_index[i].size()){
   string indexend = feature_index[i].substr(beg);
   int value = atoi(indexend.c_str());
   sf.id_val = value;
  }
  key_val.push_back(sf);
 }
 feature_matrix.push_back(key_val);
 //}
}

void LR::init_theta(vector<float>& theta, vector<float> &delta_theta,int feature_size){
 float init_theta = 0.0;
 for(size_t i = 0; i < feature_size; i++){
  theta.push_back(init_theta);
  delta_theta.push_back(init_theta);
 }
}

void LR::train(string sample_filename, vector<float>& theta, vector<float> &delta_theta, vector<int>& label,vector<vector<sparse_feature> >& feature_matrix,int myid,int numprocs){
 ifstream fin(sample_filename.c_str());//open file
 size_t step = 0, feature_number = 0;
 string sample_line;// feature line
 while(step < 1){
  while(getline(fin,sample_line)){
   if(feature_number < 10750519){
    //if(feature_number < 1 ){
    getfeature(sample_line, label, feature_matrix, myid,numprocs);
    feature_number++; 
    continue;
   }

   //getfeature(sample_filename,label,feature_matrix,myid,numprocs);
   size_t size = feature_matrix.size();//each pthread must had get 429020 lines features matrix.
   int start = myid * (size / numprocs), stop = (myid+1) * (size / numprocs);//
   if(myid == numprocs - 1) stop = size;
   vector<size_t> random; double old_y = 0;
   for(int circle = 0; circle < 200; circle++){
    srand((unsigned)time(0));random.clear();
    for(size_t i = start; i < stop; i++){
     //size_t ran_num = start +(stop - start)*rand()/(RAND_MAX + 1);
     size_t ran_num = start +rand()%(stop - start);
     random.push_back(ran_num);
    }
    //cout<<"random.size() "<<random.size()<<endl;
    // if(myid == 0)
    // for(size_t i = start; i < stop; i++)
    // cout<<random[i - start]<<endl;
    //              break;
    for(size_t i = start; i < stop; i++){
     float val,x = 0.0, y = 0.0;int k = i - start;int t = random[k];
     for(size_t j = 0; j < feature_matrix[t].size(); j++){
      int index = feature_matrix[t][j].id_index;
      val = feature_matrix[t][j].id_val; 
      x += theta[index]*val;
     }
     y = sigmoid(x);//cout<<"y = "<<y<<endl;
     //if(abs(old_y - y) < 0.01)return;
     old_y = y;
     for(size_t j = 0; j < feature_matrix[t].size(); j++)//
                          {
      if(label[t])
          delta_theta[feature_matrix[t][j].id_index] += 10*(y-label[t])*feature_matrix[t][j].id_val;//
       else delta_theta[feature_matrix[t][j].id_index] += (y-label[t])*feature_matrix[t][j].id_val;//
     }
     /*for(size_t j = 0; j < theta.size(); j++){
       int flag = 0;size_t index_fm;
       for(index_fm = 0; index_fm < feature_matrix[t].size(); index_fm++)
       if(j == feature_matrix[t][index_fm].id_index){flag = 1;break;}
     //if(flag == 1)delta_theta[j] += (y - label[t])*feature_matrix[t][j].id_val;//not delete,keep me crazy;
     if(flag == 1)delta_theta[j] += (y - label[t])*feature_matrix[t][index_fm].id_val;
     else delta_theta[j] += theta[j];//如果不在特征矩阵中，则只有theta项。
     }*/ 
     double reg = 0.0;
     if(i%500000 == 0){
      for(size_t j = 0; j < theta.size(); j++)
       reg += theta[j];
      //    theta[j] -= 0.000000001*(delta_theta[j]);//L2 regularization if paralles,theta[j] must be effected between other pthread.
      for(size_t j = 0; j < theta.size();j++)
       theta[j] -= 0.00000001*(delta_theta[j]+20*reg);//if paralles,theta[j] must be effected between other pthread.
      delta_theta.clear();        
     }
    }//end for start stop
   }//end for cirlce
   cout<<myid<<endl;
   feature_matrix.clear();label.clear();feature_number = 0;random.clear();
   }
   cout<<"step "<<step<<endl;
   step++;
  }
  fin.close();
 }
 void LR::savemodel(vector<float> &theta,int myid){
  ofstream fout("train.model");
  fout.setf(ios::fixed,ios::floatfield);
  fout.precision(7);
  for(int i = 0; i < theta.size(); i++){
   fout<<theta[i]<<endl;
  }
  fout.close();
 }
 void LR::loadmodel(vector<float> &theta){
  ifstream fin("train.model");
  //theta.clear();
  float param = 0;
  cout<<theta.size()<<" load "<<endl;
  for(int i = 0; i < theta.size(); i++){
   fin>>param;
   theta[i] = param;
  }
 }
 void LR::predict(string testfile, vector<float>& theta){
  //loadmodel(theta);
  cout<<"theta.size() = "<<theta.size()<<endl;
  cout<<"predic start-----------------------------------"<<endl;
  ifstream fin(testfile.c_str());
  string train_line;
  ofstream savefile("predict.ctr");
  savefile.setf(ios::fixed,ios::floatfield);
  savefile.precision(7);

  vector<float> predict_result;
  vector<string> predict_feature;
  float x;
  vector<int> preindex;
  vector<float> preval;
  while(getline(fin, train_line)){
   x = 0.0;
   predict_feature.clear();
   predict_feature = splitline(train_line);
   preindex.clear();
   preval.clear();
   for(size_t j = 0; j < predict_feature.size(); j++){
    int beg = 0, end = 0;
    while((end = predict_feature[j].find_first_of(":",beg)) != string::npos){
     if(end > beg){
      string string_sub = predict_feature[j].substr(beg, end - beg);
      int k = atoi(string_sub.c_str());
      preindex.push_back(k-1);
     }
     //beg += 1;
     beg = end + 1;
    }
    string string_end = predict_feature[j].substr(beg);
    int t = atoi(string_end.c_str());
    preval.push_back(t);
   }
   for(size_t j = 0; j < preindex.size(); j++){
    x += theta[preindex[j]]*preval[j];
   }
   float y = sigmoid(x);
   if (y == 1.0) cout<<"1 :"<<x<<endl;
   predict_result.push_back(y);
  }
  for(size_t j = 0; j < predict_result.size(); j++){
   savefile<<predict_result[j]<<endl;
  }
  fin.close();
  savefile.close();
 }
 double tmp[100000000];
 int main(int argc,char* argv[]){  
  int myid, numprocs,feature_num = 0,ans = 0;
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
  MPI_Status status;
  LR lr;
                const char *hostname = "127.0.0.1";
            int port = 6379;
                struct timeval timeout = {1,500000};
      redisContext *conn = redisConnectWithTimeout(hostname,port,timeout);
  if(conn == NULL || conn->err){redisFree(conn);return 0;}
  redisReply *reply;
                reply = (redisReply*)redisCommand(conn,"PING");
                printf("PING: %s\n", reply->str);
                freeReplyObject(reply);
  /* srand((unsigned)time(0));vector<size_t> random;random.clear();
     size_t start = 5, stop = 100;
     for(size_t i = start; i < stop; i++){
     size_t ran_num = start +rand()%(stop - start);
     random.push_back(ran_num);
     cout<<i-start<<":"<<ran_num<<endl;
     }
     cout<<"random.size() "<<random.size()<<endl;
     if(myid == 0)
     for(size_t i = start; i < stop; i++)
     cout<<random[i - start]<<endl;
     return 0;
     */
  string train_file = "smalltrain.feature";//the 3.9G traindata
  string test_file = "test.feature";
  feature_num = lr.get_feature_num(train_file, lr.label,lr.feature_matrix,myid,numprocs);//get feature number
  lr.init_theta(lr.theta,lr.delta_theta,feature_num);//initial
  //MPI_Barrier(MPI_COMM_WORLD);
  lr.train(train_file, lr.theta, lr.delta_theta,lr.label, lr.feature_matrix,myid,numprocs);//after train,each pthread have different theta,shoule be gather and average it.
  //return 0;        
  cout<<"after train "<<myid<<endl;
  if(myid != 0){
   memset(tmp, 0, sizeof(tmp));
   for(size_t i = 0; i < lr.theta.size(); i++)
    tmp[i] = lr.theta[i];
   MPI_Send(tmp, lr.theta.size(), MPI_DOUBLE, 0, 99, MPI_COMM_WORLD);

  }
  else{
   int size = lr.theta.size();
   memset(tmp, 0 , sizeof(tmp));
   for(int source = 1; source < 4; source++)
    MPI_Recv(tmp, lr.theta.size(), MPI_DOUBLE, source,99,MPI_COMM_WORLD,&status);
   for(size_t i = 0; i < lr.theta.size(); i++){
    lr.theta[i] += tmp[i];
   }
  }
  if(myid == 0){
   for(size_t i = 0; i < lr.theta.size(); i++)
    lr.theta[i] /= 4;
  }
  MPI_Barrier(MPI_COMM_WORLD);
  if(myid == 0){
   //delete []tmp;
   lr.feature_matrix.clear();
   lr.savemodel(lr.theta, myid);
  }
  //MPI_Barrier(MPI_COMM_WORLD);    
  if(myid == 0)
   lr.predict(test_file, lr.theta);
  MPI_Finalize();
  return 0;
 }
