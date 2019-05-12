#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main()
{
    int tmp;

    switch (fork()) {
        case -1:
            printf("error fork");
            exit(EXIT_FAILURE);
        case 0:
            _exit(-1);
        default:
            wait(&tmp);
            printf("child exit(-1), parent recieve %d\n",
                    WEXITSTATUS(tmp));
            exit(EXIT_SUCCESS);
    }
}

