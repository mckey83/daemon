#include "commands.h"
#include"store/store_simple.h"
#include"show/show.h"

#include <string.h>
#include"macro/ip_to_d_d_d_d.h"
#include <stdint.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
Test_MAIN( int testCounter = 0;)
#include <linux/types.h>
#include"is_command.h"

const char* isShowIp = "show [";
const char* isShowIpCount = "] count";

char* eth0Interface = "select iface [eth0]";
char* wlan0Interface = "select iface [wlan0]";
char* eth0InterfaceDaemon = "select_iface_[eth0]";
char* wlan0InterfaceDaemon = "select_iface_[wlan0]";
__u8* networkInterface;



pthread_t thread;
pthread_mutex_t* myMutex;

int commandAction;
int isSetInterfaceCommand = 0;
int isUsedThread = 0;
int isDaemonStart = 0;

void add (struct Store* store, struct Record* record, pthread_mutex_t* pThread_mutex_t);
__be32 getDecimalValueOfIPV4_String(char* ipAddress);


void commandInitialize(){
    commandAction = 1;
    initializeIsCommand(&isSetInterfaceCommand);
    myMutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)*1);
    pthread_mutex_init( myMutex, NULL);
    struct Store*  store = (struct Store*)malloc(sizeof(struct Store)*1);

    data = (struct Data*)malloc(sizeof(struct Data)*1);
    store->fullSize = 0;
    store->quantity = 0;
    store->records =  NULL;    

    data->store = store;
    data->storeAdd = add;
    data->pThread_mutex_t = myMutex;
    data->command = &commandAction;
    data->isDaemon = &isDaemonStart;
    initializeData(store,store->records);
    testStore(data, myMutex);
}

void commandSetDaemon(){
    data->isDaemon = 0;
}

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

void commandStart () {
    data->command = 1;
    if (!data->isDaemon){
        clearScreen();
    }
    int result;
    int a;
    result = pthread_create(&thread, NULL, snifferThread, &a);
    if (result != 0) {
        perror("ERROR : thread did not create");
    }
    isUsedThread = 1;
}

void commandStop (){
   data->command = 0;
}

void commandSettingInerface (char* string) {    
    if (isSetInterfaceCommand){
        commandExit();
    }
    if ( strcmp (string, eth0Interface) == 0 || strcmp (string, eth0InterfaceDaemon ) == 0 )
        networkInterface = "eth0";
    if ( strcmp (string, wlan0Interface) == 0 ||  strcmp (string, wlan0InterfaceDaemon) == 0 )
        networkInterface = "wlan0";
    isSetInterfaceCommand = 1;    
}

void commandExit(){
    commandStop();
    if (isUsedThread){
        pthread_join(thread, NULL);
        printf("sniffer closed \n");
    }
    else
        printf("sniffer did not use \n");
}

void * snifferThread(void * argument) {   
    startSniffer(networkInterface, data);
}

void commandSave(const char* fileName){
    save(fileName);
}

void commandLoad(const char* fileName){
    load(fileName);
}

void commandShow(){    
   commandShowStore(data->store);
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
        __be32 ip = getDecimalValueOfIPV4_String(buff);
        int quantityOfPackets = mySearch(ip);
        Test_MAIN( result_Test [testCounter++] = quantityOfPackets; )
        if ( quantityOfPackets > -1 )
            showIpPockets(buff,quantityOfPackets);
        else
             printf ("no Packets \n", ip);
    }
    else
        printf ("ERROR : IP is NOT valid\n");
}

__be32 getDecimalValueOfIPV4_String(char* ipAddress) {
    uint8_t ipbytes[4]={};
    int i =0;
    int8_t j=3;
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

void commandHelp(){
    showHelp();

}

