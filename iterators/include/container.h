#include "item.h"
#include "iterator.h"

#include <vector>
#include <string>
#include <string_view>

class Container {
  public:
    using value_type = Item;
    using container_type = std::vector<Item>;
    Container() = default;

    void insert(Item item) {
        m_items.push_back(item);
    }

    bool remove(int id) {
        return std::erase_if(m_items, [id](const value_type& item) { return item.m_id == id; });
    }

    std::size_t size() const {
        return m_items.size();
    }

    bool empty() const {
        return m_items.empty();
    }

    container_type::iterator begin() {
        return m_items.begin();
    }

    container_type::iterator end() {
        return m_items.end();
    }

    FilterView<value_type> filter_view(std::function<bool(const value_type&)> only_if) {
        return {&*m_items.begin(), &*m_items.end(), only_if};
    }

  private:
    container_type m_items;
};