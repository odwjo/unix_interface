#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "curr_time.h"
#define BUF_SIZE 256

char *currTime(const char *fmt)
{
    static char buf[BUF_SIZE];
    time_t t;
    struct tm *tmp;

    t = time(NULL);
    tmp = localtime(&t);
    if (tmp == NULL) {
        printf("error: localtime\n");
        exit(EXIT_FAILURE);
    }
    
    if (strftime(buf, sizeof(buf), fmt, tmp) == 0) {
        printf("error: strftime\n");
        exit(EXIT_FAILURE);
    }
    
    return buf;
}
