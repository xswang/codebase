#include <iostream>
#include <cmath>
#include <fstream>
#include <map>
#include <iomanip>
using namespace std;


double trapezoid(double x1, double x2, double y1, double y2){
    double base = fabs(x1 - x2);
    double height = (y1 + y2)/2;
    return base*height;
}
struct mycomp{
    bool operator()(const double &a, const double &b){
        if(a != b)return a > b;
        else return a > b;
    }
};

int main(){
    multimap<double,int,mycomp> test;
    //multimap<double, int>test;
    ifstream fctr("predict.ctr");
    ifstream fclick("click");
    ofstream fout("auc");
    if(!fctr)cout<<"open ctr file error!"<<endl;
    if(!fclick)cout<<"open click file error"<<endl;
    double ctr,click;
    while(fctr>>ctr){
        fclick>>click;
        test.insert(pair<double,int>(ctr,click));
    }
    cout<<test.size()<<endl;
    double fp = 0.0, tp = 0.0;
    double fp_pre = 0.0, tp_pre = 0.0;
    double area = 0.0;
    double f_pre = -99999999;
    int i = 1,p = 0, N = 0;
    multimap<double,int,mycomp>::iterator it;
    //multimap<double, int>::iterator it;
    cout.setf(ios::fixed);
    fout.setf(ios::fixed);
    for(it = test.begin(); it != test.end();it++){
        fout<<setprecision(7)<<it->first<<"\t"<<it->second<<endl;
        //cout<<setprecision(7)<<it->first<<"\t"<<it->second<<endl;
        if(it->first != f_pre){
            area += trapezoid(fp,fp_pre,tp,tp_pre);
            f_pre = it->first;
            fp_pre = fp;
            tp_pre = tp;  
        }
        if(it->second != 0){
            tp += 1;
            p++;
        }
        else if(it->second == 0){
            fp += 1;
            N++;
        }
    } 
    fout.close();
    cout<<N<<"--"<<p<<endl;
    area += trapezoid(N,fp_pre,p,tp_pre);
    area /= (p*N);
    cout<<"AUC = "<<area<<endl; 
    return 0;
}
