#include <pthread.h>
extern pthread_mutex_t mutex06;
void format06(struct pcap_pkthdr *header,const u_char *pkt_data,FILE *fptr,int len)
{

    int k=42;
    char outbuffer[500]="";

    //0Esc-Code
    printdec(k,1,pkt_data,outbuffer);

    //1MessageLen
    printhex(k,2,pkt_data,outbuffer);

    //3MessageType
    printhex(k,1,pkt_data,outbuffer);

    //4MessageCode
    printhex(k,1,pkt_data,outbuffer);

    //5MessageVersion
    printhex(k,1,pkt_data,outbuffer);

    //6MessageSeq
    printhex(k,4,pkt_data,outbuffer);

    //10StockCode
    printchar(k,6,pkt_data,outbuffer);

    //16MatchTime
    printhex(k,6,pkt_data,outbuffer);

    //22Reveal
    printbin(k,1,pkt_data,outbuffer);

    //23Limitup
    printbin(k,1,pkt_data,outbuffer);

    //24State
    printbin(k,1,pkt_data,outbuffer);

    //25TransactNum
    printBCD(BCDMask(k,4,pkt_data),outbuffer);


    //29Realtime
    int ti = (len - 3 - 29)/9;

    //printf("(%d - 32)/9 = %d\n",len,ti);
    for(int i=0;i<ti;i++)
    {
        printFPF(BCDMask(k,5,pkt_data),outbuffer);
        printBCD(BCDMask(k,4,pkt_data),outbuffer);
    }

    //CheckCode
    printhex(k,1,pkt_data,outbuffer);

    //TerminalCode
    printhex(k,2,pkt_data,outbuffer);


    /*

    //94PriceLowerBound
    printSPF(BCDMask(k,5,pkt_data),outbuffer);

    //99DateDue
    printBCD(BCDMask(k,4,pkt_data),outbuffer);

    //103ForeignStock
    printchar(k,1,pkt_data,outbuffer);

    //104BoardLot
    printBCD(BCDMask(k,3,pkt_data),outbuffer);

    //107CurrencyCode
    printchar(k,3,pkt_data,outbuffer);

    //110MarketInfo
    printhex(k,1,pkt_data,outbuffer);

    */

    pthread_mutex_lock(&mutex06);
    fprintf(fptr,"%s\n",outbuffer);
    /*printf("buffer = %s\n",outbuffer);
    printf("Len : %d\n",header->caplen-42);
    printf("\n");*/
    pthread_mutex_unlock(&mutex06);
}

