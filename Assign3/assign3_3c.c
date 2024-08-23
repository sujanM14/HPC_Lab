#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 10

void funct_foo() {
    printf("Hello foo\n");
}

void print(int i) {
    printf("Value %d\n", i);
}

int main() {
    #pragma omp parallel
    {
        #pragma omp for nowait
        for (int i = 0; i < N; i++) {
            print(i);
        }

        funct_foo();
    }

    return 0;
}
