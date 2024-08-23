#include <stdio.h>
#include <omp.h>
#include <time.h>

#define ARRAY_SIZE 1000000 // Default size, can be modified

void ParallelExecution(int array_size) {
    int array[array_size];
    int sum = 0;
    
    // Initialize the array
    for (int i = 0; i < array_size; i++) {
        array[i] = 1; // Example value
    }

    double itime, ftime, exec_time;
    itime = omp_get_wtime();

    #pragma omp parallel reduction(+:sum)
    {
        #pragma omp for
        for (int i = 0; i < array_size; i++) {
            sum += array[i];
        }
    }

    ftime = omp_get_wtime();
    exec_time = ftime - itime;

    printf("Parallel sum: %d\n", sum);
    printf("Time required is %f seconds\n", exec_time);
}

int main() {
   int sizes[] = {100000, 500000, 1000000}; // Different array sizes to test
    for (int i = 0; i < 3; i++) {
        int size=sizes[i];
        ParallelExecution(size);
    }

    return 0;
}
