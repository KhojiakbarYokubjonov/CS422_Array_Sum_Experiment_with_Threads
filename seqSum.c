/*
    Khojiakbar Yokubjonov
    Spring 2024
    CSC 422
    seqSum.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>   //setitimer


// global vars
int *a;     // array of nums
int arraySize;  // input given via the cmd line


int main(int argc, char **argv) {
    double elapsed;
    struct timeval start, stop;
    arraySize = atoi(argv[1]);

    a = (int *) malloc (sizeof(int) * arraySize);
    for(int i=0; i<=arraySize; i++) {
        a[i] = i;
    }
    
    long int sum = 0;
    // get the current time 
    gettimeofday(&start, NULL);

    for(int j=0; j<=arraySize; j++) {
        sum += a[j];
    }

    gettimeofday(&stop, NULL);
    printf("%ld\n", sum);
    elapsed = ((stop.tv_sec - start.tv_sec) * 1000000+(stop.tv_usec-start.tv_usec))/1000000.0;
    printf("time taken is %f seconds\n", elapsed);




}
