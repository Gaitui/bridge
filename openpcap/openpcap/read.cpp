#include <fstream>
#include <pthread.h>
#include <pcap.h>
#include <queue>

#include "data.h"
#include "head.h"
#include "trans.h"

extern bool havefile;
extern std::queue<data> indata;

static void* read(void* lp)
{
    int z=0;
    char oriroot[] = "/root/20210823/p1p1.pcap";
    char errbuf[PCAP_ERRBUF_SIZE];
    char root[60];
    char buffer[32];
    while(1)
    {
        strcpy(root,oriroot);
        if(z!=0)
        {
            sprintf(buffer,"%d",z);
            strcat(root,buffer);
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
            int port;
            int res;
            while(res = pcap_next_ex(fin,&header,&pkt_data) >=0)
            {
                port = (int)pkt_data[3];
                if(port!=0x02)
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
                                    //printf("%02d\n",dhead.mcode);
                                    data newdata;
                                    newdata.head = dhead;
                                    newdata.pkt_data = new u_char[dhead.mlen];
                                    for(int i=0;i<dhead.mlen;i++)
                                    {
                                        newdata.pkt_data[i]=pkt_data[h+i];
                                    }
                                    while(indata.size()>10);
                                    indata.push(newdata);
                                    h+=dhead.mlen-1;
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
