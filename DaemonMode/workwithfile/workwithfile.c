#include"workwithfile.h"
#include"DaemonMode/tests/test_work_with_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0;


DEBUG_TEST_ACTION(int isResult = 0;)
DEBUG_TEST_INFO(int i = 0;)

int File_write(const char* fileName, const void *data, const int dataSize , const char *openParameter){
    FILE* file;
    DEBUG_TEST_INFO(printf("%d.File_write fopen() \n", i++));
    file = fopen(fileName, openParameter);
    DEBUG_TEST_INFO(printf("%d.File_write if(file) \n", i++));
    if (file) {
        DEBUG_TEST_INFO(printf("%d.File_write fwrite() dataSize = %d, data = %s\n", i++, dataSize, data));
        fwrite(data, sizeof(char), dataSize, file);
        DEBUG_TEST_INFO(printf("%d.File_write close() \n", i++));
        int resultFile_close = fclose(file);
        DEBUG_TEST_ACTION(isResult = test_writeProcessIdentifierToFile(fileName, data,  dataSize);)
        if (!resultFile_close) {
        DEBUG_TEST_RESULT( if (isResult)
                        printf("++++>File_write() - OK\n");
                   else
                      printf("---->File_write() - IS FALIED\n");)
            return true;
        }else {
            DEBUG_TEST_INFO(printf("%d.File_write FALSE \n"));
            return false;
        }
   }else
        return false;
}

DEBUG_TEST_ACTION(
int test_writeProcessIdentifierToFile(const char*fileNameTest, const char* dataTest,  const int bufferLen) {
    DEBUG_TEST_INFO(printf("%d.File_write test_writeProcessIdentifierToFile \n", i++));
    FILE* fileTest;
    char buffer[bufferLen];
    int index = 0;for(;index < bufferLen; index++) buffer[index] = "\0";
    fileTest = fopen(fileNameTest, "r+");
    fread(&buffer, sizeof(char), bufferLen, fileTest);
    DEBUG_TEST_INFO(printf("------------>read = %s\n", buffer);)
    if (fileTest) {
        if (strcmp(buffer, dataTest) == 0 )
            if (!fclose(fileTest))
                return true;
            else
                return false;
    }else
        return false;
}
)

int sessionPidRead(){
    FILE* fileTest;
    const char* fileNamePid = "sessionPid.log";
    int bufferLen =10;
    char buffer[bufferLen];
    int index = 0;for(;index < bufferLen; index++) buffer[index] = "\0";
    fileTest = fopen(fileNamePid, "r+");
    if(fileTest){
    fread(&buffer, sizeof(char), bufferLen, fileTest);
    DEBUG_TEST_INFO(printf("------------>read = %s\n", buffer);)
    if (!fclose(fileTest)) {
        return atoi(buffer);
    }
    } else
        printf("error open file!!!");
}
