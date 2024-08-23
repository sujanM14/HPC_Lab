#include <stdio.h>
#include <omp.h>

int main() {
    int sum_of_squares = 0;
    int num_threads = 4; 
    omp_set_num_threads(num_threads);

    #pragma omp parallel reduction(+:sum_of_squares)
    {
        int thread_id = omp_get_thread_num();
        int square = thread_id * thread_id;
        printf("Thread %d: Square of ID is %d\n", thread_id, square);
        sum_of_squares += square;
    }

    printf("Total sum of squares: %d\n", sum_of_squares);

    return 0;
}
