#include "hash.hpp"

#include <iostream>

namespace CLRS {

void hash_table_chainning::insert(int value) {
    size_t h = hash_(value) % countBubbles_;
    table_[h].push_back(value);
    ++count_;
}

void hash_table_chainning::remove(int value) {
    size_t h = hash_(value) % countBubbles_;
    auto iter = table_[h].find(value);
    if (!iter) return;
    table_[h].remove(iter);
    --count_;
}

bool hash_table_chainning::contains(int value) const {
    size_t h = hash_(value) % countBubbles_;
    return table_[h].find(value) ? true : false;
}

void hash_table_chainning::print() const {
    for (int i = 0; i < countBubbles_; ++i) std::cout << table_[i].size() << " ";
    std::cout << std::endl;
}

}  // namespace CLRS

int main(int argc, char const* argv[]) {
    using namespace CLRS;

    hash_table_chainning ht(50);

    for (int i = 0; i < 1000; ++i) ht.insert(i);

    ht.print();

    std::cout << ht.contains(1000) << " " << ht.contains(100) << std::endl;

    return 0;
}
