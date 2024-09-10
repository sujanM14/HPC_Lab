#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include<time.h>

#define N 1000 // Adjust size as needed

void serial_matrix_vector_multiply(double a[N][N], double b[N], double c[N]) {
    for (int i = 0; i < N; i++) {
        c[i] = 0;
        for (int j = 0; j < N; j++)
            c[i] += a[i][j] * b[j];
    }
}

void parallel_matrix_vector_multiply(double a[N][N], double b[N], double c[N], int threads) {
    #pragma omp parallel for num_threads(threads)
    for (int i = 0; i < N; i++) {
        c[i] = 0;
        for (int j = 0; j < N; j++)
            c[i] += a[i][j] * b[j];
    }
}

int main() {
    double a[N][N], b[N], c[N];
    double start, end;

    for (int i = 0; i < N; i++) {
        b[i] = rand() % 100;
        for (int j = 0; j < N; j++)
            a[i][j] = rand() % 100;
    }

    double start1 = clock();
    serial_matrix_vector_multiply(a, b, c);
    double end1 = clock();
    
    double time1=(end1-start1)/CLOCKS_PER_SEC;
    printf("Serial Time: %f seconds\n", time1);

 
    for (int threads = 2; threads <= 8; threads *= 2) {
        double start2 =  clock();
        parallel_matrix_vector_multiply(a, b, c, threads);
        double end2 =  clock();
        double time2=(end2-start2)/CLOCKS_PER_SEC;
        printf("Parallel Time with %d threads: %f seconds\n", threads, time2);
        
        printf("Speedup %f\n",time1/time2);
    }

    return 0;
}