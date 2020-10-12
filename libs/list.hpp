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
    void push_back(int value);
    void push_front(int value);
    void pop_back();
    void pop_front();
    // if empty -- panic!
    int front() const { return head_->value_; }
    // if empty -- panic!
    int back() const { return tail_->value_; }
    void remove(std::shared_ptr<inner_node> iter);
    const std::shared_ptr<inner_node> find(int target) const;

    void print() const;

private:
    std::shared_ptr<inner_node> head_;
    std::shared_ptr<inner_node> tail_;
    size_t count_;
};

class stack {
public:
    void push(int v) { ls_.push_back(v); }
    int pop() {
        int ret = ls_.back();
        ls_.pop_back();
        return ret;
    }
    int peek() { return ls_.back(); }

private:
    list ls_;
};

class queue {
public:
    void enqueue(int v) { ls_.push_back(v); }
    int dequeue() {
        int ret = ls_.front();
        ls_.pop_front();
        return ret;
    }
    int peek() { return ls_.front(); }

private:
    list ls_;
};

}  // namespace CLRS