#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iterator>
#include <iostream>
#include <vector>

void fill_with_percentage_dups(std::vector<int>::iterator from,
                               std::vector<int>::iterator upto,
                               double percentage) {
    assert(from != upto);
    assert(percentage >= 0.0);
    assert(percentage <= 100.0);
    typedef std::vector<int>::size_type size_type;
    typedef std::vector<int>::difference_type difference_type;
    const difference_type whole = upto - from;
    const double factor = (100.0-percentage)/100.0;
    const difference_type nodups = std::min(whole, static_cast<difference_type>(factor*whole));
    if (nodups == 0)
        std::fill_n(from, nodups, std::rand());
    else {
        assert(nodups > 0);
        assert(nodups <= (upto-from));
        std::iota(from, from + nodups, 0);
        std::generate(from + nodups, upto,
                      [from, nodups]() { return *(from + (std::rand() % nodups)); });
        std::random_shuffle(from, upto);
    }
}

#define N 30000

void show(const char *text, const std::vector<int> &vec) {
    std::cout << text << ": ";
    std::copy(std::begin(vec), std::end(vec),
              std::ostream_iterator<int>(std::cout, " "));
}

double remains(std::vector<int> &vec) {
    std::sort(vec.begin(), vec.end());
    auto new_end = std::unique(vec.begin(), vec.end());
    return 100.0*(vec.end() - new_end) / vec.size();
}

int main() {
    std::vector<int> td_no_dups(N);
    std::vector<int> td_10_percent(N);
    std::vector<int> td_50_percent(N);
    std::vector<int> td_70_percent(N);
    std::vector<int> td_all_dups(N);
    std::cout << "generating test data ... " << std::flush;
    fill_with_percentage_dups(std::begin(td_no_dups),
                                std::end(td_no_dups), 0.0);
    std::cout << "no dups ... " << std::flush;
    fill_with_percentage_dups(std::begin(td_10_percent),
                                std::end(td_10_percent), 10.0);
    std::cout << "10% dups ... " << std::flush;
    fill_with_percentage_dups(std::begin(td_50_percent),
                                std::end(td_50_percent), 50.0);
    std::cout << "50% dups ... " << std::flush;
    fill_with_percentage_dups(std::begin(td_70_percent),
                                std::end(td_70_percent), 70.0);
    std::cout << "70% dups ... " << std::flush;
    fill_with_percentage_dups(std::begin(td_all_dups),
                                std::end(td_all_dups), 100.0);
    std::cout << "all dups ... " << std::flush;
#if N <= 30
    show("\n* no dups  --> ", td_no_dups);
    show("\n* 10% dups --> ", td_10_percent);
    show("\n* 50% dups --> ", td_50_percent);
    show("\n* 70% dups --> ", td_70_percent);
    show("\n* all dups --> ", td_all_dups);
#endif
    assert(remains(td_no_dups) == 0.0);
    assert(0.1 > std::fabs(remains(td_10_percent) - 10.0));
    assert(0.1 > std::fabs(remains(td_50_percent) - 50.0));
    assert(0.1 > std::fabs(remains(td_70_percent) - 70.0));
    assert(0.1 > std::fabs(remains(td_all_dups) - (100.0-100.0/N)));
    std::cout << "\n+++ DONE +++" << std::endl;
}
