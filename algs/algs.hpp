#pragma once

#include <vector>

namespace CLRS
{
    int horner_multiplication(std::vector<int> &a, int x);
    // Return index. -1 is not found.  <min, max>
    std::pair<int, int> min_max(std::vector<int> &v);
} // namespace CLRS
