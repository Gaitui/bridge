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
}

void printName(FILE *fptr,int &k,int n,const u_char* pkt_data)
{
    printf(" : ");
    for(int i=0;i<n;i++)
    {
        if(pkt_data[i+k] & 0x80)
        {
            wstring word;
            word+=pkt_data[i+k];
            word+=pkt_data[i+k+1];
            wcout<<word;
            //cout<<pkt_data[i+k]<<pkt_data[i+k+1];
            /*setlocale(LC_CTYPE,"zh_TW.UTF-8");
            const char *word = new char[2];
            word[0]=pkt_data[i+k];
            word[1]=pkt_data[i+k]+1;
            int wsize = strlen(word)+1;
            wchar_t *wword = new wchar_t[wsize];
            int ret = mbsrtowcs(wword,word,wsize);
            cout<<wword[0];*/
            //fwprintf(fptr,L"%s",word.c_str());
            fprintf(fptr,"__");
            i++;
        }
        else
        {
            fprintf(fptr,"%c",pkt_data[i+k]);
            printf("%c",pkt_data[i+k]);
        }

    }
    fprintf(fptr,",");
    printf("\n");
    k+=n;
}
void printBCD(FILE *fptr,int &k,int n,const u_char* pkt_data)
{
    printf(" : ");
    int d = 0;
    for(int i=0;i<n;i++)
    {
        //fprintf(fptr,"%02x",pkt_data[i+k]);
        d=d*100+(pkt_data[i+k]/16)*10+((pkt_data[i+k]%16));
        //printf("%02x",pkt_data[i+k]);
    }
    //printf("\n");
    /*double f = (double)d/1000;
    printf("float Num : %6.3f\n",f);
    fprintf(fptr,"%6.3f,",f);*/
    printf("%d\n",d);
    fprintf(fptr,"%d,",d);
    k+=n;
}
