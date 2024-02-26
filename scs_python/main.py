import time
import threading
from concurrent.futures import ThreadPoolExecutor

TEST_INTERVAL = 100
NUM_TESTS = 1000
NUM_ITERATIONS = 1000
def dummy_function():
    pass

def calculate_average(lst):
    if not lst:
        return 0

    lst.sort()

    middle = len(lst) // 2
    if len(lst) % 2 == 1:
        # If the list size is odd, return the middle element
        return lst[middle]
    else:
        # If the list size is even, return the average of the middle two elements
        return (lst[middle - 1] + lst[middle]) / 2

def measure_memory_allocation_time(size):
    start_time = time.perf_counter_ns()
    dynamic_list = [0] * size
    end_time = time.perf_counter_ns()
    return end_time - start_time

def measure_static_memory_access(size):
    data_list = [0] * size
    start_time = time.perf_counter_ns()
    for _ in data_list:
        element = _
    end_time = time.perf_counter_ns()
    return end_time - start_time

def measure_dynamic_memory_access(size):
    dynamic_array = [0] * size

    # Start timer
    start_time = time.perf_counter_ns()

    # Accessing and modifying each element in the list
    for i in range(size):
        dynamic_array[i] = i
        element = dynamic_array[i]

    # End timer
    end_time = time.perf_counter_ns()

    # Calculate duration in nanoseconds
    duration = end_time - start_time

    return duration
def measure_thread_creation(num_threads):
    start_time = time.perf_counter_ns()
    threads = [threading.Thread(target=lambda: None) for _ in range(num_threads)]
    for thread in threads:
        thread.start()
    for thread in threads:
        thread.join()
    end_time = time.perf_counter_ns()
    return end_time - start_time
def measure_thread_context_switch(n):
    start_time = time.perf_counter_ns()
    with ThreadPoolExecutor() as executor:
        futures = [executor.submit(dummy_function) for _ in range(n)]
        for future in futures:
            future.result()
    end_time = time.perf_counter_ns()
    return end_time - start_time

def measure_element_addition_to_list(num_elements):
    # Start timing
    start_time = time.perf_counter_ns()

    # Add N elements to the list
    my_list = [i for i in range(num_elements)]

    # Stop timing
    end_time = time.perf_counter_ns()

    # Calculate the time elapsed in nanoseconds
    duration = end_time - start_time
    return duration
def measure_element_removal_from_list(num_elements):
    my_list = list(range(num_elements * 2))  # Create a list with extra elements
    start_time = time.perf_counter_ns()
    for _ in range(num_elements):
        my_list.pop()  # Remove elements from the end
    end_time = time.perf_counter_ns()
    return end_time - start_time

def measure_list_reversal(num_elements):
    # Create a list with 'num_elements' elements
    my_list = list(range(num_elements))

    # Start timing
    start_time = time.perf_counter_ns()

    # Reverse the list
    my_list.reverse()

    # Alternatively, you could use slicing: my_list = my_list[::-1]

    # Stop timing
    end_time = time.perf_counter_ns()

    # Calculate the time elapsed in nanoseconds
    duration = end_time - start_time
    return duration

def write_result_to_file(file_name, elapsed_time_mem_alloc, elapsed_time_mem_acc_static, elapsed_time_mem_acc_dynamic, elapsed_time_thread_cr, elapsed_time_thread_cs, elapsed_time_element_addition, elapsed_time_element_removal, elapsed_time_list_reversal):
    try:
        with open(file_name, 'w') as output_file:
            output_file.write(f"{int(elapsed_time_mem_alloc)}\n")
            output_file.write(f"{int(elapsed_time_mem_acc_static)}\n")
            output_file.write(f"{int(elapsed_time_mem_acc_dynamic)}\n")
            output_file.write(f"{int(elapsed_time_thread_cr)}\n")
            output_file.write(f"{int(elapsed_time_thread_cs)}\n")
            output_file.write(f"{int(elapsed_time_element_addition)}\n")
            output_file.write(f"{int(elapsed_time_element_removal)}\n")
            output_file.write(f"{int(elapsed_time_list_reversal)}\n")
    except IOError as e:
        print(f"Error: Unable to open the file {file_name} for writing. {e}")

def write_results_to_csv(file_name, results):
    try:
        with open(file_name, 'w') as file:
            for result in results:
                file.write(f"{int(result)}\n")
    except IOError as e:
        print(f"Error opening file {file_name}. {e}")
    
