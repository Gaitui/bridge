#include <fstream>
#include <pthread.h>
#include <queue>
#include <vector>

#include "data.h"
#include "head.h"
#include "trans.h"
#include "twse01.h"
#include "twse06.h"
#include "twse21.h"
#include "twse22.h"
#include "twse23.h"
#include "tpex01.h"
#include "tpex06.h"
#include "tpex21.h"
#include "tpex22.h"
#include "tpex23.h"

extern bool havefile;
extern std::queue<data> indata;

static void* run(void *lp)
{
    FILE *fptrtest = fopen("/root/20210823/test.txt","w");
    FILE *fptrTWSE01 = fopen("/root/20210823/TWSE01.csv","w");
    FILE *fptrTWSE06 = fopen("/root/20210823/TWSE06.csv","w");
    FILE *fptrTWSE21 = fopen("/root/20210823/TWSE21.csv","w");
    FILE *fptrTWSE22 = fopen("/root/20210823/TWSE22.csv","w");
    FILE *fptrTWSE23 = fopen("/root/20210823/TWSE23.csv","w");
    FILE *fptrTPEX01 = fopen("/root/20210823/TPEX01.csv","w");
    FILE *fptrTPEX06 = fopen("/root/20210823/TPEX06.csv","w");
    FILE *fptrTPEX21 = fopen("/root/20210823/TPEX21.csv","w");
    FILE *fptrTPEX22 = fopen("/root/20210823/TPEX22.csv","w");
    FILE *fptrTPEX23 = fopen("/root/20210823/TPEX23.csv","w");

    while(1)
    {
        if(!indata.empty())
        {
            data temp = indata.front();
            indata.pop();
            int h = 0;
            h+=42;
            if(temp.pkt_data[h]==27)
            {
                Head dhead = decodeHead(temp.pkt_data,h);
                if(dhead.mtype==1)
                {
                    if(dhead.mcode==1)
                    {
                        TWSE01 twse01 = decodeTWSE01(h,temp.pkt_data,dhead);
                        printTWSE01(fptrTWSE01,twse01);
                    }
                    else if(dhead.mcode==6)
                    {
                        TWSE06 twse06 = decodeTWSE06(h,temp.pkt_data,dhead);
                        printTWSE06(fptrTWSE06,twse06);
                    }
                    else if(dhead.mcode==21)
                    {
                        TWSE21 twse21 = decodeTWSE21(h,temp.pkt_data,dhead);
                        printTWSE21(fptrTWSE21,twse21);
                    }
                    else if(dhead.mcode==22)
                    {
                        TWSE22 twse22 = decodeTWSE22(h,temp.pkt_data,dhead);
                        printTWSE22(fptrTWSE22,twse22);
                    }
                    else if(dhead.mcode==23)
                    {
                        TWSE23 twse23 = decodeTWSE23(h,temp.pkt_data,dhead);
                        printTWSE23(fptrTWSE23,twse23);
                    }
                }
                else if(dhead.mtype==2)
                {
                    if(dhead.mcode==1)
                    {
                        TPEX01 tpex01 = decodeTPEX01(h,temp.pkt_data,dhead);
                        printTPEX01(fptrTPEX01,tpex01);
                    }
                    else if(dhead.mcode==6)
                    {
                        TPEX06 tpex06 = decodeTPEX06(h,temp.pkt_data,dhead);
                        printTPEX06(fptrTPEX06,tpex06);
                    }
                    else if(dhead.mcode==21)
                    {
                        TPEX21 tpex21 = decodeTPEX21(h,temp.pkt_data,dhead);
                        printTPEX21(fptrTPEX21,tpex21);
                    }
                    else if(dhead.mcode==22)
                    {
                        TPEX22 tpex22 = decodeTPEX22(h,temp.pkt_data,dhead);
                        printTPEX22(fptrTPEX22,tpex22);
                    }
                    else if(dhead.mcode==23)
                    {
                        TPEX23 tpex23 = decodeTPEX23(h,temp.pkt_data,dhead);
                        printTPEX23(fptrTPEX23,tpex23);
                    }
                }

            }
        }
        else
        {
            if(!havefile)
                break;
        }
    }
    fclose(fptrtest);
    fclose(fptrTWSE01);
    fclose(fptrTWSE06);
    fclose(fptrTWSE21);
    fclose(fptrTWSE22);
    fclose(fptrTWSE23);
    fclose(fptrTPEX01);
    fclose(fptrTPEX06);
    fclose(fptrTPEX21);
    fclose(fptrTPEX22);
    fclose(fptrTPEX23);
    pthread_exit(NULL);
}
