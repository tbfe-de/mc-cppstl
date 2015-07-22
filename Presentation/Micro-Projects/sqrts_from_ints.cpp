#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <iterator>

#include "cpu_seconds.h"

#define N 100000

int main() {
    std::vector<int> numbers;

    std::cout << "resizing numbers vector to " << N << " entries: " << std::flush;
    std::cout << cpu_seconds([&]{
     // ------------------
        numbers.resize(N);
     // ------------------
    })*1e3 << " msec\n";

    std::cout << "creating " << N << " numbers with std::iota: " << std::flush;
    std::cout << cpu_seconds([&]{
     // -----------------------------------------------------
        std::iota(std::begin(numbers), std::end(numbers), 1);
     // -----------------------------------------------------
    })*1e3 << " msec\n";

    std::vector<double> sqrts;
    std::cout << "transforming into square-roots with std::transform: " << std::flush;
    std::cout << cpu_seconds([&]{
     // ------------------------------------------------------------------------------
        std::transform(std::begin(numbers), std::end(numbers),
                       std::back_inserter(sqrts), [](int n) { return std::sqrt(n); });
     // ------------------------------------------------------------------------------
    })*1e3 << " msec\n";

#if N <= 20
    assert(numbers.size() == sqrts.size());
    auto sqrt_it = sqrts.cbegin();
    for (auto n : numbers)
        std::cout << std::setw(2) << n << " --> " << *sqrt_it++ << '\n';
#endif
    static_assert (N >= 1, "you're trying to fool me, aren't you ...?");
    int n = numbers.front();
    for (auto r : sqrts) {
        assert(std::fabs(r*r - n)/n < 0.001);
        ++n;
    }
    std::cout << "+++ DONE +++" << std::endl;
}
