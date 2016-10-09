#include"show.h"

void commandShowStore(struct Store* store){
    printf ("\033[0d\033[2J");    
    int index;
    for (index = 0; index < store->quantity; index++){
        showRecordMain (store->records[index]);
    }
    printf(" store->fullSize = %d, store->quantity = %d\n", store->fullSize, store->quantity);
}



void showRecordMain (struct Record record) {
    printf("src ip: %d.%d.%d.%d | dst ip: %d.%d.%d.%d, quantityPockets = %d \n", NIPQUAD(record.sourceIP), NIPQUAD(record.distanationIP), record.quantityPockets );
}

void showStartMessage(){
    printf ("Please enter command, for help type : --help \n");
}

void  showIpPockets (const char* buff, int  quantityOfPackets){
   printf ("ip = %s quantity of packets = %d\n", buff, quantityOfPackets);
}

void showHelp(){
    clearScreen();
    printf ("\n1. At first please select interface command : \"select iface [wlan0]\" for wi-fi \nor \"select iface [eth0]\" for Ethernet.");
    printf ("\n2. starting work command : \"start\" stopping work command : \"stop\".");
    printf ("\n3. show traffic data command : \"show\".");
    printf ("\n4. show number of packets received from ip address command : \"show [192.168.0.1] count\" for example.");
    printf ("\n5. save data command to file : \"save\".");
    printf ("\n6. close command : \"exit\".\n");
}

void clearScreen(){
    printf ("\033[0d\033[2J");
}
