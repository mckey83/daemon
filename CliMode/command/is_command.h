#ifndef IS_COMMAND_H
#define IS_COMMAND_H
#include <linux/types.h>

int isDaemon(int argc);
//int isDaemonSelectIface(const char* string);
//void initializeIsCommand(int*  isSetInterface_);
int isCommandExit(const char* string);
int isCommandStart( const char* string);
int isCommandStop( const char* string);
int isCommandShow(const char* string);
int isCommandSettingInterface(const char *string);
int isCommandSave(const char* string);
int isCommandLoad(const char* string);
int isCommandShowIP (const char* string);
int isCommandHelp(const char* string);

#endif // IS_COMMAND_H
