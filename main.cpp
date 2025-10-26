#include <iostream>
#include <array>
#include <utility>

template<int N>
struct Fact {
    static constexpr unsigned long long value = N * Fact<N - 1>::value;
};

template<>
struct Fact<0> {
    static constexpr unsigned long long value = 1;
};

template<int N>
struct Fib {
    static constexpr unsigned long long value = Fib<N - 1>::value + Fib<N - 2>::value;
};

template<>
struct Fib<0> { static constexpr unsigned long long value = 0; };
template<>
struct Fib<1> { static constexpr unsigned long long value = 1; };

template<std::size_t... Is>
void fill(std::array<unsigned long long, sizeof...(Is)>& fact,
    std::array<unsigned long long, sizeof...(Is)>& fib,
    std::index_sequence<Is...>)
{
    ((fact[Is] = Fact<Is>::value, fib[Is] = Fib<Is>::value), ...);
}

int main() {
    constexpr int N = 4000;
    std::array<unsigned long long, N> fact{};
    std::array<unsigned long long, N> fib{};

    fill(fact, fib, std::make_index_sequence<N>{});

    for (int i = 0; i < N; ++i) {
        std::cout << "Fact[" << i << "] = " << fact[i]
            << ", Fib[" << i << "] = " << fib[i] << "\n";
    }

    return 0;
}
