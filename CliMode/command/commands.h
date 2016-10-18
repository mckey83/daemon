#ifndef COMMANDS_H
#define COMMANDS_H


#include <pthread.h>


void readCommand(char* string, int len);
void commandStartCli ();
void commandStopCli ();
void commandSettingInerfaceCli (char* string);
void commandExitCli();
void commandSaveCli();
void commandLoadCli();


void commandShowCli();
void commandShowIpPockets(char* string);
void commandHelp();

void showStartMessage();


#endif // COMMANDS_H
