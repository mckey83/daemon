#include"coretest.h"
#include <string.h>
int counter = 0;
char* test[] = {"show [192.168.0.1] count",
                "show [192.168.120.91] count",
                "show [0.0.1.11] count",
                "show [0.10.10.91] count",
//                "show [0.0.a0.1] count",
//                "select iface [wlan0]","start","show","load","show","load","show","show","stop","select iface [wlan0]",
//                "start",
                 "exit"};
void testCommand(char* string) {
    long long t = gettimeus ();
    long long t2 = gettimeus ();
    long long pause = 2000000;
    while (1){
        t2 = gettimeus ();
        if ((t2 - t) > pause) break;
    }
    memcpy(string, test[counter],strlen (test[counter]));
    counter++;
}
