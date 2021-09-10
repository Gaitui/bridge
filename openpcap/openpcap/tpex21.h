#ifndef TPEX21_H
#define TPEX21_H

struct TPEX21{
    //Header
    Head head;

    //body
    u_char scode[7];
    u_char chname[45];
    u_char enname[45];
    double cprice;
    int otime;
    int ctime;
    int fcode;
    int check;
    int terminal[2];

};

TPEX21 decodeTPEX21(int h,u_char *pkt_data,Head head)
{
    TPEX21 temp;
    temp.head = head;
    h+=10;
    toArray(h,6,temp.scode,pkt_data);
    toArray(h,44,temp.chname,pkt_data);
    toArray(h,44,temp.enname,pkt_data);
    temp.cprice = todouble(h,4,3,pkt_data);
    temp.otime = BCDtoD(h,2,pkt_data);
    temp.ctime = BCDtoD(h,2,pkt_data);
    temp.fcode = BCDtoD(h,1,pkt_data);
    temp.check = toint(h,pkt_data);
    tointArray(h,2,temp.terminal,pkt_data);
    return temp;
}

void printTPEX21(FILE *fptr,TPEX21 tw)
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
    sprintf(tempbuffer,"%s,",tw.chname);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%s,",tw.enname);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%6.2f,",tw.cprice);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%04d,",tw.otime);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%04d,",tw.ctime);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%02d,",tw.fcode);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%02x,",tw.check);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%02x",tw.terminal[0]);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%02x,",tw.terminal[1]);
    strcat(outbuffer,tempbuffer);
    fprintf(fptr,"%s\n",outbuffer);
    return;
}

#endif // TPEX21_H