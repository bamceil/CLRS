#include "sort.hpp"
#include <gtest/gtest.h>

using namespace std;
using namespace CLRS;

vector<int> basicInput{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

TEST(MergeSortTest, EmptyInput)
{
    vector<int> vec;
    ASSERT_NO_THROW(merge_sort(vec));
    EXPECT_EQ(0, vec.size());
}

TEST(MergeSortTest, BasicInput)
{
    vector<int> vec1{0, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    ASSERT_NO_THROW(merge_sort(vec1));
    EXPECT_EQ(vec1, basicInput);
}

TEST(InsertSortTest, EmptyInput)
{
    vector<int> vec;
    ASSERT_NO_THROW(insert_sort(vec));
    EXPECT_EQ(0, vec.size());
}

TEST(InsertSortTest, BasicInput)
{
    vector<int> vec1{0, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    ASSERT_NO_THROW(insert_sort(vec1));
    EXPECT_EQ(vec1, basicInput);
}

TEST(SelectSortTest, EmptyInput)
{
    vector<int> vec;
    ASSERT_NO_THROW(select_sort(vec));
    EXPECT_EQ(0, vec.size());
}

TEST(SelectSortTest, BasicInput)
{
    vector<int> vec1{0, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    ASSERT_NO_THROW(select_sort(vec1));
    EXPECT_EQ(vec1, basicInput);
}

TEST(HeapSortTest, EmptyInput)
{
    vector<int> vec;
    ASSERT_NO_THROW(heap_sort(vec));
    EXPECT_EQ(0, vec.size());
}

TEST(HeapSortTest, BasicInput)
{
    vector<int> vec1{0, 7, 5, 9, 6, 8, 4, 1, 2, 3};
    ASSERT_NO_THROW(heap_sort(vec1));
    EXPECT_EQ(vec1, basicInput);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
