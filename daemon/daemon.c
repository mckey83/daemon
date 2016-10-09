#include"daemon.h"
#include"test/timer/timer.h"
#include <sys/types.h>
  #include <sys/stat.h>
const char* fileNameDaemon = "daemon.data";

int file_exist (char *filename) {
  struct stat   buffer;
  return (stat (filename, &buffer) == 0);
}

void daemonTimerForSave() {
    long long t = gettimeus ();
    long long t2 = gettimeus ();
    long long pause = 10000000;
    while (1){
        t2 = gettimeus ();
        if ((t2 - t) > pause) {            
            t2 = 0;
            t = gettimeus ();
            commandSave(fileNameDaemon);
        }
        sleep (5);
    }
}

void startDaemon(int argc, char* argv[]) {
    if (file_exist (fileNameDaemon)) {
      commandLoad(fileNameDaemon);
    }
    int index;
    for (index = 0; index < argc; index++) {
        if (isDaemonSelectIface(argv[index])) {
            commandSetDaemon();
            commandSettingInerface(argv[index]);
            continue;
        }
        if (isCommandStart(argv[index])) {
            commandStart();
            continue;
        }
    }
    daemonTimerForSave();    
    commandExit();
}
