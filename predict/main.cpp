#include <algorithm>
#include <atomic>
#include <cassert>
#include <chrono>
#include <future>
#include <iostream>
#include <numeric>
#include <random>
#include <thread>
#include <utility>
#include <vector>
#include <array>

#define NVEC 100000000

using namespace std;

class Timer {
    chrono::high_resolution_clock::time_point m_start;

  public:
    Timer() {
        m_start = chrono::high_resolution_clock::now();
    }

    ~Timer() {
        auto end = chrono::high_resolution_clock::now();
        auto diff_ms = chrono::duration_cast<chrono::milliseconds>(end - m_start);

        cout << to_string(diff_ms.count()) << " ms" << endl;
    }
};

template <typename T>
void run_test(const char* name, int count, size_t (*fn)(const T& data), const T& data, size_t result) {
    cout << name;
    fn(data); // warmup

    Timer t;
    for (int i = 0; i < count; ++i) {
        assert(result == fn(data));
    }
}

size_t std_accumulate(const vector<uint8_t>& data) {
    auto add_if_large = [](size_t a, uint8_t b) { return b >= 128 ? a + 1 : a; };
    return accumulate(data.begin(), data.end(), static_cast<size_t>(0), add_if_large);
}

size_t regular_for(const vector<uint8_t>& _data) {
    const auto* data = _data.data();
    size_t cnt{0};

    for (size_t idx = 0; idx < NVEC; idx++) {
        if (data[idx] >= 128) {
            cnt++;
        }
    }

    return cnt;
}

size_t regular_for_omp(const vector<uint8_t>& _data) {
    const auto* data = _data.data();

    constexpr int nthreads = 8;
    array<size_t, nthreads> cnt = {0};

#pragma omp parallel for
    for (int i = 0; i < nthreads; ++i) {
        for (size_t idx = i; idx < NVEC; idx += nthreads) {
            if (data[idx] >= 128) {
                cnt[i]++;
            }
        }
    }
    return accumulate(cnt.begin(), cnt.end(), 0);
}

size_t regular_for_threads_futures(const vector<uint8_t>& _data) {
    const auto* data = _data.data();

    constexpr int nthreads = 8;
    size_t cnt{0};

    auto work = [data](size_t start_idx, promise<size_t> result) {
        size_t l_cnt{0};

        for (size_t idx = start_idx; idx < NVEC; idx += nthreads) {
            if (data[idx] >= 128) {
                ++l_cnt;
            }
        }

        result.set_value(l_cnt);
    };

    vector<pair<thread, future<size_t>>> threads;

    for (int i = 0; i < nthreads; ++i) {
        promise<size_t> p;
        auto fut = p.get_future();
        threads.push_back({thread(work, i, std::move(p)), std::move(fut)});
    }

    for (auto& [thread, fut] : threads) {
        if (thread.joinable())
            thread.join();

        cnt += fut.get();
    }
    return cnt;
}

size_t threads_shared_memory(const vector<uint8_t>& _data) {
    const auto* data = _data.data();

    constexpr int nthreads = 8;
    std::array<size_t, nthreads> cnt = {0};

    auto work = [data, &cnt](size_t start_idx) {
        size_t l_cnt{0};
        for (size_t idx = start_idx; idx < NVEC; idx += nthreads) {
            if (data[idx] >= 128) {
                ++l_cnt;
            }
        }
        cnt[start_idx] = l_cnt;
    };

    vector<thread> threads;

    for (int i = 0; i < nthreads; ++i) {
        threads.push_back(thread(work, i));
    }

    for (auto& thread : threads) {
        if (thread.joinable())
            thread.join();
    }
    return std::accumulate(cnt.begin(), cnt.end(), 0);
}

size_t iterator_for(const vector<uint8_t>& data) {
    size_t cnt{0};

    for (auto it = data.begin(); it < data.end(); ++it) {
        if (*it >= 128)
            cnt++;
    }
    return cnt;
}

size_t range_based_for(const vector<uint8_t>& data) {
    size_t cnt{0};

    for (const auto& d : data) {
        if (d >= 128)
            cnt++;
    }
    return cnt;
}

int main() {
    random_device rd;  //Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<> dis(0, 255);

    vector<uint8_t> data;
    data.resize(NVEC);

    for (auto& d : data) {
        d = static_cast<uint8_t>(dis(gen));
    }

    auto result = regular_for(data);

    run_test("regular             ", 50, regular_for, data, result);
    run_test("regular_omp         ", 50, regular_for_omp, data, result);
    run_test("threads w/ futures  ", 50, regular_for_threads_futures, data, result);
    run_test("threads w/ shm      ", 50, threads_shared_memory, data, result);
    run_test("iterator            ", 50, iterator_for, data, result);
    run_test("range               ", 50, range_based_for, data, result);
    run_test("accumulate          ", 50, std_accumulate, data, result);
}
