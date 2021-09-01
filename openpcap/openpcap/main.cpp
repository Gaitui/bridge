#include <QCoreApplication>
#include <iostream>
#include <QDebug>
#include <pcap.h>

struct TWSE_Header{
    /*char EscCode;
    char MessageLen[2];
    char MessageType[1];
    char MessageCode[1];
    char MessageVersion[1];
    char MessageSeq[4];*/
    char temp[10];
    char code[6];

};

//struct TWSE_

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    char errbuf[PCAP_ERRBUF_SIZE];
    qDebug()<<"Hi";
    pcap_t *fin = pcap_open_offline("/root/20210823/p1p1.pcap", errbuf);
    if(!fin)
    {
        qDebug()<<"error : "<<errbuf;
    }
    else
    {
        qDebug()<<"Load file success";

        struct pcap_pkthdr *header;
        const u_char *pkt_data;
        int res;
        while(res = pcap_next_ex(fin,&header,&pkt_data) >=0)
        {
            int h = 42;
            if(pkt_data[h]==27)
            {
                int seek = 0;
                //while(seek<(header->len-h))
                //{
                    TWSE_Header *data = (TWSE_Header*)(pkt_data + h + seek);
                    qDebug()<<data->code;
                //}
            }
        }
    }
    pcap_close(fin);
    return a.exec();
}
