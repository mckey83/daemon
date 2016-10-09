#ifndef DATA_H
#define DATA_H
#include"record.h"
#include <pthread.h>


struct Data {
    struct Store* store;
    void (*storeAdd)(struct Store* store, struct Record* record, pthread_mutex_t* pThread_mutex_t);
    pthread_mutex_t* pThread_mutex_t;	// инlефикатор мютекса
    int* command;
    int* isDaemon;
};


#endif // DATA_H
