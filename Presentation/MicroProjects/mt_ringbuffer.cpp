#include <array>
#include <mutex>
#include <iostream>
#include <condition_variable>

template<typename T, std::size_t N>
class RingBuffer {
    std::array<T, N+1> buf;
    std::size_t p = 0, g = 0;
    bool empty() const { return p == g; }
    bool full() const { return (p+1) % buf.size() == g; }
    std::condition_variable data_available;
    std::condition_variable space_available;
    std::mutex buffer_access;
public:
    void put(const T &val) {
        std::unique_lock<std::mutex> lock(buffer_access);
        space_available.wait(lock, [this]{ return !full(); });
        buf[p++] = val; p %= buf.size();
        data_available.notify_one();
    }
    void get(T &val) {
        std::unique_lock<std::mutex> lock(buffer_access);
        data_available.wait(lock, [this]{ return !empty(); });
        val = buf[g++]; g %= buf.size();
        space_available.notify_one();
    }
};

#include <cassert>
#include <future>

int main() {
    RingBuffer<int, 300> rb;
    constexpr auto N = 100000;
    auto producer = std::async(std::launch::async, [&rb]{
         for (auto i = 0; i < N; ++i) rb.put(i);
    });
    auto consumer = std::async(std::launch::async, [&rb]{
         for (auto i = 0; i < N; ++i) {
		int x;
                rb.get(x);
                assert(x == i);
         }
    });
    producer.get();
    consumer.get();
}
        
