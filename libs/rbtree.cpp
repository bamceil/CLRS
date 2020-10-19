#include "rbtree.hpp"

#include <cassert>
#include <iostream>
#include <random>
#include <stack>

namespace CLRS {
const red_black_tree::pointer red_black_tree::min_element() const {
    pointer ptr = root_;
    while (ptr && ptr->left_) ptr = ptr->left_;
    return ptr;
}

const red_black_tree::pointer red_black_tree::max_element() const {
    pointer ptr = root_;
    while (ptr && ptr->right_) ptr = ptr->right_;
    return ptr;
}

void red_black_tree::walk_preorder(std::function<void(int)> f) const {
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

void red_black_tree::walk_inorder(std::function<void(int)> f) const {
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

void red_black_tree::walk_postorder(std::function<void(int)> f) const {
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

red_black_tree::pointer red_black_tree::find(int value) const {
    pointer root = root_;
    while (root && root->value_ != value) {
        if (value < root->value_)
            root = root->left_;
        else
            root = root->right_;
    }
    return root;
}

void red_black_tree::insert(int value) {
    pointer ptr(new rb_node(value));
    pointer x = root_, y;
    while (x) {
        y = x;
        if (value < x->value_)
            x = x->left_;
        else
            x = x->right_;
    }
    ptr->parent_ = y;
    if (!y)
        root_ = ptr;
    else if (value < y->value_)
        y->left_ = ptr;
    else
        y->right_ = ptr;
    handle_insert_color(ptr);
    ++count_;
}

void red_black_tree::handle_insert_color(pointer ptr) {
    while (!ptr->parent_.expired()) {
        pointer parent = ptr->parent_.lock();
        if (parent->color_ != rb_color::RED) break;
        pointer gparent = parent->parent_.lock();
        if (!gparent) break;
        if (parent == gparent->left_) {
            pointer uncle = gparent->right_;
            if (uncle && uncle->color_ == rb_color::RED) {
                parent->color_ = rb_color::BLACK;
                uncle->color_ = rb_color::BLACK;
                gparent->color_ = rb_color::RED;
                ptr = gparent;
            } else {
                if (ptr == parent->right_) {
                    ptr = parent;
                    left_rotate(ptr);
                }
                pointer pptr = ptr->parent_.lock();
                if (pptr) {
                    pptr->color_ = rb_color::BLACK;
                    pointer gptr = pptr->parent_.lock();
                    if (gptr) gptr->color_ = rb_color::RED;
                    right_rotate(gptr);
                }
            }
        } else {
            pointer uncle = gparent->left_;
            if (uncle && uncle->color_ == rb_color::RED) {
                parent->color_ = rb_color::BLACK;
                uncle->color_ = rb_color::BLACK;
                gparent->color_ = rb_color::RED;
                ptr = gparent;
            } else {
                if (ptr == parent->left_) {
                    ptr = parent;
                    right_rotate(parent);
                }
                pointer pptr = ptr->parent_.lock();
                if (pptr) {
                    pptr->color_ = rb_color::BLACK;
                    pointer gptr = pptr->parent_.lock();
                    if (gptr) gptr->color_ = rb_color::RED;
                    left_rotate(gptr);
                }
            }
        }
    }
    root_->color_ = rb_color::BLACK;
}

void red_black_tree::remove(pointer ptr) {}

void red_black_tree::left_rotate(pointer ptr) {
    assert(ptr->right_);
    pointer y = ptr->right_;
    if (!y) return;
    ptr->right_ = y->left_;
    if (y->left_) y->left_->parent_ = ptr;
    y->parent_ = ptr->parent_;
    if (ptr->parent_.expired())
        root_ = y;
    else if (ptr == ptr->parent_.lock()->left_)
        ptr->parent_.lock()->left_ = y;
    else
        ptr->parent_.lock()->right_ = y;
    y->left_ = ptr;
    ptr->parent_ = y;
}

void red_black_tree::right_rotate(pointer ptr) {
    assert(ptr->left_);
    pointer x = ptr->left_;
    ptr->left_ = x->right_;
    if (x->right_) x->right_->parent_ = ptr;
    x->parent_ = ptr->parent_;
    if (ptr->parent_.expired())
        root_ = x;
    else if (ptr == ptr->parent_.lock()->left_)
        ptr->parent_.lock()->left_ = x;
    else
        ptr->parent_.lock()->right_ = x;
    x->right_ = ptr;
    ptr->parent_ = x;
}

size_t red_black_tree::count(pointer ptr) const {
    if (!ptr) return 0;
    return 1 + count(ptr->left_) + count(ptr->right_);
}

}  // namespace CLRS

int main(int argc, char const* argv[]) {
    using namespace CLRS;
    using namespace std;
    random_device rd;
    default_random_engine gen(rd());
    uniform_int_distribution<> dis(10, 1000);

    vector<pair<size_t, size_t>> pt;
    for (int i = 0; i < 1000; i++) {
        red_black_tree rb;
        while (rb.size() != 1000) rb.insert(dis(gen));
        pt.push_back(make_pair(rb.left_count(rb.root()), rb.right_count(rb.root())));
    }

    size_t left_sum = 0;
    size_t right_sum = 0;
    for (auto i : pt) {
        left_sum += i.first;
        right_sum += i.second;
    }
    cout << "Left Average: " << left_sum / 1000 << endl;
    cout << "Right Average: " << right_sum / 1000 << endl;

    return 0;
}
