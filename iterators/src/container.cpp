#include "container.h"

void Container::insert(Item item) {
    m_items.push_back(item);
}

bool Container::remove(int id) {
    return std::erase_if(m_items, [id](const value_type& item) { return item.m_id == id; });
}

std::size_t Container::size() const {
    return m_items.size();
}

bool Container::empty() const {
    return m_items.empty();
}

Container::container_type::iterator Container::begin() {
    return m_items.begin();
}

Container::container_type::iterator Container::end() {
    return m_items.end();
}

FilterView<Container::value_type> Container::filter_view(FilterView<value_type>::filter_type only_if) {
    return {&*m_items.begin(), &*m_items.end(), only_if};
}

FilterView<const Container::value_type> Container::filter_view(FilterView<const value_type>::filter_type only_if) const {
    return {&*m_items.cbegin(), &*m_items.cend(), only_if};
}