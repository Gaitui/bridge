#include <fstream>
#include <pthread.h>
#include <pcap.h>
#include <queue>

#include "data.h"
#include "head.h"
#include "trans.h"

extern char opath[];

extern bool havefile;
extern std::queue<data> q01;
extern std::queue<data> q06;
extern std::queue<data> q21;
extern std::queue<data> q22;
extern std::queue<data> q23;

static void* fread(void* lp)
{
    int z=0;
    char errbuf[PCAP_ERRBUF_SIZE];
    char root[60]="";
    while(1)
    {
        if(z!=0)
        {
            sprintf(root,"%s.pcap%d",opath,z);
        }
        else
        {
            sprintf(root,"%s.pcap",opath);
        }
        pcap_t *fin = pcap_open_offline(root,errbuf);
        if(!fin)
        {
            printf("%s not exist\n",root);
            havefile = false;
            break;
        }
        else
        {
            printf("Load %s success\n",root);
            z++;
            struct pcap_pkthdr *header;
            const u_char *pkt_data;
            int addressbyte;
            //int port;
            int res;
            while(res = pcap_next_ex(fin,&header,&pkt_data) >=0)
            {
                addressbyte = (int)pkt_data[31];
                if(addressbyte!=0x02)
                {
                    int h=0;
                    int len = (int)header->caplen;
                    while(h<len)
                    {
                        if(pkt_data[h]==27)
                        {
                            if(h+10<=len)
                            {
                                Head dhead = decodeHead((u_char*)pkt_data,h);
                                //printf("%02d\n",dhead.mlen);
                                if(h+dhead.mlen<=len && pkt_data[h+dhead.mlen-2]==0x0d && pkt_data[h+dhead.mlen-1]==0x0a)
                                {
                                    //port = (pkt_data[36]<<8)+pkt_data[37];
                                    //printf("%d\n",port);
                                    data newdata;
                                    newdata.port=(pkt_data[36]<<8)+pkt_data[37];
                                    for(int i=30;i<34;i++)
                                    {
                                        newdata.address.push_back(pkt_data[i]);
                                    }
                                    newdata.head = dhead;
                                    newdata.pkt_data = new u_char[dhead.mlen];
                                    for(int i=0;i<dhead.mlen;i++)
                                    {
                                        newdata.pkt_data[i]=pkt_data[h+i];
                                    }
                                    while(q01.size()+q06.size()+q21.size()+q22.size()+q23.size()>5);
                                    if(dhead.mcode == 1 && addressbyte == 0x00)
                                    {
                                        //printf("%02d\n",addressbyte);
                                        q01.push(newdata);
                                    }
                                    else if(dhead.mcode == 6 && addressbyte == 0x00)
                                    {
                                        q06.push(newdata);
                                    }
                                    else if(dhead.mcode == 21 && addressbyte == 0x06)
                                    {
                                        q21.push(newdata);
                                    }
                                    else if(dhead.mcode == 22 && addressbyte == 0x08)
                                    {
                                        q22.push(newdata);
                                    }
                                    else if(dhead.mcode == 23 && addressbyte == 0x08)
                                    {
                                        q23.push(newdata);
                                    }
                                    //h+=dhead.mlen-1;
                                }

                            }
                        }
                        h++;
                    }
                }
            }
            pcap_close(fin);
        }
    }
    pthread_exit(NULL);
}
