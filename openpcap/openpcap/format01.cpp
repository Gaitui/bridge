#include <pthread.h>
extern pthread_mutex_t mutex01;
void format01(struct pcap_pkthdr *header,const u_char *pkt_data,FILE *fptr)
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

    //32StockInd
    printchar(k,2,pkt_data,outbuffer);

    //34StockType
    printchar(k,2,pkt_data,outbuffer);

    //36Stocktrans
    printchar(k,2,pkt_data,outbuffer);

    //38StockExecption
    printhex(k,1,pkt_data,outbuffer);

    //39BoardNote
    printchar(k,1,pkt_data,outbuffer);

    //40ReferencePrice
    printFPF(BCDMask(k,5,pkt_data),outbuffer);

    //45Limitup
    printFPF(BCDMask(k,5,pkt_data),outbuffer);

    //50DownLimit
    printFPF(BCDMask(k,5,pkt_data),outbuffer);

    //55TenDoller
    printchar(k,1,pkt_data,outbuffer);

    //56RecommandExecption
    printchar(k,1,pkt_data,outbuffer);

    //57PriExecption
    printchar(k,1,pkt_data,outbuffer);

    //58Daytrade
    printchar(k,1,pkt_data,outbuffer);

    //59FlatSell
    printchar(k,1,pkt_data,outbuffer);

    //60FlatBarrow
    printchar(k,1,pkt_data,outbuffer);

    //61StockSec
    printBCD(BCDMask(k,3,pkt_data),outbuffer);

    //64WarrantCode
    printchar(k,1,pkt_data,outbuffer);

    //65StrikePrice
    printSPF(BCDMask(k,5,pkt_data),outbuffer);

    //70LastStrikeNum
    printBCD(BCDMask(k,5,pkt_data),outbuffer);

    //75LastWriteOff
    printBCD(BCDMask(k,5,pkt_data),outbuffer);

    //80OpenBalance
    printBCD(BCDMask(k,5,pkt_data),outbuffer);

    //85PerformPercent
    printBCD(BCDMask(k,4,pkt_data),outbuffer);

    //89PriceUpperBound
    printSPF(BCDMask(k,5,pkt_data),outbuffer);

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

    //111CheckCode
    printhex(k,1,pkt_data,outbuffer);

    //112TerminalCode
    printhex(k,2,pkt_data,outbuffer);

    pthread_mutex_lock(&mutex01);
    fprintf(fptr,"%s\n",outbuffer);
    /*printf("buffer = %s\n",outbuffer);
    printf("Len : %d\n",header->caplen-42);
    printf("\n");*/
    pthread_mutex_unlock(&mutex01);
}

