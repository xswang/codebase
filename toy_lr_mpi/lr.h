#include <string>
#include <fstream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
using namespace std;
struct sparse_feature{
	int id_index;
 	float id_val;  
};
typedef vector<sparse_feature> vec; 
typedef vector<vector<sparse_feature> > vec_vec;
class LR{
    public:
	LR();
  	~LR();
  	vector<float> theta;
        vector<float> delta_theta;
	vec sample_feature_vec;
        vec_vec feature_matrix;
        vector<int> label;
	void loadmodel(vector<float> &theta);  
        float sigmoid(float x);
        vector<string> splitline(string &line); 
	void init_theta(vector<float>& theta, vector<float>& delta_theta,int feature_size);
        void getfeature(string line, vector<int>& label,vec_vec& feature_matrix,int myid,int numprocs);
        void train(string sample_filename, vector<float>& theta, vector<float> &delta_theta,vector<int>& label, vec_vec& feature_matrix,int myid,int numprocs); 
        int get_feature_num(string sample_file, vector<int>& label,vec_vec& feature_matrix,int myid,int numprocs);
        void savemodel(vector<float> &theta, int myid);
        void predict(string filename, vector<float>& theta);
    private:
};
