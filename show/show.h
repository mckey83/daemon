#ifndef SHOW_H
#define SHOW_H
#include"macro/ip_to_d_d_d_d.h"
#include"store/store.h"
#include"data/data.h"
void commandShowStore(struct Store* store);
void showRecordMain (struct Record record);
void showStartMessage();
void showIpPockets (const char* buff, int  quantityOfPackets);
void showHelp();
void clearScreen();
#endif // SHOW_H
