#include "sort.hpp"

#define CSIZE 100000

#include <algorithm>
#include <benchmark/benchmark.h>
#include <random>

#ifdef _WIN32
#pragma comment(lib, "Shlwapi.lib")
#ifdef _DEBUG
#pragma comment(lib, "benchmark.lib")
#pragma comment(lib, "benchmark_main.lib")
#else
#pragma comment(lib, "benchmark.lib")
#pragma comment(lib, "benchmark_main.lib")
#endif
#endif

using namespace std;

vector<int> testArray(CSIZE);

int f() {
    static int i = CSIZE;
    return i--;
}

class BuildContainer {
public:
    BuildContainer() { generate(testArray.begin(), testArray.end(), f); }
};

BuildContainer b;

void insert_sort(benchmark::State& state) {
    for (auto _ : state) CLRS::insert_sort(std::vector<int>(testArray));
}

BENCHMARK(insert_sort);

void select_sort(benchmark::State& state) {
    for (auto _ : state) CLRS::select_sort(std::vector<int>(testArray));
}

BENCHMARK(select_sort);

void merge_sort(benchmark::State& state) {
    for (auto _ : state) CLRS::merge_sort(std::vector<int>(testArray));
}

BENCHMARK(merge_sort);

void mergeb2u_sort(benchmark::State& state) {
    for (auto _ : state) CLRS::merge_sort_b2u(std::vector<int>(testArray));
}

BENCHMARK(mergeb2u_sort);

void shell_sort(benchmark::State& state) {
    for (auto _ : state) CLRS::shell_sort(std::vector<int>(testArray));
}

BENCHMARK(shell_sort);

void heap_sort(benchmark::State& state) {
    for (auto _ : state) CLRS::heap_sort(std::vector<int>(testArray));
}

BENCHMARK(heap_sort);

void quick_sort(benchmark::State& state) {
    for (auto _ : state) CLRS::quick_sort(std::vector<int>(testArray));
}

BENCHMARK(quick_sort);

void quick_median3_sort(benchmark::State& state) {
    for (auto _ : state) CLRS::quick_sort_median3(std::vector<int>(testArray));
}

BENCHMARK(quick_median3_sort);

void quick_3way_sort(benchmark::State& state) {
    for (auto _ : state) CLRS::quick_sort_3way(std::vector<int>(testArray));
}

BENCHMARK(quick_3way_sort);

BENCHMARK_MAIN();