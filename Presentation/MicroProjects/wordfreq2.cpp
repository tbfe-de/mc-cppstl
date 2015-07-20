// Micro-Project: Word Frequency Analysis with `std::multiset`
#define TDD

#include <iostream>
#include <iterator>  // for std::advance
#include <set>
#include <string>

void word_freq_map(std::istream &in, std::ostream &out) {
    std::multiset<std::string> word_freq;
    std::string w;
    while (in >> w)
        word_freq.insert(w);
    for (auto it = word_freq.cbegin(); it != word_freq.cend();) {
        const auto count = word_freq.count(*it);
        out << *it << ": " << count << '\n';
        std::advance(it, count);
    }
}

#ifndef TDD
int main() {
    word_freq_map(std::cin, std::cout);
}
#else

#include <cassert>
#include <sstream>

int main() {
    std::istringstream send(
        "beware the Jabberwock my son"    "\n"
        "beware the Jubjub bird and shun" "\n" 
        "the frumious Bandersnatch"       "\n" 
    );
    std::ostringstream expect;
//  ----------------------------
    word_freq_map(send, expect);
//  ----------------------------
    assert(expect.str() ==
        "Bandersnatch: 1"   "\n"
        "Jabberwock: 1"     "\n"
        "Jubjub: 1"         "\n"
        "and: 1"            "\n"
        "beware: 2"         "\n"
        "bird: 1"           "\n"
        "frumious: 1"       "\n"
        "my: 1"             "\n"
        "shun: 1"           "\n"
        "son: 1"            "\n"
        "the: 3"            "\n"
    );

    std::cout << "*** TEST PASSED" << std::endl;
}
#endif
