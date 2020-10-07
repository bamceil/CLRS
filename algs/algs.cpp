#include "algs.hpp"

using namespace std;

int CLRS::horner_multiplication(vector<int> &a, int x)
{
    int y = 0;
    for (int i = a.size() - 1; i >= 0; --i)
        y = a[i] + x * y;
    return y;
}

pair<int, int> min_max(vector<int> &v)
{
    if (v.empty())
        return make_pair(-1, -1);
    else if (v.size() == 1)
        return make_pair(0, -1);
    else
    {
        int minx = v[0] < v[1] ? 0 : 1;
        int maxx = v[0] > v[1] ? 0 : 1;
        for (int i = 2; i < v.size(); ++i)
        {
            if (v[i] > maxx)
                maxx = i;
            else if (v[i] < minx)
                minx = i;
            else
                continue;
        }
        return make_pair(minx, maxx);
    }
}