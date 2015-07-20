#include <iostream>
#define XP(what, expect)\
    do {\
        const auto &w = what;\
        const auto &e = expect;\
        std::cout << "[" << __LINE__ << "] " #what " --> " << w;\
        if (w != e)\
            std::cout << " !=! " <<  e << " <-- (expected)";\
        std::cout << std::endl;\
    } while (0)

#include <algorithm>
#include <sstream>
#include <iterator>

int main() {
    const int x[] = { 1, 3, 5, 8, 1, 12, 1, 3 };
    std::ostringstream oss;
    std::unique_copy(std::begin(x), std::end(x),
                     std::ostream_iterator<int>(oss, " "));
    XP(oss.str(), "1 3 5 8 12 ");
}
