#ifndef TPEX23_H
#define TPEX23_H

struct TPEX23{
    //Header
    Head head;

    //body
    u_char scode[7];
    long long mtime;
    int reveal;
    int limark;
    int state;
    long long tnum;
    std::vector<double> rprice;
    std::vector<long long> rnum;
    int check;
    int terminal[2];

};

TPEX23 decodeTPEX23(int h,u_char *pkt_data,Head head)
{
    TPEX23 temp;
    temp.head = head;
    int len = head.mlen+h;
    h+=10;
    toArray(h,6,temp.scode,pkt_data);
    temp.mtime = BCDtoD(h,6,pkt_data);
    temp.reveal = tobin(h,pkt_data);
    temp.limark = tobin(h,pkt_data);
    temp.state = tobin(h,pkt_data);
    temp.tnum = BCDtoD(h,6,pkt_data);

    while(h<len-3)
    {
        temp.rprice.push_back(todouble(h,5,3,pkt_data));
        temp.rnum.push_back(BCDtoD(h,6,pkt_data));
    }

    temp.check = toint(h,pkt_data);
    tointArray(h,2,temp.terminal,pkt_data);
    return temp;
}

void printTPEX23(FILE *fptr,TPEX23 tw)
{
    char outbuffer[500]="";
    char tempbuffer[50];

    //head
    sprintf(tempbuffer,"%02d,",tw.head.esc);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%04d,",tw.head.mlen);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%02d,",tw.head.mtype);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%02d,",tw.head.mcode);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%02d,",tw.head.mver);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%08d,",tw.head.mseq);
    strcat(outbuffer,tempbuffer);

    //body
    sprintf(tempbuffer,"%s,",tw.scode);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%012lld,",tw.mtime);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%08d,",tw.reveal);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%08d,",tw.limark);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%08d,",tw.state);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%lld,",tw.tnum);
    strcat(outbuffer,tempbuffer);

    for(int i=0;i<tw.rprice.size();i++)
    {
        sprintf(tempbuffer,"%5.4f,",tw.rprice[i]);
        strcat(outbuffer,tempbuffer);
        sprintf(tempbuffer,"%lld,",tw.rnum[i]);
        strcat(outbuffer,tempbuffer);
    }

    sprintf(tempbuffer,"%02x,",tw.check);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%02x",tw.terminal[0]);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%02x,",tw.terminal[1]);
    strcat(outbuffer,tempbuffer);
    fprintf(fptr,"%s\n",outbuffer);
    return;
}


#endif // TPEX23_H
