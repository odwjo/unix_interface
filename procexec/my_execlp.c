#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

extern char **environ;

int my_execlp(const char* file, const char *arg, ...) {
    va_list ap;
    int argsz, argindex;
    size_t sz;
    char *tmp, *tmparg;
    char *path;
    long path_max, arglen;
    char **args;
/*
    path_max = pathconf(".", _PC_PATH_MAX);
    if (path_max == -1) {
        printf("Error: pathconf\n");
        exit(EXIT_FAILURE);
    }

    path = (char *) malloc(path_max);
    if (path == NULL) {
        printf("Error: malloc\n");
        exit(EXIT_FAILURE);
    }

    if (NULL == getcwd(path, path_max)) {
        printf("Error: getcwd\n");
        exit(EXIT_FAILURE);
    }

    if (file[0] != '/' && NULL == strncat(path, file, path_max)) {
        printf("Error: strncat\n");
        exit(EXIT_FAILURE);
    }
*/
    if (NULL == arg) {
        //args = NULL;
        execve(file, NULL, environ);
        
        if (errno == ENOEXEC) {
            args = (char **) malloc(3 * sizeof(char *));
            if (args == NULL) {
                printf("Error: malloc\n");
                exit(EXIT_FAILURE);
            }
            //tmp = (char *)malloc(strlen(file + 1));
            //strcpy(tmp, file);
            args[0] = "sh";
            args[1] = file;
            args[2] = NULL;
            
            printf("Just for test: file -> %s ,second : %s\n", args[0],
                  args[1] == NULL ? "YES" : "NO");

            execve("/bin/sh", args, environ);
        }
        
        printf("Error: execve\n");
        exit(EXIT_FAILURE);
    }

    argsz = 2;
    va_start(ap, arg);
    while(va_arg(ap, char *))
        argsz ++;
    argsz ++;
    va_end(ap);
    argsz++; 
    args = (char **)malloc(argsz * sizeof (char *));
    if (args == NULL) {
        printf("Error: malloc\n");
        exit(EXIT_FAILURE);
    }
    args[0] = "sh";
    args[1] = file;
    args[2] = arg;
    argindex = 3;

    va_start(ap, arg);
    while(tmparg = va_arg(ap, char *)) {
        arglen = strlen(tmparg);
        if (-1 != arglen) {
            tmp = (char *)malloc(arglen + 1);
            
            if (tmp == NULL) {
                printf("Error: malloc\n");
                exit(EXIT_FAILURE);
            }

            strcpy(tmp, tmparg);

            args[argindex++] = tmp;
            
        } else {
            printf("Error: strlen\n");
            exit(EXIT_FAILURE);
        }
    }
    va_end(ap);

    args[argindex] = NULL;

    execve(file, &args[1], environ);
  
    if (errno == ENOEXEC) {
        execve("/bin/sh", args, environ);
    }
    
    printf("Error: execve\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    /*
    char *file = "/bin/sh";
    char *args[2] ;
    args[1] = "./test.sh";
    args[2] = NULL;
    execve(file, args,  NULL);
    */
    my_execlp("./test.sh", (char *)NULL);

    exit(EXIT_FAILURE);
}
