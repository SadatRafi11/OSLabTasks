#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h> /* Standard I/O functions */
#include <stdlib.h> /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h> /* Prototypes for many system calls */
#include <errno.h> /* Declares errno and defines error constants */
#include <string.h> /* Commonly used string-handling functions */
#include <sys/wait.h>

int main() {
    int n = 0;
    pid_t pid = fork();

    if (pid < 0) {
        printf("Forking failed.\n");
    } else if (pid) {
        wait(NULL);
        n += 82;
        printf("parent: %d\n", n);
    } else {
        n += 170042082;
        printf("child: %d\n", n);
    }

    return 0;
}
