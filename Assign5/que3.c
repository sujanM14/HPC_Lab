#include <stdio.h>
#include <omp.h>
#define num_threads 8
int main() {
    int Aryabhatta = 10; 
     omp_set_num_threads(num_threads);
    #pragma omp parallel private(Aryabhatta)
    {
        int thread_id = omp_get_thread_num();
        int result = thread_id * Aryabhatta;
        printf("Thread %d: Result of multiplication is %d\n", thread_id, result);
    }

    return 0;
}
