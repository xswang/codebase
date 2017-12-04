#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <mypolicy.h>
#include <tools.h>
using namespace std;

Mypolicy policy;
Tools tool;

int main()
{
    ifstream test;
    //test.open("D:\\wxs\\coding\\E&E\\bin\\Debug\\yahoo.txt",ios::in);
    test.open("D:\\C++\\E&E\\bin\\Debug\\yahoo.txt",ios::in);

    //test.open("D:\\wxs\\ydata-fp-td-clicks-v2_0.20111002",ios::in);
   // for(int i = 0; i < 10; i++)
    //{
    //test.open("F:\\DATA\\dataR6B\\ydata-fp-td-clicks-v2_0.20111002",ios::in);
    if(!test)cout<<"error"<<endl;
    string sample;
    vector<string> vec1;
    vector<string> vec2;
    vector<string> user_feature;

    int count_of_match = 1;
    int click = 0;
    int click_or_not=0;
    int randnum;

    policy.article.clear();
    policy.click_count.clear();
    policy.match_count.clear();
    srand((int)time(0));
    int j = 0;
    while (getline(test, sample))
    {
        if(j == 1)break;
        tool.process_sample(sample,vec1,vec2,user_feature);
        sscanf(vec1[2].c_str(),"%d",&click_or_not);
        //policy.simpleploicy(vec1, vec2,click_or_not,click,count_of_match);


        //policy.randomploicy(vec1, vec2,click_or_not,click,count_of_match);
        //policy.epsilon_greedy(vec1, vec2,click_or_not,click,count_of_match);
        j++;


    }
    //for(map<string,int>::iterator index = policy.click_count.begin();
    //index != policy.click_count.end(); index++)
            //cout<<index->first<<" "<<index->second<<endl;
        //cout<<policy.click_count.size()<<endl;
     if(count_of_match > 1)
        cout<<"ctr = "<<(double)click/(count_of_match-1)<<endl;
     else cout<<"ctr = "<<(double)click/count_of_match<<endl;

     test.close();

    //}
     return 0;
}
