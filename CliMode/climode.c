#include"climode.h"
#include"CliMode/command/is_command.h"
#include"CliMode/command/commands.h"
#include"CliMode/test/coretest.h"
#include"CliMode/test/test_macro.h"
#define true  1
#define false 0

void CliMode_start(){
    showStartMessage();
    const int LEN = 100;
    while (true) {
        char string[LEN];
        int index;
        for (index = 0; index < LEN; index++)
            string[index] = NULL;
        Work_MAIN(readCommand(&string, LEN);)
        Test_MAIN(testCommand(string); printf("test command : %s \n", string);)

        if (isCommandExit(string)) {
            commandExitCli();
            break;
        }
        if (isCommandShow(string)) {
            commandShowCli();
            continue;
        }
        if (isCommandSettingInterface(string)) {
            commandSettingInerfaceCli(string);
            continue;
        }
        if (isCommandStart(string)) {
            commandStartCli();
            continue;
        }
        if (isCommandStop(string)) {
            commandStopCli();
            continue;
        }
        if (isCommandSave(string)) {
            commandSaveCli();
            continue;
        }
        if (isCommandLoad(string)) {
            commandLoadCli();
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

