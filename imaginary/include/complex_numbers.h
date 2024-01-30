#pragma once
#include <iostream>
#include <string>

class Complex {
  public:
    Complex(const int r, const int i) : m_real(r), m_imag(i) {
    }

    Complex& operator+(const Complex& other) {
        m_real += other.m_real;
        m_imag += other.m_imag;
        return *this;
    }

    Complex operator+(const Complex& other) const {
        return {m_real + other.m_real, m_imag + other.m_imag};
    }

    friend Complex operator+(const int a, Complex b) {
        b.m_real += a;
        return b;
    }

    Complex& operator*(const Complex& other) {
        const auto new_real = (m_real * other.m_real) - (m_imag * other.m_imag);
        const auto new_imag = (m_imag * other.m_real) + (m_real * other.m_imag);

        m_imag = new_imag;
        m_real = new_real;

        return *this;
    }

    bool operator==(const Complex& other) const {
        return (m_real == other.m_real) && (m_imag == other.m_imag);
    }

    [[nodiscard]] std::string to_str() const {
        return std::to_string(m_real) + "+" + std::to_string(m_imag) + "i";
    }

  private:
    int m_real = 0;
    int m_imag = 0;
};

inline Complex operator"" _im(const unsigned long long n) {
    return Complex{0, static_cast<int>(n)};
}

inline Complex operator"" _r(const unsigned long long n) {
    return Complex{static_cast<int>(n), 0};
}

inline std::ostream& operator<<(std::ostream& os, const Complex& obj) {
    os << obj.to_str();
    return os;
}
