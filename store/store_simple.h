#ifndef ADD_H
#define ADD_H
#include"store.h"
#include"data/data.h"
#include"linux/types.h"


int initializeData(struct Store* store_, struct Record* record_);
void add (struct Store* store_, struct Record* record, pthread_mutex_t* myMutex);
int mySearch (__be32 ip);
void sortingIp();
void save(const char* fileName);
void load(const char* fileName);
int Asc(int left, int right);
#endif // ADD_H
