#include <array>
#include <tuple>
#include <iostream>
#include <type_traits>
#include <utility>

template <typename TupleOfArrays, std::size_t... ValuePositions, std::size_t... ArrayPositions>
constexpr auto create_combination_impl(const TupleOfArrays& arrays,
                                       std::index_sequence<ValuePositions...>,
                                       std::index_sequence<ArrayPositions...>) {
    return std::make_tuple(std::get<ArrayPositions>(arrays)[ValuePositions]...);
}

template <typename TupleOfArrays, std::size_t... ValuePositions>
constexpr auto create_combination(const TupleOfArrays& arrays, 
                                  std::index_sequence<ValuePositions...>) {
    return create_combination_impl(arrays,
                                   std::index_sequence<ValuePositions...>{},
                                   std::make_index_sequence<sizeof...(ValuePositions)>{});
}

template <std::size_t Level, typename TupleOfArrays, std::size_t... Selected>
constexpr auto build_level(const TupleOfArrays& arrays, std::index_sequence<Selected...>);

template <std::size_t Level,
          typename TupleOfArrays,
          std::size_t... Selected,
          std::size_t... CurrentIndices>
constexpr auto build_array_impl(const TupleOfArrays& arrays,
                                std::index_sequence<Selected...>,
                                std::index_sequence<CurrentIndices...>) {
    return std::array{build_level<Level + 1>(arrays,
                                           std::index_sequence<Selected..., CurrentIndices>{})...};
}

template <std::size_t Level, typename TupleOfArrays, std::size_t... Selected>
constexpr auto build_level(const TupleOfArrays& arrays, std::index_sequence<Selected...>) {
    constexpr std::size_t total_levels = std::tuple_size_v<std::remove_reference_t<TupleOfArrays>>;

    if constexpr (Level == total_levels) {
        return create_combination(arrays, std::index_sequence<Selected...>{});
    } else {
        using CurrentArray = std::remove_reference_t<decltype(std::get<Level>(arrays))>;
        constexpr std::size_t array_size = std::tuple_size_v<CurrentArray>;

        return build_array_impl<Level>(arrays,
                                       std::index_sequence<Selected...>{},
                                       std::make_index_sequence<array_size>{});
    }
}

template <typename... Arrays>
constexpr auto cartesian_product(const Arrays&... arrays) {
    static_assert(sizeof...(Arrays) > 0, "At least one array is required");
    auto packed = std::tuple<const Arrays&...>(arrays...);
    return build_level<0>(packed, std::index_sequence<>{});
}

int main() {
    constexpr std::array<int, 2> a1 = {1, 2};
    constexpr std::array<char, 3> a2 = {'A', 'B', 'C'};
    constexpr std::array<double, 2> a3 = {0.1, 0.2};

    constexpr auto product = cartesian_product(a1, a2, a3);

    // Просто используем product без static_assert
    const auto sample = product[1][2][1];
    std::cout << "sample: "
              << std::get<0>(sample) << ' '
              << std::get<1>(sample) << ' '
              << std::get<2>(sample) << '\n';

    return 0;
}