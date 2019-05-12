#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

static void *threadf(void *p)
{
    int s;
    if ((s = pthread_join(pthread_self(), NULL)) != 0)
        printf("error happend when call pthread_join\n");
    printf("haha, join takes no effect\n");
    return NULL;
}

int main()
{
    pthread_t thr;
    if (pthread_create(&thr, NULL, threadf, NULL) != 0)
        printf("error happend when call pthread_create");

    printf("this is in main()");
    sleep(3);
    printf("still in main()");

    return 0;
}
