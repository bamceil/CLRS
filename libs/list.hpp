#pragma once

#include <memory>

namespace CLRS {

struct inner_node {
    int value_;

private:
    std::shared_ptr<inner_node> next_;
    std::weak_ptr<inner_node> prev_;
    friend class list;
};

class list {
public:
    list() : head_(), tail_(), count_(0) {}

public:
    constexpr size_t size() const { return count_; }
    constexpr bool empty() const { return count_ == 0; }
    void insert(int value);
    void remove(std::shared_ptr<inner_node> iter);
    std::shared_ptr<inner_node> find(int target);

    void print() const;

private:
    std::shared_ptr<inner_node> head_;
    std::shared_ptr<inner_node> tail_;
    size_t count_;
};

}  // namespace CLRS