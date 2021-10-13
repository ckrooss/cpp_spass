#include "item.h"

Item::Item(const Item& other) {
    m_id = other.m_id;
    m_name = other.m_name;
    m_level = other.m_level;
}

Item::Item(Item&& other) {
    m_id = other.m_id;
    m_name.swap(other.m_name);
    m_level = other.m_level;
}

Item& Item::operator=(const Item& other) {
    m_id = other.m_id;
    m_name = other.m_name;
    m_level = other.m_level;
    return *this;
}

Item& Item::operator=(Item&& other) {
    m_id = other.m_id;
    m_name.swap(other.m_name);
    m_level = other.m_level;
    return *this;
}