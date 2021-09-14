#ifndef TPEX22_H
#define TPEX22_H
#include <vector>

struct TPEX22{
    //Header
    Head head;

    //body
    u_char scode[7];
    u_char sname[17];
    u_char strans[3];
    int sexec;
    double refprice;
    double limup;
    double limdown;
    u_char dtrade;
    int ssec;
    int blot;
    int check;
    int terminal[2];

};

TPEX22 decodeTPEX22(int h,u_char *pkt_data,Head head)
{
    TPEX22 temp;
    temp.head = head;
    h+=10;
    toArray(h,6,temp.scode,pkt_data);
    toArray(h,16,temp.sname,pkt_data);
    toArray(h,2,temp.strans,pkt_data);
    temp.sexec = BCDtoD(h,1,pkt_data);
    temp.refprice = todouble(h,5,3,pkt_data);
    temp.limup = todouble(h,5,3,pkt_data);
    temp.limdown = todouble(h,5,3,pkt_data);
    temp.dtrade = tochar(h,pkt_data);
    temp.ssec = BCDtoD(h,3,pkt_data);
    temp.blot = BCDtoD(h,3,pkt_data);
    temp.check = toint(h,pkt_data);
    tointArray(h,2,temp.terminal,pkt_data);
    return temp;
}

void printTPEX22(FILE *fptr,TPEX22 tw,std::vector<int> address,int port)
{
    char outbuffer[500]="";
    char tempbuffer[50];

    for(int i=0;i<address.size();i++)
    {
        sprintf(tempbuffer,"%d,",address[i]);
        strcat(outbuffer,tempbuffer);
    }
    sprintf(tempbuffer,"%d,",port);
    strcat(outbuffer,tempbuffer);

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
    sprintf(tempbuffer,"%s,",tw.strans);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%02d,",tw.sexec);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%5.4f,",tw.refprice);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%5.4f,",tw.limup);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%5.4f,",tw.limdown);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%c,",tw.dtrade);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%d,",tw.ssec);
    strcat(outbuffer,tempbuffer);
    sprintf(tempbuffer,"%d,",tw.blot);
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


#endif // TPEX22_H
