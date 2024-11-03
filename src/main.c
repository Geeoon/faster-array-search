#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define DEFAULT_SIZE 100000L
#define TRIALS_TO_RUN 100.0

void shuffle_array(long* array, long size);
long find_index_linear(long* array, long size, long target);
long find_index_other(long* array, long size, long target);

int main(int argc, char* argv[]) {
    srand(time(NULL));
    long size = DEFAULT_SIZE;
    
    if (argc > 1) {
        size = atol(argv[1]);
    }

    assert(size > 0);

    long* array = malloc(sizeof(long) * size);
    for (long i = 0; i < size; i++) {
        array[i] = i;
    }

    printf("Shuffing array...\n");
    shuffle_array(array, size);

    // sanity check shuffling
    long right = (size - 1) * (size / 2);
    long sorted = 0;
    for (long i = 0; i < size; i++) {
        sorted += array[i];
    }

    assert(right == sorted);
    
    clock_t start, stop;
    long index = 0;
    long target = rand() % size;
    double linear_average = 0.0;
    for (int i = 0; i < TRIALS_TO_RUN; i++) {
        printf("Searching for element %ld using linear search...\n", target);
        start = clock();
        index = find_index_linear(array, size, target);
        stop = clock();
        double time = (double)(stop - start);
        printf("Found at index %ld in %.1fms\n", index, time);
        linear_average += time;
    }
    linear_average /= 100.0;
    // other method
    printf("\nLinear done, starting other method...\n");
    double other_average = 0.0;
    for (int i = 0; i < TRIALS_TO_RUN; i++) {
        printf("Searching for element %ld using other search...\n", target);
        start = clock();
        index = find_index_other(array, size, target);
        stop = clock();
        double time = (double)(stop - start);
        printf("Found at index %ld in %.1fms\n", index, time);
        other_average += time;
    }
    other_average /= 100.0;

    printf("\nThe linear method took an average of %.1fms\n", linear_average);
    printf("\nThe other method took an average of %.1fms\n", other_average);
}

void shuffle_array(long* array, long size) {
    for (long i = 0; i < size; i++) {
        long j = i + (long)(rand() / (RAND_MAX / (size - i) + 1));
        long temp = array[j];
        array[j] = array[i];
        array[i] = temp;
    }
}

long find_index_linear(long* array, long size, long target) {
    for (long i = 0; i < size; i++) {
        if (array[i] == target) return i;
    }
    return -1;
}

long find_index_other(long* array, long size, long target) {
    long index = target;
    while (array[index] != target) {
        long temp = array[index];
        index = array[temp];
    }
    return index;
}