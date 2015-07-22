#include <cmath>
#include <iostream>

#include "cpu_seconds.h"

constexpr auto N = 100000;

volatile long double sqrt2;

int main() {
    std::cout << "timing a single sqrt-call: " << std::flush;
    std::cout << cpu_seconds([&] {
     // ---------------------
        ::sqrt2 = sqrt(2.0L);
     // ---------------------
    })*1e3 << " msec\n";

    std::cout << "timing "<< N << " hand-wrapped sqrt-calls: " << std::flush;
    const auto total_sec_for_N = cpu_seconds([&] {
     // ------------------------------
        for (auto i = 0; i < N; ++i)
            ::sqrt2 = std::sqrt(2.0L);
     // ------------------------------
    });
    std::cout << 1e6*total_sec_for_N/N << " µsec per call"
              << " (" << total_sec_for_N << " secs / " << N << " calls)\n";
              
    std::cout << "timing auto-wrapped sqrt-calls: " << std::flush;
    int calls; double secs;
    std::tie(calls, secs) = cpu_seconds(10000, [&] {
     // ------------------------------
        ::sqrt2 = std::sqrt(2.0L);
     // ------------------------------
    });
    std::cout << 1e6*secs/calls << " µsec per call"
              << " (" << secs << " secs / " << calls << " calls)\n";
    
    std::cout << "timing auto-wrapped assignments of constant: " << std::flush;
    std::tie(calls, secs) = cpu_seconds(10000, [&] {
     // ------------------------------
        ::sqrt2 = 1.4142L;
     // ------------------------------
    });
    std::cout << 1e6*secs/calls << " µsec per call"
              << " (" << secs << " secs / " << calls << " calls)\n";
}
