#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#define BUFFER_SIZE 5
#define NITER 10
int buffer[BUFFER_SIZE];
int in = 0;    // next free position
int out = 0;   // first full position

int main() {
    srand(time(NULL));

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            for (int i = 0; i < NITER; i++) {
                int next_produced = rand() % 100 + 1;
                while (((in + 1) % BUFFER_SIZE) == out) {
                    #pragma omp flush(out) 
                }
                {
                    buffer[in] = next_produced;
                    printf("Producer produced [%d]. (Placed in index: in=%d, out=%d)\n", next_produced, in, out);
                    in = (in + 1) % BUFFER_SIZE;
                    #pragma omp flush(in)
                }
            }
        }

        #pragma omp section
        {
            for (int i = 0; i < NITER; i++) {
                while (in == out) {
                    #pragma omp flush(in) 
                }
                #pragma omp critical
                {
                    int next_consumed = buffer[out];
                    printf("\t\tConsumer consumed [%d]. (in=%d, Consumed from index: out=%d)\n", next_consumed, in, out);
                    out = (out + 1) % BUFFER_SIZE;
                    #pragma omp flush(out) 
                }
            }
        }
    }

    return 0;
}


