#include <iostream>
#include <tuple>
#include <string>

template <std::size_t CurrentPosition, typename TupleType>
struct TupleTraverser {
    template <typename OperationFunction>
    static void iterate_over(const TupleType& target_tuple, OperationFunction apply_operation) {

        apply_operation(std::get<CurrentPosition>(target_tuple));

        TupleTraverser<CurrentPosition + 1, TupleType>::iterate_over(target_tuple, apply_operation);
    }
};


template <typename TupleType>
struct TupleTraverser<std::tuple_size<TupleType>::value, TupleType> {
    template <typename OperationFunction>
    static void iterate_over(const TupleType&, OperationFunction) {
    }
};

template <typename... ElementTypes, typename OperationFunction>
void iterate_over_tuple(const std::tuple<ElementTypes...>& source_tuple, OperationFunction apply_operation) {

    TupleTraverser<0, std::tuple<ElementTypes...>>::iterate_over(source_tuple, apply_operation);
}

void demonstrate_mixed_types_tuple() {
    auto heterogeneous_tuple = std::make_tuple(42, 3.14159, std::string("example"), 'Z');
    
    std::cout << "tuple values: ";
    iterate_over_tuple(heterogeneous_tuple, [](const auto& each_element) {
        std::cout << each_element << ' ';
    });
    std::cout << '\n';
}

void demonstrate_numeric_tuple_sum() {
    std::tuple<int, int, int, int> numeric_sequence = {5, 10, 15, 20};
    
    int accumulated_sum = 0;
    iterate_over_tuple(numeric_sequence, [&accumulated_sum](int current_number) {
        accumulated_sum += current_number;
    });
    
    std::cout << "sum: " << accumulated_sum << '\n';
}

void show_advanced_example() {
    std::tuple<double, double, double> measurements = {1.5, 2.5, 3.5};
    double product = 1.0;
    
    iterate_over_tuple(measurements, [&product](double measurement_value) {
        product *= measurement_value;
    });
    
    std::cout << "product of measurements: " << product << '\n';
}

int main() {
    std::cout << "=== DEMONSTRATION 1: HETEROGENEOUS TUPLE ===\n";
    demonstrate_mixed_types_tuple();
    
    std::cout << "\n=== DEMONSTRATION 2: SUM OF NUMBERS ===\n";
    demonstrate_numeric_tuple_sum();
    
    std::cout << "\n=== DEMONSTRATION 3: ADVANCED EXAMPLE ===\n";
    show_advanced_example();
    
    return 0;
}