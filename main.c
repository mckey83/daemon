#include"DaemonMode/daemonmode.h"
#include"CliMode/climode.h"

int main (int argc, char* argv[]) {
    if (isDaemon(argc))
        DaemonMode_start(argc, argv);
    else
        CliMode_start ();
    return 0;
}







