#include <gtest/gtest.h>
#include "complex_numbers.h"

TEST(imaginary, init) {
    auto a = 2_r;
    auto b = 2_im;
    Complex c{2, 0};
    Complex d{0, 2};
    EXPECT_EQ(a, c);
    EXPECT_EQ(b, d);
}

TEST(imaginary, addition) {
    auto a = 2_r;
    auto b = 2_im;
    auto c = a + b;

    auto expected = Complex{2, 2};

    EXPECT_TRUE(c == expected);
}
