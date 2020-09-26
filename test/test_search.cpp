#include "search.hpp"
#include <gtest/gtest.h>

using namespace std;
using namespace CLRS;

vector<int> sortedArray{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 21, 31, 42, 53, 64, 75, 86, 97, 111, 222, 333, 444, 556};

TEST(LinearSearch, EmptyArray)
{
    vector<int> vec;
    EXPECT_EQ(-1, linear_search(vec, 1));
}

TEST(LinearSearch, NotFound)
{
    EXPECT_EQ(-1, linear_search(sortedArray, 12));
}

TEST(LinearSearch, Found)
{
    EXPECT_EQ(6, linear_search(sortedArray, 6));
}

TEST(BinarySearch, EmptyArray)
{
    vector<int> vec;
    EXPECT_EQ(-1, binary_search(vec, 1));
}

TEST(BinarySearch, NotFound)
{
    EXPECT_EQ(-1, binary_search(sortedArray, 12));
}

TEST(BinarySearch, Found)
{
    EXPECT_EQ(6, binary_search(sortedArray, 6));
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
