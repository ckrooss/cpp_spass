#pragma once
#include "item.h"
#include "iterator.h"

#include <vector>
#include <string>
#include <string_view>

class Container {
  public:
    Container() = default;

    // Types
    using value_type = Item;
    using container_type = std::vector<Item>;

    // Mutation
    void insert(Item item);
    bool remove(int id);

    // Observers
    std::size_t size() const;
    bool empty() const;

    // Iterators
    container_type::iterator begin();
    container_type::iterator end();

    // Special Iterators
    FilterView<value_type> filter_view(FilterView<value_type>::filter_type only_if);
    FilterView<const value_type> filter_view(FilterView<const value_type>::filter_type only_if) const;

  private:
    container_type m_items;
};