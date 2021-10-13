#include <vector>
#include <string>
#include <string_view>
#include <ostream>

class Item {
  public:
    Item(int id, std::string_view name = "", int level = 0) : m_id(id), m_name(name), m_level(level) {
    }

    Item(const Item& other) {
        m_id = other.m_id;
        m_name = other.m_name;
        m_level = other.m_level;
    }

    Item(Item&& other) {
        m_id = other.m_id;
        m_name.swap(other.m_name);
        m_level = other.m_level;
    }

    Item& operator=(const Item& other) {
        m_id = other.m_id;
        m_name = other.m_name;
        m_level = other.m_level;
        return *this;
    }

    Item& operator=(Item&& other) {
        m_id = other.m_id;
        m_name.swap(other.m_name);
        m_level = other.m_level;
        return *this;
    }

    int m_id;
    std::string m_name;
    int m_level;
};

inline std::ostream& operator<<(std::ostream& os, const Item& item) {
    os << "Item<id=" << item.m_id << ", name=\"" << item.m_name << "\", level=" << item.m_level << ">";
    return os;
}