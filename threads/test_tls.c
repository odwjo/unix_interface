#define _DEFAULT_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define errExit(f, s) do{\
    printf("error on call %s: %s\n", f,  strerror(s));\
    exit(EXIT_FAILURE);\
    }while(0)


static __thread int gg;

static void *threadFunc(void *arg)
{
    gg = 7;
    printf("In other thread, gg = %d\n", gg);
    return NULL;
}

int main(int argc, char *argv[])
{
    int s;
    pthread_t td;
    gg = 6;
    printf("In main thread: gg = %d\n", gg);
    printf("About to call other thread\n");
    s = pthread_create(&td, NULL, threadFunc, NULL);
    if (s != 0) {
        errExit("pthread_create", s);
    }
    s = pthread_join(td, NULL);
    if (s != 0){
        errExit("pthread_join", s);
    }
    printf("After other thread ended: gg = %d\n", gg);
    exit(EXIT_SUCCESS);
}
