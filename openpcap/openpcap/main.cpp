#include <QCoreApplication>
#include <iostream>
#include <QDebug>
#include <pcap.h>
#include <fstream>
#include "print.cpp"
#include "format01.cpp"
#include "format21.cpp"
#include "format22.cpp"

using namespace std;
void Head(int *th,const u_char* pkt_data)
{
    int h=42;
    int d=0;
    int n=0;

    th[n]=pkt_data[h];
    h++;
    n++;

    for(int i=0;i<2;i++)
    {
        d=d*100+(pkt_data[h+i]/16)*10+pkt_data[h+i]%16;
    }
    th[n]=d;
    d=0;
    h+=2;
    n++;

    for(int i=0;i<3;i++)
    {
        th[n+i]=(pkt_data[h+i]/16)*10+pkt_data[h+i]%16;
    }
    h+=3;
    n+=3;

    for(int i=0;i<4;i++)
    {
        d=d*100+(pkt_data[h+i]/16)*10+pkt_data[h+i]%16;
    }
    th[n]=d;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    char errbuf[PCAP_ERRBUF_SIZE];
    qDebug()<<"Hi";
    int x=1,y=1,z=0;
    char oriroot[] = "/root/20210823/p";
    char buffer[32];
    char root[60];
    FILE *fptr01 = fopen("/root/20210823/Format01.csv","w");
    FILE *fptr21 = fopen("/root/20210823/Format21.csv","w");
    FILE *fptr22 = fopen("/root/20210823/Format22.csv","w");
    while(x<=3)
    {
        strcpy(root,oriroot);
        sprintf(buffer,"%d",x);
        strcat(root,buffer);
        strcat(root,"p");
        sprintf(buffer,"%d",y);
        strcat(root,buffer);
        strcat(root,".pcap");
        if(z!=0)
        {
            sprintf(buffer,"%d",z);
            strcat(root,buffer);
        }
        pcap_t *fin = pcap_open_offline( root, errbuf);
        if(!fin)
        {
            printf("%s not exist\n",root);
            z=0;
            if(x==1 && y==2)
            {
                x=3;
                y=1;
            }
            else if(y==1)
            {
                y++;
            }
            else
            {
                break;
            }
        }
        else
        {
            printf("Load %s success\n",root);

            z++;

            struct pcap_pkthdr *header;
            const u_char *pkt_data;
            int res;
            int w=0;
            while(res = pcap_next_ex(fin,&header,&pkt_data) >=0)
            {
                int h = 42;
                if(pkt_data[h]==27)
                {
                    int TH[6]; //TWSE_HEADER
                    Head(TH,pkt_data);
                    /*for(int i=0;i<6;i++)
                    {
                        printf("%d ",TH[i]);
                    }
                    printf("\n");*/
                    if(TH[1]==114 && TH[3]==1)
                    {
                        format01(header,pkt_data,fptr01);
                    }
                    else if(TH[1]==116 &&TH[3]==21)
                    {
                        format21(header,pkt_data,fptr21);
                    }
                    else if(TH[1]==60 &&TH[3]==22)
                    {
                        format22(header,pkt_data,fptr22);
                    }
                    w++;
                    /*if(w>500)
                        break;*/
                }
            }
            pcap_close(fin);
        }
    }
    fclose(fptr01);
    fclose(fptr21);
    fclose(fptr22);
    printf("Done\n");
    return a.exec();
}
