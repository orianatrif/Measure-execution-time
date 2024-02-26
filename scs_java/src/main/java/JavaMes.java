//import java.io.BufferedWriter;
//import java.io.FileWriter;
//import java.io.IOException;
//import java.util.ArrayList;
//import java.util.Collections;
//import java.util.List;
//
//public class JavaMes {
//
//    public static void main(String[] args) {
//        int numberTestsTotal = 1000;
//        int testInterval = 100; // Interval for calculating means
//        List<Long> avgTimeMemAllocList = new ArrayList<>();
//        List<Long> avgTimeMemAccStaticList = new ArrayList<>();
//        List<Long> avgTimeMemAccDynamicList = new ArrayList<>();
//        List<Long> avgTimeThreadCrList = new ArrayList<>();
//        List<Long> avgTimeThreadCSList = new ArrayList<>();
//        List<Long> avgTimeAddListList = new ArrayList<>();
//        List<Long> avgTimeRemoveList = new ArrayList<>();
//        List<Long> avgTimeReverseList = new ArrayList<>();
//
//        long totalTimeAlloc = 0, totalTimeMemAccStatic = 0, totalTimeMemAccDynamic = 0, totalTimeThreadCr = 0;
//        long totalTimeThreadCS = 0, totalTimeAddList = 0, totalTimeRemoveList = 0, totalTimeReverse = 0;
//        int allocations = 10000; // Array dimension
//        int allocationThread = 10;
//
//        for (int i = 0; i < numberTestsTotal; i++) {
//            long elapsedTimeMemAlloc = measureMemoryAllocationTime(allocations);
//            long elapsedTimeMemAccStatic = measureStaticMemoryAccess(allocations);
//            long elapsedTimeMemAccDynamic = measureDynamicMemoryAccess(allocations);
//            long elapsedTimeThreadCr = measureThreadCreation(allocationThread);
//            long elapsedTimeThreadCS = measureThreadContextSwitch(allocationThread);
//            long elapsedTimeAddList = measureElementAdditionToList(allocations);
//            long elapsedTimeRemoveList = measureElementRemovalFromList(allocations);
//            long elapsedTimeReverse = measureListReversal(allocations);
//
//            totalTimeMemAccDynamic += elapsedTimeMemAccDynamic;
//            totalTimeAlloc += elapsedTimeMemAlloc;
//            totalTimeMemAccStatic += elapsedTimeMemAccStatic;
//            totalTimeThreadCr += elapsedTimeThreadCr;
//            totalTimeThreadCS += elapsedTimeThreadCS;
//            totalTimeAddList += elapsedTimeAddList;
//            totalTimeRemoveList += elapsedTimeRemoveList;
//            totalTimeReverse += elapsedTimeReverse;
//
//            // Calculate averages at every 100 tests
//            if ((i + 1) % testInterval == 0) {
//                avgTimeMemAllocList.add(totalTimeAlloc / testInterval);
//                avgTimeMemAccStaticList.add(totalTimeMemAccStatic / testInterval);
//                avgTimeMemAccDynamicList.add(totalTimeMemAccDynamic / testInterval);
//                avgTimeThreadCrList.add(totalTimeThreadCr / testInterval);
//                avgTimeThreadCSList.add(totalTimeThreadCS / testInterval);
//                avgTimeAddListList.add(totalTimeAddList / testInterval);
//                avgTimeRemoveList.add(totalTimeRemoveList / testInterval);
//                avgTimeReverseList.add(totalTimeReverse / testInterval);
//
//                totalTimeAlloc = 0;
//                totalTimeMemAccStatic = 0;
//                totalTimeMemAccDynamic = 0;
//                totalTimeThreadCr = 0;
//                totalTimeThreadCS = 0;
//                totalTimeAddList = 0;
//                totalTimeRemoveList = 0;
//                totalTimeReverse = 0;
//            }
//        }
//
//        // Write results to CSV file
//        writeResultsToCSV("java_results.csv", avgTimeMemAllocList, avgTimeMemAccStaticList, avgTimeMemAccDynamicList, avgTimeThreadCrList, avgTimeThreadCSList, avgTimeAddListList, avgTimeRemoveList, avgTimeReverseList);
//        writeResultToFile("java_results.txt", calculateAverage(avgTimeMemAllocList),calculateAverage(avgTimeMemAccStaticList), calculateAverage(avgTimeMemAccDynamicList), calculateAverage(avgTimeThreadCrList),calculateAverage(avgTimeThreadCSList),calculateAverage(avgTimeAddListList),calculateAverage(avgTimeRemoveList),calculateAverage(avgTimeReverseList));
//
//    }
//
//    private static long measureMemoryAllocationTime(int size) {
//        long startTime = System.nanoTime();
//        int[] dynamicArray = new int[size];
//        long endTime = System.nanoTime();
//        return endTime - startTime;
//    }
//
//    private static long measureStaticMemoryAccess(int size) {
//        int[] staticArray = new int[size];
//        long startTime = System.nanoTime();
//        for (int i = 0; i < size; i++) {
//            int element = staticArray[i];
//        }
//        long endTime = System.nanoTime();
//        return endTime - startTime;
//    }
//
//    private static long measureDynamicMemoryAccess(int size) {
//        int[] dynamicArray = new int[size];
//        long startTime = System.nanoTime();
//        for (int i = 0; i < size; i++) {
//            dynamicArray[i] = i;
//            int element = dynamicArray[i];
//        }
//        long endTime = System.nanoTime();
//        return endTime - startTime;
//    }
//
//    private static long measureThreadCreation(int n) {
//        Thread[] threads = new Thread[n];
//        long startTime = System.nanoTime();
//
//        // Create and start each thread
//        for (int i = 0; i < n; i++) {
//            threads[i] = new Thread(() -> {});
//            threads[i].start();
//        }
//
//        // Wait for each thread to finish
//        for (int i = 0; i < n; i++) {
//            try {
//                threads[i].join();
//            } catch (InterruptedException e) {
//                e.printStackTrace();
//            }
//        }
//
//        long endTime = System.nanoTime();
//        return endTime - startTime;
//    }
//
//    private static long measureThreadContextSwitch(int numThreads) {
//        final Object lock = new Object();
//        final long[] elapsedTime = new long[numThreads];
//
//        for (int i = 0; i < numThreads; i++) {
//            int finalI = i;
//            Thread thread = new Thread(() -> {
//                long startTime = System.nanoTime();
//                synchronized (lock) {
//                    lock.notify();
//                    try {
//                        lock.wait();
//                    } catch (InterruptedException e) {
//                        e.printStackTrace();
//                    }
//                }
//                long endTime = System.nanoTime();
//                elapsedTime[finalI] = endTime - startTime;
//            });
//
//            synchronized (lock) {
//                thread.start();
//                try {
//                    lock.wait();
//                } catch (InterruptedException e) {
//                    e.printStackTrace();
//                }
//            }
//
//            synchronized (lock) {
//                lock.notify();
//            }
//
//            try {
//                thread.join();
//            } catch (InterruptedException e) {
//                e.printStackTrace();
//            }
//        }
//
//        long totalElapsedTime = 0;
//        for (long time : elapsedTime) {
//            totalElapsedTime += time;
//        }
//
//        return totalElapsedTime / numThreads;
//    }
//
//    private static long measureElementAdditionToList(int numElements) {
//        long startTime = System.nanoTime();
//
//        List<Integer> myList = new ArrayList<>();
//
//        for (int i = 0; i < numElements; i++) {
//            myList.add(42);  // Add an element to the list
//        }
//
//        long endTime = System.nanoTime();
//
//        return endTime - startTime;
//    }
//
//    private static long measureElementRemovalFromList(int numElements) {
//        List<Integer> myList = new ArrayList<>();
//
//        for (int i = 0; i < numElements; i++) {
//            myList.add(i);  // Add elements to the list
//        }
//        long startTime = System.nanoTime();
//
//        // Remove elements from the list
//        for (int i = 0; i < numElements; i++) {
//            myList.remove(0);
//        }
//        long endTime = System.nanoTime();
//        return endTime - startTime;
//    }
//
//    private static long measureListReversal(int numElements) {
//        List<Integer> myList = new ArrayList<>();
//
//        for (int i = 0; i < numElements; i++) {
//            myList.add(i);  // Add elements to the list
//        }
//
//        long startTime = System.nanoTime();
//
//        // Reverse the list
//        Collections.reverse(myList);
//
//        long endTime = System.nanoTime();
//
//        return endTime - startTime;
//    }
//
//    private static void writeResultsToCSV(String fileName, List<Long>... lists) {
//        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName))) {
//            for (int i = 0; i < lists[0].size(); i++) {
//                for (List<Long> list : lists) {
//                    writer.write(list.get(i) + ",");
//                }
//                writer.newLine();
//            }
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//    }
//
//    public static long calculateAverage(List<Long> list) {
//        if (list == null || list.isEmpty()) {
//            return 0;
//        }
//
//        long sum = 0;
//        for (Long value : list) {
//            sum += value;
//        }
//
//        return sum / list.size();
//    }
//
//
//
//    private static void writeResultToFile(String fileName, long elapsedTimeMemAlloc, long elapsedTimeMemAccStatic, long elapsedTimeMemAccDynamic, long elapsedTimeThreadCr, long elapsedTimeThreadCS, long averageTimeAddList, long averageTimeRemove, long averageTimeReverse) {
//        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName))) {
//
//            writer.write(elapsedTimeMemAlloc + "\n"); //Average memory allocation
//            writer.write(elapsedTimeMemAccStatic + "\n");//Average memory access dynamic
//            writer.write(elapsedTimeMemAccDynamic + "\n");//Average memory access dynamic
//            writer.write(elapsedTimeThreadCr + "\n");//Average thread creation
//            writer.write(elapsedTimeThreadCS + "\n");//Average thread context switch
//            writer.write(averageTimeAddList + "\n");//Average add
//            writer.write(averageTimeRemove + "\n");//Average remove
//            writer.write(averageTimeReverse + "\n");//Average reverse
//
//            System.out.println(elapsedTimeMemAlloc); //Average memory allocation
//            System.out.println(elapsedTimeMemAccStatic);//Average memory access dynamic
//            System.out.println(elapsedTimeMemAccDynamic);//Average memory access dynamic
//            System.out.println(elapsedTimeThreadCr);//Average thread creation
//            System.out.println(elapsedTimeThreadCS);//Average thread context switch
//            System.out.println(averageTimeAddList);//Average add
//            System.out.println(averageTimeRemove);//Average remove
//            System.out.println(averageTimeReverse);//Average reverse
//
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//    }
//}
