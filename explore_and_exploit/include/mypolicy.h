#ifndef MYPOLICY_H
#define MYPOLICY_H
#include <string>
#include <vector>
#include <map>
#include <time.h>
#include <stdlib.h>
using namespace std;

class Mypolicy{
public:
    Mypolicy();
    virtual ~Mypolicy();
    void articlectr(string &artid,double ctr);
    int getrandom(int k);
    void simpleploicy(vector<string> &vec1, vector<string> &vec2, int num,int &click, int &t);
    void randomploicy(vector<string> &vec1, vector<string> &vec2, int num,int &click, int &t);
    void high_ctr_ploicy(vector<string> &vec1, vector<string> &vec2, int num,int &click, int &t);
    void epsilon_greedy(vector<string> &vec1, vector<string> &vec2, int num,int &click, int &t);
    void show(map<string,double>& art);

public:
    map<string,double>::iterator ctrindex;
    map<string,double> article;
    map<string,int> match_count;
    map<string,int> click_count;

};
#endif // MYPOLICY
