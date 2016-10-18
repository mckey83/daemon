#include"daemon_keeper.h"
#include"signal.h"
#include"DaemonMode/tests/test_daemon_keeper.h"
#include <stdio.h>
#include <stdlib.h>
#include"DaemonMode/processidentifier/processidentifier.h"
#include"DaemonMode/workwithfile/workwithfile.h"
#include"errno.h"
#include"DaemonMode/daemon/daemon.h"
#include"DaemonMode/log/log.h"


#define CHILD_NEED_WORK			1
#define CHILD_NEED_TERMINATE	2
#define FALSE_CONTINUE          0
#define TRUE_CONTINUE           1



const char* PID_FILE = "my_daemon.pid";
int processIdentifierDaemon = 0;
int status = 0;
int need_start = 1;
const char* openParameterMain = "w+";
void prepareSignals(sigset_t* customSetForSignal);

int Daemon_keeper_start(char* interface) {
    Log_write("[Daemon_keeper] start\n");
    sigset_t customSetForSignal;
    siginfo_t signalInformation;
    prepareSignals(&customSetForSignal);
                                                                                                                                                                DEBUG_TEST_ACTION(int i = 0;);
                                                                                                                                                                DEBUG_TEST_ACTION(i++;);DEBUG_TEST_INFO(printf("%d.Daemon_keeper_start() writeProcessIdentifierToFile() \n", i));
    writeProcessIdentifierToFile(PID_FILE);
                                                                                                                                                                DEBUG_TEST_ACTION(int count = 0;)
    int isContinue  = 1;
    while (isContinue) {
        if (need_start){
            forkProcessIdentifier(&processIdentifierDaemon);
            need_start = 0;
        }
        if (isProcessIdentifierBroken(processIdentifierDaemon)) {
             char* buffer[100];
             sprintf(buffer, "[Daemon_keeper] Daemon_keeper_start() : Fork failed (%s)\n", strerror(errno));
             Log_write(buffer);
        }
        if(isProcessIdentifierChild(processIdentifierDaemon)) {
            Log_Daemon_pidWrite(getpid());
            status = Daemon_start(interface);
            exit(status);
        }
        if(isProcessIdentifierParent(processIdentifierDaemon))  {
                                                                                                                                                                        DEBUG_TEST_INFO(printf("%d.Daemon_keeper_start() parent : start work\n", i));
            sigwaitinfo (&customSetForSignal, &signalInformation);
            if (signalInformation.si_signo == SIGCHLD)
            {
                                                                                                                                                                            DEBUG_TEST_INFO(printf("signalInformation.si_signo == SIGCHLD\n");)

                wait(&status);                
                status = WEXITSTATUS(status);
                                                                                                                                                                            DEBUG_TEST_INFO(printf("-->status = %d \n", status);)
                if (status == CHILD_NEED_WORK){
                    printf("NEED WORK\n");
                    need_start = 1;
                }
                else if (status == CHILD_NEED_TERMINATE){
                    printf("NEED TERMINATE\n");
                    need_start = 0;
                    kill(processIdentifierDaemon,SIGINT);
                    wait(processIdentifierDaemon);
                    break;
                }
                else{
                     printf("SNIFFER DONT WORK\n");
                    kill(processIdentifierDaemon,SIGINT);
                    wait(processIdentifierDaemon);
                    //exit(EXIT_FAILURE);
                    break;
                }
            }

            else if (signalInformation.si_signo == SIGTERM) {
                printf("Daemon_keeper_start() SIGUSR1 \n");
                sleep(1);
                kill(processIdentifierDaemon,SIGINT);
                wait(processIdentifierDaemon);
                status = 0;
                //exit(0);
                break;
            }

            else{
                printf("Daemon_keeper else => %i - %s\n", signalInformation.si_signo, sys_siglist[signalInformation.si_signo]);
                break;
            }

        }
        sleep(1);
    }
    Log_write("[Daemon_keeper] Daemon_keeper_start() : Stop\n");
                                                                                                                                                            DEBUG_TEST_RESULT(
    if (1 == i )
    printf("++++>Daemon_keeper_start() - OK, i = %d \n", i);
    else
    printf("---->Daemon_keeper_start() - is Falied, i = %d \n",i);
);
                                                                                                                                                            DEBUG_TEST_INFO(printf("%d.Daemon_keeper_start() end \n", i));
    exit(0);
}


void writeProcessIdentifierToFile(char* Filename) {
    unsigned int processIdentifierForWrite = getpid();
                                                                                                                                                                DEBUG_TEST_INFO(printf("\nprocessIdentifierForWrite = %d\n", processIdentifierForWrite);)
    int bufferLen = 20;
    char buffer[bufferLen]; int index = 0;for(;index < bufferLen; index++) buffer[index] = "\0";
    sprintf(buffer, "%d", processIdentifierForWrite);
                                                                                                                                                                DEBUG_TEST_INFO(printf("\nstring = %s\n", buffer);)
    File_write (Filename, &buffer, strlen(buffer), openParameterMain);

}

void prepareSignals(sigset_t* customSetForSignal)
{
    sigemptyset(customSetForSignal);
    sigaddset(customSetForSignal, SIGHUP);
    sigaddset(customSetForSignal, SIGTERM);
    sigaddset(customSetForSignal, SIGINT);
    sigaddset(customSetForSignal, SIGUSR1);
    sigaddset(customSetForSignal, SIGQUIT);
    sigaddset(customSetForSignal, SIGCHLD);
    sigprocmask(SIG_BLOCK, customSetForSignal, 0);
}

