#include <libgen.h>
#include <unistd.h>
#include "tlpi_hdr.h"

#define BUF_SIZE 512

int main(int argc, char *argv[])
{
    char *t1, *t2;
    int j;
    char pathbuf[BUF_SIZE];

    errno = 0;
    getcwd(pathbuf, BUF_SIZE - 1);
    if (errno != 0)
        errExit("getcwd");
    printf("realpath: %s\n", pathbuf);
    for (j = 1; j < argc; j++) {
        t1 = strdup(argv[j]);
        if (t1 == NULL)
            errExit("strdup");
        t2 = strdup(argv[j]);
        if (t2 == NULL)
            errExit("strdup");

        printf("%s ==> %s + %s\n", argv[j], dirname(t1), basename(t2));

        free(t1);
        free(t2);
    }
    exit(EXIT_SUCCESS);
}
