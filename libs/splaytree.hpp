#pragma once

#include <functional>
#include <memory>

namespace CLRS {
struct splay_node {
public:
    int value_;

    splay_node(int value) : value_(value), left_(), right_(), parent_() {}

private:
    std::shared_ptr<splay_node> left_;
    std::shared_ptr<splay_node> right_;
    std::weak_ptr<splay_node> parent_;

    friend class splay_tree;
};

class splay_tree {
public:
    using pointer = std::shared_ptr<splay_node>;

    splay_tree() : count_(0), root_() {}

    const pointer find(int value);
    void insert(int value);
    void remove(int value);
    constexpr size_t size() const { return count_; }
    constexpr bool empty() const { return count_ == 0; }
    void walk_preorder(const std::function<void(int)>& f) const;
    void walk_inorder(const std::function<void(int)>& f) const;
    void walk_postorder(const std::function<void(int)>& f) const;
    const pointer min_element();
    const pointer max_element();

private:
    void rotate_left(pointer ptr);
    void rotate_right(pointer ptr);
    void splay(pointer ptr);
    pointer min_element(pointer ptr);
    void replace(pointer u, pointer v);

private:
    size_t count_;
    pointer root_;
};
}  // namespace CLRS
