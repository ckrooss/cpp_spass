#pragma once
#include <vector>
#include <string>
#include <string_view>
#include <ostream>

class Item {
  public:
    Item() = delete;
    Item(int id, std::string_view name = "", int level = 0) : m_id(id), m_name(name), m_level(level) {
    }

    Item(const Item& other);
    Item(Item&& other);
    Item& operator=(const Item& other);
    Item& operator=(Item&& other);

    int m_id;
    std::string m_name;
    int m_level;
};

inline std::ostream& operator<<(std::ostream& os, const Item& item) {
    os << "Item<id=" << item.m_id << ", name=\"" << item.m_name << "\", level=" << item.m_level << ">";
    return os;
}