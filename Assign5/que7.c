#include <stdio.h>
#include <omp.h>

#define ARRAY_SIZE 1000

void funcUsingCriticalSection() {
    int array[ARRAY_SIZE];
    int total_sum = 0;

    // Initialize the array with the formula (55*(i-2))/10
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = (55 * (i - 2)) / 10;
    }

    double itime, ftime, exec_time;
    itime = omp_get_wtime();

    #pragma omp parallel
    {
        int partial_sum = 0;

        #pragma omp for
        for (int i = 0; i < ARRAY_SIZE; i++) {
            partial_sum += array[i];
        }

        #pragma omp critical
        {
            total_sum += partial_sum;
        }
    }

    ftime = omp_get_wtime();
    exec_time = ftime - itime;
    
    printf("Using critical Section\n");
    printf("Time required is %f seconds\n", exec_time);
    printf("Total sum: %d\n", total_sum);
}

void funcUsingAtomic() {
    int array[ARRAY_SIZE];
    int total_sum = 0;

    // Initialize the array with the formula (55*(i-2))/10
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = (55 * (i - 2)) / 10;
    }

    double itime, ftime, exec_time;
    itime = omp_get_wtime();

    #pragma omp parallel
    {
        int partial_sum = 0;

        #pragma omp for
        for (int i = 0; i < ARRAY_SIZE; i++) {
            partial_sum += array[i];
        }

        #pragma omp atomic
        total_sum += partial_sum;
    }

    ftime = omp_get_wtime();
    exec_time = ftime - itime;
    
    printf("Using Atomic Update\n");
    printf("Time required is %f seconds\n", exec_time);
    printf("Total sum: %d\n", total_sum);
}

int main() {
    funcUsingCriticalSection();
    funcUsingAtomic();
    return 0;
}
