#include "complex_numbers.h"
#include <fmt/format.h>

using namespace std;

int main() {
    constexpr auto a = 4_r + 3_im;
    constexpr auto b = 3_r + 4_im;
    static_assert(b + a == a + b);
    static_assert(b * a == a * b);

    fmt::println("abs(a) = {}", a.abs());
    fmt::println("abs(b) = {}", b.abs());
    fmt::println("{} +  {} = {}", a, b, a + b);
    fmt::println("{} *  {} = {}", a, b, a * b);
    fmt::println("{} >  {} = {}", a, b, a > b);
    fmt::println("{} == {} = {}", a, b, a == b);
    fmt::println("{} <  {} = {}", a, b, a < b);
    fmt::println("{} != {} = {}", a, b, a != b);

    fmt::println("{} + {} = {}", a, 1, a + 1);
    fmt::println("{} - {} = {}", a, 1, a - 1);
    fmt::println("{} * {} = {}", a, 2, a * 2);
}
