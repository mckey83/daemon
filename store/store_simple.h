#ifndef ADD_H
#define ADD_H
#include"store.h"
#include"data/data.h"

void add (struct Store* store_, struct Record* record, pthread_mutex_t* myMutex);
void save(pthread_mutex_t* myMutex2);
void load(pthread_mutex_t* myMutex2);
#endif // ADD_H
