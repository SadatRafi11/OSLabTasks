#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>

#define MAX_CUSTOMER_COUNT 100

sem_t waitingRoom;
sem_t barber;

void* hairCut(void* number) {
    int num = *((int*) number);
    printf("Customer %d wants to get a haircut\n", num);

    int sem_val;
    sem_getvalue(&waitingRoom, &sem_val);
    //printf("%d\n", sem_val);

    if (sem_val < 1) {
        printf("Customer %d won't be getting one!\n", num);
        return number;
    }

    //wait for room
    sem_wait(&waitingRoom);
    printf("Customer %d is waiting \n", num);

    //wait for barber
    sem_wait(&barber);

    //A chair is empty since the next customer is getting a haircut
    sem_post(&waitingRoom);

    printf("Customer %d is getting a haircut.\n", num);

    //done cutting hair
    sem_post(&barber);
    printf("Customer %d is done getting a haircut\n", num);
    pthread_exit(NULL);
    //free(number);
    //exit(0);
}

int main() {
    int numCustomers = 0, numChairs = 0;

    printf("Enter the number of Customers : ");
    scanf("%d", &numCustomers);

    while (numCustomers > MAX_CUSTOMER_COUNT) {
        printf("The maximum number of Customers can be %d. Try again...\n", 10);
        printf("Enter the number of Customers : ");
        scanf("%d", &numCustomers);
    }

    printf("Enter the number of Charis : ");
    scanf("%d", &numChairs);

    while (numChairs > MAX_CUSTOMER_COUNT) {
        printf("The maximum number of Chairs can be %d. Try again...\n", 10);
        printf("Enter the number of Chairs : ");
        scanf("%d", &numChairs) ;
    }

    //initializing semaphores.
    sem_init(&waitingRoom, 0, numChairs);
    sem_init(&barber, 0, 1);

    //A thread for each customer
    pthread_t ptid[numCustomers];

    //creating threads
    for (int i = 0; i < numCustomers; i++) {
        pthread_create(&ptid[i], NULL, hairCut, (void*)&i);
    }

    //joining threads
    for (int i = 0; i < numCustomers; i++) {
        pthread_join(ptid[i], NULL);
        sleep(2);
    }

    //Deleting the semaphores
    sem_destroy(&waitingRoom);
    sem_destroy(&barber);

    printf("\nBarber is tired, and now he is sleeping...\n");

    return 0;
}
