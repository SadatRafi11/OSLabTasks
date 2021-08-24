#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int A[10][10], B[10][10], C[10][10];
int m, n, k;

struct elements {
    int row;
    int col;
};

void* matrixMultiplication (void* arg) {
    printf("This is one of the the multiplying child thread.\n");
    struct elements* cij = (struct elements*) arg;

    int i = cij -> row;
    int j = cij -> col;
    free(cij);

    C[i][j] = 0;
    for (int inc = 0; inc < k; inc++)
        C[i][j] += A[i][inc] * B[inc][j];

    pthread_exit(NULL);
}

void createThread () {
    printf("This is the parent thread.\n");

    printf("Enter the number rows for Matrix A: ");
    scanf("%d", &m);

    printf("Enter the number columns for Matrix A and rows for Matrix B: ");
    scanf("%d", &k);

    printf("Enter the number columns for Matrix B: ");
    scanf("%d", &n);

    while (m <= 0 || k <= 0 || n <= 0 || m > 10 || n > 10 || k > 10) {
        printf("Try again with positive integer values less than 11.\n");
        printf("Enter the number rows for Matrix A: ");
        scanf("%d", &m);

        printf("Enter the number columns for Matrix A and rows for Matrix B: ");
        scanf("%d", &k);

        printf("Enter the number columns for Matrix B: ");
        scanf("%d", &n);
    }

    printf("Enter the values for Matrix A:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < k; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    printf("Enter the values Matrix B:\n");
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    pthread_t ptid[m * n];
    int cnt = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            struct elements* this_elem = (struct elements*) malloc(sizeof(struct elements));
            this_elem -> row = i;
            this_elem -> col = j;

            pthread_create(&ptid[cnt], NULL, matrixMultiplication, this_elem);
            sleep(2);
            pthread_join(ptid[cnt], NULL);
            sleep(2);
            printf("Back into the parent\n");
            cnt++;
        }
    }

    printf("\nMatrix C, after being calculated by those threads :\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    pthread_exit(NULL);
}

// Driver code
int main() {
    createThread();
    return 0;
}
