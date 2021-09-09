#include "head.h"

static Head decodeHead(const u_char* pkt_data)
{
    Head dhead;
    int h=42;
    int d=0;

    dhead.esc=pkt_data[h];
    h++;

    for(int i=0;i<2;i++)
    {
        d=d*100+(pkt_data[h+i]>>4)*10+(pkt_data[h+i] & 0x0f);
    }
    dhead.mlen=d;
    h+=2;

    d=(pkt_data[h]>>4)*10+(pkt_data[h] & 0x0f);
    dhead.mtype=d;
    h++;

    d=(pkt_data[h]>>4)*10+(pkt_data[h] & 0x0f);
    dhead.mcode=d;
    h++;

    d=(pkt_data[h]>>4)*10+(pkt_data[h] & 0x0f);
    dhead.mver=d;
    h++;

    long long n=0;

    for(int i=0;i<4;i++)
    {
        n=n*100+(pkt_data[h+i]>>4)*10+(pkt_data[h+i] & 0x0f);
    }
    dhead.mseq = n;
    return dhead;
}
