#ifndef SHOW_H
#define SHOW_H
#include"macro/ip_to_d_d_d_d.h"
#include"store/store.h"
#include"data/data.h"
void commandShowStore(struct Store* store, pthread_mutex_t* myMutex);
void showRecordMain (struct Record record);

#endif // SHOW_H
