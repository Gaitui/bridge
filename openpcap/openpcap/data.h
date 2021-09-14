#ifndef DATA_H
#define DATA_H
#include <vector>
#include "head.h"

struct data{
    std::vector<int> address;
    int port;
    Head head;
    u_char *pkt_data;
};

#endif // DATA_H
