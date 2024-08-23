#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    for(int i=0;i<20;i++)
    {
        int thread_id = omp_get_thread_num();
        if (thread_id == 0) {
            printf("Thread %d: 2\n", thread_id);
        } else if (thread_id == 1) {
            printf("Thread %d: 4\n", thread_id);
        }
    }

    return 0;
}
