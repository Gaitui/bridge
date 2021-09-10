#ifndef HEAD_H
#define HEAD_H
#include "trans.h"

struct Head{
    int esc;
    int mlen;
    int mtype;
    int mcode;
    int mver;
    int mseq;
};

Head decodeHead(u_char* pkt_data,int h)
{
    Head dhead;

    dhead.esc=pkt_data[h];
    h++;

    dhead.mlen=BCDtoD(h,2,pkt_data);

    dhead.mtype=BCDtoD(h,1,pkt_data);

    dhead.mcode=BCDtoD(h,1,pkt_data);

    dhead.mver=BCDtoD(h,1,pkt_data);

    dhead.mseq = BCDtoD(h,4,pkt_data);

    return dhead;
}

#endif // HEAD_H

