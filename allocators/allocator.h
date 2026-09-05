#pragma once

#include <cstddef>
#include <iostream>
#include <cassert>
#include <new>
#include <vector>
#include <fmt/format.h>
#include <fmt/std.h>
#include <fmt/ranges.h>

template<typename T>
struct Allocation {
    T *begin;
    std::size_t size;
};

template<typename T>
auto format_as(const Allocation<T> &o) {
    return fmt::format("Allocation(begin={}, size={})", static_cast<void*>(o.begin), o.size);
}

template<typename T>
struct ArrayAllocator {
    using value_type = T;
    std::size_t m_max_size;
    T* m_data;
    std::vector<Allocation<T>> m_allocations;

    ArrayAllocator(std::size_t max_size) {
        fmt::println("ArrayAllocator");
        m_max_size = max_size;
        m_data = (T*)malloc(max_size * sizeof(T));
    }

    ArrayAllocator(const ArrayAllocator& other) {
        *this = other;
    }

    ArrayAllocator& operator=(const ArrayAllocator& other) {
        m_data = other.m_data;
        m_allocations = other.m_allocations;
        m_max_size = other.m_max_size;

        T* new_data = (T*)malloc(m_max_size * sizeof(T));
        std::ptrdiff_t offset = (new_data - m_data);
        m_data = new_data;

        for (auto&& it: m_allocations) {
            it.begin += offset;
        }

        return *this;

    }

    ArrayAllocator(ArrayAllocator&& other) noexcept {
        *this = other;
    }

    ArrayAllocator& operator=(ArrayAllocator&& other) noexcept {
        m_data = other.m_data;
        m_allocations = other.m_allocations;
        m_max_size = other.m_max_size;

        other.m_data = nullptr;
        other.m_allocations.clear();
        other.m_max_size = 0;
        return *this;
    }

    ~ArrayAllocator() {
        fmt::println("~ArrayAllocator");
        free(m_data);
        m_data = nullptr;
    }

    void deallocate(T *p, std::size_t n) {
        fmt::println("deallocate(p={}, n={})", (void*)p, n);

        for (auto it = m_allocations.begin(); it != m_allocations.end();) {
            if (it->begin == p) {
                if (it->size == n) {
                    it = m_allocations.erase(it);
                    continue;
                } else {
                    it->begin += n;
                    it->size -= n;
                }
            }
            ++it;
        }
    }

    [[nodiscard]] T *allocate(std::size_t n) {
        fmt::println("allocate({})", n);
        auto* begin = m_data;

        for (auto&& alloc: m_allocations) {
            begin = alloc.begin + alloc.size;
        }

        if (begin + n > m_data + m_max_size) {
            throw std::bad_alloc();
        }

        m_allocations.emplace_back(Allocation{.begin = begin, .size = n});
        fmt::println("m_allocations={}", m_allocations);

        for (int nn = n; nn > 0; --nn) {
            *(begin + nn) = 69;
        }

        return begin;
    }
};