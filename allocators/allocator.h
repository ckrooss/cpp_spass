#pragma once

#include <cstddef>
#include <iostream>
#include <cassert>
#include <bitset>
#include <array>
#include <new>
#include <stdexcept>
#include <vector>

#define ArraySize 10
inline std::array<std::vector<int>::value_type, ArraySize> data;
inline std::bitset<ArraySize> occupied;

template <typename T>
struct ArrayAllocator {
    using value_type = T;

    void validate(const T* ptr) const {
        assert(ptr >= data.begin() && ptr < data.end());
    }

    void clear() {
        data = {};
        occupied = {};
    }

    std::size_t usage() const {
        return occupied.count();
    }

    void deallocate(T* p, std::size_t n) const {
        validate(p);
        
        auto p_off = ptr_to_off(p);
        std::cout << this << " " << __func__ << "(n=" << n << ") at " << p_off << " (=" << p << ")" << std::endl;

        for (std::size_t off = p_off; off < p_off + n; ++off) {
            if(!occupied[off]) {
                throw std::runtime_error("double-free");
            }
            occupied.reset(off);
        }
        
        print_allocation();
    }

    std::size_t ptr_to_off(const T* ptr) const {
        return static_cast<std::size_t>(ptr - data.begin());
    }

    T* off_to_ptr(std::size_t off) const {
        return static_cast<T*>(data.begin() + off);
    }

    [[nodiscard]] T* allocate(std::size_t n) const {
        const auto new_pos = find_space(n);
        std::cout << this << " " << __func__ << "(n=" << n << ") at " << new_pos << std::endl;

        for (std::size_t off = new_pos; off < new_pos + n; ++off) {
            occupied.set(off);
        }

        print_allocation();

        return off_to_ptr(new_pos);
    }

    std::size_t find_space(const std::size_t n) const {
        std::size_t zeroes = 0;

        for(std::size_t off = 0; off < occupied.size(); ++off) {
            if(!occupied[off]) {
                if(++zeroes == n) {
                    return off - (zeroes - 1);
                }
            }
            else {
                zeroes = 0;
            }
        }
        throw std::bad_alloc();
        
    }

    void print_allocation() const {
        std::cout << "Allocation: [";
        for (std::size_t off = 0; off < occupied.size(); ++off) {
            std::cout << occupied[off];
        }
        std::cout << "]" << std::endl;
    }
};
