#include "tlpi_dhr.h"

int main(int argc, char *argv[])
{
    char *envVec[] = { "GREET=SALUT", "BYE=ADIEU", (char*) NULL };
    char *filename;

    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s pathname\n", argv[0]);
    
    filename = strrchr(argc[1], '/');
    if (filename != NULL)
        filename ++;
    else
        filename = argv[1];

    execle(argv[1], filename, "hello world", (char *)NULL, envVec);
    errExit("execle");
}

