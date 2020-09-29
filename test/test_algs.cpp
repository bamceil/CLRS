#include "algs.hpp"

#include <gtest/gtest.h>
#include <vector>

using namespace std;
using namespace CLRS;

TEST(HornerMulti, NonInput)
{
    vector<int> v;
    EXPECT_EQ(0, horner_multiplication(v, 1));
}

TEST(HornerMulti, Xis0)
{
    vector<int> v{1, 2, 3};
    EXPECT_EQ(1, horner_multiplication(v, 0));
}

TEST(HornerMulti, RegularInput)
{
    vector<int> v{1, 2, 3, 4};
    EXPECT_EQ(142, horner_multiplication(v, 3));
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
