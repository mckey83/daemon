#include "is_command.h"
#include <string.h>
#include"macro/ip_to_d_d_d_d.h"
#include <stdint.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


const char* isExit = "exit";
const char* isStart = "start";
const char* isShow = "show";
const char* isStop = "stop";


const char* isEth0Interface = "select iface [eth0]";
const char* isWlan0Interface = "select iface [wlan0]";
const char* isDaemonEth0Interface = "select_iface_[eth0]";
const char* isDaemonWlan0Interface = "select_iface_[wlan0]";

const char* isSave = "save";
const char* isLoad = "load";

const char* isShowIpC = "show [";
const char* isShowIpCountC = "] count";

const char* isHelp = "--help";

int isDaemon(int argc){
    return argc > 1;
}


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

int isDaemonSelectIface(const char* string){
   return  strcmp (string, isDaemonEth0Interface) == 0  || strcmp (string, isDaemonWlan0Interface) == 0;
}


int isCommandSave (const char* string){
    return strcmp (string, isSave) == 0;
}

int isCommandLoad (const char* string){
    return strcmp (string, isLoad) == 0;
}

int isCommandShowIP (const char* string) {   
    int start = -1;
    char* resultStart = strstr (string, isShowIpC);
    if (resultStart == NULL) {
       return 0;
    }
    else {
        start = resultStart-string;
        char* resultFinish = strstr (string, isShowIpCountC);
        if (resultFinish == NULL)
            return 0;       
        else
            return 1;        
    }
}

int isCommandHelp(const char* string) {
    return strcmp (string, isHelp) == 0;
}


