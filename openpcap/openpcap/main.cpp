#include <QCoreApplication>
#include <bits/stdc++.h>
#include <pthread.h>
#include <queue>
#include <time.h>

#include "read.cpp"
#include "run.cpp"

char opath[] = "/root/20210823/p1p1";

bool havefile = true;
std::queue<data> q01;
std::queue<data> q06;
std::queue<data> q21;
std::queue<data> q22;
std::queue<data> q23;

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
    printf("Done time : %.2f\n",difftime(stop,start));
    return a.exec();
}
