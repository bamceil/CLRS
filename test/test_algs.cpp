#include "algs.hpp"

#include <gtest/gtest.h>
#include <vector>

using namespace std;
using namespace CLRS;

TEST(HornerMulti, NonInput) {
    vector<int> v;
    EXPECT_EQ(0, horner_multiplication(v, 1));
}

TEST(HornerMulti, Xis0) {
    vector<int> v{ 1, 2, 3 };
    EXPECT_EQ(1, horner_multiplication(v, 0));
}

TEST(HornerMulti, RegularInput) {
    vector<int> v{ 1, 2, 3, 4 };
    EXPECT_EQ(142, horner_multiplication(v, 3));
}

TEST(MinMax, Empty) {
    vector<int> v;
    auto [minIdx, maxIdx] = min_max(v);
    EXPECT_EQ(minIdx, -1);
    EXPECT_EQ(maxIdx, -1);
}

TEST(MinMax, NoMax) {
    vector<int> v{ 6 };
    auto [minIdx, maxIdx] = min_max(v);
    EXPECT_EQ(minIdx, 0);
    EXPECT_EQ(maxIdx, -1);
}

TEST(MinMax, SimpleInput) {
    vector<int> v{ 6, 1, 2, 5, 7 };
    auto [minIdx, maxIdx] = min_max(v);
    EXPECT_EQ(minIdx, 1);
    EXPECT_EQ(maxIdx, 4);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
