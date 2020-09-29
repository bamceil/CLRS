#include "algs.hpp"

using namespace std;

int CLRS::horner_multiplication(vector<int> a, int x)
{
    int y = 0;
    for (int i = a.size() - 1; i >= 0; --i)
        y = a[i] + x * y;
    return y;
}