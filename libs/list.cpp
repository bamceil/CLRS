#include "list.hpp"

#include <cassert>
#include <iostream>

using namespace std;

namespace CLRS {
void list::push_back(int value) {
    shared_ptr<inner_node> inode(new inner_node);
    inode->value_ = value;
    inode->prev_ = tail_;
    if (count_ == 0) {
        head_ = tail_ = inode;
    } else {
        tail_->next_ = inode;
        tail_ = inode;
    }
    ++count_;
}

void list::push_front(int value) {
    shared_ptr<inner_node> inode(new inner_node);
    inode->value_ = value;
    inode->next_ = head_;
    if (count_ == 0) {
        head_ = tail_ = inode;
    } else {
        head_->prev_ = inode;
        head_ = inode;
    }
    ++count_;
}

void list::pop_back() {
    if (empty()) return;
    auto prev = tail_->prev_.lock();
    if (prev) {
        prev->next_.reset();
        tail_.reset();
        tail_ = prev;
    } else {
        head_.reset();
        tail_.reset();
    }
    --count_;
}
void list::pop_front() {
    if (empty()) return;
    auto next = head_->next_;
    if (next) {
        head_->next_.reset();
        head_.reset();
        head_ = next;
    } else {
        head_.reset();
        tail_.reset();
    }
    --count_;
}

void list::remove(shared_ptr<inner_node> iter) {
    if (!iter) return;
    auto prev = iter->prev_.lock();
    if (prev) {
        prev->next_ = iter->next_;
        if (iter->next_)
            iter->next_->prev_ = prev;
        else
            tail_ = prev;
    } else {
        head_ = iter->next_;
        if (head_)
            head_->prev_.reset();
        else
            tail_.reset();
    }
    --count_;
}

const shared_ptr<inner_node> list::find(int target) const {
    auto head = head_;
    while (head) {
        if (head->value_ == target) return head;
        head = head->next_;
    }
    return shared_ptr<inner_node>();
}

void list::print() const {
    auto head = head_;
    while (head) {
        cout << head->value_ << " \tuse: " << head.use_count() << endl;
        head = head->next_;
    }
    cout << endl;
}
}  // namespace CLRS

// int main(int argc, char const* argv[]) {
//     using namespace CLRS;
//     list ls;
//     for (int i = 0; i < 2; ++i) ls.push_front(i);
//     cout << ls.size() << endl;
//     ls.pop_front();
//     ls.print();
//     cout << "-------" << endl;
//     ls.pop_back();
//     ls.print();

//     return 0;
// }
