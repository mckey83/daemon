#include"processidentifier.h"
#include"errno.h"

void forkProcessIdentifier(int* processIdentifier){
    *processIdentifier = fork();
}

int isProcessIdentifierBroken(int processIdentifier) {
   return processIdentifier < 0;
}

int isProcessIdentifierChild(int processIdentifier) {
    return processIdentifier == 0;
}


int isProcessIdentifierParent(int processIdentifier) {
    return processIdentifier > 0;
}
