#include <bits/stdc++.h>
#include <queue>

#include "data.h"
#include "head.h"
#include "twse01.h"
#include "tpex01.h"

extern bool havefile;
extern std::queue<data> q01;
extern bool TP01;
extern bool TW01;

static void* format01(void *lp)
{
    FILE *fptrTWSE01;
    FILE *fptrTPEX01;

    while(1)
    {
        if(!q01.empty())
        {
            int h = 0;
            data temp = q01.front();
            q01.pop();
            if(temp.head.mtype==1)
            {
                if(!TW01)
                {
                    fptrTWSE01 = fopen("/root/20210823/TWSE01.csv","w");
                    TW01 = true;
                }
                TWSE01 twse01 = decodeTWSE01(h,temp.pkt_data,temp.head);
                printTWSE01(fptrTWSE01,twse01);
            }
            else if(temp.head.mtype==2)
            {
                if(!TP01)
                {
                    fptrTPEX01 =  fopen("/root/20210823/TPEX01.csv","w");
                    TP01 = true;
                }
                TPEX01 tpex01 = decodeTPEX01(h,temp.pkt_data,temp.head);
                printTPEX01(fptrTPEX01,tpex01);
            }
        }
        else
        {
            if(!havefile)
                break;
        }
    }
    if(TW01)
    {
        fclose(fptrTWSE01);
    }
    if(TP01)
    {
        fclose(fptrTPEX01);
    }
    pthread_exit(NULL);
}
