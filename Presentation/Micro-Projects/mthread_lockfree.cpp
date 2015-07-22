#include <algorithm>
#include <atomic>
#include <cmath>
#include <mutex>
#include <thread>
#include <iostream>

template<typename T1, typename T2, typename Transformation>
void worker(T1 data[], std::size_t data_size, T2 result,
            std::atomic_size_t &total_progress,
            Transformation func) {
    while (total_progress < data_size) {
	constexpr auto chunks = std::size_t{100};
        std::size_t beg = total_progress.load();
	std::size_t end;
        do {
            end = ((data_size - beg) > chunks)
                ? beg + chunks
                : data_size;
        } while (!total_progress.compare_exchange_weak(beg, end));
        std::transform(&data[beg], &data[end], &result[beg], func);
    }
}

constexpr std::size_t N = 100000;
int data[N];
double sqrts[N];

int main() {
    std::iota(std::begin(data), std::end(data), 1);

    std::atomic_size_t processed_count{0};

    auto worker_task =
        [&]() { worker(data, N, sqrts, processed_count,
                       [](double e) { return std::sqrt(e); });
    };

    auto t1 = std::thread(worker_task);
    auto t2 = std::thread(worker_task);
    t1.join();
    t2.join();
}
