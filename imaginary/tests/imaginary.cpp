#include <gtest/gtest.h>
#include "complex.h"

TEST(imaginary, init) {
    auto a = 2_r;
    auto b = 2_im;
}

TEST(imaginary, addition) {
    auto a = 2_r;
    auto b = 2_im;
    auto c = a + b;

    auto expected = Complex{2, 2};

    EXPECT_TRUE(c == expected);
}
