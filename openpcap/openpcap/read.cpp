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
    char oriroot[] = "/root/20210823/p1p2.pcap";
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
            int res;
            while(res = pcap_next_ex(fin,&header,&pkt_data) >=0)
            {
                data newdata;
                newdata.len = (int)header->caplen;
                newdata.pkt_data = new u_char[newdata.len];
                for(int i=0;i<newdata.len;i++)
                {
                    newdata.pkt_data[i]=pkt_data[i];
                }
                while(indata.size()>10);
                indata.push(newdata);
            }
            pcap_close(fin);
        }
    }
    pthread_exit(NULL);
}
