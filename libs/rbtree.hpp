#pragma once

#include <functional>
#include <memory>

namespace CLRS {
enum class rb_color {
    RED,
    BLACK,
};

struct rb_node {
    int value_;

    rb_node() : value_(0), color_(rb_color::RED), left_(), right_(), parent_() {}
    explicit rb_node(int v) : value_(v), color_(rb_color::RED), left_(), right_(), parent_() {}

private:
    rb_color color_;
    std::shared_ptr<rb_node> left_;
    std::shared_ptr<rb_node> right_;
    std::weak_ptr<rb_node> parent_;

    friend class red_black_tree;
};

class red_black_tree {
public:
    using pointer = std::shared_ptr<rb_node>;

    red_black_tree() : root_(), count_(0) {}
    ~red_black_tree() {}

    void insert(int value);
    void remove(pointer ptr);
    pointer find(int value) const;
    constexpr size_t size() const { return count_; }
    constexpr bool empty() const { return count_ == 0; }
    size_t left_count(pointer ptr) const { return count(ptr->left_); }
    size_t right_count(pointer ptr) const { return count(ptr->right_); }
    size_t count(pointer ptr) const;
    const pointer root() const { return root_; }

    const pointer min_element() const;
    const pointer max_element() const;

    void walk_preorder(std::function<void(int)> f) const;

    void walk_inorder(std::function<void(int)> f) const;

    void walk_postorder(std::function<void(int)> f) const;

private:
    void left_rotate(pointer ptr);
    void right_rotate(pointer ptr);
    void handle_insert_color(pointer ptr);

private:
    pointer root_;
    size_t count_;
};

}  // namespace CLRS
