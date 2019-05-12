#include <sys/wait.h>
#include <unistd.h>
#include "tlpi_hdr.h"
#include "curr_time.h"

int main()
{
    pid_t childPid;

    setbuf(stdout, NULL);

    switch(childPid = fork()) {
        case -1:
            errExit("fork");
        case 0:
            switch (childPid = fork()) {
                case -1:
                    errExit("fork");
                case 0:
                    sleep(1);
                    printf("%s: After parent exit: pid=%ld\n", currTime("%T"), (long) getppid());
                    sleep(2);
                    printf("%s: After grand waited: pid=%ld\n", currTime("%T"), (long) getppid());
                    _exit(EXIT_SUCCESS);
                default:
                    _exit(EXIT_SUCCESS);
            }
        default:
            sleep(2);
            printf("%s Call wait:\n", currTime("%T"));
            wait(NULL);
            exit(EXIT_SUCCESS);
    }
}
