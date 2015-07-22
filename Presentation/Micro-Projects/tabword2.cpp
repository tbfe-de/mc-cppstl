// Micro-Project: Word Position Table to Text
// (saving some memory for string storage)
#define TDD

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

void tab_word_pos(std::istream &in, std::ostream &out) {
    using WordSet = std::set<std::string>;
    using WordRef = WordSet::const_iterator;
    using WordTab = std::map<int, std::map<int, WordRef>>;
    WordSet words;
    WordTab word_tab;
    std::string line;
    while (std::getline(in, line)) {
        std::istringstream iss(line);
        std::string w;
        std::getline(iss, w, ':');
        int line_nr;
        char sep;
        int pos_nr = 0;
        while (iss >> line_nr >> sep >> pos_nr) {
            // word_tab[line_nr][pos_nr] = words.insert(w).first;
            const auto wordref = words.insert(w).first;
            word_tab[line_nr].insert(std::make_pair(pos_nr, wordref));
        }
    }
    for (const auto &e_outer : word_tab) {
        for (const auto &e_inner : e_outer.second)
            out << *e_inner.second << ' ';
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
    tab_word_pos(send, expect);
//  ----------------------------
    assert(expect.str() ==
        "beware the Jabberwock my son "    "\n"
        "beware the Jubjub bird and shun " "\n" 
        "the frumious Bandersnatch "       "\n" 
    );

    std::cout << "*** TEST PASSED" << std::endl;
}
#endif
