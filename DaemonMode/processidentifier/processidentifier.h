#ifndef PROCESSIDENTIFIER_H
#define PROCESSIDENTIFIER_H

void forkProcessIdentifier(int* processIdentifier);
int isProcessIdentifierBroken(int processIdentifier);
int isProcessIdentifierChild(int processIdentifier);
int isProcessIdentifierParent(int processIdentifier);


#endif // PROCESSIDENTIFIER_H
