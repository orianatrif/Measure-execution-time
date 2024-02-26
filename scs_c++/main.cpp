#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include <future>

const int TEST_INTERVAL = 100;
const int NUM_TESTS = 1000;
// Measure memory allocation time
//long measureMemoryAllocationTime(int size) {
//    auto startTime = std::chrono::high_resolution_clock::now();
//    std::vector<int> array(size);
//    auto endTime = std::chrono::high_resolution_clock::now();
//    return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
//}
void dummyFunction() {
    // Perform a simple operation
}

long measureMemoryAllocationTime(int size) {
    auto start_time = std::chrono::high_resolution_clock::now();

    int* dynamicArray = new int[size];

    auto end_time = std::chrono::high_resolution_clock::now();

    // Delete the allocated memory
    delete[] dynamicArray;

    return std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
}
// Measure memory access static
long measureStaticMemoryAccess(int size) {
    int* arr = new int[size];

    // Initialize the array
    for (int i = 0; i < size; ++i) {
        arr[i] = i;
    }

    // Measuring access time
    auto start = std::chrono::high_resolution_clock::now();

    // Accessing all elements in the array
    for (int i = 0; i < size; ++i) {
        // Perform some trivial operation to prevent compiler optimizations
        arr[i] += 1;
    }

    auto end = std::chrono::high_resolution_clock::now();

    // Deallocate the array
    delete[] arr;

    // Calculating the duration in nanoseconds
    long duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    return duration;
}
// Measure memory access dynamically
long measureDynamicMemoryAccess(int size) {
    std::vector<int> dynamicArray(size);
    auto startTime = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; i++) {
        dynamicArray[i] = i;
        int element = dynamicArray[i];
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
}
// Measure thread creation
long measureThreadCreation(int numThreads) {
    auto startTime = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> threads;
    threads.reserve(numThreads);

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([] {});
    }

    for (auto &thread : threads) {
        thread.join();
    }

    auto endTime = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
}
// Measure thread context switch
long measureThreadContextSwitch(int numThreads) {
    std::vector<std::thread> threads;
    threads.reserve(numThreads);

    // Start timing using std::chrono::high_resolution_clock
    auto start = std::chrono::high_resolution_clock::now();

    // Create threads
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(dummyFunction);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    return duration;
}
// Measure element addition to list
long measureElementAdditionToList(int numElements) {
    struct timespec start, end;

    // Use 'new' for memory allocation in C++
    int* myList = new int[numElements];
    if (myList == nullptr) {
        std::cerr << "Memory allocation failed.\n";
        std::exit(1);
    }

    // Start the timer
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Add N elements to the list
    for (int i = 0; i < numElements; i++) {
        myList[i] = i; // Add an element to the list
    }

    // Stop the timer
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Free the allocated memory using 'delete[]'
    delete[] myList;

    // Calculate and return the duration in nanoseconds
    return (end.tv_sec - start.tv_sec) * 1000000000L + (end.tv_nsec - start.tv_nsec);
}
// Measure element removal from list
long measureElementRemovalFromList(int numElements) {
    int *myList = new int[numElements];

    for (int i = 0; i < numElements; i++) {
        myList[i] = i; // Add N elements to the list
    }

    auto startTime = std::chrono::high_resolution_clock::now();
    // Remove N elements from the list
    for (int i = 0; i < numElements; i++) {
        for (int j = i; j < numElements - 1; j++) {
            myList[j] = myList[j + 1];
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();

    delete[] myList; // Don't forget to free the allocated memory

    // Calculate the time elapsed in nanoseconds
    return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
}
// Measure list reversal
long measureListReversal(int numElements) {
    // Dynamic memory allocation using 'new'
    int *myList = new int[numElements];
    if (myList == nullptr) {
        // Handle memory allocation failure
        std::cerr << "Memory allocation failed.\n";
        return -1;
    }

    // Add elements to the list
    for (int i = 0; i < numElements; i++) {
        myList[i] = i;
    }

    // Start timing using std::chrono
    auto start = std::chrono::high_resolution_clock::now();

    // Reverse the list
    for (int i = 0, j = numElements - 1; i < j; i++, j--) {
        int temp = myList[i];
        myList[i] = myList[j];
        myList[j] = temp;
    }

    // Stop timing
    auto end = std::chrono::high_resolution_clock::now();

    // Free the memory allocated
    delete[] myList;

    // Calculate the time elapsed in nanoseconds
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    return duration;
}
// Write results to a file
void writeResultToFile(const std::string& fileName, long elapsedTimeMemAlloc, long elapsedTimeMemAccStatic, long elapsedTimeMemAccDynamic, long elapsedTimeThreadCr, long elapsedTimeThreadCS, long elapsedTimeElementAddition, long elapsedTimeElementRemoval, long elapsedTimeListReversal, int numberOfAllocations) {
    std::ofstream outputFile(fileName);
    if (outputFile.is_open()) {
        //outputFile << "C++ results:\n";
        outputFile << elapsedTimeMemAlloc << "\n";
        outputFile << elapsedTimeMemAccStatic << "\n";
        outputFile  << elapsedTimeMemAccDynamic << "\n";
        outputFile << elapsedTimeThreadCr << "\n";
        outputFile << elapsedTimeThreadCS << "\n";
        outputFile << elapsedTimeElementAddition << "\n";
        outputFile << elapsedTimeElementRemoval << "\n";
        outputFile << elapsedTimeListReversal << "\n";
        //outputFile << "Number of allocations: " << numberOfAllocations << "\n";
        outputFile.close();
    } else {
        std::cerr << "Error: Unable to open the file " << fileName << " for writing." << std::endl;
    }
}

void writeResultsToCSV(const std::string& fileName, const std::vector<long>& results) {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    for (auto result : results) {
        file << result << std::endl;
    }
}

long calculateAverage(std::vector<long>& list) {
    if (list.empty()) {
        return 0;
    }

    // Sort the list
    std::sort(list.begin(), list.end());

    size_t middle = list.size() / 2;
    if (list.size() % 2 == 1) {
        // If the list size is odd, return the middle element
        return list[middle];
    } else {
        // If the list size is even, return the average of the middle two elements
        return (list[middle - 1] + list[middle]) / 2;
    }
}

int main() {
    int tests = 1000;
    long totalTimeAlloc = 0, totalTimeMemAccStatic = 0, totalTimeMemAccDynamic = 0, totalTimeThreadCr = 0;
    long totalElemAddition = 0, totalElemRemoval = 0, totalListReversal = 0;
    long totalTimeThreadCS = 0;
    int allocations = 1000; // array dimension
    int allocationThread = 5;

    std::vector<long> avgTimeMemAllocList(NUM_TESTS / TEST_INTERVAL);
    std::vector<long> avgTimeMemAccStaticList(NUM_TESTS / TEST_INTERVAL);;
    std::vector<long> avgTimeMemAccDynamicList(NUM_TESTS / TEST_INTERVAL);
    std::vector<long> avgTimeThreadCrList(NUM_TESTS / TEST_INTERVAL);
    std::vector<long> avgTimeThreadCSList(NUM_TESTS / TEST_INTERVAL);
    std::vector<long> avgTimeElemAddition(NUM_TESTS / TEST_INTERVAL);
    std::vector<long> avgTimeElemRemoval(NUM_TESTS / TEST_INTERVAL);
    std::vector<long> avgTimeReverse(NUM_TESTS / TEST_INTERVAL);

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

    std::cout << calculateAverage(avgTimeMemAllocList) << std::endl;
    std::cout << calculateAverage(avgTimeMemAccStaticList) << std::endl;
    std::cout << calculateAverage(avgTimeMemAccDynamicList) << std::endl;
    std::cout << calculateAverage(avgTimeThreadCrList) << std::endl;
    std::cout << calculateAverage(avgTimeThreadCSList) << std::endl;
    std::cout << calculateAverage(avgTimeElemAddition) << std::endl;
    std::cout << calculateAverage(avgTimeElemRemoval) << std::endl;
    std::cout << calculateAverage(avgTimeReverse) << std::endl;

    // Print and write results to a file
    writeResultToFile("c_results.txt", calculateAverage(avgTimeMemAllocList), calculateAverage(avgTimeMemAccStaticList),calculateAverage(avgTimeMemAccDynamicList), calculateAverage(avgTimeThreadCrList), calculateAverage(avgTimeThreadCSList), calculateAverage(avgTimeElemAddition), calculateAverage(avgTimeElemRemoval),  calculateAverage(avgTimeReverse), tests);


    writeResultsToCSV("mem_alloc.csv", avgTimeMemAllocList);
    writeResultsToCSV("mem_acc_static.csv", avgTimeMemAccStaticList);
    writeResultsToCSV("mem_acc_dynamic.csv", avgTimeMemAccDynamicList);
    writeResultsToCSV("thread_creation.csv", avgTimeThreadCrList);
    writeResultsToCSV("thread_context_switch.csv", avgTimeThreadCSList);
    writeResultsToCSV("element_addition.csv", avgTimeElemAddition);
    writeResultsToCSV("element_removal.csv", avgTimeElemRemoval);
    writeResultsToCSV("reverse.csv", avgTimeReverse);

    return 0;
}

