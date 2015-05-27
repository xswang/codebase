#include <mypolicy.h>
#include <iostream>
using namespace std;

Mypolicy::Mypolicy()
{
}
Mypolicy::~Mypolicy()
{
}

struct mycomp{
    bool operator()(const double &a, const double &b)
    {
        if(a != b) return a > b;
        else return a > b;
    }
};

int Mypolicy::getrandom(int k)
{
    return rand()%k;
}

void Mypolicy::show(map<string,double>& art)
{
    for(ctrindex = art.begin(); ctrindex != art.end(); ctrindex++)
        cout<<ctrindex->first<<"  "<<ctrindex->second<<endl;
}

void Mypolicy::articlectr(string &artid,double ctr)
{
    ctrindex = article.find(artid);
    if(ctrindex == article.end())
        article.insert(make_pair(artid,ctr));
    else article[artid] = ctr;
}

void Mypolicy::simpleploicy(vector<string> &vec1, vector<string> &vec2, int num,int &click, int &t)
{
    //cout<<vec1[1]<<" "<<vec2[0]<<endl;
    if(vec2[0] == vec1[1])//如果article set 中第一个文章和show给用户的文章匹配。
    {
        map<string,int>::iterator index = match_count.find(vec1[1]);//先从匹配文章集合中查找
        if(index == match_count.end())//如果还没被匹配过。
            match_count.insert(make_pair(vec1[1],1));//放进集合中，记录为匹配1次。
        else match_count[vec1[1]]++;//如果已经被匹配过了，则匹配次数加1

        map<string,int>::iterator clickindex = click_count.find(vec1[1]);//从点击文章的集合中查找
        if(clickindex == click_count.end())//如果点击集合中没有
            click_count.insert(make_pair(vec1[1],num));//就放进点击集合中，次数为num(0或者1)
        else click_count[vec1[1]]+= num;//如果点击集合中有，则将点击次数加上该次的点击次数。

        double ctr = (double)click_count[vec1[1]]/match_count[vec1[1]];//计算匹配到的文章的点击率。
        articlectr(vec1[1],ctr);//放到点击率的集合中。
        click += num;//记录总的点击率
        t++;//记录总的匹配次数。
    }
}

void Mypolicy::randomploicy(vector<string> &vec1, vector<string> &vec2, int num,int &click, int &t)
{//随机推荐文章。
    int randnum = getrandom(vec2.size());//从0-article集合大小中产生随机数。
    //cout<<randnum<<endl;
    //cout<<"--"<<vec2[randnum]<<endl;
    if(vec1[1] == vec2[randnum])//如果随机产生的这个文章刚好和展示给用户的文章匹配。
    {
        map<string,int>::iterator index = match_count.find(vec1[1]);
        if(index == match_count.end())
            match_count.insert(make_pair(vec1[1],1));
        else match_count[vec1[1]]++;

        map<string,int>::iterator clickindex = click_count.find(vec1[1]);
        if(clickindex == click_count.end())
            click_count.insert(make_pair(vec1[1],num));
        else click_count[vec1[1]]+= num;

        double ctr = (double)click_count[vec1[1]]/match_count[vec1[1]];
        articlectr(vec1[1],ctr);
        click += num;
        t++;
    }
}

void Mypolicy::high_ctr_ploicy(vector<string> &vec1, vector<string> &vec2, int num,int &click, int &t)
{//选择ctr最高的推荐给用户。
    map<double,string,mycomp> ctr_actileid;//按照ctr对文章进行排序的集合。由原始的article:ctr集合转化而来。
    map<double,string>::iterator index;
    if(article.size() != 0){//在最开始的时候，按照最高ctr推荐时，是没有候选文章的，
        //只有通过一定的方法,比如随机或者首选第一个等方法，预先选定一部分放进已经show给用户的集合中。
        for(ctrindex = article.begin(); ctrindex != article.end();ctrindex++)
        {//首先从article中取出article:ctr,然后按照降序排列，用ctr_actileid存放。
            ctr_actileid.insert(make_pair(ctrindex->second,ctrindex->first));
        }

        index = ctr_actileid.begin();
        if(vec1[1] == (*index).second)//如果ctr最高的文章和show给用户的文章匹配。
        {
            map<string,int>::iterator index = match_count.find(vec1[1]);
            if(index == match_count.end())
                match_count.insert(make_pair(vec1[1],1));
            else match_count[vec1[1]]++;

            map<string,int>::iterator clickindex = click_count.find(vec1[1]);
            if(clickindex == click_count.end())
                click_count.insert(make_pair(vec1[1],num));
            else click_count[vec1[1]]+= num;

            double ctr = (double)click_count[vec1[1]]/match_count[vec1[1]];
            articlectr(vec1[1],ctr);
            click += num;
            t++;
        }
    }
}
void Mypolicy::epsilon_greedy(vector<string> &vec1, vector<string> &vec2, int num,int &click, int &t)
{
    int p = getrandom(100);
    if(p < 20)
    {
        //simpleploicy(vec1, vec2,num,click,t);
        randomploicy(vec1, vec2,num,click,t);
        //cout<<click<<" "<<t<<endl;
    }
    else
    {
        high_ctr_ploicy(vec1, vec2,num,click,t);
        //cout<<click<<" "<<t<<endl;
    }
}

