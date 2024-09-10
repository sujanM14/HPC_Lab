#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

#define N 100

void serial_matrix_multiply(double a[N][N], double b[N][N], double c[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            c[i][j] = 0;
            for (int k = 0; k < N; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
}

void parallel_matrix_multiply(double a[N][N], double b[N][N], double c[N][N], int threads) {
    #pragma omp parallel for num_threads(threads) collapse(2)
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            c[i][j] = 0;
            for (int k = 0; k < N; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
}

int main() {
    double a[N][N], b[N][N], c[N][N];
    double start, end;

    // Initialize matrices
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            a[i][j] = rand() % 100;
            b[i][j] = rand() % 100;
        }


    double start1 = clock();
    serial_matrix_multiply(a, b, c);
    double end1 = clock();
    double time1=(end1-start1)/CLOCKS_PER_SEC;
    printf("Serial Time: %f seconds\n", time1);
    

 
    for (int threads = 2; threads <= 8; threads *= 2) {
        double start2 =  clock();
        parallel_matrix_multiply(a, b, c, threads);
        double end2 =  clock();
        double time2=(end2-start2)/CLOCKS_PER_SEC;
        printf("Parallel Time with %d threads: %f seconds\n", threads, time2);
        
        printf("Speedup %f\n",time1/time2);
    }

    return 0;
}