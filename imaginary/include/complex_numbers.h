#pragma once
#include <string>

class Complex {
  public:
    [[nodiscard]] constexpr Complex(const int r, const int i) : m_real(r), m_imag(i) {
    }

    [[nodiscard]] constexpr Complex operator+(const Complex& other) const {
        return {m_real + other.m_real, m_imag + other.m_imag};
    }

    constexpr Complex& operator+=(const Complex& other) {
        *this = *this + other;
        return *this;
    }

    [[nodiscard]] constexpr Complex operator+(int val) const {
        return {m_real + val, m_imag};
    }

    [[nodiscard]] constexpr Complex operator-(int val) const {
        return {m_real - val, m_imag};
    }

    [[nodiscard]] constexpr Complex operator*(const Complex& other) const {
        return {(m_real * other.m_real) - (m_imag * other.m_imag), (m_imag * other.m_real) + (m_real * other.m_imag)};
    }

    [[nodiscard]] constexpr Complex operator*(int val) const {
        return {m_real * val, m_imag * val};
    }

    [[nodiscard]] constexpr bool operator==(const Complex& other) const {
        return (m_real == other.m_real) && (m_imag == other.m_imag);
    }
    [[nodiscard]] constexpr auto operator<=>(const Complex& other) const {
        return abs() <=> other.abs();
    }

    [[nodiscard]] constexpr int abs() const {
        return m_real * m_real + m_imag * m_imag;
    }

    [[nodiscard]] constexpr int imag() const {
        return m_imag;
    }

    [[nodiscard]] constexpr int real() const {
        return m_real;
    }

  private:
    int m_real = 0;
    int m_imag = 0;
};

[[nodiscard]] constexpr inline Complex operator""_im(const unsigned long long n) {
    return Complex{0, static_cast<int>(n)};
}

[[nodiscard]] constexpr inline Complex operator""_r(const unsigned long long n) {
    return Complex{static_cast<int>(n), 0};
}

inline auto format_as(const Complex& obj) {
    return std::to_string(obj.real()) + "+" + std::to_string(obj.imag()) + "i";
}