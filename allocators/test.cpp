#include "allocator.h"

#include <gtest/gtest.h>
#include <new>
#include <string_view>

struct TestStruct {
    int id;
    std::string_view data;
};

class AllocatorTest : public testing::Test {
  protected:
    AllocatorTest() {
    }

    ~AllocatorTest() override {
    }

    void SetUp() override {
        alloc.clear();
    }

    void TearDown() override {
    }

    ArrayAllocator<int> alloc;

};

TEST_F(AllocatorTest, allocate_single) {
    auto* a = alloc.allocate(1);
    auto* b = alloc.allocate(1);

    EXPECT_GT(b, a);
    EXPECT_EQ(alloc.usage(), 2);
}

TEST_F(AllocatorTest, deallocate_single) {
    auto* a = alloc.allocate(1);
    auto* b = alloc.allocate(1);
    alloc.deallocate(a, 1);
    EXPECT_EQ(alloc.usage(), 1);
    alloc.deallocate(b, 1);
    EXPECT_EQ(alloc.usage(), 0);
}

TEST_F(AllocatorTest, find_space) {
    EXPECT_EQ(alloc.find_space(2), 0);
    auto* a = alloc.allocate(2);
    EXPECT_EQ(alloc.find_space(2), 2);
    auto* b = alloc.allocate(2);
    EXPECT_EQ(alloc.find_space(1), 4);
    auto* c = alloc.allocate(1);
    EXPECT_EQ(alloc.find_space(3), 5);
    auto* d = alloc.allocate(3);
    EXPECT_EQ(alloc.find_space(2), 8);
    auto* e = alloc.allocate(2);
    EXPECT_EQ(alloc.usage(), 10);

    EXPECT_THROW(alloc.find_space(3), std::bad_alloc);
    alloc.deallocate(a, 2);
    EXPECT_THROW(alloc.find_space(3), std::bad_alloc);
    alloc.deallocate(b, 2);
    EXPECT_EQ(alloc.find_space(3), 0);
    a = alloc.allocate(2);
    alloc.deallocate(d, 3);
    EXPECT_EQ(alloc.find_space(3), 5);
    a = alloc.allocate(3);
}
