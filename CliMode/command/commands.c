#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <linux/types.h>
#include"DaemonMode/sniffer/sniffer.h"
#define COMMAND_SHOW 5
#define COMMAND_SAVE 10
#define COMMAND_LOAD 15
#define COMMAND_SEARCH_IP 25

const char* isShowIp = "show [";
const char* isShowIpCount = "] count";

char* eth0Interface = "select iface [eth0]";
char* wlan0Interface = "select iface [wlan0]";
char* wlan2Interface = "select iface [wlan2]";


__u8* networkInterface;



pthread_t thread;
pthread_mutex_t* myMutex;


int isSetInterfaceCommand = 0;
int isUsedThread = 0;
int isDaemonStart = 0;
int command = 0;
__be32 searchIp = 0;



void readCommand(char* string, int len){
    fgets(string, len, stdin);
    int i;
    for (i = 0; i < len; i++) {
        if (string[i] == '\n') {
            string[i] = '\0';
            break;
        }
    }
}

void * snifferThreadCli(void * argument) {
    Sniffer_start(networkInterface, &command,&searchIp);
}

void commandStartCli () {

    if (isSetInterfaceCommand){
    command = 1;
    printf("commandStartCli \n");
    int result;
    int a;
    result = pthread_create(&thread, NULL, snifferThreadCli, &a);
    if (result != 0) {
        perror("ERROR : thread did not create");
    }
    isUsedThread = 1;
    }
    else printf("please select interface : \"select iface [eth0]\" \n");
}



void commandStopCli (){
   command = 0;
}

void commandSettingInerfaceCli (char* string) {
    if (isSetInterfaceCommand){
        commandExitCli();
    }
    if ( strcmp (string, eth0Interface) == 0  )
        networkInterface = "eth0";
    if ( strcmp (string, wlan0Interface) == 0  )
        networkInterface = "wlan0";
    if ( strcmp (string, wlan2Interface) == 0  )
        networkInterface = "wlan2";
    isSetInterfaceCommand = 1;
        printf("for start command : \"start\" , networkInterface = %s\n", string);

}



void commandExitCli(){
    commandStopCli();
    if (isUsedThread){
        pthread_join(thread, NULL);
        printf("sniffer closed \n");
    }
    else
        printf("sniffer did not use \n");
}



void commandSaveCli(){
    command = COMMAND_SAVE;
}

void commandLoadCli(){
    command = COMMAND_LOAD;
}

void commandShowCli(){
   command = COMMAND_SHOW;
}



__be32 getDecimalValueOfIPV4_String(char* ipAddress) {
    uint8_t ipbytes[4]={};
    int i = 0;
    int8_t j = 3;
    while (ipAddress+i && i<strlen(ipAddress))
    {
       char digit = ipAddress[i];
       if (isdigit(digit) == 0 && digit!='.'){
           return 0;
       }
        j=digit=='.'?j-1:j;
       ipbytes[j]= ipbytes[j]*10 + atoi(&digit);
        i++;
    }
    uint32_t a = ipbytes[3];
    uint32_t b =  ( uint32_t)ipbytes[2] << 8;
    uint32_t c =  ( uint32_t)ipbytes[1] << 16;
    uint32_t d =  ( uint32_t)ipbytes[0] << 24;
    __be32 result =  a+b+c+d;
    return result;
}

void commandShowIpPockets (char* string) {
    int finish = -1;
    char* resultFinish = strstr (string, isShowIpCount);
    finish = resultFinish-string;
    char buff[20]; char buffPiton[20];
    int index;
    for (index = 0; index < 20; index++){
        buff[index] = NULL;
        buffPiton[index] = NULL;
    }
    memcpy(buff, string+6,finish-6);
    int piton = inet_pton(AF_INET, buff, buffPiton);
    if (piton > 0) {
         printf ("\n");
        __be32 ip = getDecimalValueOfIPV4_String(buff);
        command = COMMAND_SEARCH_IP;
        searchIp = ip;
    }
    else
        printf ("ERROR : IP is NOT valid\n");
}

void commandHelp(){
        printf ("\n1. At first please select interface command : \"select iface [wlan0]\" for wi-fi \nor \"select iface [eth0]\" for Ethernet.");
        printf ("\n2. starting work command : \"start\" stopping work command : \"stop\".");
        printf ("\n3. show traffic data command : \"show\".");
        printf ("\n4. show number of packets received from ip address command : \"show [192.168.0.1] count\" for example.");
        printf ("\n5. save data command to file : \"save\".");
        printf ("\n6. close command : \"exit\".\n");
}

void showStartMessage(){
    printf ("\n help command : \"--help\"\n");
}

