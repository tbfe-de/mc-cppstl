#include <iostream>
#include <string>

std::size_t str_hash(const char *s) {
    constexpr int p[] = { 3, 5, 7, 11, 13 };
    constexpr int N = sizeof p / sizeof p[0];
    std::size_t r = 0, i = 0;
    while (*s) r += (0xFF & *s++) * p[i++ % N];
    return r;
}

int main() {
    std::string s;
    while (std::getline(std::cin, s))
        std::cout << (str_hash(s.c_str()) % 20) << std::endl;
}
