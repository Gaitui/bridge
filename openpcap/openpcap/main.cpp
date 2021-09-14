#include <QCoreApplication>
#include <bits/stdc++.h>
#include <pthread.h>
#include <queue>
#include <vector>
#include <time.h>

#include "read.cpp"
#include "run.cpp"

char opath[] = "/root/20210823/p1p2";

bool havefile = true;
std::queue<data> q01;
std::queue<data> q06;
std::queue<data> q21;
std::queue<data> q22;
std::queue<data> q23;

std::vector<int> tw06info;
std::vector<int> tp06info;

bool TP01=false;
bool TP06=false;
bool TP21=false;
bool TP22=false;
bool TP23=false;
bool TW01=false;
bool TW06=false;
bool TW21=false;
bool TW22=false;
bool TW23=false;

int main(int argc, char *argv[])
{
    time_t start,stop;
    start=time(NULL);
    QCoreApplication a(argc, argv);

    pthread_t fr;
    pthread_t f01;
    pthread_t f06;
    pthread_t f21;
    pthread_t f22;
    pthread_t f23;

    pthread_create(&fr,NULL,fread,NULL);
    pthread_create(&f01,NULL,format01,NULL);
    pthread_create(&f06,NULL,format06,NULL);
    pthread_create(&f21,NULL,format21,NULL);
    pthread_create(&f22,NULL,format22,NULL);
    pthread_create(&f23,NULL,format23,NULL);

    pthread_join(fr,NULL);
    pthread_join(f01,NULL);
    pthread_join(f06,NULL);
    pthread_join(f21,NULL);
    pthread_join(f22,NULL);
    pthread_join(f23,NULL);


    stop=time(NULL);
    if(tw06info.size()!=0)
    {
        printf("TWSE06 Start : %d ,End : %d, Lost : ",tw06info[0],tw06info[tw06info.size()-1]);
        for(int i=1;i<tw06info.size()-1;i++)
        {
            printf("%d, ",tw06info[i]);
        }
        printf("\n");
    }
    if(tp06info.size()!=0)
    {
        printf("TPEx06 Start : %d ,End : %d, Lost : ",tp06info[0],tp06info[tp06info.size()-1]);
        for(int i=1;i<tp06info.size()-1;i++)
        {
            printf("%d, ",tp06info[i]);
        }
        printf("\n");
    }
    printf("Done time : %.2f\n",difftime(stop,start));
    return a.exec();
}
