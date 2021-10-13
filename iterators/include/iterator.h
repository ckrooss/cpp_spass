#pragma once
#include <iterator>
#include <functional>

template <typename T>
class FilterIterator {
  public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    using filter_type = std::function<bool(reference)>;

    FilterIterator(pointer ptr, pointer end, filter_type only_if) {
        m_ptr = ptr;
        m_end = end;
        m_filter = only_if;

        // Fast-forward filtering iterator to the first item that is not filtered out
        while (m_ptr != m_end && !m_filter(*m_ptr)) {
            m_ptr++;
        };
    }

    FilterIterator(pointer ptr) {
        m_ptr = ptr;
    }

    reference operator*() {
        return *m_ptr;
    }

    FilterIterator& operator++() {
        do {
            m_ptr++;
        } while (m_ptr != m_end && !m_filter(*m_ptr));
        return *this;
    }
    FilterIterator& operator++(int) {
        auto tmp = *this;
        do {
            m_ptr++;
        } while (m_ptr != m_end && !m_filter(*m_ptr));
        return tmp;
    }

    friend bool operator==(const FilterIterator& a, const FilterIterator& b) {
        return a.m_ptr == b.m_ptr;
    }

    friend bool operator!=(const FilterIterator& a, const FilterIterator& b) {
        return a.m_ptr != b.m_ptr;
    }

  private:
    pointer m_ptr;
    pointer m_end;
    filter_type m_filter;
};

template <typename T>
class FilterView {
  public:
    using pointer = typename FilterIterator<T>::pointer;
    using filter_type = typename FilterIterator<T>::filter_type;

    FilterView(pointer ptr, pointer end, filter_type filter) {
        m_ptr = ptr;
        m_end = end;
        m_filter = filter;
    }

    FilterIterator<T> begin() {
        return FilterIterator<T>(m_ptr, m_end, m_filter);
    }

    FilterIterator<T> end() {
        return FilterIterator<T>(m_end);
    }

  private:
    pointer m_ptr;
    pointer m_end;
    filter_type m_filter;
};