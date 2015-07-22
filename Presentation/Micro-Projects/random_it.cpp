#include <cstdlib>
#include <iterator>

struct RandomIterator
        : std::iterator<std::input_iterator_tag, int> {
    RandomIterator operator++() {
        return *this;
    }
    int operator*() const {
        return std::rand();
    }
};

#define TESTMAIN
#ifdef TESTMAIN

#include <algorithm>
#include <iostream>

int main() {
    using namespace std;
    copy_n(RandomIterator(), 10, ostream_iterator<int>(cout, " "));
    cout << endl;
}

#endif
