#include "Expensive.h"
#include <atomic>
#include <cassert>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <pthread.h>
#include <string>
#include <thread>
#include <vector>

using namespace std;
using namespace std::literals::chrono_literals;

constexpr int NTHREADS = 5;
constexpr int NWORK = 100;
constexpr int BATCH = 5;

static mutex g_mutex;
static condition_variable g_cond;
static atomic_bool g_shutdown;
static vector<Expensive> g_work;

void log(const string& msg) {
    // Lock mutex to prevent data races on cout
    static mutex g_cout_mutex;
    lock_guard cm{g_cout_mutex};
    cout << "[" << this_thread::get_id() << "]"
         << " " << msg << endl;
}

string vec2str(const vector<Expensive>& data) {
    // [1,2,3] -> "[1,2,3]"
    string out = "[";
    for (const auto& d : data) {
        out += to_string(d.m_idx) + ",";
    }
    out.erase(out.end() - 1);
    out += "]";
    return out;
}

void shutdown() {
    lock_guard lock{g_mutex};
    g_shutdown = true;
    g_cond.notify_all();
}

void block() {
    vector<Expensive> my_work{};

    while (true) {
        // Critical region -> wait for notification and pop data from vector
        {
            unique_lock<mutex> lock{g_mutex};
            if (g_shutdown) {
                break;
            }
            g_cond.wait(lock, []() { return g_shutdown || !g_work.empty(); });

            if (g_work.size() < BATCH) {
                log("some work available - taking all " + to_string(g_work.size()));
                my_work = std::move(g_work);
                g_work.clear();
            } else {
                log("lot of work available, taking a chunk of " + to_string(BATCH));
                auto it = next(g_work.begin(), BATCH);
                std::move(g_work.begin(), it, back_inserter(my_work));
                g_work.erase(g_work.begin(), it);
            }
        }

        log("Batch: " + vec2str(my_work));
        this_thread::sleep_for(10ms);
        my_work.clear();
    }
}

int main() {
    log("Starting...");
    g_shutdown = false;
    thread threads[NTHREADS];

    // spin up threads
    for (auto& t : threads) {
        t = thread{block};
    }

    // supply some work
    for (int i = 0; i < NWORK; i++) {
        lock_guard lock{g_mutex};
        g_work.emplace_back(i);
        g_cond.notify_one();
    }

    // wait for work to finish
    while (true) {
        {
            unique_lock lock{g_mutex};
            if (g_work.empty()) {
                break;
            }
        }
        this_thread::sleep_for(10ms);
        g_cond.notify_one();
    }

    shutdown();
    log("waiting for threads to finish");
    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }
}
