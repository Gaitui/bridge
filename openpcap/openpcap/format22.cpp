#include <pthread.h>
extern pthread_mutex_t mutex22;
void format22(struct pcap_pkthdr *header,const u_char *pkt_data,FILE *fptr)
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

    //16StockName
    printName(k,16,pkt_data,outbuffer);

    //32Stocktrans
    printchar(k,2,pkt_data,outbuffer);

    //34StockExecption
    printhex(k,1,pkt_data,outbuffer);


    //35ReferencePrice
    printFPF(BCDMask(k,5,pkt_data),outbuffer);

    //40Limitup
    printFPF(BCDMask(k,5,pkt_data),outbuffer);

    //45DownLimit
    printFPF(BCDMask(k,5,pkt_data),outbuffer);

    //50Daytrade
    printchar(k,1,pkt_data,outbuffer);

    //51StockSec
    printBCD(BCDMask(k,3,pkt_data),outbuffer);

    //54BoardLot
    printBCD(BCDMask(k,3,pkt_data),outbuffer);

    //57CheckCode
    printhex(k,1,pkt_data,outbuffer);

    //58TerminalCode
    printhex(k,2,pkt_data,outbuffer);

    pthread_mutex_lock(&mutex22);
    fprintf(fptr,"%s\n",outbuffer);
    /*printf("buffer = %s\n",outbuffer);
    printf("Len : %d\n",header->caplen-42);
    printf("\n");*/
    pthread_mutex_unlock(&mutex22);
}
