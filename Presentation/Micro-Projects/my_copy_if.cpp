// add "missing" copy_if

#if 1
// -------------------------------------------------- stand-alone implementation
//
template<typename InIt, typename OutIt, typename Pred>
OutIt my_copy_if(InIt from, InIt upto, OutIt dest, Pred cond) {
    while (from != upto) {
        if (cond(*from))
            *dest++ = *from;
        ++from;
    }
    return dest;
}
#else
// ------------------------------------ std::remove_copy_if-based implementation
//
#include <algorithm>
#include <iterator>

template<typename InIt, typename OutIt, typename Pred>
OutIt my_copy_if(InIt from, InIt upto, OutIt dest, Pred cond) {
    typedef typename std::iterator_traits<InIt>::value_type vtype;
    return std::remove_copy_if(from, upto, dest,
                               [cond](const vtype &e) { return !cond(e); });
}
#endif

#include <cassert>
#include <sstream>
#include <iterator>
#include <iostream>

int main() {
    std::istringstream send{"1 -4 3 5 7 11 9 10 1 4"};
    typedef std::istream_iterator<int> isit;
    // using isit = std::istream_iterator<int>;
    std::ostringstream received;
    typedef std::ostream_iterator<int> osit;
    // using osit = std::ostream_iterator<int>;
    my_copy_if(isit{send}, isit{},
               osit{received, " "},
               [](int e) { return (e % 2 == 1); });
    assert(received.str() == "1 3 5 7 11 9 1 ");
}