def main():
    tests = 1000
    total_time_alloc = 0
    total_time_mem_acc_static = 0
    total_time_mem_acc_dynamic = 0
    total_time_thread_cr = 0
    total_time_thread_cs = 0
    total_elem_addition = 0
    total_elem_removal = 0
    total_list_reversal = 0

    allocations = 1000  # array dimension
    allocation_thread = 5

    avg_time_mem_alloc_list = [0] * (tests // TEST_INTERVAL)
    avg_time_mem_acc_static_list = [0] * (tests // TEST_INTERVAL)
    avg_time_mem_acc_dynamic_list = [0] * (tests // TEST_INTERVAL)
    avg_time_thread_cr_list = [0] * (tests // TEST_INTERVAL)
    avg_time_thread_cs_list = [0] * (tests // TEST_INTERVAL)
    avg_time_elem_addition = [0] * (tests // TEST_INTERVAL)
    avg_time_elem_removal = [0] * (tests // TEST_INTERVAL)
    avg_time_reverse = [0] * (tests // TEST_INTERVAL)

    for i in range(tests):
        total_time_alloc += measure_memory_allocation_time(allocations)
        total_time_mem_acc_static += measure_static_memory_access(allocations)
        total_time_mem_acc_dynamic += measure_dynamic_memory_access(allocations)
        total_time_thread_cr += measure_thread_creation(allocation_thread)
        total_time_thread_cs += measure_thread_context_switch(allocation_thread)
        total_elem_addition += measure_element_addition_to_list(allocations)
        total_elem_removal += measure_element_removal_from_list(allocations)
        total_list_reversal += measure_list_reversal(allocations)

        if (i + 1) % TEST_INTERVAL == 0:
            index = i // TEST_INTERVAL
            avg_time_mem_alloc_list[index] = total_time_alloc / TEST_INTERVAL
            avg_time_mem_acc_static_list[index] = total_time_mem_acc_static / TEST_INTERVAL
            avg_time_mem_acc_dynamic_list[index] = total_time_mem_acc_dynamic / TEST_INTERVAL
            avg_time_thread_cr_list[index] = total_time_thread_cr / TEST_INTERVAL
            avg_time_thread_cs_list[index] = total_time_thread_cs / TEST_INTERVAL
            avg_time_elem_addition[index] = total_elem_addition / TEST_INTERVAL
            avg_time_elem_removal[index] = total_elem_removal / TEST_INTERVAL
            avg_time_reverse[index] = total_list_reversal / TEST_INTERVAL

            total_time_alloc = 0
            total_time_mem_acc_static = 0
            total_time_mem_acc_dynamic = 0
            total_time_thread_cr = 0
            total_time_thread_cs = 0
            total_elem_addition = 0
            total_elem_removal = 0
            total_list_reversal = 0

    avg_mem_alloc = int(calculate_average(avg_time_mem_alloc_list))
    avg_mem_acc_static = int(calculate_average(avg_time_mem_acc_static_list))
    avg_mem_acc_dynamic = int(calculate_average(avg_time_mem_acc_dynamic_list))
    avg_thread_cr = int(calculate_average(avg_time_thread_cr_list))
    avg_thread_cs = int(calculate_average(avg_time_thread_cs_list))
    avg_elem_addition = int(calculate_average(avg_time_elem_addition))
    avg_elem_removal = int(calculate_average(avg_time_elem_removal))
    avg_list_reversal = int(calculate_average(avg_time_reverse))

    # Print averages
    print(avg_mem_alloc)
    print(avg_mem_acc_static)
    print(avg_mem_acc_dynamic)
    print(avg_thread_cr)
    print(avg_thread_cs)
    print(avg_elem_addition)
    print(avg_elem_removal)
    print(avg_list_reversal)

    write_result_to_file("python_results.txt", calculate_average(avg_time_mem_alloc_list), calculate_average(avg_time_mem_acc_static_list),
                         calculate_average(avg_time_mem_acc_dynamic_list), calculate_average(avg_time_thread_cr_list), calculate_average(avg_time_thread_cs_list),
                         calculate_average(avg_time_elem_addition), calculate_average(avg_time_elem_removal), calculate_average(avg_time_reverse),)

    write_results_to_csv("mem_alloc.csv", avg_time_mem_alloc_list)
    write_results_to_csv("mem_acc_static.csv", avg_time_mem_acc_static_list)
    write_results_to_csv("mem_acc_dynamic.csv", avg_time_mem_acc_dynamic_list)
    write_results_to_csv("thread_creation.csv", avg_time_thread_cr_list)
    write_results_to_csv("thread_context_switch.csv", avg_time_thread_cs_list)
    write_results_to_csv("element_addition.csv", avg_time_elem_addition)
    write_results_to_csv("element_removal.csv", avg_time_elem_removal)
    write_results_to_csv("reverse.csv", avg_time_reverse)

if __name__ == "__main__":
    main()
