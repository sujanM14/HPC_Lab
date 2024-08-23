#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 200

void run_experiment(int chunk_size) {
    int *a = (int *)malloc(sizeof(int) * N);
    int *c = (int *)malloc(sizeof(int) * N);
    int b = 10;

    for (int i = 0; i < N; i++) {
        a[i] = 0;
    }

    omp_set_num_threads(6);

   double itime, ftime, exec_time;
    itime = omp_get_wtime();

    #pragma omp parallel for schedule(static, chunk_size)
    for (int i = 0; i < N; i++) {
        c[i] = a[i] + b;
    }

    ftime = omp_get_wtime();
    exec_time = ftime - itime;

    printf("Chunk size: %d, Time taken: %f seconds\n", chunk_size, exec_time);

    free(a);
    free(c);
}

int main() {
    int chunk_sizes[] = {1, 8, 16, 32, 64}; 
    int num_chunk_sizes = sizeof(chunk_sizes) / sizeof(chunk_sizes[0]);

    for (int i = 0; i < num_chunk_sizes; i++) {
        run_experiment(chunk_sizes[i]);
    }

    return 0;
}
