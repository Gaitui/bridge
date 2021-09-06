#include <iostream>
#include <QDebug>
#include <pcap.h>
#include <fstream>

using namespace std;

void printdec(int &k,int n,const u_char* pkt_data,char *outbuffer)
{
    char tempbuffer[10];
    for(int i=0;i<n;i++)
    {
        sprintf(tempbuffer,"%02d",pkt_data[i+k]);
        strcat(outbuffer,tempbuffer);
    }
    strcat(outbuffer,",");
    k+=n;
    return;
}

void printhex(int &k,int n,const u_char* pkt_data,char *outbuffer)
{
    char tempbuffer[10];
    for(int i=0;i<n;i++)
    {
        sprintf(tempbuffer,"%02x",pkt_data[i+k]);
        strcat(outbuffer,tempbuffer);
    }
    strcat(outbuffer,",");
    k+=n;
    return;
}

void printchar(int &k,int n,const u_char* pkt_data,char *outbuffer)
{
    char tempbuffer[10];
    for(int i=0;i<n;i++)
    {
        sprintf(tempbuffer,"%c",pkt_data[i+k]);
        strcat(outbuffer,tempbuffer);
    }
    strcat(outbuffer,",");
    k+=n;
    return;
}

void printName(int &k,int n,const u_char* pkt_data,char *outbuffer)
{

    char temp[100];
    char tempbuffer[100];
    for(int i=0;i<n;i++)
    {
        temp[i]=pkt_data[i+k];
    }
    temp[n]='\0';
    sprintf(tempbuffer,"%s",temp);
    strcat(outbuffer,tempbuffer);
    strcat(outbuffer,",");
    k+=n;
    return;
}


int BCDMask(int &k,int n,const u_char* pkt_data)
{
    int d = 0;
    for(int i=0;i<n;i++)
    {
        d=d*100+(pkt_data[i+k]/16)*10+((pkt_data[i+k]%16));
    }
    k+=n;
    return d;
}

void printBCD(int d,char *outbuffer)
{
    char temp[100];
    sprintf(temp,"%d,",d);
    strcat(outbuffer,temp);
    return;
}

void printFPF(int d,char *outbuffer)
{
    double f = (double)d/10000;
    char temp[100];
    sprintf(temp,"%5.4f,",f);
    strcat(outbuffer,temp);
    return;
}

void printSPF(int d,char *outbuffer)
{
    double f = (double)d/10000;
    char temp[100];
    sprintf(temp,"%6.4f,",f);
    strcat(outbuffer,temp);
    return;
}
