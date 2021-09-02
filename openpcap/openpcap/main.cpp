#include <QCoreApplication>
#include <iostream>
#include <QDebug>
#include <pcap.h>
#include <fstream>
#include "print.cpp"
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
    pcap_t *fin = pcap_open_offline("/root/20210823/p1p1.pcap", errbuf);
    if(!fin)
    {
        qDebug()<<"error : "<<errbuf;
    }
    else
    {
        qDebug()<<"Load file success";
        FILE *fptr = fopen("/root/20210823/p1p1.csv","w");
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
                for(int i=0;i<6;i++)
                {
                    printf("%d ",TH[i]);
                }
                printf("\n");
                if(TH[1]==114)
                {
                    int i=42;
                    for(;i<header->caplen;i++)
                    {
                        printf("%3d:%02x ",i-41,pkt_data[i]);
                        if((i-41)%5==0)
                            printf("\n");
                    }
                    cout<<endl;
                    /*cout<<i-42<<endl;
                    int seek = 0;*/
                    //TWSE_Header *data = (TWSE_Header*)(pkt_data + h + seek);
                    //qDebug()<<data->code;

                    int k=42;
                    //0Esc-Code
                    printf("Esc-code");
                    printdec(fptr,k,1,pkt_data);

                    //1MessageLen
                    printf("Message Length");
                    printhex(fptr,k,2,pkt_data);

                    //3MessageType
                    printf("Message Type");
                    printhex(fptr,k,1,pkt_data);

                    //4MessageCode
                    printf("Message Code");
                    printhex(fptr,k,1,pkt_data);

                    //5MessageVersion
                    printf("Message Version");
                    printhex(fptr,k,1,pkt_data);

                    //6MessageSeq
                    printf("Message Sequence Number");
                    printhex(fptr,k,4,pkt_data);

                    //10StockCode
                    printf("Stock Code");
                    printchar(fptr,k,6,pkt_data);

                    //16StockName
                    printf("Stock Name");
                    printName(fptr,k,16,pkt_data);

                    //32StockInd
                    printf("Stock Industry");
                    printchar(fptr,k,2,pkt_data);

                    //34StockType
                    printf("Stock Type");
                    printchar(fptr,k,2,pkt_data);

                    //36Stocktrans
                    printf("Stock Transaction");
                    printchar(fptr,k,2,pkt_data);

                    //38StockExecption
                    printf("Stock Exception");
                    printhex(fptr,k,1,pkt_data);

                    //39StockNote
                    printf("Stock Note");
                    printchar(fptr,k,1,pkt_data);

                    //40BoardNote
                    printf("Board Node");
                    printhex(fptr,k,1,pkt_data);

                    //41ReferencePrice
                    printf("Reference Price");
                    printBCD(fptr,k,5,pkt_data);

                    //46Limitup
                    printf("Limit Up");
                    printBCD(fptr,k,5,pkt_data);

                    //51DownLimit
                    printf("Down Limit");
                    printBCD(fptr,k,5,pkt_data);

                    //56TenDoller
                    printf("Not 10 TWD");
                    printchar(fptr,k,1,pkt_data);

                    //57RecommandExecption
                    printf("Recommand Exception");
                    printchar(fptr,k,1,pkt_data);

                    //58PriExecption
                    printf("Privileged Exception");
                    printchar(fptr,k,1,pkt_data);

                    //59Daytrade
                    printf("Daytrade");
                    printchar(fptr,k,1,pkt_data);

                    //60FlatSell
                    printf("Flat Sell");
                    printchar(fptr,k,1,pkt_data);

                    printf("%02x\n",pkt_data[k]);
                    if(pkt_data[k]!=0x00)
                        system("Pause");
                    /*//61FlatBarrow
                    printf("Flat Borrow");
                    printchar(fptr,k,1,pkt_data);


                    //62StockSec
                    printf("Stock Second");
                    printhex(fptr,k,3,pkt_data);*/


                    fprintf(fptr,"\n");
                    printf("Len : %d\n",header->caplen-42);
                    printf("\n");
                }
                w++;
                /*if(w>20)
                    break;*/
            }
        }
        fclose(fptr);
    }
    printf("Done\n");
    pcap_close(fin);
    return a.exec();
}
