#ifndef TOOLS_H
#define TOOLS_H
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Tools{
public:
    Tools();
    virtual ~Tools();
    vector<string> splitrec(string &tmpstr);
    vector<string> splitarticle(string &tmpstr);
    vector<string> process_sample(string &sample, vector<string> &vec1
                                  ,vector<string> &vec2,vector<string> &user_feature);
};
#endif // TOOLS_H
