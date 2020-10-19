#include "tree.hpp"

#include <iostream>
#include <random>
#include <stack>

namespace CLRS {

void binary_search_tree::walk_preorder(std::function<void(int)> f) const {
    if (empty()) return;
    std::stack<pointer> ptrs;
    ptrs.push(root_);
    while (!ptrs.empty()) {
        pointer ptr = ptrs.top();
        ptrs.pop();
        f(ptr->value_);
        if (!ptr->right_) ptrs.push(ptr->right_);
        if (!ptr->left_) ptrs.push(ptr->left_);
    }
}

void binary_search_tree::walk_inorder(std::function<void(int)> f) const {
    if (empty()) return;
    std::stack<pointer> ptrs;
    pointer ptr = root_;
    while (ptr || !ptrs.empty()) {
        while (ptr) {
            ptrs.emplace(ptr);
            ptr = ptr->left_;
        }
        ptr = ptrs.top();
        ptrs.pop();
        f(ptr->value_);
        ptr = ptr->right_;
    }
}

void binary_search_tree::walk_postorder(std::function<void(int)> f) const {
    if (empty()) return;
    std::stack<pointer> ptrs;
    pointer ptr = root_;
    pointer prev;
    while (ptr || !ptrs.empty()) {
        while (ptr) {
            ptrs.emplace(ptr);
            ptr = ptr->left_;
        }
        ptr = ptrs.top();
        ptrs.pop();
        if (!ptr->right_ || ptr->right_ == prev) {  // 如果右子树被访问过或者为空
            f(ptr->value_);
            prev = ptr;
            ptr.reset();
        } else {
            ptrs.emplace(ptr);
            ptr = ptr->right_;
        }
    }
}

const binary_search_tree::pointer binary_search_tree::find(int value) const {
    std::shared_ptr<tree_node> root = root_;
    while (root && root->value_ != value) {
        if (value < root->value_)
            root = root->left_;
        else
            root = root->right_;
    }
    return root;
}

const binary_search_tree::pointer binary_search_tree::min_element() const {
    pointer ptr = root_;
    while (ptr && ptr->left_) ptr = ptr->left_;
    return ptr;
}

const binary_search_tree::pointer binary_search_tree::max_element() const {
    pointer ptr = root_;
    while (ptr && ptr->right_) ptr = ptr->right_;
    return ptr;
}

void binary_search_tree::insert(int value) {
    pointer nptr(new tree_node);
    nptr->value_ = value;

    pointer ptr = root_;
    pointer prev;
    while (ptr) {
        prev = ptr;
        if (value < ptr->value_)
            ptr = ptr->left_;
        else
            ptr = ptr->right_;
    }
    if (!prev)  // empty
        root_ = nptr;
    else if (value < prev->value_) {
        prev->left_ = nptr;
        nptr->parent_ = prev;
    } else {
        prev->right_ = nptr;
        nptr->parent_ = prev;
    }

    ++count_;
}

void binary_search_tree::remove(pointer ptr) {
    if (empty() || !ptr) return;
    if (!ptr->left_ && !ptr->right_) {  // 待删除节点没有子节点
        pointer parent = ptr->parent_.lock();
        if (parent) {  // 待删除节点不为根节点
            if (parent->left_ == ptr)
                parent->left_.reset();
            else
                parent->right_.reset();
            ptr.reset();
        } else  // 待删除节点为根节点
            root_.reset();
        ptr.reset();
    } else if (ptr->left_ && ptr->right_) {    // 有两个节点
        pointer succor = find_successor(ptr);  // succor一定为子节点
        if (succor->right_) {
            pointer sparent = succor->parent_.lock();  // 一定不为空
            sparent->left_ = succor->right_;
            succor->right_->parent_ = sparent;
            succor->right_.reset();
        }
        succor->parent_.reset();
        succor->left_ = ptr->left_;
        if (ptr->right_ != succor) succor->right_ = ptr->right_;
        ptr->left_->parent_ = ptr->right_->parent_ = succor;

        pointer parent = ptr->parent_.lock();
        if (parent) {
            succor->parent_ = parent;
            if (parent->left_ == ptr)
                parent->left_ = succor;
            else
                parent->right_ = succor;
        } else
            root_ = succor;
        ptr.reset();
    } else {  // 有一个节点
        pointer parent = ptr->parent_.lock();
        if (!parent)  // 待删除节点为根节点
            root_ = ptr->left_ ? ptr->left_ : ptr->right_;
        else {
            if (parent->left_ == ptr)
                parent->left_ = ptr->left_ ? ptr->left_ : ptr->right_;
            else
                parent->right_ = ptr->left_ ? ptr->left_ : ptr->right_;

            if (ptr->left_)
                ptr->left_->parent_ = parent;
            else
                ptr->right_->parent_ = parent;
        }
        ptr.reset();
    }
    --count_;
}

const binary_search_tree::pointer binary_search_tree::find_successor(pointer ptr) {
    if (!ptr || !ptr->right_) return ptr;
    ptr = ptr->right_;
    while (ptr->left_) ptr = ptr->left_;
    return ptr;
}

}  // namespace CLRS

// int main(int argc, char const* argv[]) {
//     using namespace CLRS;
//     using namespace std;

//     // random_device rd;
//     // default_random_engine gen(rd());
//     // uniform_int_distribution<> dis(1, 200);
//     auto lambda = [](int v) { cout << v << " "; };

//     binary_search_tree stree;
//     int arr[] = { 211, 450, 22, 7, 34, 98, 578, 324, 657, 56, 454, 687, 434, 34, 2 };
//     for (int i = 0; i < 15; ++i) stree.insert(arr[i]);
//     stree.walk_inorder(lambda);
//     cout << endl;

//     stree.remove(stree.max_element());
//     stree.remove(stree.min_element());
//     cout << "Size: " << stree.size() << endl;
//     stree.walk_inorder(lambda);
//     cout << endl;

//     stree.remove(stree.find(34));
//     stree.remove(stree.find(578));
//     cout << "Size: " << stree.size() << endl;
//     stree.walk_inorder(lambda);
//     cout << endl;

//     return 0;
// }
