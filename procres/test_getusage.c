#include <sys/wait.h>
#include <sys/resource.h>
#include "tlpi_hdr.h"

int main()
{
    int childPid;
    struct rusage rb, ra;
    int i, m;

    if (getrusage(RUSAGE_CHILDREN, &rb) == -1)
        errExit("getrusage");

    childPid = fork();
    switch(childPid) {
        case -1:
            errExit("fork");
        case 0:
            for (i = 0; i != 1000000; ++i)
                m += i * i;
            _exit(EXIT_SUCCESS);
        default:
            wait(NULL);
            if (getrusage(RUSAGE_CHILDREN, &ra) == -1)
                errExit("getrusage");
    }
    printf("Befor: RUSAGE_CHILDREN: %ld.%06ld\n", rb.ru_utime.tv_sec, 
                                                rb.ru_stime.tv_usec);
    printf("After: RUSAGE_CHILDREN: %ld.%06ld\n", ra.ru_utime.tv_sec, 
                                                ra.ru_stime.tv_usec);
    exit(EXIT_SUCCESS);
}
