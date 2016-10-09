#ifndef COMMANDS_H
#define COMMANDS_H
#include <stdio.h>
#include "data/data.h"
#include "test/test_macro.h"

struct Data {
    struct Store* store;
    void (*storeAdd)(struct Store* store, struct Record* record, pthread_mutex_t* pThread_mutex_t);
    pthread_mutex_t* pThread_mutex_t;	// инlефикатор мютекса
    int* command;
    int* isDaemon;
};

void readCommand(char* string, int len);
void commandSetDaemon();
void commandInitialize();
void commandStart ();
void commandStop ();
void commandSettingInerface (char* string);
void commandExit();
void commandSave(const char* fileName);
void commandLoad(const char* fileName);



void commandShow();
void commandShowIpPockets(char* string);
void commandHelp();




void * snifferThread(void * argument);




#endif // COMMANDS_H
