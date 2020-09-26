#include "sort.hpp"

using namespace std;

// Sort array from begin to end by merge sort algs.
void merge_sort(vector<int> &vec, int begin, int end, int *arr);
// Merge a subarray from begin to mid and a subarray from mid to end
void merge(vector<int> &vec, int begin, int mid, int end, int *arr);
// Build a heap.
void make_heap(vector<int> &vec);
// For Heap & Heap sort.
// Return left child index. The root is at index 0.
int left_child(int parent) { return 2 * parent + 1; }
// For Heap & Heap sort.
// Return right child index. The root is at index 0.
int right_child(int parent) { return 2 * parent + 2; }
// For Heap & Heap sort.
// Return parent index. The root is at index 0.
int parent(int child) { return (child - 1) / 2; }
void swim(vector<int> &, int);
void sink(vector<int> &, int, int);

void CLRS::merge_sort(vector<int> &vec)
{
    int *arr = new int[vec.size()];
    ::merge_sort(vec, 0, vec.size() - 1, arr);
    delete[] arr;
}

void merge_sort(vector<int> &vec, int begin, int end, int *arr)
{
    if (begin >= end)
        return;
    int mid = begin + (end - begin) / 2;
    merge_sort(vec, begin, mid, arr);
    merge_sort(vec, mid + 1, end, arr);
    merge(vec, begin, mid, end, arr);
}

void merge(vector<int> &vec, int begin, int mid, int end, int *arr)
{
    int i = begin, j = mid + 1, k = 0;
    while (i <= mid && j <= end)
    {
        if (vec[i] <= vec[j])
            arr[k++] = vec[i++];
        else
            arr[k++] = vec[j++];
    }
    while (i <= mid)
        arr[k++] = vec[i++];
    while (j <= end)
        arr[k++] = vec[j++];

    for (int i = 0; i < k; ++i)
        vec[begin + i] = arr[i];
}

void CLRS::insert_sort(vector<int> &vec)
{
    for (size_t i = 1; i < vec.size(); ++i)
    {
        for (int j = i; j > 0; --j)
        {
            if (vec[j] < vec[j - 1])
                swap(vec[j], vec[j - 1]);
            else
                break;
        }
    }
}

void CLRS::select_sort(vector<int> &vec)
{
    for (size_t i = 0; i < vec.size(); ++i)
    {
        size_t min_idx = i;
        for (size_t j = i + 1; j < vec.size(); ++j)
        {
            if (vec[min_idx] > vec[j])
                min_idx = j;
        }
        swap(vec[min_idx], vec[i]);
    }
}

void CLRS::heap_sort(vector<int> &vec)
{
    make_heap(vec);
}

void make_heap(vector<int> &vec)
{
    int size = vec.size();
    for (int i = vec.size() / 2; i >= 0; --i)
        sink(vec, i, size);

    while (size > 0)
    {
        swap(vec[0], vec[size - 1]);
        --size;
        sink(vec, 0, size);
    }
}

void swim(vector<int> &vec, int k)
{
    int p = parent(k);
    while (p >= 0 && vec[p] < vec[k])
    {
        swap(vec[p], vec[k]);
        k = p;
        p = parent(k);
    }
}
void sink(vector<int> &vec, int k, int size)
{
    while (left_child(k) < size)
    {
        int j = left_child(k);
        if (j < size - 1 && vec[j] < vec[j + 1])
            ++j;
        if (vec[k] < vec[j])
        {
            swap(vec[k], vec[j]);
            k = j;
        }
        else
            break;
    }
}