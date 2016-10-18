#include"DaemonMode/log/log.h"
#include"DaemonMode/workwithfile/workwithfile.h"
#include"DaemonMode/tests/test_work_with_file.h"




void Log_write(const char* log){
    const char* fileName = "debug.log";
    const char* openParameterLog = "a+";
    DEBUG_TEST_ACTION(int isResult = ) File_write (fileName, log, strlen(log),openParameterLog);
    DEBUG_TEST_RESULT( if (isResult)
                    printf("++++>Log_write() - OK\n");
               else
                  printf("---->Log_write() - IS FALIED\n");)

}

void Log_Daemon_Keeper_sessionPidWrite(int sessionPid){
    const char* fileNamePid = "daemon.pid";
    const char* openParameterLogPid = "w+";
    char log[10];
    sprintf(&log, "%d", sessionPid);

    DEBUG_TEST_ACTION(int isResult = ) File_write (fileNamePid, log, strlen(log),openParameterLogPid);
    DEBUG_TEST_RESULT( if (isResult)
                    printf("++++>Log_Daemon_Keeper_sessionPidwrite - OK\n");
               else
                  printf("---->Log_Daemon_Keeper_sessionPidwrite - IS FALIED\n");)

}

void Log_Daemon_pidWrite(int daemonPid){
    const char* fileNamePid = "daemonPid.log";
    const char* openParameterLogPid = "w+";
    char log[10];
    sprintf(&log, "%d", daemonPid);

    DEBUG_TEST_ACTION(int isResult = ) File_write (fileNamePid, log, strlen(log),openParameterLogPid);
    DEBUG_TEST_RESULT( if (isResult)
                    printf("++++>Log_Daemon_pidWrite - OK\n");
               else
                  printf("---->Log_Daemon_pidWrite - IS FALIED\n");)

}


