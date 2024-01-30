#include <iostream>

#pragma once
class Expensive {
  public:
    Expensive(const int idx) {
        m_idx = idx;
    }

    Expensive(const Expensive& other) = delete;
    Expensive(Expensive&& other) {
        m_idx = other.m_idx;
    }

    Expensive& operator=(const Expensive& other) = delete;
    Expensive& operator=(Expensive&& other) {
        m_idx = std::move(other.m_idx);
        return *this;
    }

    ~Expensive() = default;

    /**
     * @brief The actual index
     * @details
     * Do not use for anything!
     */
    int m_idx = 0;
};
