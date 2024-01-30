#include "container.h"
#include <iostream>
#include <ranges>
#include <gtest/gtest.h>

struct ContainerTest : ::testing::Test {
    virtual void SetUp() {
    }

    void insert_some() {
        c.insert(Item{1, "Arensch", 0});
        c.insert(Item{2, "Berensch", 0});
        c.insert(Item{3, "Cadenberge", 1});
        c.insert(Item{4, "Delmenhorst", 1});
        c.insert(Item{5, "Emden", 0});
    }
    Container c;
};

TEST_F(ContainerTest, insert) {
    Container c;
    c.insert(Item{1, "Arensch", 0});
}

TEST_F(ContainerTest, empty_and_size) {
    EXPECT_TRUE(c.empty());
    EXPECT_EQ(0, c.size());
    insert_some();
    EXPECT_EQ(5, c.size());
    EXPECT_FALSE(c.empty());
}

TEST_F(ContainerTest, insert_remove) {
    Container c;
    EXPECT_EQ(0, c.size());
    c.insert(Item{1, "Arensch", 0});
    EXPECT_EQ(1, c.size());
    c.remove(999);
    EXPECT_EQ(1, c.size());
    c.remove(1);
    EXPECT_EQ(0, c.size());
}

TEST_F(ContainerTest, iterator_distance) {
    EXPECT_EQ(0, std::distance(c.begin(), c.end()));
    insert_some();
    EXPECT_EQ(5, std::distance(c.begin(), c.end()));
}

TEST_F(ContainerTest, filter_iterator) {
    insert_some();

    auto only_level_one = [](auto item) { return item.m_level == 1; };

    auto iter = c.filter_view(only_level_one);

    EXPECT_EQ(2, std::distance(iter.begin(), iter.end()));
}

TEST_F(ContainerTest, cpp20_ranges) {
    using namespace std::views;
    insert_some();

    auto only_level_one = [](auto item) { return item.m_level == 1; };
    auto iter = c | filter(only_level_one);
    EXPECT_EQ(2, std::distance(iter.begin(), iter.end()));
}