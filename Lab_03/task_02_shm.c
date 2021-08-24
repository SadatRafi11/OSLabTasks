#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void Fibonacci(int n, int* fib) {
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
    // shmget returns an identifier in shmid
    int shmid = shmget(IPC_PRIVATE,1024,0666|IPC_CREAT);

    // shmat to attach to shared memory
    int* fib = (int*) shmat(shmid,NULL,0);
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
        printf("This is parent and the series is: \n");
        printArray(fib, x);
    } else {
        fib[0] = 0;
        fib[1] = 1;
        Fibonacci(x, fib);
        printf("This is child and the fibonacci series is produced.\n");
        shmdt(fib);
        exit(0);
    }

    return 0;
}

