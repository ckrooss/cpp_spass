#include <catch2/catch_test_macros.hpp>

#include "complex_numbers.h"

TEST_CASE("complex-init", "init") {
    auto a = 2_r;
    REQUIRE(a == Complex{2, 0});

    auto b = 2_im;
    REQUIRE(b == Complex{0, 2});
}

TEST_CASE("complex-addition", "addition") {
    auto a = 2_r;
    auto b = 2_im;
    auto c = a + b;
    REQUIRE(c == Complex{2, 2});
}

TEST_CASE("complex-add-int", "addition") {
    auto a = 4 + 2_r;
    REQUIRE(a == Complex{6, 0});

    auto b = 4 + 2_im;
    REQUIRE(b == Complex{4, 2});
}

TEST_CASE("complex-multiplication", "multiplication") {
    auto a = 1_r + 2_im;
    auto b = 3_r + 4_im;
    REQUIRE(a == Complex{1, 2});
    REQUIRE(b == Complex{3, 4});

    auto c = a * b;
    REQUIRE(c == Complex{-5, 10});
}

TEST_CASE("complex-str", "str") {
    auto a = 9_r + 5_im;
    REQUIRE(a.to_str() == "9+5i");
    INFO("Maybe not great");
    WARN("Definitely not great");
}