#include"timer.h"
#include <sys/time.h>
#include <stdio.h>
#include <string.h>

inline long long gettimeus( ){
    struct timeval tv;
    gettimeofday ( &tv, NULL );
    return (long long) tv.tv_sec*1000000LL + (long long) tv.tv_usec;
}
