#include"store_test.h"

#include"store/store.h"
void testStore(struct Data* data, pthread_mutex_t* pThread_mutex_t){

    int len = 10;
    struct Record* record[len];
    int index;
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
    record[5]->sourceIP = getDecimalValueOfIPV4_String("192.168.0.1"); record[5]->quantityPockets = 125;
    record[6]->sourceIP = getDecimalValueOfIPV4_String("192.168.120.91"); record[6]->quantityPockets = 226;
    record[7]->sourceIP = getDecimalValueOfIPV4_String("0.0.1.11"); record[7]->quantityPockets = 337;
    record[8]->sourceIP = getDecimalValueOfIPV4_String("0.10.10.91"); record[8]->quantityPockets = 448;
    record[9]->sourceIP = getDecimalValueOfIPV4_String("0.0.0.1"); record[9]->quantityPockets = 999;
    for (index = 0 ; index < len; index++) {
        data->storeAdd(data->store, record[index], pThread_mutex_t);
    }    
    if (
        data->store->records[0].sourceIP == 100 && data->store->records[0].quantityPockets == 2
        && data->store->records[1].sourceIP == 300 && data->store->records[1].quantityPockets == 1
        && data->store->records[2].sourceIP == 500 && data->store->records[2].quantityPockets == 2
        && data->store->quantity == 8 && data->store->fullSize == 15
            )
        printf("-----> store test ok\n");
    else
        printf("-----> test is failed\n");
    commandShowStore(data->store, data->pThread_mutex_t);
}
