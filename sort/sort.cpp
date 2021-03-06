#include "sort.hpp"

#include <iostream>
#include <random>

using namespace std;

// Sort array from begin to end by merge sort algs.
void merge_sort(vector<int>& vec, int begin, int end, int* arr);
// Merge a subarray from begin to mid and a subarray from mid to end
void merge(vector<int>& vec, int begin, int mid, int end, int* arr);
// Build a heap.
void make_heap(vector<int>& vec);
// For Heap & Heap Sort.
// Return left child index. The root is at index 0.
int left_child(int parent) { return 2 * parent + 1; }
// For Heap & Heap Sort.
// Return right child index. The root is at index 0.
int right_child(int parent) { return 2 * parent + 2; }
// For Heap & Heap Sort.
// Return parent index. The root is at index 0.
int parent(int child) { return (child - 1) / 2; }
void swim(vector<int>&, int);
void sink(vector<int>&, int, int);
void quick_sort(vector<int>& vec, int begin, int end);
// For Quick Sort
int partition(vector<int>& vec, int begin, int end);
// For Quick Sort (Median-3 version)
// Return the pivot index
int pivot(vector<int>& vec, int begin, int end);
// For Quick Sort (Median-3 version)
// Return median number index from (i, j, k)
int median3(vector<int>& vec, int i, int j, int k);
void quick_sort_median3(vector<int>& vec, int begin, int end);
int partition_median3(vector<int>& vec, int begin, int end);
// For Quick Sort (Three way version)
void way3sort(vector<int>& vec, int begin, int end);
void radix_count_sort(vector<int>& vec, int exp);

void CLRS::merge_sort(vector<int>& vec) {
    int* arr = new int[vec.size()];
    ::merge_sort(vec, 0, vec.size() - 1, arr);
    delete[] arr;
}

void merge_sort(vector<int>& vec, int begin, int end, int* arr) {
    if (begin >= end) return;
    int mid = begin + (end - begin) / 2;
    merge_sort(vec, begin, mid, arr);
    merge_sort(vec, mid + 1, end, arr);
    merge(vec, begin, mid, end, arr);
}

void merge(vector<int>& vec, int begin, int mid, int end, int* arr) {
    int i = begin, j = mid + 1, k = 0;
    while (i <= mid && j <= end) {
        if (vec[i] <= vec[j])
            arr[k++] = vec[i++];
        else
            arr[k++] = vec[j++];
    }
    while (i <= mid) arr[k++] = vec[i++];
    while (j <= end) arr[k++] = vec[j++];

    for (int i = 0; i < k; ++i) vec[begin + i] = arr[i];
}

void CLRS::merge_sort_b2u(vector<int>& vec) {
    int* tmp = new int[vec.size()];
    for (int len = 1; len < vec.size(); len *= 2) {
        for (int lo = 0; lo < vec.size() - len; lo += len + len) {
            int mid = lo + len - 1;
            int hi = min(lo + len + len - 1, static_cast<int>(vec.size()) - 1);
            merge(vec, lo, mid, hi, tmp);
        }
    }

    delete[] tmp;
}

void CLRS::insert_sort(vector<int>& vec) {
    for (size_t i = 1; i < vec.size(); ++i) {
        for (int j = i; j > 0; --j) {
            if (vec[j] < vec[j - 1])
                swap(vec[j], vec[j - 1]);
            else
                break;
        }
    }
}

void CLRS::select_sort(vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < vec.size(); ++j) {
            if (vec[min_idx] > vec[j]) min_idx = j;
        }
        swap(vec[min_idx], vec[i]);
    }
}

void CLRS::heap_sort(vector<int>& vec) { make_heap(vec); }

void make_heap(vector<int>& vec) {
    int size = vec.size();
    for (int i = vec.size() / 2; i >= 0; --i) sink(vec, i, size);

    while (size > 0) {
        swap(vec[0], vec[size - 1]);
        --size;
        sink(vec, 0, size);
    }
}

void swim(vector<int>& vec, int k) {
    int p = parent(k);
    while (p >= 0 && vec[p] < vec[k]) {
        swap(vec[p], vec[k]);
        k = p;
        p = parent(k);
    }
}

void sink(vector<int>& vec, int k, int size) {
    while (left_child(k) < size) {
        int j = left_child(k);
        if (j < size - 1 && vec[j] < vec[j + 1]) ++j;
        if (vec[k] < vec[j]) {
            swap(vec[k], vec[j]);
            k = j;
        }
        else
            break;
    }
}

void CLRS::quick_sort(vector<int>& vec) { ::quick_sort(vec, 0, vec.size() - 1); }

