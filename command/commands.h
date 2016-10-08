#ifndef COMMANDS_H
#define COMMANDS_H
#include <stdio.h>
#include "data/data.h"




void readCommand(char* string, int len);
void commandInitialize();
void commandStart ();
void commandStop ();
void commandSettingInerface (char* string);
void commandExit();
void commandSave();
void commandLoad();
void commandShow();


void * snifferThread(void * argument);




#endif // COMMANDS_H
