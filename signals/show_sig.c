#define _GNU_SOURCE
#include <signal.h>
#include <string.h>
#include <stdio.h>

void printSig(FILE *of)
{
    int sig, cnt;

    for (sig = 1; sig < NSIG; sig++) {
            fprintf(of, "%d <> (%s)\n", sig, strsignal(sig));
    }
}

int main()
{
    printSig(stdout);

    return 0;
}
