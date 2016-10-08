#include"store_simple.h"
#include"macro/ip_to_d_d_d_d.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Store* store;
struct Record* record;



void addSimple(pthread_mutex_t* myMutex);
void addPacketToOldIP();
void increaseStore(pthread_mutex_t* myMutex);
int isNewIP ();
int initializeData(struct Store* store_, struct Record* record_);
struct Record* getOldIP();

void add (struct Store* store_, struct Record* record_, pthread_mutex_t* myMutex){
    //printf("add\n");
    if (initializeData(store_, record_)){
        addData(myMutex);
    }
    else
        printf("did not initializeData in add");
}


int initializeData(struct Store* store_, struct Record* record_){
    store = store_;
    record = record_;
    return 1;
}

void addData(pthread_mutex_t* myMutex){
    //showStore ();
    // printf("----->addStore() \n");
    if (isNewIP()) {
        if (store->quantity < store->fullSize) {
            addSimple(myMutex);
        }
        else if (store->quantity == store->fullSize) {
            //  printf("----->increaseStore \n");
            increaseStore(myMutex);
            //  printf("----->addSimple ");
            addSimple(myMutex);            }
        //showStore ();
    }
    else {
        addPacketToOldIP();
    }
}

int isNewIP (){
    int index;
    for (index = 0; index < store->quantity; index++) {
        if (store->records[index].sourceIP == record->sourceIP ) {
            //printf("----->IP is old : \n");
            return 0;
        }
    }
    //printf("----->IP is new : \n");
    return 1;
}


void addPacketToOldIP() {
    struct Record* recordOldIP =  getOldIP();
    recordOldIP->quantityPockets = recordOldIP->quantityPockets + 1;
    //showRecord();
}

struct Record* getOldIP(){
    int index;
    for (index = 0; index < store->quantity; index++) {
        if (store->records[index].sourceIP == record->sourceIP )
            return &store->records[index];
    }
}


void addSimple(pthread_mutex_t* myMutex){
    // printf("----->addSimple ");
pthread_mutex_lock( myMutex );
    store->records[store->quantity] = *record;
    store->records[store->quantity].quantityPockets = store->records[store->quantity].quantityPockets +1;
    //showRecord ();
    store->quantity = store->quantity+1;
pthread_mutex_unlock( myMutex );
    //printf("----->addSimple ");
}

void increaseStore(pthread_mutex_t* myMutex) {
pthread_mutex_lock( myMutex );
    int start = store->fullSize;
    int finish = start * 2 + 1;
    store->fullSize = finish;
    struct Record* bufferRecords = (struct Record*)malloc(sizeof(struct Record)*store->fullSize);
    struct Record** bufferRecordsPointers = (struct Record**)malloc(sizeof(struct Record*)*store->fullSize);
    unsigned index = 0;
    for (; index < store->quantity; index++){
        bufferRecords[index] = store->records[index];
        bufferRecordsPointers[index] = store->recordsPointers[index];
    }
    if (store->records!=NULL) {
        free (store->records);
        store->records = NULL;
    }
    if (store->recordsPointers != NULL) {
        free (store->recordsPointers);
        store->recordsPointers = NULL;
    }
    store->records = bufferRecords;
    store->recordsPointers = bufferRecordsPointers;
pthread_mutex_unlock( myMutex );
}

void save(pthread_mutex_t* myMutex2){

    FILE *fp;
    size_t count =0;
    fp = fopen("sample", "wb");
    if(fp == NULL) {
        perror("ошибка открытия пример.txt");
        return EXIT_FAILURE;
    }
    int sizeStore = sizeof(struct Store);
    int sizeRecord = sizeof(struct Record);
pthread_mutex_lock( myMutex2 );
    int sizeTotal = sizeof(struct Store) + sizeof(struct Record)*store->fullSize;
    printf("sizeof Store = %d байт.\nsizeof Record = %d байт.\nколичество записей = %d.\nsizeof Total = %d байт.\n",
            sizeStore, sizeRecord,store->fullSize, sizeTotal );
    count = fwrite(store, sizeof(struct Store), 1, fp);
    fseek(fp, sizeof(struct Store), SEEK_SET);
    count = fwrite(store->records, sizeRecord*store->fullSize, 1, fp);
    printf("Записано %d байт. fclose(fp) %s.\n", count, fclose(fp) == 0 ? "успешно" : "с ошибкой");
pthread_mutex_unlock( myMutex2 );
}

void load(pthread_mutex_t* myMutex2){
    printf("load() \n");

    FILE* f = fopen("sample", "rb");
    if (f != NULL){
        struct Store* storeForShow = (struct Store*)malloc(sizeof(struct Store)*1);
        storeForShow->fullSize = 0;
        storeForShow->quantity = 0;
        storeForShow->records = 0;
        storeForShow->recordsPointers = 0;
        fread (storeForShow, sizeof(struct Store), 1, f);
        struct Record* bufferRecords = (struct Record*)malloc(sizeof(struct Record)*storeForShow->fullSize);
        fseek(f, sizeof(struct Store), SEEK_SET);
        fread (bufferRecords, sizeof(struct Record)*storeForShow->fullSize, 1, f);
        printf("fclose(fp) %s.\n", fclose(f) == 0 ? "успешно" : "с ошибкой");

 pthread_mutex_lock( myMutex2 );
        store = storeForShow;
        store->records = bufferRecords;
 pthread_mutex_unlock( myMutex2 );
        commandShowStore(store, myMutex2);
    }
    else printf("No file!!!") ;
}
