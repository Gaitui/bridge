#include <QCoreApplication>
#include <bits/stdc++.h>
#include <pthread.h>
#include <queue>

#include "read.cpp"
#include "run.cpp"

bool havefile = true;
std::queue<data> indata;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    pthread_t r1;
    pthread_t r2;

    pthread_create(&r1,NULL,read,NULL);
    pthread_create(&r2,NULL,run,NULL);

    pthread_join(r1,NULL);
    pthread_join(r2,NULL);

    printf("done\n");
    return a.exec();
}
