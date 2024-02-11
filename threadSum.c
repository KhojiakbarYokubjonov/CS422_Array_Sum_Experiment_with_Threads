/*
    Khojiakbar Yokubjonov
    Spring 2024
    CSC 422
    seqSum.c
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>   //setitimer


// global vars
int *a;     // array of nums
// int *subtotal;
long int sum;
int arraySize, numThreads;  // input given via the cmd line
pthread_mutex_t L;

void *worker(void *arg) {
    int myId = *((int *) arg);
    int startpos = myId * arraySize/numThreads + 1;
    int endpos = (myId+1) * (arraySize/numThreads);
    long int currentSum = 0;

    for(int i=startpos; i <= endpos; i++) {
        currentSum += a[i];
    }
    // critical section: add current sum to global sum using a lock
    pthread_mutex_lock(&L); 
    sum += currentSum;
    pthread_mutex_unlock(&L);
    return NULL;

}
int main(int argc, char **argv) {
    int *params;
    double elapsed;
    struct timeval start, stop;
    pthread_t *threads;

    arraySize = atoi(argv[1]);
    numThreads = atoi(argv[2]);

    a = (int *) malloc(sizeof(int) * (arraySize+1));
    for(int i=0; i<=arraySize; i++) {
        a[i] = i;
    }
    sum = 0;
    // subtotal = (int *) malloc(sizeof(int) * numThreads);
    
    pthread_mutex_init(&L, NULL);

    // get the current time 
    gettimeofday(&start, NULL);

    // Allocate thread handles
    threads = (pthread_t *) malloc(numThreads * sizeof(pthread_t));
    params = (int *) malloc(numThreads * sizeof(int));

    // Create threads
    for (int i = 0; i < numThreads; i++) {
        params[i] = i;
        pthread_create(&threads[i], NULL, worker, (void *)(&params[i]));
    }

    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }
    

    gettimeofday(&stop, NULL);
    printf("%ld\n", sum);
    elapsed = ((stop.tv_sec - start.tv_sec) * 1000000+(stop.tv_usec-start.tv_usec))/1000000.0;
    printf("time taken is %f seconds\n", elapsed);




}
