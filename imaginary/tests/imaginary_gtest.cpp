#include <gtest/gtest.h>
#include "complex_numbers.h"

TEST(complex, init) {
    auto a = 2_r;
    EXPECT_EQ(a, (Complex{2, 0}));

    auto b = 2_im;
    EXPECT_EQ(b, (Complex{0, 2}));
}

TEST(complex, addition) {
    auto a = 2_r;
    auto b = 2_im;
    auto c = a + b;
    EXPECT_EQ(c, (Complex{2, 2}));
}

TEST(complex, add_int) {
    auto a = 2_r + 4;
    EXPECT_EQ(a, (Complex{6, 0}));

    auto b = 2_im + 4;
    EXPECT_EQ(b, (Complex{4, 2}));
}

TEST(complex, multiplication) {
    auto a = 1_r + 2_im;
    auto b = 3_r + 4_im;
    EXPECT_EQ(a, (Complex{1, 2}));
    EXPECT_EQ(b, (Complex{3, 4}));

    auto c = a * b;
    EXPECT_EQ(c, (Complex{-5, 10}));
}
