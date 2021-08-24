#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h> /* Standard I/O functions */
#include <stdlib.h> /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h> /* Prototypes for many system calls */
#include <errno.h> /* Declares errno and defines error constants */
#include <string.h> /* Commonly used string-handling functions */
#include <sys/wait.h>

void printFibonacci(int n) {

    int x1 = 0, x2 = 1;
    printf("%d %d ", 0, 1);
    int sum = x1 + x2;
    for (int i = 0; i < n - 2; i++) {
        printf("%d ", sum);
        x1 = x2;
        x2 = sum;
        sum = x1 + x2;
    }
    printf("\n");
}

int main() {
    int x = 0;
    printf("\nEnter the number of terms: ");
    scanf("%d", &x);

    while (x < 0) {
        printf("\nCan't be negative.\nEnter the number of terms again: ");
        scanf("%d", &x);
    }

    fflush(stdout);
    pid_t pid = fork();

    if (pid < 0) {
        printf("\nForking failed.\n");
    } else if (pid) {
        wait(NULL);
    } else {
        printFibonacci(x);
    }

    return 0;
}

