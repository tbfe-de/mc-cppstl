// Micro-Project: Word Position Table to Text
#define TDD

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

void tab_word_pos(std::istream &in, std::ostream &out) {
    std::map<int, std::map<int, std::string>> word_tab;
    std::string line;
    while (std::getline(in, line)) {
        std::istringstream iss(line);
        std::string w;
        std::getline(iss, w, ':');
        // assert(iss.good());
        int line_nr;
        char sep;
        int pos_nr = 0;
        while (iss >> line_nr >> sep >> pos_nr) {
            // assert(sep == '.');
            word_tab[line_nr][pos_nr] = w;
            // or: word_tab[line_nr].insert(std::make_pair(pos_nr, w));
        }
    }
    for (const auto &e_outer : word_tab) {
        for (const auto &e_inner : e_outer.second)
            out << e_inner.second << ' ';
        out << '\n';
    }
}

#ifndef TDD
int main() {
    word_pos_tab(std::cin, std::cout);
}
#else

#include <cassert>
#include <sstream>

int main() {
    std::istringstream send(
        "Bandersnatch: 3.2"  "\n"
        "Jabberwock: 1.2"    "\n"
        "Jubjub: 2.2"        "\n"
        "and: 2.4"           "\n"
        "beware: 1.0 2.0"    "\n"
        "bird: 2.3"          "\n"
        "frumious: 3.1"      "\n"
        "my: 1.3"            "\n"
        "shun: 2.5"          "\n"
        "son: 1.4"           "\n"
        "the: 1.1 2.1 3.0"   "\n"
    );
    std::ostringstream expect;
//  ----------------------------
    tab_word_pos(send, std::cout); return 0; //expect);
//  ----------------------------
    assert(expect.str() ==
        "beware the Jabberwock my son"    "\n"
        "beware the Jubjub bird and shun" "\n" 
        "the frumious Bandersnatch"       "\n" 
    );

    std::cout << "*** TEST PASSED" << std::endl;
}
#endif
