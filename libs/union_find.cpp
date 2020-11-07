#include "union_find.hpp"

#include <cassert>
#include <iostream>

namespace CLRS {
int ufset::find(int v) {
    assert(v >= 0 && v < parent_.size());
    int root = v;
    while (root != parent_[root]) root = parent_[root];
    while (v != root) {
        int newp = parent_[v];
        parent_[v] = root;
        v = newp;
    }
    return root;
}

void ufset::connect(int u, int v) {
    int rootU = find(u);
    int rootV = find(v);
    if (rootU == rootV) return;

    if (size_[rootU] < size_[rootV]) {
        parent_[rootU] = rootV;
        size_[rootV] += size_[rootU];
    } else {
        parent_[rootV] = rootU;
        size_[rootU] += size_[rootV];
    }
    count_--;
}
}  // namespace CLRS

int main(int argc, char const* argv[]) {
    using namespace std;
    using namespace CLRS;

    ufset uf(100);
    uf.connect(1, 10);
    uf.connect(5, 20);
    uf.connect(2, 50);
    uf.connect(10, 70);
    uf.connect(7, 3);
    uf.connect(7, 4);
    uf.connect(2, 89);
    uf.connect(76, 92);
    uf.connect(45, 37);
    cout << uf.is_connected(45, 37) << endl;
    cout << uf.count() << endl;

    return 0;
}
