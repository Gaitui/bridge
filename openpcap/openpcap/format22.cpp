void format22(struct pcap_pkthdr *header,const u_char *pkt_data,FILE *fptr)
{
    /*for(int i=42;i<header->caplen;i++)
    {
        printf("%3d:%02x ",i-41,pkt_data[i]);
        if((i-41)%5==0)
            printf("\n");
    }
    cout<<endl;*/


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
    printf("(%d)Stock Name",k-42);
    printName(fptr,k,16,pkt_data);

    //32Stocktrans
    printf("(%d)Stock Transaction",k-42);
    printchar(fptr,k,2,pkt_data);

    //34StockExecption
    printf("(%d)Stock Exception",k-42);
    printhex(fptr,k,1,pkt_data);


    //35ReferencePrice
    printf("(%d)Reference Price",k-42);
    printFPF(fptr,BCDMask(k,5,pkt_data));

    //40Limitup
    printf("(%d)Limit Up",k-42);
    printFPF(fptr,BCDMask(k,5,pkt_data));

    //45DownLimit
    printf("(%d)Down Limit",k-42);
    printFPF(fptr,BCDMask(k,5,pkt_data));

    //50Daytrade
    printf("(%d)Daytrade",k-42);
    printchar(fptr,k,1,pkt_data);

    //51StockSec
    printf("(%d)Stock Second",k-42);
    printBCD(fptr,BCDMask(k,3,pkt_data));

    //54BoardLot
    printf("(%d)BoardLot",k-42);
    printBCD(fptr,BCDMask(k,3,pkt_data));

    //57CheckCode
    printf("(%d)Check Code(Xor)",k-42);
    printhex(fptr,k,1,pkt_data);

    //58TerminalCode
    printf("(%d)Terminal Code",k-42);
    printhex(fptr,k,2,pkt_data);

    fprintf(fptr,"\n");
    printf("Len : %d\n",header->caplen-42);
    printf("\n");
}
