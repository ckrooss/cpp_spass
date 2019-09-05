#include <iostream>
#include <map>
#include <unordered_map>

template<typename T, typename P>
class Container {
public:
    using value_type = T;

    Container(const T& value) {
        m_value = value;
    }

    Container(T&& value) {
        m_value = value;
    }

// operations with T
    Container operator=(const T& value) {
        m_value = value;
        return *this;
    }

    bool operator!=(const T& value) const {
        return m_value != value;
    }

    bool operator>(const T& value) const {
        return m_value > value;
    }

    bool operator<(const T& value) const {
        return m_value < value;
    }

    bool operator==(const T& value) const {
        return m_value == value;
    }

    Container operator+(const T& value) const {
        return {m_value + value};
    }

    void operator+=(const T& value) {
        m_value += value;
    }

// operations with P (P inherits from Container<T, P>)
    Container operator=(const P& other) {
        m_value = other.m_value;
        return *this;
    }

    bool operator!=(const P& other) const {
        return m_value != other.m_value;
    }

    bool operator>(const P& other) const {
        return m_value > other.m_value;
    }

    bool operator<(const P& other) const {
        return m_value < other.m_value;
    }

    bool operator==(const P& other) const {
        return m_value == other.m_value;
    }

    Container operator+(const P& other) const {
        return {m_value + other.m_value};
    }

    friend std::ostream& operator<<(std::ostream& os, const Container& obj) {
        os << std::to_string(obj.m_value) << " " << obj.getUnit();
        return os;
    }

    bool operator++() {
        return ++m_value;
    }

//Other stuff
    T get() const {
        return m_value;
    }

    virtual std::string getUnit() const {
        return "";
    }

    protected:
        T m_value;
};

// Hash function is needed to use Container as a key for std::unordered_map
struct ContainerHash {
template<typename T, typename P>
  std::size_t operator()(const Container<T, P>& container) const {
    return std::hash<T>()(container.get());
  }
};

struct Seconds : public Container<time_t, Seconds> {
    Seconds(value_type value) : Container(value) {};
    std::string getUnit() const {
        return "s";
    }
};

struct Kph : public Container<int, Kph> {
    Kph(value_type value) : Container(value) {};
    std::string getUnit() const {
        return "km/h";
    }
};

struct Risk : public Container<int, Risk> {
    Risk(value_type value) : Container(value) {};
    std::string getUnit() const {
        return "risk";
    }
};

struct Meters : public Container<int, Meters> {
    Meters(value_type value) : Container(value) {};
    Seconds operator/(const Kph& other) {
        return {m_value / other.get()};
    }
    std::string getUnit() const {
        return "m";
    }
};

using speed_to_risk_t = std::unordered_map<Kph, Risk, ContainerHash>;
static speed_to_risk_t speed_to_risk = {
    {1, 0},
    {2, 0},
    {3, 0},
    {4, 0},
    {5, 1},
    {6, 2},
    {7, 3},
    {8, 4},
    {9, 5},
    {10, 7}
};

int main() {
    Meters x{800};
    Kph y{9};

    std::cout << x << " / " << y << " = " << x / y << std::endl;

    std::cout << "at v=" << y << " the relative risk is " << speed_to_risk.at(y) << std::endl;


    // error: invalid operands to binary expression ('Kph' and 'Meters')
    // std::cout << x << " + " << y << " = " << x + y << std::endl;

    // error: no matching member function for call to 'at'
    // no known conversion from 'Meters' to 'Kph' for 1st argument
    // std::cout << "at x=" << x<< " the relative risk is " << speed_to_risk.at(x) << std::endl;

    return 0;
}
