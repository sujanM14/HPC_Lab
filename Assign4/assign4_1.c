#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int fibonacci(int n) {
    int i, j;
    if (n < 2)
        return n;
    else {
#pragma omp task shared(i)
        i = fibonacci(n - 1);
#pragma omp task shared(j)
        j = fibonacci(n - 2);
#pragma omp taskwait
        return i + j;
    }
}

int main(int argc, char **argv) {
    char *a = argv[1];
    int n = atoi(a), result;
    double itime, ftime, exec_time;
    itime = omp_get_wtime();
#pragma omp parallel
    {
#pragma omp single
        result = fibonacci(n);
    }
    ftime = omp_get_wtime();
    exec_time = ftime - itime;
    printf("Result is %d\n", result);
    printf("Time required is %f",exec_time);
}