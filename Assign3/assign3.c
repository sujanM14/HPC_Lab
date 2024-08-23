#include <omp.h>
#include <stdio.h>
#include <time.h>

#define n 100000


void sort(int nums[]) {
    int i, j,num_threads=8;
    #pragma omp parallel num_threads(num_threads)
    {
        for (i = 0; i < n; i++) {
            int turn = i & 2;
            #pragma omp for
            for (j = turn; j < n - 1; j += 2) {
                if (nums[j] > nums[j + 1]) {
                    int temp = nums[j];
                    nums[j] = nums[j + 1];
                    nums[j + 1] = temp;
                }
            }
        }
    }
}

void sort_des(int nums[]) {
    int i, j,num_threads=8;
 
    #pragma omp parallel num_threads(num_threads)
    {
        for (i = 0; i < n; ++i) {
            int turn = i & 2;
            #pragma omp for
            for (j = turn; j < n - 1; j += 2) {
                if (nums[j] < nums[j + 1]) {
                    int temp = nums[j];
                    nums[j] = nums[j + 1];
                    nums[j + 1] = temp;
                }
            }
        }
    }
}

int main() {
    int nums1[n], nums2[n];
    
    for (int i = 0; i < n; i++) {
        nums1[i] = 10;
    }
    for (int i = 0; i < n; i++) {
        nums2[i] = 20;
    }
    int num_threads=8;
    clock_t t;
    t = clock();
    sort(nums1);
    sort_des(nums2);
    t = clock() - t;

    printf("Number of threads: %d\n",num_threads);
    double time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("Time taken (seq): %f\n", time_taken);

    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += nums1[i] * nums2[i];
    }
    printf("%d\n", sum);

    return 0;
}
