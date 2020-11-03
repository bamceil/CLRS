#include "huffman.hpp"

#include <cassert>
#include <iostream>

namespace CLRS {
void huffman_node::set_value(char ch, unsigned int freq) {
    assert(freq <= 0x00FFFFFFFFFFFFFF);
    ch_feq |= (freq << 8);
    ch_feq |= ch;
}

unsigned int huffman_node::get_frequence() const {
    unsigned int v = ch_feq;
    return (v & 0xFFFFFFFFFFFFFF00) >> 8;
}

char huffman_node::get_char() const {
    assert(!left_ && !right_);
    unsigned int v = ch_feq;
    return (v & 0x00000000000000FF);
}

void huffman_tree::build_tree(min_queue& queue) {
    assert(queue.size() > 1);

    while (queue.size() != 1) {
        pointer p(new huffman_node);
        p->left_ = queue.top();
        queue.pop();
        p->right_ = queue.top();
        queue.pop();
        p->set_value(0, p->left_->get_frequence() + p->right_->get_frequence());
        queue.push(p);
    }

    root_ = queue.top();
    queue.pop();
    assert(queue.empty());
}

void huffman_tree::print() const {
    std::vector<bool> vec;
    walk(root_, vec);
}

void huffman_tree::walk(pointer p, std::vector<bool>& vec) const {
    if (!p->left_ && !p->right_) {
        std::cout << p->get_char() << "(" << p->get_frequence() << ") :";
        for (bool b : vec) std::cout << b;
        std::cout << std::endl;
        return;
    }
    vec.push_back(false);
    walk(p->left_, vec);
    vec.pop_back();
    vec.push_back(true);
    walk(p->right_, vec);
    vec.pop_back();
}
}  // namespace CLRS

// int main(int argc, char const* argv[]) {
//     using namespace CLRS;
//     using namespace std;

//     huffman_tree::min_queue queue;
//     for (int i = 0; i < 126 - 'A'; i++) {
//         huffman_tree::pointer p(new huffman_node);
//         p->set_value('A' + i, i + 1);
//         queue.push(p);
//     }
//     huffman_tree t;
//     t.build_tree(queue);
//     t.print();

//     return 0;
// }
