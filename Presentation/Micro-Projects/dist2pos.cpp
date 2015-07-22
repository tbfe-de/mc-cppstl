#include <algorithm>
#include <iostream>
#include <iterator>
#include <tuple>
#include <vector>

using XY = std::tuple<double, double>;

namespace std {
    std::ostream &operator<<(std::ostream &os, const XY &rhs) {
        return os << "XY{" << std::get<0>(rhs)
                  << ", " << std::get<1>(rhs) << "} ";
    }
}

void print(const char *header, const std::vector<XY> &v) {
    using namespace std;
    cout << "--------------- " << header << '\n';
#if 0
    for (const auto &e : v) cout << e << '\n';
#else
    copy(v.cbegin(), v.cend(), ostream_iterator<XY>{cout, "\n"});
#endif
}

const std::vector<XY> testdata = {
    XY{1.3,  7.5},
    XY{9.7, -3.1},
    XY{-2.0, 1.0},
    XY{7.1,  3.2},
    XY{-0.6, 1.1},
};

int main() {
    print("testdata", testdata);
    std::vector<XY> positions;
    std::partial_sum(testdata.cbegin(), testdata.cend(),
                     back_inserter(positions),
                     [](const XY &e1, const XY &e2) {
                         using std::get;
                         enum { x=0, y=1 };
                         return XY{get<x>(e1) + get<x>(e2),
                                   get<y>(e1) + get<y>(e2)};
                     });
    print("positions", positions);
    std::vector<XY> distances;
    std::partial_sum(positions.cbegin(), positions.cend(),
                     back_inserter(distances),
                     [](const XY &e1, const XY &e2) {
                         using std::get;
                         enum { x=0, y=1 };
                         return XY{get<x>(e2) - get<x>(e1),
                                   get<y>(e2) - get<y>(e1)};
                     });
    print("distances", distances);
}
