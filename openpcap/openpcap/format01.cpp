void format01(struct pcap_pkthdr *header,const u_char *pkt_data,FILE *fptr)
{
    /*for(int i=42;i<header->caplen;i++)
    {
        printf("%3d:%02x ",i-41,pkt_data[i]);
        if((i-41)%5==0)
            printf("\n");
    }
    cout<<endl;
    */

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

    //32StockInd
    printf("(%d)Stock Industry",k-42);
    printchar(fptr,k,2,pkt_data);

    //34StockType
    printf("(%d)Stock Type",k-42);
    printchar(fptr,k,2,pkt_data);

    //36Stocktrans
    printf("(%d)Stock Transaction",k-42);
    printchar(fptr,k,2,pkt_data);

    //38StockExecption
    printf("(%d)Stock Exception",k-42);
    printhex(fptr,k,1,pkt_data);


    //39BoardNote
    printf("(%d)Board Node",k-42);
    //printhex(fptr,k,1,pkt_data);
    printchar(fptr,k,1,pkt_data);

    //40ReferencePrice
    printf("(%d)Reference Price",k-42);
    printFPF(fptr,BCDMask(k,5,pkt_data));

    //45Limitup
    printf("(%d)Limit Up",k-42);
    printFPF(fptr,BCDMask(k,5,pkt_data));

    //50DownLimit
    printf("(%d)Down Limit",k-42);
    printFPF(fptr,BCDMask(k,5,pkt_data));

    //55TenDoller
    printf("(%d)Not 10 TWD",k-42);
    printchar(fptr,k,1,pkt_data);

    //56RecommandExecption
    printf("(%d)Recommand Exception",k-42);
    printchar(fptr,k,1,pkt_data);

    //57PriExecption
    printf("(%d)Privileged Exception",k-42);
    printchar(fptr,k,1,pkt_data);

    //58Daytrade
    printf("(%d)Daytrade",k-42);
    printchar(fptr,k,1,pkt_data);

    //59FlatSell
    printf("(%d)Flat Sell",k-42);
    printchar(fptr,k,1,pkt_data);

    //60FlatBarrow
    printf("(%d)Flat Borrow",k-42);
    printchar(fptr,k,1,pkt_data);

    //61StockSec
    printf("(%d)Stock Second",k-42);
    printBCD(fptr,BCDMask(k,3,pkt_data));

    //64WarrantCode
    printf("(%d)Warrant Code",k-42);
    printchar(fptr,k,1,pkt_data);

    //65StrikePrice
    printf("(%d)Strike Price",k-42);
    printSPF(fptr,BCDMask(k,5,pkt_data));

    //70LastStrikeNum
    printf("(%d)Last Strike Num",k-42);
    printBCD(fptr,BCDMask(k,5,pkt_data));

    //75LastWriteOff
    printf("(%d)Last Write Off",k-42);
    printBCD(fptr,BCDMask(k,5,pkt_data));

    //80OpenBalance
    printf("(%d)Open Balance",k-42);
    printBCD(fptr,BCDMask(k,5,pkt_data));

    //85PerformPercent
    printf("(%d)Perform Percent",k-42);
    printBCD(fptr,BCDMask(k,4,pkt_data));

    //89PriceUpperBound
    printf("(%d)Price Upper Bound",k-42);
    printSPF(fptr,BCDMask(k,5,pkt_data));

    //94PriceLowerBound
    printf("(%d)Price Lower Bound",k-42);
    printSPF(fptr,BCDMask(k,5,pkt_data));

    //99DateDue
    printf("(%d)Date Due",k-42);
    printBCD(fptr,BCDMask(k,4,pkt_data));

    //103ForeignStock
    printf("(%d)ForeignStock",k-42);
    printchar(fptr,k,1,pkt_data);

    //104BoardLot
    printf("(%d)BoardLot",k-42);
    printBCD(fptr,BCDMask(k,3,pkt_data));

    //107CurrencyCode
    printf("(%d)Currency Code",k-42);
    printchar(fptr,k,3,pkt_data);

    //110MarketInfo
    printf("(%d)Market Information",k-42);
    printhex(fptr,k,1,pkt_data);

    //111CheckCode
    printf("(%d)Check Code(Xor)",k-42);
    printhex(fptr,k,1,pkt_data);

    //112TerminalCode
    printf("(%d)Terminal Code",k-42);
    printhex(fptr,k,2,pkt_data);

    fprintf(fptr,"\n");
    printf("Len : %d\n",header->caplen-42);
    printf("\n");
}
