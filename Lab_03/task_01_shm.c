#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h> /* Standard I/O functions */
#include <stdlib.h> /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h> /* Prototypes for many system calls */
#include <errno.h> /* Declares errno and defines error constants */
#include <string.h> /* Commonly used string-handling functions */
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void bubbleSort(int* a, int aLen) {
    for (int i = 0; i < aLen-1; i++) {
        for (int j = 0; j < aLen-i-1; j++) {
            if (a[j] > a[j+1]) {
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}

void printArray(int* a, int aLen) {
    for (int i = 0; i < aLen; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int binarySearch(int* a, int low, int high, int value){
    if(low <= high){
        int mid = (low + high)/2;
        if(a[mid] == value) {
            //printf("%d and %d\n", a[mid], mid);
            return mid;
        }
        else if(a[mid] > value) {
            //printf("%d\n", a[mid]);
            return binarySearch(a, low, mid-1, value);
        }
        else if(a[mid] < value) {
            //printf("%d\n", a[mid]);
            return binarySearch(a, mid+1, high, value);
        }
    }
    return -1;
}


int main(){
    int aLen;
    printf("\nEnter the length: ");
    scanf("%d", &aLen);

    // shmget returns an identifier in shmid
    int shmid = shmget(IPC_PRIVATE,1024,0666|IPC_CREAT);

    // shmat to attach to shared memory
    int* a = (int*) shmat(shmid,NULL,0);

    printf("\nEnter the array: ");
    for (int i = 0; i < aLen; i++){
        scanf("%d", &a[i]);
    }

    printf("Initial array:\n");
    printArray(a, aLen);

    int x;
    printf("\nEnter the value to be searched: ");
    scanf("%d", &x);
    while(x < 0){
        printf("\nCan't be negative.\nEnter the value again: ");
        scanf("%d", &x);
    }

    fflush(stdout);
    pid_t pid = fork();

    if(pid < 0) {
        printf("\nForking failed\n");
    } else if (pid) {
        wait(NULL);
        printf("\nThis is the parent and the sorted array is : ");
        printArray(a, aLen);

        int desired_index = binarySearch(a, 0, aLen-1, x);
        if (desired_index == -1) printf("Value not found!\n");
        else printf("Value found in index: %d of the sorted array.\n", desired_index);

        shmdt(a);
        shmctl(shmid,IPC_RMID,NULL);

    } else {
        printf("\nThis is the child.\n");
        printArray(a, aLen);
        bubbleSort(a, aLen);
        printArray(a, aLen);
        printf("Sorted.\n");

        shmdt(a);

        exit(0);
    }

    return 0;
}

// 1 4 8 5 3 2 ............ 4

