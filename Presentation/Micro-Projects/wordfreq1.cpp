// Micro-Project: Word Frequency Analysis with `std::map`
#define TDD

#include <iostream>
#include <map>
#include <string>

void word_freq_map(std::istream &in, std::ostream &out) {
    std::map<std::string, int> word_freq;
    std::string w;
    while (in >> w)
        ++word_freq[w];
    for (const auto &e : word_freq)
        out << e.first << ": " << e.second << '\n';
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
    std::ostringstream received;
//  ----------------------------
    word_freq_map(send, received);
//  ----------------------------
//  std::cout << received.str();
    assert(received.str() ==
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
