#include"store_simple.h"
#include"DaemonMode/macro/ip_to_d_d_d_d.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include"DaemonMode/tests/test_simple_store.h"


struct Store {
    struct Record* records;
    unsigned int fullSize;
    unsigned int quantity;
} Simple_Store;




void addPacketToOldIP(struct Record *record);

int isNewIP ();
void increaseStore();
void addSimple(struct Record *record);
void load();
void sortingIp();
int Asc(__be32 left, __be32 right);
int mySearch (__be32 ip);
struct Record* getOldIP(struct Record *record);



int initializeStore(){
    Simple_Store.fullSize = 0;
    Simple_Store.quantity = 0;
    Simple_Store.records = 0;
    load();
    return 1;
}

int addData(struct Record *record){
    if (isNewIP(record)) {
        if (Simple_Store.quantity < Simple_Store.fullSize) {
            addSimple(record);
        }
        else if (Simple_Store.quantity == Simple_Store.fullSize) {
            increaseStore();
            addSimple(record);
        }
       sortingIp();
    }
    else {
       addPacketToOldIP(record);
    }
    return 1;
}

int isNewIP (struct Record *record){
    if (Simple_Store.fullSize == 0) {
        return 1;
    }
    if (mySearch (record->sourceIP) > -1 )
        return 0;
    else
        return 1;
}

void addSimple(struct Record *record){
                                                                                                                                                                DEBUG_TEST_INFO(printf("Simple_Store.quantity = %d, Simple_Store.fullSize = %d. pid = %d \n",Simple_Store.quantity, Simple_Store.fullSize, getpid());)
    Simple_Store.records[Simple_Store.quantity] = *record;
    Simple_Store.records[Simple_Store.quantity].quantityPockets = Simple_Store.records[Simple_Store.quantity].quantityPockets +1;
    Simple_Store.quantity = Simple_Store.quantity+1;
}

void increaseStore() {
    int start = Simple_Store.fullSize;
    int finish = start * 2 + 1;
    Simple_Store.fullSize = finish;
    struct Record* bufferRecords = (struct Record*)malloc(sizeof(struct Record)*Simple_Store.fullSize);
    unsigned index = 0;
    for (; index < Simple_Store.quantity; index++){
        bufferRecords[index] = Simple_Store.records[index];
    }
    if (Simple_Store.records!=NULL && Simple_Store.fullSize == 0) {
        free (Simple_Store.records);
        Simple_Store.records = NULL;
    }
    Simple_Store.records = bufferRecords;
                                                                                                                                                            DEBUG_TEST_INFO(printf("Store_Simple_increaseStore() END \n");)
}

void addPacketToOldIP(struct Record *record) {
    struct Record* recordOldIP =  getOldIP(record);
    recordOldIP->quantityPockets = recordOldIP->quantityPockets + 1;
}

struct Record* getOldIP(struct Record *record){
    int index;
    for (index = 0; index < Simple_Store.quantity; index++) {
        if (Simple_Store.records[index].sourceIP == record->sourceIP )
            return &Simple_Store.records[index];
    }
}

void save() {
                                                                                                                                                                DEBUG_TEST_INFO(printf("------------------SAVE-------------------- \n");)
    const char* fileName = "data.snf";
    FILE *fp;
    fp = fopen(fileName, "w+");
    if(fp == NULL) {
        perror("error don't open for save");
        return EXIT_FAILURE;
    }
    int lenStore = sizeof(struct Store);
    int lenRecords = sizeof(struct Record)*Simple_Store.fullSize;
    int lenOfBuffer = lenStore + lenRecords;
    char* buff = (char*)malloc(lenOfBuffer);
    memcpy(buff, &Simple_Store, lenStore);
    memcpy(buff+sizeof(struct Store), Simple_Store.records, lenRecords);
    fwrite(buff, 1, lenOfBuffer, fp);
    fclose (fp);
    free(buff);
}

