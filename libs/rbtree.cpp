#include "rbtree.hpp"

#include <cassert>
#include <iostream>
#include <random>
#include <stack>

namespace CLRS {

const red_black_tree::pointer red_black_tree::min_element(pointer ptr) const {
    while (ptr && ptr->left_) ptr = ptr->left_;
    return ptr;
}

const red_black_tree::pointer red_black_tree::max_element(pointer ptr) const {
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

void red_black_tree::remove(pointer ptr) {
    if (!ptr) return;

    pointer child;
    if (!ptr->left_)  // no left child
        child = ptr->right_;
    else if (!ptr->right_)  // no right child
        child = ptr->left_;
    else {
        pointer successor = min_element(ptr->right_);
        pointer parent = ptr->parent_.lock();
        if (parent) {
            if (parent->left_ == ptr)
                parent->left_ = successor;
            else
                parent->right_ = successor;
        } else
            root_ = successor;

        child = successor->right_;
        parent = successor->parent_.lock();
        rb_color color = successor->color_;

        if (parent == ptr)
            parent = successor;
        else {
            if (child) child->parent_ = parent;
            parent->left_ = child;
            successor->right_ = ptr->right_;
            ptr->right_->parent_ = successor;
        }
        successor->parent_ = ptr->parent_;
        successor->color_ = ptr->color_;
        successor->left_ = ptr->left_;
        ptr->left_->parent_ = successor;
        if (color == rb_color::BLACK) handle_remove_color(child);
        --count_;
        return;
    }

    pointer parent = ptr->parent_.lock();
    rb_color color = ptr->color_;
    if (child) child->parent_ = parent;
    if (parent) {
        if (parent->left_ == ptr)
            parent->left_ = child;
        else
            parent->right_ = child;
    } else
        root_ = child;
    --count_;
}

void red_black_tree::handle_remove_color(pointer ptr) {
    while ((!ptr || ptr->color_ == rb_color::BLACK) && ptr != root_) {
        if (!ptr) return;
        pointer parent = ptr->parent_.lock();
        if (ptr == parent->left_) {
            pointer brother = parent->right_;
            if (!brother) break;
            if (brother->color_ == rb_color::RED) {
                brother->color_ = rb_color::BLACK;
                parent->color_ = rb_color::RED;
                left_rotate(parent);
                brother = parent->right_;
            }
            if (!brother || !brother->left_ || !brother->right_) break;
            if (brother->left_->color_ == rb_color::BLACK && brother->right_->color_ == rb_color::BLACK) {
                brother->color_ = rb_color::RED;
                ptr = parent;
            } else {
                if (brother->right_->color_ == rb_color::BLACK) {
                    brother->left_->color_ = rb_color::BLACK;
                    brother->color_ = rb_color::RED;
                    right_rotate(brother);
                    brother = parent->right_;
                }
                brother->color_ = parent->color_;
                parent->color_ = rb_color::BLACK;
                brother->right_->color_ = rb_color::BLACK;
                left_rotate(parent);
                ptr = root_;
                break;
            }
        } else {
            pointer brother = parent->left_;
            if (!brother) break;
            if (brother->color_ == rb_color::RED) {
                brother->color_ = rb_color::BLACK;
                parent->color_ = rb_color::RED;
                right_rotate(parent);
                brother = parent->left_;
            }
            if (!brother || !brother->left_ || !brother->right_) break;
            if (brother->left_->color_ == rb_color::BLACK && brother->right_->color_ == rb_color::BLACK) {
                brother->color_ = rb_color::RED;
                ptr = parent;
            } else {
                if (brother->left_->color_ == rb_color::BLACK) {
                    brother->right_->color_ = rb_color::BLACK;
                    brother->color_ = rb_color::RED;
                    left_rotate(brother);
                    brother = parent->left_;
                }
                brother->color_ = parent->color_;
                parent->color_ = rb_color::BLACK;
                brother->left_->color_ = rb_color::BLACK;
                left_rotate(parent);
                ptr = root_;
                break;
            }
        }
    }
    if (ptr) ptr->color_ = rb_color::BLACK;
}

void red_black_tree::left_rotate(pointer ptr) {
    assert(ptr->right_);
    pointer right = ptr->right_;
    pointer parent = ptr->parent_.lock();

    ptr->right_ = right->left_;
    if (right->left_) right->left_->parent_ = ptr;
    right->left_ = ptr;
    right->parent_ = parent;
    if (!parent)
        root_ = right;
    else {
        if (ptr == ptr->parent_.lock()->left_)
            parent->left_ = right;
        else
            parent->right_ = right;
    }
    ptr->parent_ = right;
}

void red_black_tree::right_rotate(pointer ptr) {
    assert(ptr->left_);
    pointer left = ptr->left_;
    pointer parent = ptr->parent_.lock();

    ptr->left_ = left->right_;
    if (left->right_) left->right_->parent_ = ptr;
    left->right_ = ptr;
    left->parent_ = parent;
    if (!parent)
        root_ = left;
    else {
        if (ptr == parent->right_)
            parent->right_ = left;
        else
            parent->left_ = left;
    }
    ptr->parent_ = left;
}

size_t red_black_tree::count(pointer ptr) const {
    if (!ptr) return 0;
    return 1 + count(ptr->left_) + count(ptr->right_);
}

}  // namespace CLRS

// int main(int argc, char const* argv[]) {
//     using namespace CLRS;
//     using namespace std;
//     random_device rd;
//     default_random_engine gen(rd());
//     uniform_int_distribution<> dis(10, 1000);

//     // vector<pair<size_t, size_t>> pt;
//     // for (int i = 0; i < 1000; i++) {
//     //     red_black_tree rb;
//     //     while (rb.size() != 1000) rb.insert(dis(gen));
//     //     pt.push_back(make_pair(rb.left_count(rb.root()), rb.right_count(rb.root())));
//     // }

//     // size_t left_sum = 0;
//     // size_t right_sum = 0;
//     // for (auto i : pt) {
//     //     left_sum += i.first;
//     //     right_sum += i.second;
//     // }
//     // cout << "Left Average: " << left_sum / 1000 << endl;
//     // cout << "Right Average: " << right_sum / 1000 << endl;

//     red_black_tree rb;
//     for (int i = 0; i < 1000; ++i) rb.insert(i);
//     cout << "Left Size: " << rb.left_count(rb.root()) << endl;
//     cout << "Right Size: " << rb.right_count(rb.root()) << endl;

//     while (rb.size() > 500) rb.remove(rb.find(dis(gen)));

//     cout << "Left Size: " << rb.left_count(rb.root()) << endl;
//     cout << "Right Size: " << rb.right_count(rb.root()) << endl;

//     return 0;
// }
