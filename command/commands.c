#include "commands.h"
#include"store/store_simple.h"

char* eth0Interface = "select iface [eth0]";
char* wlan0Interface = "select iface [wlan0]";
__u8* networkInterface;

struct Data* data;

pthread_t thread;
pthread_mutex_t* myMutex;
pthread_mutex_t* myMutex2;
int commandAction;
int isSetInterfaceCommand = 0;
int isUsedThread = 0;

void add (struct Store* store, struct Record* record, pthread_mutex_t* pThread_mutex_t);

void commandInitialize(){
    commandAction = 1;
    initializeIsCommand(&isSetInterfaceCommand);
    myMutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)*1);
    pthread_mutex_init( myMutex, NULL);
    struct Store*  store = (struct Store*)malloc(sizeof(struct Store)*1);

    myMutex2 = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)*1);
    pthread_mutex_init( myMutex2, NULL);

    data = (struct Data*)malloc(sizeof(struct Data)*1);
    store->fullSize = 0;
    store->quantity = 0;
    store->records = 0;
    store->recordsPointers = 0;

    data->store = store;
    data->storeAdd = add;
    data->pThread_mutex_t = myMutex;
    data->command = &commandAction;
    testStore(data, myMutex);
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
    printf ("\033[0d\033[2J");
    printf("commandStart \n");
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
    printf("commandSettingInerface \n");
    if (isSetInterfaceCommand){
        commandExit();
    }
    if ( strcmp (string, eth0Interface) == 0 ) networkInterface = "eth0";
    if ( strcmp (string, wlan0Interface) == 0 ) networkInterface = "wlan0";
    isSetInterfaceCommand = 1;
    printf("commandSettingInerface -OK \n");
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

void commandSave(){
    save(myMutex2);
}

void commandLoad(){
    load(myMutex2);
}

void commandShow(){
    commandShowStore(data->store, myMutex);
}

