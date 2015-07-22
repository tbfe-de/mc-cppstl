#include <cassert>
#include <ctime>
#include <tuple>

template<typename Callable>
double cpu_seconds(Callable fragment) {
    assert(std::clock() != (std::clock_t)(-1));
    const auto start_time = std::clock();
//  -------------------------
    fragment(); // to time
//  -------------------------
    const auto end_time = std::clock();
    return static_cast<double>(end_time - start_time)
         / static_cast<double>(CLOCKS_PER_SEC);
}

#include<iostream>

template<typename Callable>
std::tuple<int, double>
cpu_seconds(int runs, Callable fragment, double min = .5) {
    double delta_time;
    bool multiply{0};
    do {
        runs *= (multiply ? (multiply = 1) : 2);
        const auto start_time = std::clock();
        for (auto i = 0; i < runs; ++i)
            fragment(); // to time
        const auto end_time = std::clock();
        delta_time = static_cast<double>(end_time - start_time)
                   / static_cast<double>(CLOCKS_PER_SEC);
    } while (delta_time < min);
    return std::make_tuple(runs, delta_time);
}
