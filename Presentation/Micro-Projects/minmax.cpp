#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

#define N 5
std::list<std::vector<int>> testdata;
std::list<int> minimums, maximums;

int main() {
    for (auto i = N; --i > 0;) {
        testdata.push_back(std::vector<int>{});
        auto &vec = testdata.back();
        for (auto j = std::rand()%(2*N) + N; --j > 0;)
            vec.push_back(std::rand()%1000 + 1);
    }
    for (const auto &e : testdata) {
        minimums.push_back(*std::min_element(begin(e), end(e)));
        maximums.push_back(*std::max_element(begin(e), end(e)));
    }
#if N <= 10
    auto minimums_it = minimums.cbegin();
    auto maximums_it = maximums.cbegin();
    for (const auto &e : testdata) {
        std::cout << "«" << *minimums_it++ << "…" << *maximums_it++ << "»"
                  << " → ";
        std::copy(e.cbegin(), e.cend(),
                  std::ostream_iterator<int>(std::cout, "; "));
        std::cout << '\n';
    }
#endif
}
