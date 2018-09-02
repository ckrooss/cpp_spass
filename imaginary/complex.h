#include <iostream>
#include <string>

class Complex {
public:
    Complex(int r, int i) : m_real(r), m_imag(i) {}
    Complex(const Complex& c) = delete;
    Complex(Complex&& c) {
        m_imag = std::move(c.m_imag);
        m_real = std::move(c.m_real);
    }

    Complex& operator= (const Complex& other) = delete;
    Complex& operator= (Complex&& other) {
        m_imag = std::move(other.m_imag);
        m_real = std::move(other.m_real);
        return *this;
    }

    Complex& operator+ (const Complex& other) = delete;
    Complex& operator+ (Complex&& other) {
        m_real += std::move(other.m_real);
        m_imag += std::move(other.m_imag);
        return *this;
    }

    std::string to_str() const {
        return "[" + std::to_string(m_real) + ", " + std::to_string(m_imag) + "]";
    }

    int m_real = 0;
    int m_imag = 0;
};

Complex operator"" _im (unsigned long long n )
{
    return Complex{0, static_cast<int>(n)};
}

Complex operator"" _r ( unsigned long long n )
{
    return Complex{static_cast<int>(n), 0};
}

std::ostream& operator<<(std::ostream& os, const Complex& obj) {
    os << obj.to_str();
    return os;
}