void quick_sort(vector<int>& vec, int begin, int end) {
    if (begin >= end) return;
    int idx = partition(vec, begin, end);
    quick_sort(vec, begin, idx - 1);
    quick_sort(vec, idx + 1, end);
}

int partition(vector<int>& vec, int begin, int end) {
    int i = begin + 1, j = end;
    while (i <= j) {
        while (i <= j && vec[i] <= vec[begin]) ++i;
        while (i <= j && vec[j] >= vec[begin]) --j;
        if (i > j) break;
        swap(vec[i], vec[j]);
    }
    swap(vec[j], vec[begin]);
    return j;
}

void CLRS::quick_sort_median3(std::vector<int>& vec) { ::quick_sort_median3(vec, 0, vec.size() - 1); }

int median3(vector<int>& vec, int i, int j, int k) {
    int idx = vec[i] < vec[j] ? i : j;
    if (vec[idx] > vec[k]) return idx;
    if (idx == i)
        return vec[j] < vec[k] ? j : k;
    else
        return vec[i] < vec[k] ? i : k;
}

int pivot(vector<int>& vec, int begin, int end) {
    random_device rd;
    default_random_engine gen(rd());
    uniform_int_distribution<> dis(begin, end);
    int i = dis(gen);
    int j = dis(gen);
    int k = dis(gen);
    return median3(vec, i, j, k);
}

void quick_sort_median3(vector<int>& vec, int begin, int end) {
    if (begin >= end) return;
    int idx = partition_median3(vec, begin, end);
    quick_sort_median3(vec, begin, idx - 1);
    quick_sort_median3(vec, idx + 1, end);
}

int partition_median3(vector<int>& vec, int begin, int end) {
    swap(vec[pivot(vec, begin, end)], vec[begin]);
    int i = begin + 1, j = end;
    while (i <= j) {
        while (i <= j && vec[i] <= vec[begin]) ++i;
        while (i <= j && vec[j] >= vec[begin]) --j;
        if (i > j) break;
        swap(vec[i], vec[j]);
    }
    swap(vec[j], vec[begin]);
    return j;
}

void CLRS::quick_sort_3way(vector<int>& vec) { way3sort(vec, 0, vec.size() - 1); }

void way3sort(vector<int>& vec, int begin, int end) {
    if (begin >= end) return;
    int lt = begin, gt = end;
    int val = vec[lt];
    int i = lt + 1;
    while (i <= gt) {
        if (vec[i] < val)
            swap(vec[i++], vec[lt++]);
        else if (vec[i] > val)
            swap(vec[i], vec[gt--]);
        else
            ++i;
    }
    way3sort(vec, begin, lt - 1);
    way3sort(vec, gt + 1, end);
}

void CLRS::shell_sort(std::vector<int>& vec) {
    int len = vec.size();
    int ph = 1;
    while (ph < len / 3) ph = ph * 3 + 1;
    while (ph >= 1) {
        for (int i = ph; i < len; ++i) {
            for (int j = i; j >= ph && vec[j] < vec[j - ph]; j -= ph) swap(vec[j], vec[j - ph]);
        }
        ph /= 3;
    }
}

void CLRS::counting_sort(vector<int>& vec, int maxValue) {
    vector<int> cvec(maxValue + 1, 0);
    for (int i = 0; i < vec.size(); ++i) ++cvec[vec[i]];
    for (int i = 1; i <= maxValue; ++i) cvec[i] += cvec[i - 1];
    vector<int> sortedArray(vec.size(), 0);
    for (int i = vec.size() - 1; i >= 0; --i) {
        sortedArray[cvec[vec[i]] - 1] = vec[i];
        --cvec[vec[i]];
    }
    vec = sortedArray;
}

void CLRS::radix_sort(std::vector<int>& vec) {
    if (vec.empty()) return;
    int max = *max_element(vec.begin(), vec.end());

    for (int exp = 1; max / exp > 0; exp *= 10) ::radix_count_sort(vec, exp);
}

void radix_count_sort(vector<int>& vec, int exp) {
    vector<int> range(10, 0);
    vector<int> tmpVec(vec.size(), 0);

    for (int i = 0; i < vec.size(); ++i) range[(vec[i] / exp) % 10]++;

    for (int i = 1; i < range.size(); ++i) range[i] += range[i - 1];

    for (int i = vec.size() - 1; i >= 0; --i) {
        tmpVec[range[(vec[i] / exp) % 10] - 1] = vec[i];
        range[(vec[i] / exp) % 10]--;
    }
    vec = tmpVec;
}