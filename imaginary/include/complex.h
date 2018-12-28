#include <iostream>
#include <string>

class Complex {
public:
    Complex(int r, int i) : m_real(r), m_imag(i) {}

    Complex& operator+ (const Complex& other) {
        m_real += other.m_real;
        m_imag += other.m_imag;
        return *this;
    }

    friend Complex operator+(int a, Complex b)
    {
        b.m_real += a;
        return b;
    }


    Complex& operator* (const Complex& other) {
        std::cout << this->to_str() << " * " << other.to_str();
        auto new_real = (m_real * other.m_real) - (m_imag * other.m_imag);
        auto new_imag = (m_imag * other.m_real) + (m_real * other.m_imag);

        m_imag = new_imag;
        m_real = new_real;

        std::cout << " = " << this->to_str() << std::endl;
        return *this;
    }

    bool operator== (const Complex& other) const {
        return (m_real == other.m_real) && (m_imag == other.m_imag);
    }

    std::string to_str() const {
        return std::to_string(m_real) + "+" + std::to_string(m_imag) + "i";
    }

private:
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
