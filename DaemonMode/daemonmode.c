#include"daemonmode.h"
#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include"DaemonMode/tests/test_main.h"
#include"signal.h"
#include"DaemonMode/daemon_keeper/daemon_keeper.h"
#include"DaemonMode/processidentifier/processidentifier.h"
#include"DaemonMode/log/log.h"
#include"DaemonMode/workwithfile/workwithfile.h"

int isCorrectDaemon(int argc, char** argv);
void setMaskControlFilePermissions();
void actionSighupHandler(int sig);
void closeAllConsoleInformation();
void waitForCommandStop();
pid_t createNewSession();
void changeDirRoot();
int processIdentifier = 0;
static pid_t  sessionPid = 0;

void DaemonMode_start(int argc, char* argv[]){
    printf("start \n");
    sleep(1);
                                                                                                                                                            DEBUG_TEST_ACTION(int i = 0; char* source = "main()"; );
    int processIdentifier = 0;
    int status = 0;
                                                                                                                                                            DEBUG_TEST_ACTION(i++;)DEBUG_TEST_INFO(printf("%d.%s isCorrectDaemon \n", i, source));
    if (!isCorrectDaemon(argc, argv)){
        exit(EXIT_FAILURE);
    }

                                                                                                                                                            DEBUG_TEST_ACTION(i++;)DEBUG_TEST_INFO(printf("%d.%s forkProcessIdentifier(&processIdentifier) \n", i, source));
    forkProcessIdentifier(&processIdentifier);
    if (isProcessIdentifierBroken(processIdentifier)){
        exit(EXIT_FAILURE);
    }
//-----------------------------CHILD-------------------------------------------------------------------------------------------------
                                                                                                                                                            DEBUG_TEST_ACTION(i++;)DEBUG_TEST_INFO(printf("%d.%s isProcessIdentifierChild(processIdentifier)) \n", i, source));
    if (isProcessIdentifierChild(processIdentifier)) {
                                                                                                                                                            DEBUG_TEST_ACTION(i++;)DEBUG_TEST_INFO(printf("%d.%s Child pid(%d) setMaskControlFilePermissions() \n", i ,source, processIdentifier));
        setMaskControlFilePermissions();
                                                                                                                                                            DEBUG_TEST_ACTION(i++;)DEBUG_TEST_INFO(printf("%d.%s Child createNewSession() \n", i, source ));
        sessionPid =  createNewSession();
        Log_Daemon_Keeper_sessionPidWrite(sessionPid);
                                                                                                                                                            DEBUG_TEST_ACTION(i++;)DEBUG_TEST_INFO(printf("%d.%s Child changeDirRoot() \n", i, source));
        changeDirRoot();
        closeAllConsoleInformation(); // hide all console information
                                                                                                                                                            DEBUG_TEST_ACTION(i++;)DEBUG_TEST_INFO(printf("%d.Daemon_keeper_start() \n", i));
        status = Daemon_keeper_start(argv[1]);
                                                                                                                                                            DEBUG_TEST_RESULT(if (7==i && status>=0) printf("++++>Test Child OK \n"); else printf("---->Test Chaild - is Falied\n"));
        return status;

    }
//-----------------------------PARENT-------------------------------------------------------------------------------------------------
    if (isProcessIdentifierParent(processIdentifier))
    return 0;
}


int isEthernet0(const char* string) {
    const char* isEth0 = "eth0";
    return strcmp (string, isEth0) == 0 ;
}

int isWlan0(const char* string) {
    const char* isWlan0 = "wlan0";
    return strcmp (string, isWlan0) == 0 ;
}

int isWlan2(const char* string) {
    const char* isWlan2 = "wlan2";
    return strcmp (string, isWlan2) == 0 ;
}

int isCorrectDaemon(int argc, char** argv){
    if (argc == 2){
        if (isEthernet0(argv[1]) || isWlan2(argv[1]) || isWlan0(argv[1]) )
            return 1;
    }
        printf("is CorrectDeamon(), usage:\n./daemon eth0\n./daemon wlan0\n./daemon wlan2\netc.\n");
        return 0;
}

void setMaskControlFilePermissions(){
    umask(0);
}

pid_t  createNewSession(){
    return setsid();
}

void changeDirRoot(){
   chdir("/home/alex/workspaceCPP/Daemon/build-daemon-Desktop_Qt_5_7_0_GCC_64bit-Debug/");
}

void closeAllConsoleInformation()
{
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}







