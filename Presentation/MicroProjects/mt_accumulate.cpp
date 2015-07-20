#include <algorithm>
#include <future>
#include <iostream>

constexpr std::size_t N = 100000;
int data[N];

int main() {
    std::iota(std::begin(data), std::end(data), 1);

    auto lower_part_sum = std::async(
        []{ return std::accumulate(&data[0], &data[N/2], 0LL); }
    );
    auto upper_part_sum = std::async(
        []{ return std::accumulate(&data[N/2], &data[N], 0LL); }
    );
    auto sum = lower_part_sum.get()
             + upper_part_sum.get();
    std::cout << sum << std::endl;
}
