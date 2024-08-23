#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_POINTS 1000

double calculate_pi(int num_points) {
    int count = 0;
    #pragma omp parallel
    {
        unsigned int seed = omp_get_thread_num();
        #pragma omp for reduction(+:count)
        for (int i = 0; i < num_points; i++) {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;
            if (x * x + y * y <= 1) {
                count++;
            }
        }
    }
    return 4.0 * count / num_points;
}

int main() {
    int num_threads_arr[] = {2, 4, 8, 16}; 
    int num_points_arr[] = {500,1000,2000,5000};

    for (int i = 0; i < sizeof(num_threads_arr) / sizeof(num_threads_arr[0]); i++) {
        for (int j = 0; j < sizeof(num_points_arr) / sizeof(num_points_arr[0]); j++) {
            omp_set_num_threads(num_threads_arr[i]);
            double start_time = omp_get_wtime();
            double pi = calculate_pi(num_points_arr[j]);
            double end_time = omp_get_wtime();

            printf("Threads: %d, Points: %d\n", num_threads_arr[i], num_points_arr[j]);
            printf("Estimated value of Pi: %f\n", pi);
            printf("Time taken for Pi calculation: %f seconds\n", end_time - start_time);
            printf("\n");
        }
    }

    return 0;
}
