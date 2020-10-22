#pragma once

#include <memory>
#include <vector>

namespace CLRS {

class skip_list {
public:
    skip_list() : level_(-1), header_(new skip_list_node(MAXLEVEL, 0)), count_(0) {}

    void insert(int value);
    void remove(int value);
    bool contains(int value) const;
    bool empty() const { return count_ == 0; }
    size_t size() const { return count_; }

    template <typename Func>
    void walk(const Func& f) const;

private:
    struct skip_list_node {
        int value_;
        std::vector<std::shared_ptr<skip_list_node>> next_;

        skip_list_node(int level, int value) : value_(value), next_(level) {}
    };

    using update_array = std::vector<std::shared_ptr<skip_list_node>>;
    using pointer = std::shared_ptr<skip_list_node>;

private:
    int level_;
    pointer header_;
    size_t count_;

    enum { MAXLEVEL = 12 };

    int random_level() const;
};

}  // namespace CLRS
