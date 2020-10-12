#pragma once

#include "list.hpp"
#include <functional>

namespace CLRS {

class hash_table_chainning {
public:
    hash_table_chainning(size_t countOfBubbles) : table_(new list[countOfBubbles]), count_(0), countBubbles_(countOfBubbles), hash_() {}

    void insert(int value);
    void remove(int value);
    size_t size() const { return count_; }
    bool contains(int value) const;
    bool empty() const { return count_ == 0; }

    void print() const;

private:
    std::unique_ptr<list[]> table_;
    size_t count_;
    size_t countBubbles_;
    std::hash<int> hash_;
};

}  // namespace CLRS
