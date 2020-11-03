#pragma once

#include <memory>
#include <queue>

namespace CLRS {
struct huffman_node {
    unsigned long ch_feq;  // leaf node: 0xAAAAAAAAAAAAAAQQ: QQ is char, AAAAAAAAAAAAAA is frequence.
    std::shared_ptr<huffman_node> left_;
    std::shared_ptr<huffman_node> right_;

    huffman_node() : ch_feq(0), left_(), right_() {}

    // freq must less than 0x0100000000000000
    void set_value(char ch, unsigned int freq);
    unsigned int get_frequence() const;
    // not used for inner node
    char get_char() const;

    bool operator<(const huffman_node& other) const { return get_frequence() < other.get_frequence(); }
    bool operator>(const huffman_node& other) const { return get_frequence() > other.get_frequence(); }
};

class huffman_tree {
public:
    using pointer = std::shared_ptr<huffman_node>;
    struct compare_pointer {
    public:
        bool operator()(const pointer& a, const pointer& b) const { return a->get_frequence() > b->get_frequence(); }
    };
    using min_queue = std::priority_queue<pointer, std::vector<pointer>, compare_pointer>;

    huffman_tree() : root_() {}

    void build_tree(min_queue& queue);
    void print() const;

private:
    void walk(pointer p, std::vector<bool>& vec) const;

private:
    pointer root_;
};

}  // namespace CLRS
