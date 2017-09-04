
#include <stdio.h>
#include "config.h"

#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#else
#include <time.h>
#endif

int main(){

    printf("Try GNU Build System.\n");
    
    double sec;

#ifdef HAVE_GETTIMEOFDAY
    struct timeval tv;
    gettimeofday(&tv, NULL);
    sec = tv.tv_sec;
    sec += tv.tv_usec / 1000000.0;
#else
    sec = time(NULL);
#endif
    printf("current time seconds: %f\n", sec);

    return 0;
}

