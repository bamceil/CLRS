#pragma once

#include <vector>

namespace CLRS {
// weighted quick-union with path compression
// Values: 0 ~ N-1
class ufset {
public:
    explicit ufset(int N) : size_(N, 1), parent_(N), count_(N) {
        for (int i = 0; i < N; i++) parent_[i] = i;
    }

    int find(int v);
    void connect(int u, int v);
    bool is_connected(int u, int v) { return find(v) == find(u); }
    size_t count() const { return count_; }

private:
    std::vector<int> size_;
    std::vector<int> parent_;
    size_t count_;
};

}  // namespace CLRS
