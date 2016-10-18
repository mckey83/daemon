#ifndef WORKWITHFILE_H
#define WORKWITHFILE_H


int File_write(const char *fileName, const void *data, const int dataSize, const char* openParameter);
void File_read();
int sessionPidRead();

#endif // WORKWITHFILE_H
