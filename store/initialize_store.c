#include"initialize_store.h"

void initializeStore(struct Store* store){
    store->fullSize = 0;
    store->quantity = 0;
    store->records = 0;
    store->recordsPointers = 0;
}
