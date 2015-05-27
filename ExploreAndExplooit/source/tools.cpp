#include <tools.h>
using namespace std;

Tools::Tools(){}
Tools::~Tools(){}

vector<string> Tools::splitrec(string &tmpstr)
{
    vector<string> tmp;
    tmp.clear();
    string::iterator it;
    string::iterator itbeg = tmpstr.begin();
    string::iterator itend = tmpstr.end();
    for(it = tmpstr.begin();it != tmpstr.end(); it++)
    {
        if(*it == ' ')
        {
            itend= it;
            string ss(itbeg,itend);
            tmp.push_back(ss);
            itbeg = it+1;
        }
    }
    string ss2(itbeg,tmpstr.end());
    tmp.push_back(ss2);
    return tmp;
}

vector<string> Tools::splitarticle(string &tmpstr)
{
    vector<string> tmp;
    tmp.clear();
    string::iterator it;
    string::iterator itbeg = tmpstr.begin();
    string::iterator itend = tmpstr.end();
    for(it = tmpstr.begin();it != tmpstr.end(); it++)
    {
        if(*it == ' ')
        {
            itend= it;
            string ss(itbeg+1,itend);
            tmp.push_back(ss);
            itbeg = it+1;
        }
    }
    string ss2(itbeg+1,tmpstr.end());
    tmp.push_back(ss2);
    return tmp;
}

vector<string> Tools::process_sample(string &sample, vector<string> &vec1
                                  ,vector<string> &vec2,vector<string> &user_feature)
{
    int index1;
    int index2;
    vec1.clear();
    vec2.clear();
    user_feature.clear();

    string tmp1 = "|user";
    index1 = sample.find_first_of(tmp1);
    string sub1 = sample.substr(0,index1-1);
    vec1 = splitrec(sub1);

    string tmp2 = "|id-";
    index2 = sample.find(tmp2);
    string sub2 = sample.substr(index2,sample.size()-index2);
    vec2 = splitarticle(sub2);

    string user_feature_string = sample.substr(index1+6,index2-index1-7);
    //cout<<user_feature_string<<endl;
    user_feature = splitrec(user_feature_string);
    for(int i = 0; i < user_feature.size(); i++)
        cout<<user_feature[i]<<" ";
    cout<<endl;
    cout<<2;
}
