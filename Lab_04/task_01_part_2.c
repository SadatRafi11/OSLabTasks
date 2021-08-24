#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t table;
sem_t chopstick[5];

void* philosopherThread (void* phil_add) {
	int phil = *((int*) phil_add);
	printf("\n%d\n", phil);

	//Check if there are already 4 philosophers in the table.
	sem_wait(&table);
	printf("Philosopher %d has joined in.\n", phil);

	//wait
	sem_wait(&chopstick[phil - 1]);
	sem_wait(&chopstick[phil % 5]);

    //Critical Section
	printf("Philosopher %d gets to eat...\n", phil);
	sleep(2);
	printf("Philosopher %d is done eating\n", phil);

    //signal
	sem_post(&chopstick[(phil + 1) %5]);
	sem_post(&chopstick[phil]);

	// A philosopher is getting out
	sem_post(&table);
	printf("Philosopher %d is starting to think again.\n", phil);
}

int main() {
    //Number of philosophers here is 5
	int philosphers[5] = {1, 2, 3, 4, 5};
	pthread_t ptid[5];

	sem_init(&table, 0, 4);

	for (int i = 0; i < 5; i++) {
        sem_init(&chopstick[i], 0, 1);
		pthread_create(&ptid[i], NULL, philosopherThread, &philosphers[i]);
	}

	for (int i = 0; i < 5; i++) pthread_join(ptid[i], NULL);
    return 0;
}
