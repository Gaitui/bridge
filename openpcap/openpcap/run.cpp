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

extern char opath[];

extern bool havefile;
extern std::queue<data> q01;
extern std::queue<data> q06;
extern std::queue<data> q21;
extern std::queue<data> q22;
extern std::queue<data> q23;

extern std::vector<int> tw06info;
extern std::vector<int> tp06info;

extern bool TP01;
extern bool TP06;
extern bool TP21;
extern bool TP22;
extern bool TP23;
extern bool TW01;
extern bool TW06;
extern bool TW21;
extern bool TW22;
extern bool TW23;


static void* format01(void *lp)
{
    FILE *fptrTWSE01;
    FILE *fptrTPEX01;
    char root[60];
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
                    sprintf(root,"%sTWSE01.csv",opath);
                    fptrTWSE01 = fopen(root,"w");
                    TW01 = true;
                }
                TWSE01 twse01 = decodeTWSE01(h,temp.pkt_data,temp.head);
                printTWSE01(fptrTWSE01,twse01,temp.address,temp.port);
            }
            else if(temp.head.mtype==2)
            {
                if(!TP01)
                {
                    sprintf(root,"%sTPEX01.csv",opath);
                    fptrTPEX01 =  fopen(root,"w");
                    TP01 = true;
                }
                TPEX01 tpex01 = decodeTPEX01(h,temp.pkt_data,temp.head);
                printTPEX01(fptrTPEX01,tpex01,temp.address,temp.port);
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

static void* format06(void *lp)
{
    FILE *fptrTWSE06;
    FILE *fptrTPEX06;
    char root[60];
    bool twstart=false;
    bool tpstart=false;
    int twchseq;
    int tpchseq;
    TWSE06 twse06;
    TPEX06 tpex06;
    while(1)
    {
        if(!q06.empty())
        {
            int h = 0;
            data temp = q06.front();
            q06.pop();
            if(temp.head.mtype==1)
            {
                if(!TW06)
                {
                    sprintf(root,"%sTWSE06.csv",opath);
                    fptrTWSE06 = fopen(root,"w");
                    TW06 = true;
                }
                twse06 = decodeTWSE06(h,temp.pkt_data,temp.head);
                if(twse06.mtime>=83000000000 && !twstart)
                {
                    twchseq = twse06.head.mseq;
                    tw06info.push_back(twchseq);
                    twstart = true;
                }
                if(twstart)
                {
                    if(twchseq != twse06.head.mseq)
                    {
                        for(int i=twchseq;i<twse06.head.mseq;i++)
                        {
                            tw06info.push_back(i);
                            printf("%d\n",i);
                        }
                        twchseq = twse06.head.mseq;
                    }
                    printTWSE06(fptrTWSE06,twse06,temp.address,temp.port);
                    twchseq++;
                }
            }
            else if(temp.head.mtype==2)
            {
                if(!TP06)
                {
                    sprintf(root,"%sTPEX06.csv",opath);
                    fptrTPEX06 =  fopen(root,"w");
                    TP06 = true;
                }
                tpex06 = decodeTPEX06(h,temp.pkt_data,temp.head);
                if(tpex06.mtime>=83000000000 && !tpstart)
                {
                    tpchseq = tpex06.head.mseq;
                    tp06info.push_back(tpchseq);
                    tpstart = true;
                }
                if(tpstart)
                {
                    if(tpchseq != tpex06.head.mseq)
                    {
                        for(int i=tpchseq;i<tpex06.head.mseq;i++)
                        {
                            tp06info.push_back(i);
                            printf("%d\n",i);
                        }
                        tpchseq = tpex06.head.mseq;
                    }
                    printTPEX06(fptrTPEX06,tpex06,temp.address,temp.port);
                    tpchseq++;
                }
            }
        }
        else
        {
            if(!havefile)
                break;
        }
    }
    if(twstart)
      tw06info.push_back(twse06.head.mseq);
    if(tpstart)
      tp06info.push_back(tpex06.head.mseq);
    if(TW06)
    {
        fclose(fptrTWSE06);
    }
    if(TP06)
    {
        fclose(fptrTPEX06);
    }
    pthread_exit(NULL);
}

static void* format21(void *lp)
{
    FILE *fptrTWSE21;
    FILE *fptrTPEX21;
    char root[60];
    while(1)
    {
        if(!q21.empty())
        {
            int h = 0;
            data temp = q21.front();
            q21.pop();
            if(temp.head.mtype==1)
            {
                if(!TW21)
                {
                    sprintf(root,"%sTWSE21.csv",opath);
                    fptrTWSE21 = fopen(root,"w");
                    TW21 = true;
                }
                TWSE21 twse21 = decodeTWSE21(h,temp.pkt_data,temp.head);
                printTWSE21(fptrTWSE21,twse21,temp.address,temp.port);
            }
            else if(temp.head.mtype==2)
            {
                if(!TP21)
                {
                    sprintf(root,"%sTPEX21.csv",opath);
                    fptrTPEX21 =  fopen(root,"w");
                    TP21 = true;
                }
                TPEX21 tpex21 = decodeTPEX21(h,temp.pkt_data,temp.head);
                printTPEX21(fptrTPEX21,tpex21,temp.address,temp.port);
            }
        }
        else
        {
            if(!havefile)
                break;
        }
    }
    if(TW21)
    {
        fclose(fptrTWSE21);
    }
    if(TP21)
    {
        fclose(fptrTPEX21);
    }
    pthread_exit(NULL);
}

static void* format22(void *lp)
{
    FILE *fptrTWSE22;
    FILE *fptrTPEX22;
    char root[60];
    while(1)
    {
        if(!q22.empty())
        {
            int h = 0;
            data temp = q22.front();
            q22.pop();
            if(temp.head.mtype==1)
            {
                if(!TW22)
                {
                    sprintf(root,"%sTWSE22.csv",opath);
                    fptrTWSE22 = fopen(root,"w");
                    TW22 = true;
                }
                TWSE22 twse22 = decodeTWSE22(h,temp.pkt_data,temp.head);
                printTWSE22(fptrTWSE22,twse22,temp.address,temp.port);
            }
            else if(temp.head.mtype==2)
            {
                if(!TP22)
                {
                    sprintf(root,"%sTPEX22.csv",opath);
                    fptrTPEX22 =  fopen(root,"w");
                    TP22 = true;
                }
                TPEX22 tpex22 = decodeTPEX22(h,temp.pkt_data,temp.head);
                printTPEX22(fptrTPEX22,tpex22,temp.address,temp.port);
            }
        }
        else
        {
            if(!havefile)
                break;
        }
    }
    if(TW22)
    {
        fclose(fptrTWSE22);
    }
    if(TP22)
    {
        fclose(fptrTPEX22);
    }
    pthread_exit(NULL);
}

static void* format23(void *lp)
{
    FILE *fptrTWSE23;
    FILE *fptrTPEX23;
    char root[60];
    while(1)
    {
        if(!q23.empty())
        {
            int h = 0;
            data temp = q23.front();
            q23.pop();
            if(temp.head.mtype==1)
            {
                if(!TW23)
                {
                    sprintf(root,"%sTWSE23.csv",opath);
                    fptrTWSE23 = fopen(root,"w");
                    TW23 = true;
                }
                TWSE23 twse23 = decodeTWSE23(h,temp.pkt_data,temp.head);
                printTWSE23(fptrTWSE23,twse23,temp.address,temp.port);
            }
            else if(temp.head.mtype==2)
            {
                if(!TP23)
                {
                    sprintf(root,"%sTPEX23.csv",opath);
                    fptrTPEX23 =  fopen(root,"w");
                    TP23 = true;
                }
                TPEX23 tpex23 = decodeTPEX23(h,temp.pkt_data,temp.head);
                printTPEX23(fptrTPEX23,tpex23,temp.address,temp.port);
            }
        }
        else
        {
            if(!havefile)
                break;
        }
    }
    if(TW23)
    {
        fclose(fptrTWSE23);
    }
    if(TP23)
    {
        fclose(fptrTPEX23);
    }
    pthread_exit(NULL);
}

