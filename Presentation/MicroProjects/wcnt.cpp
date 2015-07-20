#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <string>

using WordList = std::map<std::string, int>;

std::ostream &operator<<(std::ostream &lhs, const WordList::value_type &rhs) {
    return lhs << rhs.first << ": " << rhs.second;
}

int main() {
    WordList wlist;
    using inwords = std::istream_iterator<std::string>;
    std::for_each(inwords{std::cin}, inwords{}, [&wlist](std::string w) { ++wlist[w]; });
#if 1
    for (const auto &e : wlist) std::cout << e << '\n';
#else
    using outwords = std::ostream_iterator<WordList::value_type>;
    std::copy(std::begin(wlist), std::end(wlist), outwords{std::cout, "\n"});
#endif
}
