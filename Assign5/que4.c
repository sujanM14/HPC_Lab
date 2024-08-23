#include <stdio.h>
#include <omp.h>

int main() {
    int n = 20;
    int total_sum = 0;
    int last_thread_sum = 0;

    #pragma omp parallel num_threads(4)
    {
        int thread_sum = 0;

        #pragma omp for reduction(+:total_sum)
        for (int i = 1; i <= n; i++) {
            thread_sum += i;
            total_sum += i;
            printf("Thread %d: Partial sum till %d is %d\n", omp_get_thread_num(), i, thread_sum);
        }

        #pragma omp single
        {
            last_thread_sum = thread_sum;
        }
    }

    printf("Last thread partial sum: %d\n", last_thread_sum);
    printf("Total sum of first %d natural numbers is %d\n", n, total_sum);

    return 0;
}
