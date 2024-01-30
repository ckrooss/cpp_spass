#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>
#include <atomic>
#include <cassert>

using namespace std::chrono_literals;

const int N_THREADS = 100;
const int N_COUNTS = 100;

//static int cnt = 0;
static std::atomic_int cnt{0};

//static std::mutex cnt_lock;

void counter() {
    int local_cnt = 0;

    while (local_cnt < N_COUNTS) {
        local_cnt++;
        // cnt_lock.lock();
        cnt++;
        // cnt_lock.unlock();
        std::this_thread::sleep_for(10ms);
    }
}

std::vector<std::thread> start_threads(int number) {
    std::vector<std::thread> threads;
    for (int idx = number; idx > 0; idx--) {
        std::thread t(counter);
        threads.push_back(move(t));
    }

    return threads;
}

// Auf alle Threads warten
void join_all(std::vector<std::thread>& threads) {
    for (auto& t : threads) {
        t.join();
    }
}

int main() {
    assert(cnt.is_lock_free());
    auto threads = start_threads(N_THREADS);
    assert(threads.size() == N_THREADS);
    join_all(threads);
    std::cout << cnt << std::endl;
    assert(cnt == N_THREADS * N_COUNTS);
}
