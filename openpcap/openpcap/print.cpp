#include <iostream>
#include <QDebug>
#include <pcap.h>
#include <fstream>

using namespace std;

void printdec(FILE *fptr,int &k,int n,const u_char* pkt_data)
{
    printf(" : ");
    for(int i=0;i<n;i++)
    {
        fprintf(fptr,"%02d",pkt_data[i+k]);
        printf("%02d",pkt_data[i+k]);
    }
    fprintf(fptr,",");
    printf("\n");
    k+=n;
    return;
}

void printhex(FILE *fptr,int &k,int n,const u_char* pkt_data)
{
    printf(" : ");
    for(int i=0;i<n;i++)
    {
        fprintf(fptr,"%02x",pkt_data[i+k]);
        printf("%02x",pkt_data[i+k]);
    }
    fprintf(fptr,",");
    printf("\n");
    k+=n;
    return;
}

void printchar(FILE *fptr,int &k,int n,const u_char* pkt_data)
{
    printf(" : ");
    for(int i=0;i<n;i++)
    {
        fprintf(fptr,"%c",pkt_data[i+k]);
        if(pkt_data[i+k]==' ')
            printf("_");
        else
            printf("%c",pkt_data[i+k]);
    }
    fprintf(fptr,",");
    printf("\n");
    k+=n;
    return;
}

void printName(FILE *fptr,int &k,int n,const u_char* pkt_data)
{
    printf(" : ");
    char temp[100];
    for(int i=0;i<n;i++)
    {
        /*if(pkt_data[i+k] & 0x80)
        {
            /*
            char word[2];
            strcpy(word,(char*)pkt_data[i+k]);
            strcat(word,(char*)pkt_data[i+k+1]);
            fprintf(fptr,"__");
            printf("%s",word);
            i++;
                */
            /*wstring word;
            word+=pkt_data[i+k];
            word+=pkt_data[i+k+1];
            wcout<<word;*/
            /*printf("\'%d %d\'",pkt_data[i+k],pkt_data[i+k+1]);
            fprintf(fptr,"__");
            i++;
        }
        else
        {
            fprintf(fptr,"%c",pkt_data[i+k]);
            printf("\"%d\"",pkt_data[i+k]);
        }*/
        temp[i]=pkt_data[i+k];
    }
    temp[n]='\0';
    fprintf(fptr,"%s",temp);
    printf("%s",temp);
    fprintf(fptr,",");
    printf("\n");
    k+=n;
    return;
}


int BCDMask(int &k,int n,const u_char* pkt_data)
{
    printf(" : ");
    int d = 0;
    for(int i=0;i<n;i++)
    {
        d=d*100+(pkt_data[i+k]/16)*10+((pkt_data[i+k]%16));
    }
    k+=n;
    return d;
}

void printBCD
(FILE *fptr,int d)
{
    printf(" : %d\n",d);
    fprintf(fptr,"%d,",d);
    return;
}

void printFPF(FILE *fptr,int d)
{
    double f = (double)d/10000;
    printf("%5.4f\n",f);
    fprintf(fptr,"%5.4f,",f);
    return;
}

void printSPF(FILE *fptr,int d)
{
    double f = (double)d/10000;
    printf("%6.4f\n",f);
    fprintf(fptr,"%6.4f,",f);
    return;
}