load(){
                                                                                                                                                                DEBUG_TEST_INFO(printf("------------------Load-------------------- \n");)
    const char* fileName = "data.snf";
    FILE* f = fopen(fileName, "rb");
    if (f != NULL){
        struct Store* storeForShow = (struct Store*)malloc(sizeof(struct Store)*1);
        storeForShow->fullSize = 0;
        storeForShow->quantity = 0;
        storeForShow->records = 0;
        fread (storeForShow, sizeof(struct Store), 1, f);
        struct Record* bufferRecords = (struct Record*)malloc(sizeof(struct Record)*storeForShow->fullSize);
        fseek(f, sizeof(struct Store), SEEK_SET);
        fread (bufferRecords, sizeof(struct Record), storeForShow->fullSize, f);
        fclose (f);
        if(Simple_Store.records !=0 ) free(Simple_Store.records);
        storeForShow->records = bufferRecords;
        Simple_Store.quantity = storeForShow->quantity;
        Simple_Store.fullSize = storeForShow->fullSize;
        Simple_Store.records = storeForShow->records;
        sortingIp();
                                                                                                                                                            DEBUG_TEST_INFO(int index; for (index = 0; index < Simple_Store.quantity; index++){printf("src ip: %d.%d.%d.%d | dst ip: %d.%d.%d.%d, quantity = %d, ip = %d \n", NIPQUAD(Simple_Store.records[index].sourceIP),     NIPQUAD(Simple_Store.records[index].distanationIP), Simple_Store.records[index].quantityPockets, Simple_Store.records[index].sourceIP);}printf("Simple_Store.fullSize = %d, Simple_Store.quantity = %d\n", Simple_Store.fullSize, Simple_Store.quantity);        printf("------------------Load-------------------- OK \n");)
    }
    else printf("No file") ;
}

int mySearch (__be32 ip) {
    const int N=Simple_Store.quantity;
    int left=0, right = N, mid;
    while (left <= right)     {
        mid = left + ( right - left )  /2;
        if (ip < Simple_Store.records[mid].sourceIP) right = mid - 1;
        else if (ip > Simple_Store.records[mid].sourceIP) left = mid + 1;
        else return Simple_Store.records[mid].quantityPockets;
    }
    return -1;
}

void sortingIp() {
    int(*pFunc)(__be32, __be32);
    pFunc = Asc;
    struct Record* tmp = (struct Record*)malloc(sizeof(struct Record)*1);
    int m,i;
    for ( m = 0; m < Simple_Store.quantity - 1; m++) {
        for (i = 0; i < Simple_Store.quantity - 1 - m; i++) {
            if ( pFunc (Simple_Store.records[i].sourceIP, Simple_Store.records[i+1].sourceIP) == 1 ) {
                *tmp = Simple_Store.records[i];
                Simple_Store.records[i] = Simple_Store.records[i+1];
                Simple_Store.records[i+1] = *tmp;
            }
        }
    }
    free(tmp);
}

int Asc(__be32 left,__be32 right){
    return left > right;
}

void Store_show(){
    int index; for (index = 0; index < Simple_Store.quantity; index++){
        printf("src ip: %d.%d.%d.%d | dst ip: %d.%d.%d.%d, quantity = %d, ip = %d \n",
               NIPQUAD(Simple_Store.records[index].sourceIP),
               NIPQUAD(Simple_Store.records[index].distanationIP),
               Simple_Store.records[index].quantityPockets,
               Simple_Store.records[index].sourceIP);
    }
    printf("Simple_Store.fullSize = %d, Simple_Store.quantity = %d\n", Simple_Store.fullSize, Simple_Store.quantity);
}

Store_searchIp (__be32* searchIp){
    printf ("Store_searchIp searchIp = %llu\n", *searchIp);
    int result = mySearch(*searchIp);
    if (result > -1 )
        printf("src ip: %d.%d.%d.%d quantity of pockets =%d \n", NIPQUAD(*searchIp), result );
    else
        printf("src ip: %d.%d.%d.%d not in store \n", NIPQUAD(*searchIp) );

}

