#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define TEST_INTERVAL 100
#define NUM_TESTS 1000
#define NUM_ITERATIONS 1000000

void *dummyFunction(void *arg) {
    return NULL;
}
int compareLongs(const void *a, const void *b) {
    long arg1 = *(const long *)a;
    long arg2 = *(const long *)b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

long calculateAverage(long *array, size_t size) {
    if (array == NULL || size == 0) {
        return 0;
    }

    // Sort the array
    qsort(array, size, sizeof(long), compareLongs);

    size_t middle = size / 2;
    if (size % 2 == 1) {
        // If the size is odd, return the middle element
        return array[middle];
    } else {
        // If the size is even, return the average of the middle two elements
        return (array[middle - 1] + array[middle]) / 2;
    }
}

long measureMemoryAllocationTime(int size) {
    struct timespec start_time, end_time;

    clock_gettime(CLOCK_MONOTONIC, &start_time);

    int* dynamicArray = (int*)malloc(size * sizeof(int));

    clock_gettime(CLOCK_MONOTONIC, &end_time);

    // Free the allocated memory
    free(dynamicArray);

    // Calculate the elapsed time in nanoseconds
    return (end_time.tv_sec - start_time.tv_sec) * 1e9 + (end_time.tv_nsec - start_time.tv_nsec);
}
// Measure memory access static
long measureStaticMemoryAccess(int size) {
    // Dynamically allocate an array
    int* arr = (int*)malloc(size * sizeof(int));

    // Initialize the array
    for (int i = 0; i < size; ++i) {
        arr[i] = i;
    }

    // Start timer
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Accessing all elements in the array
    for (int i = 0; i < size; ++i) {
        // Perform some operation to prevent compiler optimization
        arr[i] += 1;
    }

    // End timer
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calculate time in nanoseconds
    long duration = (end.tv_sec - start.tv_sec) * 1000000000L + (end.tv_nsec - start.tv_nsec);

    // Free the allocated memory
    free(arr);

    return duration;
}
// Measure memory access dynamically
long measureDynamicMemoryAccess(int size) {
    int *dynamicArray = (int *)malloc(size * sizeof(int));

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < size; i++) {
        dynamicArray[i] = i;
        int element = dynamicArray[i];
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    free(dynamicArray);

    return (end.tv_sec - start.tv_sec) * 1000000000L + (end.tv_nsec - start.tv_nsec);
}
// Measure thread creation
long measureThreadCreation(int numThreads) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    pthread_t threads[numThreads];

    for (int i = 0; i < numThreads; i++) {
        pthread_create(&threads[i], NULL, dummyFunction, NULL);
    }

    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    return (end.tv_sec - start.tv_sec) * 1000000000L + (end.tv_nsec - start.tv_nsec);
}
// Measure thread context switch
long measureThreadContextSwitch(int numThreads) {
    struct timespec start, end;
    pthread_t threads[numThreads];

    clock_gettime(CLOCK_MONOTONIC, &start);

    // Create and join N threads
    for (int i = 0; i < numThreads; i++) {
        pthread_create(&threads[i], NULL, dummyFunction, NULL);
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    return (end.tv_sec - start.tv_sec) * 1000000000L + (end.tv_nsec - start.tv_nsec);
}
// Measure element addition to list
long measureElementAdditionToList(int numElements) {
    struct timespec start, end;


    int* myList = (int*)malloc(numElements * sizeof(int));
    if (myList == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    clock_gettime(CLOCK_MONOTONIC, &start);
    // Add N elements to the list
    for (int i = 0; i < numElements; i++) {
        myList[i] = i; // Add an element to the list
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    free(myList);

    return (end.tv_sec - start.tv_sec) * 1000000000L + (end.tv_nsec - start.tv_nsec);
}
// Measure element removal from list
long measureElementRemovalFromList(int numElements) {
    struct timespec startTime, endTime;

    int *myList = (int *)malloc(numElements * sizeof(int));
    if (myList == NULL) {
        // Handle memory allocation failure
        return -1;
    }

    for (int i = 0; i < numElements; i++) {
        myList[i] = i; // Add N elements to the list
    }

    clock_gettime(CLOCK_MONOTONIC, &startTime);

    // Remove N elements from the list
    for (int i = 0; i < numElements; i++) {
        for (int j = i; j < numElements - 1; j++) {
            myList[j] = myList[j + 1];
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &endTime);

    free(myList); // Don't forget to free the allocated memory

    // Calculate the time elapsed in nanoseconds
    return (endTime.tv_sec - startTime.tv_sec) * 1e9 + (endTime.tv_nsec - startTime.tv_nsec);
}
// Measure list reversal
long measureListReversal(int numElements) {
    struct timespec start, end;

    int *myList = (int *)malloc(numElements * sizeof(int));
    if (myList == NULL) {
        // Handle memory allocation failure
        return -1;
    }

    // Add elements to the list
    for (int i = 0; i < numElements; i++) {
        myList[i] = i;
    }

    clock_gettime(CLOCK_MONOTONIC, &start);

    // Reverse the list
    for (int i = 0, j = numElements - 1; i < j; i++, j--) {
        int temp = myList[i];
        myList[i] = myList[j];
        myList[j] = temp;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    free(myList);

    // Calculate the time elapsed in nanoseconds
    return (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
}
// Write results to a file
void writeResultToFile(const char *fileName, long elapsedTimeMemAlloc, long elapsedTimeMemAccStatic, long elapsedTimeMemAccDynamic, long elapsedTimeThreadCr, long elapsedTimeThreadCS, long elapsedTimeElementAddition, long elapsedTimeElementRemoval, long elapsedTimeListReversal, int numberOfAllocations) {
    FILE *outputFile = fopen(fileName, "w");

    if (outputFile != NULL) {
        //fprintf(outputFile, "C results:\n");
        fprintf(outputFile, "%ld\n", elapsedTimeMemAlloc);
        fprintf(outputFile, "%ld\n", elapsedTimeMemAccStatic);
        fprintf(outputFile, "%ld\n", elapsedTimeMemAccDynamic);
        fprintf(outputFile, "%ld\n", elapsedTimeThreadCr);
        fprintf(outputFile, "%ld\n", elapsedTimeThreadCS);
        fprintf(outputFile, "%ld\n", elapsedTimeElementAddition);
        fprintf(outputFile, "%ld\n", elapsedTimeElementRemoval);
        fprintf(outputFile, "%ld\n", elapsedTimeListReversal);

        fclose(outputFile);
    } else {
        perror("Error: Unable to open the file for writing");
    }
}

void writeResultsToCSV(const char* fileName, long results[], int numResults) {
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < numResults; i++) {
        fprintf(file, "%ld\n", results[i]);
    }

    fclose(file);
}


int main() {
    int tests = 1000;
    long totalTimeAlloc = 0, totalTimeMemAccStatic = 0, totalTimeMemAccDynamic = 0, totalTimeThreadCr = 0;
    long totalElemAddition = 0, totalElemRemoval = 0, totalListReversal = 0;
    long totalTimeThreadCS = 0;
    int allocations = 1000; // array dimension
    int allocationThread = 5;

    long avgTimeMemAllocList[1000/100] = {0};
    long avgTimeMemAccStaticList[1000 / 100] = {0};
    long avgTimeMemAccDynamicList[1000 / 100]= {0};
    long avgTimeThreadCrList[1000 / 100] = {0};
    long avgTimeThreadCSList[1000 / 100]= {0};
    long avgTimeElemAddition[1000 / 100]= {0};
    long avgTimeElemRemoval[1000 / 100]= {0};
    long avgTimeReverse[1000 / 100]= {0};

    for (int i = 0; i < tests; i++) {
        totalTimeAlloc += measureMemoryAllocationTime(allocations);
        totalTimeMemAccStatic += measureStaticMemoryAccess(allocations);
        totalTimeMemAccDynamic += measureDynamicMemoryAccess(allocations);
        totalTimeThreadCr += measureThreadCreation(allocationThread);
        totalTimeThreadCS += measureThreadContextSwitch(allocationThread);
        totalElemAddition += measureElementAdditionToList(allocations);
        totalElemRemoval += measureElementRemovalFromList(allocations);
        totalListReversal += measureListReversal(allocations);

        if ((i + 1) % TEST_INTERVAL == 0) {
            int index = i / TEST_INTERVAL;
            avgTimeMemAllocList[index] = totalTimeAlloc / TEST_INTERVAL;
            avgTimeMemAccStaticList[index] = totalTimeMemAccStatic / TEST_INTERVAL;
            avgTimeMemAccDynamicList[index] = totalTimeMemAccDynamic / TEST_INTERVAL;
            avgTimeThreadCrList[index] = totalTimeThreadCr / TEST_INTERVAL;
            avgTimeThreadCSList[index] = totalTimeThreadCS / TEST_INTERVAL;
            avgTimeElemAddition[index] = totalElemAddition / TEST_INTERVAL;
            avgTimeElemRemoval[index] = totalElemRemoval/TEST_INTERVAL;
            avgTimeReverse[index] = totalListReversal/TEST_INTERVAL;
            // Add other calculations as needed

            // Reset totals
            totalTimeAlloc = 0;
            totalTimeMemAccStatic = 0;
            totalTimeMemAccDynamic = 0;
            totalTimeThreadCr = 0;
            totalTimeThreadCS = 0;
            totalElemAddition = 0;
            totalElemRemoval = 0;
            totalListReversal = 0;

        }
    }

    printf("%ld\n", calculateAverage(avgTimeMemAllocList, 10));
    printf("%ld\n", calculateAverage(avgTimeMemAccStaticList, 10));
    printf("%ld\n", calculateAverage(avgTimeMemAccDynamicList, 10));
    printf("%ld\n", calculateAverage(avgTimeThreadCrList, 10));
    printf("%ld\n", calculateAverage(avgTimeThreadCSList, 10));
    printf("%ld\n", calculateAverage(avgTimeElemAddition, 10));
    printf("%ld\n", calculateAverage(avgTimeElemRemoval, 10));
    printf("%ld\n", calculateAverage(avgTimeReverse, 10));

    // Print and write results to a file
    writeResultToFile("c_results.txt", calculateAverage(avgTimeMemAllocList, 10), calculateAverage(avgTimeMemAccStaticList, 10),calculateAverage(avgTimeMemAccDynamicList, 10), calculateAverage(avgTimeThreadCrList, 10), calculateAverage(avgTimeThreadCSList, 10), calculateAverage(avgTimeElemAddition, 10), calculateAverage(avgTimeElemRemoval, 10),  calculateAverage(avgTimeReverse, 10), tests);


    writeResultsToCSV("mem_alloc.csv", avgTimeMemAllocList, NUM_TESTS / TEST_INTERVAL);
    writeResultsToCSV("mem_acc_static.csv", avgTimeMemAccStaticList, NUM_TESTS / TEST_INTERVAL);
    writeResultsToCSV("mem_acc_dynamic.csv", avgTimeMemAccDynamicList, NUM_TESTS / TEST_INTERVAL);
    writeResultsToCSV("thread_creation.csv", avgTimeThreadCrList, NUM_TESTS / TEST_INTERVAL);
    writeResultsToCSV("thread_context_switch.csv", avgTimeThreadCSList, NUM_TESTS / TEST_INTERVAL);
    writeResultsToCSV("element_addition.csv", avgTimeElemAddition, NUM_TESTS / TEST_INTERVAL);
    writeResultsToCSV("element_removal.csv", avgTimeElemRemoval, NUM_TESTS / TEST_INTERVAL);
    writeResultsToCSV("reverse.csv", avgTimeReverse, NUM_TESTS / TEST_INTERVAL);

    return 0;
}


