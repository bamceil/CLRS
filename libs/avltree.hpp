#pragma once

#include <functional>
#include <memory>

namespace CLRS {

struct avltree_node {
public:
    int value_;

    explicit avltree_node(int value) : value_(value), height_(0), left_(), right_() {}

private:
    int height_;
    std::shared_ptr<avltree_node> left_;
    std::shared_ptr<avltree_node> right_;

    friend class avltree;
};

class avltree {
public:
    using pointer = std::shared_ptr<avltree_node>;

    avltree() : count_(0), root_() {}

    void insert(int value);
    void remove(int value);
    const pointer find(int value) const;
    constexpr size_t size() const { return count_; }
    constexpr bool empty() const { return count_ == 0; }
    const pointer min_element() const { return min_element(root_); }
    const pointer max_element() const { return max_element(root_); }
    const pointer min_element(pointer ptr) const;
    const pointer max_element(pointer ptr) const;
    void walk_preorder(std::function<void(int)> f) const;
    void walk_inorder(std::function<void(int)> f) const;
    void walk_postorder(std::function<void(int)> f) const;
    int height() const { return height(root_); }

private:
    pointer rotate_LL(pointer ptr);
    pointer rotate_RR(pointer ptr);
    pointer rotate_LR(pointer ptr);
    pointer rotate_RL(pointer ptr);
    pointer insert(pointer ptr, int value);
    pointer remove(pointer root, pointer ptr);
    int height(pointer ptr) const {
        if (ptr) return ptr->height_;
        return 0;
    }

private:
    size_t count_;
    pointer root_;
};
}  // namespace CLRS
