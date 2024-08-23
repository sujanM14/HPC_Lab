#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 2000

void add(int **a, int **b, int **c) {
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

void input(int **a, int num) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i][j] = (num * i + 50) / 3;
        }
    }
}

void freeMatrix(int **a) {
    for (int i = 0; i < N; i++) {
        free(a[i]);
    }
    free(a);
}

int main() {
    int **a = (int **)malloc(sizeof(int *) * N);
    int **b = (int **)malloc(sizeof(int *) * N);
    int **c = (int **)malloc(sizeof(int *) * N);
    for (int i = 0; i < N; i++) {
        a[i] = (int *)malloc(sizeof(int) * N);
        b[i] = (int *)malloc(sizeof(int) * N);
        c[i] = (int *)malloc(sizeof(int) * N);
    }

    input(a, 5);
    input(b, 5);

    int num_threads[] = {2, 4, 8}; // Different thread counts
    int num_experiments = sizeof(num_threads) / sizeof(num_threads[0]);

    for (int k = 0; k < num_experiments; k++) {
        omp_set_num_threads(num_threads[k]);

        double start = omp_get_wtime();
        add(a, b, c);
        double end = omp_get_wtime();

        printf("Time taken with %d threads: %f seconds for N=%d\n", num_threads[k], end - start, N);
    }

    freeMatrix(a);
    freeMatrix(b);
    freeMatrix(c);

    return 0;
}
