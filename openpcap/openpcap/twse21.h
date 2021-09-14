#ifndef TWSE21_H
#define TWSE21_H
#include <vector>

struct TWSE21{
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

TWSE21 decodeTWSE21(int h,u_char *pkt_data,Head head)
{
    TWSE21 temp;
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

void printTWSE21(FILE *fptr,TWSE21 tw,std::vector<int> address,int port)
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


#endif // TWSE21_H
