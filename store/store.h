#ifndef STORE_H
#define STORE_H
struct Store {
    struct Record** recordsPointers;
    struct Record* records;
    unsigned int fullSize;
    unsigned int quantity;
};



#endif // STORE_H
