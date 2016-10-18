#ifndef ADD_H
#define ADD_H

#include"linux/types.h"
#include <pthread.h>

#include"DaemonMode/data/record.h"


int initializeStore();
int addData(struct Record* record);
void save();
void load();
void Store_show();
Store_searchIp (__be32* searchIp);
#endif // ADD_H
