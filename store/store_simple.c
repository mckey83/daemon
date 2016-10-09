#include"store_simple.h"
#include"macro/ip_to_d_d_d_d.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"show/show.h"
#include"command/commands.h"

//struct Store* store;
//struct Record* record;



void addSimple(pthread_mutex_t* myMutex);
void addPacketToOldIP();
void increaseStore(pthread_mutex_t* myMutex);
int isNewIP ();
int initializeData(struct Store* store_, struct Record* record_);
struct Record* getOldIP();

void add (struct Store* store_, struct Record* record_, pthread_mutex_t* myMutex){    
    if (initializeData(store_, record_)){
        addData(myMutex);
    }
    else
        printf("did not initializeData in add");
}


int initializeData(struct Store* store_, struct Record* record_){
    store = *store_;
    record = record_;    
    return 1;
}

void addData(pthread_mutex_t* myMutex){
    if (isNewIP()) {
        if (store->quantity < store->fullSize) {
            addSimple(myMutex);
        }
        else if (store->quantity == store->fullSize) { 
            increaseStore(myMutex);
            addSimple(myMutex);
        }
        sortingIp();
    }
    else {
        addPacketToOldIP();
    }
}

int isNewIP (){
    int index;
    for (index = 0; index < store->quantity; index++) {
        if (store->records[index].sourceIP == record->sourceIP ) {
            return 0;
        }
    }
    return 1;
}


void addPacketToOldIP() {
    struct Record* recordOldIP =  getOldIP();
    recordOldIP->quantityPockets = recordOldIP->quantityPockets + 1;    
}

struct Record* getOldIP(){
    int index;
    for (index = 0; index < store->quantity; index++) {
        if (store->records[index].sourceIP == record->sourceIP )
            return &store->records[index];
    }
}

void addSimple(pthread_mutex_t* myMutex){    
pthread_mutex_lock( myMutex );
    store->records[store->quantity] = *record;
    store->records[store->quantity].quantityPockets = store->records[store->quantity].quantityPockets +1;    
    store->quantity = store->quantity+1;
pthread_mutex_unlock( myMutex );   
}

void increaseStore(pthread_mutex_t* myMutex) {
pthread_mutex_lock( myMutex );
    int start = store->fullSize;
    int finish = start * 2 + 1;
    store->fullSize = finish;
    struct Record* bufferRecords = (struct Record*)malloc(sizeof(struct Record)*store->fullSize);    
    unsigned index = 0;
    for (; index < store->quantity; index++){
        bufferRecords[index] = store->records[index];        
    }
    if (store->records!=NULL) {
        free (store->records);
        store->records = NULL;
    }   
    store->records = bufferRecords;


pthread_mutex_unlock( myMutex );
}

void save(const char* fileName) {
    FILE *fp;
    size_t count =0;
    fp = fopen(fileName, "wb");
    if(fp == NULL) {
        perror("error don't open for save");
        return EXIT_FAILURE;
    }    
    int sizeRecord = sizeof(struct Record);     
    count = fwrite(store, sizeof(struct Store), 1, fp);
    fseek(fp, sizeof(struct Store), SEEK_SET);
    count = fwrite(store->records, sizeRecord*store->fullSize, 1, fp);
    printf("save %s.\n", fclose(fp) == 0 ? "ok" : "error");
}

void load(const char* fileName){
    FILE* f = fopen(fileName, "rb");
    if (f != NULL){
        struct Store* storeForShow = (struct Store*)malloc(sizeof(struct Store)*1);
        storeForShow->fullSize = 0;
        storeForShow->quantity = 0;
        storeForShow->records = 0;
        fread (storeForShow, sizeof(struct Store), 1, f);
        struct Record* bufferRecords = (struct Record*)malloc(sizeof(struct Record)*storeForShow->fullSize);
        fseek(f, sizeof(struct Store), SEEK_SET);
        size_t result = fread (bufferRecords, sizeof(struct Record)*storeForShow->fullSize, 1, f);
        printf("load %s result = %d\n", fclose(f) == 0 ? "ok" : "error", result);
        *store = *storeForShow;
        //*store->records = *bufferRecords;
    }
    else printf("No file") ;
}

int mySearch (__be32 ip) {
    const int N=store->quantity;
    int left=0, right = N, mid;
    while (left <= right)     {
        mid = left + ( right - left )  /2;
        if (ip < store->records[mid].sourceIP) right = mid - 1;
        else if (ip > store->records[mid].sourceIP) left = mid + 1;
        else return store->records[mid].quantityPockets;
    }
    return -1;
}


void sortingIp() {
    int(*pFunc)(int, int);
    pFunc = Asc;
    struct Record tmp;
    int m,i;
    for ( m = 0; m < store->quantity - 1; m++) {
        for (i = 0; i < store->quantity - 1 - m; i++) {
            if ( pFunc (store->records[i].sourceIP, store->records[i+1].sourceIP) == 1 ) {
                tmp = store->records[i];
                store->records[i] = store->records[i+1];
                store->records[i+1] = tmp;
            }
        }
    }
}
int Asc(int left, int right){
    return left > right;
}



