#include"show.h"

void commandShowStore(struct Store* store, pthread_mutex_t* myMutex){
    printf ("\033[0d\033[2J");
    pthread_mutex_lock( myMutex );
    int index;
    for (index = 0; index < store->quantity; index++){
        showRecordMain (store->records[index]);
    }
    pthread_mutex_unlock( myMutex );
    printf(" store->fullSize = %d, store->quantity = %d\n", store->fullSize, store->quantity);
}



void showRecordMain (struct Record record) {
    printf("src ip: %d.%d.%d.%d | dst ip: %d.%d.%d.%d, quantityPockets = %d \n", NIPQUAD(record.sourceIP), NIPQUAD(record.distanationIP), record.quantityPockets );
}
