#include <sys/resource.h>
#include <sys/wait.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    int childPid;
    struct rusage ru;
    char *filename;

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s command arg...\n", argv[0]);

    childPid = fork();

    filename = strrchr(argv[1], '/');
    if (filename == NULL)
        filename = argv[1];

    switch (childPid) {
        case -1:
            errExit("fork");
        case 0:
            execvp(argv[1], &argv[1]);
            errExit("execvp");
        default:
            break;
    }
    
    if (wait(NULL) == -1)
        errExit("wait");

    if (getrusage(RUSAGE_CHILDREN, &ru) == -1)
        errExit("getrusage");

    printf("command %s used %ld.%06lds in user sapce\n",argv[1],
            ru.ru_utime.tv_sec, ru.ru_utime.tv_usec);
    printf("command %s used %ld.%06lds in kernel sapce\n",argv[1],
            ru.ru_stime.tv_sec, ru.ru_stime.tv_usec);
    exit(EXIT_SUCCESS);
}
