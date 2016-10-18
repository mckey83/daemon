#include"coretest.h"
#include <string.h>
int counter = 0;
char* test[] = {"select iface [wlan2]",
                "start",
                "show",
                "load",
                "show [192.168.0.59] count",
                "show [192.168.120.91] count",
                "show [0.0.1.11] count",
                "show [0.10.10.91] count",
                "show [0.0.a0.1] count",
             //   "show","load","show","show","stop","select iface [wlan0]",
                "start",
                 "exit"};
void testCommand(char* string) {
sleep(2);
    memcpy(string, test[counter],strlen (test[counter]));
    counter++;

}
