#include "sort.hpp"
#include <algorithm>
#include <gtest/gtest.h>

using namespace std;
using namespace CLRS;

int f() {
    static int i = 0;
    return i++;
}
vector<int> rangeInput(1000);

TEST(MergeSortTest, EmptyInput) {
    vector<int> vec;
    ASSERT_NO_THROW(merge_sort(vec));
    EXPECT_EQ(0, vec.size());
}

TEST(MergeSortTest, BasicInput) {
    vector<int> vec1{ 0, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    ASSERT_NO_THROW(merge_sort(vec1));
    EXPECT_TRUE(is_sorted(vec1.begin(), vec1.end()));
}

TEST(MergeSortTest, ReverseInput) {
    vector<int> vec1 = rangeInput;
    reverse(vec1.begin(), vec1.end());
    ASSERT_NO_THROW(merge_sort(vec1));
    EXPECT_TRUE(is_sorted(vec1.begin(), vec1.end()));
}

TEST(MergeSortBUTest, EmptyInput) {
    vector<int> vec;
    ASSERT_NO_THROW(merge_sort_b2u(vec));
    EXPECT_EQ(0, vec.size());
}

TEST(MergeSortBUTest, BasicInput) {
    vector<int> vec1{ 0, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    ASSERT_NO_THROW(merge_sort_b2u(vec1));
    EXPECT_TRUE(is_sorted(vec1.begin(), vec1.end()));
}

TEST(MergeSortBUTest, ReverseInput) {
    vector<int> vec1 = rangeInput;
    reverse(vec1.begin(), vec1.end());
    ASSERT_NO_THROW(merge_sort_b2u(vec1));
    EXPECT_TRUE(is_sorted(vec1.begin(), vec1.end()));
}

TEST(InsertSortTest, EmptyInput) {
    vector<int> vec;
    ASSERT_NO_THROW(insert_sort(vec));
    EXPECT_EQ(0, vec.size());
}

TEST(InsertSortTest, BasicInput) {
    vector<int> vec1{ 0, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    ASSERT_NO_THROW(insert_sort(vec1));
    EXPECT_TRUE(is_sorted(vec1.begin(), vec1.end()));
}

TEST(InsertSortTest, ReverseInput) {
    vector<int> vec1 = rangeInput;
    reverse(vec1.begin(), vec1.end());
    ASSERT_NO_THROW(insert_sort(vec1));
    EXPECT_TRUE(is_sorted(vec1.begin(), vec1.end()));
}

TEST(SelectSortTest, EmptyInput) {
    vector<int> vec;
    ASSERT_NO_THROW(select_sort(vec));
    EXPECT_EQ(0, vec.size());
}

TEST(SelectSortTest, BasicInput) {
    vector<int> vec1{ 0, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    ASSERT_NO_THROW(select_sort(vec1));
    EXPECT_TRUE(is_sorted(vec1.begin(), vec1.end()));
}

TEST(SelectSortTest, ReverseInput) {
    vector<int> vec1 = rangeInput;
    reverse(vec1.begin(), vec1.end());
    ASSERT_NO_THROW(select_sort(vec1));
    EXPECT_TRUE(is_sorted(vec1.begin(), vec1.end()));
}

TEST(ShellSortTest, EmptyInput) {
    vector<int> vec;
    ASSERT_NO_THROW(shell_sort(vec));
    EXPECT_EQ(0, vec.size());
}

TEST(ShellSortTest, BasicInput) {
    vector<int> vec1{ 0, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    ASSERT_NO_THROW(shell_sort(vec1));
    EXPECT_TRUE(is_sorted(vec1.begin(), vec1.end()));
}

TEST(ShellSortTest, ReverseInput) {
    vector<int> vec1 = rangeInput;
    reverse(vec1.begin(), vec1.end());
    ASSERT_NO_THROW(shell_sort(vec1));
    EXPECT_TRUE(is_sorted(vec1.begin(), vec1.end()));
}

TEST(HeapSortTest, EmptyInput) {
    vector<int> vec;
    ASSERT_NO_THROW(heap_sort(vec));
    EXPECT_EQ(0, vec.size());
}

TEST(HeapSortTest, BasicInput) {
    vector<int> vec1{ 0, 7, 5, 9, 6, 8, 4, 1, 2, 3 };
    ASSERT_NO_THROW(heap_sort(vec1));
    EXPECT_TRUE(is_sorted(vec1.begin(), vec1.end()));
}

TEST(HeapSortTest, ReverseInput) {
    vector<int> vec1 = rangeInput;
    reverse(vec1.begin(), vec1.end());
    ASSERT_NO_THROW(heap_sort(vec1));
    EXPECT_TRUE(is_sorted(vec1.begin(), vec1.end()));
}

TEST(QuickSortTest, EmptyInput) {
    vector<int> vec;
    ASSERT_NO_THROW(quick_sort(vec));
    EXPECT_EQ(0, vec.size());
}

TEST(QuickSortTest, BasicInput) {
    vector<int> vec1{ 0, 7, 5, 9, 6, 8, 4, 1, 2, 3 };
    ASSERT_NO_THROW(quick_sort(vec1));
    EXPECT_TRUE(is_sorted(vec1.begin(), vec1.end()));
}

TEST(QuickSortTest, ReverseInput) {
    vector<int> vec1 = rangeInput;
    reverse(vec1.begin(), vec1.end());
    ASSERT_NO_THROW(quick_sort(vec1));
    EXPECT_TRUE(is_sorted(vec1.begin(), vec1.end()));
}

TEST(Median3QuickSortTest, EmptyInput) {
    vector<int> vec;
    ASSERT_NO_THROW(quick_sort_median3(vec));
    EXPECT_EQ(0, vec.size());
}

TEST(Median3QuickSortTest, BasicInput) {
    vector<int> vec1{ 0, 7, 5, 9, 6, 8, 4, 1, 2, 3 };
    ASSERT_NO_THROW(quick_sort_median3(vec1));
    EXPECT_TRUE(is_sorted(vec1.begin(), vec1.end()));
}

TEST(Median3QuickSortTest, ReverseInput) {
    vector<int> vec1 = rangeInput;
    reverse(vec1.begin(), vec1.end());
    ASSERT_NO_THROW(quick_sort_median3(vec1));
    EXPECT_TRUE(is_sorted(vec1.begin(), vec1.end()));
}

TEST(ThreeWayQuickSortTest, EmptyInput) {
    vector<int> vec;
    ASSERT_NO_THROW(quick_sort_3way(vec));
    EXPECT_EQ(0, vec.size());
}

TEST(ThreeWayQuickSortTest, BasicInput) {
    vector<int> vec1{ 0, 7, 5, 9, 6, 8, 4, 1, 2, 3 };
    ASSERT_NO_THROW(quick_sort_3way(vec1));
    EXPECT_TRUE(is_sorted(vec1.begin(), vec1.end()));
}

TEST(ThreeWayQuickSortTest, ReverseInput) {
    vector<int> vec1 = rangeInput;
    reverse(vec1.begin(), vec1.end());
    ASSERT_NO_THROW(quick_sort_3way(vec1));
    EXPECT_TRUE(is_sorted(vec1.begin(), vec1.end()));
}

TEST(CountingSortTest, EmptyInput) {
    vector<int> vec;
    ASSERT_NO_THROW(counting_sort(vec, 0));
    EXPECT_EQ(0, vec.size());
    ASSERT_NO_THROW(counting_sort(vec, 10));
    EXPECT_EQ(0, vec.size());
}

TEST(CountingSortTest, BasicInput) {
    vector<int> vec1{ 0, 7, 5, 9, 6, 8, 4, 1, 2, 3 };
    ASSERT_NO_THROW(counting_sort(vec1, 9));
    EXPECT_TRUE(is_sorted(vec1.begin(), vec1.end()));
}

TEST(CountingSortTest, ReverseInput) {
    vector<int> vec1 = rangeInput;
    reverse(vec1.begin(), vec1.end());
    ASSERT_NO_THROW(counting_sort(vec1, rangeInput.size() - 1));
    EXPECT_TRUE(is_sorted(vec1.begin(), vec1.end()));
}

TEST(RadixSortTest, EmptyInput) {
    vector<int> vec;
    ASSERT_NO_THROW(radix_sort(vec));
    EXPECT_EQ(0, vec.size());
}

TEST(RadixSortTest, BasicInput) {
    vector<int> vec1{ 10, 71, 25, 9, 6, 8, 14, 1, 2, 3 };
    ASSERT_NO_THROW(radix_sort(vec1));
    EXPECT_TRUE(is_sorted(vec1.begin(), vec1.end()));
}

TEST(RadixSortTest, ReverseInput) {
    vector<int> vec1 = rangeInput;
    reverse(vec1.begin(), vec1.end());
    ASSERT_NO_THROW(radix_sort(vec1));
    EXPECT_TRUE(is_sorted(vec1.begin(), vec1.end()));
}

int main(int argc, char* argv[]) {
    generate(rangeInput.begin(), rangeInput.end(), f);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
