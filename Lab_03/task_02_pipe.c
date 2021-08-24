#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h> /* Standard I/O functions */
#include <stdlib.h> /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h> /* Prototypes for many system calls */
#include <errno.h> /* Declares errno and defines error constants */
#include <string.h> /* Commonly used string-handling functions */
#include <sys/wait.h>

int fib[100];

void Fibonacci(int n) {
    int x1 = 0, x2 = 1;
    int sum = x1 + x2;
    for (int i = 2; i < n; i++) {
        fib[i] = sum;
        x1 = x2;
        x2 = sum;
        sum = x1 + x2;
    }
}

void printArray(int* a, int aLen) {
    for (int i = 0; i < aLen; i++) {
        printf("%d ", a[i]);
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

    int fd[2];
    if (pipe(fd) == -1) {
        printf("Pipe failed!\n");
        return 1;
    }

    fflush(stdout);
    pid_t pid = fork();

    if (pid < 0) {
        printf("\nForking failed.\n");
    } else if (pid) {
        wait(NULL);
        printf("This is parent and the series is: \n");
        int output_fib[100] = {};
        close(fd[1]);
        read(fd[0], output_fib, x*sizeof(int));
        close(fd[0]);
        printArray(output_fib, x);
    } else {
        fib[0] = 0;
        fib[1] = 1;
        Fibonacci(x);
        printf("This is child and the fibonacci series is produced.\n");
        close(fd[0]);
        write(fd[1], fib, x*sizeof(int));
        close(fd[1]);
        exit(0);
    }

    return 0;
}

