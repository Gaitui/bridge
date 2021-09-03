void format21(struct pcap_pkthdr *header,const u_char *pkt_data,FILE *fptr)
{
    for(int i=42;i<header->caplen;i++)
    {
        printf("%3d:%02x ",i-41,pkt_data[i]);
        if((i-41)%5==0)
            printf("\n");
    }
    cout<<endl;
    /**/

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

    //10IndexCode
    printf("Index Code");
    printchar(fptr,k,6,pkt_data);

    //16IndexChName
    printf("(%d)Index Chinese Name",k-42);
    printName(fptr,k,44,pkt_data);

    //60IndexENName
    printf("(%d)Index English Name",k-42);
    printchar(fptr,k,44,pkt_data);

    //104ClosePriceYesterday
    printf("(%d)Index English Name",k-42);
    printBCD(fptr,BCDMask(k,4,pkt_data));

    //108OpenTime
    printf("(%d)Open Time",k-42);
    printBCD(fptr,BCDMask(k,2,pkt_data));

    //110CloseTime
    printf("(%d)Close Time",k-42);
    printBCD(fptr,BCDMask(k,2,pkt_data));

    //112FormatCode
    printf("(%d)Close Time",k-42);
    printBCD(fptr,BCDMask(k,1,pkt_data));

    //113CheckCode
    printf("(%d)Check Code(Xor)",k-42);
    printhex(fptr,k,1,pkt_data);

    //114TerminalCode
    printf("(%d)Terminal Code",k-42);
    printhex(fptr,k,2,pkt_data);

    fprintf(fptr,"\n");
    printf("Len : %d\n",header->caplen-42);
    printf("\n");
}
