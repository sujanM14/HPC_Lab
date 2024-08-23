#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void vector_scalar_add(int *vector, int scalar, int *result, int size) {
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        result[i] = vector[i] + scalar;
        printf("Thread no. %d: vector[%d] + %d = %d\n", omp_get_thread_num(), i, scalar, result[i]);
    }
}

int main() {
    int size = 1000;
    int scalar = 14;
    int *vector = (int *)malloc(size * sizeof(int));
    int *result = (int *)malloc(size * sizeof(int));
    int num = 18;

    for (int i = 0; i < size; i++) {
        vector[i] = num * (i + 1);
    }

    double start_tm = omp_get_wtime();
    vector_scalar_add(vector, scalar, result, size);
    double end_tm = omp_get_wtime();

    printf("Time taken: %f seconds\n", end_tm - start_tm);

    
    for (int i = 0; i < size; i++) {
        printf("result[%d] = %d\n", i, result[i]);
    }

    free(vector);
    free(result);
    return 0;
}

