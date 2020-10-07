#include "list.hpp"
#include <gtest/gtest.h>

using namespace std;

TEST(SharedPtrList, NormalTest) {
    CLRS::list ls;
    for (int i = 0; i < 10; ++i) ls.insert(i);
    EXPECT_EQ(ls.size(), 10);
    shared_ptr<CLRS::inner_node> ptr = ls.find(5);
    ASSERT_TRUE(ptr);
    EXPECT_EQ(ptr->value_, 5);
    ls.remove(ptr);
    EXPECT_EQ(ls.size(), 9);
}

TEST(SharedPtrList, NotFoundTest) {
    CLRS::list ls;
    for (int i = 0; i < 10; ++i) ls.insert(i);
    EXPECT_EQ(ls.size(), 10);
    shared_ptr<CLRS::inner_node> ptr = ls.find(-6);
    EXPECT_FALSE(ptr);
    ls.remove(ptr);
    EXPECT_EQ(ls.size(), 10);
}

TEST(SharedPtrList, BorderTest) {
    CLRS::list ls;
    for (int i = 0; i < 10; ++i) ls.insert(i);
    EXPECT_EQ(ls.size(), 10);
    shared_ptr<CLRS::inner_node> ptr = ls.find(0);
    ASSERT_TRUE(ptr);
    EXPECT_EQ(ptr->value_, 0);
    ls.remove(ptr);
    EXPECT_EQ(ls.size(), 9);
    ptr = ls.find(9);
    ASSERT_TRUE(ptr);
    EXPECT_EQ(ptr->value_, 9);
    ls.remove(ptr);
    EXPECT_EQ(ls.size(), 8);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}