#include <stdio.h>
#include <time.h>

#define ARRAY_SIZE 1000000 

void SerialExecution(int array_size) {
    int array[array_size];
    int sum = 0;
    for (int i = 0; i < array_size; i++) {
        array[i] = 1;
    }
    for (int i = 0; i < array_size; i++) {
        sum += array[i];
    }

    printf("Sequential sum: %d\n", sum);
}

int main() {
    int sizes[] = {100000, 500000, 1000000}; // Different array sizes to test
    for (int i = 0; i < 3; i++) {
        int size = sizes[i];
        clock_t start = clock();
        SerialExecution(size);
        clock_t end = clock();
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Sequential execution time for size %d: %f seconds\n", size, time_taken);
    }

    return 0;
}
