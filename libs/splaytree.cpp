#include "splaytree.hpp"

#include <cassert>
#include <iostream>
#include <random>
#include <stack>

namespace CLRS {
void splay_tree::walk_preorder(const std::function<void(int)>& f) const {
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

void splay_tree::walk_inorder(const std::function<void(int)>& f) const {
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

void splay_tree::walk_postorder(const std::function<void(int)>& f) const {
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

void splay_tree::rotate_left(pointer ptr) {
    assert(ptr->right_);
    pointer right = ptr->right_;
    ptr->right_ = right->left_;
    if (right->left_) right->left_->parent_ = ptr;
    right->parent_ = ptr->parent_;
    if (!ptr->parent_.expired()) {
        pointer parent = ptr->parent_.lock();
        if (ptr == parent->left_)
            parent->left_ = right;
        else
            parent->right_ = right;
    }
    right->left_ = ptr;
    ptr->parent_ = right;
}

void splay_tree::rotate_right(pointer ptr) {
    assert(ptr->left_);
    pointer left = ptr->left_;
    ptr->left_ = left->right_;
    if (left->right_) left->right_->parent_ = ptr;
    left->parent_ = ptr->parent_;
    if (!ptr->parent_.expired()) {
        pointer parent = ptr->parent_.lock();
        if (ptr == parent->left_)
            parent->left_ = left;
        else
            parent->right_ = left;
    }
    left->right_ = ptr;
    ptr->parent_ = left;
}

void splay_tree::splay(pointer ptr) {
    while (!ptr->parent_.expired()) {
        pointer parent = ptr->parent_.lock();
        pointer gparent = parent->parent_.lock();
        if (!gparent) {
            if (parent->left_ == ptr)
                rotate_right(parent);
            else
                rotate_left(parent);
        } else if (parent->left_ == ptr && gparent->left_ == parent) {
            rotate_right(gparent);
            rotate_right(ptr->parent_.lock());
        } else if (parent->right_ == ptr && gparent->right_ == parent) {
            rotate_left(gparent);
            rotate_left(ptr->parent_.lock());
        } else if (parent->left_ == ptr && gparent->right_ == parent) {
            rotate_right(parent);
            rotate_left(ptr->parent_.lock());
        } else {
            rotate_left(parent);
            rotate_right(ptr->parent_.lock());
        }
    }
}

const splay_tree::pointer splay_tree::find(int value) {
    pointer root = root_;
    while (root && root->value_ != value) {
        if (value < root->value_)
            root = root->left_;
        else
            root = root->right_;
    }
    if (!root)
        return root;
    else
        splay(root);
    root_ = root;
    return root_;
}

const splay_tree::pointer splay_tree::min_element() {
    pointer ptr = root_;
    while (ptr && ptr->left_) ptr = ptr->left_;
    if (!ptr)
        return ptr;
    else
        splay(ptr);
    root_ = ptr;
    return root_;
}

const splay_tree::pointer splay_tree::max_element() {
    pointer ptr = root_;
    while (ptr && ptr->right_) ptr = ptr->right_;
    if (!ptr)
        return ptr;
    else
        splay(ptr);
    root_ = ptr;
    return root_;
}

void splay_tree::insert(int value) {
    pointer ptr = root_;
    pointer prev;
    while (ptr) {
        prev = ptr;
        if (value < ptr->value_)
            ptr = ptr->left_;
        else
            ptr = ptr->right_;
    }
    ptr.reset(new splay_node(value));
    ptr->parent_ = prev;

    if (!prev)
        root_ = ptr;
    else if (value < prev->value_)
        prev->left_ = ptr;
    else
        prev->right_ = ptr;

    splay(ptr);
    root_ = ptr;
    ++count_;
}

splay_tree::pointer splay_tree::min_element(pointer ptr) {
    while (ptr && ptr->left_) ptr = ptr->left_;
    return ptr;
}

void splay_tree::replace(pointer u, pointer v) {
    pointer parent = u->parent_.lock();
    if (!parent)
        root_ = v;
    else if (u == parent->left_)
        parent->left_ = v;
    else
        parent->right_ = v;
    if (v) v->parent_ = parent;
}

void splay_tree::remove(int value) {
    pointer ptr = find(value);
    if (!ptr) return;

    if (!ptr->left_)
        replace(ptr, ptr->right_);
    else if (!ptr->right_)
        replace(ptr, ptr->left_);
    else {
        pointer maxip = min_element(ptr->right_);
        if (maxip->parent_.lock() != ptr) {
            replace(maxip, maxip->right_);
            maxip->right_ = ptr->right_;
            maxip->right_->parent_ = maxip;
        }
        replace(ptr, maxip);
        maxip->left_ = ptr->left_;
        maxip->left_->parent_ = maxip;
    }
    ptr.reset();
    --count_;
}

}  // namespace CLRS

// int main(int argc, char const* argv[]) {
//     using namespace std;
//     using namespace CLRS;

//     random_device rd;
//     default_random_engine gen(rd());
//     uniform_int_distribution<> dis(-1000, 1000);

//     splay_tree tree;
//     while (tree.size() < 1000) {
//         tree.insert(dis(gen));
//     }
//     cout << "Size: " << tree.size() << endl;
//     for (int i = -1000; tree.size() > 100; i++) {
//         if (i > 1000) i = -1000;
//         tree.remove(i);
//     }
//     cout << "Size: " << tree.size() << endl;
//     tree.walk_inorder([](int i) { cout << i << " "; });
//     cout << endl;

//     return 0;
// }
