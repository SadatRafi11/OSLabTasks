#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void printArray (int* a, int aLen) {
    for (int i = 0; i < aLen; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void* fibonacciGenerator (void* arg) {
    int fib[1000] = {};
    int n = *((int*) arg);
    printf("Inside the child thread and number of term is %d\n", n);

    fib[0] = 0, fib[1] = 1;
    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }

    pthread_exit(fib);
}

void createThread () {
    printf("This is the parent Thread.\n");

    int lim;
    printf("Enter the number of Fibonacci terms: ");
    scanf("%d", &lim);

    while (lim <= 0) {
        printf("Try positive integer limit of finding primes: ");
        scanf("%d", &lim);
    }

    void* fibonacciSeries;
    // Creating a new thread
    pthread_t ptid;
    pthread_create(&ptid, NULL, fibonacciGenerator, &lim);
    printf("Suspending the parent thread.\n");
    //suspending this thread and getting into another
    pthread_join(ptid, &fibonacciSeries);

    printf("Resuming the parent thread.\nGenerated series:");

    printArray((int*)fibonacciSeries, lim);

    pthread_exit(NULL);
}

int main() {
    createThread();
    return 0;
}

