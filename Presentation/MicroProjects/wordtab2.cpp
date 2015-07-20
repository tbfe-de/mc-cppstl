// Micro-Project: Text to Word Position Table
// (alternative solution applying std::copy)
#define TDD

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

struct line_pos {
    int line, pos;
    line_pos(int line_, int pos_) : line(line_), pos(pos_) {}
};

std::ostream &operator<<(std::ostream &lhs, const line_pos &rhs) {
    return lhs << rhs.line << '.' << rhs.pos;
}

void word_pos_tab(std::istream &in, std::ostream &out) {
    std::map<std::string, std::vector<line_pos>> word_tab;
    auto line_nr = 1;
    std::string line;
    while (std::getline(in, line)) {
        auto pos_nr = 0;
        std::string w;
        std::istringstream iss(line);
        while (iss >> w)
           word_tab[w].emplace_back(line_nr, pos_nr++);
        ++line_nr;
    }
    for (const auto &e : word_tab) {
        out << e.first << ": ";
        std::copy(e.second.cbegin(), e.second.cend(),
                  std::ostream_iterator<line_pos>(out, " "));
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
        "beware the Jabberwock my son"    "\n"
        "beware the Jubjub bird and shun" "\n" 
        "the frumious Bandersnatch"       "\n" 
    );
    std::ostringstream expect;
//  ----------------------------
    word_pos_tab(send, expect);
//  ----------------------------
    assert(expect.str() ==
        "Bandersnatch: 3.2 "  "\n"
        "Jabberwock: 1.2 "    "\n"
        "Jubjub: 2.2 "        "\n"
        "and: 2.4 "           "\n"
        "beware: 1.0 2.0 "    "\n"
        "bird: 2.3 "          "\n"
        "frumious: 3.1 "      "\n"
        "my: 1.3 "            "\n"
        "shun: 2.5 "          "\n"
        "son: 1.4 "           "\n"
        "the: 1.1 2.1 3.0 "   "\n"
    );

    std::cout << "*** TEST PASSED" << std::endl;
}
#endif
