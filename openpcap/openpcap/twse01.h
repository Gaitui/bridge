#ifndef TWSE_ISBD_H
#define TWSE_ISBD_H

struct TWSE01{
    //Header
    Head head;

    //body
    u_char scode[7];
    u_char sname[17];
    u_char sind[3];
    u_char stype[3];
    u_char strans[3];
    int sexec;
    u_char bnote;
    double refprice;
    double limup;
    double limdown;
    u_char ten;
    u_char rexec;
    u_char pexec;
    u_char dtrade;
    u_char fsell;
    u_char fborrow;
    int ssec;
    u_char wcode;
    double sprice;
    long long lsnum;
    long long lwoff;
    long long obalance;
    double ppercent;
    double pupperb;
    double plowerb;
    int due;
    char foreign;
    int blot;
    u_char ccode[4];
    int minfo;
    int check;
    int terminal[2];

};

TWSE01 decodeTWSE01(int h,u_char *pkt_data,Head head)
{
    TWSE01 temp;
    temp.head = head;
    h+=10;
    toArray(h,6,temp.scode,pkt_data);
    toArray(h,16,temp.sname,pkt_data);
    toArray(h,2,temp.sind,pkt_data);
    toArray(h,2,temp.stype,pkt_data);
    toArray(h,2,temp.strans,pkt_data);
    temp.sexec = BCDtoD(h,1,pkt_data);
    temp.bnote = tochar(h,pkt_data);
    temp.refprice = todouble(h,5,3,pkt_data);
    temp.limup = todouble(h,5,3,pkt_data);
    temp.limdown = todouble(h,5,3,pkt_data);
    temp.ten = tochar(h,pkt_data);
    temp.rexec = tochar(h,pkt_data);
    temp.pexec = tochar(h,pkt_data);
    temp.dtrade = tochar(h,pkt_data);
    temp.fsell = tochar(h,pkt_data);
    temp.fborrow = tochar(h,pkt_data);
    temp.ssec = BCDtoD(h,3,pkt_data);
    temp.wcode = tochar(h,pkt_data);
    temp.sprice = todouble(h,5,3,pkt_data);
    temp.lsnum = BCDtoD(h,5,pkt_data);
    temp.lwoff = BCDtoD(h,5,pkt_data);
    temp.obalance = BCDtoD(h,5,pkt_data);
    temp.ppercent = todouble(h,4,3,pkt_data);
    temp.pupperb = todouble(h,5,3,pkt_data);
    temp.plowerb = todouble(h,5,3,pkt_data);
    temp.due = BCDtoD(h,4,pkt_data);
    temp.foreign = tochar(h,pkt_data);
    temp.blot = BCDtoD(h,3,pkt_data);
    toArray(h,3,temp.ccode,pkt_data);
    temp.minfo = BCDtoD(h,1,pkt_data);
    temp.check = toint(h,pkt_data);
    tointArray(h,2,temp.terminal,pkt_data);
    return temp;
}

void printTWSE01(FILE *fptr,TWSE01 tw)
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
    sprintf(tempbuffer,"%s,",tw.sname);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%s,",tw.sind);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%s,",tw.stype);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%s,",tw.strans);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%02d,",tw.sexec);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%c,",tw.bnote);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%5.4f,",tw.refprice);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%5.4f,",tw.limup);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%5.4f,",tw.limdown);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%c,",tw.ten);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%c,",tw.rexec);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%c,",tw.pexec);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%c,",tw.dtrade);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%c,",tw.fsell);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%c,",tw.fborrow);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%d,",tw.ssec);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%c,",tw.wcode);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%6.4f,",tw.sprice);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%lld,",tw.lsnum);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%lld,",tw.lwoff);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%lld,",tw.obalance);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%6.2f,",tw.ppercent);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%6.4f,",tw.pupperb);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%6.4f,",tw.plowerb);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%d,",tw.due);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%c,",tw.foreign);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%d,",tw.blot);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%s,",tw.ccode);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%02d,",tw.minfo);
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

#endif // TWSE_ISBD_H
