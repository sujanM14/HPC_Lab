#include <stdio.h>
#include <omp.h>

int main() {
    const char *names[] = {"Sujan", "Yasmin", "arham", "Shifa", "Ibiza"};
    int num_members = sizeof(names) / sizeof(names[0]);

    #pragma omp parallel num_threads(num_members)
    {
        int thread_id = omp_get_thread_num();
        if (thread_id < num_members) {
            printf("Thread %d: %s, Job ID: %d\n", thread_id, names[thread_id], thread_id);
        }
    }

    return 0;
}
