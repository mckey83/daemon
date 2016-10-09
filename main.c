
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
#include"test/coretest.h"
#include"linux/types.h"
#include"test/test_macro.h"
#define true  1
#define false 0
#include"daemon/daemon.h"


const char* fileNameCli = "cli.data";

int main (int argc, char* argv[]) {
    const int LEN = 100;
    commandInitialize();
    if (isDaemon(argc)) {        
        startDaemon(argc, argv);
    }
    else {
        showStartMessage();
        while (true) {
            char string[LEN];
            int index;
            for (index = 0; index < LEN; index++)
                string[index] = NULL;
            Work_MAIN(readCommand(&string, LEN);)
            Test_MAIN(testCommand(string); printf("test command : %s \n", string);)

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
                commandSave(fileNameCli);
                continue;
            }
            if (isCommandLoad(string)) {
                commandLoad(fileNameCli);
                continue;
            }
            if (isCommandShowIP(string)) {
                commandShowIpPockets(string);
                continue;
            }
            if (isCommandHelp(string)) {
                commandHelp();
                continue;
            }
            printf("please enter correct command, for help type : --help \n");
        }
    }
    Test_MAIN(int index;for (index = 0 ; index < 5; index++){printf("result %d \n", result_Test [index]);})
    printf("OK \n");
    return 0;
}







