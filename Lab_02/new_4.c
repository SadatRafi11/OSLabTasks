#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h> /* Standard I/O functions */
#include <stdlib.h> /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h> /* Prototypes for many system calls */
#include <errno.h> /* Declares errno and defines error constants */
#include <string.h> /* Commonly used string-handling functions */
#include <sys/wait.h>

void bubbleSort(int *a, int aLen) {
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

void printArray(int *a, int aLen) {
    for (int i = 0; i < aLen; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int binarySearch(int *a, int low, int high, int value){
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

int a[1000] = {};
int main(){
    int aLen;
    printf("\nEnter the length: ");
    scanf("%d", &aLen);

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
        printf("\nThis is the parent.\n");
        printArray(a, aLen);
        int desired_index = binarySearch(a, 0, aLen-1, x);
        if (desired_index == -1) printf("Value not found!\n");
        else printf("Value found in index: %d\n", desired_index);
    } else {
        printf("\nThis is the child.\n");
        bubbleSort(a, aLen);
        printf("Sorted array:\n");
        printArray(a, aLen);
    }

    return 0;
}

// 1 4 8 5 3 2 ............ 4

