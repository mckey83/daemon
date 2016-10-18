#include"daemon.h"

#include <stddef.h>
#define CHILD_NEED_WORK			1
#define CHILD_NEED_TERMINATE	2
#define FD_LIMIT		        1024*10
#define __USE_GNU
#include <stdio.h>
#define __USE_GNU
#include <stdlib.h>
#include <signal.h>
#include <execinfo.h>
#include <sys/time.h>
#include <sys/resource.h>
#include"DaemonMode/log/log.h"
#include"DaemonMode/tests/test_daemon.h"
#include"DaemonMode/sniffer/sniffer.h"
#include"DaemonMode/store/store_simple.h"
#include <pthread.h>



int commandStart ();
int commandForSniffer = 1;
pthread_t thread;
char* interface;
__be32* searchIpDaemon = 0;

void Daemon_prepareSignals(sigset_t* customSetForSignal);

int Daemon_start(char* interface_) {
    DEBUG_TEST_ACTION(int i = 0;)
    DEBUG_TEST_ACTION(int n = 0;)
    commandForSniffer = 1;
    interface = interface_;
                                                                                                                                                                DEBUG_TEST_ACTION(i++;)
                                                                                                                                                                DEBUG_TEST_INFO(printf("%d.Daemon_start() pid = %d\n", i, getpid());)
    sigset_t customSetForSignal;
    int signo;
   Daemon_prepareSignals(&customSetForSignal);
   Log_write("[DAEMON] Started\n");

   int result = commandStart();
   sleep(1);
                                                                                                                                                               DEBUG_TEST_INFO(printf("Daemon result = %d", result);)
   if (result >-1 && commandForSniffer != CHILD_NEED_TERMINATE ) {
                                                                                                                                                                   DEBUG_TEST_INFO(printf("Daemon wait signal()");)
       sigwait(&customSetForSignal, &signo);
       printf("DEMON Signal %i - %s\n", signo, sys_siglist[signo]);
       Log_write("[DAEMON] SIGTERM Stopped\n");
       commandFinish();
       pthread_join(thread, NULL);
       save();
       sleep(1);
       Log_write("[DAEMON] OK Stopped\n");
       return CHILD_NEED_WORK;
   }
   else
       return CHILD_NEED_TERMINATE;
}

void Daemon_prepareSignals(sigset_t* customSetForSignal) {
    sigemptyset(customSetForSignal);
    sigaddset(customSetForSignal,SIGFPE); // ошибка FPU
    sigaddset(customSetForSignal,SIGILL); // ошибочная инструкция
    sigaddset(customSetForSignal,SIGSEGV); // ошибка доступа к памяти
    sigaddset(customSetForSignal,SIGBUS); // ошибка шины, при обращении к физической памяти
    sigaddset(customSetForSignal, SIGQUIT);
    sigaddset(customSetForSignal, SIGINT);
    sigaddset(customSetForSignal, SIGTERM);
    sigaddset(customSetForSignal, SIGUSR1);
    sigprocmask(SIG_BLOCK, customSetForSignal, NULL);
}

void * snifferThread(void * argument) {
    Sniffer_start(interface, argument, &searchIpDaemon);
}

int commandStart () {
    int result = pthread_create(&thread, NULL, snifferThread, &commandForSniffer);
    if (result != 0) {
        perror("ERROR : thread did not create");
        return -1;
    }
}

commandFinish(){
    commandForSniffer = 0;
}




