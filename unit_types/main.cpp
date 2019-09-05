#include <iostream>

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

    bool operator>(const T& value) {
        return m_value > value;
    }

    bool operator<(const T& value) {
        return m_value < value;
    }

    bool operator==(const T& value) {
        return m_value == value;
    }

    Container operator+(const T& value) {
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

    bool operator>(const P& other) {
        return m_value > other.m_value;
    }

    bool operator<(const P& other) {
        return m_value < other.m_value;
    }

    bool operator==(const P& other) {
        return m_value == other.m_value;
    }

    Container operator+(const P& other) {
        return {m_value + other.m_value};
    }

    friend std::ostream& operator<<(std::ostream& os, const Container& obj) {
        os << std::to_string(obj.m_value) << " " << obj.getUnit();
        return os;
    }

    bool operator++() {
        return ++m_value;
    }

    T get() const {
        return m_value;
    }

    virtual std::string getUnit() const {
        return "";
    }

    protected:
        T m_value;
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

struct Meters : public Container<int, Meters> {
    Meters(value_type value) : Container(value) {};
    Seconds operator/(const Kph& other) {
        return {m_value / other.get()};
    }
    std::string getUnit() const {
        return "m";
    }
};


//Seconds time_for_distance_at_speed();

int main() {
    Meters x{800};
    Kph y{60};

    // error: invalid operands to binary expression ('Kph' and 'Meters')
    // std::cout << x << " + " << y << " = " << x + y << std::endl;

    std::cout << x << " / " << y << " = " << x / y << std::endl;

    return 0;
}
