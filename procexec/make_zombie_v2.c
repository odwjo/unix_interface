#include <signal.h>
#include <libgen.h>
#include <sys/wait.h>
#include "tlpi_hdr.h"

#define CMD_SIZE 200
char cmd[CMD_SIZE];

void sigchldSigaction(int sig, siginfo_t *si, void *ucontext) 
{
    if (WIFEXITED(si->si_status)) { 
        system(cmd);
        if (kill(si->si_pid, SIGKILL) == -1)
            errMsg("kill");

        printf("After sending SIGKILL to zombie (PID=%ld):\n",
            (long) si->si_pid);
        system(cmd);
    }
}

int main(int argc, char *argv[])
{
    pid_t childPid;
    struct sigaction sa;
    sigset_t st, oldst;

    sigfillset(&sa.sa_mask);
    sa.sa_sigaction = sigchldSigaction;
    sa.sa_flags = SA_SIGINFO;

    sigaction(SIGCHLD, &sa, NULL);
    
    sigemptyset(&st);
    sigaddset(&st, SIGCHLD);
    sigprocmask(SIG_BLOCK, &st, &oldst);
    sigdelset(&oldst, SIGCHLD);

    setbuf(stdout, NULL);

    printf("Parent Pid=%ld\n", (long) getpid());
    
    snprintf(cmd, CMD_SIZE, "ps | grep %s", basename(argv[0]));
    cmd[CMD_SIZE - 1] = '\0';

    switch(childPid = fork()) {
        case -1:
            errExit("fork");
        case 0:
            printf("child (Pid=%ld) exiting\n", (long) getpid());
            _exit(EXIT_SUCCESS);
        default:
            if (sigsuspend(&oldst) == -1 && errno != EINTR)
                errExit("sigsuspend");
            exit(EXIT_SUCCESS);
    }
}
