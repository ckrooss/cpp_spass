#pragma once
#include <thread>
#include <deque>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <cassert>
#include <fmt/printf.h>

using namespace std::chrono_literals;

class Manager {
  public:
    static Manager& instance() {
        static Manager manager;
        return manager;
    }

    ~Manager() {
        m_thread.request_stop();
    }

    void add_work(int n) {
        {
            std::lock_guard lk{m_mtx};
            m_q.push_front(n);
        }
        m_cv.notify_one(); // Testen ob besser ohne lock notify
    }

    void finish() {
        while (true) {
            {
                std::unique_lock lk(m_mtx);
                if (m_q.empty()) {
                    return;
                }
            }
            std::this_thread::yield();
        }
    }

  private:
    std::deque<int> m_q;
    std::mutex m_mtx;
    std::jthread m_thread;
    std::condition_variable_any m_cv;

    Manager() {
        m_thread = std::jthread([this](const std::stop_token&stoken) { loop(stoken); });
    };

    void loop(const std::stop_token&stoken) {
        std::unique_lock lk(m_mtx);

        while (!stoken.stop_requested()) {
            m_cv.wait(lk, stoken, [this]() { return !m_q.empty(); });

            if (!m_q.empty()) {
                auto val = m_q.back();
                m_q.pop_back();
                std::this_thread::sleep_for(200ms);
                fmt::printf("Processing %d\n", val);
            }
        }

        if (stoken.stop_requested()) {
            fmt::printf("Stop requested\n");
        }
    }
};