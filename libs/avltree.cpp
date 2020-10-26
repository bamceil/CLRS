#include "avltree.hpp"

#include <iostream>
#include <stack>

namespace CLRS {
void avltree::walk_preorder(std::function<void(int)> f) const {
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

void avltree::walk_inorder(std::function<void(int)> f) const {
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

void avltree::walk_postorder(std::function<void(int)> f) const {
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

const avltree::pointer avltree::find(int value) const {
    std::shared_ptr<avltree_node> root = root_;
    while (root && root->value_ != value) {
        if (value < root->value_)
            root = root->left_;
        else
            root = root->right_;
    }
    return root;
}

const avltree::pointer avltree::min_element(pointer ptr) const {
    while (ptr && ptr->left_) ptr = ptr->left_;
    return ptr;
}
const avltree::pointer avltree::max_element(pointer ptr) const {
    while (ptr && ptr->right_) ptr = ptr->right_;
    return ptr;
}

avltree::pointer avltree::rotate_LL(pointer ptr) {
    pointer p = ptr->left_;
    ptr->left_ = p->right_;
    p->right_ = ptr;

    ptr->height_ = std::max(height(ptr->left_), height(ptr->right_)) + 1;
    p->height_ = std::max(height(p->left_), ptr->height_) + 1;

    return p;
}

avltree::pointer avltree::rotate_RR(pointer ptr) {
    pointer p = ptr->right_;
    ptr->right_ = p->left_;
    p->left_ = ptr;

    ptr->height_ = std::max(height(ptr->left_), height(ptr->right_)) + 1;
    p->height_ = std::max(height(p->right_), ptr->height_) + 1;

    return p;
}

avltree::pointer avltree::rotate_LR(pointer ptr) {
    ptr->left_ = rotate_RR(ptr->left_);
    return rotate_LL(ptr);
}

avltree::pointer avltree::rotate_RL(pointer ptr) {
    ptr->right_ = rotate_LL(ptr->right_);
    return rotate_RR(ptr);
}

avltree::pointer avltree::insert(pointer ptr, int value) {
    if (!ptr)
        ptr.reset(new avltree_node(value));
    else if (value < ptr->value_) {
        ptr->left_ = insert(ptr->left_, value);
        if (height(ptr->left_) - height(ptr->right_) >= 2) {
            if (value < ptr->left_->value_)
                ptr = rotate_LL(ptr);
            else
                ptr = rotate_LR(ptr);
        }
    } else {
        ptr->right_ = insert(ptr->right_, value);
        if (height(ptr->right_) - height(ptr->left_) >= 2) {
            if (value >= ptr->right_->value_)
                ptr = rotate_RR(ptr);
            else
                ptr = rotate_RL(ptr);
        }
    }
    ptr->height_ = std::max(height(ptr->left_), height(ptr->right_)) + 1;
    return ptr;
}

void avltree::insert(int value) {
    root_ = insert(root_, value);
    ++count_;
}

avltree::pointer avltree::remove(pointer root, pointer ptr) {
    if (!root || !ptr) {
        return pointer();
    }
    if (ptr->value_ < root->value_) {
        root->left_ = remove(root->left_, ptr);
        if (height(root->right_) - height(root->left_) >= 2) {
            pointer right = root->right_;
            if (height(right->left_) > height(right->right_))
                root = rotate_RL(root);
            else
                root = rotate_RR(root);
        }
    } else if (ptr->value_ > root->value_) {
        root->right_ = remove(root->right_, ptr);
        if (height(root->left_) - height(root->right_) >= 2) {
            pointer left = root->left_;
            if (height(left->right_) > height(left->left_))
                root = rotate_LR(root);
            else
                root = rotate_LL(root);
        }
    } else {
        if (root->left_ && root->right_) {
            if (height(root->left_) > height(root->right_)) {
                pointer p = max_element(root->left_);
                root->value_ = p->value_;
                root->left_ = remove(root->left_, p);
            } else {
                pointer p = min_element(root->right_);
                root->value_ = p->value_;
                root->right_ = remove(root->right_, p);
            }
        } else {
            pointer p = root;
            root = root->left_ ? root->left_ : root->right_;
            p.reset();
        }
    }
    if (root) root->height_ = std::max(height(root->left_), height(root->right_)) + 1;
    return root;
}

void avltree::remove(int value) {
    pointer p = find(value);
    if (p) {
        root_ = remove(root_, p);
        --count_;
    }
}
}  // namespace CLRS

// int main(int argc, char const* argv[]) {
//     using namespace std;
//     using namespace CLRS;

//     avltree avl;
//     for (int i = 0; i < 1000; i++) {
//         avl.insert(i);
//     }

//     // avl.walk_inorder([](int i) { cout << i << " "; });
//     cout << endl;
//     cout << "Height: " << avl.height() << endl << "Size: " << avl.size() << endl;

//     int i = 999;
//     while (avl.size() > 100) {
//         avl.remove(i);
//         i--;
//     }

//     // avl.walk_inorder([](int i) { cout << i << " "; });
//     cout << endl;
//     cout << "Height: " << avl.height() << endl << "Size: " << avl.size() << endl;

//     return 0;
// }
