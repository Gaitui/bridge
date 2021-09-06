#include <pthread.h>
extern pthread_mutex_t mutex21;
void format21(struct pcap_pkthdr *header,const u_char *pkt_data,FILE *fptr)
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

    //10IndexCode
    printchar(k,6,pkt_data,outbuffer);

    //16IndexChName
    printName(k,44,pkt_data,outbuffer);

    //60IndexENName
    printchar(k,44,pkt_data,outbuffer);

    //104ClosePriceYesterday
    printBCD(BCDMask(k,4,pkt_data),outbuffer);

    //108OpenTime
    printBCD(BCDMask(k,2,pkt_data),outbuffer);

    //110CloseTime
    printBCD(BCDMask(k,2,pkt_data),outbuffer);

    //112FormatCode
    printBCD(BCDMask(k,1,pkt_data),outbuffer);

    //113CheckCode
    printhex(k,1,pkt_data,outbuffer);

    //114TerminalCode
    printhex(k,2,pkt_data,outbuffer);

    pthread_mutex_lock(&mutex21);
    fprintf(fptr,"%s\n",outbuffer);
    /*printf("buffer = %s\n",outbuffer);
    printf("Len : %d\n",header->caplen-42);
    printf("\n");*/
    pthread_mutex_unlock(&mutex21);
}
