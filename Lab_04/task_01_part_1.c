#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

int prime_list[1000001] = {};
bool primeOrNot[1000001] = {};

void* primeGenerator (void* arg) {
    int n = *((int*) arg);
    printf("Inside the child thread and limit is %d\n", n);

    //Sieve of Eratosthenes
    prime_list[0] = 2;
    for (int i = 3; i <= n; i += 2) {
        for (int j = i * i; j <= n; j += (i*2)) {
            //printf("got here at %d\n", j);
            primeOrNot[j >> 1] = true;
        }
    }

    int cnt = 0;
    for (int i = 3, j = 1; i < n; i += 2) {
        if (!primeOrNot[i >> 1]) {
            prime_list[j++] = i;
            //printf("prime found! It's %d\n", prime_list[j - 1]);
            cnt++;
        }
    }

    printf("primes are: \n");
    for (int i = 0; i <= cnt; i++) printf("%d ", prime_list[i]);
    printf("\n");

    pthread_exit(NULL);
}

void createThread () {
    printf("This is the parent Thread.\n");
    pthread_t ptid;
    int lim;
    printf("Enter the integer limit of finding primes: ");
    scanf("%d", &lim);

    while (lim <= 0) {
        printf("Try positive integer limit of finding primes: ");
        scanf("%d", &lim);
    }

    // Creating a new thread
    pthread_create(&ptid, NULL, primeGenerator, &lim);
    //suspending this thread and getting into another
    pthread_join(ptid, NULL);

    printf("Back into the parent thread.\n");

    pthread_exit(NULL);
}

// Driver code
int main() {
    createThread();
    return 0;
}
