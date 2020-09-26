#include "search.hpp"

using namespace std;

int CLRS::linear_search(vector<int> &vec, int target)
{
    for (int i = 0; i < vec.size(); ++i)
    {
        if (vec[i] == target)
            return i;
    }
    return -1;
}

int CLRS::binary_search(vector<int> &vec, int target)
{
    int begin = 0, end = vec.size() - 1;

    while (begin <= end)
    {
        int mid = begin + (end - begin) / 2;
        if (vec[mid] == target)
            return mid;
        else if (vec[mid] < target)
            begin = mid + 1;
        else
            end = mid - 1;
    }
    return -1;
}