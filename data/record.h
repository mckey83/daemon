#ifndef RECORD_H
#define RECORD_H
#include <linux/types.h>

struct Record {
   __be32 sourceIP;
   __be32 distanationIP;
    int quantityPockets;
};
#endif // RECORD_H
