#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int fibonacciSeries[1000] = {};

void* fibonacciGenerator (void* arg) {
    int n = *((int*) arg);
    //printf("Inside the child thread and number of term is %d\n", n);

    if (n > 1) fibonacciSeries[n] = fibonacciSeries[n-1] + fibonacciSeries[n-2];

    pthread_exit(NULL);
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

    // Creating a new thread
    pthread_t ptid[lim];
    fibonacciSeries[0] = 0;
    fibonacciSeries[1] = 1;
    for (int i = 0; i < lim; i++) {
        pthread_create(&ptid[i], NULL, (void*)fibonacciGenerator, &i);
        //for each of the iteration parent thread will be temporarily suspended for calculation
        pthread_join(ptid[i], NULL);
        printf("%d ", fibonacciSeries[i]);
    }
    printf("\n");

    pthread_exit(NULL);
}

int main() {
    createThread();
    return 0;
}

