#ifndef TWSE_ISBD_H
#define TWSE_ISBD_H
#include "head.h"

struct TWSEISBD{
    //Header
    Head head;

    //body
    char scode[6];
    char sname[17];
    char sind[2];
    char stype[2];
    char strans[2];
    int sexec;
    char cnote;
    char bnote;
    int irefprice;
    int frefprice;
    int ilup;
    int dlup;
    int ildown;
    int fldown;
    char ten;
    char rexec;
    char pexec;
    char dtrade;
    char fsell;
    char fborrow;
    int ssec;
    char wcode;
    int isprice;
    int dsprice;
    int lsnum;
    int lwoff;
    int obalance;
    int ippercent;
    int fppercent;
    int ipupperb;
    int fpupperb;
    int iplowerb;
    int fplowerb;
    int due;
    int blot;
    char ccode[3];
    int minfo;
    int check;
    int terminal[2];

};

#endif // TWSE_ISBD_H
