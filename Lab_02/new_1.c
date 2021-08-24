#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h> /* Standard I/O functions */
#include <stdlib.h> /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h> /* Prototypes for many system calls */
#include <errno.h> /* Declares errno and defines error constants */
#include <string.h> /* Commonly used string-handling functions */
#include <sys/wait.h>

int main(){
    pid_t pid;

    fflush(stdout);

    if ((pid = fork()) < 0) {
        printf("first one failed!\n");
    } else if (pid) {
        wait(NULL);
        printf("This is the first parent process\n");
        printf("parent: %d\ncurrent: %d\n", getppid(), getpid());
    } else if (!pid) {
        printf("This is the first child process\n");
        printf("parent: %d\ncurrent: %d\n", getppid(), getpid());
    }
    fflush(stdout);

    if ((pid = fork()) < 0) {
        printf("second one failed!\n");
    } else if (pid) {
        wait(NULL);
        printf("This is the second parent process\n");
        printf("parent: %d\ncurrent: %d\n", getppid(), getpid());
    } else if (!pid) {
        printf("This is the second child process\n");
        printf("parent: %d\ncurrent: %d\n", getppid(), getpid());
    }
    fflush(stdout);

    if ((pid = fork()) < 0) {
        printf("third one failed!\n");
    } else if (pid) {
        wait(NULL);
        printf("This is the third parent process\n");
        printf("parent: %d\ncurrent: %d\n", getppid(), getpid());
    } else if (!pid) {
        printf("This is the third child process\n");
        printf("parent: %d\ncurrent: %d\n", getppid(), getpid());
    }

    return 0;
}

