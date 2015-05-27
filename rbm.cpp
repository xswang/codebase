#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <string>
#define User 943
#define Movies 1682
#define Hidnum 18
#define e 2.7182818
#define learningrate 0.1
using namespace std;

double v[User][Movies];
double transfv[Movies][User];
double virtualV[User][Movies];
double transfvirtualV[Movies][User];
double w[Movies][Hidnum];

double logistics(double x){
    return 1.0/(1+pow(e,x));
}

int InitialWandAsso(double w[][Hidnum]){
    for(int i = 0;i < Movies;i++)
        for(int j = 0;j < Hidnum;j++)
            w[i][j] = 0.0;
    return 0;
}

int InitialTrandfWandAsso(double w[][Hidnum],double tw[][Movies]){
    for(int i = 0;i < Hidnum;i++)
        for(int j = 0;j < Movies;j++)
            tw[i][j] = w[j][i];
    return 0;
}

int InitialV(double h[][Movies]){
    for(int i = 0;i < User;i++)
        for(int j = 0;j < Movies;j++)
            h[i][j] = 0.0;
    return 0;
}

int InitialTransfV(double v[][Movies],double transfV[][User]){
    for(int i = 0;i < Movies;i++)
        for(int j = 0;j < User;j++)
            transfV[i][j] = v[j][i];
    return 0;
}

int InitialHidden(double h[][Hidnum]){
    for(int i = 0;i < User;i++)
        for(int j = 0;j < Hidnum;j++)
            h[i][j] = 0.0;
    return 0;
}

int MultipleVWtoH(double v[][Movies],double w[][Hidnum],double h[][Hidnum]){
    for(int i = 0;i < User;i++)
        for(int j = 0;j < Hidnum;j++){
            double num = 0.0;
            for(int k = 0;k < Movies;k++)
                num += v[i][k]*w[k][j];
            h[i][j] = logistics(num);
        }
    return 0;
}

int multipleTVHtoASSociation(double tv[][User],double h[][Hidnum],double Asso[][Hidnum]){
    for(int i = 0;i < Movies;i++)
        for(int j = 0;j < Hidnum;j++){
            double num = 0.0;
            for(int k = 0;k < User;k++)
                num += tv[i][k]*h[k][j];
            Asso[i][j] = logistics(num);
        }
    return 0;
}

int MultipleHTWtoVirV(double h[][Hidnum],double tw[][Movies],double VirV[][Movies]){
    for(int i = 0;i < User;i++)
        for(int j = 0;j < Movies;j++){
            double num = 0.0;
            for(int k = 0;k < Hidnum;k++)
                num += h[i][k]*tw[k][j];
            VirV[i][j] = logistics(num);
        }
    return 0;
}

double gaussrand(){
    static double v1,v2,s;
    static int phase = 0;
    double x;
    if(phase == 0){
        do{
            double U1 = (double)rand()/RAND_MAX;
            double U2 = (double)rand()/RAND_MAX;
            v1 = 2*U1-1;
            v2 = 2*U2-1;
            s = v1*v1+v2*v2;
        }while(s >= 1 || s == 0);
        x = v1*sqrt(-2*log(s)/s);
    }else x = v2*sqrt(-2*log(s)/s);
    phase = 1 ¨C phase;
    return x;
}

int updateweights(double a[][Hidnum],double b[][Hidnum]){
    for(int i = 0;i < Movies;i++)
        for(int j = 0;j < Hidnum;j++)
            a[i][j] += b[i][j];
    return 0;
}

void train(int steps,double w[][Hidnum]){
    for(int epoch = 0;epoch < steps;epoch++){
        cout<<epoch<<endl;
        double hidden[User][Hidnum];
        InitialHidden(hidden);
        MultipleVWtoH(v,w,hidden);//
        double Associations1[Movies][Hidnum];
        InitialWandAsso(Associations1);

        InitialTransfV(v,transfv);//

        multipleTVHtoASSociation(transfv,hidden,Associations1);

        InitialV(virtualV);
        double Hidstates[User][Hidnum];
        InitialHidden(Hidstates);
        for(int i = 0;i < User;i++)
        for(int j = 0;j < Hidnum;j++){
            if( hidden[i][j] > (double)rand()/RAND_MAX )
                Hidstates[i][j] = 1.0;
            else Hidstates[i][j] = 0.0;
        }
        double transfw[Hidnum][Movies];
        InitialTrandfWandAsso(w,transfw);
        MultipleHTWtoVirV(Hidstates,transfw,virtualV);
//¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª
        double associations2[Movies][Hidnum];
        InitialWandAsso(associations2);
        MultipleVWtoH(virtualV,w,hidden);

        InitialTransfV(v,transfvirtualV);
        multipleTVHtoASSociation(transfvirtualV,hidden,associations2);
        double deltw[Movies][Hidnum];
        InitialWandAsso(deltw);
        for(int i = 0;i < Movies;i++)
            for(int j = 0;j < Hidnum;j++)
                deltw[i][j] = learningrate*( (Associations1[i][j] ¨C associations2[i][j])/(User*1.0) );
        updateweights(w,deltw);
        double error = 0;
        for(int i = 0;i < User;i++)
            for(int j = 0;j < Movies;j++){
                error += pow( (v[i][j] ¨C virtualV[i][j]),2);
            }
        cout<<"step "<<epoch<<" the error is "<<error/1586126.0<<endl;
    }

}

void probe(double w[][Hidnum]){
    double tw[Hidnum][Movies];
    InitialTrandfWandAsso(w,tw);

    double result[1][Movies];
    int road = 0;
    double p[1][18]={0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0};
    double nom[1][Movies];
    for(int i = 0;i < 1;i++)
    for(int j = 0;j < Movies;j++){
        nom[i][j] = (double)rand()/RAND_MAX;
        cout<<nom[i][j]<<" " ;
    }
    for(int i = 0;i < 1;i++)
        for(int j = 0;j < Movies;j++){
            double num = 0.0;
            for(int k = 0;k < 18;k++)
                num += p[i][k]*tw[k][j];
                if(logistics(num) > nom[i][j]){
                    result[i][j] = 1.0;
                    road++;
                cout<<j<<"->"<<result[i][j]<<"|| ";
                }
                else result[i][j] = 0.0;
        }
    cout<<"**********  "<<road<<"  *************"<<endl;
}

int main(){
    //double w[Movies][Hidnum];
    srand((unsigned)time(NULL));

    for(int i = 0;i < Movies;i++)
        for(int j = 0;j < Hidnum;j++)
             w[i][j] = 0.1*gaussrand();//
    InitialV(v);
    ifstream datafile("u.data",ios::app);
    int Uid = 0,Mid = 0,rate = 0;
    while (datafile>>Uid>>Mid>>rate)
        if(rate >= 3)v[Uid-1][Mid-1] = 1.0;
    train(30,w);
    probe(w);

    return 0;
}
