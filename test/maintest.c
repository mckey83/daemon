#include"maintest.h"

#include"store/store.h"

void testStore(struct Data* data, pthread_mutex_t* pThread_mutex_t){

    int len = 5;
    struct Record* record[len];
    int index;
     ;
    for (index = 0 ; index < len; index++) {
        record[index] = (struct Record*)malloc(sizeof(struct Record)*1);
        record[index]->sourceIP = 0;
        record[index]->quantityPockets = 0;
        record[index]->distanationIP = 0;
    }

    record[0]->sourceIP = 100;
    record[1]->sourceIP = 500;
    record[2]->sourceIP = 500;
    record[3]->sourceIP = 300;
    record[4]->sourceIP = 100;
printf("-----> 1\n");
    for (index = 0 ; index < len; index++) {
        data->storeAdd(data->store, record[index], pThread_mutex_t);
    }
    printf("-----> 2\n");
    if (
        data->store->records[0].sourceIP == 100 && data->store->records[0].quantityPockets == 2
        && data->store->records[1].sourceIP == 500 && data->store->records[1].quantityPockets == 2
        && data->store->records[2].sourceIP == 300 && data->store->records[2].quantityPockets == 1
        && data->store->quantity == 3 && data->store->fullSize == 3
            )
        printf("-----> test ok\n");
    else
        printf("-----> test is failed\n");
    commandShowStore(data->store, data->pThread_mutex_t);
}
