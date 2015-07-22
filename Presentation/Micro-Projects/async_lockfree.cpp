#include <algorithm>
#include <cmath>
#include <mutex>
#include <future>
#include <iostream>

constexpr std::size_t N = 100000;
int data[N];
double sqrts[N];
std::mutex mtx;

template<typename T1, typename T2, typename Transformation>
void worker(T1 args[], std::size_t data_size, T2 result,
            std::atomic_size_t &total_progress,
            Transformation func) {
    while (total_progress < N) {
        std::size_t beg = total_progress.load();
	std::size_t end;
	constexpr auto chunks = std::size_t{100};
        do {
            end = ((data_size - beg) > chunks)
                ? beg + chunks
                : data_size;
        } while ((beg = total_progress.exchange(end)) != beg);
        std::transform(&data[beg], &data[end], &sqrts[beg], func);
    }
}

int main() {
    std::iota(std::begin(data), std::end(data), 1);

    std::atomic_size_t done;

    auto w1 = std::async([&done]{ worker(data, N, sqrts, done,
                                  [](int e){ return std::sqrt(e); }); });
    auto w2 = std::async([&done]{ worker(data, N, sqrts, done,
                                  [](int e){ return std::sqrt(e); }); });
    w1.get();
    w2.get();
}
