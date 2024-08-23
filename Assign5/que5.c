#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 500

// Serial matrix multiplication
void matrix_multiply_serial(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Parallel matrix multiplication with static scheduling
void matrix_multiply_static(int A[N][N], int B[N][N], int C[N][N]) {
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Parallel matrix multiplication with dynamic scheduling
void matrix_multiply_dynamic(int A[N][N], int B[N][N], int C[N][N]) {
    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Serial execution timing
void SerialTime() {
    int A[N][N], B[N][N], C[N][N];
    srand(time(0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
        }
    }

    clock_t start = clock();
    matrix_multiply_serial(A, B, C);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Serial execution time: %f seconds\n", time_taken);
}

// Static scheduling timing
void StaticShedule() {
    int A[N][N], B[N][N], C[N][N];
    srand(time(0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
        }
    }

    double start = omp_get_wtime();
    matrix_multiply_static(A, B, C);
    double end = omp_get_wtime();
    printf("Static scheduling execution time: %f seconds\n", end - start);
}

// Dynamic scheduling timing
void DynamicSchedule() {
    int A[N][N], B[N][N], C[N][N];
    srand(time(0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
        }
    }

    double start = omp_get_wtime();
    matrix_multiply_dynamic(A, B, C);
    double end = omp_get_wtime();
    printf("Dynamic scheduling execution time: %f seconds\n", end - start);
}

int main() {
    SerialTime();
    StaticShedule();
    DynamicSchedule();

    return 0;
}
