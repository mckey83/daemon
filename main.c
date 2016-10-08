
#include"sniffer/sniffer.h"
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include"data/data.h"
#include"store/store.h"
#include"store/initialize_store.h"
#include"command/commands.h"
#include"show/show.h"
#include"command/is_command.h"






int main ( ) {



    int len = 100;







    commandInitialize();



    while (1) {
        fflush(stdout);
        char string[len];
        readCommand(&string, len);
        if (isCommandExit(string)) {
            commandExit();
            break;
        }
        if (isCommandShow(string)) {
            commandShow();
            continue;
        }
        if (isCommandSettingInterface(string)) {
            commandSettingInerface(string);
            continue;
        }
        if (isCommandStart(string)) {
            commandStart();
            continue;
        }
        if (isCommandStop(string)) {
            commandStop();
            continue;
        }
        if (isCommandSave(string)) {
            commandSave();
            continue;
        }
        if (isCommandLoad(string)) {
            commandLoad();
            continue;
        }
       // printf("please enter correct command, for help type : --help \n");


    }
}







