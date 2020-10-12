#pragma once

#include <functional>
#include <memory>

namespace CLRS {

struct tree_node {
public:
    int value_;

private:
    std::shared_ptr<tree_node> left_;
    std::shared_ptr<tree_node> right_;
    std::weak_ptr<tree_node> parent_;

    friend class binary_search_tree;
};

class binary_search_tree {
public:
    using pointer = std::shared_ptr<tree_node>;

    binary_search_tree() : root_(), count_(0) {}
    ~binary_search_tree() {}

    void insert(int value);
    void remove(pointer ptr);
    const pointer find(int value) const;
    constexpr size_t size() const { return count_; }
    constexpr bool empty() const { return count_ == 0; }
    const pointer min_element() const;
    const pointer max_element() const;

    void walk_preorder(std::function<void(int)> f) const;

    void walk_inorder(std::function<void(int)> f) const;

    void walk_postorder(std::function<void(int)> f) const;

private:
    const pointer find_successor(pointer ptr);

private:
    pointer root_;
    size_t count_;
};

}  // namespace CLRS
