#include <iostream>
#include <vector>
#include <deque>
#include <chrono>
#include <random>
#include <iterator>

template <typename RandomAccessIterator, typename Compare>
void restore_heap_property(RandomAccessIterator sequence_start,
                          std::size_t target_index,
                          std::size_t valid_size,
                          Compare comparison_rule) {
    std::size_t current_position = target_index;

    while (true) {
        std::size_t left_index = 2 * current_position + 1;
        if (left_index >= valid_size) break;

        std::size_t largest_index = current_position;
        std::size_t right_index = left_index + 1;

        if (comparison_rule(*(sequence_start + largest_index), *(sequence_start + left_index))) {
            largest_index = left_index;
        }
        
        if (right_index < valid_size && 
            comparison_rule(*(sequence_start + largest_index), *(sequence_start + right_index))) {
            largest_index = right_index;
        }

        if (largest_index == current_position) break;

        std::iter_swap(sequence_start + current_position, sequence_start + largest_index);
        current_position = largest_index;
    }
}

template <typename RandomAccessIterator, typename Compare>
void perform_heap_sort(RandomAccessIterator first_element, 
                      RandomAccessIterator last_element, 
                      Compare comparison_rule) {
    std::size_t total_items = static_cast<std::size_t>(last_element - first_element);
    
    if (total_items < 2) return;

    for (std::size_t node_index = total_items / 2; node_index > 0; --node_index) {
        restore_heap_property(first_element, node_index - 1, total_items, comparison_rule);
    }

    for (std::size_t remaining_elements = total_items; remaining_elements > 1; --remaining_elements) {
        std::iter_swap(first_element, first_element + remaining_elements - 1);
        restore_heap_property(first_element, 0, remaining_elements - 1, comparison_rule);
    }
}

bool sort_ascending(int left_value, int right_value) {
    return left_value < right_value;
}

struct SortDescending {
    bool operator()(int left_value, int right_value) const {
        return left_value > right_value;
    }
};

template <typename ContainerType>
long long measure_sorting_performance(ContainerType container_copy) {
    auto operation_start = std::chrono::steady_clock::now();
    
    perform_heap_sort(container_copy.begin(), container_copy.end(), 
                     [](int left_value, int right_value) { return left_value < right_value; });
    
    auto operation_end = std::chrono::steady_clock::now();
    
    return std::chrono::duration_cast<std::chrono::milliseconds>(operation_end - operation_start).count();
}

void compare_vector_vs_deque_performance() {
    const int DATA_SET_SIZE = 500000;

    std::vector<int> generated_numbers;
    generated_numbers.reserve(DATA_SET_SIZE);

    std::mt19937 random_number_generator(42);
    std::uniform_int_distribution<int> number_range(-1000000, 1000000);

    for (int iteration = 0; iteration < DATA_SET_SIZE; ++iteration) {
        generated_numbers.push_back(number_range(random_number_generator));
    }

    std::vector<int> vector_test_data(generated_numbers.begin(), generated_numbers.end());
    std::deque<int> deque_test_data(generated_numbers.begin(), generated_numbers.end());

    long long vector_sorting_time = measure_sorting_performance(vector_test_data);
    long long deque_sorting_time = measure_sorting_performance(deque_test_data);

    std::cout << "vector ms: " << vector_sorting_time << '\n';
    std::cout << "deque ms: " << deque_sorting_time << '\n';

    if (vector_sorting_time < deque_sorting_time) {
        std::cout << "faster: vector\n";
    } else {
        std::cout << "faster: deque\n";
    }
}

int main() {
    std::cout << "=== DEMONSTRATION OF HEAP SORT ===\n";
    
    std::cout << "\n=== PERFORMANCE COMPARISON ===\n";
    compare_vector_vs_deque_performance();
    
    return 0;
}