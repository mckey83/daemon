#include "is_command.h"
const char* isExit = "exit";
const char* isStart = "start";
const char* isShow = "show";
const char* isStop = "stop";

const char* isEth0Interface = "select iface [eth0]";
const char* isWlan0Interface = "select iface [wlan0]";

const char* isSave = "save";
const char* isLoad = "load";

int*  isSetInterface = 0;
void initializeIsCommand(int*  isSetInterface_) {
    isSetInterface = isSetInterface_;
}

int isCommandExit(const char* string) {
    return strcmp (string, isExit) == 0;
}
int isCommandStart(const char* string) {
    if (strcmp (string, isStart) == 0) {
        if (*isSetInterface)
            return 1;
        else
            printf("for command : \"start\"  please select iface \n");
    }
    return 0;
}

int isCommandStop( const char* string) {
    if (strcmp (string, isStop)  == 0) {
        if (*isSetInterface)
            return 1;
        else
            printf("for command: \"stop\" please select iface \n");
    }
    return 0;
}


int isCommandShow(const char* string) {
    return strcmp (string, isShow) == 0;
}

int isCommandSettingInterface(const char* string){
   return  strcmp (string, isEth0Interface) == 0  || strcmp (string, isWlan0Interface) == 0;
}


int isCommandSave (const char* string){
    return strcmp (string, isSave) == 0;
}

int isCommandLoad (const char* string){
    return strcmp (string, isLoad) == 0;
}
